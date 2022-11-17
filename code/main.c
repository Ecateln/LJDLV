#include <time.h>
#include <stdio.h>
#include <stdlib.h>

// Generator configuration
#define HEIGHT 20
#define LENGTH 20
#define CELLS_COUNT (HEIGHT * LENGTH) // patouche

#define PRINT_INTERVAL 250 // in ms

/*
 * TODO:
 * - Array of int representing the cells
 *   0: empty, 1: house, 2: store, ..... (add: work, roads?)
 * - Decide of the rules
 */

/**
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

void printGrid(int *grid)
{
	char *types[3] = {"  ", "\e[0;32m██\e[0m", "\e[0;34m██\e[0m"};

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

void changeCell(int *grid, int i, int value)
{
	if (i >= 0 && i < CELLS_COUNT)
		grid[i] = value;
}

void nextStep(int *grid)
{
	int *res = malloc(sizeof(int) * CELLS_COUNT);
	for (int i = 0; i < CELLS_COUNT; i++)
		res[i] = grid[i];

	for (int i = 0; i < CELLS_COUNT; i++)
	{
		if (grid[i] == 1)
		{
			// Change all cells around a house to a house
			if (i % LENGTH != 0)
				changeCell(res, i - 1, 1);
			if (i % LENGTH != LENGTH - 1)
				changeCell(res, i + 1, 1);

			changeCell(res, i - LENGTH, 1);
			changeCell(res, i + LENGTH, 1);
		}
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

	grid[rand() % (CELLS_COUNT)] = 1;

	for (; 1;)
	{
		clearStdout();
		printGrid(grid);
		wait(PRINT_INTERVAL);
		nextStep(grid);
	}

	return 0;
}
