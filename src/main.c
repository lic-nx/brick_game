
#include "consts.h"
#include "brick_game/tetris/structs.h"
#include "gui/cli/front.h"

#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

int start_game(game_paremeters *game_paremeters_);
int tetris_game();

int main() {
  
  tetris_game();
  return 0;
}


int tetris_game(){
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

  game_paremeters_.state_ = &state;
  InitializeFSM(&game_paremeters_);
  start_game(&game_paremeters_);
  return 0;
}


int start_game(game_paremeters *game_paremeters_) {
  srand(time(NULL));
  initscr();
  keypad(stdscr, true);
  nodelay(stdscr, true);
  // mvprintw(10, 2, "chouse game: !");
  // mvprintw(11, 2, "t - tetris, s - snake"); // предлагаем ввести человеку в
                                            // какую игру хочет сыграть
  int key = 0;
  UserAction_t user_action_ = 0;
  struct timeval last_update_time_, current_time_;
  gettimeofday(&last_update_time_, NULL);
  while (*game_paremeters_->state_ != sExitGame) {
    PrintGameTetris(game_paremeters_);
    key = getch();
    if (key != EOF) {
      user_action_ = GetSignal(key);
      userInput(user_action_, game_paremeters_);
    }
    if (TimerAction(&last_update_time_,
                    &current_time_, // делает игру более играбельной
                    *game_paremeters_
                         ->current_speed_)) // ну проверяет можно ли опускать
      userInput(Down, game_paremeters_);
    if (key == 'e') {
      break;
    }
    // refresh();

    // usleep(100000);
    // getchar();
  };
  endwin();
  return 0;
}