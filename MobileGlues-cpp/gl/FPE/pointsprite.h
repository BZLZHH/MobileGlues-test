#ifndef _FPE4ES_POINTSPRITE_H_
#define _FPE4ES_POINTSPRITE_H_



typedef struct {
    GLfloat size;
    GLfloat sizeMin;
    GLfloat sizeMax;
    GLfloat fadeThresholdSize;
    GLfloat distance[3];
    GLenum coordOrigin;
} pointsprite_t;

void APIENTRY_FPE4ES fpe4es_glPointParameteri(GLenum pname, GLint param);
void APIENTRY_FPE4ES fpe4es_glPointParameteriv(GLenum pname, const GLint* params);
void APIENTRY_FPE4ES fpe4es_glPointParameterf(GLenum pname, GLfloat param);
void APIENTRY_FPE4ES fpe4es_glPointParameterfv(GLenum pname, const GLfloat* params);

void APIENTRY_FPE4ES fpe4es_glPointSize(GLfloat size);

#endif // _FPE4ES_POINTSPRITE_H_
