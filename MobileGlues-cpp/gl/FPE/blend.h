#ifndef _FPE4ES_BLEND_H_
#define _FPE4ES_BLEND_H_

#include "buffers.h"

void APIENTRY_FPE4ES fpe4es_glBlendColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
void APIENTRY_FPE4ES fpe4es_glBlendFuncSeparate(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha,
                                                GLenum dfactorAlpha);
void APIENTRY_FPE4ES fpe4es_glBlendEquationSeparate(GLenum modeRGB, GLenum modeA);
void APIENTRY_FPE4ES fpe4es_glBlendFunc(GLenum sfactor, GLenum dfactor);
void APIENTRY_FPE4ES fpe4es_glBlendEquation(GLenum mode);

#endif //_FPE4ES_BLEND_H_
