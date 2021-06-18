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

void	distance_sibling(t_lem *lem, int object, int add_reduce)
{
	int	i;

	i = 0;
	object = 1; // remove
	if (add_reduce == 1)
	{
		while (i < lem->nbr_tunnels)
		{
			if (lem->tunnel_dir[i][0] != lem->e_room_index
				&& lem->tunnel_dir[i][1] != lem->e_room_index
				&& lem->tunnel_dir[i][2] > 0)
				lem->tunnel_dir[i][2]++;
			// else if ((lem->tunnel_dir[i][0] == object       //  <------------------- Smth here is blocking too many tunnels.
			// 	|| lem->tunnel_dir[i][1] == object)         //  <------------------- See testy2 map: when parent is 1, child is 3, 
			// 	&& lem->tunnel_dir[i][2] == 0 && lem->tunnel_dir[i][3] == 0)  // <-- tunnel 3-4 is blocked during DISTANCE CHILD PLUS
			// 	lem->tunnel_dir[i][2] = 1;
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
				&& lem->tunnel_dir[i][2] == 0 && lem->tunnel_dir[i][3] == 0)
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

void	add_reduce_dead_end(t_lem *lem, int add_reduce)
{
	int i;

	i = 0;
	while (i < lem->nbr_tunnels)
	{
		if (lem->tunnel_dir[i][3] > 0)
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
	int i;

	tunnel = 0;
	//TEST//
	ft_printf("\nFIND FAMILY CALLED WITH PARENT: %d, CHILD: %d\n", parent->name, child->name);
	//TEST//
//	print_tunnel_dir(lem->tunnel_dir, lem->nbr_tunnels);
	i = find_parent_links(parent->name, lem, child->name, 0);
	lem->test_stopper++;
	ft_printf("child name: %d, parent name: %d i: %d, links found: %d\n", child->name, parent->name, i, lem->links_found);
	//if (lem->test_stopper == 10)
	//	exit(1);
	if (i >= 0 && lem->links_found > 1)
	{
		ft_printf("\nPRINTING TUNNELS: DISTANCE SIBLING PLUS FLAG\n");
	//	ft_printf("nbr_tunnels: %d\n", lem->nbr_tunnels);
	//	print_tunnel_dir(lem->tunnel_dir, lem->nbr_tunnels);
		lem->tunnel_dir[i][2] = 1;
		ft_printf("BLOCKED [%d][%d]\n", lem->tunnel_dir[i][0], lem->tunnel_dir[i][1]);
		lem->sib_name = make_sibling(child, parent, lem);
		lem->tunnel_dir[i][2] = 0;
		ft_printf("UNBLOCKED [%d][%d]\n", lem->tunnel_dir[i][0], lem->tunnel_dir[i][1]);
		lem->sib_name = 0;
	}
	if (child->name != lem->e_room_index)
	{
		i = find_parent_links(parent->name, lem, child->name, 1);
		ft_printf("i:%d\n", i);
		ft_printf("BLOCKED [%d][%d]\n", lem->tunnel_dir[i][0], lem->tunnel_dir[i][1]);
		lem->tunnel_dir[i][2] = -1;
		tunnel = make_child(child, lem);
		ft_printf("UNBLOCKED [%d][%d]\n", lem->tunnel_dir[i][0], lem->tunnel_dir[i][1]);
		ft_printf("child->name:%d\n", child->name);
		lem->tunnel_dir[i][2] = 0;
	}
	if (lem->links_found == 0)
	{
		ft_printf("\n\n**********FOUND DEAD END**********\n\n");
		child = tree_init(lem, parent);

	}
}

int	make_sibling(t_tree *child, t_tree *parent, t_lem *lem)
{
	t_tree	*sibling;
	int		i;
	int		j;

	j = 0;
	i = 0;
	//TEST//
	ft_printf("MAKE_SIB CALLED WITH PARENT: %d\n", parent->name);
	//TEST//
	sibling = tree_init(lem, parent);
	child->sib = sibling;
	while (j < lem->nbr_tunnels)
	{
		if (lem->tunnel_dir[j][2] != 0 || lem->tunnel_dir[j][3] != 0)
			j++;
		// else if (ft_strword(lem->tunnel_dir[j], lem->e_room_index))
		// 	j++;
		else if (ft_strword(lem->tunnel_dir[j], parent->name))
		{
			sibling->name = ft_strword(lem->tunnel_dir[j], parent->name);
			sibling->parent = parent;
		//	lem->tunnel_dir[j][2] = 1;
			//TEST//
			ft_printf("\nPARENT NAME: %d, SIBLING NAME: %d\n", parent->name, sibling->name);
			//TEST//
			break ;
		}
		else
			j++;
	}
	if (sibling->name != 0 && sibling->name == lem->e_room_index)
	{
		lem->total_paths++;
		ft_printf("\n\n\nFOUND END IN MAKE SIBLING RECURSION STOPS HERE\n");
		ft_printf("Sibling:%d\nParent:%d\n", sibling->name, parent->name);
	//	print_tunnel_dir(lem->tunnel_dir, lem->nbr_tunnels);
	//	print_tunnel_dir(lem->tunnel_dir, lem->nbr_tunnels);
	}
	if (sibling->name != 0)
		find_family(lem, parent, sibling);
	if (sibling->name == 0)   // sibling name should never be 0 as we already check for multiple in find family
	{						 // so this test was to see if too much is blocked, this can be removed once we have everything working
	//	print_tunnel_dir(lem->tunnel_dir, lem->nbr_tunnels);
		ft_printf("WRONG\n");
		exit (1);
	}
	return (sibling->name);
}

int	make_child(t_tree *parent, t_lem *lem)
{
	t_tree *child;
	int	i;
	int	j;

	j = 0;
	i = 0;
	//TEST//
	ft_printf("MAKE_CHILD CALLED WITH PARENT: %d\n", parent->name);
	//TEST//
	child = tree_init(lem, parent);
	parent->child = child;
	while (j < lem->nbr_tunnels)
	{
		if (lem->tunnel_dir[j][2] == 0 && lem->tunnel_dir[j][3] == 0)
		{
			if (ft_strword(lem->tunnel_dir[j], parent->name))
			{
				child->name = ft_strword(lem->tunnel_dir[j], parent->name);
				child->parent = parent;
					//TEST//
					ft_printf("\nPARENT NAME: %d, CHILD NAME: %d\n", parent->name, child->name);
					//TEST//
				break ;
			}
		}
		j++;
	}
	if (child->name != 0 && child->name != lem->e_room_index)
	{
		find_family(lem, parent, child);
	}
	if (child->name != 0 && child->name == lem->e_room_index)
	{
		lem->total_paths++;
		ft_printf("\n\n\nFOUND THE END IN MAKECHILD\n");
		ft_printf("Child:%d\nParent:%d\n", child->name, parent->name);
	//	print_tunnel_dir(lem->tunnel_dir, lem->nbr_tunnels);
	}
	if (child->name == 0)
	{
		lem->end_trigger = 1;
		ft_printf("\n\n\n***----->FOUND DEAD END IN MAKECHILD<-----***\n");
		ft_printf("Child:%d\nParent:%d\n", child->name, parent->name);
	//	print_tunnel_dir(lem->tunnel_dir, lem->nbr_tunnels);
	}
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
//	print_tunnel_dir(lem->tunnel_dir, lem->nbr_tunnels);
}
