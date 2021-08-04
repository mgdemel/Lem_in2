#include "lem_in.h"

// int	find_parent_links2(t_lem *lem, int parent, int child, int save)
// {
// 	int	tunnel;

// 	tunnel = lem->t_index - 1;
// 	while (tunnel > 0)
// 	{
// 		if (lem->tunnel_dir[tunnel][2] != 0 || lem->tunnel_dir[tunnel][3] != 0)
// 			tunnel--;
// 		else if (haystack_finder(lem->tunnel_dir[tunnel], parent))
// 		{
// 			if (haystack_finder(lem->tunnel_dir[tunnel], child))
// 			{
// 				save = tunnel;
// 				if (lem->siborchild == 1)
// 					return (save);
// 			}
// 			lem->links_found++;
// 			tunnel--;
// 		}
// 		else
// 			tunnel--;
// 	}
// 	return (save);
// }

int	find_parent_links(int parent, t_lem *lem, int child, int i)
{
	int	save;

	save = -1;
	lem->links_found = 0;
	while (i < lem->nbr_tunnels)
	{
		if (lem->tunnel_dir[i][2] != 0 || lem->tunnel_dir[i][3] != 0)
			i++;
		else if (haystack_finder(lem->tunnel_dir[i], parent))
		{
			if (haystack_finder(lem->tunnel_dir[i], child))
			{
				save = i;
				if (lem->siborchild == 1)
					return (save);
			}
			lem->links_found++;
			i++;
		}
		else
			i++;
	}
	//save = find_parent_links2(lem, parent, child, save);
	return (save);
}

/*
**	Returns a 1 if it finds the exact word in haystack 
**  that was in needle before or 
** 	after a '-' character.
*/

int	haystack_finder(int *haystack, int needle)
{
	if (haystack[0] == needle)
		return (haystack[1]);
	else if (haystack[1] == needle)
		return (haystack[0]);
	return (0);
}
