/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bubble_sort_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 13:21:32 by jkauppi           #+#    #+#             */
/*   Updated: 2020/01/17 10:17:46 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void			swap_int(int *i1, int *i2)
{
	int		tmp;

	tmp = *i1;
	*i1 = *i2;
	*i2 = tmp;
}

void			minimize_last_actions(t_sort_result *sort_result)
{
	size_t		c;

	if (sort_result->seq_action_counter > (size_t)sort_result->stack_size / 2)
	{
		c = 0;
		sort_result->action_list_size -= sort_result->seq_action_counter;
		while (c++ < (size_t)sort_result->stack_size -
												sort_result->seq_action_counter)
		{
			sort_result->action_list[sort_result->action_list_size] =
													ft_strdup("rra");
			sort_result->action_list_size++;
		}
	}
}

void			add_action(t_sort_result *sort_result, char *action_string)
{
	if (sort_result->seq_action_counter)
		if (ft_strequ(sort_result->last_action, action_string))
			sort_result->seq_action_counter++;
		else
		{
			minimize_last_actions(sort_result);
			sort_result->seq_action_counter = 1;
			sort_result->last_action = action_string;
		}
	else
	{
		sort_result->seq_action_counter = 1;
		sort_result->last_action = action_string;
	}
	sort_result->action_list[sort_result->action_list_size] =
													ft_strdup(action_string);
	sort_result->action_list_size++;
	if (sort_result->seq_action_counter == (size_t)sort_result->stack_size)
	{
		sort_result->action_list_size -= sort_result->stack_size;
		sort_result->seq_action_counter = 0;
	}
	return ;
}

static int		loop_if_swap(t_sort_result *sort_result, size_t top_i)
{
	int			is_sorted;
	size_t		current;
	size_t		current_1;
	int			*stack;

	stack = sort_result->stack;
	current = top_i;
	current_1 = current ? current - 1 : sort_result->stack_size - 1;
	is_sorted = 1;
	while (current_1 != top_i)
	{
		if (*(stack + current) > *(stack + current_1))
		{
			swap_int(stack + current, stack + current_1);
			add_action(sort_result, "sa");
			is_sorted = 0;
		}
		add_action(sort_result, "ra");
		current = current ? current - 1 : sort_result->stack_size - 1;
		current_1 = current ? current - 1 : sort_result->stack_size - 1;
	}
	add_action(sort_result, "ra");
	return (is_sorted);
}

void			bubble_sort_v1(t_sort_result *sort_result)
{
	int			is_sorted;
	size_t		top_i;

	top_i = sort_result->stack_size - 1;
	sort_result->action_list_size = 0;
	is_sorted = 0;
	while (!is_sorted)
	{
		is_sorted = loop_if_swap(sort_result, top_i);
	}
	return ;
}
