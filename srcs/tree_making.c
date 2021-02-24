#include "../includes/lem_in.h"

void	find_child_or_sibling(t_lem *lem, int *forbidden_array, t_tree *parent, t_tree *child)
{
	int 	*new;
	char	*sibling_name;

	sibling_name = NULL;
	ft_printf("Started find child or sibling\n");
	if (find_parent_links(parent->name, lem, forbidden_array))
	{
		ft_printf("started sibling\n");
		new = add_elem_int_array(forbidden_array, lem, parent->name, 1);
		new = add_elem_int_array(new, lem, child->name, 0);
		sibling_name = make_sibling(child, parent, lem, new);
		ft_printf("sibling_name: %s\n", sibling_name);
		forbidden_array = add_elem_int_array(forbidden_array, lem, sibling_name, 0);
	}
	ft_printf("went here\n");
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
    sibling = tree_init(parent);
	child->sibling = sibling;
	i = 0;
	ft_printf("step: %d\n", lem->test_index);
	lem->test_index++;
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
	ft_printf("SIBLING: child name is %s\n", child->name);
	ft_printf("SIBLING: sibling name is %s\n", sibling->name);
	ft_printf("SIBLING: parent name is %s\n", parent->name);
	ft_printf("\n");
	find_child_or_sibling(lem, forbidden_array, parent, sibling);
	return (sibling->name);
}

void make_child(t_tree *parent, t_lem *lem, int *forbidden_array)  // TODO tunnels double char probably?
{
    t_tree  *child;
	int i;
	int j;

	j = 0;
	i = 0;
	child = tree_init(parent);
	parent->child = child;
	ft_printf("step: %d\n", lem->test_index);
	lem->test_index++;
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
	ft_printf("CHILD: parent name is %s\n", parent->name);
	ft_printf("\n");
	if (child->name != NULL)
		find_child_or_sibling(lem, forbidden_array, parent, child);
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
    current_child = head_tree_init(lem->start_room_name);
    lem->tree = current_child; //saves head branch
	i = 0;
	while (i < lem->nbr_tunnels)
		i++;
	make_child(current_child, lem, forbidden_array);
	return (0);
}
