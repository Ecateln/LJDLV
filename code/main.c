#include <time.h>
#include <stdio.h>
#include <stdlib.h>

// Generator configuration
#define HEIGHT 30
#define LENGTH 40

#define NEIGHBOURS_DISTANCE 3
#define CELL_TYPE_COUNT 5
#define PRINT_INTERVAL 250 // in ms

#define CELLS_COUNT (HEIGHT * LENGTH) // patouche

/*
 * TODO:
 * - Decide of the rules
 * - Ponderage de la distance
 */

/*
 * idk if i'll need this again, so i kept it jsut in case
 * for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < LENGTH; j++)
			printf("%d, ", res[i * LENGTH + j]);
		printf("\n");
	}
 */

// The name is self-explanatory imo
void clearStdout()
{
#ifdef _WIN32
  system("cls");
#elif _WIN64
  system("cls");
#elif __unix__
  system("clear");
#endif
}

void wait(int ms)
{
	struct timespec ts;
	ts.tv_sec = ms / 1000;
	ts.tv_nsec = (ms % 1000) * 1000000;
	nanosleep(&ts, NULL);
}

void printArray(int *arr, int n) {
  for (int i = 0; i < n-1; i++)
    printf("%d, ", arr[i]);
  printf("%d\n", arr[n-1]);
}

void printGrid(int *grid)
{
  char *types[4] = {"  ", "\e[0;32m██\e[0m", "\e[0;31m██\e[0m", "\e[0;34m██\e[0m"};

	printf("┏━");
	for (int i = 0; i < LENGTH; i++)
		printf("━━");
	printf("━┓\n");

	for (int i = 0; i < HEIGHT; i++)
	{
		printf("┃ ");
		for (int j = 0; j < LENGTH; j++)
			printf("%s", types[grid[i * LENGTH + j]]);
		printf(" ┃\n");
	}

	printf("┗━");
	for (int i = 0; i < LENGTH; i++)
		printf("━━");
	printf("━┛\n");
}

void editCell(int *grid, int i, int value)
{
  if (i >= 0 && i < CELLS_COUNT)
    grid[i] = value;
}

int distance(int a, int b) {
  return abs((b % LENGTH) - (a % LENGTH)) + abs((b / LENGTH) - (a / LENGTH));
}

int *findSurroundings(int *grid, int k) {
  int *res = malloc(sizeof(int) * CELL_TYPE_COUNT);
  for (int i = CELL_TYPE_COUNT; i--; res[i] = 0);

  for (int i = 0; i < HEIGHT * LENGTH; i++) {
    if (distance(i, k) <= NEIGHBOURS_DISTANCE && i != k)
      res[grid[i]]++;
  }

  return res;
}

void nextStep(int *grid)
{
  int *res = malloc(sizeof(int) * CELLS_COUNT);
  for (int i = 0; i < CELLS_COUNT; i++)
    res[i] = grid[i];
  
  for (int i = 0; i < CELLS_COUNT; i++)
  {
    int *surroundings = findSurroundings(grid, i);

    // A house surrounded by houses becomes a store
    if (grid[i] != 2 && surroundings[1] >= 5 && rand() % 100 < 5)
      editCell(res, i, 2);

    // If few houses and no stores nearby, 5% chance to disappear
    else if (grid[i] != 0 && surroundings[1] <= 2 && rand() % 100 < 5)
      editCell(res, i, 0);

    // Some people like to settle in rural areas
    else if (grid[i] == 0 && surroundings[1] <= 2 && rand() % 100 < (15 * (surroundings[2])))
      editCell(res, i, 1);

    else if (grid[i] == 2 && (surroundings[1] <= 3 || surroundings[2] >= 4) && rand() % 100 < 25)
      editCell(res, i, rand() % 100 < 25);
    
    /*
    if (grid[i] == 1)
    {
      // Change all cells around a house to a house
      if (i % LENGTH != 0 && rand() % 2)
	editCell(res, i - 1, 1);
      
      if (i % LENGTH != LENGTH - 1 && rand() % 2)
	editCell(res, i + 1, 1);
      
      if (rand() % 2)
	editCell(res, i - LENGTH, 1);
      
      if (rand() % 2)
	editCell(res, i + LENGTH, 1);
    }
    */
  }
  
  // grid = res; // why not
  
  for (int i = 0; i < CELLS_COUNT; i++)
    grid[i] = res[i];
  
  free(res);
}

int main()
{
  srand(time(NULL));
 
  int *grid = malloc(sizeof(int) * CELLS_COUNT);
  for (int i = 0; i < CELLS_COUNT; i++)
    grid[i] = 0;
  
  grid[rand() % (CELLS_COUNT)] = 2;
  
  for (;;)
  {
    fflush(stdout);
    clearStdout();
    
    printGrid(grid);
    wait(PRINT_INTERVAL);
    nextStep(grid);
  }
  
  return 0;
}
