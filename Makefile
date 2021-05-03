DEBUG=yes
#DEBUG=no
CC=gcc
EXEC=crypto

#################################
###### SETUP COMPILE FLAGS ######
#################################

ifeq ($(DEBUG), yes)
	CFLAGS = -Wall -Wextra -g
else
	CFLAGS = -Ofast
endif

#################################
###### COMPILATION PROJECT ######
#################################

all: build $(EXEC)

build:
	./build.sh

$(EXEC): main.o chiffrement.o Dechiffrement.o myInclude.o
	$(CC) target/main.o target/chiffrement.o target/Dechiffrement.o target/myInclude.o -o bin/$@

run: 
	./bin/crypto

#################################
########## COMPILE FILE #########
#################################

main.o: src/main/Main.c
	$(CC) -c $(CFLAGS) $< -o target/$@

chiffrement.o: src/lib/Chiffrement.c src/lib/Chiffrement.h
	$(CC) -c $(CFLAGS) $< -o target/$@

Dechiffrement.o: src/lib/Dechiffrement.c src/lib/Dechiffrement.h
	$(CC) -c $(CFLAGS) $< -o target/$@

myInclude.o: src/lib/MyInclude.c src/lib/MyInclude.h
	$(CC) -c $(CFLAGS) $< -o target/$@

#################################
######## VALGRIND AND DGB #######
#################################

vg:
	valgrind ./bin/$(EXEC)

vg2:
	valgrind --leak-check=full --show-leak-kinds=all ./bin/$(EXEC) $(FILE)

vg3:
	valgrind -v ./bin/$(EXEC)

gdb:
	gdb ./bin/$(EXEC)

#################################
############  CLEAN  ############
#################################

clean:
	rm target/*.o
	rmdir target/

mrproper: clean
	rm bin/$(EXEC)
	rmdir bin/