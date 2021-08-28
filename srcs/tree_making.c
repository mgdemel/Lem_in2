#include "lem_in.h"

void	reset_temp_blocking(t_lem *lem)
{
	int i;
	
	i = 0;
	while (i < lem->nbr_tunnels)
	{
		lem->tunnel_dir[i][4] = 0;
		i++;
	}
}

/*
**	Returns a 1 if it finds the exact word in haystack 
**  that was in needle before or 
** 	after a '-' character.
*/
int	ft_strword(int *haystack, int needle)
{
	if (haystack[0] == needle)
		return (haystack[1]);
	else if (haystack[1] == needle)
		return (haystack[0]);
	return (0);
}

t_queue	*put_into_queue(int child, t_queue *queue)
{
	t_queue *next_queue;

	next_queue = (t_queue *)malloc(sizeof(t_queue));
	next_queue->next = NULL;
	next_queue->prev = queue;
	next_queue->room = 0;
	queue->room = child;
	queue->next = next_queue;
	return (next_queue);
}

void	make_path(int i, t_lem *lem, int direction)
{
	int *path;
	int j;
	int room;
	int negative;
	int other_direction;


	if (direction == 3)
		other_direction = 2;
	else
		other_direction = 3;

	negative = 2;
	room = lem->e_room_index;
	j = lem->tunnel_dir[i][4] - 1;
	ft_printf("j%d\n", j);
	path = (int*)malloc(sizeof(int) * lem->tunnel_dir[i][4] + 2); //adding start room name - need to change sort and output logic accordingly
	if (path == NULL)
		error_message(lem, 1);
	lem->tunnel_dir[i][direction] = direction;
	path[0] = (lem->tunnel_dir[i][4] * -1) - 1;
	path[lem->tunnel_dir[i][4] + 1] = lem->e_room_index;
	path[lem->tunnel_dir[i][4]] = ft_strword(lem->tunnel_dir[i], lem->e_room_index);


	ft_printf("path[0]%d\n", path[0]);
	room = ft_strword(lem->tunnel_dir[i], lem->e_room_index);
	ft_printf("room%d\n", room);
	while (j >= 1)
	{
		i = 0;
		while (i < lem->nbr_tunnels)
		{
			if ((lem->tunnel_dir[i][0] == room || lem->tunnel_dir[i][1] == room)
				&& (lem->tunnel_dir[i][4] == (path[0] * -1) - negative))
			{
				room = ft_strword(lem->tunnel_dir[i], room);
				path[j] = room;
				j--;
				negative++;
				lem->tunnel_dir[i][direction] = direction;
			}
			i++;
		}
	}
	print_int_arr(path, 5, "PATH");
	reset_temp_blocking(lem);
	print_tunnel_dir(lem->tunnel_dir, lem->nbr_tunnels);

}
//direction depends on which is first and which is second in the tunnel name
int		bfs(t_lem *lem, int start/*, int direction*/)
{
	int i;
	int condition;
	int counter;
	int sibling;
	t_queue *queue;
	t_queue *scan;

	counter = 1;
	sibling = 0;
	queue = (t_queue *)malloc(sizeof(t_queue));
	scan = (t_queue *)malloc(sizeof(t_queue));
	if (queue == NULL || scan == NULL)
		error_message(lem, 1);
	queue->next = NULL;
	queue->prev = NULL;
	queue->room = 0;
	condition = 0;
	i = 0;
	scan = queue;
	ft_printf("start:%d\n", start);
	while (1)
	{
		ft_printf("Scanning %d with %d and %d\n", start, lem->tunnel_dir[i][0], lem->tunnel_dir[i][1]);
		if ((lem->tunnel_dir[i][0] != start && lem->tunnel_dir[i][1] != start) || lem->tunnel_dir[i][4] > 0)
			i++;
		else
		{
			if (condition == 1)
				sibling++;
			condition = 1;
			queue = put_into_queue(ft_strword(lem->tunnel_dir[i], start), queue);
			ft_printf("queue ROOM IS %d\n", queue->prev->room);
			lem->tunnel_dir[i][4] = counter;
			print_tunnel_dir(lem->tunnel_dir, lem->nbr_tunnels);
			if (queue->prev->room == lem->e_room_index)
				break ;
		}
		if (i == lem->nbr_tunnels)
		{
			ft_printf("ended\n");
			if (condition == 0)
				break ;
			condition = 0;
			start = scan->room;
			scan = scan->next;
			i = 0;
			if (sibling > 0)
			{
				counter++;
				sibling *= -1;
			}
			else
				sibling++;
		}
	}
	make_path(i, lem, 3);
	return (queue->room);
}

void	tree_creation(t_lem *lem)
{
	int path;

//	while ()
	path = bfs(lem, lem->s_room_index);
	ft_printf("Queue room at the end of scan: %d\n", path);
	// lem->max_paths = 0; //init at zero, increase with each new valid path found in BFS
	// lem->all_paths = (int **)malloc(sizeof(int *) * lem->max_paths); //re-malloc with each new valid path found in BFS and fill in previous paths
	// if (lem->all_paths == NULL)
	// 	error_message(lem, 1);
}
