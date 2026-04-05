#ifndef _FPE4ES_SHADERCONV_H_
#define _FPE4ES_SHADERCONV_H_


#include "program.h"

char* ConvertShader(const char* pBuffer, int isVertex, shaderconv_need_t* need);

int isBuiltinAttrib(const char* name);
int isBuiltinMatrix(const char* name);

const char* hasBuiltinAttrib(const char* vertexShader, int Att);
const char* builtinAttribGLName(const char* name);
const char* builtinAttribInternalName(const char* name);

#endif // _FPE4ES_SHADERCONV_H_
