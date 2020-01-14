/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bubble_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 13:21:32 by jkauppi           #+#    #+#             */
/*   Updated: 2020/01/14 10:17:24 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void		swap_int(int *i1, int *i2)
{
	int		tmp;

	tmp = *i1;
	*i1 = *i2;
	*i2 = tmp;
}

static void		add_action(t_sort_result *sort_result, char *action_string)
{
	sort_result->action_list[sort_result->action_list_size] =
													ft_strdup(action_string);
	sort_result->action_list_size++;
	return ;
}

void			bubble_sort_v1(int *stack, int size, t_sort_result *sort_result)
{
	int		is_sorted;
	int		*top_ptr;

	is_sorted = 1;
	top_ptr = stack + size - 1;
	sort_result->action_list_size = 0;
	while (is_sorted)
	{
		is_sorted = 0;
		while (top_ptr > stack)
		{
			if (*top_ptr > *(top_ptr - 1))
			{
				swap_int(top_ptr, top_ptr - 1);
				add_action(sort_result, "sa");
				is_sorted = 1;
			}
			add_action(sort_result, "ra");
			top_ptr--;
		}
		add_action(sort_result, "ra");
		top_ptr = stack + size - 1;
	}
	return ;
}
