/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_two_stacks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 12:13:23 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/12 17:59:43 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void		move_all_to_stack_b_v1(t_sort_result *sort_result)
{
	while (sort_result->stack_a.int_lst_size)
		execute_action(sort_result, pb);
	return ;
}

void		move_all_to_stack_b_v4_1(t_sort_result *sort_result)
{
	while (sort_result->stack_a.int_lst_size > 2)
		execute_action(sort_result, pb);
	return ;
}

void		move_all_to_stack_b_v2(t_sort_result *sort_result)
{
	t_stack			*stack_a;
	t_stack			*stack_b;

	stack_b = &sort_result->stack_b;
	stack_a = &sort_result->stack_a;
	while (sort_result->stack_a.int_lst_size)
	{
		execute_action(sort_result, pb);
		if (stack_a->top &&
			*(int *)stack_b->top->content <= sort_result->stack_a.median &&
			*(int *)stack_b->top->next->content > sort_result->stack_a.median &&
			*(int *)stack_a->top->content > sort_result->stack_a.median)
			execute_action(sort_result, rr);
		else if (*(int *)stack_b->top->content <= sort_result->stack_a.median &&
			*(int *)stack_b->top->next->content > sort_result->stack_a.median)
			execute_action(sort_result, rb);
	}
	return ;
}

void		move_all_to_stack_b_v3(t_sort_result *sort_result)
{
	t_stack			*stack_a;
	double			factor;
	t_stack			*stack_b;

	stack_b = &sort_result->stack_b;
	factor = 1.5;
	stack_a = &sort_result->stack_a;
	while (sort_result->stack_a.int_lst_size)
	{
		execute_action(sort_result, pb);
		if (stack_a->top &&
			*(int *)stack_b->top->content <= stack_a->median &&
			*(int *)stack_b->top->next->content > stack_a->median &&
			*(int *)stack_a->top->content > stack_a->median / 2 &&
			*(int *)stack_a->top->content < stack_a->median * factor)
			execute_action(sort_result, rr);
		else if (*(int *)stack_b->top->content <= stack_a->median &&
			*(int *)stack_b->top->next->content > stack_a->median)
			execute_action(sort_result, rb);
	}
	return ;
}

void		split_one_stack_to_two_v1(t_sort_result *sort_result)
{
	t_stack			*stack_a;
	t_list			*start_ptr;

	stack_a = &sort_result->stack_a;
	start_ptr = NULL;
	while (stack_a->top != start_ptr)
	{
		if (*(int *)stack_a->top->content <= sort_result->stack_a.median)
			execute_action(sort_result, pb);
		else
		{
			if (!start_ptr)
				start_ptr = stack_a->top;
			execute_action(sort_result, ra);
		}
	}
	return ;
}
