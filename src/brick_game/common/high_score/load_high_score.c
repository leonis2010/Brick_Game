#include "high_score.h"

int load_high_score(int flag) {
  char filename[256];
  snprintf(filename, sizeof(filename), "%s/bin/%s", getenv("HOME"),
           HIGH_SCORE_FILENAME);
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    return 0;
  }

  int high_score = 0;
  int current_line = 0;

  // Читаем файл построчно
  // feof Возвращает ненулевое значение (истина),
  // если указатель на файл (file) достиг конца файла.
  while (!feof(file)) {
    int score;
    if (fscanf(file, "%d", &score) == 1) {
      current_line++;
      if (current_line == flag) {
        high_score = score;
        break;
      }
    } else {
      break;
    }
  }

  fclose(file);
  return high_score;
}