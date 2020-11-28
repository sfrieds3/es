CC = g++
CCFLAGS = -Wall -g

objects = es.o io.o

edit : $(objects)
	$(CC) $(CCFLAGS) -o es $(objects)


.PHONY : clean
clean :
	-rm $(objects) es
