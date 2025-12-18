#include <unistd.h>

#include "s21_tetris_game_core.h"

void speed_from_level(struct Tetris_Game tetris_game,
                      const struct timespec sp_start,
                      const struct timespec sp_end, struct timespec* ts2) {
  int base_delay = 33000000;  // Базовая задержка в наносекундах
  int level_delay_reduction = 3000000;  // Уменьшение задержки на каждом уровне
  int level_delay = base_delay - (tetris_game.level * level_delay_reduction);
  if (level_delay <= 3000000) {
    level_delay = 4500000;  // Минимальная задержка
  }
  if (sp_end.tv_sec - sp_start.tv_sec <= 0 &&
      (ts2->tv_nsec = level_delay - (sp_end.tv_nsec - sp_start.tv_nsec)) > 0) {
    nanosleep(ts2, NULL);
  }
}