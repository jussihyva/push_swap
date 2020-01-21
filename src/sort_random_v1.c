/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_random_v1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 17:10:01 by jkauppi           #+#    #+#             */
/*   Updated: 2020/01/21 10:26:54 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int		check_order(int *array, size_t size)
{
	int		*ptr;
	int		*previous;

	ptr = array;
	previous = ptr;
	ptr = ptr == (array + size - 1) ? array : ++ptr;
	while (ptr != array && *previous > *ptr)
	{
		previous = ptr;
		ptr = ptr == array + size - 1 ? array : ++ptr;
	}
	if (ptr == array)
		return (1);
	previous = ptr;
	ptr = ptr == (array + size - 1) ? array : ++ptr;
	while (previous != array && *previous > *ptr)
	{
		previous = ptr;
		ptr = ptr == array + size - 1 ? array : ++ptr;
	}
	return (previous == array);
}

static int		do_next_action(t_sort_result *sort_result,
													t_move_action valid_actions)
{
	t_stack_ptr		stack_ptr;
	int				is_sorted;
	t_move_action	new_valid_actions;

	new_valid_actions = 0;
	stack_ptr = sort_result->stack_ptr;
	is_sorted = check_order(sort_result->stack, sort_result->stack_size);
	if (is_sorted && sort_result->action_list_size > 90)
		is_sorted = 0;
	if (is_sorted || sort_result->action_list_size < 100)
	{
		if (!is_sorted && (valid_actions & sa))
		{
			execute_action(sort_result, "sa");
			new_valid_actions = ra | rra;
			is_sorted = do_next_action(sort_result, new_valid_actions);
			if (!is_sorted)
				execute_action(sort_result, "sa");
		}
		if (!is_sorted && (valid_actions & ra))
		{
			execute_action(sort_result, "ra");
			new_valid_actions = sa | ra;
			is_sorted = do_next_action(sort_result, new_valid_actions);
			if (!is_sorted)
				execute_action(sort_result, "rra");
		}
		if (!is_sorted && (valid_actions & rra))
		{
			execute_action(sort_result, "rra");
			new_valid_actions = sa | rra;
			is_sorted = do_next_action(sort_result, new_valid_actions);
			if (!is_sorted)
				execute_action(sort_result, "ra");
		}
	}
	else
		is_sorted = 0;
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
	is_sorted = loop_if_swap(sort_result);
	while (*stack_ptr->top != sort_result->min)
		execute_action(sort_result, "rra");
	return ;
}
