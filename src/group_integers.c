/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group_integers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 18:09:18 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/08 14:08:15 by jkauppi          ###   ########.fr       */
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
	int			stop_index;

	i = -1;
	while (++i < sort_result->move_cost_size)
		sort_result->move_cost[i].sort_group = none;
	stop_index = (sort_result->move_cost_size) / 6;
	i = -1;
	while (++i < stop_index)
		sort_result->move_cost[i].sort_group = group1;
	stop_index += (sort_result->move_cost_size) / 6;
	i--;
	while (++i < stop_index)
		sort_result->move_cost[i].sort_group = group2;
	stop_index += (sort_result->move_cost_size) / 6;
	i--;
	while (++i < stop_index)
		sort_result->move_cost[i].sort_group = group3;
	stop_index += (sort_result->move_cost_size) / 6;
	i--;
	while (++i < stop_index)
		sort_result->move_cost[i].sort_group = group4;
	stop_index += (sort_result->move_cost_size) / 6;
	i--;
	while (++i < stop_index)
		sort_result->move_cost[i].sort_group = group5;
	i--;
	while (++i < sort_result->move_cost_size)
		sort_result->move_cost[i].sort_group = group6;
	return ;
}

void			devide_integers_into_groups_v3(t_sort_result *sort_result)
{
	int			i;
	int			stop_index;

	i = -1;
	while (++i < sort_result->move_cost_size)
		sort_result->move_cost[i].sort_group = none;
	stop_index = (sort_result->move_cost_size) / 7;
	i = -1;
	while (++i < stop_index)
		sort_result->move_cost[i].sort_group = group1;
	stop_index += (sort_result->move_cost_size) / 7;
	i--;
	while (++i < stop_index)
		sort_result->move_cost[i].sort_group = group2;
	stop_index += (sort_result->move_cost_size) / 7;
	i--;
	while (++i < stop_index)
		sort_result->move_cost[i].sort_group = group3;
	stop_index += (sort_result->move_cost_size) / 7;
	i--;
	while (++i < stop_index)
		sort_result->move_cost[i].sort_group = group4;
	stop_index += (sort_result->move_cost_size) / 7;
	i--;
	while (++i < stop_index)
		sort_result->move_cost[i].sort_group = group5;
	stop_index += (sort_result->move_cost_size) / 7;
	i--;
	while (++i < stop_index)
		sort_result->move_cost[i].sort_group = group6;
	i--;
	while (++i < sort_result->move_cost_size)
		sort_result->move_cost[i].sort_group = group7;
	return ;
}
