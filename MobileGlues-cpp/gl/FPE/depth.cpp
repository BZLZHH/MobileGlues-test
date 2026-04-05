#include "depth.h"

#include "fpe_core.h"
#include "glstate.h"

void APIENTRY_FPE4ES fpe4es_glDepthFunc(GLenum func) {
    if (glstate->list.compiling) {
        PUSH_IF_COMPILING(glDepthFunc);
    }
    noerrorShim();
    if (glstate->depth.func == func) return;
    FLUSH_BEGINEND;
    glstate->depth.func = func;
    GLES.glDepthFunc(func);
}

void APIENTRY_FPE4ES fpe4es_glDepthMask(GLboolean flag) {
    if (glstate->list.compiling) {
        PUSH_IF_COMPILING(glDepthMask);
    }
    noerrorShim();
    if (glstate->depth.mask == flag) return;
    FLUSH_BEGINEND;
    glstate->depth.mask = flag;
    GLES.glDepthMask(flag);
}

GLfloat clamp(GLfloat a) {
    return (a < 0.f) ? 0.f : ((a > 1.f) ? 1.f : a);
}

void APIENTRY_FPE4ES fpe4es_glDepthRangef(GLclampf Near, GLclampf Far) {
    Near = clamp(Near);
    Far = clamp(Far);
    if (glstate->list.compiling) {
        PUSH_IF_COMPILING(glDepthRangef);
    }
    noerrorShim();
    if ((glstate->depth.Near == Near) && (glstate->depth.Far == Far)) return;
    FLUSH_BEGINEND;
    glstate->depth.Near = Near;
    glstate->depth.Far = Far;
    GLES.glDepthRangef(Near, Far);
}

void APIENTRY_FPE4ES fpe4es_glClearDepthf(GLclampf depth) {
    depth = clamp(depth);
    if (glstate->list.compiling) {
        PUSH_IF_COMPILING(glClearDepthf);
    }
    noerrorShim();
    glstate->depth.clear = depth;
    GLES.glClearDepthf(depth);
}

AliasExport(void, glDepthFunc, , (GLenum func));
AliasExport(void, glDepthMask, , (GLboolean flag));
AliasExport(void, glDepthRangef, , (GLclampf nearVal, GLclampf farVal));
AliasExport(void, glClearDepthf, , (GLclampf depth));
