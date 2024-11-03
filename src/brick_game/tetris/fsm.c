#include "fsm.h"

// инициализация автомата
void InitializeFSM(struct game_paremeters *game_paremeters_) {
  for (int i = 0; i < NUM_STATES; i++) {
    for (int j = 0; j < NUM_ACTIONS; j++) {
      game_paremeters_->fsm[i][j] = NULL;
    };
  };
  game_paremeters_->fsm[sStart][Start] = Action__Start_Start;
  game_paremeters_->fsm[sStart][Terminate] = Event__Start_Exit;
  for (int i = 0; i < NUM_ACTIONS; i++) {
    game_paremeters_->fsm[sSpawn][i] = Event__Spawn_Enter;
  }
  // fsm[sStart][sSpawn] = Event__Spawn_Enter;
  game_paremeters_->fsm[sPause][Pause] = Action__Pause_Pause;
  game_paremeters_->fsm[sPause][Terminate] = Action__Pause_Terminate;
  game_paremeters_->fsm[sMoving][Pause] = Action__Moving_Pause;
  game_paremeters_->fsm[sMoving][Terminate] = Action__Moving_Terminate;
  // fsm[sMoving][Pause] = Action__Moving_Pause;
  game_paremeters_->fsm[sMoving][Left] = Action__Moving_Left;
  game_paremeters_->fsm[sMoving][Right] = Action__Moving_Right;
  game_paremeters_->fsm[sMoving][Down] = Action__Moving_Down;
  game_paremeters_->fsm[sMoving][Action] = Action__Moving_Action;
  game_paremeters_->fsm[sGameOver][Start] = Action__sGameOver_Start;
  game_paremeters_->fsm[sGameOver][Terminate] = Event__sExitGame_Enter;
}

/// @brief переход к заданному состоянию (последовательно: вызов события выхода
/// из текущего состояния, переход и вызов события входа в новое состояние)
/// @param parameters_  текущие параметры
/// @param new_state_  новое состояние
/// tested
void TransitionToNewState(game_paremeters *parameters_, Game_State new_state_) {
  //запуск события выхода из текущего состояния
  *(parameters_->state_) = new_state_;
};

//обработка сигналов

/// @brief обработка действия Старт для состояния Старт
/// @param parameters_ текущие параметры
// tested
void Action__Start_Start(game_paremeters *parameters_) {
  LoadRecord(parameters_);
  InitializeParameters(parameters_);
  TransitionToNewState(parameters_, sSpawn);
};

/// @brief обработка действия Выход для состояния Старт
/// @param parameters_ текущие параметры
//void Action__Start_Terminate(game_paremeters *parameters_) {
  //SaveRecord(parameters_);

  //TransitionToNewState(parameters_, sExitGame);
//};

/// @brief обработка действия Пауза для состояния Пауза
/// @param parameters_ текущие параметры
/// tested
void Action__Pause_Pause(game_paremeters *parameters_) {
  TransitionToNewState(parameters_, sMoving);
};

/// @brief обработка действия Выход для состояния Пауза
/// @param parameters_ текущие параметры
void Action__Pause_Terminate(game_paremeters *parameters_) {
  SaveRecord(parameters_);
  TransitionToNewState(parameters_, sExitGame);
};

/// @brief обработка действия Выход для состояния Движение
/// @param parameters_ текущие параметры
/// testing
void Action__Moving_Terminate(game_paremeters *parameters_) {
  SaveRecord(parameters_);
  TransitionToNewState(parameters_, sExitGame);
};

/// @brief обработка действия Влево для состояния Движение
/// @param parameters_ текущие параметры
/// testing
void Action__Moving_Left(game_paremeters *parameters_) {
  if (CheckNextBlockState(parameters_, -1, 0, 0) == false)
    SetNextBlockStat(parameters_, -1, 0, 0);
};

/// @brief обработка действия Вправо для состояния Движение
/// @param parameters_ текущие параметры
/// testing
void Action__Moving_Right(game_paremeters *parameters_) {
  if (CheckNextBlockState(parameters_, +1, 0, 0) == false)
    SetNextBlockStat(parameters_, +1, 0, 0);
};

/// @brief обработка действия Вниз для состояния Движение
/// @param parameters_ текущие параметры
void Action__Moving_Down(game_paremeters *parameters_) {
  if (CheckNextBlockState(parameters_, 0, +1, 0) == false)
    SetNextBlockStat(parameters_, 0, +1, 0);
  else
    Event__Attaching_Enter(parameters_);
};

/// @brief обработка действия Действие для состояния Движение
/// @param parameters_ текущие параметры
// tested
void Action__Moving_Action(game_paremeters *parameters_) {
  if (CheckNextBlockState(parameters_, 0, 0, +1) == false)
    SetNextBlockStat(parameters_, 0, 0, +1);
};

/// @brief обработка действия Пауза для состояния Движение
/// @param parameters_ текущие параметры
void Action__Moving_Pause(game_paremeters *parameters_) {
  TransitionToNewState(parameters_, sPause);
};

/// @brief обработка действия Старт для состояния КонецИгры
/// @param parameters_ текущие параметры
void Action__sGameOver_Start(game_paremeters *parameters_) {
  SaveRecord(parameters_);
  LoadRecord(parameters_);
  InitializeParameters(parameters_);

  TransitionToNewState(parameters_, sSpawn);
};



//обработка событий
/// @brief обработка события Выход для состояния Старт
/// @param parameters_ текущие параметры
void Event__Start_Exit(game_paremeters *parameters_) {
  LoadRecord(parameters_);
  InitializeParameters(parameters_);
};

/// @brief обработка события Вход для состояния Спаун
/// @param parameters_ текущие параметры
void Event__Spawn_Enter(game_paremeters *parameters_) {
  SetNewBlock(parameters_);
  if (CheckNextBlockState(parameters_, 0, 0, 0) == false)
    TransitionToNewState(parameters_, sMoving);
  else
    TransitionToNewState(parameters_, sGameOver);
};

/// @brief обработка события Вход для состояния Выход
/// @param parameters_ текущие параметры
/// tested
void Event__sExitGame_Enter(game_paremeters *parameters_) {
  SaveRecord(parameters_);
  TransitionToNewState(parameters_, sExitGame);
};

/// @brief обработка события Вход для состояния Присоединение
/// @param parameters_ текущие параметры
void Event__Attaching_Enter(game_paremeters *game_paremeters) {
  SetBlockToGameBoard(game_paremeters->board_->square_, game_paremeters);
  CollapseLines(game_paremeters);
  TransitionToNewState(game_paremeters, sSpawn);
};
