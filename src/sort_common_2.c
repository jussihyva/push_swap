/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_common_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 10:54:38 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/13 17:18:42 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void			count_num_of_consecutive(t_sort_result *sort_result)
{
	size_t			c;
	t_move_action	last_action;

	c = 1;
	if (sort_result->action_list_size)
	{
		last_action =
					sort_result->action_list[sort_result->action_list_size - 1];
		while (last_action ==
				sort_result->action_list[sort_result->action_list_size - c - 1])
			c++;
	}
	sort_result->seq_action_counter = c;
	return ;
}

static void		optimize_ra_rra(t_sort_result *sort_result,
									t_move_action last_action, t_stack stack)
{
	size_t			c;

	while ((last_action == ra || last_action == rra) && stack.int_lst_size > 0)
	{
		if (sort_result->seq_action_counter >= (size_t)stack.int_lst_size)
			sort_result->action_list_size -= stack.int_lst_size;
		else if (sort_result->seq_action_counter >
												(size_t)stack.int_lst_size / 2)
		{
			sort_result->action_list_size -= sort_result->seq_action_counter;
			c = 0;
			while (c++ < (size_t)stack.int_lst_size -
												sort_result->seq_action_counter)
			{
				sort_result->action_list[sort_result->action_list_size] =
												last_action == ra ? rra : ra;
				sort_result->action_list_size++;
			}
		}
		else
			break ;
		count_num_of_consecutive(sort_result);
		last_action =
					sort_result->action_list[sort_result->action_list_size - 1];
	}
}

static void		optimize_rb_rrb(t_sort_result *sort_result,
									t_move_action last_action, t_stack stack)
{
	size_t			c;

	while ((last_action == rb || last_action == rrb) && stack.int_lst_size > 0)
	{
		if (sort_result->seq_action_counter >= (size_t)stack.int_lst_size)
			sort_result->action_list_size -= stack.int_lst_size;
		else if (sort_result->seq_action_counter >
												(size_t)stack.int_lst_size / 2)
		{
			sort_result->action_list_size -= sort_result->seq_action_counter;
			c = 0;
			while (c++ < (size_t)stack.int_lst_size -
												sort_result->seq_action_counter)
			{
				sort_result->action_list[sort_result->action_list_size] =
												last_action == rb ? rrb : rb;
				sort_result->action_list_size++;
			}
		}
		else
			break ;
		count_num_of_consecutive(sort_result);
		last_action =
					sort_result->action_list[sort_result->action_list_size - 1];
	}
}

void			optimize_last_actions(t_sort_result *sort_result)
{
	t_move_action	last_action;
	t_move_action	*action_list;

	action_list = sort_result->action_list;
	if (sort_result->action_list_size > 1)
	{
		last_action = action_list[sort_result->action_list_size - 1];
		optimize_rb_rrb(sort_result, last_action, sort_result->stack_b);
		last_action = action_list[sort_result->action_list_size - 1];
		optimize_ra_rra(sort_result, last_action, sort_result->stack_a);
		last_action = action_list[sort_result->action_list_size - 1];
		if ((last_action == rr || last_action == rrr) &&
			sort_result->seq_action_counter ==
									(size_t)sort_result->stack_b.int_lst_size &&
			(size_t)sort_result->stack_a.int_lst_size ==
									(size_t)sort_result->stack_b.int_lst_size)
		{
			sort_result->action_list_size -= sort_result->stack_b.int_lst_size;
			count_num_of_consecutive(sort_result);
		}
		last_action = action_list[sort_result->action_list_size - 1];
	}
	return ;
}

int				check_merge_actions(t_sort_result *sort_result,
								t_move_action last_action, t_move_action action)
{
	int		result;

	if (last_action &&
		((last_action == ra && action == rb) ||
		(last_action == rb && action == ra)))
	{
		sort_result->action_list_size--;
		sort_result->action_list[sort_result->action_list_size] = rr;
		sort_result->action_list_size++;
		count_num_of_consecutive(sort_result);
		result = 1;
	}
	else if (last_action &&
		((last_action == rra && action == rrb) ||
		(last_action == rrb && action == rra)))
	{
		sort_result->action_list_size--;
		sort_result->action_list[sort_result->action_list_size] = rrr;
		sort_result->action_list_size++;
		count_num_of_consecutive(sort_result);
		result = 1;
	}
	else
		result = 0;
	return (result);
}
