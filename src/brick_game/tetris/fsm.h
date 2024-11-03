#ifndef BRICK_GAME_TETRIS_TETRIS_FSM
#define BRICK_GAME_TETRIS_TETRIS_FSM

#include <ncurses.h>
#include <stdbool.h>

#include "../../consts.h"
#include "back.h"
#include "structs.h"

void InitializeFSM(game_paremeters *game_paremeters_);
void Action__Start_Start(game_paremeters *game_paremeters_);
void Action__Start_Terminate(game_paremeters *game_paremeters_);
void Action__Pause_Pause(game_paremeters *game_paremeters_);
void Action__Pause_Terminate(game_paremeters *game_paremeters_);
void Action__Moving_Terminate(game_paremeters *game_paremeters_);
void Action__Moving_Left(game_paremeters *game_paremeters_);
void Action__Moving_Right(game_paremeters *game_paremeters_);
void Action__Moving_Down(game_paremeters *game_paremeters_);
void Action__Moving_Action(game_paremeters *game_paremeters_);
void Action__Moving_Pause(game_paremeters *game_paremeters_);
void Action__sGameOver_Start(game_paremeters *game_paremeters_);
void Action__sGameOver_Terminate(game_paremeters *game_paremeters_);
void Event__Start_Exit(game_paremeters *game_paremeters_);
void Event__Spawn_Enter(game_paremeters *game_paremeters_);
void Event__sExitGame_Enter(game_paremeters *game_paremeters_);
void Event__Attaching_Enter(game_paremeters *game_paremeters_);

#endif  // BRICK_GAME_TETRIS_TETRIS_FSM