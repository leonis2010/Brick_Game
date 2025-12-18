// s21_tetris_cli.h
#ifndef TETRIS_CLI_H
#define TETRIS_CLI_H
#include <ncurses.h>

#include "s21_tetris_game_core.h"

#ifdef TEST_MODE
// При тестировании заглушка для curs_set
int curs_set(int visibility);
#else
#endif

/**
 * @brief Цветовая пара для игрового поля.
 */
#define color_field 8

/**
 * @brief Цветовая пара для следующей фигуры.
 */
#define color_field_next_figure 12

/**
 * @brief Цветовая пара для фигуры.
 */
#define color_figure 9

/**
 * @brief Цветовая пара для паузы.
 */
#define PAUSE_COLOR_PAIR 22

/**
 * @brief Отображает паузу в игре.
 *
 * @param win_game Указатель на окно игры.
 */
void cli_print_pause(WINDOW* win_game);

/**
 * @brief Отображает конец игры.
 *
 * @param tetris_game Указатель на игру.
 * @param win_game Указатель на окно игры.
 */
void cli_game_over(Tetris_Game* tetris_game, WINDOW* win_game);

/**
 * @brief Отображает игру в CLI.
 *
 * @param tetris_game Указатель на игру.
 * @param win_game Указатель на окно игры.
 * @param win_next_figure Указатель на окно следующей фигуры.
 * @param win_score_level Указатель на окно очков и уровня.
 * @param win_high_score Указатель на окно рекорда.
 */
void cli_print_game(Tetris_Game* tetris_game, WINDOW* win_game,
                    WINDOW* win_next_figure, WINDOW* win_score_level,
                    WINDOW* win_high_score);

/**
 * @brief Рисует фигуру в окне.
 *
 * @param figure Указатель на фигуру.
 * @param offset_x Смещение по X.
 * @param offset_y Смещение по Y.
 * @param win_next_figure Указатель на окно следующей фигуры.
 */
void cli_draw_figure(Tetris_Figure* figure, int offset_x, int offset_y,
                     WINDOW* win_next_figure);

/**
 * @brief Создает фреймы для игры.
 *
 * @param win_game Указатель на окно игры.
 * @param win_next_figure Указатель на окно следующей фигуры.
 * @param win_score_level Указатель на окно очков и уровня.
 * @param win_high_score Указатель на окно рекорда.
 * @return 0, если успешно, иначе код ошибки.
 */
int cli_create_frames_for_game(WINDOW** win_game, WINDOW** win_next_figure,
                               WINDOW** win_score_level,
                               WINDOW** win_high_score);

/**
 * @brief Отображает начальный экран.
 *
 * @param high_score Рекорд игры.
 * @param win_game Указатель на окно игры.
 * @param win_next_figure Указатель на окно следующей фигуры.
 * @param win_score_level Указатель на окно очков и уровня.
 * @param win_high_score Указатель на окно рекорда.
 */
void display_welcome_screen(int high_score, WINDOW* win_game,
                            WINDOW* win_next_figure, WINDOW* win_score_level,
                            WINDOW* win_high_score, int brick_game);

/**
 * @brief Обрабатывает паузу в игре.
 *
 * @param tetris_game Указатель на игру.
 * @param paused Указатель на переменную состояния паузы.
 * @param win_game Указатель на окно игры.
 */
void pause_processing(Tetris_Game* tetris_game, bool* paused, WINDOW* win_game);

/**
 * @brief Обрабатывает конец игры и сохраняет рекорд.
 *
 * @param tetris_game Указатель на игру.
 * @param win_game Указатель на окно игры.
 */
void game_over(Tetris_Game* tetris_game, WINDOW* win_game,
               int (*input_func)(void));

/**
 * @brief Выводит рекорд игры.
 *
 * @param tetris_game Указатель на игру.
 */
void print_high_score(Tetris_Game* tetris_game);

/**
 * @brief Ожидание нажатия Enter.
 */
void waiting_Enter();

/**
 * @brief Функция ввода (для обработки событий в CLI).
 */
int input_func(void);

/**
 * @brief Инициализация цветов.
 */
void initialization_of_colors();

#endif  // TETRIS_CLI_H