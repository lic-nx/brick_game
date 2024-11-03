#ifndef SRC_BRICK_GAME_SNAKE_MODELS_GAME_H
#define SRC_BRICK_GAME_SNAKE_MODELS_GAME_H

#include <stdbool.h>

#include "../../consts.h"

#ifdef __cplusplus  // only actually define the class if this is C++

#include <deque>
#include <fstream>
#include <iostream>
#include <queue>

namespace s21 {

// действия пользователя

class Block {
 public:
  Block() : x_(5), y_(10){}; // tested
  Block(int x, int y)
      : x_{x % (BOARD_WIDTH)}, y_{y % (BOARD_HEIGHT)} {}; // tested возможно нужно будет добавить +1
  bool operator==(const Block& other) const; // tested
  void RandomPlase(); // tested
  bool isOutBorders() const noexcept; // tested
  void change_y_(int value); // tested
  void change_x_(int value); // tested
  int get_x(); // tested
  int get_y(); // tested
  private:
  int x_;
  int y_;

};

class Snake {
 private:
  UserAction_t side_;

 public:
  void setSide(); // tested
  std::deque<Block> snake_body_;
  Block meal_;
  bool isOpposite(UserAction_t newDirection) const noexcept; // tested
  Snake(); // tested
  void Move(UserAction_t direction_); // tested
  void InitSnake(); // tested
  int getLength() const; // tested
  bool CheckCollisionBodyOrBorder() const; // tested
  bool CheckCollisionMeal(Block meal) const; // tested
  void grow(); // tested
  // void changeUserAction_t(UserAction_t newDirection);
  void generateNewMeal(); // tested
  bool CheckCollisionHeadAndMeal(); // tested
};

class GameScore {
 public:
  explicit GameScore(); // tested
  void loadTopScore();  // tested
  void saveTopScore(); // tested
  void increase() noexcept; // tested
  int getCurrentScore() const noexcept { return current_; } // tested
  int getTopScore() const noexcept { return top_; } // tested
  void reset(); // tested

 private:
  int current_ = 0; /**< The current score */
  int top_;         /**< The top score */
};
}  // namespace s21

#endif

#endif  // SRC_BRICK_GAME_SNAKE_MODELS_GAME_H
