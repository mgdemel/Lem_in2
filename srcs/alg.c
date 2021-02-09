#include "../includes/lem_in.h"

int		roomname_scan(t_lem *lem, char *name, int start)
{
	int i;
	int j;
	int	amount;

	i = 0;
	amount = 0;
	while (lem->tunnels[i] != '\0')
	{
		j = 0;
		while (lem->tunnels[i][j] == name[j] || lem->tunnels[i][j] == '-')
			j++;
		if (lem->tunnels[i][j] == '-')
			amount++;
		i++;
	}
	return (amount - start);
}

void		maximum_paths(t_lem *lem)
{
	int	amount;

	amount = 0;
	amount += roomname_scan(lem, lem->start_room_name, 0); // finds the paths leading from start room
	lem->nbr_paths = amount;
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
		newstr[i] = " ";
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

int	make_path(char *child_room, char **tunnels, char *parent_room) // , t_path *path)
{
	int i;
	int save_loc;
	int	room;

	room = 0;
	i = 0;
	save_loc = 0;
	while (tunnels[i])
	{
		if (ft_strstr(tunnels[i], child_room) && (!ft_strstr(tunnels[i], parent_room)))
		{
			if (save_loc != 0)
			{
				parent_room = child_room;
				child_room = needle_crop(tunnels[i], child_room);
				path->start_room = head;
				make_path(child_room, tunnels, parent_room, path->next);
				save_loc = 0;
			}
			else
			{
				parent_room = child_room;
				child_room = needle_crop(tunnels[i], child_room);
				save_loc = i;
			}
		}
		i++;
	}
	return (1);
}



int pathfinding(t_lem *lem, t_room *room)
{
	int		i;
	char	*new_path;
	//t_path	*new_path;
	char	*path;
	//t_path	*path;
	char	*other_room;

	other_room = NULL;
	new_path = NULL;
	path = NULL;
	i = 0;
	if (!(lem->all_paths = (t_path**)malloc(sizeof(t_path*)))) //allocates paths array of structs
		return (1);
	while (lem->tunnels[i])  // we go through all the tunnels
	{
		if (ft_strstr(lem->tunnels[i], lem->start_room_name)) // to find the start room links
		{
			other_room = needle_crop(lem->tunnels[i], lem->start_room_name);
			if(path = make_path(other_room, lem->tunnels, lem->start_room_name)) //, lem->all_paths)) // when we've found a link we make a path
			{
				lem->all_paths[j] == path;
				j++;
				//path = initialize_path(room);
				//new_path = initialize_path(room);
				//path->next = new_path;
				//new_path->prev = path;
			}
		}
	}
	return (0);
}

   r1-r2
   start-r1
-> r2-end



	S
   |  |
   r2 r1
    \   |  \
      - r3 - r4
	   	|		\
		r5 ---  end

	s-r1-r4-end
	s-r1-r3-r4-end
	s-r2-r3-r4-end

	* r1-r4
	//r1-r3-r4
	* r2-r3-r5

