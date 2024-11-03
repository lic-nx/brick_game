// #include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>

#include "../../brick_game/snake/controller.h"
// #include "../../gui/cli/front.h"

int main() {
  Controller* controller_ = Controller_new();
  // SnakeGame* snake_game_ = SnakeGame_new();
  int key = 0;
  Game_State state = Start;
  int block = 0;

  // Инициализация ncurses
  initscr();
  raw();  // Включение режима raw для getch()
  keypad(stdscr, TRUE);  // Включение обработки специальных клавиш
  noecho();  // Отключение эхо-ввода
  nodelay(stdscr, true);
  // Основной цикл
  while ((key = getch()) != 'E') {
    state = Controller_userInput(controller_, key);
    if (state == sPause) {
      mvprintw(10, 5, "Pause");  // выводим паузу
    } else if (state == sExitGame) {
      break;
    } else if (state == sGameOver) {
      mvprintw(10, 5, "Game over");  // выводим паузу
    } else {
      for (int i = 0; i < BOARD_HEIGHT + 2; i++) {
        for (int j = 0; j < BOARD_WIDTH + 2; j++) {
          block = Controller_getSnakeArray(controller_, i, j);
          mvaddch(i, j,
                  block != 0 ? (block == 1 ? ACS_CKBOARD : ACS_HLINE) : ' ');
        }
      }
    }
    // Обновление экрана
    refresh();
    // Задержка для отображения изменений
    // napms(100); // Задержка в миллисек
  }
  // Завершение работы ncurses
  endwin();

  Controller_delete(controller_);
  return 0;
}