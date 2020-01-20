/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_insertion_v1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 16:39:09 by jkauppi           #+#    #+#             */
/*   Updated: 2020/01/20 18:48:21 by jkauppi          ###   ########.fr       */
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
	while (*(stack_ptr->top) != *sort_result->max_ptr)
	{
		loop_cnt++;
		if (*stack_ptr->top > *stack_ptr->next)
		{
			execute_action(sort_result, "sa");
			execute_action(sort_result, "ra");
			break ;
		}
		else
		{
			if (!is_sorted && *stack_ptr->bottom <= sort_result->median)
				break ;
			execute_action(sort_result, "ra");
		}
	}
	if (loop_cnt != sort_result->stack_size - 1)
		is_sorted = 0;
	return (is_sorted);
}

static int		loop_up_if_swap(t_sort_result *sort_result,
													t_stack_ptr *stack_ptr)
{
	int				is_sorted;

	is_sorted = 0;
	while (*stack_ptr->top != *sort_result->max_ptr)
	{
		if (*stack_ptr->next < *stack_ptr->top)
		{
			execute_action(sort_result, "sa");
			execute_action(sort_result, "rra");
		}
		else
			execute_action(sort_result, "rra");
	}
	execute_action(sort_result, "ra");
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

void			insertion_sort_v1(t_sort_result *sort_result)
{
	int				is_sorted;
	t_stack_ptr		*stack_ptr;

	stack_ptr = &sort_result->stack_ptr;
	is_sorted = 0;
	while (!is_sorted)
		is_sorted = loop_if_swap(sort_result);
	while (*stack_ptr->top != *sort_result->min_ptr)
		execute_action(sort_result, "rra");
	return ;
}
