#include "../includes/lem_in.h"

/*
**	In logique it moves to step 9, but then traces back to r2, because that isn't blocked in this forbidden_array
*/

void	print_int_arr(int *arr, int len, char *str)
{
	int i;
	
	i = 0;
	ft_printf("\n***---STARTING PRINT ARR---***\n");
	while (i < len)
	{
		ft_printf("%s:%d\n", str, arr[i]);
		i++;
	}
}

int *ft_newintarr(int *forbidden_array, int i)
{
	int *new;
	int j;
	j = i;

	if (!(new = (int *)malloc(sizeof(int) * (i))))
		return (NULL);
	i--;
	while (i >= 0)
	{
		new[i] = forbidden_array[i];
		i--;
	}
	return(new);
}

void find_child_or_sibling(t_lem *lem, int *forbidden_array, t_tree *parent, t_tree *child)
{
	int *tmp;
	int i;

	i = 0;
	tmp = NULL;
	if (find_parent_links(parent->name, lem, forbidden_array))
	{
		add_elem_int_array(forbidden_array, lem, parent->name, 1);
		tmp = ft_newintarr(forbidden_array, lem->nbr_tunnels); //must allocate space internally
		add_elem_int_array(tmp, lem, child->name, 0);
		lem->sibling_name = make_sibling(child, parent, lem, tmp);
		free(tmp);
		i = 1;
	}
	if (ft_strcmp(child->name, lem->end_room_name))
	{
		if (i == 0)
			add_elem_int_array(forbidden_array, lem, parent->name, 1);
		make_child(child, lem, forbidden_array);
	}
}

int ft_blocked_index(int tunnels, int *forbidden_array, int j)
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

char *make_sibling(t_tree *child, t_tree *parent, t_lem *lem, int *forbidden_array)
{
	t_tree *sibling;
	int i;
	int j;

	j = 0;
	i = 0;
	ft_printf("MAKE SIBLING\n");
	print_int_arr(forbidden_array, lem->nbr_tunnels, parent->name);
	ft_printf("\n");
	lem->test_index++;
	sibling = tree_init(parent);
	child->sibling = sibling;
	i = 0;
	while (j < lem->nbr_tunnels - 1)
	{
		if (ft_strstr(lem->tunnels[j], parent->name))
		{
			if (ft_blocked_index(lem->nbr_tunnels, forbidden_array, j) == 0)
			{
				sibling->name = needle_crop(lem->tunnels[j], parent->name);
				ft_printf("MADE SIBLING WITH NAME %s\n", sibling->name);
				sibling->parent = parent;
				break;
			}
		}
		j++;
	}
	find_child_or_sibling(lem, forbidden_array, parent, sibling);
//	free(forbidden_array);
	return (sibling->name);
}

void make_child(t_tree *parent, t_lem *lem, int *forbidden_array)
{
	t_tree *child;
	int i;
	int j;

	j = 0;
	i = 0;
	ft_printf("MAKE CHILD\n");
	print_int_arr(forbidden_array, lem->nbr_tunnels, parent->name);
	ft_printf("\n");
	child = tree_init(parent);
	parent->child = child;
	while (j < lem->nbr_tunnels) // we go through tunnels to find the child to the parent
	{
		if (ft_strstr(lem->tunnels[j], parent->name))
		{
			ft_printf("j = %d\n", j);
			if (ft_blocked_index(lem->nbr_tunnels, forbidden_array, j) == 0)
			{
				child->name = needle_crop(lem->tunnels[j], parent->name);
				ft_printf("MADE CHILD WITH NAME %s\n", child->name);
				child->parent = parent;
				break;
			}
		}
		j++;
	}
	if (child->name != NULL)
	{
		find_child_or_sibling(lem, forbidden_array, parent, child);
	}
	// else
	// {
	// 	ft_printf("TEST\n");
	// 	free(forbidden_array);
	// }
}

int tree_creation(t_lem *lem)
{
	int *forbidden_array;
	int i;
	int c; 

	/*
	**
	**	Maybe add tmp as name instead of sending start_room_name in head_tree_init
	**
	*/

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
	lem->tree = head_tree_init(lem->start_room_name); //saves head branch 
	make_child(lem->tree, lem, forbidden_array);
	return (0);
}
