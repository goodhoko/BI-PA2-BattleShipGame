PROGRAM=koutnja1

CC=g++
CFLAGS=-std=c++11 -Wall -pedantic -g -Wno-long-long -O0 -ggdb

all: compile doc

run: compile
	./$(PROGRAM)

runclient: 
	./$(PROGRAM) -c

compile: $(PROGRAM)

doc: src/AIPlayer.cpp src/CleverAIPlayer.cpp src/Coord.h src/GeniusAIPlayer.h src/Session.h src/AIPlayer.h src/CleverAIPlayer.h src/EasyAIPlayer.cpp \
	src/main.cpp src/Ship.cpp src/Board.cpp src/Client.h src/EasyAIPlayer.h src/NetworkPlayer.cpp src/Ship.h src/Board.h src/CMakeLists.txt \
	src/Game.cpp src/NetworkPlayer.h src/Strategy.cpp src/BoardTile.cpp src/ConsolePlayer.cpp src/Game.h src/Player.h src/Strategy.h src/BoardTile.h \
	src/ConsolePlayer.h src/GeniusAIPlayer.cpp src/Session.cpp
	doxygen Doxyfile

$(PROGRAM): objs/main.o objs/AIPlayer.o objs/Board.o objs/BoardTile.o objs/CleverAIPlayer.o objs/ConsolePlayer.o objs/EasyAIPlayer.o objs/Game.o \
			objs/GeniusAIPlayer.o objs/NetworkPlayer.o objs/Session.o objs/Ship.o objs/Strategy.o
			$(CC) $(CFLAGS) $^ -o $@

objs/main.o: src/main.cpp src/Session.h src/Client.h | objs
	$(CC) $(CFLAGS) -c $< -o $@

objs/AIPlayer.o: src/AIPlayer.cpp src/AIPlayer.h | objs
	$(CC) $(CFLAGS) -c $< -o $@

objs/Board.o: src/Board.cpp src/Board.h | objs
	$(CC) $(CFLAGS) -c $< -o $@

objs/BoardTile.o: src/BoardTile.cpp src/BoardTile.h | objs
	$(CC) $(CFLAGS) -c $< -o $@

objs/CleverAIPlayer.o: src/CleverAIPlayer.cpp src/CleverAIPlayer.h | objs
	$(CC) $(CFLAGS) -c $< -o $@

objs/ConsolePlayer.o: src/ConsolePlayer.cpp src/ConsolePlayer.h | objs
	$(CC) $(CFLAGS) -c $< -o $@

objs/EasyAIPlayer.o: src/EasyAIPlayer.cpp src/EasyAIPlayer.h | objs
	$(CC) $(CFLAGS) -c $< -o $@

objs/Game.o: src/Game.cpp src/Game.h | objs
	$(CC) $(CFLAGS) -c $< -o $@

objs/GeniusAIPlayer.o: src/GeniusAIPlayer.cpp src/GeniusAIPlayer.h | objs
	$(CC) $(CFLAGS) -c $< -o $@

objs/NetworkPlayer.o: src/NetworkPlayer.cpp src/NetworkPlayer.h | objs
	$(CC) $(CFLAGS) -c $< -o $@

objs/Session.o: src/Session.cpp src/Session.h | objs
	$(CC) $(CFLAGS) -c $< -o $@

objs/Ship.o: src/Ship.cpp src/Ship.h | objs
	$(CC) $(CFLAGS) -c $< -o $@

objs/Strategy.o: src/Strategy.cpp src/Strategy.h | objs
	$(CC) $(CFLAGS) -c $< -o $@

objs:
	mkdir objs

clean:
	rm -rf $(PROGRAM) objs/ doc/ 2>/dev/null

