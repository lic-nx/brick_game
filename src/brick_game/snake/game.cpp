#include "game.h"

namespace s21 {

/// @brief обнуляет игровые параметры
/// @param game_paremeters_ текущие параметры
void SnakeGame::Start_game() {
  snake_ = new Snake;
  InitializeFSM();
  fullArray();
  user_action_ = UserAction_t::NUM_ACTIONS;
  start = std::chrono::time_point_cast<std::chrono::milliseconds>(clock::now());
  game_state_ = Game_State::sStart;
  score_.reset();
  mover_ = Up;
  level_ = 0;
  speed_ = 500;
}

/// @brief Заполняет игровое поле. пустое пространнство - 0, тело змеи - 1, еда
/// - 2, бортики - 3
/// @param  текущие параметры
void SnakeGame::fullArray() {
  // const Block head = snake_.snake_body_.front();
  for (int i = 0; i < BOARD_HEIGHT + 2; i++) {
    for (int j = 0; j < BOARD_WIDTH + 2; j++) {
      if (i == 0 || i == BOARD_HEIGHT + 1 || j == 0 || j == BOARD_WIDTH + 1) {
        array[i][j] = 3;
      } else
        array[i][j] = 0;
    }
  }
  for (auto it = snake_->snake_body_.begin(); it != snake_->snake_body_.end();
       ++it) {
    array[it->get_y() + 1][it->get_x() + 1] = 1;
  }
  array[snake_->meal_.get_y() + 1][snake_->meal_.get_x() + 1] = 2;
}
/// @brief Заполняет автомат конечных состояний
/// @param  текущие параметры
void SnakeGame::InitializeFSM() {
  for (int i = 0; i < NUM_STATES; i++) {
    for (int j = 0; j < NUM_ACTIONS; j++) {
      fsm[i][j] = NULL;
    };
  };
  fsm[sStart][Start] = &SnakeGame::Action__Start_Start;
  fsm[sStart][Terminate] = &SnakeGame::Action__Terminate;
  fsm[sPause][Pause] = &SnakeGame::Action__Pause_Pause;
  fsm[sPause][Terminate] = &SnakeGame::Action__Terminate;
  fsm[sMoving][Pause] = &SnakeGame::Action__Moving_Pause;
  fsm[sMoving][Terminate] = &SnakeGame::Action__Terminate;
  fsm[sMoving][Left] = &SnakeGame::Action__Moving_;
  fsm[sMoving][Right] = &SnakeGame::Action__Moving_;
  fsm[sMoving][Down] = &SnakeGame::Action__Moving_;
  fsm[sMoving][Up] = &SnakeGame::Action__Moving_;
  fsm[sGameOver][Start] = &SnakeGame::Action__sGameOver_Start;
  fsm[sGameOver][Terminate] = &SnakeGame::Action__Terminate;
}

/// @brief Изменяет скорость змейки. чем выше уровень, тем быстрее змейка
/// @param  текущие параметры
void SnakeGame::UpdateSpeed() { speed_ = 500 - 30 * (level_); };

/// @brief подсчет уровня
/// @param  текущие параметры
void SnakeGame::computeCurrentLevel() noexcept {
  int absoluteLevel = score_.getCurrentScore() / SCORE_LEVEL_UP;
  if (absoluteLevel > level_) {
    level_ = absoluteLevel >= LEVEL_MAX ? LEVEL_MAX : absoluteLevel;
    UpdateSpeed();
  }
}

/// @brief генерация еды для змейки
/// @param  текущие параметры
void SnakeGame::generateNewMeal() noexcept { snake_->generateNewMeal(); }

/// @brief рост змейки и проверка что она не максимальной длины
/// @param  текущие параметры
void SnakeGame::processSnakeEating() noexcept {
  snake_->grow();  // рост змейки
  score_.increase();
  computeCurrentLevel();
  if (snake_->getLength() == MAX_LENTH) {
    game_state_ = Game_State::sWin;
    return;
  }
  generateNewMeal();
  game_state_ = Game_State::sMoving;
}

/// @brief возвращение скорости
/// @param  текущие параметры
int SnakeGame::getSpeed() { return speed_; }
/// @brief возврващение счета
/// @param  текущие параметры
int SnakeGame::getScore() { return score_.getCurrentScore(); }

void SnakeGame::setGame_state_(Game_State state){ game_state_ = state;}
/// @brief возврващение счета
/// @param  текущие параметры
int SnakeGame::getRecord() { return score_.getTopScore(); }
/// @brief возвращение уровня
/// @param  текущие параметры
int SnakeGame::getLevel() { return level_; }

/// @brief обработка действия Старт для состояния Старт
/// @param текущие параметры
void SnakeGame::Action__Start_Start() {
  snake_->setSide();
  user_action_ = Up;
  mover_ = Up;
  level_ = 0;
  speed_ = 500;
  score_.reset();  // обновляем счет
  game_state_ = sMoving;
};

/// @brief обработка действия Выход для состояния Старт
/// @param текущие параметры
void SnakeGame::Action__Terminate() {
  score_.saveTopScore();
  game_state_ = sExitGame;
};

/// @brief обработка действия Пауза для состояния Пауза
/// @param текущие параметры
void SnakeGame::Action__Pause_Pause() { game_state_ = sMoving; };

/// @brief обработка кнопок перемещения
/// @param  текущие параметры
void SnakeGame::Action__Moving_() {
  if ((user_action_ == Up || user_action_ == Down || user_action_ == Left ||
       user_action_ == Right) &&
      snake_->isOpposite(user_action_) == false) {
    snake_->Move(user_action_);
    mover_ = user_action_;
  } else {
    snake_->Move(mover_);
  }
  if (snake_->CheckCollisionHeadAndMeal()) processSnakeEating();

  if (snake_->CheckCollisionBodyOrBorder()) {
    game_state_ = sGameOver;
  }
};

/// @brief обработка действия Пауза для состояния Движение
/// @param  текущие параметры
void SnakeGame::Action__Moving_Pause() { game_state_ = sPause; };

Game_State SnakeGame::get_game_state() { return game_state_; }
/// @brief обработка действия Старт для состояния КонецИгры
/// @param  текущие параметры
void SnakeGame::Action__sGameOver_Start() {
  score_.saveTopScore();
  // InitializeFSM();
  snake_->InitSnake();
  snake_->setSide();
  user_action_ = Up;
  mover_ = Up;
  game_state_ = sMoving;
};
int SnakeGame::getArray(int x, int y) { return array[x][y]; }

/// @brief переход из состояния в состояние конечного автомата.
/// @param UserAction_t signal_ текущие параметры
void SnakeGame::userAction(UserAction_t signal_) {
  if (game_state_ >= NUM_STATES && user_action_ >= NUM_ACTIONS) return;
  user_action_ = signal_;  // сохраняем то что делает пользователь
  if (fsm[game_state_][signal_] != nullptr)
    (this->*fsm[game_state_][signal_])();
}

};  // namespace s21
