#ifndef _FPE4ES_FOG_H_
#define _FPE4ES_FOG_H_



typedef struct {
    GLenum mode;
    GLfloat density;
    GLenum distance;
    GLfloat start;
    GLfloat end;
    GLfloat index;
    GLfloat color[4];
    GLenum coord_src;
} fog_t;

void APIENTRY_FPE4ES fpe4es_glFogfv(GLenum pname, const GLfloat* params);
void APIENTRY_FPE4ES fpe4es_glFogf(GLenum pname, GLfloat param);

void APIENTRY_FPE4ES fpe4es_glFogCoordf(GLfloat coord);
void APIENTRY_FPE4ES fpe4es_glFogCoordfv(const GLfloat* coord);

#endif // _FPE4ES_FOG_H_
