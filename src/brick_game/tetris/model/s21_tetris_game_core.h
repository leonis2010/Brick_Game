// s21_tetris_game_core.h
#ifndef GAME_CORE_H
#define GAME_CORE_H

#include <errno.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

/**
 * @brief Начальное количество тиков.
 */
#define TET_TICK_START 30

/**
 * @brief Очки за очистку одной линии.
 */
#define score_for_1_line 100

/**
 * @brief Имя файла для сохранения рекорда.
 */
#define HIGH_SCORE_FILENAME "high_score.txt"

/**
 * @brief Перечисление состояний игры.
 */
enum { GAME_OVER = 0, PLAYING };

/**
 * @brief Перечисление действий игрока.
 */
enum {
  PLAYER_NOP = 0,
  PLAYER_UP,
  PLAYER_DOWN,
  PLAYER_LEFT,
  PLAYER_RIGHT,
  PLAYER_QUIT,
  PLAYER_PAUSE
};

/**
 * @brief Структура, представляющая кирпичик фигуры.
 */
typedef struct Tetris_Block {
  int b; /**< Значение кирпичика */
} Tetris_Block;

/**
 * @brief Структура, представляющая текущую фигуру (падающую).
 */
typedef struct Tetris_Figure {
  int x;                /**< Координата X фигуры */
  int y;                /**< Координата Y фигуры */
  int size;             /**< Размер фигуры */
  int color_pair;       /**< Цветовая пара фигуры */
  Tetris_Block* blocks; /**< Массив кирпичиков фигуры */
} Tetris_Figure;

/**
 * @brief Структура, представляющая шаблон фигур.
 */
typedef struct Tetris_Figures_Template {
  int number_of_figures; /**< Количество фигур */
  int size;              /**< Размер фигур */
  const Tetris_Block* blocks; /**< Массив кирпичиков шаблона фигур */
} Tetris_Figures_Template;

/**
 * @brief Структура, представляющая игровое поле.
 */
typedef struct Tetris_Field {
  int width;  /**< Ширина игрового поля */
  int height; /**< Высота игрового поля */
  Tetris_Block* blocks; /**< Массив кирпичиков игрового поля */
} Tetris_Field;

/**
 * @brief Структура, представляющая игрока.
 */
typedef struct Tetris_Player {
  int action; /**< Действие игрока */
} Tetris_Player;

/**
 * @brief Структура, представляющая игру.
 */
typedef struct Tetris_Game {
  Tetris_Field* field;        /**< Игровое поле */
  Tetris_Figure* figure;      /**< Текущая фигура */
  Tetris_Figure* next_figure; /**< Следующая фигура */
  Tetris_Figures_Template* figures_template; /**< Шаблон фигур */
  Tetris_Player* player;                     /**< Игрок */
  int ticks;       /**< Количество тиков */
  int ticks_left;  /**< Оставшееся количество тиков */
  int playing;     /**< Состояние игры */
  int score;       /**< Очки игрока */
  int level;       /**< Уровень игры */
  int high_score;  /**< Рекорд игры */
  int* figure_bag; /**< "Мешок" с фигурами */
  int bag_index;   /**< Индекс в "мешке" */
} Tetris_Game;

/**
 * @brief Внешний массив шаблонов фигур.
 */
extern const Tetris_Block figures_template[];

/**
 * @brief Создает шаблон фигур в памяти.
 *
 * @param number_of_figures Количество фигур.
 * @param figures_size Размер фигур.
 * @param figures_template Массив шаблонов фигур.
 * @return Указатель на созданный шаблон фигур.
 */
Tetris_Figures_Template* create_memory_figures_template(
    int number_of_figures, int figures_size,
    const Tetris_Block* figures_template);

/**
 * @brief Создает игровое поле в памяти.
 *
 * @param width Ширина игрового поля.
 * @param height Высота игрового поля.
 * @return Указатель на созданное игровое поле.
 */
Tetris_Field* create_memory_field(int width, int height);

/**
 * @brief Создает игру в памяти.
 *
 * @param field_width Ширина игрового поля.
 * @param field_height Высота игрового поля.
 * @param figures_size Размер фигур.
 * @param number_of_figures Количество фигур.
 * @param figures_template Массив шаблонов фигур.
 * @return Указатель на созданную игру.
 */
Tetris_Game* create_memory_game(int field_width, int field_height,
                                int figures_size, int number_of_figures,
                                const Tetris_Block* figures_template);

/**
 * @brief Перемещает фигуру вниз.
 *
 * @param tetg Указатель на игру.
 */
void moveFigureDown(Tetris_Game* tetg);

/**
 * @brief Перемещает фигуру вверх.
 *
 * @param tetg Указатель на игру.
 */
void moveFigureUp(Tetris_Game* tetg);

/**
 * @brief Перемещает фигуру вправо.
 *
 * @param tetg Указатель на игру.
 */
void moveFigureRight(Tetris_Game* tetg);

/**
 * @brief Перемещает фигуру влево.
 *
 * @param tetg Указатель на игру.
 */
void moveFigureLeft(Tetris_Game* tetg);

/**
 * @brief Проверяет столкновение фигуры.
 *
 * @param tetris_game Указатель на игру.
 * @return 1, если столкновение есть, иначе 0.
 */
int collision(Tetris_Game* tetris_game);

/**
 * @brief Размещает фигуру после падения.
 *
 * @param tetris_game Указатель на игру.
 */
void plant_figure(Tetris_Game* tetris_game);

/**
 * @brief Проверяет, заполнена ли линия.
 *
 * @param i Индекс линии.
 * @param tfl Указатель на игровое поле.
 * @return 1, если линия заполнена, иначе 0.
 */
int line_filled(int i, Tetris_Field* tfl);

/**
 * @brief Сдвигает линию вниз.
 *
 * @param i Индекс линии.
 * @param tfl Указатель на игровое поле.
 */
void drop_line(int i, Tetris_Field* tfl);

/**
 * @brief Очищает заполненные линии.
 *
 * @param tetg Указатель на игру.
 * @return Количество очищенных линий.
 */
int erasse_lines(Tetris_Game* tetg);

/**
 * @brief Создает фигуру в памяти.
 *
 * @param tetris_game Указатель на игру.
 * @return Указатель на созданную фигуру.
 */
Tetris_Figure* create_memory_figure(Tetris_Game* tetris_game);

/**
 * @brief Создает новую фигуру.
 *
 * @param tetris_game Указатель на игру.
 */
void drop_new_figure(Tetris_Game* tetris_game);

/**
 * @brief Поворачивает фигуру.
 *
 * @param tetg Указатель на игру.
 * @return Указатель на повернутую фигуру.
 */
Tetris_Figure* rotTetFigure(Tetris_Game* tetg);

/**
 * @brief Выполняет вычисления для игры.
 *
 * @param tetris_game Указатель на игру.
 * @return true, если состояние игры изменилось, иначе false.
 */
bool calculate(Tetris_Game* tetris_game);

/**
 * @brief Обрабатывает нажатие кнопок.
 *
 * @param ch Символ нажатой кнопки.
 * @param tetris_game Указатель на игру.
 */
void buttons_reaction(int ch, Tetris_Game* tetris_game);

/**
 * @brief Сбрасывает игру.
 *
 * @param tetg Указатель на игру.
 */
void reset_game(Tetris_Game* tetg);

/**
 * @brief Освобождает память, занятую "мешком" с фигурами.
 *
 * @param bag Указатель на "мешок" с фигурами.
 */
void free_figure_bag(int* bag);

/**
 * @brief Освобождает память, занятую шаблоном фигур.
 *
 * @param tetris_figures_template Указатель на шаблон фигур.
 */
void free_tetris_figures_template(
    Tetris_Figures_Template* tetris_figures_template);

/**
 * @brief Освобождает память, занятую игровым полем.
 *
 * @param tetris_field Указатель на игровое поле.
 */
void free_tetris_field(Tetris_Field* tetris_field);

/**
 * @brief Освобождает память, занятую игрой.
 *
 * @param tetris_game Указатель на игру.
 */
void free_memory_game(Tetris_Game* tetris_game);

/**
 * @brief Освобождает память, занятую фигурой.
 *
 * @param tetris_figure Указатель на фигуру.
 */
void free_tetris_figure(Tetris_Figure* tetris_figure);

/**
 * @brief Сохраняет рекорд игры.
 *
 * @param high_score Рекорд игры.
 */
void save_high_score(int high_score, int flag);

/**
 * @brief Загружает рекорд игры.
 *
 * @return Рекорд игры.
 */
int load_high_score(int flag);
void print_high_score(Tetris_Game* tetris_game);
void counting_score_and_level(Tetris_Game* tetris_game, int lines);
void execute_player_command(int action, Tetris_Game* tetris_game,
                            bool* state_changed);
Tetris_Figure* create_figure_from_template(Tetris_Game* tetris_game, int fnum);

/**
 * @brief Устанавливает скорость игры в зависимости от уровня.
 *
 * @param tetris_game Игровое состояние.
 * @param sp_start Начальное время.
 * @param sp_end Конечное время.
 * @param ts1 Временная переменная.
 * @param ts2 Временная переменная.
 */
void speed_from_level(struct Tetris_Game tetris_game,
                      const struct timespec sp_start,
                      const struct timespec sp_end, struct timespec* ts2);

#endif  // GAME_CORE_H
