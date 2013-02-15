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


all: resize srface

resize: EXTRA_LIBS=-lsurfaceflinger_client -landroid_runtime
resize.o: resize.cpp

surface: EXTRA_LIBS=-lsurfaceflinger_client -landroid_runtime
surface.o: surface.cpp

push-%: %
	adb push $^ /data/local

run-%: %
	adb shell /data/local/$^

clean:
	rm -f *.o
