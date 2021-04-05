#include "lem_in.h"

/*
**	Scans the array if the number i exists, MOVE TO UTILS
*/

static int	scan_forbidden(int *array, int i, t_lem *lem)
{
	int j;

	j = 0;
	while (j < lem->nbr_tunnels)
	{
		if (array[j] == i)
			return (1);
		j++;
	}
	return (0);
}

/*
** Adds an element onto the int array
*/

int			add_elem_int_array(int *forb, t_lem *lem, char *block, int parent)
{
	int i;
	int j;

	j = 0;
	i = 0;
	ft_printf("add_elem_int_array info:\nblock:%s\nparent:%d\n", block, parent);
	while (i < lem->nbr_tunnels)
	{
		if (scan_forbidden(forb, i, lem) == 1)
			i++;
		else if (ft_strword(lem->tunnels[i], block))
		{
			while (forb[j] > -1)
				j++;
			forb[j] = i;
			i++;
			if (parent == 1)
				return (1);
		}
		else
			i++;
	}
	return (0);
}

/*
**	Searching for parent links, taking any forbidden into account.
*/

int			find_parent_links(char *parent, t_lem *lem, int *forbidden_array)
{
	int i;
	int t;

	t = 0;
	i = 0;
	while (i < lem->nbr_tunnels)
	{
		if (scan_forbidden(forbidden_array, i, lem) == 1)
			i++;
		else if (ft_strword(lem->tunnels[i], parent))
		{
			t++;
			i++;
		}
		else
			i++;
	}
	if (t > 1)
		return (1);
	return (0);
}
