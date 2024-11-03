#ifndef CONSTANTS_H_
#define CONSTANTS_H_

// board settings
#define BOARD_HEIGHT 20
#define BOARD_WIDTH 10

// // for tetris settings
#define NUM_BLOCK_PARAM 4
#define RECORD_FILE_TETRIS_NAME "Records_tetris.txt"
#define INIT_BLOCK_X 3
#define INIT_BLOCK_Y 1

// for snake settings
#define SNAKE_LENTH 4
#define RECORD_FILE_SNAKE_NAME "Records_snake.txt"
#define INIT_BLOCK_X_SNAKE 5
#define INIT_BLOCK_Y_SNAKE 10
#define MAX_LENTH 200

#define KEY_ESCAPE 27
#define KEY_SPACE 32
#define KEY_START 10

#define LEVEL_MAX 10
#define SCORE_LEVEL_UP 10;
#define LEVEL_STEP 300;

typedef enum {
  sStart,
  sSpawn,
  sMoving,
  sShifting,
  sAttaching,
  sPause,
  sGameOver,
  sExitGame,
  sWin,
  NUM_STATES
} Game_State;

// действия пользователя
typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action,
  NUM_ACTIONS
} UserAction_t;

#endif  // CONSTANTS_H_
