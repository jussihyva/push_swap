/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_bubble_common.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 10:54:38 by jkauppi           #+#    #+#             */
/*   Updated: 2020/01/18 16:15:08 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void		count_num_of_consecutive(t_sort_result *sort_result)
{
	size_t		c;

	c = 0;
	if (sort_result->action_list_size)
	{
		c++;
		while (sort_result->last_action ==
				sort_result->action_list[sort_result->action_list_size - c - 1])
			c++;
	}
	sort_result->seq_action_counter = c;
	return ;
}

void			optimize_last_actions(t_sort_result *sort_result)
{
	size_t		c;

	if (sort_result->seq_action_counter > (size_t)sort_result->stack_size / 2)
	{
		c = 0;
		sort_result->action_list_size -= sort_result->seq_action_counter;
		while (c++ < (size_t)sort_result->stack_size -
												sort_result->seq_action_counter)
		{
			if (ft_strequ(sort_result->last_action, "ra"))
				sort_result->action_list[sort_result->action_list_size] =
													ft_strdup("rra");
			else
				sort_result->action_list[sort_result->action_list_size] =
													ft_strdup("ra");
			sort_result->action_list_size++;
		}
	}
	return ;
}

void			add_action(t_sort_result *sort_result, char *action_string)
{
	if ((ft_strequ(sort_result->last_action, "ra") &&
											ft_strequ(action_string, "rra")) ||
		(ft_strequ(sort_result->last_action, "rra") &&
												ft_strequ(action_string, "ra")))
	{
		sort_result->action_list_size--;
		if (sort_result->action_list_size)
			sort_result->last_action =
					sort_result->action_list[sort_result->action_list_size - 1];
		else
			sort_result->last_action = ft_strdup("");
		count_num_of_consecutive(sort_result);
	}
	else if (sort_result->seq_action_counter)
	{
		if (ft_strequ(sort_result->last_action, action_string))
			sort_result->seq_action_counter++;
		else
		{
			optimize_last_actions(sort_result);
			sort_result->seq_action_counter = 1;
			sort_result->last_action = action_string;
		}
		sort_result->action_list[sort_result->action_list_size] =
													ft_strdup(action_string);
		sort_result->action_list_size++;
	}
	else
	{
		sort_result->seq_action_counter = 1;
		sort_result->last_action = action_string;
		sort_result->action_list[sort_result->action_list_size] =
													ft_strdup(action_string);
		sort_result->action_list_size++;
	}
	if (sort_result->seq_action_counter == (size_t)sort_result->stack_size)
	{
		sort_result->action_list_size -= sort_result->stack_size;
		if (sort_result->action_list_size)
			sort_result->last_action =
					sort_result->action_list[sort_result->action_list_size - 1];
		else
			sort_result->last_action = ft_strdup("");
		count_num_of_consecutive(sort_result);
	}
	return ;
}
