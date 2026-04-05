#include "blend.h"

#include "debug.h"
#include "fpe_core.h"
#include "glstate.h"
#include "init.h"

static int fpeBlendFunc(GLenum func) {
    int ret = -1;
#define GO(A)                                                                                                          \
    case GL_##A:                                                                                                       \
        ret = FPE_BLEND_##A;                                                                                           \
        break
    switch (func) {
        GO(ZERO);
        GO(ONE);
        GO(SRC_COLOR);
        GO(ONE_MINUS_SRC_COLOR);
        GO(DST_COLOR);
        GO(ONE_MINUS_DST_COLOR);
        GO(SRC_ALPHA);
        GO(ONE_MINUS_SRC_ALPHA);
        GO(DST_ALPHA);
        GO(ONE_MINUS_DST_ALPHA);
        GO(CONSTANT_COLOR);
        GO(ONE_MINUS_CONSTANT_COLOR);
        GO(CONSTANT_ALPHA);
        GO(ONE_MINUS_CONSTANT_ALPHA);
        GO(SRC_ALPHA_SATURATE);
    }
#undef GO
    return ret;
}
static int fpeBlendEq(GLenum func) {
    int ret = -1;
#define GO(A)                                                                                                          \
    case GL_##A:                                                                                                       \
        ret = FPE_BLENDEQ_##A;                                                                                         \
        break
    switch (func) {
        GO(FUNC_ADD);
        GO(FUNC_SUBTRACT);
        GO(FUNC_REVERSE_SUBTRACT);
        GO(MIN);
        GO(MAX);
    }
#undef GO
    return ret;
}

void APIENTRY_FPE4ES fpe4es_glBlendColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha) {
    if (!glstate->list.pending) PUSH_IF_COMPILING(glBlendColor)

    if (glstate->blend_color[0] == red && glstate->blend_color[1] == green && glstate->blend_color[2] == blue &&
        glstate->blend_color[3] == alpha)
        return;

    FLUSH_BEGINEND;

    glstate->blend_color[0] = red;
    glstate->blend_color[1] = green;
    glstate->blend_color[2] = blue;
    glstate->blend_color[3] = alpha;

    if (!globals4es.shaderblend) {
        // LOAD_GLES2_OR_OES(glBlendColor);
        // if  (gles_glBlendColor)
        //     gles_glBlendColor(red, green, blue, alpha);
        // else {
        //     static int test = 1;
        //     if (test) {
        //         LOGD("stub glBlendColor(%f, %f, %f, %f)\n", red, green, blue, alpha);
        //         test = 0;
        //     }
        // }
    }
}
AliasExport(void, glBlendColor, , (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha));
AliasExport(void, glBlendColor, EXT, (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha));
AliasExport(void, glBlendColor, ARB, (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha));

void APIENTRY_FPE4ES fpe4es_glBlendFuncSeparate(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha,
                                                GLenum dfactorAlpha) {
    if (!glstate->list.pending) PUSH_IF_COMPILING(glBlendFuncSeparate)

    // LOAD_GLES2_OR_OES(glBlendFuncSeparate);
    if (sfactorRGB == glstate->blendsfactorrgb && dfactorRGB == glstate->blenddfactorrgb &&
        sfactorAlpha == glstate->blendsfactoralpha && dfactorAlpha == glstate->blenddfactoralpha)
        return; // no change...

    FLUSH_BEGINEND;

    if (globals4es.shaderblend) {
        int srcrgb = fpeBlendFunc(sfactorRGB);
        int dstrgb = fpeBlendFunc(dfactorRGB);
        int srcalpha = fpeBlendFunc(sfactorAlpha);
        int dstalpha = fpeBlendFunc(dfactorAlpha);
        if (srcrgb < 0 || dstrgb < 0 || srcalpha < 0 || dstalpha < 0) {
            errorShim(GL_INVALID_VALUE);
            return;
        }
        glstate->fpe_state->blendsrcrgb = srcrgb;
        glstate->fpe_state->blenddstrgb = dstrgb;
        glstate->fpe_state->blendsrcalpha = srcalpha;
        glstate->fpe_state->blenddstalpha = dstalpha;
    }

    glstate->blendsfactorrgb = sfactorRGB;
    glstate->blenddfactorrgb = dfactorRGB;
    glstate->blendsfactoralpha = sfactorAlpha;
    glstate->blenddfactoralpha = dfactorAlpha;
}
AliasExport(void, glBlendFuncSeparate, ,
            (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha));
AliasExport(void, glBlendFuncSeparate, EXT,
            (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha));

void APIENTRY_FPE4ES fpe4es_glBlendEquationSeparate(GLenum modeRGB, GLenum modeA) {
    if (!glstate->list.pending) PUSH_IF_COMPILING(glBlendEquationSeparate);

    if (glstate->blendeqrgb == modeRGB && glstate->blendeqalpha == modeA) return;

    if (globals4es.shaderblend) {
        int rgb = fpeBlendEq(modeRGB);
        int alpha = fpeBlendEq(modeA);
        if (rgb < 0 || alpha < 0) {
            errorShim(GL_INVALID_VALUE);
            return;
        }
        glstate->fpe_state->blendeqrgb = rgb;
        glstate->fpe_state->blendeqalpha = alpha;
    }

    glstate->blendeqrgb = modeRGB;
    glstate->blendeqalpha = modeA;
}
AliasExport(void, glBlendEquationSeparate, , (GLenum modeRGB, GLenum modeA));
AliasExport(void, glBlendEquationSeparate, EXT, (GLenum modeRGB, GLenum modeA));

void APIENTRY_FPE4ES fpe4es_glBlendFunc(GLenum sfactor, GLenum dfactor) {
    if (!glstate->list.pending) PUSH_IF_COMPILING(glBlendFunc)

    if (sfactor == glstate->blendsfactorrgb && dfactor == glstate->blenddfactorrgb &&
        sfactor == glstate->blendsfactoralpha && dfactor == glstate->blenddfactoralpha)
        return; // already set

    FLUSH_BEGINEND;

    glstate->blendsfactorrgb = sfactor;
    glstate->blenddfactorrgb = dfactor;
    glstate->blendsfactoralpha = sfactor;
    glstate->blenddfactoralpha = dfactor;

    if (globals4es.shaderblend) {
        int srcrgb = fpeBlendFunc(sfactor);
        int dstrgb = fpeBlendFunc(dfactor);
        int srcalpha = fpeBlendFunc(sfactor);
        int dstalpha = fpeBlendFunc(dfactor);
        if (srcrgb < 0 || dstrgb < 0 || srcalpha < 0 || dstalpha < 0) {
            errorShim(GL_INVALID_VALUE);
            return;
        }
        glstate->fpe_state->blendsrcrgb = srcrgb;
        glstate->fpe_state->blenddstrgb = dstrgb;
        glstate->fpe_state->blendsrcalpha = srcalpha;
        glstate->fpe_state->blenddstalpha = dstalpha;
    }
}
AliasExport(void, glBlendFunc, , (GLenum sfactor, GLenum dfactor));

void APIENTRY_FPE4ES fpe4es_glBlendEquation(GLenum mode) {
    if (!glstate->list.pending) PUSH_IF_COMPILING(glBlendEquation)

    if (glstate->blendeqrgb == mode && glstate->blendeqalpha == mode) return;

    glstate->blendeqrgb = mode;
    glstate->blendeqalpha = mode;

    if (globals4es.shaderblend) {
        int rgb = fpeBlendEq(mode);
        int alpha = fpeBlendEq(mode);
        if (rgb < 0 || alpha < 0) {
            errorShim(GL_INVALID_VALUE);
            return;
        }
        glstate->fpe_state->blendeqrgb = rgb;
        glstate->fpe_state->blendeqalpha = alpha;
    }
}
AliasExport(void, glBlendEquation, , (GLenum mode));
AliasExport(void, glBlendEquation, EXT, (GLenum mode));
