#include "../includes/lem_in.h"

int	check_tunnel_validity(t_lem *lem)
{
	int trigger;
	int i;

	i = 0;
	trigger = 0;
	while (i < lem->nbr_tunnels && i != -1) 
	{
		if (lem->forbidden_array[i] == trigger) //check every elem in forbidden, if it's equal, it's forbidden, we don't check it.
		{
			trigger++;
			i = -1;
		}
		i++;
	}
	if (trigger == lem->nbr_tunnels)
		return (-1);
	else
		return (trigger);
}

void	make_sibling(t_tree *child, char **tunnels, t_tree *parent, t_lem *lem)
{
    t_tree  *sibling;
	int i;
	int j;
	int	forbidden;

	forbidden = 0;
	j = 0;
	i = 0;
	sleep(1);
    sibling = tree_init(parent->name);
	sibling->sibling = child;
	while (tunnels[j])
	{
		if (ft_strstr(tunnels[j], parent->name))
		{
			i = 0;
			while (i < lem->nbr_tunnels)
			{
				if (j == lem->forbidden_array[i])
					forbidden = 1;
				i++;
			}
			if (forbidden == 0)
			{
				sibling->name = needle_crop(tunnels[j], parent->name);
				sibling->parent = parent;
				lem->trigger--;
				lem->trigger += find_parent_links(lem->tunnels, sibling->name, lem); //checks for cases where there are more than one sibling
			}
			forbidden = 0;
		}
		j++;
	//	j += check_tunnel_validity(lem);
	//	if (j != -1 && ft_strstr(tunnels[j], parent->name)) //if we find name of parent in tunnels and it's not forbidden, it's a sibling
	//	{
	//		sibling->name = needle_crop(tunnels[j], parent->name);
	//		sibling->parent = parent;
	//		lem->trigger--;
	//		lem->trigger += find_parent_links(lem->tunnels, sibling->name, lem); //checks for cases where there are more than one sibling
	//	}
		printf("everything seems ok so far in SIBLING\n");
	}
	ft_printf("child name is %s\n", child->name);
	ft_printf("parent name is %s\n", parent->name);
	ft_printf("trigger is %d\n", lem->trigger);
	i = 0;
	while (i < lem->nbr_tunnels)
	{
		ft_printf("array: %d\n", lem->forbidden_array[i]);
		i++;
	}
	if (lem->trigger > 0)
		make_sibling(sibling, tunnels, parent, lem);
	i = 0;
	while (i < lem->nbr_tunnels)
	{
		if (lem->forbidden_array[i] != -1)
			make_child(child, tunnels, lem);
		i++;
	}
}

void make_child(t_tree *parent, char **tunnels, t_lem *lem)  // TODO tunnels double char probably?
{
    t_tree  *child;
	int i;
	int j;
	int	forbidden;

	forbidden = 0;
	j = 0;
	i = 0;
	sleep(1);
	child = tree_init(parent->name);
	while (tunnels[j])
	{
		if (ft_strstr(tunnels[j], parent->name))
		{
			i = 0;
			while (i < lem->nbr_tunnels)
			{
				if (j == lem->forbidden_array[i])
					forbidden = 1;
				i++;
			}
			if (forbidden == 0)
			{
				child->name = needle_crop(tunnels[j], parent->name);
				child->parent = parent;
				lem->trigger += find_parent_links(lem->tunnels, child->name, lem); //checks for cases where there are more than one sibling
				lem->trigger--;
			}
			forbidden = 0;
		}
		j++;
	}
	ft_printf("child name is %s\n", child->name);
	ft_printf("parent name is %s\n", parent->name);
	ft_printf("trigger is %d\n", lem->trigger);
	i = 0;
	while (i < lem->nbr_tunnels)
	{
		ft_printf("array in make_child: %d\n", lem->forbidden_array[i]);
		i++;
	}
	if (lem->trigger > 0)
		make_sibling(child, tunnels, parent, lem);
	i = 0;
	while (i < lem->nbr_tunnels)
	{
		if (lem->forbidden_array[i] != -1)
			make_child(child, tunnels, lem);
		i++;
	}
}

int	tree_creation(t_lem *lem)
{
    t_tree  *current_child;
	int i;
	int c;

	c = 0;
	i = 0;
	if (!(lem->forbidden_array = (int*)malloc(sizeof(int) * (lem->nbr_tunnels))))
		return (1);
	while (i < (lem->nbr_tunnels))
	{
		lem->forbidden_array[i] = -1;
		i++;
	}
    current_child = tree_init(lem->start_room_name);
    lem->tree = current_child; //saves head branch
//	lem->trigger = find_parent_links(lem->tunnels, current_child->name, lem); //tells us how many children this room has
	i = 0;
	while (i < lem->nbr_tunnels)
	{
		ft_printf("array in tree: %d\n", lem->forbidden_array[i]);
		i++;
	}
	ft_printf("tunnels last %s\n", lem->tunnels[8]);
	ft_printf("Did we even go into tree creation?\n");
	ft_printf("first child name: %s\n", current_child->name);
	make_child(current_child, lem->tunnels, lem);
	return (0);
}
