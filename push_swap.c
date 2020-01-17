/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 17:56:31 by jkauppi           #+#    #+#             */
/*   Updated: 2020/01/17 10:20:02 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int				count_median(int *array, size_t size)
{
	int			median;
	int			is_sorted;
	size_t		c;

	is_sorted = 0;
	while (!is_sorted)
	{
		is_sorted = 1;
		c = -1;
		while (++c < size - 1)
		{
			if (array[c] > array[c + 1])
			{
				ft_int_swap(array + c, array + c + 1);
				is_sorted = 0;
			}
		}
	}
	median = array[(size + 1) / 2 - 1];
	return (median);
}

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
	sort_result->action_list_size = 0;
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
	t_sort_result	*sort_result;
	char			*s;
	int				*tmp_array;
	size_t			c;

	if (argc > 1)
	{
		sort_result = init_sort_result();
		s = merge_args(argv + 1, argc - 1);
		sort_result->stack = save_to_stack(s, sort_result);
		tmp_array = (int *)ft_memalloc(sizeof(*tmp_array) *
													sort_result->stack_size);
		c = -1;
		while (++c < sort_result->stack_size)
			tmp_array[sort_result->stack_size - c - 1] = sort_result->stack[c];
		sort_result->median = count_median(tmp_array, sort_result->stack_size);
		free(tmp_array);
		tmp_array = NULL;
		bubble_sort_v2(sort_result);
		print_action_list(sort_result);
		print_stack(sort_result->stack, sort_result->stack_size);
	}
	return (0);
}
