#include "lem_in.h"

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

/*
**	A util of scan_paths in gater_paths
*/

void	get_room_num(t_tree *tree, t_lem *lem, int r, int i)
{
	t_room	*room;

	room = lem->all_rooms;
	while (room->next != NULL && (ft_strcmp(room->name, tree->name) != 0))
		room = room->next;
	lem->all_paths[i][r] = room->roomnum;
}
