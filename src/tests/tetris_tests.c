#include "../brick_game/tetris/back.h"

#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


START_TEST(s21_ceil_f) {
  int matrix[BOARD_HEIGHT][BOARD_WIDTH];

  // Инициализация матрицы
  InitializeBoard(matrix);

  // Проверка, что все элементы матрицы равны 0
  for (int i = 0; i < BOARD_HEIGHT; i++) {
    for (int j = 0; j < BOARD_WIDTH; j++) {
      ck_assert_int_eq(matrix[i][j], 0);
    };
  };
};
END_TEST

START_TEST(s21_getSignal) {
  UserAction_t check;
  check = GetSignal(KEY_DOWN);
  ck_assert_int_eq(check, Down);
  check = GetSignal(KEY_LEFT);
  ck_assert_int_eq(check, Left);
  check = GetSignal(KEY_RIGHT);
  ck_assert_int_eq(check, Right);
  check = GetSignal(KEY_ESCAPE);
  ck_assert_int_eq(check, Terminate);
  check = GetSignal(KEY_START);
  ck_assert_int_eq(check, Start);
  check = GetSignal('p');
  ck_assert_int_eq(check, Pause);
  check = GetSignal('P');
  ck_assert_int_eq(check, Pause);
  check = GetSignal(KEY_SPACE);
  ck_assert_int_eq(check, Action);
  check = GetSignal(KEY_UP);
  ck_assert_int_eq(check, Action);
  check = GetSignal(0401);
  ck_assert_int_eq(check, Up);
  check = GetSignal('g');
  ck_assert_int_eq(check, Up);

};
END_TEST


START_TEST(s21_UpdateSpeed) {
  game_paremeters game_paremeters_ = {0};

  int current_speed_ = 500;
  int current_level = 1;
  
  game_paremeters_.current_level_ = &current_level;
  game_paremeters_.current_speed_ = &current_speed_;
 
  UpdateSpeed(&game_paremeters_);
  int speed = *(game_paremeters_.current_speed_);
  ck_assert_int_eq(speed, 470);
};
END_TEST

START_TEST(s21_UpdateRecord) {
  game_paremeters game_paremeters_ = {0};
  int current_score_ = 0;
  int record_ = 0;

  
  game_paremeters_.current_score_ = &current_score_;
  game_paremeters_.record_ = &record_;

  *(game_paremeters_.current_score_) = 10;
  UpdateRecord(&game_paremeters_);
  int record = *(game_paremeters_.record_);
  ck_assert_int_eq(record, 10);
};
END_TEST


// Тест для функции InitNextBlock
START_TEST(s21_init_next_block) {
    game_paremeters game_paremeters_;
 
  Block_Type next_bloc = 0;

  game_paremeters_.next_block_ = &next_bloc;


    srand(time(NULL));  
    
    InitNextBlock(&game_paremeters_);

    ck_assert_int_ge(*(game_paremeters_.next_block_), 0);
    ck_assert_int_lt(*(game_paremeters_.next_block_), NUM_BLOCK_TYPES);
}
END_TEST

START_TEST(s21_SetBoardToGameBoard) {
  game_paremeters game_paremeters_;
  board_struct board_ = {0};
  game_paremeters_.board_ = &board_;
  InitializeBoard(game_paremeters_.board_->square_);

        // Инициализация данных
    int matrix[BOARD_HEIGHT][BOARD_WIDTH] = {0};
    // Заполнение данных для теста
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            game_paremeters_.board_->square_[i][j] = i + j;
        }
    }

    // game_paremeters_.board_ = &board;

    // Вызов функции
    SetBoardToGameBoard(matrix, &game_paremeters_);

    // Проверка результатов
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
          ck_assert_int_eq(game_paremeters_.board_->square_[i][j], i + j);
        
        }
    }


  }
END_TEST




START_TEST(s21_SetGameBoard) {
  game_paremeters game_paremeters_;
  board_struct board_ = {0};
  board_struct show_board_ = {0};
  Block_Type next_bloc = 0;
  Block_Property current_block_ = {0,0,3,0};
  game_paremeters_.board_ = &board_;
  game_paremeters_.next_block_ = &next_bloc;
  game_paremeters_.current_block_ = &current_block_;
  game_paremeters_.show_board_ = &show_board_;
  // int bit_mask_ = block_collection_[3][0];
   board_struct board = {
        .square_ = {{0,0,0,0,0,0,0,0,0,0},{0,2,2,0,0,0,0,0,0,0},{0,2,2,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}}
    };

  // int test = {{0,0,0,0,0,0,0,0,0,0},{0,1,1,0,0,0,0,0,0,0},{0,1,1,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};
  
  SetGameBoard(game_paremeters_.board_->square_, &game_paremeters_);
  for (int i = 0; i < NUM_BLOCK_PARAM; i++) {
    for (int j = 0; j < NUM_BLOCK_PARAM; j++) {
        ck_assert_int_eq(game_paremeters_.board_->square_[i][j] , board.square_[i][j]);
    };
  };

  }
END_TEST




START_TEST(s21_SetNewBlock) {
  game_paremeters game_paremeters_;
  Block_Type next_bloc = 3;
  Block_Property current_block_ = {0,0,0,0};

  game_paremeters_.next_block_ = &next_bloc;
  game_paremeters_.current_block_ = &current_block_;
  // int bit_mask_ = block_collection_[3][0];
   Block_Property test_block = {
        .block_rotation_ = 0,
        .block_type_ = 3,
        .x_ = INIT_BLOCK_X,
        .y_ = INIT_BLOCK_Y
    };

  // int test = {{0,0,0,0,0,0,0,0,0,0},{0,1,1,0,0,0,0,0,0,0},{0,1,1,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};
  
  SetNewBlock( &game_paremeters_);


  ck_assert_int_eq(current_block_.block_rotation_ , test_block.block_rotation_);
  ck_assert_int_eq(current_block_.block_type_ , test_block.block_type_);
  ck_assert_int_eq(current_block_.x_ , test_block.x_);
  ck_assert_int_eq(current_block_.y_ , test_block.y_);
  SetNextBlockStat(&game_paremeters_, 10, 10, 1);
  ck_assert_int_eq(game_paremeters_.current_block_->x_, INIT_BLOCK_X + 10);
  ck_assert_int_eq(game_paremeters_.current_block_->y_, INIT_BLOCK_Y + 10);
  ck_assert_int_eq(game_paremeters_.current_block_->block_rotation_, 1);
  }
END_TEST



START_TEST(s21_Initialize) {
  int current_score_ = 50;
  int current_level_ = 50;
  int current_speed_ = 5540;
  int max_score_ = LEVEL_STEP; // сколько нужно для получения следующего уро
  int record_ = 0;
  game_paremeters game_paremeters_;
  board_struct board_ = {0};
  board_struct show_board_ = {0};
  Block_Type next_bloc = 0;
  Block_Property current_block_ = {0,0,3,0};

  game_paremeters_.current_score_ = &current_score_;
  game_paremeters_.current_level_ = &current_level_;
  game_paremeters_.current_speed_ = &current_speed_;
  game_paremeters_.max_score_ = &max_score_;
  game_paremeters_.record_ = &record_;

  game_paremeters_.board_ = &board_;
  game_paremeters_.next_block_ = &next_bloc;
  game_paremeters_.current_block_ = &current_block_;
  game_paremeters_.show_board_ = &show_board_;
  InitializeParameters (&game_paremeters_);

  ck_assert_int_eq(current_score_, 0);
  ck_assert_int_eq(current_level_, 0);
  ck_assert_int_eq(current_speed_, 500);
  // ck_assert_int_eq(current_block_.y_ , test_block.y_);
  }
END_TEST


START_TEST(s21_userInput) {
 int current_score_ = 0;
  int current_level_ = 0;
  int current_speed_ = 500;
  int max_score_ = LEVEL_STEP; // сколько нужно для получения следующего уро
  int record_ = GetRecord();
  // PlayerState_t *current_state_;
  board_struct show_board_ = {0};
  board_struct board_ = {0};

  Block_Type next_bloc = {0};
  Block_Property current_block_ = {0};
  // Game_State *state_;
  Game_State state = sStart;
  game_paremeters game_paremeters_ = {0};
  game_paremeters_.current_score_ = &current_score_;
  game_paremeters_.current_level_ = &current_level_;
  game_paremeters_.current_speed_ = &current_speed_;
  game_paremeters_.max_score_ = &max_score_;
  game_paremeters_.record_ = &record_;

  game_paremeters_.board_ = &board_;
  game_paremeters_.show_board_ = &show_board_;
  game_paremeters_.next_block_ = &next_bloc;
  game_paremeters_.current_block_ = &current_block_;
  InitializeFSM(&game_paremeters_);
  game_paremeters_.state_ = &state;
  userInput (Start, &game_paremeters_);

  ck_assert_int_eq(*game_paremeters_.state_, sSpawn);
    userInput (Start, &game_paremeters_);
  ck_assert_int_eq(state, sMoving);

   userInput (Terminate, &game_paremeters_);
  ck_assert_int_eq(state, sExitGame);
  state = sMoving;
     userInput (Pause, &game_paremeters_);
  ck_assert_int_eq(state, sPause);
       userInput (Pause, &game_paremeters_);
  ck_assert_int_eq(state, sMoving);
  userInput (Left, &game_paremeters_);
  ck_assert_int_eq(game_paremeters_.current_block_->x_, INIT_BLOCK_X - 1);
  ck_assert_int_eq(game_paremeters_.current_block_->y_, INIT_BLOCK_Y);
  ck_assert_int_eq(state, sMoving);
  userInput (Right, &game_paremeters_);
  ck_assert_int_eq(game_paremeters_.current_block_->x_, INIT_BLOCK_X );
  ck_assert_int_eq(game_paremeters_.current_block_->y_, INIT_BLOCK_Y);
  ck_assert_int_eq(state, sMoving);
  userInput (Down, &game_paremeters_);
  ck_assert_int_eq(state, sMoving);
  userInput (Action, &game_paremeters_);
  ck_assert_int_eq(state, sMoving);
  userInput (Terminate, &game_paremeters_);
  ck_assert_int_eq(state, sExitGame);
  state = sGameOver;
  userInput (Terminate, &game_paremeters_);
  ck_assert_int_eq(state, sExitGame);
  state = sGameOver;
  userInput (Start, &game_paremeters_);
  ck_assert_int_eq(state, sSpawn);

  // ck_assert_int_eq(current_speed_, 500);
  // ck_assert_int_eq(current_block_.y_ , test_block.y_);
  }
END_TEST



START_TEST(s21_CheckNextBlockState) {
 int current_score_ = 0;
  int current_level_ = 0;
  int current_speed_ = 500;
  int max_score_ = LEVEL_STEP; // сколько нужно для получения следующего уро
  int record_ = GetRecord();
  // PlayerState_t *current_state_;
  board_struct show_board_ = {0};
  board_struct board_ = {0};

  Block_Type next_bloc = {0};
  Block_Property current_block_ = {0};
  // Game_State *state_;
  Game_State state = sStart;
  game_paremeters game_paremeters_ = {0};
  game_paremeters_.current_score_ = &current_score_;
  game_paremeters_.current_level_ = &current_level_;
  game_paremeters_.current_speed_ = &current_speed_;
  game_paremeters_.max_score_ = &max_score_;
  game_paremeters_.record_ = &record_;

  game_paremeters_.board_ = &board_;
  game_paremeters_.show_board_ = &show_board_;
  game_paremeters_.next_block_ = &next_bloc;
  game_paremeters_.current_block_ = &current_block_;
  InitializeFSM(&game_paremeters_);
  game_paremeters_.state_ = &state;
  bool status = CheckNextBlockState (&game_paremeters_, 1, 1, 0);

  ck_assert_int_eq(status, false);

  status = CheckNextBlockState (&game_paremeters_, 19, 1, 0);

  ck_assert_int_eq(status, true);

  // ck_assert_int_eq(current_speed_, 500);
  // ck_assert_int_eq(current_block_.y_ , test_block.y_);
  }
END_TEST



START_TEST(s21_IsEmptyLine) {
 int current_score_ = 0;
  int current_level_ = 0;
  int current_speed_ = 500;
  int max_score_ = LEVEL_STEP; // сколько нужно для получения следующего уро
  int record_ = GetRecord();
  // PlayerState_t *current_state_;
  board_struct show_board_ = {0};
  board_struct board_ = {0};

  Block_Type next_bloc = {0};
  Block_Property current_block_ = {0};
  // Game_State *state_;
  Game_State state = sStart;
  game_paremeters game_paremeters_ = {0};
  game_paremeters_.current_score_ = &current_score_;
  game_paremeters_.current_level_ = &current_level_;
  game_paremeters_.current_speed_ = &current_speed_;
  game_paremeters_.max_score_ = &max_score_;
  game_paremeters_.record_ = &record_;

  game_paremeters_.board_ = &board_;
  game_paremeters_.show_board_ = &show_board_;
  game_paremeters_.next_block_ = &next_bloc;
  game_paremeters_.current_block_ = &current_block_;
  InitializeFSM(&game_paremeters_);
  game_paremeters_.state_ = &state;
  bool status = IsEmptyLine (0, &game_paremeters_);

  ck_assert_int_eq(status, true);

  for (int i = 0; i < BOARD_WIDTH ; i++){
    game_paremeters_.board_->square_[19][i] = 1;
    game_paremeters_.board_->square_[17][i] = 1;
    game_paremeters_.board_->square_[16][i] = 1;
  }
   for (int i = 0; i < 5; i++){
    game_paremeters_.board_->square_[18][i] = 1;
  }
  status = IsEmptyLine (19, &game_paremeters_);
  ck_assert_int_eq(status, false);
  status = IsEmptyLine (18, &game_paremeters_);
  ck_assert_int_eq(status, false);
  status = IsFullLine(19, &game_paremeters_);
  ck_assert_int_eq(status, true);
  status = IsFullLine (18, &game_paremeters_);
  ck_assert_int_eq(status, false);
  CollapseLines(&game_paremeters_);
  ck_assert_int_eq(current_score_, 700);
  ck_assert_int_eq(current_level_, 2);
  status = IsEmptyLine (17, &game_paremeters_);
  ck_assert_int_eq(status, true);
  status = IsEmptyLine (16, &game_paremeters_);
  ck_assert_int_eq(status, true);

  }
END_TEST

START_TEST(s21_FallingTopLines) {
 int current_score_ = 0;
  int current_level_ = 0;
  int current_speed_ = 500;
  int max_score_ = LEVEL_STEP; // сколько нужно для получения следующего уро
  int record_ = GetRecord();
  // PlayerState_t *current_state_;
  board_struct show_board_ = {0};
  board_struct board_ = {0};

  Block_Type next_bloc = {0};
  Block_Property current_block_ = {0};
  // Game_State *state_;
  Game_State state = sStart;
  game_paremeters game_paremeters_ = {0};
  game_paremeters_.current_score_ = &current_score_;
  game_paremeters_.current_level_ = &current_level_;
  game_paremeters_.current_speed_ = &current_speed_;
  game_paremeters_.max_score_ = &max_score_;
  game_paremeters_.record_ = &record_;

  game_paremeters_.board_ = &board_;
  game_paremeters_.show_board_ = &show_board_;
  game_paremeters_.next_block_ = &next_bloc;
  game_paremeters_.current_block_ = &current_block_;
  InitializeFSM(&game_paremeters_);
  game_paremeters_.state_ = &state;
  bool status = IsEmptyLine (0, &game_paremeters_);

  ck_assert_int_eq(status, true);

  for (int i = 0; i < BOARD_WIDTH ; i++){
    game_paremeters_.board_->square_[19][i] = 1;
  }
   for (int i = 0; i < 5; i++){
    game_paremeters_.board_->square_[18][i] = 1;
  }
  status = IsEmptyLine (19, &game_paremeters_);
  ck_assert_int_eq(status, false);
  status = IsEmptyLine (18, &game_paremeters_);
  ck_assert_int_eq(status, false);
  FallingTopLines(19, &game_paremeters_);
  status = IsFullLine (19, &game_paremeters_);
  ck_assert_int_eq(status, false);

  }
END_TEST



START_TEST(s21_File) {
 int current_score_ = 900;
  int current_level_ = 0;
  int current_speed_ = 500;
  int max_score_ = LEVEL_STEP; // сколько нужно для получения следующего уро
  int record_ = 60;
  // PlayerState_t *current_state_;
  board_struct show_board_ = {0};
  board_struct board_ = {0};

  Block_Type next_bloc = {0};
  Block_Property current_block_ = {0};
  // Game_State *state_;
  Game_State state = sStart;
  game_paremeters game_paremeters_ = {0};
  game_paremeters_.current_score_ = &current_score_;
  game_paremeters_.current_level_ = &current_level_;
  game_paremeters_.current_speed_ = &current_speed_;
  game_paremeters_.max_score_ = &max_score_;
  game_paremeters_.record_ = &record_;

  game_paremeters_.board_ = &board_;
  game_paremeters_.show_board_ = &show_board_;
  game_paremeters_.next_block_ = &next_bloc;
  game_paremeters_.current_block_ = &current_block_;
  InitializeFSM(&game_paremeters_);
  game_paremeters_.state_ = &state;
  SaveRecord(&game_paremeters_);
  LoadRecord(&game_paremeters_);
  ck_assert_int_eq(record_, 900);

  }
END_TEST

START_TEST(s21_UpdateScore) {
 int current_score_ = 0;
  int current_level_ = 0;
  int current_speed_ = 500;
  int max_score_ = LEVEL_STEP; // сколько нужно для получения следующего уро
  int record_ = 60;
  // PlayerState_t *current_state_;
  board_struct show_board_ = {0};
  board_struct board_ = {0};

  Block_Type next_bloc = {0};
  Block_Property current_block_ = {0};
  // Game_State *state_;
  Game_State state = sStart;
  game_paremeters game_paremeters_ = {0};
  game_paremeters_.current_score_ = &current_score_;
  game_paremeters_.current_level_ = &current_level_;
  game_paremeters_.current_speed_ = &current_speed_;
  game_paremeters_.max_score_ = &max_score_;
  game_paremeters_.record_ = &record_;

  game_paremeters_.board_ = &board_;
  game_paremeters_.show_board_ = &show_board_;
  game_paremeters_.next_block_ = &next_bloc;
  game_paremeters_.current_block_ = &current_block_;
  InitializeFSM(&game_paremeters_);
  game_paremeters_.state_ = &state;
  UpdateScore(3, &game_paremeters_);

  
  ck_assert_int_eq(current_score_, 700);

  UpdateLevel(&game_paremeters_);

  ck_assert_int_eq(current_level_, 2);
  }
END_TEST


Suite *lib_suite(void) {
  Suite *s;
  s = suite_create("Func Check");

  TCase *tc_ceil;

  tc_ceil = tcase_create("Ceil func");
  suite_add_tcase(s, tc_ceil);
  tcase_add_test(tc_ceil, s21_ceil_f);
  tcase_add_test(tc_ceil, s21_getSignal);
  tcase_add_test(tc_ceil, s21_UpdateSpeed);
  tcase_add_test(tc_ceil, s21_UpdateRecord);
  tcase_add_test(tc_ceil, s21_init_next_block);

  tcase_add_test(tc_ceil, s21_SetBoardToGameBoard);
  tcase_add_test(tc_ceil, s21_SetGameBoard);
  tcase_add_test(tc_ceil, s21_SetNewBlock);
  tcase_add_test(tc_ceil, s21_Initialize);
  tcase_add_test(tc_ceil, s21_userInput);
  tcase_add_test(tc_ceil, s21_CheckNextBlockState);
  tcase_add_test(tc_ceil, s21_IsEmptyLine);
  tcase_add_test(tc_ceil, s21_FallingTopLines);
  tcase_add_test(tc_ceil, s21_File);
  tcase_add_test(tc_ceil, s21_UpdateScore);

  return s;
}

int main(void) {
  Suite *s;
  SRunner *sr;

  s = lib_suite();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_VERBOSE);
  srunner_free(sr);
  return 0;
}
