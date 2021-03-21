#include "../includes/lem_in.h"

void	find_sibling(int *forbidden_array, t_lem *lem, t_tree *parent, t_tree *child)
{
	int 	*w_parent;
	int		*w_child;
	char	*sibling_name;

	w_parent = add_elem_int_array(forbidden_array, lem, parent->name, 1);
	w_child = add_elem_int_array(w_parent, lem, child->name, 0);
	sibling_name = make_sibling(child, parent, lem, w_child);
	forbidden_array = add_elem_int_array(forbidden_array, lem, sibling_name, 0);
	free(w_parent);
	free(forbidden_array);
	free(sibling_name);
}


/*
** TODO CHANGE THIS SO ITS NOT SHIT, it's breaking and leaking with int *new
*/

void	find_child_or_sibling(t_lem *lem, int *forbidden_array, t_tree *parent, t_tree *child)
{
	if (find_parent_links(parent->name, lem, forbidden_array))
	{
		find_sibling(forbidden_array, lem, parent, child);
	}
	if (ft_strcmp(child->name, lem->end_room_name))
	{
		forbidden_array = add_elem_int_array(forbidden_array, lem, parent->name, 1);
		make_child(child, lem, forbidden_array);
	}
}

int	ft_blocked_index(int tunnels, int *forbidden_array, int j)			
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
	return(forbidden);
}

char	*make_sibling(t_tree *child, t_tree *parent, t_lem *lem, int *forbidden_array)
{
    t_tree  *sibling;
	int i;
	int j;

	j = 0;
	i = 0;
	lem->test_index++;
	ft_printf("test index %d\n", lem->test_index);
    sibling = tree_init(parent);
	child->sibling = sibling;
	i = 0;
	while (j < lem->nbr_tunnels)
	{
		if (ft_strstr(lem->tunnels[j], parent->name))
		{
			if (ft_blocked_index(lem->nbr_tunnels, forbidden_array, j) == 0)
			{
				sibling->name = needle_crop(lem->tunnels[j], parent->name);
				sibling->parent = parent;
				break ;
			}
		}
		j++;
	}
	find_child_or_sibling(lem, forbidden_array, parent, sibling);
	free(forbidden_array);
	return (sibling->name);
}

void	make_child(t_tree *parent, t_lem *lem, int *forbidden_array)
{
    t_tree  *child;
	int i;
	int j;

	j = 0;
	i = 0;
	child = tree_init(parent);
	parent->child = child;
	while (j < lem->nbr_tunnels) // we go through tunnels to find the child to the parent
	{
		if (ft_strstr(lem->tunnels[j], parent->name))
		{
			if (ft_blocked_index(lem->nbr_tunnels, forbidden_array, j) == 0)
			{
				child->name = needle_crop(lem->tunnels[j], parent->name);
				child->parent = parent;
				break ;
			}
		}
		j++;
	}
	ft_printf("CHILD: child name is %s\n", child->name);
	ft_printf("CHILD: parent name is %s\n\n", parent->name);
	if (child->name != NULL)
	{
		find_child_or_sibling(lem, forbidden_array, parent, child);
		free(forbidden_array);
	}
	else
		free(forbidden_array);
}

int	tree_creation(t_lem *lem)
{
	int *forbidden_array;
	int i;
	int c;
	char *tmp;

	c = 0;
	i = 0;
	lem->test_index = 0;
	ft_printf("startroomname: %s\nnbr_tunnels:%d\n", lem->start_room_name, lem->nbr_tunnels);
	tmp = ft_strdup(lem->start_room_name);
	if (!(forbidden_array = (int*)malloc(sizeof(int) * (lem->nbr_tunnels))))
		return (1);
	while (i < (lem->nbr_tunnels))
	{
		forbidden_array[i] = -1;
		i++;
	}
    lem->tree = head_tree_init(tmp); //saves head branch
	make_child(lem->tree, lem, forbidden_array);
//	free(forbidden_array);
	free(tmp);
	return (0);
}
