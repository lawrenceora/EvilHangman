FLAGS = -Wall -g -std=gnu99 
DEPENDENCIES = class.h reader.h

all: evil_hangman

evil_hangman: evil_hangman.o class.o reader.o 
	gcc ${FLAGS} -o $@ $^

%.o: %.c ${DEPENDENCIES}
	gcc ${FLAGS} -c $<

clean: 
	rm -f *.o family evil_hangman reading 
