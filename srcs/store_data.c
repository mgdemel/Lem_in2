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

void 	get_room_data(char *line, t_room *room)
{
	int		i;
	char	**coord;

	i = 0;
	if (!(room->name = (char*)malloc(sizeof(char) * ((int)ft_strlen(line) + 1))))
		ft_putstr("ERROR. COULD NOT MALLOC ROOM NAME\n");
	line[(int)ft_strlen(line) + 1] = '\0';
	while (line[i] != ' ') //stores the name of the room
	{
		room->name[i] = line[i];
		i++;
	}
	i++; //moves past next space to get to coords
	if (!(coord = ft_strsplit(&line[i], ' ')))
		ft_putstr("ERROR IN FT_STRSPLIT - GET_ROOM FUNCTION");
	room->x = ft_atoi(coord[0]);
	room->y = ft_atoi(coord[1]);
	free_array(coord);
}

t_room		*get_room(char *line, t_room *room)
{
	t_room *new_room;

	new_room = initialize_room();
	room->next = new_room;
	new_room->prev = room;
	get_room_data(line, room);
	return(new_room);
}

int				store_data(char *line, t_lem *lem, t_room *room, int fd)
{
	int i;

	i = 0;
	get_next_line(fd, &line);
	lem->ants = ft_atoi(line);
	ft_strdel(&line);
	if (!(lem->tunnels = (char**)malloc(sizeof(char*) * (lem->nbr_tunnels)))) //allocates tunnels array
		return (1);
	while (get_next_line(fd, &line) > 0)
	{
	//	if (line[0] == '#' && line[1] != '#') nevermind doesn't work, fix this lukas!
	//	{	
			if (!(ft_strstr(line, "-")))
			{
				if (ft_strstr((char*)line, "##start"))
					room->roomtype = 1;
				else if (ft_strstr((char*)line, "##end"))
					room->roomtype = 3;
				if (!(ft_strstr((char*)line, "##")))
					room = get_room(line, room);
			}
			else
			{
				lem->tunnels[i] = ft_strdup(line);
				i++;
			}
	//	}
	}
	return (0);
}
