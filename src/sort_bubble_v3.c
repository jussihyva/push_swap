/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_bubble_v3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 11:21:02 by jkauppi           #+#    #+#             */
/*   Updated: 2020/01/19 10:49:42 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void		execute_action(t_sort_result *sort_result, int *stack,
								char *action_string)
{
	t_stack_index *stack_index;

	stack_index = &sort_result->stack_index;
	add_action(sort_result, action_string);
	if (ft_strequ(action_string, "sa"))
		ft_int_swap(stack + stack_index->top, stack + stack_index->next);
	else if (ft_strequ(action_string, "ra"))
	{
		stack_index->top = stack_index->top ? stack_index->top - 1 :
													sort_result->stack_size - 1;
		stack_index->next = stack_index->top ? stack_index->top - 1 :
													sort_result->stack_size - 1;
		stack_index->bottom = (stack_index->top + 1) % sort_result->stack_size;
	}
	else if (ft_strequ(action_string, "rra"))
	{
		stack_index->top = (stack_index->top + 1) % sort_result->stack_size;
		stack_index->next = stack_index->top ? stack_index->top - 1 :
													sort_result->stack_size - 1;
		stack_index->bottom = (stack_index->top + 1) % sort_result->stack_size;
	}
}

static int		loop_down_if_swap(t_sort_result *sort_result,
													t_stack_index *stack_index)
{
	int				is_sorted;
	int				*stack;
	size_t			loop_cnt;

	stack = sort_result->stack;
	is_sorted = 1;
	loop_cnt = 0;
	while (*(stack + stack_index->top) != sort_result->max)
	{
		loop_cnt++;
		if (*(stack + stack_index->top) > *(stack + stack_index->next))
		{
			execute_action(sort_result, stack, "sa");
			is_sorted = 0;
			execute_action(sort_result, stack, "ra");
		}
		else
		{
			if (!is_sorted && *(stack + stack_index->bottom) <=
															sort_result->median)
				break ;
			execute_action(sort_result, stack, "ra");
		}
	}
	if (loop_cnt != sort_result->stack_size - 1)
		is_sorted = 0;
	return (is_sorted);
}

static int		loop_up_if_swap(t_sort_result *sort_result,
													t_stack_index *stack_index)
{
	int				is_sorted;
	int				*stack;

	stack = sort_result->stack;
	is_sorted = 0;
	while (*(stack + stack_index->top) != sort_result->max)
	{
		if (*(stack + stack_index->next) < *(stack + stack_index->top))
		{
			execute_action(sort_result, stack, "sa");
			execute_action(sort_result, stack, "rra");
		}
		else
			execute_action(sort_result, stack, "rra");
	}
	execute_action(sort_result, stack, "ra");
	return (is_sorted);
}

static int		loop_if_swap(t_sort_result *sort_result)
{
	int				is_sorted;
	t_stack_index 	*stack_index;

	stack_index = &sort_result->stack_index;
	is_sorted = loop_down_if_swap(sort_result, stack_index);
	if (!is_sorted)
	{
		stack_index->top = sort_result->stack_index.top;
		stack_index->next = stack_index->top ? stack_index->top - 1 :
													sort_result->stack_size - 1;
		stack_index->bottom = (stack_index->top + 1) % sort_result->stack_size;
		is_sorted = loop_up_if_swap(sort_result, stack_index);
	}
	return (is_sorted);
}

void			bubble_sort_v3(t_sort_result *sort_result)
{
	int				is_sorted;
	int				*stack;

	stack = sort_result->stack;
	if (*(stack + sort_result->stack_index.top) > sort_result->median &&
				*(stack + sort_result->stack_index.next) > sort_result->median)
	{
		if (*(stack + sort_result->stack_index.top) >
									*(stack + sort_result->stack_index.next))
			execute_action(sort_result, stack, "sa");
		execute_action(sort_result, stack, "ra");
		execute_action(sort_result, stack, "ra");
	}
	is_sorted = 0;
	while (!is_sorted)
		is_sorted = loop_if_swap(sort_result);
	while (sort_result->stack[sort_result->stack_index.top] != sort_result->min)
	{
		sort_result->stack_index.top =
					++sort_result->stack_index.top % sort_result->stack_size;
		add_action(sort_result, "rra");
	}
	return ;
}
