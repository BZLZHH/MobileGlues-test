#ifndef _FPE4ES_BLIT_H_
#define _FPE4ES_BLIT_H_
#include <GL/gl.h>
#include "../../gles/gles.h"
#define BLIT_ALPHA 0
#define BLIT_OPAQUE 1
#define BLIT_COLOR 2

void fpe4es_blitTexture(GLuint texture, GLfloat sx, GLfloat sy, GLfloat width, GLfloat height, GLfloat nwidth,
                        GLfloat nheight, GLfloat zoomx, GLfloat zoomy, GLfloat vpwidth, GLfloat vpheight, GLfloat x,
                        GLfloat y, GLint mode);

#endif // _FPE4ES_BLIT_H_
