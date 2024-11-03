#ifndef GUI_CLI_FRONTEND
#define GUI_CLI_FRONTEND

#include <ncurses.h>

#include "../../brick_game/tetris/back.h"
#include "../../brick_game/tetris/structs.h"
#include "../../consts.h"
// c++
// #include "../../brick_game/snake/classes.h"
// #include "../../brick_game/snake/consts.h"
// #include "../../brick_game/snake/game.h"
// #include "../../brick_game/snake/controller.h"

// риссуем ограничения для игрового поля
void PrintBoardFields(int top_y, int bottom_y, int left_x, int right_x);
void PrintBlocsInGame(game_paremeters *game_paremeters_);

void PrintScore(int current_score_);
void PrintHighScore(game_paremeters *game_paremeters_);
void PrintLevel(int current_level_);
void PrintHighRecord(int record_);
void PrintNextBlock(game_paremeters *game_paremeters_);
void PrintGameTetris(game_paremeters *game_paremeters_);
// int TimerAction(struct timeval *last_update_time_,
//                 struct timeval *current_time_, int speed);
#endif  // GUI_CLI_FRONTEND
