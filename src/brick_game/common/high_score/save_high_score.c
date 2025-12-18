#include "high_score.h"
void save_high_score(int high_score, int flag) {
  char filename[256];
  snprintf(filename, sizeof(filename), "%s/bin/%s", getenv("HOME"),
           HIGH_SCORE_FILENAME);

  FILE *file = fopen(filename, "r");
  int scores[2] = {0, 0};
  if (file != NULL) {
    if (fscanf(file, "%d", &scores[0]) != 1) {
      scores[0] = 0;  // Первая строка для тетриса
    }
    if (fscanf(file, "%d", &scores[1]) != 1) {
      scores[1] = 0;  // Вторая строка для змейки
    }
    // fscanf(file, "%d", &scores[0]);
    // fscanf(file, "%d", &scores[1]);
    fclose(file);
  }

  if (flag == 1) {
    scores[0] = high_score;
  } else if (flag == 2) {
    scores[1] = high_score;
  }

  file = fopen(filename, "w");
  if (file == NULL) {
    fprintf(stderr, "Failed to open file for writing: %s\n", filename);
    return;
  }
  fprintf(file, "%d\n%d", scores[0], scores[1]);
  fclose(file);
}