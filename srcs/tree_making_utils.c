#include "lem_in.h"

/*
**	Searching for parent links, taking any forbidden into account.
*/

int			find_parent_links(int parent, t_lem *lem)
{
	int i;
	int t;

	t = 0;
	i = 0;
	// if (parent == 2)
	//	print_tunnel_dir(lem->tunnel_directory, lem->nbr_tunnels);
	while (i < lem->nbr_tunnels)
	{
		if (lem->tunnel_directory[i][2] != 0)
			i++;
		else if (ft_strword(lem->tunnel_directory[i], lem->e_room_index))
			i++;
		else if (ft_strword(lem->tunnel_directory[i], parent))
		{
			t++;
			i++;
		}
		else
			i++;
		if (t > 1)
			return (1);
	}
	return (0);
}

void find_room_name(t_lem *lem, char *room_name, int row, int column)
{
	int i;
	int j;
	
	i = 0;
	j = 1;
	while (i < (lem->nbr_rooms + 1)) //searching for the index of the room name we are adding to the tunnel directory row
	{
		if (ft_strcmp(lem->room_directory[j], room_name) == 0) // need to keep track of what info we are pulling out of tunnels
			lem->tunnel_directory[row][column] = j;
		else
			j++;
		i++;
	}
}

void get_tunnel_int_arr(t_lem *lem)
{
	int i;
	int j;
	char **rooms;

	i = 0;
	j = 0;
	if (!(lem->tunnel_directory = (int**)malloc(sizeof(int*) * lem->nbr_tunnels)))
		ft_putendl("error");
	while (i < lem->nbr_tunnels)
	{
		if (!(lem->tunnel_directory[i] = (int*)malloc(sizeof(int) * 3)))
			ft_putendl("error");
		i++;
	}
	i = 0;
	while (i < lem->nbr_tunnels) //as long as there are tunnels to add to the directory
	{
		j = 0;
		rooms = ft_strsplit(lem->tunnels[i], '-');
		lem->tunnel_directory[i][2] = 0;
		while (j < 2) //as long as there are rooms to be added to the tunnel directory's row ...
		{
			find_room_name(lem, rooms[j], i, j);
			j++;
		}
		free(rooms[0]);
		free(rooms[1]);
		free(rooms);
		i++;
	}
	print_tunnel_dir(lem->tunnel_directory, lem->nbr_tunnels);
}
