/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_random_v3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:12:25 by jkauppi           #+#    #+#             */
/*   Updated: 2020/01/28 12:04:29 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	check_order_high(t_list *top, int median, int max)
{
	t_list		*ptr;

	ptr = top;
	while (*(int *)ptr->content != median)
		ptr = ptr->next;
	ptr = ptr->next;
	while (*(int *)ptr->prev->content != max &&
							*(int *)ptr->prev->content < *(int *)ptr->content)
		ptr = ptr->next;
	ptr = ptr->next;
	while (*(int *)ptr->content != median &&
											*(int *)ptr->prev->content < median)
		ptr = ptr->next;
	return (*(int *)ptr->prev->content < median);
}

static int	check_order(t_sort_result *sort_result, t_move_action **valid_actions)
{
	t_list			*ptr;
	int				is_sorted;
	static int		is_sorted_high;
	t_list			*top;
	t_stack_ptr		*stack_ptr;

	stack_ptr = &sort_result->stack_ptr;
	top = sort_result->stack_ptr.top_a;
	ptr = top->next;
	while (ptr != top && *(int *)ptr->prev->content < *(int *)ptr->content)
		ptr = ptr->next;
	if (ptr == top)
		return (1);
	ptr = ptr->next;
	while (ptr->prev != top &&
							*(int *)ptr->prev->content < *(int *)ptr->content)
		ptr = ptr->next;
	is_sorted = ptr->prev == top;
	if (!is_sorted)
	{
		if (!is_sorted_high)
		{
			is_sorted_high = check_order_high(top, sort_result->median,
															sort_result->max);
			if (is_sorted_high)
			{
				*(*valid_actions + 0) = v11;
				*(*valid_actions + 1) = null;
			}
		}
	}
	if (is_sorted)
	{
		while (stack_ptr->top_b)
		{
			is_sorted = 0;
			execute_action(sort_result, pa);
		}
	}
	return (is_sorted);
}

static int	do_next_action(t_sort_result *sort_result,
		t_move_action *valid_actions, t_move_action rule, t_list **result_array,
		size_t *max_actions)
{
	int						is_sorted;
	static t_move_action	new_valid_actions[4];
	size_t					c;
	t_stack_ptr		*stack_ptr;

	stack_ptr = &sort_result->stack_ptr;
	is_sorted = check_order(sort_result, &valid_actions);
	if (is_sorted)
		save_result(sort_result, max_actions, result_array);
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
	t_stack_ptr		*stack_ptr;

	stack_ptr = &sort_result->stack_ptr;
	start_ptr = count_max_average(sort_result->stack, sort_result->stack_size);
	if ((size_t)(start_ptr - sort_result->stack) >= sort_result->stack_size / 2)
	{
		while (*(int *)sort_result->stack_ptr.top_a->content < sort_result->median)
			execute_action(sort_result, pb);
		if (*sort_result->stack_ptr.top > *sort_result->stack_ptr.next &&
			*sort_result->stack_ptr.next >= sort_result->median)
			execute_action(sort_result, sa);
		while (sort_result->stack_ptr.top != start_ptr)
		{
			execute_action(sort_result, rra);
			while (*(int *)sort_result->stack_ptr.top_a->content < sort_result->median)
				execute_action(sort_result, pb);
			if (*sort_result->stack_ptr.top > *sort_result->stack_ptr.next &&
				*sort_result->stack_ptr.next >= sort_result->median)
				execute_action(sort_result, sa);
			while (*(int *)sort_result->stack_ptr.top_a->content < sort_result->median)
				execute_action(sort_result, pb);
		}
	}
	else
	{
		while (*(int *)sort_result->stack_ptr.top_a->content < sort_result->median)
			execute_action(sort_result, pb);
		if (*sort_result->stack_ptr.top > *sort_result->stack_ptr.next &&
			*sort_result->stack_ptr.next >= sort_result->median)
			execute_action(sort_result, sa);
		while (sort_result->stack_ptr.top != start_ptr)
		{
			execute_action(sort_result, ra);
			while (*(int *)sort_result->stack_ptr.top_a->content < sort_result->median)
				execute_action(sort_result, pb);
			if (*sort_result->stack_ptr.top > *sort_result->stack_ptr.next &&
				*sort_result->stack_ptr.next >= sort_result->median)
				execute_action(sort_result, sa);
			while (*(int *)sort_result->stack_ptr.top_a->content < sort_result->median)
				execute_action(sort_result, pb);
		}
	}
	rule = v31;
	create_action_order(sort_result, valid_actions, null, rule);
	is_sorted = do_next_action(sort_result, valid_actions, rule, result_array,
															max_actions);
	return (is_sorted);
}

void		random_sort_v3(t_sort_result *sort_result, t_list **result_array,
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
