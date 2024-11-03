.POSIX:
CC=gcc -std=c11
CFLAGS = -Wall -Wextra -Werror -lncurses
INSTALL_FILES = main.c gui/cli/*.c brick_game.a -lncurses

FLAGSCH = -lcheck
TARGET = brick_game


ifeq ($(shell uname),Linux)
	FLAGSCH += -lm -lsubunit
endif

OPEN_COMMAND =open
ifeq ($(OS), Linux)
	OPEN_COMMAND=xdg-open
else
	OPEN_COMMAND=open
endif

all: clean install

install:clean uninstall
	mkdir games
	clang-format -style=Google -i brick_game/tetris/*.h brick_game/tetris/*.c
	clang-format -style=Google -i gui/cli/*.h gui/cli/*.c
	gcc -Wall -Wextra -Werror main.c gui/cli/front.c brick_game/tetris/*.c  consts.h -o games/tetris -lncurses -lcheck
	
	clang-format -style=Google -i brick_game/snake/*.h brick_game/snake/*.cpp  
	g++ -c brick_game/snake/classes.cpp -o classes.o
	g++ -c brick_game/snake/controller.cpp -o controller.o
	g++ -c brick_game/snake/game.cpp -o game.o
	gcc -c gui/cli/snake.c -o snake.o -lncurses
	g++ classes.o controller.o game.o snake.o -o games/snake -lncurses

uninstall:
	rm -rf games


clean:
	rm -rf *.o *.a testing snake snake_test tetris_test tetris_game check *.gcno *.gcda *.info report *.dSYM tetris test

test: clean 
	$(CC) brick_game/tetris/*.c  consts.h   --coverage tests/tetris_tests.c -o tetris_test $(FLAGSCH)
	./tetris_test
	g++ -c brick_game/snake/classes.cpp -o classes.o
	g++ -c brick_game/snake/controller.cpp -o controller.o
	g++ -c brick_game/snake/game.cpp -o game.o
	g++ -c tests/snake_tests.cpp -o _snake_tests.o
# gcc -c gui/cli/snake.c -o snake.o -lncurses
	g++ classes.o controller.o game.o _snake_tests.o -o snake_test -lncurses -lgtest -lrt -lm -lpthread --coverage -lstdc++ -std=c++17 -Wall -Wextra -Werror -g
	./snake_test

gcov_report: test
	lcov -t "result" -o res.info -c -d .
	genhtml -o report res.info
	open report/index.html
	rm -rf *gcda *gcno res.info test


decst:
ifeq ("", "$(wildcard Build)")
	mkdir Build
else
	rm -rf Build/*
endif
	cd gui/desktop/decstop-front && qmake && make -j6 &> /dev/null \
	&& make clean &> /dev/null  \
	&& cd ../../ && mv gui/desktop/build-decstop-front-Desktop-Release/decstop-front.app Build
	


dvi:
	${OPEN_COMMAND} README.md

dist:
	tar -czvf archive.tar.gz ./*


#_________________________________
#все что ниже не проверено 

test_valgrind:
	@mkdir -p ../tests/build
	gcc ../tests/main_test.c ${CFLAGS} $(BACKEND) ${COMMON} $(TEST_FLAGS) -o ./test.out
	valgrind ${VALGRIND_FLAGS} ./test.out

clang_i:
	cp ../materials/linters/.clang-format .
	@find .. -type f -name "*.c" -exec clang-format -i -style=Google {} \;
	@find .. -type f -name "*.h" -exec clang-format -i -style=Google {} \;
	@echo "Clang format style apply is finished"


clang_n:
	cp ../materials/linters/.clang-format .
	@find .. -type f -name "*.c" -exec clang-format -n -style=Google {} \;
	@find .. -type f -name "*.h" -exec clang-format -n -style=Google {} \;
	@echo "Clang format style check is finished"


clean_project:
	@find .. -type f -name "*.records" -exec rm {} \;

.PHONY: all install unistall clean test dvi dist gcov_report clang

