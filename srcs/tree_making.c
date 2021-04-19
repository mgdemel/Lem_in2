#include "lem_in.h"

int ft_blocked_index(int tunnels, int *forbidden_array, int j)
{
	int i;

	i = 0;
	while (i < tunnels)
	{
		if (j == forbidden_array[i])
			return (1);
		i++;
	}
	return (0);
}

int sibling_name(t_tree *parent, t_lem *lem, int *forb)
{
	int j;

	j = 0;
	while (j < lem->nbr_tunnels)
	{
		if (ft_strword(lem->tunnel_directory[j], parent->name))
		{
			if (ft_blocked_index(lem->nbr_tunnels, forb, j) == 0)
				return (needle_crop(lem->tunnel_directory[j], parent->name));
		}
		j++;
	}
	return (0);
}

void distance_special(t_lem *lem, int sibling)
{
	int i;

	i = 0;
	while (i < lem->nbr_tunnels)
	{
		if ((lem->tunnel_directory[i][0] == sibling || lem->tunnel_directory[i][1] == sibling) && lem->tunnel_directory[i][2] == 0)
			lem->tunnel_directory[i][2] = -1;
		i++;
	}
}

void distance_handling(t_lem *lem, int neg_pos, int object, int add_reduce) //neg_pos == -1/1 //add_reduce == -1/1
{
	int i;

	i = 0;
	if (add_reduce == 1)
	{
		while (i < lem->nbr_tunnels)
		{
			if (neg_pos < 0 && lem->tunnel_directory[i][2] < 0)
				lem->tunnel_directory[i][2]--;
			if (neg_pos > 0 && lem->tunnel_directory[i][2] > 0)
				lem->tunnel_directory[i][2]++;
			if ((lem->tunnel_directory[i][0] == object || lem->tunnel_directory[i][1] == object) && lem->tunnel_directory[i][2] == 0)
				lem->tunnel_directory[i][2] = neg_pos;
			i++;
		}
	}
	else if (add_reduce == -1)
	{
		while (i < lem->nbr_tunnels)
		{
			if (neg_pos < 0 && lem->tunnel_directory[i][2] < 0)
				lem->tunnel_directory[i][2]++;
			if (neg_pos > 0 && lem->tunnel_directory[i][2] > 0)
				lem->tunnel_directory[i][2]--;
			i++;
		}
	}
}

void find_family(t_lem *lem, int *forb, t_tree *parent, t_tree *child, int delete2)
{
	int *tmp;
	int found_sibling;

	found_sibling = 0;
	tmp = NULL;

	if (find_parent_links(parent->name, lem, forb))
	{
		lem->test_index++;
		while (delete2 <= 5)
		{
			//		ft_printf("-");
			delete2++;
		}
		tmp = ft_newintarr(forb, lem->nbr_tunnels);
		add_elem_int_array(tmp, lem, parent->name, 1);
		add_elem_int_array(tmp, lem, child->name, 0);
		ft_printf("UNCHANGED\n");
		ft_printf("sibling->name:%d\n", child->name);
		print_tunnel_dir(lem->tunnel_directory, lem->nbr_tunnels);
		distance_handling(lem, 1, child->name, 1);
		ft_printf("CHANGED\n");
		print_tunnel_dir(lem->tunnel_directory, lem->nbr_tunnels);
		lem->sib_name = make_sibling(child, parent, lem, tmp);
		distance_handling(lem, 1, 0, -1);
		distance_special(lem, lem->sib_name);
		if (lem->sib_name != 0)
			add_elem_int_array(forb, lem, lem->sib_name, 0);
		lem->sib_name = 0;
		free(tmp);
	}
	if (child->name != lem->e_room_index)
	{
		add_elem_int_array(forb, lem, parent->name, 1);
		//	ft_printf("\n");
		ft_printf("UNCHANGED\n");
		ft_printf("parent->name:%d\n", parent->name);
		print_tunnel_dir(lem->tunnel_directory, lem->nbr_tunnels);
		distance_handling(lem, -1, parent->name, 1);
		ft_printf("CHANGED\n");
		print_tunnel_dir(lem->tunnel_directory, lem->nbr_tunnels);
		make_child(child, lem, forb);
		distance_handling(lem, -1, 0, -1);
		ft_printf("CHILD:%d\n", child->name);
		if (lem->total_paths == 5)
		{
			print_tunnel_dir(lem->tunnel_directory, lem->nbr_tunnels);
			exit(1);
		}
	}

	// if (find_parent_links(parent->name, lem, forb))
	// {
	// 	lem->test_index++;
	// 	while (delete2 <= 5)
	// 	{
	// 		ft_printf("-");
	// 		delete2++;
	// 	}
	// //	found_sibling = 1;
	// 	tmp = ft_newintarr(forb, lem->nbr_tunnels);
	// 	add_elem_int_array(forb, lem, parent->name, 1);
	// 	add_elem_int_array(forb, lem, child->name, 0);
	// 	add_elem_int_array(forb, lem, make_sibling(child, parent, lem, forb), 0); // lem->sib_name = sibling_name(parent, lem, tmp);
	// 	if (lem->sib_name != 0)
	// 		add_elem_int_array(tmp, lem, lem->sib_name, 0);
	// 	lem->sib_name = 0;
	// }
	// if (child->name != lem->e_room_index)
	// {
	// 	add_elem_int_array(tmp, lem, parent->name, 1);
	// 	ft_printf("\n");
	// 	make_child(child, lem, tmp);
	// 	// if (found_sibling == 1)
	// 	// {
	// 	// 	lem->sib_name = make_sibling(child, parent, lem, tmp);
	// 	// 	free(tmp);

	// 	// }
	// }
}

int make_sibling(t_tree *child, t_tree *parent, t_lem *lem, int *forb)
{
	t_tree *sibling;
	int i;
	int j;
	int delete;
	int delete2;

	delete2 = 0;
	lem->making_sibling = 1;
	j = 0;
	i = 0;
	sibling = tree_init(parent);
	child->sib = sibling;
	while (j < lem->nbr_tunnels)
	{
		if (ft_strword(lem->tunnel_directory[j], parent->name))
		{
			if (ft_blocked_index(lem->nbr_tunnels, forb, j) == 0)
			{
				sibling->name = needle_crop(lem->tunnel_directory[j], parent->name);
				delete = sibling->name;
				while (delete != 0)
				{
					delete = delete / 10;
					delete2++;
				}
				ft_printf("%d", sibling->name);
				sibling->parent = parent;
				break;
			}
		}
		j++;
	}
	if (sibling->name != 0 && lem->total_paths < lem->stopper)
		find_family(lem, forb, parent, sibling, delete2);
	lem->test_index--;
	return (sibling->name);
}

void make_child(t_tree *parent, t_lem *lem, int *forbidden_array)
{
	t_tree *child;
	int i;
	int j;
	int test_delete;
	int delete;
	int delete2 = 0;

	lem->ended = 0;
	test_delete = lem->test_index;
	j = 0;
	i = 0;
	delete = 0;
	while (test_delete > 1)
	{
		ft_printf("|     ");
		test_delete--;
	}
	ft_printf("|\n");
	while (test_delete < lem->test_index)
	{
		ft_printf("|     ");
		test_delete++;
	}
	lem->making_sibling = 0;
	child = tree_init(parent);
	parent->child = child;
	while (j < lem->nbr_tunnels)
	{
		if (ft_strword(lem->tunnel_directory[j], parent->name))
		{
			if (ft_blocked_index(lem->nbr_tunnels, forbidden_array, j) == 0)
			{
				child->name = needle_crop(lem->tunnel_directory[j], parent->name);
				delete = child->name;
				while (delete > 0)
				{
					delete = delete / 10;
					delete2++;
				}
				ft_printf("%d", child->name);
				child->parent = parent;
				break;
			}
		}
		j++;
	}
	// if (child->name == NULL || ft_strcmp(child->name, lem->e_room_name) == 0)
	// {
	// 	ft_printf("FOUND END ROOM\n");
	// 	exit(1);
	// }
	if (child->name != 0 && child->name != lem->e_room_index && lem->total_paths < lem->stopper)
		find_family(lem, forbidden_array, parent, child, delete2);
	if (child->name != 0 && child->name == lem->e_room_index)
	{
		lem->total_paths++;
	}
	//	if (lem->ended == 1)
	//	{
	///		ft_printf("\n");
	//	while (test_delete > 1)
	//	{
	//		ft_printf("|     ");
	//		test_delete--;
	//	}
	//	}
	if (child->name == 0 || child->name == lem->e_room_index)
	{
		lem->ended = 1;
		ft_printf("E");
	}
	//	child->child = tree_init(child);
	//ft_printf("found end with name:%s\n", child->name);
	//ft_printf("WANBDHAWKJFAKJFAKJFSAJKDJW:AK:DWAK:DWJKDJWKA:KADJWJKDWAJDWAJKDWJKDAWJK:WJ\n");
}

int tree_creation(t_lem *lem)
{
	int *forbidden_array;
	int i;
	int c;

	c = 0;
	i = 0;
	lem->making_sibling = 0;
	lem->test_index = 1;
	ft_printf("\n\n<--****STARTING TREE MAKING****-->\n\n");
	ft_printf("Total of tunnels:%d\n", lem->nbr_tunnels);
	ft_printf("Total of rooms:%d\n\n", lem->nbr_rooms);
	if (!(forbidden_array = (int *)malloc(sizeof(int) * (lem->nbr_tunnels))))
		return (1);
	while (i < (lem->nbr_tunnels))
	{
		forbidden_array[i] = -1;
		i++;
	}
	lem->tree = head_tree_init(lem->start_room_index);
	ft_printf("%d\n", lem->start_room_index);
	make_child(lem->tree, lem, forbidden_array);
	free(forbidden_array);
	ft_printf("\n\n");
	return (0);
}
