#include "back.h"

/// @brief инициализирует поле нулями
/// @param game_paremeters_ текущие параметры
/// tests
void InitializeBoard(int matrix_[BOARD_HEIGHT][BOARD_WIDTH]) {
  for (int i = 0; i < BOARD_HEIGHT; i++) {
    for (int j = 0; j < BOARD_WIDTH; j++) {
      matrix_[i][j] = 0;
    };
  };
};

/// @brief переносит поле в игровое поле (для отображения)
/// @param matrix заполняемая матрица игрового поля
/// @param game_paremeters_ текущие параметры
/// tested
void SetBoardToGameBoard(int matrix[BOARD_HEIGHT][BOARD_WIDTH],
                         const game_paremeters *game_paremeters_) {
  for (int i = 0; i < BOARD_HEIGHT; i++) {
    for (int j = 0; j < BOARD_WIDTH; j++) {
      matrix[i][j] = matrix[i][j] + game_paremeters_->board_->square_[i][j];
    };
  };
};

/// @brief инициализация следующего игрового блока
/// @param game_paremeters_ текущие параметры
/// tested
void InitNextBlock(game_paremeters *game_paremeters_) {
  *game_paremeters_->next_block_ = rand() % NUM_BLOCK_TYPES;
};

/// @brief создание игрового поля
/// @param matrix заполняемая матрица игрового поля
/// @param game_paremeters_ текущие параметры
/// testing
void SetGameBoard(int matrix[BOARD_HEIGHT][BOARD_WIDTH],
                  game_paremeters *game_paremeters_) {
  InitializeBoard(matrix);
  SetBlockToGameBoard(matrix, game_paremeters_);
  SetBoardToGameBoard(matrix, game_paremeters_);
};

/// @brief устанавливает текущего игрока из next и случайно генерирует next
/// @param game_paremeters_  текущие параметры
/// tested
void SetNewBlock(game_paremeters *game_paremeters_) {
  game_paremeters_->current_block_->block_type_ =
      *game_paremeters_->next_block_;
  game_paremeters_->current_block_->block_rotation_ = 0;
  game_paremeters_->current_block_->x_ = INIT_BLOCK_X;
  game_paremeters_->current_block_->y_ = INIT_BLOCK_Y;
  InitNextBlock(game_paremeters_);
};

/// @brief устанавливает значения для начала игры
/// @param game_paremeters_ текущие параметры
/// tested
void InitializeParameters(game_paremeters *game_paremeters_) {
  *game_paremeters_->current_level_ = 0;
  *game_paremeters_->current_score_ = 0;
  *game_paremeters_->current_speed_ = 500;
  InitializeBoard(game_paremeters_->board_->square_);
  InitializeBoard(game_paremeters_->show_board_->square_);
  InitNextBlock(game_paremeters_);
  SetNewBlock(game_paremeters_);
};

/// @brief ввод пользователем
/// @param signal_ заполняемая матрица игрового поля
/// @param game_paremeters_ текущие параметры
/// tested
void userInput(UserAction_t signal_, game_paremeters *game_paremeters_) {
  if (*game_paremeters_->state_ >= NUM_STATES && signal_ >= NUM_ACTIONS) return;
  StateFun action = *game_paremeters_->fsm[*game_paremeters_->state_][signal_];
  if (action != NULL) action(game_paremeters_);
  SetGameBoard(game_paremeters_->show_board_->square_, game_paremeters_);
}

/// @brief получаем информацию о нажатой кнопке пользователем
/// @param key код нажатой клавиши ползователем
/// tests
UserAction_t GetSignal(int key) {
  int signal = Up;
  if (key == KEY_DOWN)
    signal = Down;
  else if (key == KEY_LEFT)
    signal = Left;
  else if (key == KEY_RIGHT)
    signal = Right;
  else if (key == KEY_ESCAPE)
    signal = Terminate;
  else if (key == KEY_START)
    signal = Start;
  else if (key == 'p' || key == 'P')
    signal = Pause;
  else if (key == KEY_SPACE || key == KEY_UP)
    signal = Action;
  return signal;
}

/// @brief инициализация следующего игрового блока
/// @param key заполняемая матрица игрового поля
/// tested
void SetNextBlock(int matrix[NUM_BLOCK_PARAM][NUM_BLOCK_PARAM],
                  Block_Type block_type_, int block_rotation_) {
  int bit_mask_ = block_collection_[block_type_][block_rotation_];
  for (int i = 0; i < NUM_BLOCK_PARAM; i++) {
    for (int j = 0; j < NUM_BLOCK_PARAM; j++) {
      matrix[i][j] = matrix[i][j] + (bit_mask_ & (1 << (i * 4 + j))) ? 1 : 0;
    };
  };
};

/// @brief получение следующего поворота фигуры
/// @param parameters заполняемая матрица игрового поля
/// @param shift_state_ заполняемая матрица игрового поля
/// tested
int GetNextBlockRotationState(game_paremeters *parameters, int shift_state_) {
  return (parameters->current_block_->block_rotation_ + shift_state_) %
         NUM_BLOCK_PARAM;
};

/// @brief проверка следующего состояния у блока
/// @param game_paremeters_ заполняемая матрица игрового поля
/// @param shift_x_ заполняемая матрица игрового поля
/// @param shift_y_ заполняемая матрица игрового поля
/// @param shift_state заполняемая матрица игрового поля
/// tested
bool CheckNextBlockState(game_paremeters *game_paremeters_, int shift_x_,
                         int shift_y_, int shift_state) {
  int next_block_matrix_[NUM_BLOCK_PARAM][NUM_BLOCK_PARAM] = {0};
  int next_block_state_ =
      GetNextBlockRotationState(game_paremeters_, shift_state);
  SetNextBlock(next_block_matrix_,
               game_paremeters_->current_block_->block_type_,
               next_block_state_);
  SetNextBoardToBlock(next_block_matrix_, game_paremeters_, shift_x_, shift_y_);
  return CheckBlockMatrix(next_block_matrix_);
};

/// @brief проверяет матрицу на наличие элементов со значением больше 1
/// @param matrix проверяемая матрица
/// @return TRUE если элемент найден, иначе FALSE
/// tested
bool CheckBlockMatrix(int matrix[NUM_BLOCK_PARAM][NUM_BLOCK_PARAM]) {
  bool result = false;
  for (int i = 0; i < NUM_BLOCK_PARAM && !result; i++) {
    for (int j = 0; j < +NUM_BLOCK_PARAM && !result; j++) {
      if (matrix[i][j] > 1) result = true;
    };
  };
  return result;
};

/// @brief переносит в матрицу кусочек поля (на основании координат расположения
/// блока фигуры на поле); в случае выхода за пределы переносит +1
/// @param matrix матрица для переноса
/// @param game_paremeters_ текущие параметры
/// tested
void SetNextBoardToBlock(int matrix[NUM_BLOCK_PARAM][NUM_BLOCK_PARAM],
                         const game_paremeters *game_paremeters_, int shift_x_,
                         int shift_y_) {
  int x, y;

  for (int i = 0; i < NUM_BLOCK_PARAM; i++) {
    for (int j = 0; j < +NUM_BLOCK_PARAM; j++) {
      x = j + game_paremeters_->current_block_->x_ + shift_x_;
      y = i + game_paremeters_->current_block_->y_ + shift_y_;
      if (x < 0 || x >= BOARD_WIDTH || y < 0 || y >= BOARD_HEIGHT)
        matrix[i][j] = matrix[i][j] + 1;
      else
        matrix[i][j] = matrix[i][j] + game_paremeters_->board_->square_[y][x];
    };
  };
};

/// @brief проверка что полоса пустая
/// @param game_parameters заполняемая матрица игрового поля
/// @param y_ заполняемая матрица игрового поля
/// tested
bool IsEmptyLine(int y_, game_paremeters *game_paremeters_) {
  bool is_empty_line_ = true;
  for (int i = 0; i < BOARD_WIDTH && is_empty_line_ == true; i++) {
    if (!!game_paremeters_->board_->square_[y_][i]) is_empty_line_ = false;
  };
  return is_empty_line_;
}

/// @brief проверка что полоса заполнена
/// @param y_ заполняемая матрица игрового поля
/// @param game_paremeters_ заполняемая матрица игрового поля
/// tested
bool IsFullLine(int y_, game_paremeters *game_paremeters_) {
  bool is_full_line_ = true;
  for (int i = 0; i < BOARD_WIDTH && is_full_line_ == true; i++) {
    if (!game_paremeters_->board_->square_[y_][i]) is_full_line_ = false;
  };
  return is_full_line_;
};

/// @brief переносит строки выше схлопывающейся строки на 1 ниже (пока не дойдет
/// до верха или не встретит пустую строку)
/// @param collapsed_line_ номер схлопнувшейся строки
/// @param game_paremeters_ текущие параметры
/// tested
void FallingTopLines(int collapsed_line_, game_paremeters *game_paremeters_) {
  for (int i = collapsed_line_ - 1; i >= 0; i--) {
    for (int j = 0; j < BOARD_WIDTH; j++) {
      game_paremeters_->board_->square_[i + 1][j] =
          game_paremeters_->board_->square_[i][j];
    }
  }
};

/// @brief обновляет значение текущего уровня в зависимости от текущего счета
/// @param parameters_ текущие параметры
// tested
void UpdateLevel(game_paremeters *game_paremeters_) {
  int current_level_ =
      *game_paremeters_->current_score_ / *game_paremeters_->max_score_;
  if (current_level_ > *game_paremeters_->current_level_) {
    *game_paremeters_->max_score_ = *game_paremeters_->max_score_ + LEVEL_STEP;
    *game_paremeters_->current_level_ =
        (current_level_ > LEVEL_MAX) ? LEVEL_MAX : current_level_;
  }
};

/// @brief обновляет рекорд, если текущий счет больше рекорда
/// @param game_paremeters_ текущие параметры
/// tests
void UpdateRecord(game_paremeters *game_paremeters_) {
  *game_paremeters_->record_ =
      (*game_paremeters_->current_score_ > *game_paremeters_->record_)
          ? *game_paremeters_->current_score_
          : *game_paremeters_->record_;
};

/// @brief определить скорость (фактически: время задержки) по уровню
/// @param level уровень
/// @return значение скорости (задержки)
/// tests
void UpdateSpeed(game_paremeters *game_paremeters_) {
  *game_paremeters_->current_speed_ =
      500 - 30 * (*game_paremeters_->current_level_);
};

/// @brief схлопывание полностью заполненных строк с начислением очков и
/// изменением скорости игры
/// @param game_paremeters_ текущие параметры
/// tested
void CollapseLines(game_paremeters *game_paremeters_) {
  int num_collapse_ = 0;
  for (int i = BOARD_HEIGHT - 1;
       i >= 0 && IsEmptyLine(i, game_paremeters_) == false;) {
    if (IsFullLine(i, game_paremeters_) == true) {
      num_collapse_++;
      FallingTopLines(i, game_paremeters_);
    } else
      i--;
  };
  UpdateScore(num_collapse_, game_paremeters_);
  UpdateLevel(game_paremeters_);
  UpdateSpeed(game_paremeters_);
  UpdateRecord(game_paremeters_);
};

/// @brief получение рекордного значения
/// @param y_ заполняемая матрица игрового поля
/// @param game_paremeters_ заполняемая матрица игрового поля
int GetRecord() {
  FILE *file;
  int record = 0;

  file = fopen(RECORD_FILE_TETRIS_NAME, "r");
  if (file) {
    // Читаем число из файла
    if (fscanf(file, "%d", &record) != 1) {
      //      mvprintw(10, 2, "не удалось прочитать число");
      // Если не удалось прочитать число, возвращаем 0
      fclose(file);
      return 0;
    }
    fclose(file);
  }
  // Закрываем файл после чтения

  return record;
}

/// @brief обновляет текущий счет в зависимости от количество схлопнувшихся
/// линий
/// @param num_collapsed_lines количество схплопнувшихся линий
/// @param game_paremeters_  текущие параметры
/// tested
void UpdateScore(int num_collapsed_lines, game_paremeters *game_paremeters_) {
  int points[] = {0, 100, 300, 700, 1500};
  if (num_collapsed_lines >= 1 && num_collapsed_lines <= 4)
    *game_paremeters_->current_score_ += points[num_collapsed_lines];
};

/// @brief переносит конфигурацию фигурки в игровое поле (для отображения)
/// @param game_paremeters_ текущие параметры
/// testing
void SetBlockToGameBoard(int matrix[BOARD_HEIGHT][BOARD_WIDTH],
                         game_paremeters *game_paremeters_) {
  int x = 0, y = 0;
  int bit_mask_ =
      block_collection_[game_paremeters_->current_block_->block_type_]
                       [game_paremeters_->current_block_->block_rotation_];
  for (int i = 0; i < NUM_BLOCK_PARAM; i++) {
    for (int j = 0; j < NUM_BLOCK_PARAM; j++) {
      y = i + game_paremeters_->current_block_->y_;
      x = j + game_paremeters_->current_block_->x_;
      if (!(y < 0 || y >= BOARD_HEIGHT || x < 0 || x >= BOARD_WIDTH))
        matrix[y][x] = matrix[y][x] + (bit_mask_ & (1 << (i * 4 + j))) ? 1 : 0;
    };
  };
}

/// @brief переводит игрока в следующее состояние
/// @param game_paremeters_ текущие параметры
/// @param shift_x_ смещение по горизонтали (-1 влево, +1 вправо)
/// @param shift_y_ смещение по вертикали (+1 вниз)
/// @param shift_state смещение по вращению (+1 вращение)
// tested
void SetNextBlockStat(game_paremeters *game_paremeters_, int shift_x_,
                      int shift_y_, int shift_state) {
  game_paremeters_->current_block_->x_ += shift_x_;
  game_paremeters_->current_block_->y_ += shift_y_;
  game_paremeters_->current_block_->block_rotation_ =
      GetNextBlockRotationState(game_paremeters_, shift_state);
};

/// @brief загружает рекорд из файла
/// @param game_paremeters_ текущие параметры
// tested
void LoadRecord(game_paremeters *game_paremeters_) {
  FILE *p_file = fopen(RECORD_FILE_TETRIS_NAME, "rb");
  if (!!p_file) {
    fread(game_paremeters_->record_, sizeof(int), 1, p_file);
    fclose(p_file);
  } else
    *game_paremeters_->record_ = 0;
};

/// @brief сохраняет рекорд в файл
/// @param game_paremeters_ текущие параметры
// tested
void SaveRecord(game_paremeters *game_paremeters_) {
  FILE *p_file = fopen(RECORD_FILE_TETRIS_NAME, "wb");
  if (!!p_file) {
    fwrite(game_paremeters_->current_score_, sizeof(int), 1, p_file);
    fclose(p_file);
  };
};

int TimerAction(struct timeval *last_update_time_,
                struct timeval *current_time_, int speed) {
  int result = 0;
  gettimeofday(current_time_, NULL);
  double elapsed_time =
      (current_time_->tv_sec - last_update_time_->tv_sec) * 1000.0 +
      (current_time_->tv_usec - last_update_time_->tv_usec) /
          1000.0;  // переводим в милисекунды
  if (elapsed_time >= speed) {
    *last_update_time_ = *current_time_;
    result = 1;
  }
  usleep(1000);
  return result;
}
