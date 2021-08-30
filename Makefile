CPPC:=g++
CFLAGS:=-I/opt/vc/include \
	-L/opt/vc/lib \
	-lGLESv2 -lEGL -lbcm_host -lvcos -lvchiq_arm -lpthread -lrt
PROJECT:=.

default:
	$(CPPC) $(CFLAGS) -Wall -o app $(PROJECT)/main.cpp
