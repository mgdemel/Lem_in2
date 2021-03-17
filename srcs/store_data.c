#include "../includes/lem_in.h"

int 	get_room_data(char *line, t_room *room, t_lem *lem)
{
	int		i;
	char	**coord;

	i = 0;
	if (!(room->name = (char*)malloc(sizeof(char) * ((int)ft_strlen(line) + 1))))
		return (1);
	line[(int)ft_strlen(line) + 1] = '\0';
	while (line[i] != ' ') //stores the name of the room
	{
		room->name[i] = line[i];
		i++;
	}
	lem->room_directory[lem->room_dir_index] = room->name;
	lem->room_dir_index++;
	if (room->roomtype == 1 || room->roomtype == 3)
	{
		if(room->roomtype == 1)
			lem->start_room_name = ft_strdup(room->name);
		else
			lem->end_room_name = ft_strdup(room->name);
	}
	i++; //moves past next space to get to coords
	if (!(coord = ft_strsplit(&line[i], ' ')))
		return (1);
	room->x = ft_atoi(coord[0]);
	room->y = ft_atoi(coord[1]);
	free_array(coord);
	return (0);
}

t_room		*get_room(char *line, t_room *room, t_lem *lem)
{
	room->next = initialize_room(lem);
	get_room_data(line, room, lem);
	return(room->next);
}

int				store_data(char *line, t_lem *lem, t_room *room, int fd)
{
	int i;

	i = 0;
	get_next_line(fd, &line);
	lem->ants = ft_atoi(line);
	ft_strdel(&line);
	if (!(lem->tunnels = (char**)malloc(sizeof(char*) * (lem->nbr_tunnels))))
		return (1);
	if (!(lem->room_directory = (char**)malloc(sizeof(char*) * (lem->nbr_rooms))))
		return (1);
	lem->tunnels[lem->nbr_tunnels] = NULL;
	lem->room_directory[lem->nbr_rooms] = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		if (!(ft_strstr(line, "-")))
		{
			if (ft_strstr(line, "##start"))
				room->roomtype = 1;
			else if (ft_strstr(line, "##end"))
				room->roomtype = 3;
			if (!(ft_strstr(line, "#")))
				room = get_room(line, room, lem);
		}
		else
		{
			lem->tunnels[i] = ft_strdup(line);
			i++;
		}
		free(line);
	}
	return (0);
}
