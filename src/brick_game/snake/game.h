#ifndef CPP3_BRICKGAME_V2_SRC_BRICK_GAME_SNAKE_GAME_H_
#define CPP3_BRICKGAME_V2_SRC_BRICK_GAME_SNAKE_GAME_H_

// #include <iostream>
#include "../../consts.h"
#include "classes.h"

#ifdef __cplusplus  // only actually define the class if this is C++
#include <unistd.h>

#include <chrono>
#include <ctime>
#include <iostream>

namespace s21 {

class SnakeGame {
 public:
  SnakeGame() { Start_game(); } // tested
  void Start_game(); // tested 
  void InitializeFSM(); // TESTED
  void UpdateSpeed();
  void computeCurrentLevel() noexcept;
  void generateNewMeal() noexcept;
  void processSnakeEating() noexcept;
  void Action__Moving_(); 
  typedef void (SnakeGame::*StateFun)();
  void fullArray(); // tested

  int getArray(int x, int y);
  Snake *snake_;
  Game_State get_game_state(); // tested
  int getSpeed(); // tested
  int getScore(); // tested
  void setGame_state_(Game_State state); // tested
  int getLevel(); // tested
  int getRecord(); // tested
  void userAction(UserAction_t signal_); // tested

 private:
  StateFun fsm[NUM_STATES][NUM_ACTIONS];
  void Action__Start_Start(); // tested
  void Action__Terminate(); // tested
  void Action__Pause_Pause(); // tested

  // void Action__Moving_();
  void Action__Moving_Left(); // tested
  void Action__Moving_Pause(); // tested
  void Action__sGameOver_Start(); // tested
  Game_State game_state_;
  UserAction_t user_action_;
  UserAction_t mover_ = Up;
  int array[BOARD_HEIGHT + 2][BOARD_WIDTH + 2];
  GameScore score_;
  int level_;
  int speed_ = 500;
  using clock = std::chrono::system_clock;
  using time_point_type =
      std::chrono::time_point<clock, std::chrono::milliseconds>;
  time_point_type start;
};
}  // namespace s21
#endif  // __cplusplus

#endif  // CPP3_BRICKGAME_V2_SRC_BRICK_GAME_SNAKEGAME_H_
