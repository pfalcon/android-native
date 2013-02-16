NDK_ROOT=/home/pfalcon/devel/android-ndk-r5b
AOSP_HEADERS=android-platform-headers/android-2.3.5_r1
CROSS_COMPILE=arm-linux-androideabi-
API_LEVEL=9
ARCH=arm

CC=$(CROSS_COMPILE)gcc
CXX=$(CROSS_COMPILE)g++
LD=$(CROSS_COMPILE)ld
PLATFORM_PATH=$(NDK_ROOT)/platforms/android-$(API_LEVEL)/arch-$(ARCH)
LDLIBS_PATH_SDK=$(PLATFORM_PATH)/usr/lib
LDLIBS_PATH=lib-nooktablet/
# Path to compiler C++ headers, these are tricky with NDK
CXX_HEADERS=-I$(NDK_ROOT)/sources/cxx-stl/system/include

CPPFLAGS = \
    -I$(PLATFORM_PATH)/usr/include \
    $(CXX_HEADERS) \
    -I$(AOSP_HEADERS)/system/core/include \
    -I$(AOSP_HEADERS)/frameworks/base/include \
    -I$(AOSP_HEADERS)/frameworks/base/native/include \
    -I$(AOSP_HEADERS)/hardware/libhardware/include \
    $(EXTRA_INCLUDES)

#    -I$(AOSP_ROOT)/external/skia/include \
    -I.

CXXFLAGS=-fno-exceptions

%: %.o
	$(LD) --entry=_start --dynamic-linker /system/bin/linker \
	-nostdlib \
	-rpath /system/lib -rpath-link $(LDLIBS_PATH) -rpath-link $(LDLIBS_PATH_SDK) \
	-L$(LDLIBS_PATH) -L$(LDLIBS_PATH_SDK) \
	$^ $(EXTRA_LIBS) -lstdc++ -lc $(LDLIBS_PATH_SDK)/crtbegin_dynamic.o $(LDLIBS_PATH_SDK)/crtend_android.o -o $@


all: $(ALL)

push:
	for exe in $(ALL); do \
	    adb push $$exe /data/local; \
	done

push-%: %
	adb push $^ /data/local

run-%: %
	adb shell /data/local/$^

clean:
	rm -f *.o

distclean: clean
	rm -f $(ALL)
