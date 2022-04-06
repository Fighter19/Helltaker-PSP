TARGET = template
OBJS = main.o field.o movement.o controls.o
DEPENDS = $(OBJS:.o=.d)

BUILD_PRX=1

INCDIR =
CFLAGS = -O2 -G0 -Wall -MMD
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LDFLAGS =

EXTRA_TARGETS = EBOOT.PBP
EXTRA_CLEAN = $(DEPENDS)
PSP_EBOOT_TITLE = Template

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak

-include $(DEPENDS)
