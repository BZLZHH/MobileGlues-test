#ifndef _FPE4ES_TEXGEN_H_
#define _FPE4ES_TEXGEN_H_

void APIENTRY_FPE4ES fpe4es_glTexGenfv(GLenum coord, GLenum pname, const GLfloat* params);
void APIENTRY_FPE4ES fpe4es_glTexGeni(GLenum coord, GLenum pname, GLint param);
void gen_tex_coords(GLfloat* verts, GLfloat* norm, GLfloat** coords, GLint count, GLint* needclean, int texture,
                    GLushort* indices, GLuint ilen);
void gen_tex_clean(GLint cleancode, int texture);
void APIENTRY_FPE4ES fpe4es_glGetTexGenfv(GLenum coord, GLenum pname, GLfloat* params);

void APIENTRY_FPE4ES fpe4es_glLoadTransposeMatrixf(const GLfloat* m);
void APIENTRY_FPE4ES fpe4es_glLoadTransposeMatrixd(const GLdouble* m);
void APIENTRY_FPE4ES fpe4es_glMultTransposeMatrixd(const GLdouble* m);
void APIENTRY_FPE4ES fpe4es_glMultTransposeMatrixf(const GLfloat* m);

#endif // _FPE4ES_TEXGEN_H_
