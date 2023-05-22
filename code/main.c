#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/// Generator configuration
#define HEIGHT 40
#define LENGTH 40

#define NEIGHBOURS_DISTANCE 1
#define CELL_TYPE_COUNT 5
#define PRINT_INTERVAL 250 // in ms

// Do not edit:
#define CELL_COUNT (HEIGHT * LENGTH)

/// Functions
int min(int a, int b) { return a > b ? b : a; }
int max(int a, int b) { return a > b ? a : b; }

double min_d(double a, double b) { return a > b ? b : a; }
double max_d(double a, double b) { return a > b ? a : b; }

void clearStdout() {
#ifdef _WIN32
  system("cls");
#elif _WIN64
  system("cls");
#elif __unix__
  system("clear");
#endif
}

void wait(int ms) {
  struct timespec ts;
  ts.tv_sec = ms / 1000;
  ts.tv_nsec = (ms % 1000) * 1000000;
  nanosleep(&ts, NULL);
}

void printArray(int *arr, int n) {
  for (int i = 0; i < n - 1; i++)
    printf("%d, ", arr[i]);
  printf("%d\n", arr[n - 1]);
}

void printGrid(int *grid){
  char *colors[4] = {
    "  ",
    "\e[0;32m██\e[0m",
    "\e[0;34m██\e[0m",
    "\e[0;31m██\e[0m",
  };

  printf("┏━");
  for (int i = 0; i < LENGTH; i++)
    printf("━━");
  printf("━┓\n");

  for (int i = 0; i < HEIGHT; i++) {
    printf("┃ ");
    for (int j = 0; j < LENGTH; j++)
      printf("%s", colors[grid[i * LENGTH + j]]);
    printf(" ┃\n");
  }

  printf("┗━");
  for (int i = 0; i < LENGTH; i++)
    printf("━━");
  printf("━┛\n");
}

void editCell(int *grid, int i, int value) {
  if (i >= 0 && i < CELL_COUNT)
    grid[i] = value;
}

int *findSurroundings(int *grid, int k) {
  int *res = malloc(sizeof(int) * CELL_TYPE_COUNT);
  for (int i = CELL_TYPE_COUNT; i--; res[i] = 0);

  int kx = k % LENGTH,
      ky = k / LENGTH;

  for (int x = max(0, kx - NEIGHBOURS_DISTANCE); x <= min(LENGTH - 1, kx + NEIGHBOURS_DISTANCE); x++)
  {
    for (int y = max(0, ky - NEIGHBOURS_DISTANCE); y <= min(HEIGHT - 1, ky + NEIGHBOURS_DISTANCE); y++)
	  {
	    if (y == ky && x == kx) continue;
	    res[grid[y * LENGTH + x]]++;
	  }
  }
  
  return res;
}

void nextStep(int *grid) {
  int *res = malloc(sizeof(int) * CELL_COUNT);
  for (int i = 0; i < CELL_COUNT; i++)
    res[i] = grid[i];

  for (int i = 0; i < CELL_COUNT; i++) {
    printf("%d/%d", i, CELL_COUNT);
    int *surroundings = findSurroundings(grid, i);

    double probs[5] = {0, 0, 0, 0, 0};

    // Void to
    if (grid[i] == 0) {
    }

    // House to
    else if (grid[i] == 1) {

      // Void (1% if no park, almost no shop, almost no work)
      probs[0] = 0.01 * (surroundings[2] <= 1 && surroundings[3] <= 1 && surroundings[4] == 0);

      // House
      // /

      // Shop (5% if many houses, few shops)
      probs[2] = min_d(0, 0.05 * ((surroundings[1] >= 3) * surroundings[1] * 0.34 - surroundings[2]));

      // Work
      probs[3] = 0.1 * (surroundings[1] >= 3);

      // Park
      //probs[4] = ...
    }


    // Rand choice
    double prob_sum = 0;
    for (int j = 0; j < 5; j++)
      prob_sum += i - j ? probs[j] : 0;

    probs[i] = 1 - prob_sum;

    double sc[5] = {probs[0], 0, 0, 0, 0};
    for (int j = 1; j < 5; j++)
      sc[j] = sc[j - 1] + probs[j];
    
    printf(" - :)\n");

    // TODO:
    // Roulette pondérée

    /*
    // Houses pop up in the void
    if (grid[i] == 0 && surroundings[0] >= 3 && rand() % 1000 <= surroundings[0]*surroundings[0])
      editCell(res, i, 1);

    // House/void becomes marketplace if at least 4 houses + less than 1 market nearby
    else if ((grid[i] == 0 || grid[i] == 1) && surroundings[1] >= 5 && surroundings[2] < 1 && rand() % 100 < 1)
      editCell(res, i, 2);
    */

    /*
    // Change all cells around a house to a house
    if (surroundings[1] > 0)
      editCell(res, i, 1);
    */
  }

  for (int i = 0; i < CELL_COUNT; i++)
    grid[i] = res[i];

  free(res);
}

int main() {
  srand(time(NULL));

  int *grid = malloc(sizeof(int) * CELL_COUNT);
  for (int i = 0; i < CELL_COUNT; i++)
    grid[i] = 0;

  grid[rand() % (CELL_COUNT)] = 1;

  for (;;) {
    fflush(stdout);
    clearStdout();

    printGrid(grid);
    wait(PRINT_INTERVAL);
    nextStep(grid);
  }

  return 0;
}
