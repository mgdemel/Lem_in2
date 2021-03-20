#include "../includes/lem_in.h"

void	free_array(char **array)
{
	int i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_int_array(int **array, int max_paths)
{
	int i;

	i = 0;
	while (i < max_paths)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void free_lem(t_lem *lem)
{
	free_array(lem->tunnels);
	ft_printf("4\n");
	ft_printf("5\n");

	free_int_array(lem->all_paths, lem->max_paths);
	
}

void free_room(t_room *room)
{
	t_room *tmp;
	t_room *current;

	current = room;
	while (current->next != NULL)
	{
		ft_printf("name: %s\n", current->name);
	//	ft_printf("type: %s\n", room->roomtype);
		tmp = current->next;
		free(current->name);
		free(current);
		current = tmp;
	}
	free(current->name);
	free(current);
}

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
		ft_printf("\nFREEING1\n");
		free(start->name);
		free(start);
		start = tmp;
		if (start->name == NULL)
			break ;
	}
	ft_printf("Freeing last room %s\n", start->name);
	free(start->name);
	free(start);
}