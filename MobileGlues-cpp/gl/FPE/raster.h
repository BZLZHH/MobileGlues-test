#ifndef _FPE4ES_RASTER_H_
#define _FPE4ES_RASTER_H_


#include "list.h"

#ifndef GL_STENCIL_INDEX
#define GL_STENCIL_INDEX 0x1901
#endif // GL_STENCIL_INDEX
#ifndef GL_DEPTH_COMPONENT
#define GL_DEPTH_COMPONENT 0x1902
#endif // GL_DEPTH_COMPONENT

typedef struct {
    GLfloat x;
    GLfloat y;
    GLfloat z;
} rasterpos_t;

typedef struct {
    GLint x;
    GLint y;
    GLsizei width;
    GLsizei height;
} viewport_t;

int raster_need_transform();

void APIENTRY_FPE4ES fpe4es_glBitmap(GLsizei width, GLsizei height, GLfloat xorig, GLfloat yorig, GLfloat xmove,
                                     GLfloat ymove, const GLubyte* bitmap);
void APIENTRY_FPE4ES fpe4es_glDrawPixels(GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* data);
void APIENTRY_FPE4ES fpe4es_glRasterPos3f(GLfloat x, GLfloat y, GLfloat z);
void APIENTRY_FPE4ES fpe4es_glWindowPos3f(GLfloat x, GLfloat y, GLfloat z);
void APIENTRY_FPE4ES fpe4es_glViewport(GLint x, GLint y, GLsizei width, GLsizei height);
void render_raster();

void APIENTRY_FPE4ES fpe4es_glPixelZoom(GLfloat xfactor, GLfloat yfactor);

void APIENTRY_FPE4ES fpe4es_glPixelTransferf(GLenum pname, GLfloat param);

void APIENTRY_FPE4ES fpe4es_glPixelMapfv(GLenum map, GLsizei mapsize, const GLfloat* values);
void APIENTRY_FPE4ES fpe4es_glPixelMapuiv(GLenum map, GLsizei mapsize, const GLuint* values);
void APIENTRY_FPE4ES fpe4es_glPixelMapusv(GLenum map, GLsizei mapsize, const GLushort* values);
void APIENTRY_FPE4ES fpe4es_glGetPixelMapfv(GLenum map, GLfloat* data);
void APIENTRY_FPE4ES fpe4es_glGetPixelMapuiv(GLenum map, GLuint* data);
void APIENTRY_FPE4ES fpe4es_glGetPixelMapusv(GLenum map, GLushort* data);

void render_raster_list(rasterlist_t* raster);

void bitmap_flush();

#endif // _FPE4ES_RASTER_H_
