#ifndef _FPE4ES_ARBPARSER_H_
#define _FPE4ES_ARBPARSER_H_

#include <stddef.h>

#include "arbhelper.h"

struct sSpecialCases {
	int hasFogFragCoord;
	int isDepthReplacing;
};

eToken readNextToken(sCurStatus* curStatus);
void parseToken(sCurStatus *curStatus, int vertex, char **error_msg, struct sSpecialCases *hasFogFragCoord);

#endif // _FPE4ES_ARBPARSER_H_
