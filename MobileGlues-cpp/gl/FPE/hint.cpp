#include "hint.h"

#include <fpe4eshint.h>
#include "init.h"
#include "loader.h"
#include "fpe_core.h"
#include "glstate.h"

#ifdef PANDORA
void pandora_set_gamma();
#endif

void APIENTRY_FPE4ES fpe4es_glHint(GLenum pname, GLenum mode) {
    
    FLUSH_BEGINEND;

    LOAD_GLES(glHint);
    noerrorShim();
    switch(pname) {
        // some Hint are not supported in GLES2, so just ignoring them
        case GL_FOG_HINT:
            if(hardext.esversion>1)
                return;
            gles_glHint(pname, mode);
            break;
        case GL_PERSPECTIVE_CORRECTION_HINT:
            if(hardext.esversion>1)
                return;
            gles_glHint(pname, mode);
            break;
        case GL_LINE_SMOOTH_HINT:
            if(hardext.esversion>1)
                return;
            gles_glHint(pname, mode);
            break;
        case GL_POINT_SMOOTH_HINT:
            if(hardext.esversion>1)
                return;
            gles_glHint(pname, mode);
            break;
        case GL_TEXTURE_COMPRESSION_HINT:   // ignore this one
            // TODO: track setted value
            return;
        // specifics FPE4ES Hints
        case GL_SHRINK_HINT_FPE4ES:
            if (mode<=11)
                globals4es.texshrink = mode;
            else
                errorShim(GL_INVALID_ENUM); 
            break;
        case GL_ALPHAHACK_HINT_FPE4ES: 
            if (mode<=1)
                globals4es.alphahack = mode;
            else
                errorShim(GL_INVALID_ENUM); 
            break;
        case GL_RECYCLEFBO_HINT_FPE4ES: 
            if (mode<=1)
                globals4es.recyclefbo = mode;
            else
                errorShim(GL_INVALID_ENUM); 
            break;
        case GL_MIPMAP_HINT_FPE4ES: 
            if (mode<=4)
                globals4es.automipmap = mode;
            else
                errorShim(GL_INVALID_ENUM); 
            break;
        case GL_TEXDUMP_HINT_FPE4ES: 
            if (mode<=1)
                globals4es.texdump = mode;
            else
                errorShim(GL_INVALID_ENUM); 
            break;
        case GL_COPY_HINT_FPE4ES: 
            if (mode>1) //removed
                errorShim(GL_INVALID_ENUM); 
            break;
        case GL_NOLUMAPHA_HINT_FPE4ES: 
            if (mode<=1)
                globals4es.nolumalpha = mode;
            else
                errorShim(GL_INVALID_ENUM); 
            break;
        case GL_BLENDHACK_HINT_FPE4ES: 
            if (mode<=1)
                globals4es.blendhack = mode;
            else
                errorShim(GL_INVALID_ENUM); 
            break;
        case GL_BATCH_HINT_FPE4ES:
            globals4es.minbatch = 0;
            globals4es.maxbatch = mode*100;
            break;
        case GL_NOERROR_HINT_FPE4ES: 
            if (mode<=1)
                globals4es.noerror = mode;
            else
                errorShim(GL_INVALID_ENUM); 
            break;
        case GL_NODOWNSAMPLING_HINT_FPE4ES:
            if (mode<=1)
                globals4es.nodownsampling = mode;
            else
                errorShim(GL_INVALID_ENUM); 
            break;
        case GL_NOVAOCACHE_HINT_FPE4ES:
            if (mode<=1)
                globals4es.novaocache = mode;
            else
                errorShim(GL_INVALID_ENUM); 
            break;
        case GL_BEGINEND_HINT_FPE4ES:
            if(mode<=2)
                globals4es.beginend = mode;
            else
                errorShim(GL_INVALID_ENUM); 
        case GL_AVOID16BITS_HINT_FPE4ES:
            if (mode<=1)
                globals4es.avoid16bits = mode;
            else
                errorShim(GL_INVALID_ENUM); 
            break;
        case GL_GAMMA_HINT_FPE4ES:
            globals4es.gamma = ((float)mode)/10.f;
#ifdef PANDORA
            pandora_set_gamma();
#endif
            break;
        default:
            errorGL();
            gles_glHint(pname, mode);
    }
}
AliasExport(void,glHint,,(GLenum pname, GLenum mode));