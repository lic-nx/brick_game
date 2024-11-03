
#include <gtest/gtest.h>

#include "../brick_game/snake/game.h"
#include "../brick_game/snake/classes.h"
#include "../brick_game/snake/controller.h"

TEST(mull, GenerateBlock) {
  // TestS21Matrix A, B;
  s21::Block A;
  ASSERT_EQ(5, A.get_x());
  ASSERT_EQ(10, A.get_y());
  
}

TEST(mull, GenerateBlock2) {
  // TestS21Matrix A, B;
  s21::Block A(13, 10);
  ASSERT_EQ(3, A.get_x());
  ASSERT_EQ(10, A.get_y());
  
}

// TEST(mull, EqualBlock) {
//   // TestS21Matrix A, B;
//   s21::Block A(5, 10);
//   s21::Block B;
//   ASSERT_EQ(true, A == B);
//   ASSERT_EQ(true, B == A);
//   B.change_x_(4);
//   B.change_y_(-5);
//   ASSERT_EQ(9, B.x_);
//   ASSERT_EQ(5, B.y_);
//   ASSERT_EQ(false, B == A);
  
// }

TEST(mull, EqualBlock) {
  // TestS21Matrix A, B;
  s21::Block A(15, 10);
  s21::Block B;
  ASSERT_EQ(true, A == B);
  ASSERT_EQ(true, B == A);
  B.change_x_(4);
  B.change_y_(-5);
  ASSERT_EQ(9, B.get_x());
  ASSERT_EQ(5, B.get_y());
  ASSERT_EQ(false, B == A);
}

TEST(mull, IsOutBoard) {
  // TestS21Matrix A, B;
  s21::Block A(0, 10);
  ASSERT_EQ(false, A.isOutBorders());
  A.change_x_(-4);
  ASSERT_EQ(true, A.isOutBorders());
  
}


TEST(mull, Random) {
  // TestS21Matrix A, B;
  s21::Block block;
    block.RandomPlase();
    EXPECT_FALSE(block.isOutBorders());  
}

TEST(game_score, loadTopScore) {
    // Создание файла и запись в него значения
    std::ofstream file(RECORD_FILE_SNAKE_NAME);
    if (!file) {
        throw std::runtime_error("Unable to open file for writing");
    }
    file << 1;
    file.close();

    s21::GameScore block;
    block.loadTopScore();
    int score = block.getTopScore();
    ASSERT_EQ(1, score);
    score = block.getCurrentScore();
    ASSERT_EQ(0, score);
    block.increase();
    block.increase();
    score = block.getCurrentScore();
    ASSERT_EQ(2, score);
     block.saveTopScore();
     score = block.getTopScore();
    ASSERT_EQ(2, score);
    block.reset();
    score = block.getCurrentScore();
    ASSERT_EQ(0, score);

}


TEST(Snake, Initialithe) {
    // Создание файла и запись в него значени
    s21::Snake snake;
    int lenth = snake.getLength();
    ASSERT_EQ(4, lenth);
    snake.setSide();
    bool mover = snake.isOpposite( UserAction_t::Down );
    ASSERT_EQ(true, mover);
    snake.Move(Up);
    int x = snake.snake_body_.front().get_x();
    int y = snake.snake_body_.front().get_y();
    ASSERT_EQ(5, x);
    ASSERT_EQ(9, y);

    snake.Move(Left);
    x = snake.snake_body_.front().get_x();
    y = snake.snake_body_.front().get_y();
    ASSERT_EQ(4, x);
    ASSERT_EQ(9, y);

    snake.Move(Down);
    x = snake.snake_body_.front().get_x();
    y = snake.snake_body_.front().get_y();
    ASSERT_EQ(4, x);
    ASSERT_EQ(10, y);
    snake.Move(Right);
    x = snake.snake_body_.front().get_x();
    y = snake.snake_body_.front().get_y();
    ASSERT_EQ(5, x);
    ASSERT_EQ(10, y);
}
TEST(Snake, grow) {
    // Создание файла и запись в него значени
    s21::Snake snake;
    int lenth = snake.getLength();
    ASSERT_EQ(4, lenth);
    snake.grow();
    lenth = snake.getLength();
    ASSERT_EQ(5, lenth);
    bool checker = snake.CheckCollisionBodyOrBorder();
    ASSERT_EQ(false, checker);
    snake.generateNewMeal();
    int x = snake.meal_.get_x();
    int y = snake.meal_.get_y();
    EXPECT_GE(x, 0);
    EXPECT_LT(x, BOARD_WIDTH);
    EXPECT_GE(y, 0);
    EXPECT_LT(y, BOARD_HEIGHT);
}

TEST(Snake, checker) {
    // Создание файла и запись в него значени
    s21::Snake snake;
    int lenth = snake.getLength();
    ASSERT_EQ(4, lenth);
    bool checker = snake.CheckCollisionHeadAndMeal();
    ASSERT_EQ(false, checker);
}

TEST(SnakeGame, init) {
    s21::SnakeGame game;

    EXPECT_NE(game.snake_, nullptr);
    EXPECT_EQ(game.get_game_state(), Game_State::sStart);
    EXPECT_EQ(game.getLevel(), 0);
    EXPECT_EQ(game.getSpeed(), 500);
    EXPECT_EQ(game.getScore(), 0);
    EXPECT_EQ(game.getRecord(), 2);
}

TEST(SnakeGame, fsm) {
    s21::SnakeGame game;
    game.setGame_state_(sStart);
    game.userAction(Start);
    Game_State state = game.get_game_state();
    EXPECT_EQ(state, sMoving);
    game.userAction(Pause);
    state = game.get_game_state();
    EXPECT_EQ(state, sPause);
    game.userAction(Pause);
    state = game.get_game_state();
    EXPECT_EQ(state, sMoving);
    game.userAction(Left);
    state = game.get_game_state();
    EXPECT_EQ(state, sMoving);
    game.userAction(Down);
    state = game.get_game_state();
    EXPECT_EQ(state, sMoving);
    game.userAction(Right);
    state = game.get_game_state();
    EXPECT_EQ(state, sMoving);
    game.userAction(Up);
    state = game.get_game_state();
    EXPECT_EQ(state, sMoving);
    game.userAction(Terminate);
    state = game.get_game_state();
    EXPECT_EQ(state, sExitGame);

    game.setGame_state_(sStart);
    game.userAction(Terminate);
    state = game.get_game_state();
    EXPECT_EQ(state, sExitGame);

    game.setGame_state_(sPause);
    game.userAction(Terminate);
    state = game.get_game_state();
    EXPECT_EQ(state, sExitGame);

    game.setGame_state_(sGameOver);
    game.userAction(Start);
    state = game.get_game_state();
    EXPECT_EQ(state, sMoving);

     game.setGame_state_(sGameOver);
    game.userAction(Terminate);
    state = game.get_game_state();
    EXPECT_EQ(state, sExitGame);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}