#include "../includes/lem_in.h"



/*
**	Scans the array if the number i exists, MOVE TO UTILS
*/
int scan_forbidden(int *array, int i, t_lem *lem)
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
** Adds an element onto the int array, UTILS FUNCTION
*/

int *add_elem_int_array(int *forbidden_array, t_lem *lem, char *block_name, int parent)
{
	int i;
	int j;
	int *new;

	j = 0;
	i = 0;
	//ft_printf("parent is %s\nsibling is %s\n", parent, sibling);
	if (!(new = (int*)malloc(sizeof(int) * (lem->nbr_tunnels))))
		return (NULL);
	while (i < (lem->nbr_tunnels))
	{
		new[i] = forbidden_array[i];
		i++;
	}
	i = 0;
	while (i < lem->nbr_tunnels)
	{
		if (scan_forbidden(new, i, lem) == 1) // moves forward in the index if it's forbidden
			i++;
		else if (ft_strstr(lem->tunnels[i], block_name))
		{
			while (new[j] > -1)
				j++;
			new[j] = i;
			i++;
			if (parent == 1)
				return (new);
		}
		else
			i++;
	}
	//free_int_array(forbidden_array, lem->nbr_tunnels);
	return (new);
}

int find_parent_links(char *parent, t_lem *lem, int *forbidden_array) //returns the amount of hits of a room name found in tunnels
{
	int i;
	int t;

	t = 0;
	i = 0;
	while (i < lem->nbr_tunnels)
	{
		if (scan_forbidden(forbidden_array, i, lem) == 1) // moves forward in the index if it's forbidden
			i++;
		//if (lem->sibling_array == child/parent)
			// make sibling (7.b)
		else if (ft_strstr(lem->tunnels[i], parent))
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

/*
**	This functions will find the needle in the haystack, then return
**	the other part of the haystack minus the middle character
**	dividing them.
*/

char *needle_crop(const char *haystack, const char *needle)
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
			{
			//	free(temp);
				ft_printf("test1\n");
				return ((char *)&haystack[i + ft_strlen(needle) + 1]);
			}
			else if (needle[a + 1] == '\0' && haystack[a + i + 1] == '\0')
			{
				ft_printf("test2\n");
				return ((char *)temp);
			}
			a++;
		}
		if (haystack[i] != '-')
			temp[i] = haystack[i];
		a = 0;
		i++;
	}
	free(temp);
	return (NULL);
}