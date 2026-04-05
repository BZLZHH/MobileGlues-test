#ifndef _FPE4ES_DEBUG_H_
#define _FPE4ES_DEBUG_H_

#include <GL/gl.h>

const char* PrintEnum(GLenum what);

const char* PrintEGLError(int onlyerror);

void CheckGLError(int fwd);

#endif // _FPE4ES_DEBUG_H_
