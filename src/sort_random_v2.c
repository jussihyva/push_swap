/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_random_v2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 10:42:58 by jkauppi           #+#    #+#             */
/*   Updated: 2020/01/24 11:58:31 by jkauppi          ###   ########.fr       */
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
		t_move_action *valid_actions, t_list **result_array, size_t *max_actions)
{
	int						is_sorted;
	static t_move_action	new_valid_actions[4];
	t_sort_result			*save_result;
	size_t					c;

	is_sorted = check_order(sort_result->stack, sort_result->stack_size);
	if (is_sorted)
	{
		c = 0;
		while (*sort_result->stack_ptr.top != sort_result->min)
		{
			execute_action(sort_result, rra);
			c++;
		}
		save_result = (t_sort_result *)ft_memalloc(sizeof(*save_result));
		init_sort_result(save_result);
		save_result->action_list = ft_int_array_dup(sort_result->action_list,
												sort_result->action_list_size);
		save_result->action_list_size = sort_result->action_list_size;
		ft_lstadd_e(result_array, ft_lstnew(&save_result, sizeof(save_result)));
		if (*max_actions > save_result->action_list_size)
			*max_actions = save_result->action_list_size;
		free(save_result);
		save_result = NULL;
		while (c--)
			execute_action(sort_result, ra);
	}
	c = 0;
	while (!is_sorted && sort_result->action_list_size < *max_actions &&
															valid_actions[c])
	{
		execute_action(sort_result, valid_actions[c]);
		create_action_order(sort_result, new_valid_actions, valid_actions[c]);
		is_sorted = do_next_action(sort_result, new_valid_actions,
													result_array, max_actions);
		if (!is_sorted)
		{
			if (valid_actions[c] == sa)
				execute_action(sort_result, sa);
			else if (valid_actions[c] == ra)
				execute_action(sort_result, rra);
			else if (valid_actions[c] == rra)
				execute_action(sort_result, ra);
		}
		c++;
	}
	return (is_sorted);
}

static int	loop_if_swap(t_sort_result *sort_result, t_list **result_array,
															size_t *max_actions)
{
	int				is_sorted;
	t_move_action	valid_actions[4];

	create_action_order(sort_result, valid_actions, (t_move_action)null);
	is_sorted = do_next_action(sort_result, valid_actions, result_array,
																max_actions);
	return (is_sorted);
}

void		random_sort_v2(t_sort_result *sort_result, t_list **result_array,
															size_t *max_actions)
{
	int				is_sorted;
	t_stack_ptr		*stack_ptr;
	int				result_required;

	stack_ptr = &sort_result->stack_ptr;
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
