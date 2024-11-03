#ifndef CPP3_BRICKGAME_V2_SRC_BRICK_GAME_SNAKE_CONTROLLER_H_
#define CPP3_BRICKGAME_V2_SRC_BRICK_GAME_SNAKE_CONTROLLER_H_

#include <ncurses.h>

#include "game.h"

#ifdef __cplusplus  // only actually define the class if this is C++
namespace s21 {

class Controller {
 public:
  std::chrono::system_clock::time_point last_update_time=
        std::chrono::system_clock::now();
  SnakeGame* game_;
  // UserAction_t last_mover = Up;
  Controller() {
    game_ = new SnakeGame;
  }
  bool TimerAction();
  UserAction_t GetSignal(int key);
  Game_State mover();
  Game_State userInput(int key);
  int Get_speed();
  int Get_record();
  int getSnakeArray(int x, int y);
  int Get_score();
  int Get_level();
};

#endif

// access functions
#ifdef __cplusplus
extern "C" {
#define EXPORT_C extern "C"
#else
#define EXPORT_C
#endif

typedef struct Controller Controller;

EXPORT_C Controller* Controller_new();
EXPORT_C void Controller_delete(Controller* instance);
EXPORT_C Game_State Controller_userInput(Controller* instance, int signal_);
EXPORT_C int Controller_getSnakeArray(Controller* instance, int x, int y);

#ifdef __cplusplus
}
}
#endif

#endif  // CPP3_BRICKGAME_V2_SRC_BRICK_GAME_SNAKE_CONTROLLER_H_
