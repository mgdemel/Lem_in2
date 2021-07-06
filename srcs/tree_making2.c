#include "lem_in.h"

void find_family2(t_lem *lem, t_tree *parent, t_tree *child)
{
	int i;

	i = find_parent_links(parent->name, lem, child->name, 0);
	if (i >= 0 && lem->links_found > 1)
	{
		lem->tunnel_dir[i][2] = 1;
		make_sibling2(child, parent, lem);
		lem->tunnel_dir[i][2] = 0;
	}
	i = 0;
	if (child->name != lem->e_room_index)
	{
		i = find_parent_links2(parent->name, lem, child->name, 1);
		if (i < lem->nbr_tunnels && i >= 0)
		{
			lem->tunnel_dir[i][2] = -1;
			make_child2(child, lem, parent->name);
			lem->tunnel_dir[i][2] = 0;
			i = 0;
			while (i < lem->nbr_tunnels)
			{
				if (lem->tunnel_dir[i][2] != 0 && lem->tunnel_dir[i][3] != 0 
					&& (lem->tunnel_dir[i][0] == parent->name || lem->tunnel_dir[i][1] == parent->name))
					lem->tunnel_dir[i][2] = 0;
				i++;
			}
		}
	}
	if (lem->links_found == 0)
		child = tree_init(lem, parent);
}

int make_sibling2(t_tree *child, t_tree *parent, t_lem *lem)
{
	t_tree *sibling;
	int j;

	j = lem->nbr_tunnels - 1;
	sibling = tree_init(lem, parent);
	child->sib = sibling;
	ft_printf("MAKING A SIB FOR TREE2\n");
	print_tunnel_dir(lem->tunnel_dir, lem->nbr_tunnels);
	while (j >= 0)
	{
		if (lem->tunnel_dir[j][2] != 0 || lem->tunnel_dir[j][3] != 0)
			j--;
		else if ( j > -1 && ft_strword(lem->tunnel_dir[j], parent->name))
		{
			sibling->name = ft_strword(lem->tunnel_dir[j], parent->name);
			sibling->parent = parent;
			ft_printf("made sib: %d from parent %d\n", sibling->name, sibling->parent->name);
			break ;
		}
		else
			j--;
	}
	if (sibling->name != 0)
		find_family2(lem, parent, sibling);
	return (0);
}

int make_child2(t_tree *parent, t_lem *lem, int super_parent)
{
	t_tree *child;
	int j;
	int i;

	j = lem->nbr_tunnels - 1;
	i = lem->nbr_tunnels - 1;
	child = tree_init(lem, parent);
	parent->child = child;
	while (j >= 0)
	{
		if (lem->tunnel_dir[j][2] == 0 && lem->tunnel_dir[j][3] == 0)
		{
			if (ft_strword(lem->tunnel_dir[j], parent->name))
			{
				child->name = ft_strword(lem->tunnel_dir[j], parent->name);
				child->parent = parent;
				ft_printf("made child: %d from parent %d\n", child->name, child->parent->name);
				break;
			}
		}
		j--;
	}
	while (i >= 0)
	{
		if (lem->tunnel_dir[i][2] == 0 && lem->tunnel_dir[i][3] == 0 
			&& (lem->tunnel_dir[i][0] == super_parent || lem->tunnel_dir[i][1] == super_parent))
			lem->tunnel_dir[i][2] = -1;
		i--;
	}
	if (child->name != 0 && child->name != lem->e_room_index)
		find_family2(lem, parent, child);
	return (0);
}
