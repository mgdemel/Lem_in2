#include "../includes/lem_in.h"



t_path *init_path(char **path, t_lem *lem)
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

char *	find_path(char **tunnels, char *room_name)
{
	int 	i;
	char	*other_room;

	i = 0;
	while (!(ft_strstr(tunnels[i], room_name)))
		i++;
	if (tunnels[i][0] == room_name)
		ft_strcpy(other_room, tunnels[i][2]);
	else
		ft_strcpy(other_room, tunnels[i][0]);
}

int scan_for_path(t_lem *lem, int j)
{
	int 	i;
	char	**path;

	i = 1;
	path[0] = find_path(lem->tunnels, lem->start_room_name);
	while (!(ft_strcmp(lem->end_room_name, path[i]) || i <= lem->nbr_tunnels))
	{
		path[i] = find_path(lem->tunnels, path[i]);
		i++;
	}
	if (i <= lem->nbr_tunnels)
	{
		find_path(lem->tunnels, lem->end_room_name);
   		lem->all_paths[j] = init_path(path, lem);
		return (0);
	}
	return (1);
}

int search_for_all_paths(t_lem *lem)
{
    int j;
	int nbr;

	nbr = 0;
    j = 0;
    while (j < 1)
    {
		nbr += scan_for_path(lem, j);
        if (nbr > lem->nbr_paths)
            return (1);
        else 
            j++;
        return (0);
    }
	return (0);
}
