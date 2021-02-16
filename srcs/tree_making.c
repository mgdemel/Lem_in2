#include "../includes/lem_in.h"

char	*make_sibling(t_tree *child, t_tree *parent, t_lem *lem, int *forbidden_array)
{
    t_tree  *sibling;
	int i;
	int j;
	int t;
	int	forbidden;
	int *new;
	char	*sibling_name;

	forbidden = 0;
	j = 0;
	i = 0;
	t = 0;
	sleep(1);
    sibling = tree_init(parent->name);
	sibling->sibling = child;
	while (i < lem->nbr_tunnels)
	{
		ft_printf("forbidden array: %d\n", forbidden_array[i]);
		i++;
	}
	i = 0;
	while (lem->tunnels[j])
	{
		if (ft_strstr(lem->tunnels[j], parent->name))
		{
			i = 0;
			while (i < lem->nbr_tunnels)
			{
				if (j == forbidden_array[i])
					forbidden = 1;
				i++;
			}
			if (forbidden == 0)
			{
				sibling->name = needle_crop(lem->tunnels[j], parent->name);
				sibling->parent = parent;
				break ;
			}
			forbidden = 0;
		}
		j++;
	}

	ft_printf("SIBLING: sibling name is %s\n", sibling->name);
	ft_printf("SIBLING: parent name is %s\n", parent->name);
	ft_printf("\n");
	
	if (find_parent_links(parent->name, lem, forbidden_array))
	{
		new = add_elem_int_array(forbidden_array, lem, parent->name, 1);
		new = add_elem_int_array(new, lem, child->name, 0);
		while (t < lem->nbr_tunnels)
		{
			ft_printf("array before make sibling in make sibling: %d\n", new[t]);
			t++;
		}
		t = 0;
		sibling_name = make_sibling(child, parent, lem, new);
	}
	if (ft_strcmp(sibling->name, lem->end_room_name))
	{
		ft_printf("fuck\n");
		forbidden_array = add_elem_int_array(forbidden_array, lem, parent->name, 1);
		ft_printf("fuck1.5\n");
		while (t < lem->nbr_tunnels)
		{
			ft_printf("before make child in make sibling: %d\n", forbidden_array[t]);
			t++;
		}
		t = 0;
		make_child(sibling, lem, forbidden_array);
	}
	return (sibling->name);
}

void make_child(t_tree *parent, t_lem *lem, int *forbidden_array)  // TODO tunnels double char probably?
{
    t_tree  *child;
	int i;
	int j;
	int t;
	int	forbidden;
	int *new;
	char	*sibling_name;

	forbidden = 0;
	j = 0;
	i = 0;
	t = 0;
	sleep(1);
	child = tree_init(parent->name);
	while (lem->tunnels[j])
	{
		if (ft_strstr(lem->tunnels[j], parent->name))
		{
			i = 0;
			while (i < lem->nbr_tunnels)
			{
				if (j == forbidden_array[i])
					forbidden = 1;
				i++;
			}
			if (forbidden == 0)
			{
				child->name = needle_crop(lem->tunnels[j], parent->name);
				child->parent = parent;
				break ;
			}
			forbidden = 0;
		}
		j++;
	}

	ft_printf("CHILD: child name is %s\n", child->name);
	ft_printf("CHILD: parent name is %s\n", parent->name);
	ft_printf("\n");
	
	if (find_parent_links(parent->name, lem, forbidden_array))
	{
		new = add_elem_int_array(forbidden_array, lem, parent->name, 1);
		new = add_elem_int_array(new, lem, child->name, 0);
		while (t < lem->nbr_tunnels)
		{
			ft_printf("array before make sib in make child: %d\n", new[t]);
			t++;
		}
		t = 0;
		sibling_name = make_sibling(child, parent, lem, new);
	}
	if (ft_strcmp(child->name, lem->end_room_name))
	{
		forbidden_array = add_elem_int_array(forbidden_array, lem, parent->name, 1);
		while (t < lem->nbr_tunnels)
		{
			ft_printf("array before child make child: %d\n", forbidden_array[t]);
			t++;
		}
		t = 0;
		make_child(child, lem, forbidden_array);
	}
}

int	tree_creation(t_lem *lem)
{
    t_tree  *current_child;
	int *forbidden_array;
	int i;
	int c;

	c = 0;
	i = 0;
	if (!(forbidden_array = (int*)malloc(sizeof(int) * (lem->nbr_tunnels))))
		return (1);
	while (i < (lem->nbr_tunnels))
	{
		forbidden_array[i] = -1;
		i++;
	}
    current_child = tree_init(lem->start_room_name);
    lem->tree = current_child; //saves head branch
	i = 0;
	while (i < lem->nbr_tunnels)
	{
		ft_printf("array in tree: %d\n", forbidden_array[i]);
		i++;
	}
	make_child(current_child, lem, forbidden_array);
	return (0);
}
