TOP = ..
include $(TOP)/common.mk

ALL = angeles configdump fillrate filter finish gl_basic gl2_basic \
     linetex swapinterval textures tritex

all: $(ALL)

angeles: EXTRA_LIBS=-lm -lGLESv1_CM -lEGL -lui
angeles: angeles.o app-linux.o

configdump: EXTRA_LIBS=-lGLESv1_CM -lEGL
configdump: configdump.o

fillrate: EXTRA_LIBS=-lGLESv1_CM -lEGL -lui -lutils
fillrate: fillrate.o

filter: EXTRA_LIBS=-lGLESv1_CM -lEGL -lui
filter: filter.o

finish: EXTRA_LIBS=-lGLESv1_CM -lEGL -lui -lutils
finish: finish.o

gl_basic: EXTRA_LIBS=-lGLESv1_CM -lEGL -lui -lm
gl_basic: gl_basic.o

gl2_basic: EXTRA_LIBS=-lGLESv2 -lEGL -lui
gl2_basic: gl2_basic.o

linetex: EXTRA_LIBS=-lGLESv1_CM -lEGL -lui
linetex: linetex.o

swapinterval: EXTRA_LIBS=-lGLESv1_CM -lEGL -lui -lutils
swapinterval: swapinterval.o

textures: EXTRA_LIBS=-lGLESv1_CM -lEGL -lui
textures: textures.o

tritex: EXTRA_LIBS=-lGLESv1_CM -lEGL -lui -lm
tritex: tritex.o
