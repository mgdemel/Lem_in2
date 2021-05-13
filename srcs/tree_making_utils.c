#include "lem_in.h"

/*
**	Searching for parent links, taking any forbidden into account.
*/
int	find_parent_links(int parent, t_lem *lem)
{
	int	i;
	int	t;

	i = 0;
	t = 0;
	while (i < lem->nbr_tunnels)
	{
		if (lem->tunnel_dir[i][2] != 0)
			i++;
		else if (ft_strword(lem->tunnel_dir[i], lem->e_room_index))
			i++;
		else if (ft_strword(lem->tunnel_dir[i], parent))
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

/*
**	Returns a 1 if it finds the exact word in haystack 
**  that was in needle before or 
** 	after a '-' character.
*/

// CHANGE THE NAME OF THIS FUNCTION YOU DINGUS
int	ft_strword(int *haystack, int needle)
{
	if (haystack[0] == needle)
		return (haystack[1]);
	else if (haystack[1] == needle)
		return (haystack[0]);
	return (0);
}
