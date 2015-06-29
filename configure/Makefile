#COMAKE2 edit-mode: -*- Makefile -*-
####################64Bit Mode####################
#ifeq ($(shell uname -m),x86_64)
CC=gcc
CXX=g++
CXXFLAGS=-g \
  -pipe \
  -W \
  -Wall
CFLAGS=-g \
  -pipe \
  -W \
  -Wall
CPPFLAGS=-D_GNU_SOURCE \
  -D__STDC_LIMIT_MACROS \
  -D_DEBUG
INCPATH=-I. \
	-I../file \
	-I..

LIBPATH=-lpthread \
		../file/libfile.a

#src:=$(wildcard *.cpp)
#obj:=$(src:%.cpp=%.o)
all:test

OBJ:=rawData.o configUnit.o configGroup.o configArray.o reader.o configure.o

test:test.o $(OBJ) 
	@echo "[[1;32;40mMAKE:BUILD[0m][Target:'[1;32;40m$@[0m']"
	$(CXX) $(OBJ) $@.o -Xlinker "-(" $(LIBPATH)	-Xlinker "-)" -o $@
	@echo "make $@ done"

%.o:%.cpp
	@echo "[[1;32;40mMAKE:BUILD[0m][Target:'[1;32;40m$@[0m']"
	$(CXX) -c $(INCPATH)  $(CPPFLAGS) $(CXXFLAGS) $< -o $@
	@echo "make $@ done"


clean:
	@echo "[[1;32;40mMAKE:BUILD[0m][Target:'[1;32;40mclean[0m']"
	rm -rf $(OBJ)
	rm -rf test.o
	@echo "make clean done"

#endif #ifeq ($(shell uname -m),x86_64)


