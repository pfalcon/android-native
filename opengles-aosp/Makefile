NDK_ROOT=/home/pfalcon/devel/android-ndk-r5b
#AOSP_ROOT=/home/pfalcon/projects-3rdparty/android-donut
AOSP_ROOT=/home/pfalcon/projects-3rdparty/android-gingerbread
CROSS_COMPILE=arm-linux-androideabi-
API_LEVEL=9
ARCH=arm

CC=$(CROSS_COMPILE)gcc
CXX=$(CROSS_COMPILE)g++
LD=$(CROSS_COMPILE)ld
PLATFORM_PATH=$(NDK_ROOT)/platforms/android-$(API_LEVEL)/arch-$(ARCH)
LDLIBS_PATH_SDK=$(PLATFORM_PATH)/usr/lib
LDLIBS_PATH=../lib-nooktablet
CPPFLAGS = \
    -I$(PLATFORM_PATH)/usr/include \
    -I$(NDK_ROOT)/sources/cxx-stl/system/include \
    -I$(AOSP_ROOT)/system/core/include \
    -I$(AOSP_ROOT)/frameworks/base/include \
    -I$(AOSP_ROOT)/frameworks/base/native/include \
    -I$(AOSP_ROOT)/hardware/libhardware/include \
    -I$(AOSP_ROOT)/external/skia/include \
    -I.
CXXFLAGS=-fno-exceptions

%: %.o
	$(LD) --entry=_start --dynamic-linker /system/bin/linker \
	-nostdlib \
	-rpath /system/lib -rpath-link $(LDLIBS_PATH) -rpath-link $(LDLIBS_PATH_SDK) \
	-L$(LDLIBS_PATH) -L$(LDLIBS_PATH_SDK) \
	$^ $(EXTRA_LIBS) -lstdc++ -lc $(LDLIBS_PATH_SDK)/crtbegin_dynamic.o $(LDLIBS_PATH_SDK)/crtend_android.o -o $@

#-lGLESv2 -lGLESv1_CM -lEGL -lui


all: angeles configdump fillrate filter finish gl_basic gl2_basic \
     linetex swapinterval textures tritex


angeles: EXTRA_LIBS=-lm -lGLESv1_CM -lui
angeles: angeles.o app-linux.o

configdump: EXTRA_LIBS=-lGLESv1_CM
configdump: configdump.o

fillrate: EXTRA_LIBS=-lGLESv1_CM -lui
fillrate: fillrate.o

filter: EXTRA_LIBS=-lGLESv1_CM -lui
filter: filter.o

finish: EXTRA_LIBS=-lGLESv1_CM -lui
finish: finish.o

gl_basic: EXTRA_LIBS=-lGLESv1_CM -lui
gl_basic: gl_basic.o

gl2_basic: EXTRA_LIBS=-lGLESv2 -lui
gl2_basic: gl2_basic.o

linetex: EXTRA_LIBS=-lGLESv1_CM -lui
linetex: linetex.o

swapinterval: EXTRA_LIBS=-lGLESv1_CM -lui
swapinterval: swapinterval.o

textures: EXTRA_LIBS=-lGLESv1_CM -lui
textures: textures.o

tritex: EXTRA_LIBS=-lGLESv1_CM -lui
tritex: tritex.o


push-%: %
	adb push $^ /data/local

run-%: %
	adb shell /data/local/$^

clean:
	rm -f *.o
