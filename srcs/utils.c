#include "../includes/lem_in.h"

/*
**	Scans the array if the number i exists, MOVE TO UTILS
*/
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

/*
** Adds an element onto the int array, UTILS FUNCTION
*/
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


int		find_parent_links(char **tunnels, char *parent, t_lem *lem) //returns the amount of hits of a room name found in tunnels
{
	int i;
	
	i = 0;
	while (tunnels[i])
	{
		if (scan_forbidden(lem->forbidden_array, i)) // moves forward in the index if it's forbidden
			i++;
		else if (ft_strstr(tunnels, parent))
		{
			lem->forbidden_array = add_elem_int_array(i, lem); // add the current index in tunnels so we don't reuse it
			return (1);
		}
		else
			i++;
	}
	return (0);
}

/*
**	This functions will find the needle in the haystack, then return
**	the other part of the haystack minus the middle character
**	dividing them.
*/

char	*needle_crop(const char *haystack, const char *needle)
{
	int i;
	int a;
	char *temp;

	i = 0;
	a = 0;
	temp = ft_strnew(ft_strlen(haystack) - ft_strlen(needle) - 1);
	while (haystack[i] != '\0')
	{
		if (needle[a] == '\0')
			return (NULL);
		while (haystack[a + i] == needle[a] && haystack[a + i] != '\0')
		{
			if (needle[a + 1] == '\0' && haystack[a + i + 1] != '\0')
				return ((char*)&haystack[i + ft_strlen(needle) + 1]);
			else if (needle[a + 1] == '\0' && haystack[a + i + 1] == '\0')
				return ((char*)temp);
			a++;
		}
		if (haystack[i] != '-')
			temp[i] = haystack[i];
		a = 0;
		i++;
	}
	return (NULL);
}
