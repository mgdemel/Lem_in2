


#include "../libft/include/libft.h"
#include <stdio.h>

int		*add_elem_int_array(int nbr, t_lem *lem)
{
	int	*new;
	int i;
	int j;

	i = 0;
	j = 0;
	while (lem->forbidden_array[nbr])
		nbr++;
	new = malloc(sizeof(int) * nbr + 1);
	while (j < nbr)
	{
		new[j] = lem->forbidden_array[j];
		j++;
	}
	new[j] = nbr;
	return (new);
}

int		scan_forbidden(int *array, int i)
{
	int j;

	j = 0;
	while (array[j])
	{
		if (array[j] == i)
			return (1);
		j++;
	}
	return (0);
}


int		find_parent_links(char **tunnels, char *parent) //returns the amount of hits of a room name found in tunnels
{
	int i;
	int c;
	int **forbidden_indexes; // 0 and 1 and etc...
	
	forbidden_indexes[j][d] = 3
	c = 0;
	i = 0;
	j = ft(forbidden_indexes);
	while (tunnels[i])
	{
		if (scan_forbidden(lem->forbidden_array, i))
			i++;
		else if (ft_strstr(tunnels, parent))
		{
			c++;
			lem->forbidden_array = add_elem_int_array(i, lem);
		}
		i++;
	}
	return (c);
}


int	main(void)
{
	char **tunnels;
	char *parent;

	printf("%s@\n", ft_strstr2(haystack, needle));
	return (0);
}