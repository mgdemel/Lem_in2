#include "../includes/lem_in.h"

void arr_row_size(t_tree *start, t_lem *lem)
{
    t_tree *tree;

    tree = start;
    while (ft_strcmp(tree->name, lem->end_room_name) != 0)
    {
        if (tree->sibling != NULL)
        {
            lem->max_paths++;
            arr_row_size(tree->sibling, lem);
        }
        tree = tree->child;
		if (tree->name == NULL)
			break ;
    }
}