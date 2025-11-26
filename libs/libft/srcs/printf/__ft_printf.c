/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __ft_printf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:11:54 by yyyyyy            #+#    #+#             */
/*   Updated: 2025/09/23 17:26:21 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// NOTE: this surely does NOT work uwu

#ifdef ALLOW_MALLOC
#include "__ft_printf.h"

static void init_token(char *format, char **token_start, t_token_type *token_type)
{
	*token_start = format;
	if (*format == '%')
		*token_type = __TT_CONVERT;
	else
		*token_type = __TT_RAW;
}

static void save_raw(t_buff *buff, char *data, usz len)
{
	t_buff raw_buff;
	t_buff new_buff;

	raw_buff.data = data;
	raw_buff.len = len;
	new_buff = ft_bufcat(*buff, raw_buff);
	ft_bufclear(*buff);
	*buff = new_buff;
}

static t_buff convert(va_list *arguments, char chartype, usz precision)
{
	switch (chartype)
	{
	case 'd':
	case 'i':

		break;

	default:
		break;
	}
}

static void convert_arg(t_buff *buff, va_list *arguments, char *start)
{
	t_conversion conversion;
	t_buff converted;

	while (ft_strchr(__FLAGS, *start))
	{
		switch (*start)
		{
		case '-':
			conversion.left_justify = TRUE;
			break;
		case '0':
			conversion.zero_padding = TRUE;
			break;
		case '#':
			conversion.alternate_form = TRUE;
			break;
		case ' ':
			conversion.space_for_positive = TRUE;
			break;
		case '+':
			conversion.always_sign = TRUE;
			break;
		default:
			break;
		}
		start++;
	}
	conversion.minimal_width = 0;
	while (ft_isdigit(*start))
	{
		conversion.minimal_width *= 10;
		conversion.minimal_width += *start - '0';
		start++;
	}
	conversion.precision = 0;
	if (*start++ == '.')
		while (ft_isdigit(*start))
		{
			conversion.precision *= 10;
			conversion.precision += *start - '0';
			start++;
		}
	while (!ft_strchr(__TYPES, *start))
		start++;
	converted = convert(arguments, *start, conversion.precision);
	format(&converted, conversion);
	freeing_bufcat(buff, converted);
}

void __ft_printf(char *format, va_list arguments, t_buff *buff)
{
	char *token_start;
	t_token_type token_type;

	while (*format)
	{
		switch (token_type)
		{
		case __TT_UNKNOWN:
			init_token(format, &token_start, &token_type);
			continue;
		case __TT_RAW:
			if (*format == '%')
			{
				save_raw(buff, token_start, format - token_start);
				token_type = __TT_UNKNOWN;
				continue;
			}
			break;
		case __TT_CONVERT:
			if (ft_strchr(__TYPES, *format))
			{
				convert_arg(buff, &arguments, token_start);
				token_type = __TT_UNKNOWN;
			}
			break;
		}
		format++;
	}
	if (token_type == __TT_RAW)
		save_raw(buff, token_start, format - token_start);
}
#endif
