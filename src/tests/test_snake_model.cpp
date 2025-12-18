#include <gtest/gtest.h>

#include "../brick_game/snake/model/snake_model.h"

namespace s21 {

class SnakeModelTest : public ::testing::Test {
 protected:
  SnakeModel model;
};

// Проверка начального состояния
TEST_F(SnakeModelTest, InitialState) {
  EXPECT_EQ(model.GetDirection(), DOWN);
  EXPECT_FALSE(model.IsGameOver());
  EXPECT_FALSE(model.IsPause());
  EXPECT_FALSE(model.IsWin());
  EXPECT_TRUE(model.IsStartScreen());
  EXPECT_EQ(model.GetScore(), 0);
  EXPECT_EQ(model.GetLevel(), 1);
  EXPECT_EQ(model.GetDelay(), SPEED_DELAY);
  EXPECT_EQ(model.GetSnake().size(), 4);
}

// Проверка движения вправо
TEST_F(SnakeModelTest, MoveRight) {
  model.SetDirection(RIGHT);
  auto old_head = model.GetSnake().front();
  model.Move();
  auto new_head = model.GetSnake().front();

  EXPECT_EQ(new_head.first, old_head.first);
  EXPECT_EQ(new_head.second, old_head.second + 1);
}

// Проверка поедания еды
TEST_F(SnakeModelTest, EatFoodIncreasesScore) {
  model.PlaceFoodInFront();  // Еда перед головой
  model.Move();

  EXPECT_EQ(model.GetScore(), SCORE);
  EXPECT_EQ(model.GetSnake().size(), 5);
}

// Столкновение со стеной
TEST_F(SnakeModelTest, CollisionWithWallEndsGame) {
  model.SetDirection(UP);
  for (int i = 0; i < HEIGHT * 2 && !model.IsGameOver(); ++i) {
    model.Move();
  }
  EXPECT_TRUE(model.IsGameOver());
  EXPECT_FALSE(model.IsWin());
}

// Проверка паузы
TEST_F(SnakeModelTest, TogglePause) {
  model.TogglePause();
  EXPECT_TRUE(model.IsPause());

  model.TogglePause();
  EXPECT_FALSE(model.IsPause());
}

// Ускорение
TEST_F(SnakeModelTest, BoostSpeed) {
  model.SetBoost(true);
  EXPECT_LT(model.GetDelay(), SPEED_DELAY);
  model.SetBoost(false);
  EXPECT_EQ(model.GetDelay(), SPEED_DELAY);
}

// Обновление уровня
TEST_F(SnakeModelTest, UpdateLevelIncreasesLevel) {
  int initial_level = model.GetLevel();
  model.FeedSnake(5);  // Съесть 5 еды

  EXPECT_GT(model.GetLevel(), initial_level);
  EXPECT_LT(model.GetDelay(), SPEED_DELAY);
}

// Сброс игры
TEST_F(SnakeModelTest, ResetGame) {
  model.FeedSnake(10);
  model.Reset();

  EXPECT_EQ(model.GetScore(), 0);
  EXPECT_EQ(model.GetLevel(), 1);
  EXPECT_FALSE(model.IsGameOver());
  EXPECT_FALSE(model.IsPause());
  EXPECT_EQ(model.GetSnake().size(), 4);
}

}  // namespace s21
