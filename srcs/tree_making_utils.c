#include "lem_in.h"

/*
**	Searching for parent links, taking any forbidden into account.
*/

int find_parent_links(int parent, t_lem *lem)
{
	int i;
	int t;
	int delete; //delete
	int count;
//	int	*tmp;
//	int	tmp_i;

//	tmp_i = 0;
//	tmp = malloc(sizeof(int) * lem->nbr_rooms);
	// while (tmp_i < lem->nbr_rooms)
	// {
	// 	tmp[tmp_i] = 0;
	// 	tmp_i++;
	// }
//	tmp_i = 0;
	count = 0;
	delete = 0;
	t = 0;
	i = 0;
	// if (parent == 2)
	//ft_printf("\n");
	while (delete < lem->nbr_tunnels)
	{
		if (lem->tunnel_directory[delete][2] != 0)
			count++;
		delete ++;
	}
	//ft_printf("count:%d\n", count);

	//print_tunnel_dir(lem->tunnel_directory, lem->nbr_tunnels);
	//ft_printf("\nNEXT\n");
	while (i < lem->nbr_tunnels)
	{
		if (lem->tunnel_directory[i][2] != 0)
			i++;
		else if (ft_strword(lem->tunnel_directory[i], lem->e_room_index))
			i++;
		else if (ft_strword(lem->tunnel_directory[i], parent))
		{
			// if (count > 1744)
			// {
			// 	ft_printf("parent:%d\n", parent);
			// 	ft_printf("i:%d\n", i);
			// 	ft_printf("tunnel[0]:%d\n", lem->tunnel_directory[i][0]);
			// 	ft_printf("tunnel[1]:%d\n", lem->tunnel_directory[i][1]);
			// //	ft_printf("\n");
			//}
		//	else
		//		ft_printf("count is low\n");
	//		tmp[tmp_i] = ft_strword(lem->tunnel_directory[i], parent);
	//		tmp_i++;
	//		ft_printf("t:%d\n", t);
			t++;
	//		ft_printf("increased t:%d\n\n", t);
			i++;
		}
		else
			i++;
	}
//	tmp_i = 0;
	i = 0;
	// while (tmp[tmp_i] != 0)
	// {
	// 	i = 0;
	// 	while (tmp[i] != 0)
	// 	{
	// 		if (tmp[tmp_i] == tmp[i] && tmp_i != i)
	// 			t--;
	// 		i++;
	// 	}
	// 	tmp_i++;
	// }
	if (t > 1)
	{
		//	ft_printf("found %d siblings\n", t - 1);
		return (t);
	}
	return (0);
}

