/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 18:37:12 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/13 19:53:11 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "checker.h"

char						*merge_args(char **array, int size)
{
	char		*s;
	char		*tmp;
	int			c;

	c = 0;
	s = ft_strdup(array[c]);
	while (++c < size)
	{
		tmp = ft_strjoin(s, " ");
		ft_strdel(&s);
		s = ft_strjoin(tmp, array[c]);
		ft_strdel(&tmp);
	}
	return (s);
}

static void					add_to_list(t_list **list, int *integer)
{
	t_list		*elem;

	elem = ft_lstnew(integer, sizeof(integer));
	if (*list)
		ft_lstadd_e(list, elem);
	else
		*list = elem;
}

static int					is_dublicate(int integer, int *stack, size_t size)
{
	size_t		c;

	c = 0;
	while (c < size && stack[c] != integer)
		c++;
	if (c < size)
		return (1);
	return (0);
}

static t_validation_result	conv_and_save(t_input_data *input, char **str_array)
{
	size_t		i;
	int			*stack;
	char		*endptr;
	char		*s;

	endptr = NULL;
	stack = (int *)ft_memalloc(sizeof(*stack) * input->int_array_size);
	i = input->int_array_size;
	while (stack && i--)
	{
		s = str_array[input->int_array_size - i - 1];
		stack[i] = ft_strtoi(s, &endptr, 10);
		if (errno || (endptr && *endptr) || is_dublicate(stack[i],
								&stack[i + 1], input->int_array_size - i - 1))
			return (error);
		add_to_list(&input->int_list, stack + i);
		input->int_array = stack;
	}
	return (ok);
}

int							string_to_array(char *s, t_input_data *input)
{
	char						**str_array;
	t_validation_result			result;

	result = ok;
	input->int_array = NULL;
	if ((str_array = ft_strsplit(s, ' ')))
	{
		if (*str_array)
		{
			while (*(str_array + input->int_array_size))
				input->int_array_size++;
			result = conv_and_save(input, str_array);
		}
		else
			result = no_param;
		ft_arraydel(str_array);
	}
	return (result);
}
