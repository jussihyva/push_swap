/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 15:41:12 by jkauppi           #+#    #+#             */
/*   Updated: 2020/01/09 21:16:06 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void			conv_to_upper(char *s)
{
	size_t					i;

	i = -1;
	while (*(s + ++i))
		*(s + i) = ft_toupper(*(s + i));
	return ;
}

static void			set_unsigned_hex_parameter(t_substring *substring)
{
	char					*s;
	unsigned long long		par_value;

	par_value = *(unsigned long long *)substring->par_value;
	if (par_value == 0 && substring->precision == 0)
		save_parameter(substring, "");
	else
	{
		s = ft_ulltoa_base(par_value, 16);
		if (substring->conv_type == 'X')
			conv_to_upper(s);
		if (par_value < 0)
		{
			save_parameter(substring, ft_strdup(s + 1));
			ft_strdel(&s);
		}
		else
			save_parameter(substring, s);
	}
	free(substring->par_value);
	substring->par_value = NULL;
	return ;
}

void				adjust_unsigned_hex(t_substring *substring)
{
	set_unsigned_hex_parameter(substring);
	set_sign(substring);
	set_prefix(substring);
	set_zero_filler(substring);
	set_pre_filler(substring);
	set_post_filler(substring);
	return ;
}

char				*conv_unsigned_hex(va_list *ap, t_substring *substring,
																int *attrs)
{
	unsigned long long		*nbr;

	(*attrs)++;
	nbr = (unsigned long long *)ft_memalloc(sizeof(*nbr));
	if (!substring->param_type)
		*nbr = (unsigned int)(va_arg(*ap, void *));
	else
		*nbr = read_o_u_x_param(substring->param_type->type, ap);
	substring->par_value = nbr;
	if (*nbr < 0)
		substring->par_value_is_neg = 1;
	return (NULL);
}
