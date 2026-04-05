/* Blit utility function */
#include "blit.h"

#include <math.h>

#include "fpe.h"
#include "fpe_core.h"
#include "glstate.h"
#include "init.h"
#ifdef TEXSTREAM
#ifndef GL_TEXTURE_STREAM_IMG
#define GL_TEXTURE_STREAM_IMG 0x8C0Ds
#endif
#include "../glx/streaming.h"
#endif

// hacky viewport temporary changes
void pushViewport(GLint x, GLint y, GLsizei width, GLsizei height);
void popViewport();

const char _blit_vsh[] = "#version 100                  \n"
                         "attribute highp vec2 aPosition;                        \n"
                         "attribute highp vec2 aTexCoord;                        \n"
                         "varying mediump vec2 vTexCoord;                        \n"
                         "void main(){                                           \n"
                         "gl_Position = vec4(aPosition.x, aPosition.y, 0.0, 1.0);\n"
                         "vTexCoord = aTexCoord;                                 \n"
                         "}                                                      \n";

const char _blit_fsh[] = "#version 100                  \n"
                         "uniform sampler2D uTex;                                \n"
                         "varying mediump vec2 vTexCoord;                        \n"
                         "void main(){                                           \n"
                         "gl_FragColor = texture2D(uTex, vTexCoord);             \n"
                         "}                                                      \n";

const char _blit_vsh_alpha[] = "#version 100            \n"
                               "attribute highp vec2 aPosition;                        \n"
                               "attribute highp vec2 aTexCoord;                        \n"
                               "varying mediump vec2 vTexCoord;                        \n"
                               "void main(){                                           \n"
                               "gl_Position = vec4(aPosition.x, aPosition.y, 0.0, 1.0);\n"
                               "vTexCoord = aTexCoord;                                 \n"
                               "}                                                      \n";

const char _blit_fsh_alpha[] = "#version 100            \n"
                               "uniform sampler2D uTex;                                \n"
                               "varying mediump vec2 vTexCoord;                        \n"
                               "void main(){                                           \n"
                               "lowp vec4 p = texture2D(uTex, vTexCoord);              \n"
                               "if (p.a==0.0) discard;                                 \n"
                               "gl_FragColor = p;                                      \n"
                               "}                                                      \n";

void fpe4es_blitTexture_gles2(GLuint texture, GLfloat sx, GLfloat sy, GLfloat width, GLfloat height, GLfloat nwidth,
                              GLfloat nheight, GLfloat zoomx, GLfloat zoomy, GLfloat vpwidth, GLfloat vpheight,
                              GLfloat x, GLfloat y, GLint mode) {

    if (!glstate->blit) {
        glstate->blit = (glesblit_t*)malloc(sizeof(glesblit_t));
        memset(glstate->blit, 0, sizeof(glesblit_t));

        GLint success;
        const char* src[1];
        src[0] = _blit_fsh;
        glstate->blit->pixelshader = GLES.glCreateShader(GL_FRAGMENT_SHADER);
        GLES.glShaderSource(glstate->blit->pixelshader, 1, (const char**)src, NULL);
        GLES.glCompileShader(glstate->blit->pixelshader);
        GLES.glGetShaderiv(glstate->blit->pixelshader, GL_COMPILE_STATUS, &success);
        if (!success) {
            char log[400];
            GLES.glGetShaderInfoLog(glstate->blit->pixelshader, 399, NULL, log);
            free(glstate->blit);
            glstate->blit = NULL;
        }

        src[0] = _blit_fsh_alpha;
        glstate->blit->pixelshader_alpha = GLES.glCreateShader(GL_FRAGMENT_SHADER);
        GLES.glShaderSource(glstate->blit->pixelshader_alpha, 1, (const char**)src, NULL);
        GLES.glCompileShader(glstate->blit->pixelshader_alpha);
        GLES.glGetShaderiv(glstate->blit->pixelshader_alpha, GL_COMPILE_STATUS, &success);
        if (!success) {
            char log[400];
            GLES.glGetShaderInfoLog(glstate->blit->pixelshader_alpha, 399, NULL, log);
            free(glstate->blit);
            glstate->blit = NULL;
        }

        src[0] = _blit_vsh;
        glstate->blit->vertexshader = GLES.glCreateShader(GL_VERTEX_SHADER);
        GLES.glShaderSource(glstate->blit->vertexshader, 1, (const char**)src, NULL);
        GLES.glCompileShader(glstate->blit->vertexshader);
        GLES.glGetShaderiv(glstate->blit->vertexshader, GL_COMPILE_STATUS, &success);
        if (!success) {
            char log[400];
            GLES.glGetShaderInfoLog(glstate->blit->vertexshader, 399, NULL, log);
            free(glstate->blit);
            glstate->blit = NULL;
        }

        src[0] = _blit_vsh_alpha;
        glstate->blit->vertexshader_alpha = GLES.glCreateShader(GL_VERTEX_SHADER);
        GLES.glShaderSource(glstate->blit->vertexshader_alpha, 1, (const char**)src, NULL);
        GLES.glCompileShader(glstate->blit->vertexshader_alpha);
        GLES.glGetShaderiv(glstate->blit->vertexshader_alpha, GL_COMPILE_STATUS, &success);
        if (!success) {
            char log[400];
            GLES.glGetShaderInfoLog(glstate->blit->vertexshader_alpha, 399, NULL, log);
            free(glstate->blit);
            glstate->blit = NULL;
        }

        glstate->blit->program = GLES.glCreateProgram();
        GLES.glBindAttribLocation(glstate->blit->program, 0, "aPosition");
        GLES.glBindAttribLocation(glstate->blit->program, 1, "aTexCoord");
        GLES.glAttachShader(glstate->blit->program, glstate->blit->pixelshader);
        GLES.glAttachShader(glstate->blit->program, glstate->blit->vertexshader);
        GLES.glLinkProgram(glstate->blit->program);
        GLES.glGetProgramiv(glstate->blit->program, GL_LINK_STATUS, &success);
        if (!success) {
            free(glstate->blit);
            glstate->blit = NULL;
        }
        GLuint oldprog = glstate->gleshard->program;
        GLES.glUseProgram(glstate->blit->program);
        GLES.glUniform1i(GLES.glGetUniformLocation(glstate->blit->program, "uTex"), 0);

        glstate->blit->program_alpha = GLES.glCreateProgram();
        GLES.glBindAttribLocation(glstate->blit->program_alpha, 0, "aPosition");
        GLES.glBindAttribLocation(glstate->blit->program_alpha, 1, "aTexCoord");
        GLES.glAttachShader(glstate->blit->program_alpha, glstate->blit->pixelshader_alpha);
        GLES.glAttachShader(glstate->blit->program_alpha, glstate->blit->vertexshader_alpha);
        GLES.glLinkProgram(glstate->blit->program_alpha);
        GLES.glGetProgramiv(glstate->blit->program_alpha, GL_LINK_STATUS, &success);
        if (!success) {
            free(glstate->blit);
            glstate->blit = NULL;
        }
        GLES.glUseProgram(glstate->blit->program_alpha);
        GLES.glUniform1i(GLES.glGetUniformLocation(glstate->blit->program_alpha, "uTex"), 0);
        GLES.glUseProgram(oldprog);
    }

    int customvp = (vpwidth > 0.0);
    GLfloat w2 = 2.0f / (customvp ? vpwidth : glstate->raster.viewport.width);
    GLfloat h2 = 2.0f / (customvp ? vpheight : glstate->raster.viewport.height);
    GLfloat blit_x1 = roundf(x);
    GLfloat blit_x2 = roundf(x + width * zoomx);
    GLfloat blit_y1 = roundf(y);
    GLfloat blit_y2 = roundf(y + height * zoomy);
    GLfloat* vert = glstate->blit->vert;
    GLfloat* tex = glstate->blit->tex;
    vert[0] = blit_x1 * w2 - 1.0f;
    vert[1] = blit_y1 * h2 - 1.0f;
    vert[2] = blit_x2 * w2 - 1.0f;
    vert[3] = vert[1];
    vert[4] = vert[2];
    vert[5] = blit_y2 * h2 - 1.0f;
    vert[6] = vert[0];
    vert[7] = vert[5];
    GLfloat sw = sx / nwidth;
    GLfloat sh = sy / nheight;
    GLfloat rw = (sx + width) / nwidth;
    GLfloat rh = (sy + height) / nheight;
    tex[0] = sw;
    tex[1] = sh;
    tex[2] = rw;
    tex[3] = sh;
    tex[4] = rw;
    tex[5] = rh;
    tex[6] = sw;
    tex[7] = rh;
    fpe4es_glDisable(GL_BLEND);
    int alpha = 0;
    switch (mode) {
    case BLIT_OPAQUE:
        // fpe4es_glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        break;
    case BLIT_ALPHA:
        alpha = 1;
        break;
    case BLIT_COLOR:
        // fpe4es_glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        break;
    }

    realize_blitenv(alpha);

    GLES.glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void fpe4es_blitTexture(GLuint texture, GLfloat sx, GLfloat sy, GLfloat width, GLfloat height, GLfloat nwidth,
                        GLfloat nheight, GLfloat zoomx, GLfloat zoomy, GLfloat vpwidth, GLfloat vpheight, GLfloat x,
                        GLfloat y, GLint mode) {
    // printf("blitTexture(%d, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %d) customvp=%d, vp=%d/%d/%d/%d\n",
    // texture, sx, sy, width, height, nwidth, nheight, zoomx, zoomy, vpwidth, vpheight, x, y, mode, (vpwidth>0.0),
    // glstate->raster.viewport.x, glstate->raster.viewport.y, glstate->raster.viewport.width,
    // glstate->raster.viewport.height);

    realize_textures(1);

    fpe4es_glPushAttrib(GL_TEXTURE_BIT | GL_ENABLE_BIT | GL_TRANSFORM_BIT | GL_COLOR_BUFFER_BIT | GL_CURRENT_BIT);

    if (glstate->gleshard->active) {
        glstate->gleshard->active = 0;
        GLES.glActiveTexture(GL_TEXTURE0);
    }

    GLint depthwrite = glstate->depth.mask;

    fpe4es_glDisable(GL_DEPTH_TEST);
    fpe4es_glDisable(GL_CULL_FACE);
    fpe4es_glDisable(GL_STENCIL_TEST);

    if (depthwrite) fpe4es_glDepthMask(GL_FALSE);

#ifdef TEXSTREAM
    // Streaming not supported in GLES2-only mode
#endif
    int tmp = glstate->enable.texture[0];

    if (glstate->actual_tex2d[0] != texture) GLES.glBindTexture(GL_TEXTURE_2D, texture);

    fpe4es_blitTexture_gles2(texture, sx, sy, width, height, nwidth, nheight, zoomx, zoomy, vpwidth, vpheight, x, y,
                             mode);

    // All the previous states are Pushed / Poped anyway...
    if (glstate->actual_tex2d[0] != texture) GLES.glBindTexture(GL_TEXTURE_2D, glstate->actual_tex2d[0]);

    if (depthwrite) fpe4es_glDepthMask(GL_TRUE);

    fpe4es_glPopAttrib();
}
