/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group_integers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 18:09:18 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/13 20:37:14 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void			devide_integers_into_groups(t_sort_result *sort_result)
{
	int			c;

	c = -1;
	while (++c < sort_result->move_cost_size)
		sort_result->move_cost->sort_group = none;
	return ;
}

void			devide_integers_into_groups_v1(t_sort_result *sort_result)
{
	int			c;

	c = -1;
	while (++c < sort_result->move_cost_size)
		sort_result->move_cost[c].sort_group = none;
	c = -1;
	while (++c < (sort_result->move_cost_size + 1) / 2)
		sort_result->move_cost[c].sort_group = group1;
	c--;
	while (++c < sort_result->move_cost_size)
		sort_result->move_cost[c].sort_group = group2;
	return ;
}

void			devide_integers_into_groups_v2(t_sort_result *sort_result)
{
	int			i;
	int			group;
	size_t		num_groups;
	size_t		int_per_group;

	num_groups = 6;
	int_per_group = 1 + (sort_result->move_cost_size - 1) / num_groups;
	group = 0;
	i = -1;
	while (++i < sort_result->move_cost_size)
	{
		if (!(i % int_per_group))
			group++;
		sort_result->move_cost[i].sort_group = group;
	}
	return ;
}

void			devide_integers_into_groups_v3(t_sort_result *sort_result)
{
	int			i;
	int			group;
	size_t		num_groups;
	size_t		int_per_group;

	num_groups = 4;
	int_per_group = 1 + (sort_result->move_cost_size - 1) / num_groups;
	group = 0;
	i = -1;
	while (++i < sort_result->move_cost_size)
	{
		if (!(i % int_per_group))
			group++;
		sort_result->move_cost[i].sort_group = group;
	}
	return ;
}
