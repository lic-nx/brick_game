#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QWidget>
#include <QMainWindow>
#include <QPainter>
#include <QTimer>
#include "../../../brick_game/snake/classes.h"
#include "../../../consts.h"
#include "../../../brick_game/snake/controller.h"
#include "../../../brick_game/snake/game.h"
#include "helpfield.h"
#include <QGridLayout>
#include "QKeyEvent"
extern "C" {
#include "../../../brick_game/tetris/back.h"
#include "../../../consts.h"
#include "../../../brick_game/tetris/fsm.h"
#include "../../../brick_game/tetris/structs.h"
}
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class GameFieldTetris: public QWidget{
    Q_OBJECT
   public:
    GameFieldTetris();
    game_paremeters game_paremeters_;


protected:
    void paintEvent(QPaintEvent *e) override;
    int m_itemSize;
private:
//    Game_State state;
    QTimer *m_moveTetrisTimer;
    void keyPressEvent(QKeyEvent *e) override;
    int current_score_ = 0;
    int current_level_ = 0;
    int current_speed_ = 500;
    int max_score_ = LEVEL_STEP; // сколько нужно для получения следующего уро
    int record_;
    board_struct board_;
    board_struct show_board_;
//      board_struct board_ = {{0}};
    Block_Type next_bloc = NUM_BLOCK_TYPES;
    Block_Property current_block_ = {0,0,NUM_BLOCK_TYPES,0};
    Game_State state = sStart;
private slots:
    void MoveTetrisSlot();

};

class GameField : public QWidget{
    Q_OBJECT
   public:
    GameField();

    s21::Controller *controller;
    Game_State get_state();
protected:
    void paintEvent(QPaintEvent *e) override;
private:
    Game_State state;
    QTimer *m_moveSnakeTimer;
    int m_snakeItemSize;
    void keyPressEvent(QKeyEvent *e) override;
private slots:
    void MoveSnakeSlot();
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void showGame1();
    void showGame2();
    GameField *m_gameField1;// class for show
    GameFieldTetris *m_gameField2;
    HelpField *m_helpField;
    QWidget *m_centralWidget;
    QGridLayout *m_gridLayout;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
