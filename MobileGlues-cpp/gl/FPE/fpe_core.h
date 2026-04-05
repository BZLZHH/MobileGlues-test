#ifndef _FPE4ES_FPE4ES_H_
#define _FPE4ES_FPE4ES_H_

#ifdef __ARM_NEON__
#include <arm_neon.h>
#endif // __ARM_NEON__

#include "glstate.h"
#include "gleswrapper.h"
#include "../../gles/gles.h"
#include <GL/gl.h>

#define MSVC_SPC(MACRO, ARGS) MACRO ARGS

#define PUSH_IF_COMPILING_EXT(nam, ...)                                                                                \
    if (glstate->list.active) {                                                                                        \
        if (!glstate->list.pending) {                                                                                  \
            NewStage(glstate->list.active, STAGE_GLCALL);                                                              \
            MSVC_SPC(push_##nam, (__VA_ARGS__));                                                                       \
            noerrorShim();                                                                                             \
            return (nam##_RETURN)0;                                                                                    \
        } else                                                                                                         \
            fpe4es_flush();                                                                                            \
    }

#define PUSH_IF_COMPILING(name) PUSH_IF_COMPILING_EXT(name, name##_ARG_NAMES)

#define checkError(code)                                                                                               \
    {                                                                                                                  \
        int error;                                                                                                     \
        while ((error = glGetError())) {}                                                                              \
        code if ((error = glGetError())) printf(#code " -> %i\n", error);                                              \
    }

#define printError(file, line)                                                                                         \
    {                                                                                                                  \
        int error;                                                                                                     \
        if ((error = glGetError())) printf(file ":%i -> %i\n", line, error);                                           \
    }

#define FLUSH_BEGINEND                                                                                                 \
    if (glstate->list.pending) fpe4es_flush()

#define ERROR_IN_BEGIN                                                                                                 \
    if (glstate->list.begin) {                                                                                         \
        errorShim(GL_INVALID_OPERATION);                                                                               \
        return;                                                                                                        \
    }

const GLubyte* APIENTRY_FPE4ES fpe4es_glGetString(GLenum name);
void APIENTRY_FPE4ES fpe4es_glGetIntegerv(GLenum pname, GLint* params);
void APIENTRY_FPE4ES fpe4es_glGetFloatv(GLenum pname, GLfloat* params);
void APIENTRY_FPE4ES fpe4es_glEnable(GLenum cap);
void APIENTRY_FPE4ES fpe4es_glDisable(GLenum cap);
void APIENTRY_FPE4ES fpe4es_glEnableClientState(GLenum cap);
void APIENTRY_FPE4ES fpe4es_glDisableClientState(GLenum cap);
GLboolean APIENTRY_FPE4ES fpe4es_glIsEnabled(GLenum cap);
void APIENTRY_FPE4ES fpe4es_glDrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices);
void APIENTRY_FPE4ES fpe4es_glDrawArrays(GLenum mode, GLint first, GLsizei count);
void APIENTRY_FPE4ES fpe4es_glInterleavedArrays(GLenum format, GLsizei stride, const GLvoid* pointer);
void APIENTRY_FPE4ES fpe4es_glBegin(GLenum mode);
void APIENTRY_FPE4ES fpe4es_glEnd(void);
void APIENTRY_FPE4ES fpe4es_glNormal3f(GLfloat nx, GLfloat ny, GLfloat nz);
void APIENTRY_FPE4ES fpe4es_glVertex4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
void APIENTRY_FPE4ES fpe4es_glColor4f(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
void APIENTRY_FPE4ES fpe4es_glSecondaryColor3f(GLfloat r, GLfloat g, GLfloat b);
void APIENTRY_FPE4ES fpe4es_glMaterialfv(GLenum face, GLenum pname, const GLfloat* params);
void APIENTRY_FPE4ES fpe4es_glMaterialf(GLenum face, GLenum pname, const GLfloat param);
void APIENTRY_FPE4ES fpe4es_glTexCoord4f(GLfloat s, GLfloat t, GLfloat r, GLfloat q);
void APIENTRY_FPE4ES fpe4es_glMultiTexCoord4f(GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q);
void APIENTRY_FPE4ES fpe4es_glArrayElement(GLint i);
void APIENTRY_FPE4ES fpe4es_glLockArrays(GLint first, GLsizei count);
void APIENTRY_FPE4ES fpe4es_glUnlockArrays(void);
GLuint APIENTRY_FPE4ES fpe4es_glGenLists(GLsizei range);
void APIENTRY_FPE4ES fpe4es_glNewList(GLuint list, GLenum mode);
void APIENTRY_FPE4ES fpe4es_glEndList(void);
void APIENTRY_FPE4ES fpe4es_glCallList(GLuint list);
void APIENTRY_FPE4ES fpe4es_glCallLists(GLsizei n, GLenum type, const GLvoid* lists);
void APIENTRY_FPE4ES fpe4es_glDeleteLists(GLuint list, GLsizei range);
void APIENTRY_FPE4ES fpe4es_glListBase(GLuint base);
GLboolean APIENTRY_FPE4ES fpe4es_glIsList(GLuint list);
void APIENTRY_FPE4ES fpe4es_glPolygonMode(GLenum face, GLenum mode);
GLenum APIENTRY_FPE4ES fpe4es_glGetError(void);

void APIENTRY_FPE4ES fpe4es_glSecondaryColorPointer(GLint size, GLenum type, GLsizei stride, const GLvoid* pointer);
void APIENTRY_FPE4ES fpe4es_glIndexPointer(GLenum type, GLsizei stride, const GLvoid* pointer);
void APIENTRY_FPE4ES fpe4es_glEdgeFlagPointer(GLsizei stride, const GLvoid* pointer);
void APIENTRY_FPE4ES fpe4es_glGetPointerv(GLenum pname, GLvoid** params);
void APIENTRY_FPE4ES fpe4es_glFlush(void);
void APIENTRY_FPE4ES fpe4es_glFinish(void);
void APIENTRY_FPE4ES fpe4es_glFogfv(GLenum pname, const GLfloat* params);

void APIENTRY_FPE4ES fpe4es_glStencilMaskSeparate(GLenum face, GLuint mask);

void APIENTRY_FPE4ES fpe4es_glMultiDrawArrays(GLenum mode, const GLint* first, const GLsizei* count, GLsizei primcount);
void APIENTRY_FPE4ES fpe4es_glMultiDrawElements(GLenum mode, GLsizei* count, GLenum type, const void* const* indices,
                                                GLsizei primcount);

void fpe4es_flush(void);

int adjust_vertices(GLenum mode, int nb);

extern glstate_t* glstate;

void fpe_Init(glstate_t* glstate);    // defined in fpe.c
void fpe_Dispose(glstate_t* glstate); // defined in fpe.c

// glGetError() return last error, but that error is not reset until read
// So if 2 operations generate an error,
//  the 2nd error is lost if glGetError has not been called after 1st op
static inline void errorGL() { // next glGetError will be from GL
    if (glstate->type_error && glstate->shim_error == GL_NO_ERROR)
        glstate->type_error = 0;
    else if (glstate->type_error == 2)
        glstate->type_error = 1; // will need to read glGetError...
}
static inline void errorShim(GLenum error) { // next glGetError will be "error" from fpe4es
    if (glstate->type_error && glstate->shim_error == GL_NO_ERROR) glstate->type_error = 1;
    if (glstate->shim_error == GL_NO_ERROR) glstate->shim_error = error;
}
static inline void noerrorShim() {
    if (glstate->type_error && glstate->shim_error == GL_NO_ERROR) glstate->type_error = 1;
}

static inline void noerrorShimNoPurge() {
    // doing nothing
}

void fpe4es_scratch(int alloc);
void fpe4es_scratch_vertex(int alloc);
void fpe4es_scratch_indices(int alloc);
void fpe4es_use_scratch_vertex(int use);
void fpe4es_use_scratch_indices(int use);

void ToBuffer(int first, int count);
void UnBuffer();

GLboolean APIENTRY_FPE4ES glIsList(GLuint list);
GLuint APIENTRY_FPE4ES glGenLists(GLsizei range);
void APIENTRY_FPE4ES glActiveTextureARB(GLenum texture);
void APIENTRY_FPE4ES glArrayElement(GLint i);
void APIENTRY_FPE4ES glBegin(GLenum mode);
void APIENTRY_FPE4ES glCallList(GLuint list);
void APIENTRY_FPE4ES glCallLists(GLsizei n, GLenum type, const GLvoid* lists);
void APIENTRY_FPE4ES glClearDepth(GLdouble depth);
void APIENTRY_FPE4ES glDeleteList(GLuint list);
void APIENTRY_FPE4ES glDeleteLists(GLuint list, GLsizei range);
void APIENTRY_FPE4ES glDrawArrays(GLenum mode, GLint first, GLsizei count);
void APIENTRY_FPE4ES glEnd(void);
void APIENTRY_FPE4ES glEndList(void);
void APIENTRY_FPE4ES glFrustum(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble Near,
                               GLdouble Far);
void APIENTRY_FPE4ES glGetDoublev(GLenum pname, GLdouble* params);
void APIENTRY_FPE4ES glIndexf(GLfloat i);
void APIENTRY_FPE4ES glInterleavedArrays(GLenum format, GLsizei stride, const GLvoid* pointer);
void APIENTRY_FPE4ES glListBase(GLuint base);
void APIENTRY_FPE4ES glLockArraysEXT(GLint first, GLsizei count);
void APIENTRY_FPE4ES glNewList(GLuint list, GLenum mode);
void APIENTRY_FPE4ES glOrtho(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble Near, GLdouble Far);
void APIENTRY_FPE4ES glSecondaryColor3f(GLfloat r, GLfloat g, GLfloat b);
void APIENTRY_FPE4ES glTexCoord2f(GLfloat s, GLfloat t);
void APIENTRY_FPE4ES glUnlockArraysEXT(void);
void APIENTRY_FPE4ES glVertex2f(GLfloat x, GLfloat y);
void APIENTRY_FPE4ES glVertex2i(GLint x, GLint y);
void APIENTRY_FPE4ES glVertex3f(GLfloat x, GLfloat y, GLfloat z);
GLenum APIENTRY_FPE4ES glGetError(void);

// custom functions
void APIENTRY_FPE4ES glPushCall(void* call);

void APIENTRY_FPE4ES fpe4es_glClearDepth(GLdouble depth);
void APIENTRY_FPE4ES fpe4es_glClipPlane(GLenum plane, const GLdouble* equation);
void APIENTRY_FPE4ES fpe4es_glDepthRange(GLdouble nearVal, GLdouble farVal);
void APIENTRY_FPE4ES fpe4es_glFogi(GLenum pname, GLint param);
void APIENTRY_FPE4ES fpe4es_glFogiv(GLenum pname, GLint* params);
void APIENTRY_FPE4ES fpe4es_glFrustum(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble Near,
                                      GLdouble Far);
void APIENTRY_FPE4ES fpe4es_glGetDoublev(GLenum pname, GLdouble* params);
void APIENTRY_FPE4ES fpe4es_glLighti(GLenum light, GLenum pname, GLint param);
void APIENTRY_FPE4ES fpe4es_glLightiv(GLenum light, GLenum pname, GLint* iparams);
void APIENTRY_FPE4ES fpe4es_glLightModeli(GLenum pname, GLint param);
void APIENTRY_FPE4ES fpe4es_glLightModeliv(GLenum pname, GLint* iparams);
void APIENTRY_FPE4ES fpe4es_glMateriali(GLenum face, GLenum pname, GLint param);
void APIENTRY_FPE4ES fpe4es_glMaterialiv(GLenum face, GLenum pname, GLint* param);
void APIENTRY_FPE4ES fpe4es_glMultiTexCoord2f(GLenum target, GLfloat s, GLfloat t);
void APIENTRY_FPE4ES fpe4es_glOrtho(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble Near,
                                    GLdouble Far);
void APIENTRY_FPE4ES fpe4es_glGetMaterialiv(GLenum face, GLenum pname, GLint* params);
void APIENTRY_FPE4ES fpe4es_glGetLightiv(GLenum light, GLenum pname, GLint* params);
void APIENTRY_FPE4ES fpe4es_glGetClipPlane(GLenum plane, GLdouble* equation);

void APIENTRY_FPE4ES fpe4es_glDrawRangeElements(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type,
                                                const void* indices);
// color
void APIENTRY_FPE4ES fpe4es_glColor3f(GLfloat r, GLfloat g, GLfloat b);
void APIENTRY_FPE4ES fpe4es_glColor3fv(GLfloat* c);
void APIENTRY_FPE4ES fpe4es_glColor4fv(GLfloat* c);
void APIENTRY_FPE4ES fpe4es_glIndexfv(const GLfloat* c);
void APIENTRY_FPE4ES fpe4es_glSecondaryColor3fv(const GLfloat* v);

// raster
void APIENTRY_FPE4ES fpe4es_glRasterPos2f(GLfloat x, GLfloat y);
void APIENTRY_FPE4ES fpe4es_glRasterPos2fv(const GLfloat* v);
void APIENTRY_FPE4ES fpe4es_glRasterPos3f(GLfloat x, GLfloat y, GLfloat z);
void APIENTRY_FPE4ES fpe4es_glRasterPos3fv(const GLfloat* v);
void APIENTRY_FPE4ES fpe4es_glRasterPos4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
void APIENTRY_FPE4ES fpe4es_glRasterPos4fv(const GLfloat* v);
void APIENTRY_FPE4ES fpe4es_glWindowPos2f(GLfloat x, GLfloat y);
void APIENTRY_FPE4ES fpe4es_glWindowPos2fv(const GLfloat* v);
void APIENTRY_FPE4ES fpe4es_glWindowPos3f(GLfloat x, GLfloat y, GLfloat z);
void APIENTRY_FPE4ES fpe4es_glWindowPos3fv(const GLfloat* v);

void APIENTRY_FPE4ES fpe4es_glPixelStoref(GLenum pname, GLfloat param);
void APIENTRY_FPE4ES fpe4es_glGetTexGendv(GLenum coord, GLenum pname, GLdouble* params);
void APIENTRY_FPE4ES fpe4es_glGetTexGeniv(GLenum coord, GLenum pname, GLint* params);
void APIENTRY_FPE4ES fpe4es_glPixelTransferi(GLenum pname, GLint param);
void APIENTRY_FPE4ES fpe4es_glPixelTransferf(GLenum pname, GLfloat param);

// eval
void APIENTRY_FPE4ES fpe4es_glEvalCoord1d(GLdouble u);
void APIENTRY_FPE4ES fpe4es_glEvalCoord1dv(GLdouble* v);
void APIENTRY_FPE4ES fpe4es_glEvalCoord1fv(GLfloat* v);
void APIENTRY_FPE4ES fpe4es_glEvalCoord2d(GLdouble u, GLdouble v);
void APIENTRY_FPE4ES fpe4es_glEvalCoord2dv(GLdouble* v);
void APIENTRY_FPE4ES fpe4es_glEvalCoord2fv(GLfloat* v);
void APIENTRY_FPE4ES fpe4es_glMapGrid1d(GLint un, GLdouble u1, GLdouble u2);
void APIENTRY_FPE4ES fpe4es_glMapGrid2d(GLint un, GLdouble u1, GLdouble u2, GLint vn, GLdouble v1, GLdouble v2);

// matrix
void APIENTRY_FPE4ES fpe4es_glLoadMatrixd(const GLdouble* m);
void APIENTRY_FPE4ES fpe4es_glMultMatrixd(const GLdouble* m);

// normal
void APIENTRY_FPE4ES fpe4es_glNormal3fv(GLfloat* v);

// fog (defined in fog.c)
void APIENTRY_FPE4ES fpe4es_glFogCoordd(GLdouble coord);
void APIENTRY_FPE4ES fpe4es_glFogCoorddv(const GLdouble* coord);

// rect
#define GL_RECT(suffix, type)                                                                                          \
    void APIENTRY_FPE4ES fpe4es_glRect##suffix(type x1, type y1, type x2, type y2);                                    \
    void APIENTRY_FPE4ES fpe4es_glRect##suffix##v(const type* v1, const type* v2);

GL_RECT(d, GLdouble)
GL_RECT(f, GLfloat)
GL_RECT(i, GLint)
GL_RECT(s, GLshort)
#undef GL_RECT

// textures

void APIENTRY_FPE4ES fpe4es_glTexCoord1f(GLfloat s);
void APIENTRY_FPE4ES fpe4es_glTexCoord1fv(GLfloat* t);
void APIENTRY_FPE4ES fpe4es_glTexCoord2f(GLfloat s, GLfloat t);
void APIENTRY_FPE4ES fpe4es_glTexCoord2fv(GLfloat* t);
void APIENTRY_FPE4ES fpe4es_glTexCoord3f(GLfloat s, GLfloat t, GLfloat r);
void APIENTRY_FPE4ES fpe4es_glTexCoord3fv(GLfloat* t);
void APIENTRY_FPE4ES fpe4es_glTexCoord4fv(GLfloat* t);

void APIENTRY_FPE4ES fpe4es_glMultiTexCoord1f(GLenum target, GLfloat s);
void APIENTRY_FPE4ES fpe4es_glMultiTexCoord1fv(GLenum target, GLfloat* t);
void APIENTRY_FPE4ES fpe4es_glMultiTexCoord2f(GLenum target, GLfloat s, GLfloat t);
void APIENTRY_FPE4ES fpe4es_glMultiTexCoord2fv(GLenum target, GLfloat* t);
void APIENTRY_FPE4ES fpe4es_glMultiTexCoord3f(GLenum target, GLfloat s, GLfloat t, GLfloat r);
void APIENTRY_FPE4ES fpe4es_glMultiTexCoord3fv(GLenum target, GLfloat* t);
void APIENTRY_FPE4ES fpe4es_glMultiTexCoord4fv(GLenum target, GLfloat* t);

void APIENTRY_FPE4ES fpe4es_glGetTexLevelParameterfv(GLenum target, GLint level, GLenum pname, GLfloat* params);

void APIENTRY_FPE4ES fpe4es_glPolygonMode(GLenum face, GLenum mode);

// texgen
void APIENTRY_FPE4ES fpe4es_glTexGend(GLenum coord, GLenum pname, GLdouble param);
void APIENTRY_FPE4ES fpe4es_glTexGeni(GLenum coord, GLenum pname, GLint param);
void APIENTRY_FPE4ES fpe4es_glTexGenf(GLenum coord, GLenum pname, GLfloat param);
void APIENTRY_FPE4ES fpe4es_glTexGendv(GLenum coord, GLenum pname, const GLdouble* params);
void APIENTRY_FPE4ES fpe4es_glTexGenfv(GLenum coord, GLenum pname, const GLfloat* params);
void APIENTRY_FPE4ES fpe4es_glTexGeniv(GLenum coord, GLenum pname, const GLint* params);

// transforms
void APIENTRY_FPE4ES fpe4es_glRotated(GLdouble angle, GLdouble x, GLdouble y, GLdouble z);
void APIENTRY_FPE4ES fpe4es_glScaled(GLdouble x, GLdouble y, GLdouble z);
void APIENTRY_FPE4ES fpe4es_glTranslated(GLdouble x, GLdouble y, GLdouble z);

// vertex
void APIENTRY_FPE4ES fpe4es_glVertex2f(GLfloat x, GLfloat y);
void APIENTRY_FPE4ES fpe4es_glVertex2fv(GLfloat* v);
void APIENTRY_FPE4ES fpe4es_glVertex3fv(GLfloat* v);
void APIENTRY_FPE4ES fpe4es_glVertex3f(GLfloat r, GLfloat g, GLfloat b);
void APIENTRY_FPE4ES fpe4es_glVertex4fv(GLfloat* v);

// OES wrappers

void APIENTRY_FPE4ES glClearDepthfOES(GLfloat depth);
void APIENTRY_FPE4ES glClipPlanefOES(GLenum plane, const GLfloat* equation);
void APIENTRY_FPE4ES glDepthRangefOES(GLclampf Near, GLclampf Far);
void APIENTRY_FPE4ES glFrustumfOES(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat Near, GLfloat Far);
void APIENTRY_FPE4ES glGetClipPlanefOES(GLenum plane, GLfloat equation[4]);
void APIENTRY_FPE4ES glOrthofOES(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat Near, GLfloat Far);

// basic thunking

#define THUNK(suffix, type)                                                                                            \
    void APIENTRY_FPE4ES fpe4es_glColor3##suffix##v(const type* v);                                                    \
    void APIENTRY_FPE4ES fpe4es_glColor3##suffix(type r, type g, type b);                                              \
    void APIENTRY_FPE4ES fpe4es_glColor4##suffix##v(const type* v);                                                    \
    void APIENTRY_FPE4ES fpe4es_glColor4##suffix(type r, type g, type b, type a);                                      \
    void APIENTRY_FPE4ES fpe4es_glSecondaryColor3##suffix##v(const type* v);                                           \
    void APIENTRY_FPE4ES fpe4es_glSecondaryColor3##suffix(type r, type g, type b);                                     \
    void APIENTRY_FPE4ES fpe4es_glIndex##suffix##v(const type* c);                                                     \
    void APIENTRY_FPE4ES fpe4es_glIndex##suffix(type c);                                                               \
    void APIENTRY_FPE4ES fpe4es_glNormal3##suffix##v(const type* v);                                                   \
    void APIENTRY_FPE4ES fpe4es_glNormal3##suffix(type x, type y, type z);                                             \
    void APIENTRY_FPE4ES fpe4es_glRasterPos2##suffix##v(type* v);                                                      \
    void APIENTRY_FPE4ES fpe4es_glRasterPos2##suffix(type x, type y);                                                  \
    void APIENTRY_FPE4ES fpe4es_glRasterPos3##suffix##v(type* v);                                                      \
    void APIENTRY_FPE4ES fpe4es_glRasterPos3##suffix(type x, type y, type z);                                          \
    void APIENTRY_FPE4ES fpe4es_glRasterPos4##suffix##v(type* v);                                                      \
    void APIENTRY_FPE4ES fpe4es_glRasterPos4##suffix(type x, type y, type z, type w);                                  \
    void APIENTRY_FPE4ES fpe4es_glWindowPos2##suffix##v(type* v);                                                      \
    void APIENTRY_FPE4ES fpe4es_glWindowPos2##suffix(type x, type y);                                                  \
    void APIENTRY_FPE4ES fpe4es_glWindowPos3##suffix##v(type* v);                                                      \
    void APIENTRY_FPE4ES fpe4es_glWindowPos3##suffix(type x, type y, type z);                                          \
    void APIENTRY_FPE4ES fpe4es_glVertex2##suffix##v(type* v);                                                         \
    void APIENTRY_FPE4ES fpe4es_glVertex2##suffix(type x, type y);                                                     \
    void APIENTRY_FPE4ES fpe4es_glVertex3##suffix##v(type* v);                                                         \
    void APIENTRY_FPE4ES fpe4es_glVertex3##suffix(type x, type y, type z);                                             \
    void APIENTRY_FPE4ES fpe4es_glVertex4##suffix(type x, type y, type z, type w);                                     \
    void APIENTRY_FPE4ES fpe4es_glVertex4##suffix##v(type* v);                                                         \
    void APIENTRY_FPE4ES fpe4es_glTexCoord1##suffix(type s);                                                           \
    void APIENTRY_FPE4ES fpe4es_glTexCoord1##suffix##v(type* t);                                                       \
    void APIENTRY_FPE4ES fpe4es_glTexCoord2##suffix(type s, type t);                                                   \
    void APIENTRY_FPE4ES fpe4es_glTexCoord2##suffix##v(type* t);                                                       \
    void APIENTRY_FPE4ES fpe4es_glTexCoord3##suffix(type s, type t, type r);                                           \
    void APIENTRY_FPE4ES fpe4es_glTexCoord3##suffix##v(type* t);                                                       \
    void APIENTRY_FPE4ES fpe4es_glTexCoord4##suffix(type s, type t, type r, type q);                                   \
    void APIENTRY_FPE4ES fpe4es_glTexCoord4##suffix##v(type* t);                                                       \
    void APIENTRY_FPE4ES fpe4es_glMultiTexCoord1##suffix(GLenum target, type s);                                       \
    void APIENTRY_FPE4ES fpe4es_glMultiTexCoord1##suffix##v(GLenum target, type* t);                                   \
    void APIENTRY_FPE4ES fpe4es_glMultiTexCoord2##suffix(GLenum target, type s, type t);                               \
    void APIENTRY_FPE4ES fpe4es_glMultiTexCoord2##suffix##v(GLenum target, type* t);                                   \
    void APIENTRY_FPE4ES fpe4es_glMultiTexCoord3##suffix(GLenum target, type s, type t, type r);                       \
    void APIENTRY_FPE4ES fpe4es_glMultiTexCoord3##suffix##v(GLenum target, type* t);                                   \
    void APIENTRY_FPE4ES fpe4es_glMultiTexCoord4##suffix(GLenum target, type s, type t, type r, type q);               \
    void APIENTRY_FPE4ES fpe4es_glMultiTexCoord4##suffix##v(GLenum target, type* t);                                   \
    void APIENTRY_FPE4ES fpe4es_glMultiTexCoord1##suffix##ARB(GLenum target, type s);                                  \
    void APIENTRY_FPE4ES fpe4es_glMultiTexCoord1##suffix##vARB(GLenum target, type* t);                                \
    void APIENTRY_FPE4ES fpe4es_glMultiTexCoord2##suffix##ARB(GLenum target, type s, type t);                          \
    void APIENTRY_FPE4ES fpe4es_glMultiTexCoord2##suffix##vARB(GLenum target, type* t);                                \
    void APIENTRY_FPE4ES fpe4es_glMultiTexCoord3##suffix##ARB(GLenum target, type s, type t, type r);                  \
    void APIENTRY_FPE4ES fpe4es_glMultiTexCoord3##suffix##vARB(GLenum target, type* t);                                \
    void APIENTRY_FPE4ES fpe4es_glMultiTexCoord4##suffix##ARB(GLenum target, type s, type t, type r, type q);          \
    void APIENTRY_FPE4ES fpe4es_glMultiTexCoord4##suffix##vARB(GLenum target, type* t);

THUNK(b, GLbyte)
THUNK(d, GLdouble)
THUNK(i, GLint)
THUNK(s, GLshort)
THUNK(ub, GLubyte)
THUNK(ui, GLuint)
THUNK(us, GLushort)
#undef THUNK

#define THUNK(suffix, type) void APIENTRY_FPE4ES glGet##suffix##v(GLenum pname, type* params);

THUNK(Double, GLdouble)
THUNK(Integer, GLint)
THUNK(Float, GLfloat)
#undef THUNK

#define THUNK(suffix, type)                                                                                            \
    void APIENTRY_FPE4ES fpe4es_glVertexAttrib1##suffix(GLuint index, type v0);                                        \
    void APIENTRY_FPE4ES fpe4es_glVertexAttrib2##suffix(GLuint index, type v0, type v1);                               \
    void APIENTRY_FPE4ES fpe4es_glVertexAttrib3##suffix(GLuint index, type v0, type v1, type v2);                      \
    void APIENTRY_FPE4ES fpe4es_glVertexAttrib4##suffix(GLuint index, type v0, type v1, type v2, type v3);             \
    void APIENTRY_FPE4ES fpe4es_glVertexAttrib1##suffix##v(GLuint index, const type* v);                               \
    void APIENTRY_FPE4ES fpe4es_glVertexAttrib2##suffix##v(GLuint index, const type* v);                               \
    void APIENTRY_FPE4ES fpe4es_glVertexAttrib3##suffix##v(GLuint index, const type* v);
THUNK(s, GLshort);
THUNK(d, GLdouble);
#undef THUNK
void APIENTRY_FPE4ES fpe4es_glVertexAttrib4dv(GLuint index, const GLdouble* v);
#define THUNK(suffix, type)                                                                                            \
    void APIENTRY_FPE4ES fpe4es_glVertexAttrib4##suffix##v(GLuint index, const type* v);                               \
    void APIENTRY_FPE4ES fpe4es_glVertexAttrib4N##suffix##v(GLuint index, const type* v)
THUNK(b, GLbyte);
THUNK(ub, GLubyte);
THUNK(s, GLshort);
THUNK(us, GLushort);
THUNK(i, GLint);
THUNK(ui, GLuint);
#undef THUNK
void APIENTRY_FPE4ES fpe4es_glVertexAttrib4Nub(GLuint index, GLubyte v0, GLubyte v1, GLubyte v2, GLubyte v3);

// ============= GL_ARB_vertex_shader =================
GLvoid APIENTRY_FPE4ES glVertexAttrib1fARB(GLuint index, GLfloat v0);
GLvoid APIENTRY_FPE4ES glVertexAttrib1sARB(GLuint index, GLshort v0);
GLvoid APIENTRY_FPE4ES glVertexAttrib1dARB(GLuint index, GLdouble v0);
GLvoid APIENTRY_FPE4ES glVertexAttrib2fARB(GLuint index, GLfloat v0, GLfloat v1);
GLvoid APIENTRY_FPE4ES glVertexAttrib2sARB(GLuint index, GLshort v0, GLshort v1);
GLvoid APIENTRY_FPE4ES glVertexAttrib2dARB(GLuint index, GLdouble v0, GLdouble v1);
GLvoid APIENTRY_FPE4ES glVertexAttrib3fARB(GLuint index, GLfloat v0, GLfloat v1, GLfloat v2);
GLvoid APIENTRY_FPE4ES glVertexAttrib3sARB(GLuint index, GLshort v0, GLshort v1, GLshort v2);
GLvoid APIENTRY_FPE4ES glVertexAttrib3dARB(GLuint index, GLdouble v0, GLdouble v1, GLdouble v2);
GLvoid APIENTRY_FPE4ES glVertexAttrib4sARB(GLuint index, GLshort v0, GLshort v1, GLshort v2, GLshort v3);
GLvoid APIENTRY_FPE4ES glVertexAttrib4dARB(GLuint index, GLdouble v0, GLdouble v1, GLdouble v2, GLdouble v3);
GLvoid APIENTRY_FPE4ES glVertexAttrib4NubARB(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w);
GLvoid APIENTRY_FPE4ES glVertexAttrib1fvARB(GLuint index, const GLfloat* v);
GLvoid APIENTRY_FPE4ES glVertexAttrib1svARB(GLuint index, const GLshort* v);
GLvoid APIENTRY_FPE4ES glVertexAttrib1dvARB(GLuint index, const GLdouble* v);
GLvoid APIENTRY_FPE4ES glVertexAttrib2fvARB(GLuint index, const GLfloat* v);
GLvoid APIENTRY_FPE4ES glVertexAttrib2svARB(GLuint index, const GLshort* v);
GLvoid APIENTRY_FPE4ES glVertexAttrib2dvARB(GLuint index, const GLdouble* v);
GLvoid APIENTRY_FPE4ES glVertexAttrib3fvARB(GLuint index, const GLfloat* v);
GLvoid APIENTRY_FPE4ES glVertexAttrib3svARB(GLuint index, const GLshort* v);
GLvoid APIENTRY_FPE4ES glVertexAttrib3dvARB(GLuint index, const GLdouble* v);
GLvoid APIENTRY_FPE4ES glVertexAttrib4svARB(GLuint index, const GLshort* v);
GLvoid APIENTRY_FPE4ES glVertexAttrib4dvARB(GLuint index, const GLdouble* v);
GLvoid APIENTRY_FPE4ES glVertexAttrib4ivARB(GLuint index, const GLint* v);
GLvoid APIENTRY_FPE4ES glVertexAttrib4bvARB(GLuint index, const GLbyte* v);
GLvoid APIENTRY_FPE4ES glVertexAttrib4ubvARB(GLuint index, const GLubyte* v);
GLvoid APIENTRY_FPE4ES glVertexAttrib4usvARB(GLuint index, const GLushort* v);
GLvoid APIENTRY_FPE4ES glVertexAttrib4uivARB(GLuint index, const GLuint* v);
GLvoid APIENTRY_FPE4ES glVertexAttrib4NbvARB(GLuint index, const GLbyte* v);
GLvoid APIENTRY_FPE4ES glVertexAttrib4NsvARB(GLuint index, const GLshort* v);
GLvoid APIENTRY_FPE4ES glVertexAttrib4NivARB(GLuint index, const GLint* v);
GLvoid APIENTRY_FPE4ES glVertexAttrib4NubvARB(GLuint index, const GLubyte* v);
GLvoid APIENTRY_FPE4ES glVertexAttrib4NusvARB(GLuint index, const GLushort* v);
GLvoid APIENTRY_FPE4ES glVertexAttrib4NuivARB(GLuint index, const GLuint* v);

#endif // _FPE4ES_FPE4ES_H_
