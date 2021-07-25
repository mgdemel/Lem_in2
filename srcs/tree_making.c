#include "lem_in.h"

void find_family(t_lem *lem, t_tree *parent, t_tree *child)
{
	int i;
	i = find_parent_links(parent->name, lem, child->name, 0);
	if (i >= 0 && lem->links_found > 1)
	{
		lem->tunnel_dir[i][2] = 1;
		make_sibling(child, parent, lem);
		lem->tunnel_dir[i][2] = 0;
	}
	i = 0;
	if (child->name != lem->e_room_index)
	{
		i = find_parent_links(parent->name, lem, child->name, 1);
		if (i < lem->nbr_tunnels && i >= 0)
		{
			lem->tunnel_dir[i][2] = -1;
			make_child(child, lem, parent->name);
			lem->tunnel_dir[i][2] = 0;
			i = 0;
			while (i < lem->nbr_tunnels)
			{
				if ((lem->tunnel_dir[i][2] != 0 || lem->tunnel_dir[i][3] != 0) 
					&& (lem->tunnel_dir[i][0] == parent->name || lem->tunnel_dir[i][1] == parent->name))
						lem->tunnel_dir[i][2] = 0;
				i++;
			}
		}
	}
	if (lem->links_found == 0)
		child = tree_init(lem, parent);
}

int make_sibling(t_tree *child, t_tree *parent, t_lem *lem)
{
	t_tree *sibling;
	int j;
	int tunnel;

	tunnel = lem->t_index;
	j = lem->t_index;
	sibling = tree_init(lem, parent);
	child->sib = sibling;
	while (j < lem->nbr_tunnels)
	{
		if (lem->tunnel_dir[j][2] == 0 && lem->tunnel_dir[j][3] == 0)
		{
			if (ft_strword(lem->tunnel_dir[j], parent->name))
			{
				sibling->name = ft_strword(lem->tunnel_dir[j], parent->name);
				sibling->parent = parent;
				break;
			}
		}
		j++;
	}
	tunnel--;
	while (tunnel > 0)
	{
		if (lem->tunnel_dir[tunnel][2] == 0 && lem->tunnel_dir[tunnel][3] == 0)
		{
			if (ft_strword(lem->tunnel_dir[tunnel], parent->name))
			{
				sibling->name = ft_strword(lem->tunnel_dir[tunnel], parent->name);
				sibling->parent = parent;
				break;
			}
		}
		tunnel--;
	}
	if (sibling->name != 0)
		find_family(lem, parent, sibling);
	return (sibling->name);
}

void	block_parent(t_lem *lem, int super_parent)
{
	int i;

	i = 0;
	while (i < lem->nbr_tunnels)
	{
		if (lem->tunnel_dir[i][2] == 0 && lem->tunnel_dir[i][3] == 0 
			&& (lem->tunnel_dir[i][0] == super_parent
			|| lem->tunnel_dir[i][1] == super_parent))
			lem->tunnel_dir[i][2] = -1;
		i++;
	}
}

int make_child(t_tree *parent, t_lem *lem, int super_parent)
{
	t_tree *child;
	int j;
	int tunnel;

	tunnel = lem->t_index;
	j = lem->t_index;

	child = tree_init(lem, parent);
	parent->child = child;
	while (j < lem->nbr_tunnels)
	{
		if (lem->tunnel_dir[j][2] == 0 && lem->tunnel_dir[j][3] == 0)
		{
			
			if (ft_strword(lem->tunnel_dir[j], parent->name))
			{
				child->name = ft_strword(lem->tunnel_dir[j], parent->name);
				child->parent = parent;
				break;
			}
		}
		j++;
	}
	tunnel--;
	while (tunnel > 0)
	{
		if (lem->tunnel_dir[tunnel][2] == 0 && lem->tunnel_dir[tunnel][3] == 0)
		{
			if (ft_strword(lem->tunnel_dir[tunnel], parent->name))
			{
				child->name = ft_strword(lem->tunnel_dir[tunnel], parent->name);
				child->parent = parent;
				break;
			}
		}
		tunnel--;
	}
	block_parent(lem, super_parent); // might need an if
	if (child->name != 0 && child->name != lem->e_room_index)
		find_family(lem, parent, child);
	return (parent->name);
}

void tree_creation(t_lem *lem)
{
	lem->tree = (t_tree **)malloc(sizeof(t_tree *) * lem->nbr_tunnels);
	if (lem->tree == NULL)
		error_message(lem, 0);
	while (lem->t_index < 2)
	{
		lem->tree[lem->t_index] = head_tree_init(lem, lem->s_room_index);
		make_child(lem->tree[lem->t_index], lem, -1);
		init_tunnel_arr(lem);
		remove_duplicated(lem);
		remove_deadends(lem, 0, 1);
		lem->t_index++;
	}
}
