#include "../includes/lem_in.h"

int		roomname_scan(t_lem *lem, char *name, int start)
{
	int i;
	int j;
	int	amount;

	i = 0;
	amount = 0;
	while (lem->tunnels[i] != '\0')
	{
		j = 0;
		while (lem->tunnels[i][j] == name[j] || lem->tunnels[i][j] == '-')
			j++;
		if (lem->tunnels[i][j] == '-')
			amount++;
		i++;
	}
	return (amount - start);
}

void		maximum_paths(t_lem *lem)
{
	int	amount;

	amount = 0;
	amount += roomname_scan(lem, lem->start_room_name, 0); // finds the paths leading from start room
	lem->nbr_paths = amount;
}

char		*ft_strjoin_spc(char const *s1, char const *s2)
{
	int		i;
	int		j;
	int		len;
	char	*newstr;

	i = 0;
	j = 0;
	len = (ft_strlen((char *)s1) + ft_strlen((char *)s2)) + 1;
	if ((newstr = (char *)malloc(sizeof(char) * len + 1)))
	{
		while (s1[i] != '\0')
		{
			newstr[i] = s1[i];
			i++;
		}
		newstr[i] = " ";
		i++;
		while (s2[j] != '\0')
		{
			newstr[i + j] = s2[j];
			j++;
		}
		newstr[i + j] = '\0';
		return (newstr);
	}
	else
		return (NULL);
}

int	make_path(char *start_point, t_lem *lem)
{
	int i;
	
	i = 0;
	if (ft_strstr(lem->tunnels[i], start_point))
}



   r1-r2
-> start-r1
   r2-end


char	*ft_strstr(const char *haystack, const char *needle)
{
	int i;
	int a;

	i = 0;
	a = 0;
	if (needle[0] == '\0')
		return ((char*)haystack);
	while (haystack[i] != '\0')
	{
		if (needle[a] == '\0')
			return (NULL);
		while (haystack[a + i] == needle[a] && haystack[a + i] != '\0')
		{
			if (needle[a + 1] == '\0')
				return ((char*)&haystack[i + ft_strlen(needle) + 1]); // start-r1  needle = start
			else if ()
				return ((char*)&haystack[i - ft_strlen(needle)]); // start-r1 needle = r1
			a++;
		}
		a = 0;
		i++;
	}
	return (NULL);
}



int pathfinding(t_lem *lem, t_room *room)
{
	int i;
	t_path *new_path;
	t_path *path;
	new_path = NULL;
	path = NULL;
	i = 0;
	if (!(lem->all_paths = (s_path**)malloc(sizeof(s_path*)))) //allocates paths array of structs
		return (1);
	while (lem->tunnels[i])  // we go through all the tunnels
	{
		if (ft_strstr(lem->tunnels[i], lem->start_room_name)) // to find the start room links
			if(make_path(lem->tunnels[i], lem)) // when we've found a link we make a path
			{
				path = initialize_path(room);
				new_path = initialize_path(room);
				path->next = new_path;
				new_path->prev = path;
			}
	}
	/*
    while (j < 1)
    {
		if (nbr > lem->nbr_paths)
            return (1);
        else 
            j++;
		nbr += scan_for_path(lem, j);
        return (0);
    }
	*/
	return (0);
}

while (tunnels[i] != NULL)
{
	if (ft_strstr(tunnel[i], lem->start_room_name))
		if (make_path(tunnel[i]))
			lem->all_paths->next;
		
	else
		i++;
	
}

   r1-r2
   start-r1
-> r2-end