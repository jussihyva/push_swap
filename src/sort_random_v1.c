/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_random_v1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 17:10:01 by jkauppi           #+#    #+#             */
/*   Updated: 2020/01/21 17:50:12 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	check_order(int *array, size_t size)
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

static int	do_next_action(t_sort_result *sort_result,
		t_move_action valid_actions, t_list **result_array, size_t *max_actions)
{
	t_stack_ptr		stack_ptr;
	int				is_sorted;
	t_move_action	new_valid_actions;
	t_sort_result	*save_result;
	size_t			c;

	new_valid_actions = 0;
	stack_ptr = sort_result->stack_ptr;
	is_sorted = check_order(sort_result->stack, sort_result->stack_size);
	if (is_sorted)
	{
		c = 0;
		while (*sort_result->stack_ptr.top != sort_result->min)
		{
			execute_action(sort_result, "rra");
			c++;
		}
		save_result = init_sort_result();
		save_result->action_list = ft_str_array_dup(sort_result->action_list,
												sort_result->action_list_size);
		save_result->action_list_size = sort_result->action_list_size;
		ft_lstadd_e(result_array, ft_lstnew(save_result, sizeof(*save_result)));
		if (*max_actions > save_result->action_list_size)
			*max_actions = save_result->action_list_size;
		free(save_result);
		save_result = NULL;
		is_sorted = 0;
		while (c--)
			execute_action(sort_result, "ra");
	}
	if (is_sorted || sort_result->action_list_size < *max_actions)
	{
		if (!is_sorted && (valid_actions & sa))
		{
			execute_action(sort_result, "sa");
			new_valid_actions = ra | rra;
			is_sorted = do_next_action(sort_result, new_valid_actions,
													result_array, max_actions);
			if (!is_sorted)
				execute_action(sort_result, "sa");
		}
		if (!is_sorted && (valid_actions & ra))
		{
			execute_action(sort_result, "ra");
			new_valid_actions = sa | ra;
			is_sorted = do_next_action(sort_result, new_valid_actions,
													result_array, max_actions);
			if (!is_sorted)
				execute_action(sort_result, "rra");
		}
		if (!is_sorted && (valid_actions & rra))
		{
			execute_action(sort_result, "rra");
			new_valid_actions = sa | rra;
			is_sorted = do_next_action(sort_result, new_valid_actions,
													result_array, max_actions);
			if (!is_sorted)
				execute_action(sort_result, "ra");
		}
	}
	else
		is_sorted = 0;
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

void		random_sort_v1(t_sort_result *sort_result, t_list **result_array)
{
	int				is_sorted;
	t_stack_ptr		*stack_ptr;
	size_t			max_actions;

	stack_ptr = &sort_result->stack_ptr;
	max_actions = 10;
	while (!(*result_array))
	{
		is_sorted = loop_if_swap(sort_result, result_array, &max_actions);
		max_actions += 5;
	}
	while (*stack_ptr->top != sort_result->min)
		execute_action(sort_result, "rra");
	return ;
}