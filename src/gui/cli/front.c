#include "front.h"

#include "../../brick_game/tetris/back.h"
#include "../../brick_game/tetris/structs.h"
#include "../../consts.h"

// риссуем ограничения для игрового поля
void PrintBoardFields(int top_y, int bottom_y, int left_x, int right_x) {
  for (int i = left_x + 1; i < right_x; i++) mvaddch(top_y, i, ACS_HLINE);
  for (int i = top_y + 1; i < bottom_y; i++) mvaddch(i, left_x, ACS_VLINE);
  for (int i = top_y + 1; i < bottom_y; i++) mvaddch(i, right_x, ACS_VLINE);
  for (int i = left_x + 1; i < right_x; i++) mvaddch(bottom_y, i, ACS_HLINE);
  mvaddch(top_y, right_x, ACS_URCORNER);
  mvaddch(bottom_y, left_x, ACS_LLCORNER);
  mvaddch(top_y, left_x, ACS_ULCORNER);
  mvaddch(bottom_y, right_x, ACS_LRCORNER);
}

/// @brief отобразить игровое поле
/// @param game_paremeters
void PrintBlocsInGame(game_paremeters *game_paremeters_) {
  for (int i = 0; i < BOARD_HEIGHT; i++) {
    for (int j = 0; j < BOARD_WIDTH; j++) {
      mvaddch(i + 1, 2 * j + 1,
              game_paremeters_->show_board_->square_[i][j] == 0 ? ' '
                                                                : ACS_CKBOARD);
      mvaddch(i + 1, 2 * j + 2,
              game_paremeters_->show_board_->square_[i][j] == 0 ? ' '
                                                                : ACS_CKBOARD);
    }
  };
  PrintBoardFields(0, 2 * BOARD_WIDTH + 1, 0, 2 * BOARD_WIDTH + 1);
}

/// @brief отобразить текущий счет
/// @param game_paremeters
void PrintScore(int current_score_) {
  PrintBoardFields(0, 2, 2 * BOARD_WIDTH + 4, 2 * BOARD_WIDTH + 18);
  mvprintw(0, 2 * BOARD_WIDTH + 5, " Score ");
  mvprintw(1, 2 * BOARD_WIDTH + 6, "        ");
  mvprintw(1, 2 * BOARD_WIDTH + 6, "%d", current_score_);
}
void PrintHighRecord(int record_) {
  PrintBoardFields(3, 5, 2 * BOARD_WIDTH + 4, 2 * BOARD_WIDTH + 18);
  mvprintw(3, 2 * BOARD_WIDTH + 5, " Record ");
  mvprintw(4, 2 * BOARD_WIDTH + 6, "      ");
  mvprintw(4, 2 * BOARD_WIDTH + 6, "%d", record_);
}
/// @brief отобразить рекорд
/// @param game_paremeters
void PrintHighScore(game_paremeters *game_paremeters_) {
  PrintBoardFields(6, 8, 2 * BOARD_WIDTH + 4, 2 * BOARD_WIDTH + 18);
  mvprintw(6, 2 * BOARD_WIDTH + 5, " High score ");
  mvprintw(7, 2 * BOARD_WIDTH + 6, "      ");
  mvprintw(7, 2 * BOARD_WIDTH + 6, "%d", *game_paremeters_->max_score_);
}

/// @brief отобразить текущий уровень
/// @param game_paremeters
void PrintLevel(int current_level_) {
  PrintBoardFields(9, 11, 2 * BOARD_WIDTH + 4, 2 * BOARD_WIDTH + 18);
  mvprintw(9, 2 * BOARD_WIDTH + 5, " Level ");
  mvprintw(10, 2 * BOARD_WIDTH + 6, "      ");
  mvprintw(10, 2 * BOARD_WIDTH + 6, "%d", current_level_);
}

/// @brief отобразиь следующую фигурку
/// @param game_paremeters
void PrintNextBlock(game_paremeters *game_paremeters_) {
  // mvprintw(11, 2 * BOARD_WIDTH + 6, "%d", *game_paremeters_->next_block_);
  int bit_mask_ = block_collection_[*game_paremeters_->next_block_][0];
  for (int i = 0; i < NUM_BLOCK_PARAM; i++) {
    for (int j = 0; j < NUM_BLOCK_PARAM; j++) {
      mvaddch(i + 15, 2 * (j + BOARD_WIDTH) + 8,
              (bit_mask_ & (1 << (i * 4 + j))) == 0 ? ' ' : ACS_CKBOARD);
      mvaddch(i + 15, 2 * (j + BOARD_WIDTH) + 9,
              (bit_mask_ & (1 << (i * 4 + j))) == 0 ? ' ' : ACS_CKBOARD);
    };
  };
  PrintBoardFields(13, 19, 2 * BOARD_WIDTH + 4, 2 * BOARD_WIDTH + 18);
  mvprintw(13, 2 * BOARD_WIDTH + 5, " Next figure ");
}

void PrintStart() {
  mvprintw(10, 2, "Press ENTER to Start!");
  mvprintw(11, 2, "Press ESC to Exit!");
}

void PrintPause() {
  mvprintw(10, 2, "Press P to Continue!");
  mvprintw(11, 2, "Press ESC to Exit!");
}

/// @brief итобразить игровое поле польностью
/// @param game_paremeters
void PrintGameTetris(game_paremeters *game_paremeters_) {
  if (*game_paremeters_->state_ == sStart) PrintStart();
  // else if (*game_paremeters_->state_ == sGameOver)
  //   PrintStart();
  else if (*game_paremeters_->state_ == sPause)
    PrintPause();
  else {
    mvprintw(10, 2, "                          ");
    mvprintw(11, 2, "                          ");
    PrintBlocsInGame(game_paremeters_);
    // PrintCurrentBlock(game_paremeters_);
    PrintScore(*game_paremeters_->current_score_);
    PrintHighRecord(*game_paremeters_->record_);
    PrintHighScore(game_paremeters_);
    PrintLevel(*game_paremeters_->current_level_);
    PrintNextBlock(game_paremeters_);
  }

  // mvprintw(0, 2, "%d", *game_paremeters_->next_block_);
  // mvprintw(0, 4, "%d", game_paremeters_->current_block_->block_rotation_);
  // mvprintw(0, 6, "%d", game_paremeters_->current_block_->block_type_);
  // mvprintw(1, 2, "%d", *game_paremeters_->state_);
  // mvprintw(2, 2, "%d", game_paremeters_->current_block_->x_);
  // mvprintw(3, 2, "%d", game_paremeters_->current_block_->y_);
  refresh();
}

// int TimerAction(struct timeval *last_update_time_,
//                 struct timeval *current_time_, int speed) {
//   int result = 0;
//   gettimeofday(current_time_, NULL);
//   double elapsed_time =
//       (current_time_->tv_sec - last_update_time_->tv_sec) * 1000.0 +
//       (current_time_->tv_usec - last_update_time_->tv_usec) / 1000.0; //
//       переводим в милисекунды
//   if (elapsed_time >= speed) {
//     *last_update_time_ = *current_time_;
//     result = 1;
//   }
//   usleep(1000);
//   return result;
// }
