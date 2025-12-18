#include <gtest/gtest.h>

#include <cstdlib>
#include <filesystem>
#include <fstream>
extern "C" {
#include "../brick_game/tetris/model/s21_tetris_cli.h"
}

namespace fs = std::filesystem;

class TetrisTest : public ::testing::Test {
 protected:
  void SetUp() override {
    // Создаем временную директорию для тестов
    temp_dir = fs::temp_directory_path() / "tetris_test";
    fs::create_directory(temp_dir);

    // Устанавливаем HOME во временную директорию
    old_home = getenv("HOME");
    setenv("HOME", temp_dir.c_str(), 1);
  }

  void TearDown() override {
    // Восстанавливаем HOME
    setenv("HOME", old_home.c_str(), 1);

    // Удаляем временную директорию
    fs::remove_all(temp_dir);
  }

  fs::path temp_dir;
  std::string old_home;
};

TEST_F(TetrisTest, test_counting_score_and_level_1_line) {
  Tetris_Game game;
  game.score = 0;
  game.level = 1;
  counting_score_and_level(&game, 1);
  EXPECT_EQ(game.score, 100);
  EXPECT_EQ(game.level, 1);
}

TEST_F(TetrisTest, test_counting_score_and_level_2_lines) {
  Tetris_Game game;
  game.score = 0;
  game.level = 1;
  counting_score_and_level(&game, 2);
  EXPECT_EQ(game.score, 300);
  EXPECT_EQ(game.level, 1);
}
TEST_F(TetrisTest, test_counting_score_and_level_3_lines) {
  Tetris_Game game;
  game.score = 0;
  game.level = 1;
  counting_score_and_level(&game, 3);
  EXPECT_EQ(game.score, 700);
  EXPECT_EQ(game.level, 2);
}
TEST_F(TetrisTest, test_counting_score_and_level_4_lines) {
  Tetris_Game game;
  game.score = 0;
  game.level = 1;
  counting_score_and_level(&game, 4);
  EXPECT_EQ(game.score, 1500);
  EXPECT_EQ(game.level, 3);
}

TEST_F(TetrisTest, test_counting_score_and_level_max_level) {
  Tetris_Game game;
  game.score = 6000;  // Уровень на границе
  game.level = 10;
  counting_score_and_level(&game, 4);
  EXPECT_EQ(game.score, 6000 + 1500);
  // уровень не должен измениться, т.к. 10 - максимальный
  EXPECT_EQ(game.level, 10);
}

TEST_F(TetrisTest, test_load_high_score) {
  // Создаем временный файл с известным рекордом
  char filename[256];
  snprintf(filename, sizeof(filename), "%s/bin/%s", getenv("HOME"),
           HIGH_SCORE_FILENAME);
  // Создаем директорию, если она не существует
  char dir[256];
  snprintf(dir, sizeof(dir), "%s/bin", getenv("HOME"));
  mkdir(dir, 0777);
  // Записываем рекорд в файл
  FILE *file = fopen(filename, "w");
  ASSERT_NE(file, nullptr);
  fprintf(file, "12345");
  fclose(file);
  // Вызываем функцию load_high_score
  int high_score = load_high_score(1);
  // Проверяем, что функция вернула ожидаемый рекорд
  EXPECT_EQ(high_score, 12345);
  remove(filename);
}

TEST_F(TetrisTest, test_load_high_score_file_not_found) {
  // Сохраняем текущую переменную окружения и устанавливаем новую
  char *old_home = getenv("HOME");
  setenv("HOME", "/non_existent_dir", 1);
  int high_score = load_high_score(1);
  // Восстанавливаем переменную окружения
  setenv("HOME", old_home, 1);
  // Проверяем, что функция вернула 0, так как файл не найден
  EXPECT_EQ(high_score, 0);
}

TEST_F(TetrisTest, test_print_high_score) {
  int field_width = 10;
  int field_height = 20;
  int figures_size = 4;
  int number_of_figures = 7;
  Tetris_Game *tetris_game =
      create_memory_game(field_width, field_height, figures_size,
                         number_of_figures, figures_template);
  // Устанавливаем начальные значения
  tetris_game->score = 500;
  tetris_game->high_score = 300;
  // Вызываем функцию print_high_score
  print_high_score(tetris_game);
  // Проверяем, что рекорд был обновлен
  EXPECT_EQ(tetris_game->high_score, 500);
  // Устанавливаем счет меньше рекорда
  tetris_game->score = 200;
  // Вызываем функцию print_high_score
  print_high_score(tetris_game);
  // Проверяем, что рекорд не изменился
  EXPECT_EQ(tetris_game->high_score, 500);
  free_memory_game(tetris_game);
}

TEST_F(TetrisTest, test_save_high_score) {
  // Создаем временный файл с известным рекордом
  char filename[256];
  snprintf(filename, sizeof(filename), "%s/bin/%s", getenv("HOME"),
           HIGH_SCORE_FILENAME);

  // Создаем директорию, если она не существует
  char dir[256];
  snprintf(dir, sizeof(dir), "%s/bin", getenv("HOME"));
  mkdir(dir, 0777);
  int expected_high_score = 12345;
  save_high_score(expected_high_score, 1);
  int expected_high_score_snake = 45;
  save_high_score(expected_high_score_snake, 2);
  // Открываем файл для чтения
  FILE *file = fopen(filename, "r");
  ASSERT_NE(file, nullptr);
  // Читаем рекорд из файла
  int actual_high_score;
  fscanf(file, "%d", &actual_high_score);
  fclose(file);
  // Проверяем, что функция сохранила ожидаемый рекорд
  EXPECT_EQ(actual_high_score, expected_high_score);
  EXPECT_EQ(load_high_score(1), 12345);
  EXPECT_EQ(load_high_score(2), 45);
  remove(filename);
}

// Тест для проверки обработки ошибки открытия файла
TEST_F(TetrisTest, test_save_high_score_file_open_error) {
  // Создаем временный файл с несуществующим именем
  char filename[256];
  snprintf(filename, sizeof(filename), "%s/bin/non_existent_file.txt",
           getenv("HOME"));

  // Создаем директорию, если она не существует
  char dir[256];
  snprintf(dir, sizeof(dir), "%s/bin", getenv("HOME"));
  mkdir(dir, 0777);
  // Ожидаемый рекорд
  int expected_high_score = 12345;
  // Перехватываем вывод ошибок
  FILE *stderr_backup = stderr;
  stderr = tmpfile();
  // Сохраняем текущую переменную окружения и устанавливаем новую
  char *old_home = getenv("HOME");
  setenv("HOME", "/non_existent_dir", 1);
  // Вызываем функцию save_high_score
  save_high_score(expected_high_score, 1);
  // Восстанавливаем переменную окружения
  setenv("HOME", old_home, 1);
  // Восстанавливаем стандартный вывод ошибок
  fflush(stderr);
  rewind(stderr);
  char error_message[256];
  fgets(error_message, sizeof(error_message), stderr);
  fclose(stderr);
  stderr = stderr_backup;
  // Проверяем, что функция вывела сообщение об ошибке
  //   ck_assert_msg(strstr(error_message,
  //                        "Failed to open file for writing: "
  //                        "/non_existent_dir/bin/high_score.txt") != NULL,
  //                 "Expected error message not found");///////////////////
}

TEST_F(TetrisTest, test_buttons_reaction) {
  int field_width = 10;
  int field_height = 20;
  int figures_size = 4;
  int number_of_figures = 7;
  Tetris_Game *tetris_game =
      create_memory_game(field_width, field_height, figures_size,
                         number_of_figures, figures_template);

  // Создаем игрока
  Tetris_Player player;
  tetris_game->player = &player;

  // Проверка нажатия пробела (поворот фигуры)
  buttons_reaction(32, tetris_game);
  EXPECT_EQ(tetris_game->player->action, PLAYER_UP);

  buttons_reaction('s', tetris_game);
  EXPECT_EQ(tetris_game->player->action, PLAYER_DOWN);

  buttons_reaction(KEY_DOWN, tetris_game);
  EXPECT_EQ(tetris_game->player->action, PLAYER_DOWN);

  buttons_reaction('a', tetris_game);
  EXPECT_EQ(tetris_game->player->action, PLAYER_LEFT);

  buttons_reaction(KEY_LEFT, tetris_game);
  EXPECT_EQ(tetris_game->player->action, PLAYER_LEFT);

  buttons_reaction('d', tetris_game);
  EXPECT_EQ(tetris_game->player->action, PLAYER_RIGHT);

  buttons_reaction(KEY_RIGHT, tetris_game);
  EXPECT_EQ(tetris_game->player->action, PLAYER_RIGHT);

  // Проверка нажатия 'q' или 'Q' (выход из игры)
  buttons_reaction(81, tetris_game);
  EXPECT_EQ(tetris_game->player->action, PLAYER_QUIT);
  EXPECT_EQ(tetris_game->playing, GAME_OVER);

  buttons_reaction(113, tetris_game);
  EXPECT_EQ(tetris_game->player->action, PLAYER_QUIT);
  EXPECT_EQ(tetris_game->playing, GAME_OVER);

  // Проверка нажатия ESC (пауза)
  buttons_reaction(27, tetris_game);
  EXPECT_EQ(tetris_game->player->action, PLAYER_PAUSE);

  // Проверка нажатия неизвестной клавиши (NOP)
  buttons_reaction(123, tetris_game);
  EXPECT_EQ(tetris_game->player->action, PLAYER_NOP);

  // Проверка случая ERR (нет нажатия клавиши)
  buttons_reaction(ERR, tetris_game);
  EXPECT_EQ(tetris_game->player->action, PLAYER_NOP);
  free_memory_game(tetris_game);
}

TEST_F(TetrisTest, test_collision) {
  int field_width = 10;
  int field_height = 20;
  int figures_size = 4;
  int number_of_figures = 7;
  Tetris_Game *tetris_game =
      create_memory_game(field_width, field_height, figures_size,
                         number_of_figures, figures_template);

  // Создаем фигуру
  Tetris_Figure *figure = create_memory_figure(tetris_game);
  tetris_game->figure = figure;

  // Устанавливаем фигуру в центр поля
  figure->x = field_width / 2 - figure->size / 2;
  figure->y = 0;

  // Проверка отсутствия столкновения
  EXPECT_EQ(collision(tetris_game), 0);

  // Устанавливаем фигуру за пределами поля (слева)
  figure->x = -1;
  // Устанавливаем блок фигуры, который выходит за пределы поля
  figure->blocks[0].b = 1;
  EXPECT_EQ(collision(tetris_game), 1);

  // Устанавливаем фигуру за пределами поля (справа)
  figure->x = field_width - 1;
  // Устанавливаем блок фигуры, который выходит за пределы поля
  figure->blocks[3].b = 1;
  EXPECT_EQ(collision(tetris_game), 1);

  // Устанавливаем фигуру за пределами поля (снизу)
  figure->x = field_width / 2 - figure->size / 2;
  figure->y = field_height - 1;
  // Устанавливаем блок фигуры, который выходит за пределы поля
  figure->blocks[12].b = 1;
  EXPECT_EQ(collision(tetris_game), 1);

  // Устанавливаем фигуру на место другого блока
  figure->x = 0;
  figure->y = 0;
  // Устанавливаем блок на поле
  tetris_game->field->blocks[0].b = 1;
  EXPECT_EQ(collision(tetris_game), 1);
  free_memory_game(tetris_game);
}

TEST_F(TetrisTest, test_create_memory_game) {
  int field_width = 10;
  int field_height = 20;
  int figures_size = 4;
  int number_of_figures = 7;
  Tetris_Game *tetris_game =
      create_memory_game(field_width, field_height, figures_size,
                         number_of_figures, figures_template);

  // Проверяем, что игра создана успешно
  ASSERT_NE(tetris_game, nullptr);
  EXPECT_EQ(tetris_game->field->width, field_width);
  EXPECT_EQ(tetris_game->field->height, field_height);
  EXPECT_EQ(tetris_game->figures_template->number_of_figures,
            number_of_figures);
  EXPECT_EQ(tetris_game->figures_template->size, figures_size);
  free_memory_game(tetris_game);
}

TEST_F(TetrisTest, test_drop_new_figure) {
  int field_width = 10;
  int field_height = 20;
  int figures_size = 4;
  int number_of_figures = 7;
  Tetris_Game *tetris_game =
      create_memory_game(field_width, field_height, figures_size,
                         number_of_figures, figures_template);

  // Проверяем, что начальная фигура и следующая фигура равны NULL
  ASSERT_EQ(tetris_game->figure, nullptr);
  ASSERT_EQ(tetris_game->next_figure, nullptr);

  drop_new_figure(tetris_game);

  // Проверяем, что фигура и следующая фигура стали не равны NULL
  ASSERT_NE(tetris_game->figure, nullptr);
  ASSERT_NE(tetris_game->next_figure, nullptr);
  free_memory_game(tetris_game);
}

TEST_F(TetrisTest, test_create_figure_from_template) {
  int field_width = 10;
  int field_height = 20;
  int figures_size = 4;
  int number_of_figures = 7;
  Tetris_Game *tetris_game =
      create_memory_game(field_width, field_height, figures_size,
                         number_of_figures, figures_template);

  // Создаем фигуру из шаблона
  Tetris_Figure *figure = create_figure_from_template(tetris_game, 0);

  // Проверяем, что фигура не равна NULL
  ASSERT_NE(figure, nullptr);

  // Проверяем, что фигура имеет правильные размеры и цвет
  ASSERT_EQ(figure->size, figures_size);
  ASSERT_EQ(figure->color_pair, 1);

  free_tetris_figure(figure);
  free_memory_game(tetris_game);
}

TEST_F(TetrisTest, test_calculate) {
  Tetris_Game *tetris_game = create_memory_game(10, 20, 4, 7, figures_template);
  int high_score = load_high_score(1);
  Tetris_Player player;
  player.action = PLAYER_NOP;
  tetris_game->player = &player;
  tetris_game->high_score = high_score;
  drop_new_figure(tetris_game);

  // Вправо
  tetris_game->player->action = PLAYER_RIGHT;
  int initial_x = tetris_game->figure->x;
  bool state_changed = false;
  execute_player_command(tetris_game->player->action, tetris_game,
                         &state_changed);
  EXPECT_EQ(state_changed, true);
  EXPECT_EQ(tetris_game->figure->x, initial_x + 1);

  // Влево
  tetris_game->player->action = PLAYER_LEFT;
  initial_x = tetris_game->figure->x;
  state_changed = false;
  execute_player_command(tetris_game->player->action, tetris_game,
                         &state_changed);
  EXPECT_EQ(state_changed, true);
  EXPECT_EQ(tetris_game->figure->x, initial_x - 1);

  // Вниз
  tetris_game->player->action = PLAYER_DOWN;
  initial_x = tetris_game->figure->x;
  int initial_y = tetris_game->figure->y;
  state_changed = false;
  execute_player_command(tetris_game->player->action, tetris_game,
                         &state_changed);
  EXPECT_EQ(state_changed, true);
  EXPECT_EQ(tetris_game->figure->x, initial_x);
  EXPECT_EQ(tetris_game->figure->y, initial_y + 1);

  // Вверх
  tetris_game->player->action = PLAYER_UP;
  Tetris_Figure *old_figure = create_memory_figure(tetris_game);
  old_figure->x = 5;
  old_figure->y = 10;
  old_figure->size = 4;
  int initial_blocks[16] = {0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0};

  // Переносим данные из initial_blocks в old_figure->blocks, а также клонируем
  // в фигуру
  for (int i = 0; i < 16; i++) {
    old_figure->blocks[i].b = initial_blocks[i];
    tetris_game->figure->blocks[i].b = initial_blocks[i];
  }
  state_changed = false;
  execute_player_command(tetris_game->player->action, tetris_game,
                         &state_changed);
  EXPECT_EQ(state_changed, true);

  // Проверки блока после поворота
  for (int i = 0; i < tetris_game->figure->size; i++) {
    for (int j = 0; j < tetris_game->figure->size; j++) {
      EXPECT_EQ(
          tetris_game->figure->blocks[i * tetris_game->figure->size + j].b,
          old_figure
              ->blocks[(tetris_game->figure->size - 1 - j) *
                           tetris_game->figure->size +
                       i]
              .b);
    }
  }

  // Выход
  tetris_game->player->action = PLAYER_QUIT;
  state_changed = false;
  execute_player_command(tetris_game->player->action, tetris_game,
                         &state_changed);
  EXPECT_EQ(state_changed, true);
  EXPECT_EQ(tetris_game->playing, GAME_OVER);

  // Пауза
  tetris_game->player->action = PLAYER_PAUSE;
  tetris_game->playing = GAME_OVER;
  state_changed = false;
  execute_player_command(tetris_game->player->action, tetris_game,
                         &state_changed);
  EXPECT_EQ(state_changed, true);
  EXPECT_EQ(tetris_game->playing, PLAYING);

  free_tetris_figure(old_figure);
  free_memory_game(tetris_game);
}

TEST_F(TetrisTest, test_calculate_move_figure_down) {
  Tetris_Game *tetris_game = create_memory_game(10, 20, 4, 7, figures_template);
  int high_score = load_high_score(1);
  Tetris_Player player;
  player.action = PLAYER_NOP;
  tetris_game->player = &player;
  tetris_game->high_score = high_score;
  drop_new_figure(tetris_game);

  tetris_game->ticks_left = 0;
  tetris_game->ticks = 1;
  tetris_game->figure->x = 5;
  tetris_game->figure->y = 10;

  bool state_changed = calculate(tetris_game);

  EXPECT_EQ(tetris_game->ticks, 1);
  EXPECT_EQ(tetris_game->ticks_left, 0);
  EXPECT_EQ(state_changed, true);
  EXPECT_EQ(tetris_game->figure->x, 5);
  EXPECT_EQ(tetris_game->figure->y, 11);

  free_memory_game(tetris_game);
}

TEST_F(TetrisTest, test_calculate_collision) {
  Tetris_Game *tetris_game = create_memory_game(10, 20, 4, 7, figures_template);
  Tetris_Player player;
  player.action = PLAYER_NOP;
  tetris_game->player = &player;
  drop_new_figure(tetris_game);

  tetris_game->ticks_left = 0;
  tetris_game->ticks = 1;

  int initial_blocks[16] = {0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0};

  for (int i = 0; i < 16; i++) {
    tetris_game->figure->blocks[i].b = initial_blocks[i];
  }
  tetris_game->figure->x = 5;
  tetris_game->figure->y = 9;
  // Заполнение поля с 12 строки и до низу
  for (int i = 111; i < tetris_game->field->height * tetris_game->field->width;
       i++) {
    tetris_game->field->blocks[i].b = 1;
  }
  bool state_changed = calculate(tetris_game);

  EXPECT_EQ(tetris_game->figure->y, 0);
  EXPECT_EQ(state_changed, true);

  free_memory_game(tetris_game);
}

TEST_F(TetrisTest, test_reset_game) {
  Tetris_Game *tetris_game = create_memory_game(10, 20, 4, 7, figures_template);
  for (int i = 0; i < tetris_game->field->width * tetris_game->field->height;
       i++) {
    tetris_game->field->blocks[i].b = 1;
  }
  tetris_game->playing = GAME_OVER;
  tetris_game->score = 100;
  tetris_game->level = 10;
  tetris_game->figure = NULL;
  tetris_game->next_figure = NULL;

  reset_game(tetris_game);

  EXPECT_EQ(tetris_game->playing, PLAYING);
  EXPECT_EQ(tetris_game->score, 0);
  EXPECT_EQ(tetris_game->level, 1);
  EXPECT_EQ(tetris_game->field->blocks[55].b, 0);
  ASSERT_NE(tetris_game->figure, nullptr);
  ASSERT_NE(tetris_game->next_figure, nullptr);

  free_memory_game(tetris_game);
}

TEST_F(TetrisTest, test_speed_from_level) {
  Tetris_Game *tetris_game = (Tetris_Game *)malloc(sizeof(Tetris_Game));
  tetris_game->level = 10;
  struct timespec ts2 = {0, 0};
  speed_from_level(*tetris_game, (struct timespec){0, 0},
                   (struct timespec){0, 1000000}, &ts2);
  EXPECT_EQ(ts2.tv_nsec, 3500000);

  free(tetris_game);
}

TEST_F(TetrisTest, test_pause_processing) {
  Tetris_Game tetris_game;
  Tetris_Player player;
  tetris_game.player = &player;
  player.action = PLAYER_PAUSE;
  bool paused = false;

  pause_processing(&tetris_game, &paused, NULL);
  EXPECT_EQ(paused, true);

  // Проверка переключения состояния
  pause_processing(&tetris_game, &paused, NULL);
  EXPECT_EQ(paused, false);
}

// Подготовка к тестированию функции test_game_over_and_save_high_score
// Переменная для имитации нажатия клавиши
int mock_getch_value = ERR;
// Перехват функции getch()
int mock_getch(void) { return mock_getch_value; }
TEST_F(TetrisTest, GameOver) {
  int field_width = 10;
  int field_height = 20;
  int figures_size = 4;
  int number_of_figures = 7;
  Tetris_Game *tetris_game =
      create_memory_game(field_width, field_height, figures_size,
                         number_of_figures, figures_template);
  tetris_game->playing = PLAYING;

  // Имитируем нажатие клавиши ESC
  mock_getch_value = 27;
  game_over(tetris_game, NULL, mock_getch);
  EXPECT_EQ(tetris_game->playing, GAME_OVER);

  // Вариант с нажатием 10- enter
  mock_getch_value = 10;
  game_over(tetris_game, NULL, mock_getch);
  free_memory_game(tetris_game);
}

TEST_F(TetrisTest, test_GUI) {
  WINDOW *win_game = NULL;
  WINDOW *win_next_figure = NULL;
  WINDOW *win_score_level = NULL;
  WINDOW *win_high_score = NULL;
  int brick_game = 1;
  int high_score = 0;
  cli_create_frames_for_game(&win_game, &win_next_figure, &win_score_level,
                             &win_high_score);
  display_welcome_screen(high_score, win_game, win_next_figure, win_score_level,
                         win_high_score, brick_game);
  initialization_of_colors();
}