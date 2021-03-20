#include "../includes/lem_in.h"

static int	check_tunnel_validity(char *line, t_lem *lem)
{
	if (ft_strstr(line, "-") || ft_strstr(line, "#"))
	{
		if (ft_strstr(line, "#"))
			return (0);
		lem->nbr_tunnels++;
		if (!(lem->tunnels = (char**)malloc(sizeof(char*) * (lem->nbr_tunnels))))
			return (1);
	}
	else
		return (1);
	return (0);
}

int	check_rooms_validity(char *line, t_lem *lem)
{
	int i;
	int valid;

	valid = 0;
	i = 0;
	if (ft_strstr(line, "##start") || ft_strstr(line, "##end"))
	{
		lem->found_start_end++;
		return (0);
	}
	else if (!(ft_strstr(line, "-")))
	{
		if (ft_strstr(line, "#"))
			return (0);
		else
		{
			while (line[i] != '\0')
			{
				if (line[i] == ' ')
					valid++;
				i++;
			}
			lem->nbr_rooms++;
		}
	}
	if (valid == 2)
		return (0);
	return (1);
}

int 	get_room_data(char *line, t_room *room, t_lem *lem)
{
	int		len;
	int i;

	len = 0;
	while (line[len] != ' ')
		len++;
	if (!(room->name = (char*)malloc(sizeof(char) * len + 1)))
		return (1);
	line[len] = '\0';
	i = len;
	while (len > 0) //stores the name of the room
	{
		len--;
		room->name[len] = line[len];
	}
	ft_printf("room->name: %s\n", room->name);
	ft_printf("roomtype: %d\n", room->roomtype);
	if (room->roomtype == 1 || room->roomtype == 3)
	{
		if(room->roomtype == 1)
			lem->start_room_name = ft_strdup(room->name);
		else
			lem->end_room_name = ft_strdup(room->name);
	}
	i++;
	room->x = ft_atoi(&line[i]);
	while (line[i] != ' ')
		i++;
	room->y = ft_atoi(&line[i]);
	ft_printf("x: %d\ny: %d\n", room->x, room->y);
	return (0);
}

t_room		*get_room(char *line, t_room *room, t_lem *lem)
{
	room->next = initialize_room(lem);
	get_room_data(line, room, lem);
	return(room->next);
}

int				store_data(t_lem *lem, t_room *room, int fd)
{
	int i;
	char *line;

	i = 0;
//	line = NULL;
	get_next_line(fd, &line);
	if (!ft_isalldigit(line))
		return (1);
	lem->ants = ft_atoi(line);
	ft_strdel(&line);
	ft_printf("nbr_tunnels: %d\n", lem->nbr_tunnels);
	
	lem->tunnels[lem->nbr_tunnels] = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		if (!(ft_strstr(line, "-")))
		{
			if (check_rooms_validity(line, lem) == 1 || lem->found_start_end > 2)
				return (1);
			if (ft_strstr(line, "##start"))
				room->roomtype = 1;
			else if (ft_strstr(line, "##end"))
				room->roomtype = 3;
			if (!(ft_strstr(line, "#")))
				room = get_room(line, room, lem);
		}
		else
		{
			if (check_tunnel_validity(line, lem) == 1 || lem->found_start_end != 2 || lem->nbr_rooms == 0)
				return (1);
			ft_printf("i = %d\n", i);
			lem->tunnels[i] = ft_strdup(line);
			i++;
			ft_printf("Went in tunnel checking\n");
		}
		ft_strdel(&line);
	}
	ft_printf("ended store data\n");
	while (1);
	return (0);
}
