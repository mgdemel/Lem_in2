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

int search_for_all_paths(lem)
{
    int j;
	int nbr;

	nbr = 0;
    j = 0;
    while (we find every possible path)
    {
		nbr += scan_for_path(lem, j);
        if (nbr > lem->nbr_paths)
            return (1);
        else 
            j++;
        return (0);
    }

 

}

	/*
	while (!(ft_strstr(lem->tunnels[i], lem->start_room_name)))
	{
		i++;
	}
	if (lem->tunnels[i][0] == lem->start_room_name)
		other_room = lem->tunnels[i][2];
	else
		other_room = lem->tunnels[i][0];
	*/
	/*
	while (lem->all_rooms->roomtype != 1)
        lem->all_rooms = lem->all_rooms->next;
	while (!(ft_strstr(lem->tunnels[i], lem->all_rooms->name)))
		i++;
	if (lem->tunnels[i][0] == lem->all_rooms->name[0])
		other_room = lem->tunnels[i][2];
	else
		other_room = lem->tunnels[i][0];
	i = 0;
	while (lem->all_rooms->roomtype != 3)
	{
		lem->all_rooms = lem->all_rooms->next;
		while (!(ft_strstr(lem->tunnels[i], lem->all_rooms->name)))
			i++;
		
	}
	*/
	end_room setup

    0-2 <- we are here
    2-3
    3-1

	while (lemallrooms node name != strstr end room name)
		while (tunnel)
			if (lemallrooms node name == strstr tunnelroom1)
				add(lemallrooms node name == strstr tunnelroom2) to path
						room1 -
					room2 tunnel =
					node1 = room1
						node2 = room2 if (lemallrooms node name == strstr tunnelroom2)
									add(lemallrooms node name == strstr tunnelroom3) to path
										room2 -
								room3 tunnel =
									node1 = room1
										node2 = room2
											node3 = room3 if (path includes start and end)
												init_path(path, lem);
}

	start room








while (tunnels[i]) != ft_strstr(lem->start_room_name) //get's us to the first tunnel in the list that mentions start room
    i++;
temp = piece of tunnel str that is the room connected to start room;
while (temp != name of end room)
    find from tunnels the first mention of temp.
    temp = piece of tunnel str that is the room connected to old temp;

