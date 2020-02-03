/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_random_v2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 10:42:58 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/03 10:48:28 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	check_order_high(t_list *top, int median, int max)
{
	t_list		*ptr;
	t_list		*previous;

	ptr = top;
	while (*(int *)ptr->content != max)
		ptr = ptr->prev;
	previous = ptr;
	ptr = ptr->prev;
	while (*(int *)previous->content != median &&
							*(int *)previous->content > *(int *)ptr->content)
	{
		previous = ptr;
		ptr = ptr->prev;
	}
	previous = ptr;
	ptr = ptr->prev;
	while (*(int *)ptr->content != max && *(int *)previous->content < median)
	{
		previous = ptr;
		ptr = ptr->prev;
	}
	return (*(int *)previous->content < median);
}

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
		t_move_action *valid_actions, t_move_action rule, t_list **result_array,
		size_t *max_actions)
{
	int						is_sorted;
	static int				is_sorted_high;
	static t_move_action	new_valid_actions[4];
	t_sort_result			*save_result;
	size_t					c;

	is_sorted = check_order(sort_result->stack_a.top);
	if (!is_sorted)
	{
		if (!is_sorted_high)
		{
			is_sorted_high = check_order_high(sort_result->stack_a.top,
										sort_result->median, sort_result->max);
			if (is_sorted_high)
			{
				valid_actions[0] = v11;
				valid_actions[1] = null;
			}
		}
	}
	if (is_sorted)
	{
		c = 0;
		while (*(int *)sort_result->stack_a.top->content != sort_result->min)
		{
			execute_action(sort_result, rra);
			c++;
		}
		save_result = (t_sort_result *)ft_memalloc(sizeof(*save_result));
		init_sort_result(save_result);
		save_result->action_list = ft_int_array_dup(sort_result->action_list,
												sort_result->action_list_size);
		save_result->action_list_size = sort_result->action_list_size;
		ft_lstadd_e(result_array, ft_lstnew(save_result, sizeof(*save_result)));
		if (*max_actions > save_result->action_list_size)
			*max_actions = save_result->action_list_size;
		free(save_result);
		save_result = NULL;
		while (c--)
			execute_action(sort_result, ra);
	}
	else if (sort_result->total_num_of_actions < 80000)
	{
		c = 0;
		while (!is_sorted && sort_result->action_list_size < *max_actions &&
															valid_actions[c])
		{
			if (valid_actions[c] & (v0 | v1 | v2 | v11))
				rule = valid_actions[c];
			else
				execute_action(sort_result, valid_actions[c]);
			create_action_order(sort_result, new_valid_actions,
														valid_actions[c], rule);
			is_sorted = do_next_action(sort_result, new_valid_actions, rule,
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
	}
	return (is_sorted);
}

static int	loop_if_swap(t_sort_result *sort_result, t_list **result_array,
															size_t *max_actions)
{
	int				is_sorted;
	t_move_action	valid_actions[4];
	t_move_action	rule;
	int				*start_ptr;

	start_ptr = count_max_average(sort_result->stack_array, sort_result->stack_a.int_lst_size);
	if ((size_t)(start_ptr - sort_result->stack_array) >= sort_result->stack_a.int_lst_size / 2)
	{
		if (*(int *)sort_result->stack_a.top->content > *(int *)sort_result->stack_a.top->next->content &&
			*(int *)sort_result->stack_a.top->next->content >= sort_result->median)
			execute_action(sort_result, sa);
		while (*(int *)sort_result->stack_a.top->content != *start_ptr)
		{
			execute_action(sort_result, rra);
			if (*(int *)sort_result->stack_a.top->content > *(int *)sort_result->stack_a.top->next->content &&
				*(int *)sort_result->stack_a.top->next->content >= sort_result->median)
				execute_action(sort_result, sa);
		}
	}
	else
	{
		if (*(int *)sort_result->stack_a.top->content > *(int *)sort_result->stack_a.top->next->content &&
			*(int *)sort_result->stack_a.top->next->content >= sort_result->median)
			execute_action(sort_result, sa);
		while (*(int *)sort_result->stack_a.top->content != *start_ptr)
		{
			execute_action(sort_result, ra);
			if (*(int *)sort_result->stack_a.top->content > *(int *)sort_result->stack_a.top->next->content &&
				*(int *)sort_result->stack_a.top->next->content >= sort_result->median)
				execute_action(sort_result, sa);
		}
	}
	rule = v1;
	create_action_order(sort_result, valid_actions, null, rule);
	is_sorted = do_next_action(sort_result, valid_actions, rule, result_array,
															max_actions);
	return (is_sorted);
}

void		random_sort_v2(t_sort_result *sort_result, t_list **result_array,
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
