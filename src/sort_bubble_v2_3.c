/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_bubble_v2_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 09:28:38 by jkauppi           #+#    #+#             */
/*   Updated: 2020/01/31 09:31:18 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void		sort_a(t_sort_result *sort_result)
{
	int				is_sorted;
	t_stack_ptr		*stack_ptr;

	stack_ptr = &sort_result->stack_ptr;
	while (*(int *)stack_ptr->top_a->content != sort_result->max)
	{
		if (*(int *)stack_ptr->top_a->content > *(int *)stack_ptr->next_a->content)
			execute_action(sort_result, sa);
		execute_action(sort_result, ra);
	}
	execute_action(sort_result, ra);
	is_sorted = 0;
	while (!is_sorted)
	{
		is_sorted = 1;
		while (*(int *)stack_ptr->top_a->content != sort_result->max)
		{
			if (*(int *)stack_ptr->top_a->content > *(int *)stack_ptr->next_a->content)
			{
				execute_action(sort_result, sa);
				is_sorted = 0;
			}
			execute_action(sort_result, ra);
		}
		execute_action(sort_result, ra);
	}
	return ;
}

static void		sort_b(t_sort_result *sort_result)
{
	int				is_sorted;
	t_stack_ptr		*stack_ptr;

	stack_ptr = &sort_result->stack_ptr;
	while (*(int *)stack_ptr->top_b->content != sort_result->min_b)
	{
		if (*(int *)stack_ptr->top_b->content < *(int *)stack_ptr->top_b->next->content)
			execute_action(sort_result, sb);
		else
			execute_action(sort_result, rb);
	}
	execute_action(sort_result, rb);
	is_sorted = 0;
	while (!is_sorted)
	{
		is_sorted = 1;

		while (*(int *)stack_ptr->top_b->content != sort_result->min_b)
		{
			if (*(int *)stack_ptr->top_b->content < *(int *)stack_ptr->top_b->next->content)
			{
				execute_action(sort_result, sb);
				is_sorted = 0;
			}
			else
				execute_action(sort_result, rb);
		}
		execute_action(sort_result, rb);
	}
	return ;
}

static void		move_stack_b_to_a(t_sort_result *sort_result)
{
	t_stack_ptr		*stack_ptr;

	stack_ptr = &sort_result->stack_ptr;
	while (sort_result->stack_ptr.top_b)
		execute_action(sort_result, pa);
}

void			bubble_sort_v2_3(t_sort_result *sort_result,
									t_list **result_array, size_t *max_actions)
{
	if (sort_result->min != sort_result->max)
	{
		split_one_stack_to_two_v3(sort_result);
		sort_a(sort_result);
		sort_b(sort_result);
		move_stack_b_to_a(sort_result);
	}
	*max_actions = (*max_actions > sort_result->action_list_size) ?
				sort_result->action_list_size : *max_actions;
	save_result(sort_result, max_actions, result_array);
	return ;
}