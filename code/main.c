#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/// Generator configuration
#define HEIGHT 41
#define LENGTH 96

#define NEIGHBOURS_DISTANCE 6
#define CELL_TYPE_COUNT 5
#define PRINT_INTERVAL 100 // in ms

// Do not edit:
const int CELL_COUNT = HEIGHT * LENGTH;
const int NEIGHBOURS_COUNT = (2 * NEIGHBOURS_DISTANCE + 1) * (2 * NEIGHBOURS_DISTANCE + 1) - 1;

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

void printGrid(int *grid){
  char *colors[CELL_TYPE_COUNT] = {
    "",         // none
    "\e[0;32m", // green
    "\e[0;34m", // blue
    "\e[0;33m", // orange
    "\e[0;37m", // white
  };

  printf("\n┏━");
  for (int i = 0; i < LENGTH; i++)
    printf("━━");
  printf("━┓\n");

  for (int i = 0; i < HEIGHT; i++) {
    printf("┃ ");
    for (int j = 0; j < LENGTH; j++) {
      printf(
        "%s%s",
        j == 0 || grid[i * LENGTH + j] != grid[i * LENGTH + j - 1] ? colors[grid[i * LENGTH + j]] : "",
        grid[i * LENGTH + j] ? "██" : "  "
      );
    }
    printf("\e[0m ┃\n");
  }

  printf("┗━");
  for (int i = 0; i < LENGTH; i++)
    printf("━━");
  printf("━┛\n");
}

int **findNeighbours(int *grid, int k) {
  const int kx = k % LENGTH, ky = k / LENGTH;

  int *total_neighbours = malloc(sizeof(int *) * NEIGHBOURS_DISTANCE);
  int **res = malloc(sizeof(int *) * NEIGHBOURS_DISTANCE);

  for (int i = NEIGHBOURS_DISTANCE; i--;){
    total_neighbours[i] = 0;
    res[i] = malloc(sizeof(int) * CELL_TYPE_COUNT);
    for (int j = CELL_TYPE_COUNT; j--; res[i][j] = 0);
  }

  for (int x = max(0, kx - NEIGHBOURS_DISTANCE); x <= min(LENGTH - 1, kx + NEIGHBOURS_DISTANCE); x++)
  {
    for (int y = max(0, ky - NEIGHBOURS_DISTANCE); y <= min(HEIGHT - 1, ky + NEIGHBOURS_DISTANCE); y++)
    {
      if (y == ky && x == kx) continue;
      int d = max(abs(x - kx), abs(y - ky));

      for (int i = d; i <= NEIGHBOURS_DISTANCE; i++)
      {
        res[i - 1][grid[y * LENGTH + x]]++;
        total_neighbours[d]++;
      }
    }
  }

  for (int i = 0; i < NEIGHBOURS_DISTANCE; i++)
    res[i][0] += NEIGHBOURS_COUNT - total_neighbours[i];

  free(total_neighbours);
  return res;
}

// Computes the next generation of the automaton given its current state in {grid}
void nextGeneration(int *grid) {
  int *res = malloc(sizeof(int) * CELL_COUNT);
  for (int i = 0; i < CELL_COUNT; i++)
    res[i] = grid[i];

  for (int i = 0; i < CELL_COUNT; i++) {
    int **neighbours = findNeighbours(grid, i);

    double probs[CELL_TYPE_COUNT];
    for (int j = 0; j < CELL_TYPE_COUNT; j++) probs[j] = 0;

    // Void to
    if (grid[i] == 0) {
      // Void
      // /

      // House
      probs[1] = 0.000015 + 0.01 * (neighbours[0][1] >= 1) * (1 + neighbours[0][1] / 1.5) * max(1, 3 * neighbours[0][2]) * max(1, 6 * neighbours[0][4]);

      // Shop
      probs[2] = 0.000020 * (neighbours[3][2] == 0) * neighbours[0][1] + 0.01 * (neighbours[0][3] <= 1 && neighbours[0][2] >= 1 && neighbours[5][2] <= 16);

      // Work
      probs[3] = 0.000025 * (neighbours[3][3] == 0 && neighbours[2][2] <= 3) * neighbours[0][1] + 0.01 * (neighbours[0][2] <= 1 && neighbours[0][3] >= 1 && neighbours[4][3] <= 7);

      // Park
      probs[4] = 0.001 * (neighbours[4][1] >= 60 && neighbours[5][4] == 0);
    }
    // House to
    else if (grid[i] == 1) {
      // Void
      probs[0] = 0; // 0.01 * (neighbours[1][1] >= 10);

      // House
      // /

      // Shop
      probs[2] = 0.000020 * (neighbours[3][2] == 0) * neighbours[0][1] + 0.01 * (neighbours[0][3] <= 1 && neighbours[0][2] >= 1 && neighbours[5][2] <= 16);

      // Work
      probs[3] = 0.000025 * (neighbours[3][3] == 0 && neighbours[2][2] <= 3) * neighbours[0][1] + 0.01 * (neighbours[0][2] <= 1 && neighbours[0][3] >= 1 && neighbours[4][3] <= 7);

      // Park
      probs[4] = 0.001 * (neighbours[3][1] >= 30 && neighbours[1][4] <= 5 && neighbours[5][4] <= 5) * (10 * neighbours[0][4]) * max(neighbours[0][1], 1);
    }
    // Shop to
    else if (grid[i] == 2) {
      // Void
      probs[0] = 0;

      // House
      probs[1] = 0.01 * (neighbours[0][2] < 2);

      // Shop
      // /

      // Work
      probs[3] = 0;

      // Park
      probs[4] = 0;
    }
    // Workplace to
    else if (grid[i] == 3) {
      // Void
      probs[0] = 0;

      // House
      probs[1] = 0.01 * (neighbours[1][3] < 2);

      // Shop
      probs[2] = 0;

      // Work
      // /

      // Park
      probs[4] = 0;
    }
    // Park to
    else if (grid[i] == 4) {
      // Void
      probs[0] = 0;

      // House
      probs[1] = 0.01 * (neighbours[0][1] < 2 || neighbours[1][1] < 8);

      // Shop
      probs[2] = 0;

      // Work
      probs[3] = 0;

      // Park
      // /
    }

    /* // Void to
    if (grid[i] == 0) {
      // Void
      // /

      // House
      probs[1] = 0.15 * (neighbours[1] >= 1) + 0.000015;

      // Shop
      probs[2] = 0.07 * (neighbours[1] >= 3) + 0.01 * (neighbours[1] >= 3) * neighbours[3] + 0.000001;

      // Work
      probs[3] = 0.000001;

      // Park
      probs[4] = 0.05 * (neighbours[1] >= 5 && neighbours[4] == 0);
    }
    // House to
    else if (grid[i] == 1) {
      // Void
      probs[0] = max_d(0.01 * (neighbours[2] <= 1 && neighbours[3] <= 1 && neighbours[4] == 0) - 0.025 * neighbours[0], 0);

      // House
      // /

      // Shop (5% if many houses, few shops)
      probs[2] = min_d(0, 0.005 * ((neighbours[1] >= 3) + neighbours[1] * 0.2 - neighbours[2]));

      // Work
      probs[3] = 0.005 * (neighbours[1] >= 5) + 0.005 * (neighbours[2] >= 3);

      // Park
      probs[4] = 0.001 * (neighbours[1] >= 7 && neighbours[4] == 0);
    }
    // Shop to
    else if (grid[i] == 2) {
      // Void
      probs[0] = 0.1 * (non_empty <= 3) + 0.01 * (neighbours[1] <= 2) + 0.05 * (max(2 - neighbours[1], 0));

      // House
      probs[1] = 0.05 * (neighbours[2] >= 3) * (neighbours[2]);

      // Shop
      // /

      // Work
      probs[3] = 0.05 * (neighbours[2] >= 4);

      // Park
      probs[4] = 0.0001 * (neighbours[4] == 0 && neighbours[1] >= 6);
    }
    // Workplace to
    else if (grid[i] == 3) {
      // Void
      probs[0] = 0.1 * (non_empty <= 3);

      // House
      probs[1] = 0.05 * (neighbours[3] >= 3);

      // Shop
      probs[2] = 0.05 * (neighbours[1] >= 3 && neighbours[3] >= 2);;

      // Work
      // /

      // Park
      probs[4] = 0;
    }
    // Park to
    else if (grid[i] == 4) {
      // Void
      probs[0] = 0.1 * (non_empty <= 4) + (neighbours[4] >= 1) * 0.0001;

      // House
      probs[1] = 0.01 * (neighbours[1] <= 3) + 0.0001;

      // Shop
      probs[2] = 0.01 * (neighbours[2] >= 2) + 0.0001;

      // Work
      probs[3] = 0.01 * (neighbours[3] >= 2) + 0.0001;

      // Park
      // /
    } */

    /// Rand choice
    // Initialisation des tableaux
    double prob_sum = 0;
    for (int j = 0; j < CELL_TYPE_COUNT; j++)
      prob_sum += j != i ? probs[j] : 0;

    probs[grid[i]] = 1 - prob_sum;

    double sc[CELL_TYPE_COUNT] = {probs[0], 0, 0, 0, 0};
    for (int j = 1; j < CELL_TYPE_COUNT; j++)
      sc[j] = sc[j - 1] + probs[j];

    // Choix pondéré
    int choice = 0;
    double rand_double = ((double)rand() / RAND_MAX);
    while(choice < CELL_TYPE_COUNT - 1 && sc[choice] < rand_double)
      choice++;

    if (choice != grid[i])
      res[i] = choice;

    // Free stuff
    for (int i = NEIGHBOURS_DISTANCE; i--; free(neighbours[i]));
    free(neighbours);

    /*
    // Houses pop up in the void
    if (grid[i] == 0 && neighbours[0] >= 3 && rand() % 1000 <= neighbours[0]*neighbours[0])
      res[i] = 1;

    // House/void becomes marketplace if at least 4 houses + less than 1 market nearby
    else if ((grid[i] == 0 || grid[i] == 1) && neighbours[1] >= 5 && neighbours[2] < 1 && rand() % 100 < 1)
      res[i] = 2;
    */

    /*
    // Change all cells around a house to a house
    if (neighbours[1] > 0)
      res[i] = 1;
    */
  }

  // Copy res to grid
  for (int i = CELL_COUNT; i--; grid[i] = res[i]);

  free(res);
}

void printStats(int grid[CELL_COUNT]) {
  // Init table
  int count[CELL_TYPE_COUNT];
  for (int i = CELL_TYPE_COUNT; i--; count[i] = 0);
  // Count cells in grid
  for (int i = CELL_COUNT; i--; count[grid[i]]++);

  printf("\e[0;32mHouses\e[0m: %d (%2.1lf%%) - \e[0;34mShops\e[0m: %d (%2.1lf%%) - \e[0;33mWorkplaces\e[0m: %d (%2.1lf%%) - \e[0;37mParks\e[0m: %d (%2.1lf%%)\n",
         count[1], 100 * ((double)count[1] / CELL_COUNT),
         count[2], 100 * ((double)count[2] / CELL_COUNT),
         count[3], 100 * ((double)count[3] / CELL_COUNT),
         count[4], 100 * ((double)count[4] / CELL_COUNT));
}

int main() {
  const long int start_time = time(NULL);
  srand(start_time);

  int *grid = malloc(sizeof(int) * CELL_COUNT);
  for (int i = 0; i < CELL_COUNT; i++)
    grid[i] = 0;

  // Print first grid
  printGrid(grid);
  printStats(grid);
  wait(PRINT_INTERVAL);

  // Main loop
  for (int64_t gens = 1; ;) {
    // Start timer
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);

    // Compute next grid
    nextGeneration(grid);

    // Clear previously displayed grid
    fflush(stdout);
    clearStdout();

    // Print next grid
    printGrid(grid);
    printStats(grid);

    // End timer
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    int time_spent = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;

    // Print debug stats
    printf("\e[0;39mGeneration #%ld - Elapsed time: %lds - FPS: %2.0f - Rendered in: %2.3fms\e[0m\n",
           ++gens, time(NULL) - start_time, (double)gens / (time(NULL) - start_time), (double)time_spent / 1000);

    wait(max(PRINT_INTERVAL - time_spent / 1000, 0));
  }

  return 0;
}
