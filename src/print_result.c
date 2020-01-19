/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_result.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 14:31:01 by jkauppi           #+#    #+#             */
/*   Updated: 2020/01/19 14:39:49 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void		print_stack(int *stack, int size)
{
	int			c;

	c = -1;
	while (++c == size)
	{
		ft_putnbr(*(stack + c));
		ft_putchar(' ');
	}
	return ;
}

void		print_action_list(t_sort_result *sort_result)
{
	size_t			c;

	c = -1;
	while (++c < sort_result->action_list_size)
		ft_putendl((sort_result->action_list[c]));
	return ;
}

void		print_num_of_actions(t_sort_result *sort_result)
{
	ft_printf("V2: %5d\n", sort_result->action_list_size);
	return ;
}