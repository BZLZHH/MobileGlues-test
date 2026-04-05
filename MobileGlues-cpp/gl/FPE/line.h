#ifndef _FPE4ES_LINE_H
#define _FPE4ES_LINE_H

#include "list.h"

void APIENTRY_FPE4ES fpe4es_glLineStipple(GLuint factor, GLushort pattern);
GLfloat* gen_stipple_tex_coords(GLfloat* vert, GLushort* sindices, modeinit_t* modes, int stride, int length,
                                GLfloat* noalloctex);
void bind_stipple_tex();

#endif // _FPE4ES_LINE_H
