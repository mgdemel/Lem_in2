#include "lem_in.h"

/*
**	Returns a 1 if it finds the exact word in haystack that was in needle before or 
** 	after a '-' character.
*/

// CHANGE THE NAME OF THIS FUNCTION YOU DINGUS
int		ft_strword(int *haystack, int needle)
{
	if (haystack[0] == needle)
		return (haystack[1]);
	else if (haystack[1] == needle)
		return (haystack[0]);
	return (0);
}

/*
**	An int** array is sent in to be increased by one, so we add one in
**	tmp and copy over all content to the tmp and return that.
*/

int		**append_array(int **arr, int max)
{
	int **tmp;
	int i;
	int j;
	
	/*
	**  arr[0] = -3|4|0
	**	arr[1] = -4|5|0|2
	*/
	i = 0;
	ft_printf("arr[i][0]:%d\n", (arr[i][0] * -1));
	if (!(tmp = (int **)malloc(sizeof(int *) * (max + 1))))
		return (NULL);
	while (i < max)
	{
		j = 0;
		if (!(tmp[i] = (int *)malloc(sizeof(int) * (arr[i][0] * -1))))
			return (NULL);
		while (j < (arr[i][0] * -1))
		{
			tmp[i][j] = arr[i][j];
			j++;
		}
		i++;
	}
	i = 0;
	while (i < max)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (tmp);
}

/*
**	Discards dead ends from all_paths and sorts paths from short to long
*/
void	sort_paths(t_lem *lem)
{
	int *tmp;
	int i;
	int j;
	int x;
	int tab;

	i = 0;
	j = 0;
	x = 0;
	tab = lem->max_paths;
	ft_printf("lem->negative_one:%d\n", lem->negative_one);
	if (!(lem->final_paths = (int **)malloc(sizeof(int *) * lem->negative_one)))
		ft_printf("ERROR in sort_paths");
	while (i < tab)
	{
		if (lem->all_paths[i][lem->all_paths[i][0] * -1] == -1)
		{
			lem->final_paths[j] = lem->all_paths[i];
			j++;
		}
		else
			lem->max_paths--;
		i++;
	}
	while (x + 1 < lem->negative_one)
	{
		if (lem->final_paths[x][0] * -1 > lem->final_paths[x + 1][0] * -1)
		{
			tmp = lem->final_paths[x];
			lem->final_paths[x] = lem->final_paths[x + 1];
			lem->final_paths[x + 1] = tmp;
			x = 0;
		}
		else
			x++;
	}
	ft_putstr("\n\nALL VALID PATHS - SORTED: \n");
	ft_printf("total:%d\n", lem->total_paths);
	print_double_arr(lem->final_paths, lem->max_paths);
}

/*
**	Takes an int array and returns the copy.
*/
int		*ft_newintarr(int *forbidden_array, int i)
{
	int *new;
	int j;

	j = i;
	if (!(new = (int *)malloc(sizeof(int) * (i))))
		return (NULL);
	i--;
	while (i >= 0)
	{
		new[i] = forbidden_array[i];
		i--;
	}
	return (new);
}

void	count_valid_paths(t_lem *lem)
{
	int i;

	i = 0;
	lem->negative_one = 0;
	while (i < lem->max_paths)
	{
		if (lem->all_paths[i][lem->all_paths[i][0] * -1] == -1)
			lem->negative_one++;
		i++;
	}
}
