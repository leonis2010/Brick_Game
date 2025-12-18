#ifndef HIGH_SCORE_H
#define HIGH_SCORE_H
#include <stdio.h>
#include <stdlib.h>
/**
 * @brief Имя файла для сохранения рекорда.
 */
#define HIGH_SCORE_FILENAME "high_score.txt"

int load_high_score(int game_type);
void save_high_score(int score, int game_type);

#endif  // HIGH_SCORE_H
