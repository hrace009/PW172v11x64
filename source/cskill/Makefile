#
# Makefile 
#

TOP_SRCDIR = ..

include ./mk/gcc.defs.mk

SHAREOBJ = 
LOGSTUB = 
LOGOBJ = 

OBJS = ./skill/skill.o ./skill/skillwrapper.o ./skill/playerwrapper.o ./skill/skillfilter.o

STUBOBJS =  ./skills/stubs0.o
STUBOBJS += ./skills/stubs1.o
STUBOBJS += ./skills/stubs2.o
STUBOBJS += ./skills/stubs3.o
STUBOBJS += ./skills/stubs4.o
STUBOBJS += ./skills/stubs5.o
STUBOBJS += ./skills/stubs6.o
STUBOBJS += ./skills/stubs7.o
STUBOBJS += ./skills/stubs8.o
STUBOBJS += ./skills/stubs9.o
STUBOBJS += ./skills/stubs10.o
STUBOBJS += ./skills/stubs11.o
STUBOBJS += ./skills/stubs12.o
STUBOBJS += ./skills/stubs13.o
STUBOBJS += ./skills/stubs14.o
STUBOBJS += ./skills/stubs15.o
STUBOBJS += ./skills/stubs16.o
STUBOBJS += ./skills/stubs17.o
STUBOBJS += ./skills/stubs18.o
STUBOBJS += ./skills/stubs19.o
STUBOBJS += ./skills/stubs20.o
STUBOBJS += ./skills/stubs21.o
STUBOBJS += ./skills/stubs22.o
STUBOBJS += ./skills/stubs23.o
STUBOBJS += ./skills/stubs24.o
STUBOBJS += ./skills/stubs25.o
STUBOBJS += ./skills/stubs26.o
STUBOBJS += ./skills/stubs27.o
STUBOBJS += ./skills/stubs28.o
STUBOBJS += ./skills/stubs29.o
STUBOBJS += ./skills/stubs30.o
STUBOBJS += ./skills/stubs31.o
STUBOBJS += ./skills/stubs32.o
STUBOBJS += ./skills/stubs33.o
STUBOBJS += ./skills/stubs34.o

CLEAN += ./skills/*.o 

INCLUDES += -I./skill -I./header -I./header/include -I./lua/src -I./lua/LuaBridge
DEFINES	+=-D_SKILL_SERVER 
CFLAGS += -fPIC -finput-charset="cp1251"

all : dlib

dlib : $(OBJS) $(STUBOBJS) 
	rm libskill.so -f
	$(LD) -shared -fPIC $(LDFLAGS) $(OBJS) $(STUBOBJS) skilllua.o -o libskill.so


include ./mk/gcc.rules.mk


	
	