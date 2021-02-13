#include "../includes/lem_in.h"

t_tree	*make_sibling(char **tunnels, t_tree *parent, t_lem *lem)
{
    t_tree  *sibling;
	int i;
	int j;

	j = 0;
	i = 0;
    sibling = tree_init(parent->name);
	while (tunnels[j])
	{
		i = 0;
		while (lem->forbidden_array[i]) 
		{
			if (lem->forbidden_array[i] == j) //check every elem in forbidden, if it's equal, it's forbidden, we don't check it.
			{
				j++;
				i = -1;
			}
			i++;
		}
		if (ft_strstr(tunnels[j], parent->name)) //if we find name of parent in tunnels and it's not forbidden, it's a sibling
		{
			sibling->name = needle_crop(tunnels[j], parent->name);
			sibling->parent = parent;
			lem->trigger--;
			lem->trigger += find_parent_links(lem->tunnels, sibling->name, lem); //checks for cases where there are more than one sibling
		}
		j++;
	}
	if (lem->trigger > 0)
		make_sibling(tunnels, parent, lem);
	make_child(sibling, tunnels, lem);
	return (sibling);
}

void make_child(t_tree *parent, char **tunnels, t_lem *lem)  // TODO tunnels double char probably?
{
    t_tree  *child;
	int i;

	i = 0;
	child = tree_init(parent->name);
	if (lem->trigger > 0)
	{
   		child->sibling = make_sibling(tunnels, parent, lem); // make sibling if any links still exists
	}
	child->name = needle_crop(tunnels, parent->name);  // name is added to the current child
    child->parent = parent;
	lem->trigger += find_parent_links(lem->tunnels, child->name, lem); // add onto our trigger to see if we have links
	if (child != NULL)				// TODO continue the cycle of making children until end, make													
	{													// a trigger for END
		make_child(child, tunnels, lem);
	}
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
    make_child(current_child, lem->tunnels, lem); 
}


PROCESS PSEUDOCODE:

Tree creation makes headnode