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
	amount += roomname_scan(lem, lem->start_room_name, 0);
	while (lem->all_rooms)
	{
		amount += roomname_scan(lem, lem->all_rooms->name, 1);
		lem->all_rooms = lem->all_rooms->next;
	}
	lem->nbr_paths = amount;
}

t_path *init_path(t_lem *lem)
{
    t_path *valid_path;
	int i;

	i = 0;
	while (lem->all_rooms->roomtype != 1 || lem->all_rooms->roomtype != 3)
	{
		if (lem->all_rooms->roomtype == 1)
			valid_path->start_room = lem->all_rooms; //set the first room equal to the current room + all it's values after that loop!
		else if (lem->all_rooms->roomtype == 3)
			valid_path->end_room = lem->all_rooms; //set the end room equal to the current room + all it's values after that loop!
		else
		{
			valid_path->inbetween_rooms[i] = lem->all_rooms;
			lem->all_rooms = lem->all_rooms->next;
			i++;
		}
	}
    return(valid_path);
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

char *	find_path(char **tunnels, char *room_name)
{
	int 	i;
	char	*other_room;
	char *path;

	i = 0;
	while (!(ft_strstr(tunnels[i], room_name)))
		i++;
	if (tunnels[i][0] == room_name)
		ft_strcpy(other_room, tunnels[i][2]);
	else
		ft_strcpy(other_room, tunnels[i][0]);
	path = ft_strjoin_spc(room_name, other_room);
	return(path);
}

int scan_for_path(t_lem *lem, int j) //the outcome of this is an array of strs that are each composed of the names of all the rooms in a valid path, separated by a space
{
	int i;

	i = 1;
	if (!(lem->paths_found = (char**)malloc(sizeof(char*) * lem->nbr_paths))) //allocates paths_found array
		return (1);
	lem->paths_found[0] = find_path(lem->tunnels, lem->start_room_name); // puts the first path in the array
	while (!(ft_strcmp(lem->end_room_name, lem->paths_found[i]) || i <= lem->nbr_tunnels)) // puts the rest until the end
	{
		lem->paths_found[i] = find_path(lem->tunnels, lem->paths_found[i]);
		i++;
	}
	if (i <= lem->nbr_tunnels) 
	{
		find_path(lem->tunnels, lem->end_room_name);
   		lem->all_paths[j] = init_path(lem);
		return (0);
	}
	return (1);
}

int pathfinding(t_lem *lem)
{
    int j;
	int nbr;

	nbr = 0;
    j = -1;
	maximum_paths(lem);
    while (j < 1)
    {
		if (nbr > lem->nbr_paths)
            return (1);
        else 
            j++;
		nbr += scan_for_path(lem, j);
        return (0);
    }
	return (0);
}


path_function(char *path, char *room)
{

}