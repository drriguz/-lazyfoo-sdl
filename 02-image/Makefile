OBJS = image.cpp
CC = g++
COMPILER_FLAGS = -w
LINKER_FLAGS = -lSDL2 -lSDL2_image
OBJ_NAME = hello.exe

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

.PHONY : clean
clean :
	rm -f *.obj
	rm -f *.o
	rm -f $(OBJ_NAME)
