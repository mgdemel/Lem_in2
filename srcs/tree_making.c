#include "../includes/lem_in.h"

t_tree	*make_sibling(t_tree *child, char **tunnels, t_tree *parent, t_lem *lem)
{
    t_tree  *sibling;
    sibling = tree_init(parent->name);
	int i;

    sibling->name = needle_crop(tunnels[i], child->name);
    sibling->parent = parent;
	if (lem->trigger > 0)
		sibling->sibling = make_sibling(sibling, tunnels, parent, lem);
	sibling->child = make_child(sibling, tunnels, lem);

	// while (c > 0 && tunnels[i])
	// {
	// 	if ()	
	// }
	return (sibling);
}

t_tree	*make_child(t_tree *parent, char *tunnels, t_lem *lem)
{
    t_tree  *child;
    child = tree_init(parent->name);
	int i;

	i = 0;
    child->name = needle_crop(tunnels, parent->name);  // name is added to the current child
    child->parent = parent;
	lem->trigger += find_parent_links(lem->tunnels, child->name, lem); // add onto our trigger to see if we have links
	if (lem->trigger > 0)
	{
   		child->sibling = make_sibling(child, tunnels, parent, lem); // make sibling if any links still exists
		   															// TODO reduce the amount of trigger

	}
	while (lem->trigger > 0 && tunnels[i])				// TODO continue the cycle of making children until end, make
														// a trigger for END
	{
		if (lem->trigger > 0)
	}
	return (child);
}
/*
** Adds an element onto the int array, UTILS FUNCTION
*/
int		*add_elem_int_array(int nbr, t_lem *lem)
{
	int	*new;
	int i;
	int j;

	i = 0;
	j = 0;
	while (lem->forbidden_array[nbr])
		nbr++;
	new = malloc(sizeof(int) * nbr + 1);
	while (j < nbr)
	{
		new[j] = lem->forbidden_array[j];
		j++;
	}
	new[j] = nbr;
	return (new);
}

/*
**	Scans the array if the number i exists, MOVE TO UTILS
*/
int		scan_forbidden(int *array, int i)
{
	int j;

	j = 0;
	while (array[j])
	{
		if (array[j] == i)
			return (1);
		j++;
	}
	return (0);
}


int		find_parent_links(char **tunnels, char *parent, t_lem *lem) //returns the amount of hits of a room name found in tunnels
{
	int i;
	int c;
	
	c = 0;
	i = 0;
	while (tunnels[i])
	{
		if (scan_forbidden(lem->forbidden_array, i)) // moves forward in the index if it's forbidden
			i++;
		else if (ft_strstr(tunnels, parent))
		{
			c++;
			lem->forbidden_array = add_elem_int_array(i, lem); // add the current index in tunnels so we don't reuse it
			i++;
		}
		else
			i++;
	}
	return (c);
}

void	tree_creation(t_lem *lem)
{
    t_tree  *current_child;
	int i;
	int c;

	c = 0;
	i = 0;
    current_child = tree_init(lem->start_room_name);
    lem->tree = current_child; //saves head branch
	lem->trigger = find_parent_links(lem->tunnels, current_child, lem); //tells us how many children this room has
    while (lem->trigger > 0) //always will be at least one
	{
        current_child = make_child(current_child, lem->tunnels, lem); 
        current_child = current_child->child;
	}
}

t_tree	*tree_init(char *name)
{
	t_tree	*tree;

	if (!(tree = (t_tree *)malloc(sizeof(t_tree))))
		return (NULL);
    tree->name = name;
    tree->parent = NULL;
    tree->child = NULL;
    tree->sibling = NULL;
	tree->used = 0;
    return(tree);
}