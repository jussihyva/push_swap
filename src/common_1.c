/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 18:37:12 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/10 13:37:37 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "checker.h"

char			*merge_args(char **array, int size)
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

static void		add_to_list(t_list **list, int *integer)
{
	t_list		*elem;

	elem = ft_lstnew(integer, sizeof(integer));
	if (*list)
		ft_lstadd_e(list, elem);
	else
		*list = elem;
}

static int		is_dublicate(int integer, int *stack, size_t size)
{
	size_t		c;

	c = 0;
	while (c < size && stack[c] != integer)
		c++;
	if (c < size)
		return (1);
	return (0);
}

static int		conv_and_save(t_input_data *input, char **str_array)
{
	size_t		i;
	int			*stack;
	char		*endptr;

	endptr = NULL;
	stack = (int *)ft_memalloc(sizeof(*stack) * input->int_array_size);
	i = input->int_array_size;
	while (stack && i--)
	{
		stack[i] = ft_strtoi(str_array[input->int_array_size - i - 1],
																&endptr, 10);
		if (errno || (endptr && *endptr) || is_dublicate(stack[i],
								&stack[i + 1], input->int_array_size - i - 1))
			return (1);
		add_to_list(&input->int_list, stack + i);
		input->int_array = stack;
	}
	return (0);
}

int				string_to_array(char *s, t_input_data *input)
{
	char		**str_array;
	int			result;

	result = 0;
	input->int_array = NULL;
	if ((str_array = ft_strsplit(s, ' ')))
	{
		while (*(str_array + input->int_array_size))
			input->int_array_size++;
		result = conv_and_save(input, str_array);
		ft_arraydel(str_array);
	}
	return (result);
}
