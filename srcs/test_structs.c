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
    ft_putchar('\n');
    ft_putchar('\n');
    
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

    ft_putstr("found_start_end: ");
    ft_putnbr(lem->found_start_end);
    ft_putchar('\n');

    // ft_putstr("all_paths: \n");
    // test_array(lem->all_paths);
    // ft_putchar('\n');

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

        room = room->next;
    }

    // // ********    ROOM FROM END TO START:    ********    //prev may not be working. Check this later
    // ft_printf("check\n");
    // t_room *room2 = lem->all_rooms;
    // ft_printf("check\n");
    // while (room2->next != NULL)
    //     room2 = room2->next;
    // ft_printf("check\n");
    // while (room2->prev != NULL)
    // {
    //     ft_putstr("name: ");
    //     ft_putstr(room2->name);
    //     ft_putchar('\n');

    //     ft_putstr("x: ");
    //     ft_putnbr(room2->x);
    //     ft_putchar('\n');

    //     ft_putstr("y: ");
    //     ft_putnbr(room2->y);
    //     ft_putchar('\n');

    //     ft_putstr("room2type: ");
    //     ft_putnbr(room2->roomtype);
    //     ft_putchar('\n');
    //     ft_putchar('\n');

    //     room2 = room2->prev;
    // }

     // ********   PATH FROM START TO END:    ********
    
    t_tree *tree = lem->tree;
    while (tree->name != NULL)
    {
        ft_putstr("name of head node of tree: ");
        ft_putstr(tree->name);
        ft_putchar('\n');

        tree = tree->sibling;
    }

    // ft_putstr("name of parent: ");
    // ft_putstr(tree->parent->name);
    // ft_putchar('\n');

    // ft_putstr("name of child: ");
    // ft_putstr(tree->child->name);
    // ft_putchar('\n');

    // ft_putstr("name of sibling: ");
    // ft_putstr(tree->sibling->name);
    // ft_putchar('\n');
    
}