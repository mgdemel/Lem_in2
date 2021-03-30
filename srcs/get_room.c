#include "lem_in.h"

static void	input_coordinates(int i, char *line, t_room *room)
{
	room->x = ft_atoi(&line[i]);
	while (line[i] != ' ')
		i++;
	room->y = ft_atoi(&line[i]);
}

static int	get_room_data(char *line, t_room *room, t_lem *lem)
{
	int len;

	len = 0;
	while (line[len] != ' ')
		len++;
	if (!(room->name = (char *)malloc(sizeof(char) * len + 1)))
		return (1);
	room->name[len] = '\0';
	input_coordinates(len + 1, line, room);
	while (len > 0)
	{
		len--;
		room->name[len] = line[len];
	}
	if (room->roomtype == 1 || room->roomtype == 3)
	{
		if (room->roomtype == 1)
			lem->start_room_name = ft_strdup(room->name);
		else
			lem->e_room_name = ft_strdup(room->name);
	}
	return (0);
}

t_room		*get_room(char *line, t_room *room, t_lem *lem)
{
	room->next = initialize_room(lem);
	get_room_data(line, room, lem);
	return (room->next);
}
