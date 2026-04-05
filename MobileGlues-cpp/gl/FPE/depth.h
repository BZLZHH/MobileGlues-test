#ifndef _FPE4ES_DEPTH_H_
#define _FPE4ES_DEPTH_H_
#include "buffers.h"
void APIENTRY_FPE4ES fpe4es_glDepthFunc(GLenum func);
void APIENTRY_FPE4ES fpe4es_glDepthMask(GLboolean flag);
void APIENTRY_FPE4ES fpe4es_glDepthRangef(GLclampf nearVal, GLclampf farVal);
void APIENTRY_FPE4ES fpe4es_glClearDepthf(GLclampf depth);

#endif // _FPE4ES_DEPTH_H_
