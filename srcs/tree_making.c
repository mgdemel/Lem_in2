#include "lem_in.h"

void	find_family(t_lem *lem, int *forb, t_tree *parent, t_tree *child)
{
	int *tmp;

	tmp = NULL;
	if (find_parent_links(parent->name, lem, forb))
	{
		tmp = ft_newintarr(forb, lem->nbr_tunnels);
		add_elem_int_array(tmp, lem, parent->name, 1);
		add_elem_int_array(tmp, lem, child->name, 0);
		lem->sib_name = make_sibling(child, parent, lem, tmp);
		if (lem->sib_name != NULL)
			add_elem_int_array(forb, lem, lem->sib_name, 0);
		lem->sib_name = NULL;
		free(tmp);
	}
	if (ft_strcmp(child->name, lem->e_room_name))
	{
		add_elem_int_array(forb, lem, parent->name, 1);
		make_child(child, lem, forb);
	}
}

int		ft_blocked_index(int tunnels, int *forbidden_array, int j)
{
	int i;
	int forbidden;

	i = 0;
	forbidden = 0;
	while (i < tunnels)
	{
		if (j == forbidden_array[i])
			forbidden = 1;
		i++;
	}
	return (forbidden);
}

char	*make_sibling(t_tree *child, t_tree *parent, t_lem *lem, int *forb)
{
	t_tree	*sibling;
	int		i;
	int		j;

	j = 0;
	i = 0;
	lem->test_index++;
	sibling = tree_init(parent);
	child->sib = sibling;
	while (j < lem->nbr_tunnels - 1)
	{
		if (ft_strword(lem->tunnels[j], parent->name))
		{
			if (ft_blocked_index(lem->nbr_tunnels, forb, j) == 0)
			{
				sibling->name = needle_crop(lem->tunnels[j], parent->name);
				sibling->parent = parent;
				break ;
			}
		}
		j++;
	}
	if (sibling->name != NULL)
		find_family(lem, forb, parent, sibling);
	return (sibling->name);
}

void	make_child(t_tree *parent, t_lem *lem, int *forbidden_array)
{
	t_tree	*child;
	int		i;
	int		j;
	int		test_delete;

	test_delete = 0;
	j = 0;
	i = 0;
	child = tree_init(parent);
	parent->child = child;
	while (j < lem->nbr_tunnels)
	{
		if (ft_strword(lem->tunnels[j], parent->name))
		{
			ft_printf("Found a match in tunnels: %s and parent: %s, j:%d\n", lem->tunnels[j], parent->name, j);
			// while (test_delete < 10)
			// {
			// 	ft_printf("%d\n", forbidden_array[test_delete]);
			// 	test_delete++;
			// }
			// test_delete = 0;
			if (ft_blocked_index(lem->nbr_tunnels, forbidden_array, j) == 0)
			{
				ft_printf("needle cropping %s and %s\n", lem->tunnels[j], parent->name);
				child->name = needle_crop(lem->tunnels[j], parent->name);
				ft_printf("result child name: %s\n", child->name);
				child->parent = parent;
				break ;
			}
		}
		j++;
	}
	if (child->name != NULL && ft_strcmp(child->name, lem->e_room_name) != 0)
		find_family(lem, forbidden_array, parent, child);
}

int		tree_creation(t_lem *lem)
{
	int *forbidden_array;
	int i;
	int c;

	c = 0;
	i = 0;
	lem->test_index = 0;
	if (!(forbidden_array = (int *)malloc(sizeof(int) * (lem->nbr_tunnels))))
		return (1);
	while (i < (lem->nbr_tunnels))
	{
		forbidden_array[i] = -1;
		i++;
	}
	lem->tree = head_tree_init(lem->start_room_name);
	make_child(lem->tree, lem, forbidden_array);
	free(forbidden_array);
	return (0);
}
