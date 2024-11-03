#ifndef BRICK_GAME_TETRIS_TETRIS_STRUCT
#define BRICK_GAME_TETRIS_TETRIS_STRUCT

#include "../../consts.h"
// board
typedef struct {
  int square_[BOARD_HEIGHT][BOARD_WIDTH];
} board_struct;

//ПЕРЕЧИСЛЕНИЯ
// состояния

typedef enum {
  kBlockI = 0,
  kBlockJ = 1,
  kBlockL = 2,
  kBlockO = 3,
  kBlockS = 4,
  kBlockT = 5,
  kBlockZ = 6,
  NUM_BLOCK_TYPES
} Block_Type;

typedef struct {
  int x_;
  int y_;
  Block_Type block_type_;
  int block_rotation_;
} Block_Property;

typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

// Предварительное объявление структуры
typedef struct game_paremeters game_paremeters;

// Указатель на функцию
typedef void (*StateFun)(game_paremeters *);

// Настройки игры
// Структура с адресами
typedef struct game_paremeters {
  int *current_score_;
  int *current_level_;
  int *current_speed_;
  int *max_score_;  // сколько нужно для получения следующего уро
  int *record_;
  // PlayerState_t *current_state_;
  board_struct *show_board_;
  board_struct *board_;
  Block_Type *next_block_;
  Block_Property *current_block_;
  Game_State *state_;
  StateFun fsm[NUM_STATES][NUM_ACTIONS];  // конечный автомат
} game_paremeters;

// Указатель на функцию
// typedef void (*StateFun)(game_paremeters *);

// Глобальные переменные
// ориентации блоков
static const int block_collection_[NUM_BLOCK_TYPES][NUM_BLOCK_PARAM] = {
    {0b0100010001000100, 0b0000000011110000, 0b0100010001000100,
     0b0000000011110000},  // I
    {0b0000001000100110, 0b0000010001110000, 0b0000001100100010,
     0b0000000001110001},  // J
    {0b0000001000100011, 0b0000000001110100, 0b0000011000100010,
     0b0000000101110000},  // L
    {0b0000011001100000, 0b0000011001100000, 0b0000011001100000,
     0b0000011001100000},  // O
    {0b0000000000110110, 0b0000010001100010, 0b0000000000110110,
     0b0000010001100010},  // S
    {0b0000001001110000, 0b0000001000110010, 0b0000000001110010,
     0b0000001001100010},  // T
    {0b0000000001100011, 0b0000001001100100, 0b0000000001100011,
     0b0000001001100100},  // Z
};

#endif  // BRICK_GAME_TETRIS_TETRIS_STRUCT