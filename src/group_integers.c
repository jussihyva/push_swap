/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group_integers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 18:09:18 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/06 18:14:46 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void			devide_integers_into_groups_v1(t_sort_result *sort_result)
{
	int			c;

	c = -1;
	while (++c < sort_result->move_cost_size)
		sort_result->move_cost[c].sort_group = none;
	c = -1;
	while (++c < (sort_result->move_cost_size / 2) + 1)
	{
		sort_result->move_cost[c].sort_group = group1;
	}
	while (++c < sort_result->move_cost_size)
	{
		sort_result->move_cost[c].sort_group = group2;
	}
	return ;
}

