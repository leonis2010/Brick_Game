#include <gtest/gtest.h>

#include "../brick_game/snake/cli_controller/snake_controller.h"
#include "../brick_game/snake/model/snake_model.h"
#include "../gui/cli/snake/snake_view.h"

namespace s21 {

class SnakeControllerTest : public ::testing::Test {
 protected:
  SnakeModel model_;
  class MockSnakeView : public SnakeView {
   public:
    MockSnakeView() : SnakeView(nullptr, nullptr, nullptr, nullptr) {}
  };
  MockSnakeView view_;
  SnakeController controller_{model_, view_};
};

// Проверяем, что контроллер корректно инициализируется
TEST_F(SnakeControllerTest, ConstructorWorks) {
  EXPECT_FALSE(controller_.IsGameOver());
}

// ESC переключает паузу
TEST_F(SnakeControllerTest, EscapeTogglesPause) {
  // Пауза выключена изначально
  EXPECT_FALSE(model_.IsPause());

  controller_.HandleInput(27);  // ESC
  EXPECT_TRUE(model_.IsPause());

  controller_.HandleInput(27);  // ESC снова
  EXPECT_FALSE(model_.IsPause());
}

// Стрелка вверх меняет направление
TEST_F(SnakeControllerTest, DirectionChangeNotAllowed_up) {
  model_.SetDirection(Direction::DOWN);
  controller_.HandleInput(KEY_UP);
  EXPECT_EQ(model_.GetDirection(), Direction::DOWN);
}

// Стрелка вниз не может быть изменена на противоположную (UP -> DOWN)
TEST_F(SnakeControllerTest, DirectionChangeNotAllowed_down) {
  model_.SetDirection(Direction::UP);
  controller_.HandleInput(KEY_DOWN);  // Направление вниз — запрещено
  EXPECT_EQ(model_.GetDirection(), Direction::UP);  // Не должно поменяться
}

TEST_F(SnakeControllerTest, DirectionChangeNotAllowed_right) {
  model_.SetDirection(Direction::RIGHT);
  controller_.HandleInput(KEY_LEFT);
  EXPECT_EQ(model_.GetDirection(), Direction::RIGHT);  // Не должно поменяться
}

TEST_F(SnakeControllerTest, DirectionChangeNotAllowed_left) {
  model_.SetDirection(Direction::LEFT);
  controller_.HandleInput(KEY_RIGHT);
  EXPECT_EQ(model_.GetDirection(), Direction::LEFT);  // Не должно поменяться
}

// Пробел активирует буст
TEST_F(SnakeControllerTest, SpaceActivatesBoost) {
  controller_.HandleInput(' ');
  EXPECT_TRUE(model_.GetBoost());
}

// Буст деактивируется, если клавиша отпущена
TEST_F(SnakeControllerTest, BoostTurnsOffWhenReleased) {
  model_.SetBoost(true);
  controller_.checkingBoost();
  EXPECT_FALSE(model_.GetBoost());
}

// Клавиши 'q' и 'Q' завершают игру
TEST_F(SnakeControllerTest, QuitGameWithQ) {
  controller_.HandleInput('q');
  EXPECT_TRUE(model_.IsGameOver());

  model_.SetGameOver(false);

  controller_.HandleInput('Q');
  EXPECT_TRUE(model_.IsGameOver());
}

// Обновление вызывает движение змейки
TEST_F(SnakeControllerTest, UpdateMovesSnake) {
  auto snake_before = model_.GetSnake();
  controller_.Update();
  auto snake_after = model_.GetSnake();

  if (!model_.IsGameOver()) {
    EXPECT_NE(snake_before.front(), snake_after.front());
  }
}
TEST_F(SnakeControllerTest, waiting_Enter) {}
}  // namespace s21