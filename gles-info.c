#include <stdio.h>
#include <stdlib.h>

#include <egl.h>

// From 2.3.7 frameworks/base/include/ui/egl/android_natives.h
#define ANDROID_NATIVE_MAKE_CONSTANT(a,b,c,d) \
    (((unsigned)(a)<<24)|((unsigned)(b)<<16)|((unsigned)(c)<<8)|(unsigned)(d))

#define ANDROID_NATIVE_WINDOW_MAGIC \
    ANDROID_NATIVE_MAKE_CONSTANT('_','w','n','d')

#define ANDROID_NATIVE_BUFFER_MAGIC \
    ANDROID_NATIVE_MAKE_CONSTANT('_','b','f','r')

NativeWindowType displayWindow;

int main(int argc, char** argv)
{
    EGLint majorVersion, minorVersion;
    EGLContext eglContext;
    EGLSurface eglSurface;
    EGLConfig eglConfig;
    EGLDisplay eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    int numConfigs;

    // Window surface that covers the entire screen, from libui.
    displayWindow = android_createDisplaySurface();

//    eglInitialize(eglDisplay, &majorVersion, &minorVersion);
//    printf("GL version: %d.%d\n",majorVersion,minorVersion);

    unsigned magic = *(unsigned*)displayWindow;
    printf("EGLNativeWindowType magic: %#x\n", magic);

    if (magic == ANDROID_NATIVE_WINDOW_MAGIC) {
        printf("2.0+ ANativeWindow/android_native_window_t detected\n");
    } else if (magic == 0x600913) {
        printf("1.6- egl_native_window_t detected\n");
        printf("Window specs: magic:%x size: %d*%d format=%d\n",
         displayWindow->magic,
         displayWindow->width,
         displayWindow->height,
         displayWindow->format);
    }

    return 0;
}
