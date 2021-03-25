#include "../includes/lem_in.h"

/*
**	In logique it moves to step 9, but then traces back to r2, because that isn't blocked in this forbidden_array
*/


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

// if (find_parent_links(parent->name, lem, forbidden_array))
// 	{
// 		new = add_elem_int_array(forbidden_array, lem, parent->name, 1);
// 		new = add_elem_int_array(new, lem, child->name, 0);
// 		sibling_name = make_sibling(child, parent, lem, new);
// 		forbidden_array = add_elem_int_array(forbidden_array, lem, sibling_name, 0);
// 	}
// 	if (ft_strcmp(child->name, lem->end_room_name))
// 	{
// 		forbidden_array = add_elem_int_array(forbidden_array, lem, parent->name, 1);
// 		make_child(child, lem, forbidden_array);
// 	}

void find_child_or_sibling(t_lem *lem, int *forbidden_array, t_tree *parent, t_tree *child)
{
	int *tmp;

	tmp = NULL;
	if (find_parent_links(parent->name, lem, forbidden_array))
	{
		tmp = ft_newintarr(forbidden_array, lem->nbr_tunnels); //must allocate space internally
		add_elem_int_array(tmp, lem, parent->name, 1);
		add_elem_int_array(tmp, lem, child->name, 0);
		lem->sibling_name = make_sibling(child, parent, lem, tmp);
		if (lem->sibling_name != NULL)
			add_elem_int_array(forbidden_array, lem, lem->sibling_name, 0);
		lem->sibling_name = NULL;
		free(tmp);
	}
	if (ft_strcmp(child->name, lem->end_room_name))
	{
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
	lem->test_index++;
	sibling = tree_init(parent);
	child->sibling = sibling;
	i = 0;
	ft_printf("parent name:%s\n", parent->name);
	ft_printf("nbr_tunnels:%d\n", lem->nbr_tunnels);
	while (j < lem->nbr_tunnels - 1)
	{
		if (ft_strstr(lem->tunnels[j], parent->name))
		{
		//	if (ft_strstr(parent->name, "Xii9"))
		//		print_int_arr(forbidden_array, lem->nbr_tunnels, "Parent is Xii9");
		//	ft_printf("PRINTED ARRAY DONE\n");
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
	if (sibling->name != NULL)
		find_child_or_sibling(lem, forbidden_array, parent, sibling);
	ft_printf("end\n");
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
	child = tree_init(parent);
	parent->child = child;
	while (j < lem->nbr_tunnels) // we go through tunnels to find the child to the parent
	{
		if (ft_strstr(lem->tunnels[j], parent->name))
		{
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
