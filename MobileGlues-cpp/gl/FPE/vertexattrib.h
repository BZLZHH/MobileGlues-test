#ifndef _FPE4ES_VERTEXATTRIB_H_
#define _FPE4ES_VERTEXATTRIB_H_



// actual definition of vertexattrib_t is in buffer.h, as they are part of VAO...

void APIENTRY_FPE4ES fpe4es_glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid * pointer);
void APIENTRY_FPE4ES fpe4es_glVertexAttribIPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid * pointer);
void APIENTRY_FPE4ES fpe4es_glEnableVertexAttribArray(GLuint index);
void APIENTRY_FPE4ES fpe4es_glDisableVertexAttribArray(GLuint index);

// other variant are defined in wrap...
void APIENTRY_FPE4ES fpe4es_glVertexAttrib4f(GLuint index, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
void APIENTRY_FPE4ES fpe4es_glVertexAttrib4fv(GLuint index, const GLfloat *v);


void APIENTRY_FPE4ES fpe4es_glGetVertexAttribdv(GLuint index, GLenum pname, GLdouble *params);
void APIENTRY_FPE4ES fpe4es_glGetVertexAttribfv(GLuint index, GLenum pname, GLfloat *params);
void APIENTRY_FPE4ES fpe4es_glGetVertexAttribiv(GLuint index, GLenum pname, GLint *params);
void APIENTRY_FPE4ES fpe4es_glGetVertexAttribPointerv(GLuint index, GLenum pname, GLvoid **pointer);

// GL_ARB_instanced_arrays (OpenGL 3.0+)
// void APIENTRY_FPE4ES fpe4es_glVertexAttribDivisor(GLuint index, GLuint divisor);

#endif // _FPE4ES_VERTEXATTRIB_H_
