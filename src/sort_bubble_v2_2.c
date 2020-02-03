/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_bubble_v2_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:17:53 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/03 08:03:47 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void		sort_a(t_sort_result *sort_result)
{
	int				is_sorted;
	t_stack			*stack_a;

	stack_a = &sort_result->stack_a;
	while (*(int *)stack_a->top->content != sort_result->max)
	{
		if (*(int *)stack_a->top->content > *(int *)stack_a->top->next->content)
			execute_action(sort_result, sa);
		execute_action(sort_result, ra);
	}
	execute_action(sort_result, ra);
	is_sorted = 0;
	while (!is_sorted)
	{
		is_sorted = 1;
		while (*(int *)stack_a->top->content != sort_result->max)
		{
			if (*(int *)stack_a->top->content > *(int *)stack_a->top->next->content)
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

void			bubble_sort_v2_2(t_sort_result *sort_result,
									t_list **result_array, size_t *max_actions)
{
	if (sort_result->min != sort_result->max)
	{
		split_one_stack_to_two_v2(sort_result);
		sort_a(sort_result);
		sort_b(sort_result);
		move_stack_b_to_a(sort_result);
	}
//	*max_actions = (*max_actions > sort_result->action_list_size) ?
//				sort_result->action_list_size : *max_actions;
	save_result(sort_result, max_actions, result_array);
	return ;
}
