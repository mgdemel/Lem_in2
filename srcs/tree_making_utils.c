#include "lem_in.h"

/*
**	Searching for parent links, taking any forbidden into account.
*/

int find_parent_links(int parent, t_lem *lem)
{
	int i;
	int t;

	i = 0;
	t = 0;
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
	}
	i = 0;
	if (t > 1)
		return (t);
	return (0);
}

