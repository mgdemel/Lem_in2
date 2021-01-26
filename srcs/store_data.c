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

t_room		*get_room(char *line, t_room *room, int fd)
{
	t_room *new_room = NULL;
	t_room *temp = NULL;
	int		i;
	char	**coord;
	i = 0;

	room->next = new_room;
	room = new_room;
	room->prev = temp;
	if (ft_strstr((char*)line, "##start")) //labels room based on type
	{
		room->roomtype = 1;
		ft_strdel(&line);
		get_next_line(fd, &line);
	}
	else if (ft_strstr((char*)line, "##end"))
	{
		room->roomtype = 3;
		ft_strdel(&line);
		get_next_line(fd, &line);
	}
	else
		room->roomtype = 2;
	while (*line != ' ') //stores the name of the room
	{
		room->name[i] = *line;
		i++;
		line++;
	} 
	i++;
	if (!(coord = ft_strsplit(&line[i], ' ')))
		ft_putstr("ERROR IN FT_STRSPLIT - GET_ROOM FUNCTION");
	room->x = ft_atoi(coord[0]);
	room->y = ft_atoi(coord[1]);
	free_array(coord);
	return(room = room->next);
}

int				store_data(char *line, t_room *room, t_lem *lem, int fd)
{
	int i;

	i = 0;
	get_next_line(fd, &line);
	lem->ants = ft_atoi(line);
	ft_strdel(&line);
	while (get_next_line(fd, &line) > 0)
	{
		if (!(ft_strstr(line, "-")))
			room = get_room(line, room, fd);
		else
			lem-> tunnels[i++] = ft_strdup(line);  // check if it works
		ft_strdel(&line);
	}
	return (0);
}
