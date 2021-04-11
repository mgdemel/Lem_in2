#include "lem_in.h"

/*
**	Returns a 1 if it finds the exact word in haystack that was in needle before or 
** 	after a '-' character.
*/

int		ft_strword(char *haystack, char *needle)
{
	int j;
	char **new;
	int word;

	word = 0;
	new = ft_strsplit(haystack, '-');
	while (word < 2)
	{
		j = 0;
		while (new[word][j] == needle[j])
		{
			if (needle[j] == '\0' && new[word][j] == '\0')
			{
				free(new[0]);
				free(new[1]);
				free(new);
				return (1);
			}
			j++;
		}
		word++;
	}
	free(new[0]);
	free(new[1]);
	free(new);
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
	if (!(tmp = (int **)malloc(sizeof(int *) * (max + 1))))
		return (NULL);
	while (i < max)
	{
		j = 0;
		if (!(tmp[i] = (int *)malloc(sizeof(int) * arr[i][0] * -1)))
			return (NULL);
		while (j < arr[i][0] * -1)
		{
			tmp[i][j] = arr[i][j];
			j++;
		}
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

/*
**	This functions will find the needle in the haystack, then return
**	the other part of the haystack minus the middle character
**	dividing them.
*/

char	*needle_crop(char *haystack, char *needle)
{
	char **new;
	char *ret;

	new = ft_strsplit(haystack, '-');
	if (ft_strcmp(new[0], needle))
		ret = ft_strdup(new[0]);
	else
		ret = ft_strdup(new[1]);
	free(new[0]);
	free(new[1]);
	free(new);
	return (ret);
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
