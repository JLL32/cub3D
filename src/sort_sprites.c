#include "../cub3D.h"

static void swap(t_pair *xp, t_pair *yp)
{
	t_pair temp = *xp;
	*xp = *yp;
	*yp = temp;
}

static void pair_sort(t_pair arr[], int n)
{
	int i, j;
	for (i = 0; i < n - 1; i++)
		for (j = 0; j < n - i - 1; j++)
			if (arr[j].first > arr[j + 1].first)
				swap(&arr[j], &arr[j + 1]);
}

void sort_sprites(int *order, double *dist, int amount)
{
	/* std::vector<std::pair<double, int>> sprites(amount); */
	t_pair sprites[amount];
	for (int i = 0; i < amount; i++)
	{
		sprites[i].first = dist[i];
		sprites[i].second = order[i];
	}
	pair_sort(sprites, amount);
	// restore in reverse order to go from farthest to nearest
	for (int i = 0; i < amount; i++)
	{
		dist[i] = sprites[amount - i - 1].first;
		order[i] = sprites[amount - i - 1].second;
	}
}