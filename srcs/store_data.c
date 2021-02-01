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

void 	get_room_data(char *line, t_room *room, int roomtype)
{
	int		i;
	char	**coord;
	i = 0;

	ft_putstr("In get room data: ");
	ft_putstr(line);
	ft_putchar('\n');
	room->roomtype = roomtype;
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

t_room		*get_room(char *line, t_lem *lem, t_room *room, int fd)
{
	t_room *new_room;

	new_room = initialize_room();
	room->next = new_room;
	if (room->first == 0)
	{
		lem->temp = room;
		room->prev = lem->temp;
		get_room_data(line, new_room, fd);
	}
	get_room_data(line, room, fd);
	return(new_room);
}

int				store_data(char *line, t_lem *lem, t_room *room, int fd)
{
	int i;
	int roomtype;

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
			ft_putstr("In GNL while loop: ");
			ft_putstr(line);
			ft_putchar('\n');
			roomtype = 2;
			if (!(ft_strstr(line, "-") && ft_strstr((char*)line, "##")))
			{
				if (ft_strstr((char*)line, "##start"))
				{
					roomtype = 1;
					ft_strdel(&line);
					get_next_line(fd, &line);
				}
				else if (ft_strstr((char*)line, "##end"))
				{
					roomtype = 3;
					ft_strdel(&line);
					get_next_line(fd, &line);
				}
			}
			if (!(ft_strstr(line, "-") && (!(ft_strstr((char*)line, "##")))))
				room = get_room(line, lem, room, roomtype);
			else
			{
				lem->tunnels[i] = ft_strdup(line);
				i++;
			}
	//	}
	}
	return (0);
}
