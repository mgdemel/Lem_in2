/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasanoj <lvasanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 14:26:21 by lvasanoj          #+#    #+#             */
/*   Updated: 2021/06/11 18:54:23 by lvasanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>

/*
**	STRUCTS
*/

typedef struct s_ftprintf
{
	int			percentages;
	int			char_count;
	char		*letters;
	const char	*format;
	int			printed;
	int			type;
	int			width;
	int			minus;
	int			zero;
	int			dot;
	int			star;
	int			x_case;
	int			short_h;
	int			long_l;
	int			j;
	int			large_l;
	int			hash;
	int			plus;
	int			space;
	int			save_remainder;
	int			float_comp;
	int			dot2;
	int			intcopy;
	long double	save;
	char		*octal_num;
	char		*prev_octal;
	int			isneg;
	int			increase;
}				t_ftprintf;

/*
**	PROTOTYPES
*/

void			initialize(t_ftprintf *p);
void			init_flags(t_ftprintf *flags);
int				is_f(int c);
int				is_t(int c);
int				flag_dot(const char *copy, int start, t_ftprintf *flags,
					va_list args);
void			flag_width(va_list args, t_ftprintf *flags);
void			flag_digit(char c, t_ftprintf *flags);
void			flag_minus(t_ftprintf *flags);
int				flag_short_or_long(t_ftprintf *flags, char first, char second);
void			treatment(char type, t_ftprintf *flags, va_list args);
intmax_t		typecast_num(t_ftprintf *flags, va_list args);
intmax_t		typecast_uoxx(t_ftprintf *flags, va_list args);
void			treat_string(char *str, t_ftprintf *flags);
void			treat_char(char c, t_ftprintf *flags);
void			treat_width(int width, int minus, int if_zero,
					t_ftprintf *flags);
int				treat_d(intmax_t arg, t_ftprintf *flags);
void			putstrprecision(char *str, int precision, t_ftprintf *flags);
int				treat_u(unsigned long long u, t_ftprintf *flags);
int				treat_x(uintmax_t x, t_ftprintf *flags);
int				treat_f(char *arg, t_ftprintf *flags, double n);
char			*decimal_to_hexa(uintmax_t n, t_ftprintf *flags);
int				treat_p(unsigned long long p, t_ftprintf *flags);
int				treat_o(unsigned long long o, t_ftprintf *flags);
void			fltoascii(long double n, t_ftprintf *flags);
long double		ftoa_helper(char *big);
int				count_big_f(long double f);
long double		ten_pow(int pow);
char			*increase_last_big(char *str);
char			*increase_last(char *str, t_ftprintf *flags);
char			*small_f(long double f, int p, char *big);
char			*big_f(long double f);
char			set_sign_f(long double f, t_ftprintf *flags);
char			*calc_octal(unsigned long long decimal);
int				is_not_str(char *str);
void			treat_d_putchar(char *num, int i, t_ftprintf *flags);
void			put_part_d(int i, char *num, t_ftprintf *flags);
char			*ft_itoa_new(intmax_t n, t_ftprintf *flags);
int				ft_printf(const char *format, ...);

#endif
