#include "controller.h"

namespace s21 {
/// @brief проверка нажатой кнопки пользователем
/// @param int key текущие параметры
UserAction_t Controller::GetSignal(int key) {
  UserAction_t signal = UserAction_t::Action;
  if (key == KEY_UP)
    signal = UserAction_t::Up;
  else if (key == KEY_DOWN)
    signal = UserAction_t::Down;
  else if (key == KEY_LEFT)
    signal = UserAction_t::Left;
  else if (key == KEY_RIGHT)
    signal = UserAction_t::Right;
  else if (key == KEY_ESCAPE)
    signal = UserAction_t::Terminate;
  else if (key == KEY_START)
    signal = UserAction_t::Start;
  else if (key == 'p' || key == 'P')
    signal = UserAction_t::Pause;
  else if (key == KEY_SPACE)
    signal = UserAction_t::Action;
  return signal;
}

/// @brief таймер для более плавного движения
/// @param текущие параметры
bool Controller::TimerAction() {
  auto current_time = std::chrono::system_clock::now();
  auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(
                          current_time - last_update_time)
                          .count();

  if (elapsed_time >= game_->getSpeed()) {
    last_update_time = current_time;
    return true;
  }

  usleep(1000);
  return false;
}
/// @brief возвращение уровня
/// @param текущие параметры
int Controller::Get_level() { return game_->getLevel(); }
/// @brief возвращение счета
/// @param текущие параметры
int Controller::Get_score() { return game_->getScore(); }
/// @brief возвращение счета
/// @param текущие параметры
int Controller::Get_record() { return game_->getRecord(); }
/// @brief возвращение скорости
/// @param текущие параметры
int Controller::Get_speed() { return game_->getSpeed(); }

/// @brief получение кнопки, и на основе действия переключение между состояниями
/// автомата
/// @param int key текущие параметры
Game_State Controller::userInput(int key) {
  UserAction_t signal_ = GetSignal(key);

  game_->userAction(signal_);
  game_->fullArray();

  return mover();
}

Game_State Controller::mover() {
  if (TimerAction() && game_->get_game_state() == sMoving)
    game_->Action__Moving_();

  return (game_->get_game_state());
}

/// @brief получение значения из ячейки массива со змейкой
/// @param int x, int y текущие параметры
int Controller::getSnakeArray(int x, int y) { return game_->getArray(x, y); }

}  // namespace s21
extern "C" {

s21::Controller* Controller_new() { return new s21::Controller(); }

void Controller_delete(s21::Controller* instance) { delete instance; }

UserAction_t Controller_GetSignal(s21::Controller* instance, int key) {
  return instance->GetSignal(key);
}

Game_State Controller_userInput(s21::Controller* instance, int key) {
  return instance->userInput(key);
}

int Controller_getSnakeArray(s21::Controller* instance, int x, int y) {
  //  printf("hey/ i'm print  Controller_getSnakeArray\n");
  return instance->game_->getArray(x, y);
}
}
