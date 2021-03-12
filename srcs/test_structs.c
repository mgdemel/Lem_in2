#include "../includes/lem_in.h"

void test_array(t_lem *lem)
{
    int i;

    i = 0;
    while (i < lem->nbr_tunnels)
    {
        ft_printf("%s\n", lem->tunnels[i]);
        i++;
    }
}

void test_array2(t_lem *lem)
{
    int i;

    i = 0;
    while (i < lem->nbr_rooms)
    {
        ft_printf("%s\n", lem->room_directory[i]);
        i++;
    }
}

void scan_tree(t_tree *start, t_lem *lem, int i)
{
    t_tree *tree;

	ft_printf("STARTED SCAN_TREE\n");
    tree = start;
    i = 0;
    sleep(2);
	ft_printf("name %s\n", tree->name);
    //  ft_printf("child name %s\n", tree->child->name);
    //  ft_printf("sibling pointer address %p\n", tree->sibling);
    while (ft_strcmp(tree->name, lem->end_room_name) != 0)
    {
        ft_putchar('\n');
        ft_printf("Step %d\n", lem->path);
        ft_printf("name of current room %s|\n", tree->name);
        ft_printf("child is %s\n", tree->child->name);
        lem->path++;
        if (tree->sibling != NULL)
        {
            ft_printf("Changing PATH, found sibling\n");
            ft_printf("parent is %s\n", tree->parent->name);
            scan_tree(tree->sibling, lem, lem->path);
        }
        tree = tree->child;
    }
}

void scan_rooms(t_lem *lem)
{
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

        ft_putstr("roomnum: ");
        ft_putnbr(room->roomnum);
        ft_putchar('\n');
        ft_putchar('\n');

        room = room->next;
    }
}

void print_lem(t_lem *lem)
{
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
    test_array(lem);
    ft_putchar('\n');

    ft_putstr("room directory: \n");
    test_array(lem);
    ft_putchar('\n');

    ft_putstr("start room name: \n");
    ft_putstr(lem->start_room_name);
    ft_putchar('\n');

    ft_putstr("end room name: \n");
    ft_putstr(lem->end_room_name);
    ft_putchar('\n');
}

void test_structs(t_lem *lem)
{
    // t_tree *start = lem->tree;
	lem->max_paths = lem->max_paths;
    ft_putchar('\n');
    ft_putchar('\n');

    // ********    LEM:    ********
    ft_printf("********    LEM TESTING:    ********\n");
    ft_printf("********    PRINT INFO:    ********\n\n");
  //  print_lem(lem);

    // ********    ROOM FROM START TO END:    ********
    ft_printf("********    SCAN ROOMS:    ********\n\n");

  //  scan_rooms(lem);

    // ********   PATH FROM START TO END:    ********
    // ft_printf("********    SCAN THE TREE OF ROOMS:    ********\n\n");
	// ft_printf("BEFORE STARTING SCAN_TREE\n");
    // scan_tree(start, lem, 1);
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