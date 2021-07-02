#include "lem_in.h"

int make_sibling2(t_tree *child, t_tree *parent, t_lem *lem)
{
	t_tree *sibling;
	int i;
	int j;

	j = lem->nbr_tunnels - 1;
	i = 0;
	sibling = tree_init(lem, parent);
	child->sib = sibling;
	while (j >= 0)
	{
		if (lem->tunnel_dir[j][2] != 0 || lem->tunnel_dir[j][3] != 0)
			j--;
		else if (ft_strword(lem->tunnel_dir[j], parent->name))
		{
			ft_printf("creating sibling:%d\n", sibling->name);
			sibling->name = ft_strword(lem->tunnel_dir[j], parent->name);
			sibling->parent = parent;
			break ;
		}
		else
			j--;
	}
	if (sibling->name != 0 && sibling->name == lem->e_room_index)
		lem->total_paths++;
	if (sibling->name != 0)
		find_family(lem, parent, sibling);
	return (sibling->name);
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
	ft_printf("Make child\n");
	while (j >= 0)
	{
		if (lem->tunnel_dir[j][2] == 0 && lem->tunnel_dir[j][3] == 0)
		{
			if (ft_strword(lem->tunnel_dir[j], parent->name))
			{
				child->name = ft_strword(lem->tunnel_dir[j], parent->name);
				ft_printf("creating child:%d\n", child->name);
				child->parent = parent;
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
		find_family(lem, parent, child);
	if (child->name != 0 && child->name == lem->e_room_index)
		lem->total_paths++;
	return (parent->name);
}
