/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_random_v1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 17:10:01 by jkauppi           #+#    #+#             */
/*   Updated: 2020/01/20 19:04:04 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int		check_order(int **array, t_stack_ptr stack_ptr, size_t size)
{
	int		*ptr;
	int		previous;

	ptr = stack_ptr.smallest_int;
	previous = *ptr;
	ptr = ptr == (*array + size - 1) ? *array : ptr++;
	while (ptr != stack_ptr.smallest_int && previous < *ptr)
		ptr = ptr == *array + size - 1 ? *array : ptr++;
	return (ptr == stack_ptr.smallest_int);
}

static int		do_next_action(t_sort_result *sort_result,
													t_move_action valid_actions)
{
	int				*array;
	t_stack_ptr		stack_ptr;
	int				is_sorted;

	array = sort_result->stack;
	stack_ptr = sort_result->stack_ptr;
	is_sorted = check_order(&sort_result->stack, stack_ptr, sort_result->stack_size);
	if (sort_result->action_list_size < 100000)
	{
		if (!is_sorted && (valid_actions & sa))
		{
			execute_action(sort_result, "sa");
			valid_actions = ra | rra;
			is_sorted = do_next_action(sort_result, valid_actions);
		}
		if (!is_sorted && (valid_actions & ra))
		{
			execute_action(sort_result, "ra");
			valid_actions = sa | ra;
			is_sorted = do_next_action(sort_result, valid_actions);
		}
		if (!is_sorted && (valid_actions & rra))
		{
			execute_action(sort_result, "rra");
			valid_actions = sa | rra;
			is_sorted = do_next_action(sort_result, valid_actions);
		}
	}
	return (is_sorted);
}

static int		loop_if_swap(t_sort_result *sort_result)
{
	int				is_sorted;
	t_move_action	valid_actions;

	valid_actions = sa | ra | rra;
	is_sorted = do_next_action(sort_result, valid_actions);
	return (is_sorted);
}

void			random_sort_v1(t_sort_result *sort_result)
{
	int				is_sorted;
	t_stack_ptr		*stack_ptr;

	stack_ptr = &sort_result->stack_ptr;
	is_sorted = 0;
	while (!is_sorted)
		is_sorted = loop_if_swap(sort_result);
	while (*stack_ptr->top != *sort_result->min_ptr)
		execute_action(sort_result, "rra");
	return ;
}
