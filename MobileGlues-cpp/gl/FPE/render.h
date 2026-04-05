#ifndef _FPE4ES_RENDER_H_
#define _FPE4ES_RENDER_H_

#include "buffers.h"

GLint APIENTRY_FPE4ES fpe4es_glRenderMode(GLenum mode);
void APIENTRY_FPE4ES fpe4es_glInitNames(void);
void APIENTRY_FPE4ES fpe4es_glPopName(void);
void APIENTRY_FPE4ES fpe4es_glPushName(GLuint name);
void APIENTRY_FPE4ES fpe4es_glLoadName(GLuint name);
void APIENTRY_FPE4ES fpe4es_glSelectBuffer(GLsizei size, GLuint* buffer);

void select_glDrawElements(const vertexattrib_t* vtx, GLenum mode, GLuint count, GLenum type, GLvoid* indices);
void select_glDrawArrays(const vertexattrib_t* vtx, GLenum mode, GLuint first, GLuint count);

#endif // _FPE4ES_RENDER_H_
