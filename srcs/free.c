#include "lem_in.h"

void	free_array(char **array, int max)
{
	int	i;

	i = 0;
	while (i < max)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_int_array(int **array, int max)
{
	int	i;

	i = 0;
	while (i < max)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_lem(t_lem *lem)
{
	free_tree(lem->tree, lem);
	free_array(lem->tunnels, lem->nbr_tunnels);
	free_array(lem->room_directory, lem->current_roomnum);
	free_int_array(lem->sorted, lem->max_valid);
	free_int_array(lem->final, lem->final_tab);
	free_int_array(lem->all_paths, lem->all_paths_size);
	free_int_array(lem->tunnel_dir, lem->nbr_tunnels);
	free(lem);
}

void	free_room(t_room *room)
{
	t_room	*tmp;
	t_room	*current;

	current = room;
	while (current->next != NULL)
	{
		tmp = current->next;
		free(current->name);
		free(current);
		current = tmp;
	}
	free(current->name);
	free(current);
}

void	free_tree(t_tree *start, t_lem *lem)
{
	t_tree	*tmp;

	if (start->name != 0)
	{
		while (start->name != lem->e_room_index)
		{
			tmp = start->child;
			if (start->sib != NULL)
				free_tree(start->sib, lem);
			free(start);
			start = tmp;
			if (start->name == 0)
				break ;
		}
	}
	free(start);
}
