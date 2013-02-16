include common.mk

ALL = hello hellocpp \
     dlopen ashmem \
     hal-info hal-gralloc hal-copybit \
     display-info gralloc surface-client \
     gles-info

all: $(ALL)

hello.o: hello.c
hellocpp.o: hellocpp.cpp

hello: hello.o
hellocpp: hellocpp.o

ashmem: EXTRA_LIBS=-lcutils
ashmem.o: ashmem.c

resize: EXTRA_LIBS=-lsurfaceflinger_client
resize.o: resize.cpp

display-info: EXTRA_LIBS=-lsurfaceflinger_client
display-info.o: display-info.cpp

surface-client: EXTRA_LIBS=-lsurfaceflinger_client
surface-client.o: surface-client.cpp

hal-info: EXTRA_LIBS=-lhardware
hal-info.o: hal-info.c

hal-gralloc: EXTRA_LIBS=-lhardware
hal-gralloc.o: hal-gralloc.c

hal-copybit: EXTRA_LIBS=-lhardware
hal-copybit.o: hal-copybit.c

gralloc: EXTRA_LIBS=-lsurfaceflinger -lsurfaceflinger_client
gralloc.o: gralloc.cpp

gles: EXTRA_LIBS=-lGLESv1_CM -lui
gles.o: gles.c

gles-info: EXTRA_LIBS=-lGLESv1_CM -lui
gles-info.o: gles-info.c

dlopen: EXTRA_LIBS=-ldl
dlopen.o: dlopen.c
