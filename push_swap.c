/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 17:56:31 by jkauppi           #+#    #+#             */
/*   Updated: 2020/01/15 16:49:06 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int				*save_to_stack(char *s, t_sort_result *sort_result)
{
	int			*stack;
	size_t		i;
	int			min;
	int			max;
	char		**string_array;

	stack = NULL;
	min = INT_MAX;
	max = INT_MIN;
	string_array = ft_strsplit(s, ' ');
	while (string_array[sort_result->stack_size])
		sort_result->stack_size++;
	if (string_array)
	{
		i = sort_result->stack_size;
		stack = (int *)ft_memalloc(sizeof(*stack) * sort_result->stack_size);
		while (i--)
		{
			stack[i] = ft_atoi(string_array[sort_result->stack_size - i - 1]);
			max = (stack[i] > max) ? stack[i] : max;
			min = (stack[i] < min) ? stack[i] : min;
		}
		sort_result->average = (max - min) / 2;
	}
	return (stack);
}

static t_sort_result	*init_sort_result(void)
{
	t_sort_result	*sort_result;

	sort_result = (t_sort_result *)ft_memalloc(sizeof(*sort_result));
	sort_result->seq_action_counter = 0;
	sort_result->stack_size = 0;
	sort_result->average = 0;
	sort_result->action_list =
			(char **)ft_strnew(sizeof(*sort_result->action_list) * 10000000);
	return (sort_result);
}

static char				*merge_args(char **array, int size)
{
	char		*s;
	char		*tmp;
	int			c;

	c = -1;
	s = NULL;
	while (++c < size)
	{
		if (s)
		{
			tmp = ft_strjoin(s, array[c]);
			ft_strdel(&s);
			s = tmp;
			tmp = ft_strjoin(s, " ");
			ft_strdel(&s);
			s = tmp;
		}
		else
			s = ft_strjoin(array[c], " ");
	}
	return (s);
}

int						main(int argc, char **argv)
{
	int				size;
	t_sort_result	*sort_result;
	char			*s;

	if (argc > 1)
	{
		sort_result = init_sort_result();
		size = argc - 1;
		s = merge_args(argv + 1, size);
		sort_result->stack = save_to_stack(s, sort_result);
		bubble_sort_v1(sort_result);
		print_action_list(sort_result);
		print_stack(sort_result->stack, sort_result->stack_size);
	}
	return (0);
}
