/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_bubble_v3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 11:21:02 by jkauppi           #+#    #+#             */
/*   Updated: 2020/01/18 11:38:52 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void		execute_action(t_sort_result *sort_result, int *stack,
								t_stack_index *stack_index, char *action_string)
{
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
													t_stack_index stack_index)
{
	int				is_sorted;
	int				*stack;

	stack = sort_result->stack;
	is_sorted = 1;
	while (*(stack + stack_index.top) != sort_result->max)
	{
		if (*(stack + stack_index.top) > *(stack + stack_index.next))
		{
			execute_action(sort_result, stack, &stack_index, "sa");
			is_sorted = 0;
			execute_action(sort_result, stack, &stack_index, "ra");
		}
		else
		{
			if (!is_sorted && *(stack + stack_index.bottom) <=
															sort_result->median)
				break ;
			execute_action(sort_result, stack, &stack_index, "ra");
		}
	}
	sort_result->top_ptr = stack_index.top;
	return (is_sorted);
}

static int		loop_up_if_swap(t_sort_result *sort_result,
													t_stack_index stack_index)
{
	int				is_sorted;
	int				*stack;

	stack = sort_result->stack;
	is_sorted = 0;
	while (*(stack + stack_index.top) != sort_result->max)
	{
		if (*(stack + stack_index.next) < *(stack + stack_index.top))
		{
			execute_action(sort_result, stack, &stack_index, "sa");
			execute_action(sort_result, stack, &stack_index, "rra");
		}
		else
		{
			if (!is_sorted && *(stack + stack_index.next) <=
															sort_result->median)
				break ;
			execute_action(sort_result, stack, &stack_index, "rra");
		}
	}
	sort_result->top_ptr = stack_index.top;
	return (is_sorted);
}

static int		loop_if_swap(t_sort_result *sort_result)
{
	int				is_sorted;
	t_stack_index	stack_index;

	stack_index.top = sort_result->top_ptr;
	stack_index.next = stack_index.top ? stack_index.top - 1 :
													sort_result->stack_size - 1;
	stack_index.bottom = (stack_index.top + 1) % sort_result->stack_size;
	is_sorted = loop_down_if_swap(sort_result, stack_index);
	if (!is_sorted)
	{
		stack_index.top = sort_result->top_ptr;
		stack_index.next = stack_index.top ? stack_index.top - 1 :
													sort_result->stack_size - 1;
		stack_index.bottom = (stack_index.top + 1) % sort_result->stack_size;
		is_sorted = loop_up_if_swap(sort_result, stack_index);
	}
	return (is_sorted);
}

void			bubble_sort_v3(t_sort_result *sort_result)
{
	int			is_sorted;

	sort_result->top_ptr = sort_result->stack_size - 1;
	if (sort_result->stack[sort_result->top_ptr] > sort_result->median)
	{
		sort_result->action_list_size = 0;
		add_action(sort_result, "ra");
		sort_result->top_ptr--;
	}
	else if (sort_result->stack[0] <= sort_result->median)
	{
		sort_result->action_list_size = 0;
		add_action(sort_result, "rra");
		sort_result->top_ptr = 0;
	}
	is_sorted = 0;
	while (!is_sorted)
		is_sorted = loop_if_swap(sort_result);
	while (sort_result->stack[sort_result->top_ptr] != sort_result->min)
	{
		sort_result->top_ptr = ++sort_result->top_ptr % sort_result->stack_size;
		add_action(sort_result, "rra");
	}
	minimize_last_actions(sort_result);
	return ;
}
