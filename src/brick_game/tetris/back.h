#ifndef BRICK_GAME_TETRIS_TETRIS_BACK
#define BRICK_GAME_TETRIS_TETRIS_BACK

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#include "../../consts.h"
#include "fsm.h"
#include "structs.h"

void InitializeBoard(int matrix_[BOARD_HEIGHT][BOARD_WIDTH]);
void InitNextBlock(game_paremeters *game_paremeters_);
void SetGameBoard(int matrix[BOARD_HEIGHT][BOARD_WIDTH],
                  game_paremeters *game_paremeters_);
void SetNewBlock(game_paremeters *game_paremeters_);
void InitializeParameters(game_paremeters *game_paremeters_);
UserAction_t GetSignal(int key);
void userInput(UserAction_t signal_, game_paremeters *game_paremeters_);
int GetNextBlockRotationState(game_paremeters *parameters, int shift_state_);
bool CheckNextBlockState(game_paremeters *game_paremeters_, int shift_x_,
                         int shift_y_, int shift_state);
bool CheckBlockMatrix(int matrix[NUM_BLOCK_PARAM][NUM_BLOCK_PARAM]);
void FallingTopLines(int collapsed_line_, game_paremeters *game_paremeters_);
void UpdateLevel(game_paremeters *game_paremeters_);
void UpdateRecord(game_paremeters *game_paremeters_);
void UpdateSpeed(game_paremeters *game_paremeters_);
void CollapseLines(game_paremeters *game_paremeters_);
void SetBlockToGameBoard(int matrix[BOARD_HEIGHT][BOARD_WIDTH],
                         game_paremeters *game_paremeters_);
void SetNextBlockStat(game_paremeters *game_paremeters_, int shift_x_,
                      int shift_y_, int shift_state);
void SetBoardToGameBoard(int matrix[BOARD_HEIGHT][BOARD_WIDTH],
                         const game_paremeters *game_paremeters_);
bool IsEmptyLine(int y_, game_paremeters *game_paremeters_);
void SetNextBoardToBlock(int matrix[NUM_BLOCK_PARAM][NUM_BLOCK_PARAM],
                         const game_paremeters *game_paremeters_, int shift_x_,
                         int shift_y_);
bool IsFullLine(int y_, game_paremeters *game_paremeters_);
void UpdateScore(int num_collapsed_lines, game_paremeters *game_paremeters_);
int GetRecord();
void LoadRecord(game_paremeters *game_paremeters_);
void SaveRecord(game_paremeters *game_paremeters_);
int TimerAction(struct timeval *last_update_time_,
                struct timeval *current_time_, int speed);
#endif  // BRICK_GAME_TETRIS_TETRIS_BACK