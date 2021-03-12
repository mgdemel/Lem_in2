#include "../includes/lem_in.h"

void free_tree(t_tree *start, t_lem *lem)
{
    t_tree *tmp;

	while (ft_strcmp(start->name, lem->end_room_name) != 0)
	{
		ft_printf("step: %d\n", lem->test_index);
		lem->test_index++;
   		tmp = start->child;
		if (start->sibling != NULL)
			free_tree(start->sibling, lem);
		ft_printf("name: %s\n", start->name);
		free(start->name);
		free(start);	
		start = tmp;
		if (start->name == NULL)
			break ;
	}
	free(start->name);
	free(start);

//     typedef struct 		s_tree
// {
// 	char			*name;
// 	struct s_tree	*parent;
// 	struct s_tree	*child;
// 	struct s_tree	*sibling;
// }					t_tree;
/*
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
	*/
}