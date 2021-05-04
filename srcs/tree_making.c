#include "lem_in.h"

void distance_special(t_lem *lem, int sibling)
{
	int i;

	i = 0;
	while (i < lem->nbr_tunnels)
	{
		if ((lem->tunnel_directory[i][0] == sibling || lem->tunnel_directory[i][1] == sibling) && lem->tunnel_directory[i][2] == 0)
		{
			lem->tunnel_directory[i][2] = -1;
			lem->tunnel_directory[i][3] = 1;
		}
		i++;
	}
}

void distance_sibling(t_lem *lem, int object, int add_reduce)
{
	int i;

	i = 0;
	if (add_reduce == 1)
	{
		while (i < lem->nbr_tunnels)
		{
			if (lem->tunnel_directory[i][0] != lem->e_room_index && lem->tunnel_directory[i][1] != lem->e_room_index && lem->tunnel_directory[i][2] > 0)
				lem->tunnel_directory[i][2]++;
			else if ((lem->tunnel_directory[i][0] == object || lem->tunnel_directory[i][1] == object) && lem->tunnel_directory[i][2] == 0)
				lem->tunnel_directory[i][2] = 1;
			i++;
		}
	}
	else if (add_reduce == -1)
	{
		while (i < lem->nbr_tunnels)
		{
			if (lem->tunnel_directory[i][2] > 0)
				lem->tunnel_directory[i][2]--;
			i++;
		}
	}
}

void distance_child(t_lem *lem, int object, int add_reduce)
{
	int i;

	i = 0;
	if (add_reduce == 1)
	{
		while (i < lem->nbr_tunnels)
		{
			if (lem->tunnel_directory[i][2] < 0)
				lem->tunnel_directory[i][2]--;
			else if ((lem->tunnel_directory[i][0] == object || lem->tunnel_directory[i][1] == object) && lem->tunnel_directory[i][2] >= 0)
				lem->tunnel_directory[i][2] = -1;
			i++;
		}
	}
	else if (add_reduce == -1)
	{
		while (i < lem->nbr_tunnels)
		{
			if (lem->tunnel_directory[i][2] < 0)
				lem->tunnel_directory[i][2]++;
			i++;
		}
	}
}

void distance_special2(t_lem *lem)
{
	int i;

	i = 0;
	while (i < lem->nbr_tunnels)
	{
		if (lem->tunnel_directory[i][2] < -1)
			lem->tunnel_directory[i][2]++;
		i++;
	}
}

void find_family(t_lem *lem, t_tree *parent, t_tree *child)
{
//	ft_printf("TUNNELS WITH PARENT: %d\n", parent->name);
//	print_tunnel_dir(lem->tunnel_directory, lem->nbr_tunnels);
	if (find_parent_links(parent->name, lem) > 1)
	{
		distance_sibling(lem, child->name, 1);
		lem->sib_name = make_sibling(child, parent, lem);
		distance_sibling(lem, 0, -1);
		//distance_special(lem, lem->sib_name);
		lem->sib_name = 0;
	}
	if (child->name != lem->e_room_index)
	{
		distance_child(lem, parent->name, 1);
		if (make_child(child, lem) != 0)
			distance_child(lem, 0, -1);
	//	else
	//		distance_special2(lem);
	}
}

int make_sibling(t_tree *child, t_tree *parent, t_lem *lem)
{
	t_tree *sibling;
	int i;
	int j;
	int delete;
	int delete2;

	delete2 = 0;
	j = 0;
	i = 0;
	sibling = tree_init(parent);
	child->sib = sibling;
	while (j < lem->nbr_tunnels)
	{
		if (lem->tunnel_directory[j][2] != 0)
			j++;
		else if (ft_strword(lem->tunnel_directory[j], lem->e_room_index))
			j++;
		else if (ft_strword(lem->tunnel_directory[j], parent->name))
		{
			sibling->name = ft_strword(lem->tunnel_directory[j], parent->name);
			ft_printf("sibling:%d\n", sibling->name);
			if (sibling->name == 664)
			{
				ft_printf("hello\n");
				lem->test_index++;
				
			}
			delete = sibling->name;
			while (delete != 0)
			{
				delete = delete / 10;
				delete2++;
			}
			sibling->parent = parent;
			break;
		}
		else
			j++;
	}
	if (sibling->name != 0)
		find_family(lem, parent, sibling);
	return (sibling->name);
}

int make_child(t_tree *parent, t_lem *lem)
{
	t_tree *child;
	int i;
	int j;

	j = 0;
	i = 0;
	child = tree_init(parent);
	parent->child = child;
	while (j < lem->nbr_tunnels)
	{
		if (lem->tunnel_directory[j][2] == 0)
		{
			if (ft_strword(lem->tunnel_directory[j], parent->name))
			{
				child->name = ft_strword(lem->tunnel_directory[j], parent->name);
				ft_printf("child:%d\n", child->name);
				if (child->name == 664)
				{
					ft_printf("hello\n");
					lem->test_index++;
					if (lem->test_index == 4)
					{
						print_tunnel_dir(lem->tunnel_directory, lem->nbr_tunnels);
						exit(1);
					}
				}
				child->parent = parent;
				break;
			}
		}
		j++;
	}
	if (child->name != 0 && child->name != lem->e_room_index)
		find_family(lem, parent, child);
	if (child->name != 0 && child->name == lem->e_room_index)
		lem->total_paths++;
	return (child->name);
}

int tree_creation(t_lem *lem)
{
	int i;

	i = 0;
	lem->test_index = 0; // delete
	lem->tree = head_tree_init(lem->start_room_index);
	make_child(lem->tree, lem);
	distance_child(lem, 0, -1);
	print_tunnel_dir(lem->tunnel_directory, lem->nbr_tunnels);
//	exit (1);
	return (0);
}
