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


// s1234-s12346 -> needle = s1234

// if (needle[i] == haystack[i])
// 	while(needle[i] == haystack[i])
// 		i++;
// 	i++;
// 	while(haystack[i] != '\0')
// 		new[j] = haystack[i];
// 		i++;
// 		j++;
// else
// 	while (haystack[i] != '-')
// 		new[j] = haystack[i];

// roomnbr1-s    needle roomnbr1

// while (haystack[i] != '-')  
// 	len++;
// malloc temp to len
// while (haystack[i] != '-')      //s-ri
// 	temp[i] = haystack[i]       //s
// 	if (ft_strcmp(temp, needle) == 0)
// 	//needle is at the start of the string
// else
// 	free(temp)
// 	while(haystack[i] != '\0')
// 		len++
// 	malloc tem to len
// 		temp[i] = remainder of str up until \0
// 	return(temp)
	
char *needle_crop(char *haystack, char *needle)
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
	return(ret);
}

// char *needle_crop(const char *haystack, const char *needle)
// {
// 	int i;
// 	int a;
// 	char *temp;

// 	i = 0;
// 	a = 0;
// 	temp = ft_strnew(ft_strlen(haystack) - ft_strlen(needle) - 1);
// 	while (haystack[i] != '\0')
// 	{
// 		if (needle[a] == '\0')
// 			return (NULL);
// 		while (haystack[a + i] == needle[a] && haystack[a + i] != '\0')
// 		{
// 			if (needle[a + 1] == '\0' && haystack[a + i + 1] != '\0')
// 			{
// 				temp = ft_strdup(&haystack[i + ft_strlen(needle) + 1]);
// 				return (temp);
// 			}
// 			else if (needle[a + 1] == '\0' && haystack[a + i + 1] == '\0')
// 				return (temp);
// 			a++;
// 		}
// 		if (haystack[i] != '-')
// 			temp[i] = haystack[i];
// 		a = 0;
// 		i++;
// 	}
// 	free(temp);
// 	return (NULL);
// }