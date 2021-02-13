#include "../includes/lem_in.h"

int		roomname_scan(t_lem *lem, char *name)
{
	int i;
	int	amount;

	i = 0;
	amount = 0;
	while (lem->tunnels[i] != NULL)
	{
		ft_printf("tunnels is: %s\n", lem->tunnels[i]);
		if (ft_strstr(lem->tunnels[i], name))
		{
			amount++;
			ft_printf("Amount inside strstr statement: %i\n", amount);
		}
		i++;
	}
	ft_printf("Amount before returning %d\n", amount);
	if (ft_strcmp(name, lem->start_room_name) && (amount - 2) >= 0)
	{
		ft_printf("FIRST\n");
		return (amount - 2);
	}
	else if (amount - 2 < 0 && (!(ft_strcmp(name, lem->start_room_name))))
	{
		ft_printf("SECOND\n");
		return (0);
	}
	else
	{
		ft_printf("THIRD\n");
		return (amount);
		
	}
}

void	maximum_paths(t_lem *lem)
{
	int	amount;

	amount = 0;
	while (lem->all_rooms->next != NULL)
	{
		ft_printf("Allroom name is %s, Startroom name is %s\n", lem->all_rooms->name, lem->start_room_name);
		amount += roomname_scan(lem, lem->all_rooms->name);
		ft_printf("\n\n");
		lem->all_rooms = lem->all_rooms->next;
	}
	lem->nbr_paths = amount;
	ft_printf("lem->nbr_paths: %i\n", lem->nbr_paths);
}

char		*ft_strjoin_spc(char const *s1, char const *s2)
{
	int		i;
	int		j;
	int		len;
	char	*newstr;

	i = 0;
	j = 0;
	len = (ft_strlen((char *)s1) + ft_strlen((char *)s2)) + 1;
	if ((newstr = (char *)malloc(sizeof(char) * len + 1)))
	{
		while (s1[i] != '\0')
		{
			newstr[i] = s1[i];
			i++;
		}
		newstr[i] = ' ';
		i++;
		while (s2[j] != '\0')
		{
			newstr[i + j] = s2[j];
			j++;
		}
		newstr[i + j] = '\0';
		return (newstr);
	}
	else
		return (NULL);
}

int	make_path(char *child_room, char *parent_room, t_lem *lem)
{
	int i;
	int save_loc;
	int	room;

	room = 0;
	i = 0;
	save_loc = 0;
	while (lem->tunnels[i])
	{
		if (ft_strstr(lem->tunnels[i], child_room) && (!ft_strstr(lem->tunnels[i], parent_room)))
		{
			if (ft_strstr(lem->tunnels[i], needle_crop(lem->tunnels[save_loc], parent_room)))
			{
				parent_room = child_room;
				child_room = needle_crop(lem->tunnels[i], child_room);
				make_path(child_room, parent_room, lem);
				save_loc = 0;
			}
			else
			{
				parent_room = child_room;
				child_room = needle_crop(lem->tunnels[i], child_room);
				lem->all_paths[lem->path_index] = ft_strjoin(parent_room, child_room);
				save_loc = i;
			}
		}
		i++;
	}
	lem->path_index++;
	return (1);
}

int pathfinding(t_lem *lem)
{
	int		i;
	int		j;
	char	*other_room;

	other_room = NULL;
	i = 0;
	j = 0;
	maximum_paths(lem);
	if (!(lem->all_paths = (char**)malloc(sizeof(char*) * lem->nbr_paths))) //allocates paths array of structs
		return (1);
	while (lem->tunnels[i])  // we go through all the tunnels
	{
		if (ft_strstr(lem->tunnels[i], lem->start_room_name)) // to find the start room links
		{
			other_room = needle_crop(lem->tunnels[i], lem->start_room_name);
			if(make_path(other_room, lem->start_room_name, lem)) // when we've found a link we make a path
			{

			}
		}
	}
	return (0);
}

