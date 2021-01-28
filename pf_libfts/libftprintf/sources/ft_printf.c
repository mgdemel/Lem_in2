/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasanoj <lvasanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 14:24:29 by lvasanoj          #+#    #+#             */
/*   Updated: 2020/09/01 22:28:26 by lvasanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

/*
**	Here we return the index we need it to be depending on the flag
**	and also check and save what flag there is to be treated in
**	the treatment in handle_copy.
*/

static int	flag_ifs(const char *copy, int i, t_ftprintf *flags, va_list args)
{
	if (copy[i] == '0' && flags->width == 0 && flags->minus == 0)
		flags->zero = 1;
	if (copy[i] == '.')
		i = flag_dot(copy, i, flags, args);
	if (copy[i] == '-')
		flag_minus(flags);
	if (copy[i] == '*')
		flag_width(args, flags);
	if (copy[i] == 'h' || copy[i] == 'l' ||
	(copy[i] == 'L' && copy[i + 1] == 'f') || copy[i] == 'j' || copy[i] == 'L')
		i += flag_short_or_long(flags, copy[i], copy[i + 1]);
	if (copy[i] == '#')
		flags->hash = 1;
	if (copy[i] == '+')
		flags->plus = 1;
	if (copy[i] == ' ')
		flags->space = 1;
	if (ft_isdigit(copy[i]))
		flag_digit(copy[i], flags);
	return (i);
}

int			flag_parsing(const char *copy, int i, t_ftprintf *flags,
va_list args)
{
	while (copy[i])
	{
		if (!ft_isdigit(copy[i]) && !is_t(copy[i]) && !is_f(copy[i]))
			break ;
		i = flag_ifs(copy, i, flags, args);
		if (is_t(copy[i]))
		{
			flags->type = copy[i];
			break ;
		}
		i++;
	}
	return (i);
}

/*
**	Here we create a struct with flags so we can save what flags are being
**	used for each moment in the string. We put an infinite loop here and
**	make a break point if we notice that our string is at the end. So we
**	initialize the flags first and then start checking if we find a %
**	sign, and the next char	has something.
**	Then we change the index i at the same time as we parse the flags.
**
**	After that we check if the character after % is in the type list and if so
**	we add to the character counter as well as treat whatever the type asked
**	for. If it isn't we add to the char counter and putchars the character and
**	continue the loop.
*/

int			found_percentage(const char *copy, va_list args, t_ftprintf *p,
int i)
{
	i = flag_parsing(copy, (i + 1), p, args);
	if (is_t(copy[i]))
		treatment((char)p->type, p, args);
	else if (copy[i])
	{
		p->char_count++;
		ft_putchar(copy[i]);
	}
	return (i);
}

int			handle_copy(const char *copy, va_list args, t_ftprintf *p)
{
	int			i;
	int			len;

	i = 0;
	len = 0;
	while (1)
	{
		init_flags(p);
		if (!copy[i])
			break ;
		else if (copy[i] == '%' && copy[i + 1])
			i = found_percentage(copy, args, p, i);
		else if (copy[i] != '%')
		{
			p->char_count++;
			ft_putchar(copy[i]);
		}
		i++;
		len += p->char_count;
		ft_bzero(p, sizeof(p));
	}
	return (len);
}

/*
**	Here we start by making a copy of our format that was given,
**	and initialize the values in the ftprintf struct for future use.
**	And we start using the stdarg functions by saving in the va_list
**	args the arguments after format.
**
**	We send the copy and the args over to handle_copy. We end the args
**	and free the copy in the end before returning.
*/

int			ft_printf(const char *format, ...)
{
	const char	*copy;
	va_list		args;
	t_ftprintf	*p;
	int			characters;

	copy = ft_strdup(format);
	if (!(p = (t_ftprintf*)malloc(sizeof(t_ftprintf))))
		return (-1);
	initialize(p);
	va_start(args, format);
	characters = handle_copy(copy, args, p);
	va_end(args);
	free(p);
	free((char *)copy);
	return (characters);
}
