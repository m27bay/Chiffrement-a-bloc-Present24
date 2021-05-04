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

$(EXEC): Main.o Chiffrement.o Dechiffrement.o Attaque2Present24.o MyInclude.o
	$(CC) target/Main.o target/Chiffrement.o target/Dechiffrement.o target/Attaque2Present24.o target/MyInclude.o -o bin/$@

run: 
	./bin/crypto

#################################
########## COMPILE FILE #########
#################################

Main.o: src/main/Main.c
	$(CC) -c $(CFLAGS) $< -o target/$@

Chiffrement.o: src/lib/Chiffrement.c src/lib/Chiffrement.h
	$(CC) -c $(CFLAGS) $< -o target/$@

Dechiffrement.o: src/lib/Dechiffrement.c src/lib/Dechiffrement.h
	$(CC) -c $(CFLAGS) $< -o target/$@

Attaque2Present24.o: src/lib/Attaque2Present24.c src/lib/Attaque2Present24.h
	$(CC) -c $(CFLAGS) $< -o target/$@

MyInclude.o: src/lib/MyInclude.c src/lib/MyInclude.h
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