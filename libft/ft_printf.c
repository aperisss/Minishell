/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppajot <ppajot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 18:53:08 by ppajot            #+#    #+#             */
/*   Updated: 2022/05/24 15:17:19 by ppajot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	putnbr_flags(va_list arg, t_flags flags, int *count, char convert)
{
	long	i;
	int		minsize;
	int		a;

	i = va_arg(arg, long);
	i = ft_convert(i, convert);
	minsize = getsize_base(i, flags, convert);
	if (convert == 'p' && !i)
		minsize = 5;
	a = hassign(i, flags, convert) + ft_max(minsize, flags.precision);
	if (flags.leftzero)
		return (putnbrleftzero(i, flags, count, convert));
	if (!flags.rightfill && flags.minsize > a)
		ft_fill(' ', flags.minsize - a, count);
	if (flags.precision >= 0)
		putsign(&i, flags, count, convert);
	if (flags.precision >= 0 && flags.precision > minsize)
		minsize += ft_fill('0', flags.precision - minsize, count);
	if (flags.precision == -1)
		putsign(&i, flags, count, convert);
	if (!(flags.precision == 0 && i == 0))
		ft_putnbr(i, convert, count);
	if (flags.rightfill && flags.minsize > a)
		ft_fill(' ', flags.minsize - a, count);
}

void	ft_putnbr(long i, char convert, int *count)
{
	if (convert == 'i' || convert == 'd')
		ft_putnbr_long(i, "0123456789", count);
	if (convert == 'u')
		ft_putnbr_long(i, "0123456789", count);
	if (convert == 'x')
		ft_putnbr_long(i, "0123456789abcdef", count);
	if (convert == 'X')
		ft_putnbr_long(i, "0123456789ABCDEF", count);
	if (convert == 'p' && i)
		ft_putnbr_long(i, "0123456789abcdef", count);
	else if (convert == 'p' && !i)
	{
		write(1, "(nil)", 5);
		*count += 5;
	}
}

void	ft_flags(char **str, t_flags *flags)
{
	while (isflags(**str))
	{
		if (**str == '#')
			flags->hexprefix = 1;
		if (**str == '-' )
		{
			flags->rightfill = 1;
			flags->leftzero = 0;
		}
		if (**str == '0' && flags->rightfill == 0)
			flags->leftzero = 1;
		if (**str == '+')
			flags->spacesign = 2;
		if (**str == ' ' && !flags->spacesign)
			flags->spacesign = 1;
		(*str)++;
	}
	if (**str >= '1' && **str <= '9')
		flags->minsize = atoi_move(str);
	if (**str == '.')
	{	
		(*str)++;
		flags->precision = atoi_move(str);
		flags->leftzero = 0;
	}
}

const char	*ft_put(va_list arg, const char *format, t_flags *flags, int *count)
{
	ft_flags((char **)&format, flags);
	if (*format == '%')
	{
		write(1, format, 1);
		(*count)++;
	}
	else if (*format == 'c')
		putchar_flags(arg, *flags, count);
	else if (*format == 's')
		putstring_flags(arg, *flags, count);
	else if (*format == 'p')
	{
		flags->precision = -1;
		flags->hexprefix = 1;
		putnbr_flags(arg, *flags, count, 'p');
	}
	else if (*format == 'u')
	{
		flags->spacesign = 0;
		putnbr_flags(arg, *flags, count, *format);
	}
	else if (*format == 'd' || *format == 'i'
		|| *format == 'x' || *format == 'X')
		putnbr_flags(arg, *flags, count, *format);
	return (format + 1);
}

int	ft_printf(const char *format, ...)
{
	va_list	arg;
	int		count;
	t_flags	flags;

	count = 0;
	va_start(arg, format);
	while (*format && count >= 0)
	{
		if (*format == '%')
		{	
			format++;
			setflags(&flags);
			format = ft_put(arg, format, &flags, &count);
		}
		else
		{
			count++;
			write(1, format++, 1);
		}
	}
	va_end(arg);
	return (count);
}

/*
int main()
{
	ft_printf("%2.0i2\n", 0);
	printf("%2.0i2\n", 0);
}
*/