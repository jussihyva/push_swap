/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_common_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 10:54:38 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/02 17:42:49 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void			step_prt_up(t_sort_result *sort_result)
{
	int				*stack;
	t_stack_ptr		*stack_ptr;

	stack = sort_result->stack;
	stack_ptr = &sort_result->stack_ptr;
	if (sort_result->stack_a_size)
		stack_ptr->top_a = stack_ptr->top_a->prev;
	return ;
}

void			step_prt_down(t_sort_result *sort_result)
{
	int				*stack;
	t_stack_ptr		*stack_ptr;

	stack = sort_result->stack;
	stack_ptr = &sort_result->stack_ptr;
	if (sort_result->stack_a_size)
		stack_ptr->top_a = stack_ptr->top_a->next;
	return ;
}

void			step_prt_down_b(t_sort_result *sort_result)
{
	int				*stack;
	t_stack_ptr		*stack_ptr;

	stack = sort_result->stack;
	stack_ptr = &sort_result->stack_ptr;
	stack_ptr->top_b = stack_ptr->top_b->next;
	return ;
}

static void		count_num_of_consecutive(t_sort_result *sort_result)
{
	size_t			c;
	t_move_action	last_action;

	c = 1;
	if (sort_result->action_list_size)
	{
		last_action = sort_result->action_list[sort_result->action_list_size - 1];
		while (last_action ==
				sort_result->action_list[sort_result->action_list_size - c - 1])
			c++;
	}
	sort_result->seq_action_counter = c;
	return ;
}

void			optimize_last_actions(t_sort_result *sort_result)
{
	size_t			c;
	t_move_action	last_action;

	if (sort_result->action_list_size > 1)
	{
		last_action = sort_result->action_list[sort_result->action_list_size - 1];
		if ((last_action == ra || last_action == rra) &&
			sort_result->seq_action_counter == (size_t)sort_result->stack_a_size)
		{
			sort_result->action_list_size -= sort_result->stack_a_size;
			if (sort_result->action_list_size)
				sort_result->last_action =
						sort_result->action_list[sort_result->action_list_size - 1];
			else
				sort_result->last_action = null;
			count_num_of_consecutive(sort_result);
		}
		last_action = sort_result->action_list[sort_result->action_list_size - 1];
		while ((last_action == rb || last_action == rrb) &&
			(size_t)sort_result->stack_b_size > 2 &&
			sort_result->seq_action_counter >= (size_t)sort_result->stack_b_size)
		{
			sort_result->action_list_size -= sort_result->stack_b_size;
			if (sort_result->action_list_size)
				sort_result->last_action =
						sort_result->action_list[sort_result->action_list_size - 1];
			else
				sort_result->last_action = null;
			count_num_of_consecutive(sort_result);
			last_action = sort_result->action_list[sort_result->action_list_size - 1];
		}
		last_action = sort_result->action_list[sort_result->action_list_size - 1];
		if ((last_action == rr || last_action == rrr) &&
			sort_result->seq_action_counter == (size_t)sort_result->stack_b_size &&
			(size_t)sort_result->stack_a_size == (size_t)sort_result->stack_b_size)
		{
			sort_result->action_list_size -= sort_result->stack_b_size;
			if (sort_result->action_list_size)
				sort_result->last_action =
						sort_result->action_list[sort_result->action_list_size - 1];
			else
				sort_result->last_action = null;
			count_num_of_consecutive(sort_result);
		}
		last_action = sort_result->action_list[sort_result->action_list_size - 1];
		if ((last_action == ra || last_action == rra) &&
			(size_t)sort_result->stack_a_size > 2 &&
			sort_result->seq_action_counter > (size_t)sort_result->stack_a_size / 2)
		{
			sort_result->action_list_size -= sort_result->seq_action_counter;
			c = 0;
			while (c++ < (size_t)sort_result->stack_a_size -
													sort_result->seq_action_counter)
			{
				if (last_action == ra)
					sort_result->action_list[sort_result->action_list_size] = rra;
				else
					sort_result->action_list[sort_result->action_list_size] = ra;
				sort_result->action_list_size++;
			}
			if (sort_result->action_list_size)
				sort_result->last_action =
						sort_result->action_list[sort_result->action_list_size - 1];
			else
				sort_result->last_action = null;
			count_num_of_consecutive(sort_result);
		}
		last_action = sort_result->action_list[sort_result->action_list_size - 1];
		// if ((last_action == rr) &&
		// 	sort_result->seq_action_counter > (size_t)sort_result->stack_a_size / 2 &&
		// 	(size_t)sort_result->stack_a_size == (size_t)sort_result->stack_b_size)
		// {
		// 	sort_result->action_list_size -= sort_result->seq_action_counter;
		// 	c = 0;
		// 	while (c++ < (size_t)sort_result->stack_a_size -
		// 											sort_result->seq_action_counter)
		// 	{
		// 		sort_result->action_list[sort_result->action_list_size] = rrr;
		// 		sort_result->action_list_size++;
		// 	}
		// 	if (sort_result->action_list_size)
		// 		sort_result->last_action =
		// 				sort_result->action_list[sort_result->action_list_size - 1];
		// 	else
		// 		sort_result->last_action = null;
		// 	count_num_of_consecutive(sort_result);
		// }
		last_action = sort_result->action_list[sort_result->action_list_size - 1];
		if ((last_action == rb || last_action == rrb) &&
			sort_result->seq_action_counter > (size_t)sort_result->stack_b_size / 2)
		{
			sort_result->action_list_size -= sort_result->seq_action_counter;
			c = 0;
			while (c++ < (size_t)sort_result->stack_b_size -
													sort_result->seq_action_counter)
			{
				if (last_action == rb)
					sort_result->action_list[sort_result->action_list_size] = rrb;
				else
					sort_result->action_list[sort_result->action_list_size] = rb;
				sort_result->action_list_size++;
			}
			if (sort_result->action_list_size)
				sort_result->last_action =
						sort_result->action_list[sort_result->action_list_size - 1];
			else
				sort_result->last_action = null;
			count_num_of_consecutive(sort_result);
		}
	}
	return ;
}

void			add_action(t_sort_result *sort_result, t_move_action action)
{
	t_move_action	last_action;

	last_action = !sort_result->action_list_size ? null :
		sort_result->action_list[sort_result->action_list_size - 1];
	if (last_action &&
		((last_action == ra && action == rra) ||
		(last_action == rra && action == ra) ||
		(last_action == sa && action == sa)))
	{
		sort_result->action_list_size--;
		if (sort_result->action_list_size)
			sort_result->last_action =
					sort_result->action_list[sort_result->action_list_size - 1];
		else
			sort_result->last_action = null;
		count_num_of_consecutive(sort_result);
	}
	else if (last_action &&
		((last_action == ra && action == rb) ||
		(last_action == rb && action == ra)))
	{
		sort_result->action_list_size--;
		sort_result->action_list[sort_result->action_list_size] = rr;
		sort_result->action_list_size++;
		if (sort_result->action_list_size)
			sort_result->last_action =
					sort_result->action_list[sort_result->action_list_size - 1];
		else
			sort_result->last_action = null;
		count_num_of_consecutive(sort_result);
	}
	else if (sort_result->seq_action_counter)
	{
		if (last_action == action)
			sort_result->seq_action_counter++;
		else
			sort_result->seq_action_counter = 1;
		sort_result->last_action = action;
		sort_result->action_list[sort_result->action_list_size] = action;
		sort_result->action_list_size++;
	}
	else
	{
		sort_result->seq_action_counter = 1;
		sort_result->last_action = action;
		sort_result->action_list[sort_result->action_list_size] = action;
		sort_result->action_list_size++;
	}
	optimize_last_actions(sort_result);
	return ;
}
