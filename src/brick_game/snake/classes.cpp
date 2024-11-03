#include "classes.h"

#include <stdbool.h>
namespace s21 {
int Block::get_x(){return x_;}
int Block::get_y(){return y_;}

/// @brief сравнивание совподают ли координаты
/// @param Block текущие параметры
bool Block::operator==(const Block& other) const {
  return (x_ == other.x_) && (y_ == other.y_);
}

/// @brief проверка не касается ли змея границ игрового поля
/// @param текущие параметры
bool Block::isOutBorders() const noexcept {
  return ((x_ < 0 || x_ >= BOARD_WIDTH) || (y_ < 0 || y_ >= BOARD_HEIGHT));
}
/// @brief изменение по оси ординат
/// @param int value текущие параметры
void Block::change_y_(int value) { y_ = y_ + value; }

/// @brief изменение по оси абсцисс
/// @param int value текущие параметры
void Block::change_x_(int value) { x_ = x_ + value; }

/// @brief генерируем точку до тех пор пока она не окажется на свободном месте
/// поля
/// @param текущие параметры
void Block::RandomPlase() {
  x_ = rand() % (BOARD_WIDTH);
  y_ = rand() % BOARD_HEIGHT;
  while (isOutBorders()) {
    x_ = rand() % (BOARD_WIDTH);
    y_ = rand() % BOARD_HEIGHT;
  }
}

/////////////////// Snake class /////////////////////////////
Snake::Snake() { InitSnake(); }

/// @brief изменяем последнее направление змейки
/// @param текущие параметры
void Snake::setSide() { side_ = Up; }

/// @brief движение змейки
/// @param UserAction_t direction текущие параметры
void Snake::Move(UserAction_t direction_) {
  Block newHead = snake_body_.front();
  switch (direction_) {
    case UserAction_t::Up:
      newHead.change_y_(-1);
      side_ = UserAction_t::Up;
      break;
    case UserAction_t::Down:
      newHead.change_y_(1);
      side_ = UserAction_t::Down;
      break;
    case UserAction_t::Left:
      newHead.change_x_(-1);
      side_ = UserAction_t::Left;
      break;
    case UserAction_t::Right:
      newHead.change_x_(1);
      side_ = UserAction_t::Right;
      break;
    default:
    break;
  }
  // newHead.change_y_(-1);
  // ля я гений. добавляем голову вперед, а хвост удаляем. и так кажется что
  // змейка движется
  snake_body_.push_front(newHead);
  snake_body_.pop_back();

  // возможно сюда стоит добавить проверку того что врезались в тело
}

/// @brief инициализация змейки
/// @param текущие параметры
void Snake::InitSnake() {
  while (snake_body_.size() > 0) {
    snake_body_.pop_back();
  }
  for (int i = 0; i < SNAKE_LENTH; ++i) {
    Block head(INIT_BLOCK_X_SNAKE, INIT_BLOCK_Y_SNAKE + i);
    snake_body_.push_back(head);
  }
  generateNewMeal();
}

/// @brief проверка врезалась змея в тело или бордюр
/// @param текущие параметры
bool Snake::CheckCollisionBodyOrBorder() const {
  const Block head = snake_body_.front();
  for (auto it = snake_body_.begin() + 1; it != snake_body_.end(); ++it) {
    if (head == *it) {
      return true;
    }
  }

  return snake_body_.front().isOutBorders();
}

/// @brief проверка что еда не создана на змее
/// @param текущие параметры
bool Snake::CheckCollisionMeal(Block meal) const {
  for (const auto& segment : snake_body_) {
    if (segment == meal) {
      return true;
    }
  }

  return false;
}
/// @brief возвращение длины змеи
/// @param текущие параметры
int Snake::getLength() const { return snake_body_.size(); }

/// @brief пероверка совпадения еды и головы змеи
/// @param текущие параметры
bool Snake::CheckCollisionHeadAndMeal() { return meal_ == snake_body_.front(); }

/// @brief рост змеи
/// @param текущие параметры
void Snake::grow() { snake_body_.push_back(snake_body_.back()); }

/// @brief создание еды на новом месте
/// @param текущие параметры
void Snake::generateNewMeal() {
  meal_.RandomPlase();
  while (CheckCollisionMeal(meal_)) {
    meal_.RandomPlase();
  }
}

/// @brief проверка что задается не противоположное движение
/// @param текущие параметры
bool Snake::isOpposite(UserAction_t newDirection) const noexcept {
  return (side_ == UserAction_t::Up && newDirection == UserAction_t::Down) ||
         (side_ == UserAction_t::Down && newDirection == UserAction_t::Up) ||
         (side_ == UserAction_t::Left && newDirection == UserAction_t::Right) ||
         (side_ == UserAction_t::Right && newDirection == UserAction_t::Left);
}

GameScore::GameScore() { loadTopScore(); }
/// @brief обнуление счетчика
/// @param текущие параметры
void GameScore::reset() { current_ = 0; }
/// @brief получение лучшего результата
/// @param текущие параметры
void GameScore::loadTopScore() {
  std::ifstream file(RECORD_FILE_SNAKE_NAME);
  if (!file) {
    top_ = 0;
    return;
  }

  file >> top_;
  if (file.fail()) {
    throw std::runtime_error("Failed to read top score from file");
  }
}

/// @brief сохранение лучшего результата
/// @param текущие параметры
void GameScore::saveTopScore() {
  std::ofstream file(RECORD_FILE_SNAKE_NAME);
  if (!file) {
    throw std::runtime_error("Unable to open file for writing");
  }

  if (current_ > top_) top_ = current_;

  file << top_;
  current_ = 0;
  if (file.fail()) {
    throw std::runtime_error("Failed to write top score to file");
  }
}
/// @brief увеличение счетчика на один
/// @param текущие параметры
void GameScore::increase() noexcept { current_ += 1; }

}  // namespace s21
