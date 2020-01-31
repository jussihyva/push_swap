/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_two_stacks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 12:13:23 by jkauppi           #+#    #+#             */
/*   Updated: 2020/01/31 09:35:38 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void		split_one_stack_to_two_v1(t_sort_result *sort_result)
{
	t_stack_ptr		*stack_ptr;
	t_list			*start_ptr;

	stack_ptr = &sort_result->stack_ptr;
	start_ptr = NULL;
	while (stack_ptr->top_a != start_ptr)
	{
		if (*(int *)stack_ptr->top_a->content <= sort_result->median)
			execute_action(sort_result, pb);
		else
		{
			if (!start_ptr)
				start_ptr = stack_ptr->top_a;
			execute_action(sort_result, ra);
		}
	}
	return ;
}

void		split_one_stack_to_two_v2(t_sort_result *sort_result)
{
	t_stack_ptr		*stack_ptr;
	t_list			*start_ptr;

	stack_ptr = &sort_result->stack_ptr;
	start_ptr = NULL;
	while (stack_ptr->top_a != start_ptr)
	{
		if (*(int *)stack_ptr->top_a->content <= sort_result->median)
		{
			execute_action(sort_result, pb);
			if (*(int *)stack_ptr->top_b->content <
										*(int *)stack_ptr->top_b->next->content)
				execute_action(sort_result, sb);
		}
		else
		{
			if (!start_ptr)
				start_ptr = stack_ptr->top_a;
			execute_action(sort_result, ra);
		}
	}
	return ;
}

void		split_one_stack_to_two_v3(t_sort_result *sort_result)
{
	t_stack_ptr		*stack_ptr;
	t_list			*start_ptr;

	stack_ptr = &sort_result->stack_ptr;
	start_ptr = NULL;
	while (stack_ptr->top_a != start_ptr)
	{
		if (*(int *)stack_ptr->top_a->content <= sort_result->median)
		{
			execute_action(sort_result, pb);
			if (*(int *)stack_ptr->top_b->content < sort_result->median / 2)
				execute_action(sort_result, rb);
			if (*(int *)stack_ptr->top_b->content <
										*(int *)stack_ptr->top_b->next->content)
				execute_action(sort_result, sb);
		}
		else
		{
			if (!start_ptr)
				start_ptr = stack_ptr->top_a;
			execute_action(sort_result, ra);
		}
	}
	return ;
}
