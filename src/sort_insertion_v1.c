/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_insertion_v1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 16:39:09 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/13 19:45:23 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int		loop_down_if_swap(t_sort_result *sort_result,
													t_stack *stack_a)
{
	int				is_sorted;
	size_t			loop_cnt;

	is_sorted = 1;
	loop_cnt = 0;
	while (*(int *)stack_a->top->content != sort_result->stack_a.max)
	{
		loop_cnt++;
		if (*(int *)stack_a->top->content > *(int *)stack_a->top->next->content)
		{
			execute_action(sort_result, sa);
			execute_action(sort_result, ra);
			break ;
		}
		else
		{
			if (!is_sorted && *(int *)stack_a->top->prev->content <=
													sort_result->stack_a.median)
				break ;
			execute_action(sort_result, ra);
		}
	}
	if (loop_cnt != sort_result->stack_a.int_lst_size - 1)
		is_sorted = 0;
	return (is_sorted);
}

static int		loop_up_if_swap(t_sort_result *sort_result,
													t_stack *stack_a)
{
	int				is_sorted;

	is_sorted = 0;
	while (*(int *)stack_a->top->content != sort_result->stack_a.max)
	{
		if (*(int *)stack_a->top->next->content < *(int *)stack_a->top->content)
		{
			execute_action(sort_result, sa);
			execute_action(sort_result, rra);
		}
		else
			execute_action(sort_result, rra);
	}
	execute_action(sort_result, ra);
	return (is_sorted);
}

static int		loop_if_swap(t_sort_result *sort_result)
{
	int				is_sorted;
	t_stack			*stack_a;

	stack_a = &sort_result->stack_a;
	is_sorted = loop_down_if_swap(sort_result, stack_a);
	if (!is_sorted)
		is_sorted = loop_up_if_swap(sort_result, stack_a);
	return (is_sorted);
}

void			insertion_sort_v1(t_sort_result *sort_result,
									t_list **result_array, size_t *max_actions)
{
	int				is_sorted;
	t_stack			*stack_a;

	stack_a = &sort_result->stack_a;
	is_sorted = 0;
	while (!is_sorted && sort_result->total_num_of_actions < MAX_ACTIONS)
		is_sorted = loop_if_swap(sort_result);
	while (*(int *)stack_a->top->content != sort_result->stack_a.min)
		execute_action(sort_result, rra);
	save_result(sort_result, max_actions, result_array);
	return ;
}
