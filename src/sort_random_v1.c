/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_random_v1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 17:10:01 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/13 11:01:41 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	check_order(t_list *top)
{
	t_list		*ptr;
	t_list		*previous;

	ptr = top;
	previous = ptr;
	ptr = ptr->prev;
	while (ptr != top && *(int *)previous->content > *(int *)ptr->content)
	{
		previous = ptr;
		ptr = ptr->prev;
	}
	if (ptr == top)
		return (1);
	previous = ptr;
	ptr = ptr->prev;
	while (previous != top && *(int *)previous->content > *(int *)ptr->content)
	{
		previous = ptr;
		ptr = ptr->prev;
	}
	return (previous == top);
}

static int	do_next_action(t_sort_result *sort_result,
		t_move_action valid_actions, t_list **result_array, size_t *max_actions)
{
	int				is_sorted;
	t_move_action	new_valid_actions;

	new_valid_actions = 0;
	is_sorted = check_order(sort_result->stack_a.top);
	if (is_sorted)
		save_result(sort_result, max_actions, result_array);
	is_sorted = 0;
	if (sort_result->total_num_of_actions < 20000 &&
		(is_sorted || sort_result->action_list_size < *max_actions))
	{
		if (!is_sorted && (valid_actions & sa))
		{
			execute_action(sort_result, sa);
			new_valid_actions = ra | rra;
			is_sorted = do_next_action(sort_result, new_valid_actions,
													result_array, max_actions);
			if (!is_sorted)
				execute_action(sort_result, sa);
		}
		if (!is_sorted && (valid_actions & ra))
		{
			execute_action(sort_result, ra);
			new_valid_actions = sa | ra;
			is_sorted = do_next_action(sort_result, new_valid_actions,
													result_array, max_actions);
			if (!is_sorted)
				execute_action(sort_result, rra);
		}
		if (!is_sorted && (valid_actions & rra))
		{
			execute_action(sort_result, rra);
			new_valid_actions = sa | rra;
			is_sorted = do_next_action(sort_result, new_valid_actions,
													result_array, max_actions);
			if (!is_sorted)
				execute_action(sort_result, ra);
		}
	}
	return (is_sorted);
}

static int	loop_if_swap(t_sort_result *sort_result, t_list **result_array,
															size_t *max_actions)
{
	int				is_sorted;
	t_move_action	valid_actions;

	valid_actions = sa | ra | rra;
	is_sorted = do_next_action(sort_result, valid_actions, result_array,
																max_actions);
	return (is_sorted);
}

void		random_sort_v1(t_sort_result *sort_result, t_list **result_array,
															size_t *max_actions)
{
	int				is_sorted;
	int				result_required;

	result_required = (*max_actions == (size_t)-1) ? 1 : 0;
	if (result_required)
		*max_actions = 10;
	while (!(*result_array) || !result_required)
	{
		is_sorted = loop_if_swap(sort_result, result_array, max_actions);
		if (result_required)
			*max_actions += 5;
		else
			break ;
	}
	return ;
}
