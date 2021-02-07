#include "../includes/lem_in.h"

void test_array(char **array)
{
    int i;

    i = 0;
    while (array[i] != NULL)
    {
        ft_putstr(array[i]);
        ft_putchar('\n');
        i++;
    }
}

void test_structs(t_lem *lem)
{
    // ********    LEM:    ********
    ft_putstr("ants: ");
    ft_putnbr(lem->ants);
    ft_putchar('\n');

    ft_putstr("nbr_tunnels: ");
    ft_putnbr(lem->nbr_tunnels);
    ft_putchar('\n');

    ft_putstr("nbr_rooms: ");
    ft_putnbr(lem->nbr_rooms);
    ft_putchar('\n');

    ft_putstr("nbr_paths: ");
    ft_putnbr(lem->nbr_paths);
    ft_putchar('\n');

    ft_putstr("nbr_paths: ");
    ft_putnbr(lem->nbr_paths);
    ft_putchar('\n');

    ft_putstr("found_start_end: ");
    ft_putnbr(lem->found_start_end);
    ft_putchar('\n');

    ft_putstr("paths_found: \n");
    test_array(lem->paths_found);
    ft_putchar('\n');

    ft_putstr("tunnels: \n");
    test_array(lem->tunnels);
    ft_putchar('\n');

    ft_putstr("start room name: \n");
    ft_putstr(lem->start_room_name);
    ft_putchar('\n');

    ft_putstr("end room name: \n");
    ft_putstr(lem->end_room_name);
    ft_putchar('\n');

   // ********    ROOM FROM START TO END:    ********
    
    t_room *room = lem->all_rooms;
    while (room->next != NULL)
    {
        ft_putstr("name: ");
        ft_putstr(room->name);
        ft_putchar('\n');

        ft_putstr("x: ");
        ft_putnbr(room->x);
        ft_putchar('\n');

        ft_putstr("y: ");
        ft_putnbr(room->y);
        ft_putchar('\n');

        ft_putstr("roomtype: ");
        ft_putnbr(room->roomtype);
        ft_putchar('\n');
        ft_putchar('\n');

        ft_putstr("first: ");
        ft_putnbr(room->first);
        ft_putchar('\n');
        ft_putchar('\n');

        room = room->next;
    }

    // ********    ROOM FROM END TO START:    ********

    t_room *room = lem->all_rooms;
    while (room->next != NULL)
        room = room->next;
    while (room->prev != NULL)
    {
        ft_putstr("name: ");
        ft_putstr(room->name);
        ft_putchar('\n');

        ft_putstr("x: ");
        ft_putnbr(room->x);
        ft_putchar('\n');

        ft_putstr("y: ");
        ft_putnbr(room->y);
        ft_putchar('\n');

        ft_putstr("roomtype: ");
        ft_putnbr(room->roomtype);
        ft_putchar('\n');
        ft_putchar('\n');

        ft_putstr("first: ");
        ft_putnbr(room->first);
        ft_putchar('\n');
        ft_putchar('\n');

        room = room->prev;
    }
}