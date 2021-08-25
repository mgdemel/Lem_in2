#include "lem_in.h"

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

int		bfs(t_lem *lem, int start)
{
	int i;
	int condition;
	t_queue *queue;
	t_queue *scan;

	queue = (t_queue *)malloc(sizeof(t_queue));
	scan = (t_queue *)malloc(sizeof(t_queue));
	queue->next = NULL;
	queue->prev = NULL;
	queue->room = 0;
	condition = 0;
	i = 0;
	scan = queue;
	ft_printf("start:%d\n", start);
	
	while (i < lem->nbr_tunnels)
	{
		ft_printf("Scanning %d with %d and %d\n", start, lem->tunnel_dir[i][0], lem->tunnel_dir[i][1]);
		if ((lem->tunnel_dir[i][0] != start && lem->tunnel_dir[i][1] != start) || lem->tunnel_dir[i][4] == 1)
			i++;
		else
		{
			condition = 1;
			queue = put_into_queue(ft_strword(lem->tunnel_dir[i], start), queue);
			ft_printf("queue ROOM IS %d\n", queue->prev->room);
			lem->tunnel_dir[i][4] = 1;
		//	print_tunnel_dir(lem->tunnel_dir, lem->nbr_tunnels);
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
		}
	}
	return (queue->room);
}

void	tree_creation(t_lem *lem)
{
	int path;

//	while ()
	path = bfs(lem, lem->s_room_index);
	ft_printf("Queue room at the end of scan: %d\n", path);
}
