#include "../libftprintf/ft_printf.h"

void test_array(char *arr)
{
    int i;
    int j;
    i = 0;
    j = 0;
    while (i < arr)
    {
        ft_putstr(arr[i]);
        ft_putchar('\n');
        i++;
    }
}

void test_structs(t_lem *lem, t_room *r_data)
{
    int i;
    int j;

    i = 0;
    j = 0;

    // ********    LEM:    ********
    ft_putstr("ants: ");
    ft_putnbr(lem->ants);
    ft_putchar('\n');

    ft_putstr("nbr_tunnels: ");
    ft_putnbr(lem->nbr_tunnels);
    ft_putchar('\n');

    ft_putstr("tunnels: ");
    test_array(lem->tunnels);
    ft_putchar('\n');

    // ********    ROOM:    ********
    while (r_data->next)
    {
        ft_putstr("name: ");
        ft_str(r_data->name);
        ft_putchar('\n');

        ft_putstr("x: ");
        ft_putnbr(r_data->x);
        ft_putchar('\n');

        ft_putstr("y: ");
        ft_putnbr(r_data->y);
        ft_putchar('\n');

        ft_putstr("roomtype: ");
        ft_putnbr(r_data->roomtype);
        ft_putchar('\n');

        r_data->next++;
    }
}