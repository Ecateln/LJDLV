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
#define CELLS_COUNT (HEIGHT * LENGTH)

/// Functions
int min(int a, int b) { return a > b ? b : a; }
int max(int a, int b) { return a > b ? a : b; }

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
  if (i >= 0 && i < CELLS_COUNT)
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
  int *res = malloc(sizeof(int) * CELLS_COUNT);
  for (int i = 0; i < CELLS_COUNT; i++)
    res[i] = grid[i];

  for (int i = 0; i < CELLS_COUNT; i++) {
    int *surroundings = findSurroundings(grid, i);

    int probs[5] = {0; 0; 0; 0; 0};

    // Void to
    if (grid[i] == 0) {
    }

    // House to
    else if (grid[i] == 1) {

      // Void (rare, 1%)
      grid[0] = 0.01 * (surroundings[2] <= 1 && surroundings[3] <= 1 && surroundings[4] == 0);

      // House
      // /

      // Shop
      grid[2] = 

      // Void (must be rare -> 0.1 % ?)
      if (surroundings[2] <= 1 && surroundings[] && surroundings[4])
        editCell(res, i, 0);
      // Shop (not that frequent, yet)
      else if (surroundings[1] >= 5 && surroundings[2] < 2)
        editCell(res, i, 2);
      // Workplace (rare)
      else if ()
        editCell(res, i, 3);
      // Park (frequent if too many houses)
      else if ()
        editCell(res, i, 4);
    }

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

  for (int i = 0; i < CELLS_COUNT; i++)
    grid[i] = res[i];

  free(res);
}

int main() {
  srand(time(NULL));

  int *grid = malloc(sizeof(int) * CELLS_COUNT);
  for (int i = 0; i < CELLS_COUNT; i++)
    grid[i] = 0;

  grid[rand() % (CELLS_COUNT)] = 1;

  for (;;) {
    fflush(stdout);
    clearStdout();

    printGrid(grid);
    wait(PRINT_INTERVAL);
    nextStep(grid);
  }

  return 0;
}
