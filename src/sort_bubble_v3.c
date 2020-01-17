/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_bubble_v3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 11:21:02 by jkauppi           #+#    #+#             */
/*   Updated: 2020/01/17 17:35:56 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int		loop_down_if_swap(t_sort_result *sort_result)
{
	int			is_sorted;
	size_t		current;
	size_t		next;
	size_t		previous;
	int			*stack;

	stack = sort_result->stack;
	current = sort_result->top_ptr;
	next = current ? current - 1 : sort_result->stack_size - 1;
	previous = (current + 1) % sort_result->stack_size;
	is_sorted = 1;
	while (next != sort_result->top_ptr)
	{
		if (*(stack + current) > *(stack + next) &&
				*(stack + current) <= sort_result->median)
		{
			ft_int_swap(stack + current, stack + next);
			add_action(sort_result, "sa");
			is_sorted = 0;
			add_action(sort_result, "ra");
			current = current ? current - 1 : sort_result->stack_size - 1;
			next = current ? current - 1 : sort_result->stack_size - 1;
			previous = (current + 1) % sort_result->stack_size;
		}
		else
		{
			if (!is_sorted && *(stack + previous) <= sort_result->median)
			{
				add_action(sort_result, "rra");
				add_action(sort_result, "rra");
				add_action(sort_result, "rra");
				sort_result->top_ptr = previous;
				break ;
			}
			add_action(sort_result, "ra");
			current = current ? current - 1 : sort_result->stack_size - 1;
			next = current ? current - 1 : sort_result->stack_size - 1;
			previous = (current + 1) % sort_result->stack_size;
		}
	}
	add_action(sort_result, "ra");
	current = current ? current - 1 : sort_result->stack_size - 1;
	next = current ? current - 1 : sort_result->stack_size - 1;
	previous = (current + 1) % sort_result->stack_size;
	return (is_sorted);
}

static int		loop_up_if_swap(t_sort_result *sort_result)
{
	int			is_sorted;
	size_t		current;
	size_t		next;
	size_t		previous;
	int			*stack;

	stack = sort_result->stack;
	current = sort_result->top_ptr;
	next = (current + 1) % sort_result->stack_size;
	previous = current ? current - 1 : sort_result->stack_size - 1;
	is_sorted = 1;
	while (next != sort_result->top_ptr)
	{
		if (*(stack + current) < *(stack + next) &&
				*(stack + current) > sort_result->median)
		{
			ft_int_swap(stack + current, stack + next);
			add_action(sort_result, "sa");
			is_sorted = 0;
			add_action(sort_result, "rra");
			current = (current + 1) % sort_result->stack_size;
			next = (current + 1) % sort_result->stack_size;
			previous = current ? current - 1 : sort_result->stack_size - 1;
		}
		else
		{
			if (!is_sorted && *(stack + next) <= sort_result->median)
			{
				while (*(stack + next) == sort_result->max)
				{
					add_action(sort_result, "ra");
					add_action(sort_result, "ra");
					current = (current + 1) % sort_result->stack_size;
					next = (current + 1) % sort_result->stack_size;
				}
				sort_result->top_ptr = next;
				break ;
			}
			add_action(sort_result, "rra");
			current = (current + 1) % sort_result->stack_size;
			next = (current + 1) % sort_result->stack_size;
			previous = current ? current - 1 : sort_result->stack_size - 1;
		}
	}
	add_action(sort_result, "rra");
	current = (current + 1) % sort_result->stack_size;
	next = (current + 1) % sort_result->stack_size;
	return (is_sorted);
}

static int		loop_if_swap(t_sort_result *sort_result)
{
	int			is_sorted;

	is_sorted = loop_down_if_swap(sort_result);
	if (!is_sorted)
		is_sorted = loop_up_if_swap(sort_result);
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
	{
		is_sorted = loop_if_swap(sort_result);
	}
	while ( sort_result->stack[sort_result->top_ptr] != sort_result->min)
	{
		sort_result->top_ptr++;
		sort_result->top_ptr %= sort_result->stack_size;
		add_action(sort_result, "rra");
	}
	minimize_last_actions(sort_result);
	return ;
}
