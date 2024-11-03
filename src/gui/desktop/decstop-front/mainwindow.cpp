#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setFixedSize(400, 500);

    // Создаем кнопки для выбора игры
    QPushButton *buttonGame1 = new QPushButton("Snake", this);
    QPushButton *buttonGame2 = new QPushButton("Tetris", this);

    // Создаем виджеты для игр
    m_gameField1 = new GameField();
    m_gameField2 = new GameFieldTetris();
    m_helpField = new HelpField();

    // Создаем макет для кнопок
    QVBoxLayout *buttonLayout = new QVBoxLayout();
    buttonLayout->addWidget(buttonGame1);
    buttonLayout->addWidget(buttonGame2);

    // Создаем макет для игровых полей
    m_gridLayout = new QGridLayout();
    m_gridLayout->addWidget(m_gameField1, 0, 0);
    m_gridLayout->addWidget(m_helpField, 1, 0);
    m_gridLayout->addWidget(m_gameField2, 0, 0);
    m_gridLayout->addWidget(m_helpField, 1, 0);

    // Создаем центральный виджет и устанавливаем макет
    m_centralWidget = new QWidget();
    m_centralWidget->setLayout(m_gridLayout);

    // Создаем виджет для кнопок и добавляем его в центральный виджет
    QWidget *buttonWidget = new QWidget();
    buttonWidget->setLayout(buttonLayout);
    m_gridLayout->addWidget(buttonWidget, 2, 0);

    setCentralWidget(m_centralWidget);

    // Подключаем кнопки к слотам для переключения игр
    connect(buttonGame1, &QPushButton::clicked, this, &MainWindow::showGame1);
    connect(buttonGame2, &QPushButton::clicked, this, &MainWindow::showGame2);

    // По умолчанию показываем первую игру
    showGame1();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showGame1()
{
    m_gameField1->show();
    m_gameField2->hide();
}

void MainWindow::showGame2()
{
    m_gameField1->hide();
    m_gameField2->show();
}

GameField::GameField()
{
    controller = new s21::Controller();
    setFocusPolicy(Qt::StrongFocus);
    setFixedSize(300, 300);
    m_snakeItemSize = 10;

    m_moveSnakeTimer = new QTimer(this);
    connect(m_moveSnakeTimer, &QTimer::timeout, this, &GameField::MoveSnakeSlot);
    m_moveSnakeTimer->start(100); // Установите интервал таймера в миллисекундах
}

Game_State GameField::get_state()
{
    return state;
}

void GameField::keyPressEvent(QKeyEvent *e)
{
    int move;
    switch (e->key()) {
        case Qt::Key_Up:    move = KEY_UP; break;
        case Qt::Key_Down:  move = KEY_DOWN; break;
        case Qt::Key_Left:  move = KEY_LEFT; break;
        case Qt::Key_Right: move = KEY_RIGHT; break;
        case Qt::Key_Escape: move = KEY_ESCAPE; break;
        case Qt::Key_Enter: move = KEY_START; break;
        case Qt::Key_P: move = 'p'; break;
        case Qt::Key_Space: move = KEY_SPACE; break;
        default: move = KEY_SPACE;
    }
    state = controller->userInput(move);
    repaint();
}

void GameField::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QBrush gameFieldBrush(QColor(100,100,100), Qt::SolidPattern);
    QBrush SnakeBrush(QColor(0,225,0), Qt::SolidPattern);
    QBrush foodFieldBrush(QColor(225,0,0), Qt::SolidPattern);
    QPainter painter(this);
    painter.drawRect(0, 0, width() - 1, height() - 1);
    if (state == sStart) {
        painter.setFont(QFont("Arial", 10, 700));
        painter.drawText(QRect(0, 0, width(), height()), Qt::AlignCenter, "для начала змейки нажмите Enter");
    } else if (state == sPause) {
        painter.setFont(QFont("Arial", 10, 700));
        painter.drawText(QRect(0, 0, width(), height()), Qt::AlignCenter, "игра на паузе");
    } else {
        for (int i = 0; i < 22; i++) {
            for (int j = 0; j < 12; j++) {
                int block = controller->getSnakeArray(i, j);
                if (block == 1) { // snake
                    painter.setBrush(SnakeBrush);
                    painter.drawEllipse(j * m_snakeItemSize, i * m_snakeItemSize, m_snakeItemSize, m_snakeItemSize);
                } else if (block == 2) { // food
                    painter.setBrush(foodFieldBrush);
                    painter.drawEllipse(j * m_snakeItemSize, i * m_snakeItemSize, m_snakeItemSize, m_snakeItemSize);
                } else if (block == 3) { // border
                    painter.setBrush(gameFieldBrush);
                    painter.drawRect(j * m_snakeItemSize, i * m_snakeItemSize, m_snakeItemSize, m_snakeItemSize);
                }
            }
        }

    }
    painter.drawText(QRect(1, -140, width(), height()), Qt::AlignCenter, "record: ");
    painter.drawText(QRect(50, -140, width(), height()), Qt::AlignCenter, QString::number(controller->Get_record()));
    painter.drawText(QRect(1, -125, width(), height()), Qt::AlignCenter, "score: ");
    painter.drawText(QRect(50, -125, width(), height()), Qt::AlignCenter, QString::number(controller->Get_score()));
    painter.drawText(QRect(50, -110, width(), height()), Qt::AlignCenter, QString::number(controller->Get_level()));
    painter.drawText(QRect(1, -110, width(), height()), Qt::AlignCenter, "level: ");
}

void GameField::MoveSnakeSlot()
{
    state = controller->userInput(KEY_SPACE);
    repaint();
    if (state == sExitGame) {
        QApplication::quit();
    }
}

GameFieldTetris::GameFieldTetris()
{
    setFocusPolicy(Qt::StrongFocus);
    setFixedSize(300, 300);
    m_itemSize = 10;


      // PlayerState_t *current_state_;
       record_ = GetRecord() ;
      game_paremeters_.current_score_ = &current_score_;
      game_paremeters_.current_level_ = &current_level_;
      game_paremeters_.current_speed_ = &current_speed_;
      game_paremeters_.max_score_ = &max_score_;
      game_paremeters_.record_ = &record_;
      game_paremeters_.show_board_ = &show_board_;
      game_paremeters_.board_ = &board_;
      game_paremeters_.next_block_ = &next_bloc;
      game_paremeters_.current_block_ = &current_block_;

      game_paremeters_.state_ = &state;
      InitializeFSM(&game_paremeters_);
      InitializeParameters(&game_paremeters_);



      m_moveTetrisTimer = new QTimer(this);
      connect(m_moveTetrisTimer, &QTimer::timeout, this, &GameFieldTetris::MoveTetrisSlot);
      m_moveTetrisTimer->start(*game_paremeters_.current_speed_); // Установите интервал таймера в миллисекундах


}


void GameFieldTetris::keyPressEvent(QKeyEvent *e)
{
    int move;
    switch (e->key()) {
        case Qt::Key_Up:    move = KEY_UP; break;
        case Qt::Key_Down:  move = KEY_DOWN; break;
        case Qt::Key_Left:  move = KEY_LEFT; break;
        case Qt::Key_Right: move = KEY_RIGHT; break;
        case Qt::Key_Escape: move = KEY_ESCAPE; break;
        case Qt::Key_Enter: move = KEY_START; break;
        case Qt::Key_P: move = 'p'; break;
        case Qt::Key_Space: move = KEY_SPACE; break;
        default: move = KEY_SPACE;
    }
    UserAction_t  user_action_ = GetSignal(move);
    userInput(user_action_, &game_paremeters_);
    repaint();
}



void GameFieldTetris::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
//    QBrush gameFieldBrush(QColor(100,100,100), Qt::SolidPattern);
    QBrush BlockBrush(QColor(0,225,0), Qt::SolidPattern);
//    QBrush foodFieldBrush(QColor(225,0,0), Qt::SolidPattern);
    QPainter painter(this);
    painter.drawRect(0, 0, width() - 1, height() - 1);
    if (*game_paremeters_.state_ == sStart) {
        painter.setFont(QFont("Arial", 10, 700));
        painter.drawText(QRect(0, 0, width(), height()), Qt::AlignCenter, "для начала Тетриса нажмите Enter");
    } else if (*game_paremeters_.state_ == sPause) {
        painter.setFont(QFont("Arial", 10, 700));
        painter.drawText(QRect(0, 0, width(), height()), Qt::AlignCenter, "игра на паузе");
    } else {
        for (int i = 0; i < BOARD_HEIGHT; i++) {
            for (int j = 0; j < BOARD_WIDTH; j++) {
                painter.setBrush(BlockBrush);
                if(j == 0){

                   painter.drawRect(j * m_itemSize, (i+1) * m_itemSize, m_itemSize, m_itemSize);
                }
                if (i == 0 ){
                   painter.drawRect((j+1) * m_itemSize, i * m_itemSize, m_itemSize, m_itemSize);
                }
                if (i == BOARD_HEIGHT-1 )
                {

                   painter.drawRect((j+1) * m_itemSize, (i+1) * m_itemSize, m_itemSize, m_itemSize);
                }
                if (j == BOARD_WIDTH-1){
                    painter.drawRect((j+2) * m_itemSize, (i+1) * m_itemSize, m_itemSize, m_itemSize);
                }
                int block = game_paremeters_.show_board_->square_[i][j];
                if (block != 0) {
                     painter.setBrush(BlockBrush);
                    painter.drawRect((j+1) * m_itemSize, (i) * m_itemSize, m_itemSize, m_itemSize);
                } /*else {
                    painter.drawRect(j * m_itemSize, i * m_itemSize, m_itemSize, m_itemSize);
                }*/
            }
        }
        int bit_mask_ = block_collection_[*game_paremeters_.next_block_][0];

        for (int i = 0; i < NUM_BLOCK_PARAM; i++){
            for (int j = 0; j < NUM_BLOCK_PARAM; j++){
                if((bit_mask_ & (1 << (i * 4 + j)))){
                   painter.drawRect((j+13) * m_itemSize, (i+7) * m_itemSize, m_itemSize, m_itemSize);
                }
            }
        }
    }
    painter.drawText(QRect(1, -140, width(), height()), Qt::AlignCenter, "record: ");
    painter.drawText(QRect(50, -140, width(), height()), Qt::AlignCenter, QString::number(*(game_paremeters_.record_)));
    painter.drawText(QRect(1, -125, width(), height()), Qt::AlignCenter, "score: ");
    painter.drawText(QRect(50, -125, width(), height()), Qt::AlignCenter, QString::number(*(game_paremeters_.current_score_)));
    painter.drawText(QRect(50, -110, width(), height()), Qt::AlignCenter, QString::number(*(game_paremeters_.current_level_)));
    painter.drawText(QRect(1, -110, width(), height()), Qt::AlignCenter, "level: ");
    painter.drawText(QRect(10, -95, width(), height()), Qt::AlignCenter, "next block: ");
}

void GameFieldTetris::MoveTetrisSlot()
{
    userInput(Down, &game_paremeters_);
    repaint();
    if (*(game_paremeters_.state_) == sExitGame) {
        QApplication::quit();
    }
}
