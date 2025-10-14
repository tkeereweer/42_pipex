/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkeerewe <mkeerewe@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 19:32:27 by mkeerewe          #+#    #+#             */
/*   Updated: 2025/09/04 10:35:28 by mkeerewe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_is_spec(char c)
{
	if (c == '%' || c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i'
		|| c == 'u' || c == 'x' || c == 'X')
	{
		return (1);
	}
	return (0);
}

static int	ft_getformat(const char *str, int i, t_format *format)
{
	format->ht = 0;
	format->plus = 0;
	format->space = 0;
	while (ft_is_spec(str[i]) == 0)
	{
		if (str[i] == '#')
			format->ht = 1;
		else if (str[i] == ' ')
			format->space = 1;
		else if (str[i] == '+')
			format->plus = 1;
		i++;
	}
	return (i);
}

static int	ft_print(const char *str, va_list *args, t_format *format, int i)
{
	int	ret;

	ret = 0;
	if (str[i] == '%')
		ret = ft_putchar('%');
	else if (str[i] == 'c')
		ret = ft_putchar(va_arg(*args, int));
	else if (str[i] == 's')
		ret = ft_putstr(va_arg(*args, char *));
	else if (str[i] == 'p')
		ret = ft_putptr(va_arg(*args, void *));
	else if (str[i] == 'd' || str[i] == 'i')
		ret = ft_putnbr(va_arg(*args, int), format);
	else if (str[i] == 'u')
		ret = ft_putuint(va_arg(*args, unsigned int), 0);
	else if (str[i] == 'x')
		ret = ft_puthex(va_arg(*args, int), 0, format);
	else if (str[i] == 'X')
		ret = ft_puthex(va_arg(*args, int), 1, format);
	return (ret);
}

int	ft_printf(const char *str, ...)
{
	va_list		args;
	t_format	format;
	int			i;
	int			ret;

	va_start(args, str);
	i = 0;
	ret = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			i++;
			i = ft_getformat(str, i, &format);
			ret += ft_print(str, &args, &format, i);
		}
		else
			ret += ft_putchar(str[i]);
		i++;
	}
	va_end(args);
	return (ret);
}
