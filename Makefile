CC=g++
CFLAGS= -Wall

all: oneg.exe

oneg.exe: main.cpp Onegin.cpp 
	   	   $(CC) main.cpp Onegin.cpp -o onegin.exe
		   

clean:
	   del *.o *.exe