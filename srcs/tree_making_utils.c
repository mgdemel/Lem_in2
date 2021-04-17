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

int			add_elem_int_array(int *forb, t_lem *lem, int block, int parent)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while (i < lem->nbr_tunnels)
	{
		if (scan_forbidden(forb, i, lem) == 1)
			i++;
		else if (ft_strword(lem->tunnel_directory[i], block))
		{
			ft_printf("/HWAFHFAWHFAHFHAHFHFWAHFAW");
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

// change parent to int
int			find_parent_links(int parent, t_lem *lem, int *forbidden_array)
{
	int i;
	int t;

	t = 0;
	i = 0;
	while (i < lem->nbr_tunnels)
	{
		if (scan_forbidden(forbidden_array, i, lem) == 1)
			i++;
		else if (ft_strword(lem->tunnel_directory[i], lem->e_room_index)) // change to e_room_name_num or something
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
		if (!(lem->tunnel_directory[i] = (int*)malloc(sizeof(int) * 2)))
			ft_putendl("error");
		i++;
	}
	i = 0;
	while (i < lem->nbr_tunnels) //as long as there are tunnels to add to the directory
	{
		j = 0;
		rooms = ft_strsplit(lem->tunnels[i], '-');
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
}
