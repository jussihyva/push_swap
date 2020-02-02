/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_insertion_v1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 16:39:09 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/02 13:21:31 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int		loop_down_if_swap(t_sort_result *sort_result,
													t_stack_ptr *stack_ptr)
{
	int				is_sorted;
	size_t			loop_cnt;

	is_sorted = 1;
	loop_cnt = 0;
	while (*(int *)stack_ptr->top_a->content != sort_result->max)
	{
		loop_cnt++;
		if (*(int *)stack_ptr->top_a->content > *(int *)stack_ptr->top_a->next->content)
		{
			execute_action(sort_result, sa);
			execute_action(sort_result, ra);
			break ;
		}
		else
		{
			if (!is_sorted && *stack_ptr->bottom <= sort_result->median)
				break ;
			execute_action(sort_result, ra);
		}
	}
	if (loop_cnt != sort_result->stack_a_size - 1)
		is_sorted = 0;
	return (is_sorted);
}

static int		loop_up_if_swap(t_sort_result *sort_result,
													t_stack_ptr *stack_ptr)
{
	int				is_sorted;

	is_sorted = 0;
	while (*(int *)stack_ptr->top_a->content != sort_result->max)
	{
		if (*(int *)stack_ptr->top_a->next->content < *(int *)stack_ptr->top_a->content)
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
	t_stack_ptr		*stack_ptr;

	stack_ptr = &sort_result->stack_ptr;
	is_sorted = loop_down_if_swap(sort_result, stack_ptr);
	if (!is_sorted)
		is_sorted = loop_up_if_swap(sort_result, stack_ptr);
	return (is_sorted);
}

void			insertion_sort_v1(t_sort_result *sort_result,
									t_list **result_array, size_t *max_actions)
{
	int				is_sorted;
	t_stack_ptr		*stack_ptr;

	stack_ptr = &sort_result->stack_ptr;
	is_sorted = 0;
	while (!is_sorted && sort_result->total_num_of_actions < 80000)
		is_sorted = loop_if_swap(sort_result);
	while (*(int *)stack_ptr->top_a->content != sort_result->min)
		execute_action(sort_result, rra);
	ft_lstadd_e(result_array, ft_lstnew(sort_result, sizeof(*sort_result)));
	*max_actions = (*max_actions > sort_result->action_list_size) ?
				sort_result->action_list_size : *max_actions;
	return ;
}
