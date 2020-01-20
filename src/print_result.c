/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_result.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 14:31:01 by jkauppi           #+#    #+#             */
/*   Updated: 2020/01/20 15:44:08 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void		save_result(t_sort_result *sort_result)
{
	(void)sort_result;
	return ;
}

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

void		print_action_list(t_list **result_array)
{
	size_t			c;
	t_sort_result	*sort_result;
	t_list			*elem;

	sort_result = NULL;
	elem = *result_array;
	while (elem)
	{
		if (!sort_result)
			sort_result = (t_sort_result *)elem->content;
		else if (((t_sort_result *)elem->content)->action_list_size <
												sort_result->action_list_size)
			sort_result = (t_sort_result *)elem->content;
		elem = elem->next;
	}
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
