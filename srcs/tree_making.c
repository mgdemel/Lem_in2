#include "lem_in.h"

void	distance_special(t_lem *lem, int sibling)
{
	int	i;

	i = 0;
	while (i < lem->nbr_tunnels)
	{
		if ((lem->tunnel_dir[i][0] == sibling || lem->tunnel_dir[i][1] == sibling) && lem->tunnel_dir[i][2] == 0)
			lem->tunnel_dir[i][2] = -1;
		i++;
	}
}

//if (lem->tunnel_dir[i][0] == lem->e_room_index || lem->tunnel_dir[i][1] == lem->e_room_index) (?)
/*
1
|
2------3------4------5
              |      |
			  10	 6
					 |
					 7
					 |
					 8

When going back up from 8 we set a trigger and place 1 in tunnel_dir[3]
lem->end_trigger = 1;
8-1 = 1
7-6 = 1
6-5 = 1
when moving left again remove trigger
lem->end_trigger = 0
*/

void	distance_sibling(t_lem *lem, int object, int add_reduce)
{
	int	i;

	i = 0;
	if (add_reduce == 1)
	{
		while (i < lem->nbr_tunnels)
		{
			if (lem->tunnel_dir[i][0] != lem->e_room_index
				&& lem->tunnel_dir[i][1] != lem->e_room_index
				&& lem->tunnel_dir[i][2] > 0)
				lem->tunnel_dir[i][2]++;
			else if ((lem->tunnel_dir[i][0] == object
				|| lem->tunnel_dir[i][1] == object)
				&& lem->tunnel_dir[i][2] == 0 && lem->tunnel_dir[i][3] == 0)
				lem->tunnel_dir[i][2] = 1;
			i++;
		}
	}
	else if (add_reduce == -1)
	{
		while (i < lem->nbr_tunnels)
		{
			if (lem->tunnel_dir[i][2] > 0)
				lem->tunnel_dir[i][2]--;
			i++;
		}
	}
}

void	distance_child(t_lem *lem, int object, int add_reduce)
{
	int	i;

	i = 0;
	if (add_reduce == 1)
	{
		while (i < lem->nbr_tunnels)
		{
			if (lem->tunnel_dir[i][2] < 0)
				lem->tunnel_dir[i][2]--;
			else if ((lem->tunnel_dir[i][0] == object
				|| lem->tunnel_dir[i][1] == object)
				&& lem->tunnel_dir[i][2] >= 0 && lem->tunnel_dir[i][3] == 0)
				lem->tunnel_dir[i][2] = -1;
			i++;
		}
	}
	else if (add_reduce == -1)
	{
		while (i < lem->nbr_tunnels)
		{
			if (lem->tunnel_dir[i][2] < 0)
				lem->tunnel_dir[i][2]++;
			i++;
		}
	}
}

void	distance_special2(t_lem *lem, int tunnel, int add_reduce)
{
	int i;
	int checker;

	checker = 0;
	i = 0;
	if (lem->end_trigger2 != 0)
	{
		if (add_reduce > 0)
			lem->end_trigger2++;
		else
			lem->end_trigger2--;
	}
	ft_printf("Started Distance_Special2\n");
	ft_printf("tunnel: %d\nadd_reduce: %d\n", tunnel, add_reduce);
	ft_printf("lem->tunnel_dir[tunnel][3]%d\n", lem->tunnel_dir[tunnel][3]);
	ft_printf("end_trigger2:%d\n", lem->end_trigger2);
	if ((lem->end_trigger2 == 1 || lem->end_trigger2 == 0) && add_reduce < 0 && lem->tunnel_dir[tunnel][3] == 0)
		lem->tunnel_dir[tunnel][3] = 1;
	// while (i < lem->nbr_tunnels)
	// {
	// 	if (lem->tunnel_dir[i][3] != 0)
	// 	{
	// 		if (add_reduce > 0)
	// 			lem->tunnel_dir[i][3]++;
	// 		else if (tunnel != i)
	// 			lem->tunnel_dir[i][3]--;
	// 	}	
	// 	i++;
	// }
	i = 0;
	ft_printf("nbr_tunnels: %d\n", lem->nbr_tunnels);
	print_tunnel_dir(lem->tunnel_dir, lem->nbr_tunnels);
	while (i < lem->nbr_tunnels)
	{
		if (lem->tunnel_dir[i][3] != 0)
		{
			checker++;
		}
		i++;
	}
	ft_printf("checker:%d\n", checker);

//  |
// 10---1
// 	    |
//   	2---3
//  	|   |
//  	4   DE
	if (checker == 0)
	{
		lem->end_trigger = 0;
		lem->end_trigger2 = 0;
		ft_printf("nbr_tunnels LAST: %d\n", lem->nbr_tunnels);
		print_tunnel_dir(lem->tunnel_dir, lem->nbr_tunnels);
		ft_printf("EXIT\n");
		exit(1);
	}
}

void	add_reduce_dead_end(t_lem *lem, int add_reduce)
{
	int i;

	i = 0;
	while (i < lem->nbr_tunnels)
	{
		if (lem->tunnel_dir[i][3] != 0)
		{
			if (add_reduce > 0)
				lem->tunnel_dir[i][3]++;
			else
				lem->tunnel_dir[i][3]--;
		}
		i++;
	}
}

void	find_family(t_lem *lem, t_tree *parent, t_tree *child)
{
	int tunnel;

	tunnel = 0;
	if (find_parent_links(parent->name, lem) > 1)
	{
		add_reduce_dead_end(lem, 1);
		remove_deadends(lem, 0, 0);
		ft_printf("Making sibling\n");
		distance_sibling(lem, child->name, 1);
		lem->sib_name = make_sibling(child, parent, lem);
	//	if (lem->end_trigger == 1 && lem->end_trigger2 == 0)
	//		lem->end_trigger2 = 1;
		distance_sibling(lem, 0, -1);
		distance_special(lem, lem->sib_name);
		lem->sib_name = 0;
		add_reduce_dead_end(lem, -1);
	}
	if (child->name != lem->e_room_index)
	{
		add_reduce_dead_end(lem, 1);
		remove_deadends(lem, 0, 0);
		ft_printf("Making child\n");
		distance_child(lem, parent->name, 1);
		// if (lem->end_trigger == 1/* && tunnel != lem->nbr_tunnels*/)
		// 	distance_special2(lem, tunnel, 1);
		tunnel = make_child(child, lem);
	//	if (tunnel != 0)
		distance_child(lem, 0, -1);
	
		// if (tunnel < lem->nbr_tunnels && lem->end_trigger == 1/* && tunnel != lem->nbr_tunnels*/)
		// 	distance_special2(lem, tunnel, -1);
		add_reduce_dead_end(lem, -1);
	}
}

int	make_sibling(t_tree *child, t_tree *parent, t_lem *lem)
{
	t_tree	*sibling;
	int		i;
	int		j;

	j = 0;
	i = 0;
	sibling = tree_init(lem, parent);
	child->sib = sibling;
//	ft_printf("nbr_tunnels: %d\n", lem->nbr_tunnels);
//	print_tunnel_dir(lem->tunnel_dir, lem->nbr_tunnels);
	while (j < lem->nbr_tunnels)
	{
		if (lem->tunnel_dir[j][2] != 0 || lem->tunnel_dir[j][3] != 0)
			j++;
		else if (ft_strword(lem->tunnel_dir[j], lem->e_room_index))
			j++;
		else if (ft_strword(lem->tunnel_dir[j], parent->name))
		{
			sibling->name = ft_strword(lem->tunnel_dir[j], parent->name);
		//	ft_printf("sibling:%d\n", sibling->name);
			sibling->parent = parent;
			break ;
		}
		else
			j++;
	}
	if (sibling->name != 0)
		find_family(lem, parent, sibling);
	return (sibling->name);
}

int	make_child(t_tree *parent, t_lem *lem)
{
	t_tree *child;
	int	i;
	int	j;

	j = 0;
	i = 0;
	child = tree_init(lem, parent);
	parent->child = child;
	while (j < lem->nbr_tunnels)
	{
		if (lem->tunnel_dir[j][2] == 0 && lem->tunnel_dir[j][3] == 0)
		{
			if (ft_strword(lem->tunnel_dir[j], parent->name))
			{
				child->name = ft_strword(lem->tunnel_dir[j], parent->name);
			//	ft_printf("child:%d with parent:%d\n", child->name, parent->name);
				child->parent = parent;
				break ;
			}
		}
		j++;
	}
	if (child->name != 0 && child->name != lem->e_room_index)
		find_family(lem, parent, child);
	if (child->name != 0 && child->name == lem->e_room_index)
		lem->total_paths++;
	if (child->name == 0)
		lem->end_trigger = 1;
//	ft_printf("j:%d\n", j);
	return (child->name);
}

void	tree_creation(t_lem *lem)
{
	int	i;

	i = 0;
	lem->test_index = 0; // delete
	lem->tree = head_tree_init(lem, lem->s_room_index);
	make_child(lem->tree, lem);
	ft_printf("\nPRINTING TUNNELS: END OF TREE_CREATION\n");
	ft_printf("nbr_tunnels: %d\n", lem->nbr_tunnels);
	print_tunnel_dir(lem->tunnel_dir, lem->nbr_tunnels);
//	exit (1);
}
