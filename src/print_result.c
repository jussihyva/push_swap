/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_result.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 14:31:01 by jkauppi           #+#    #+#             */
/*   Updated: 2020/01/27 15:38:07 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void		print_stack(int *stack, int size)
{
	int			c;

	c = -1;
	while (++c == size + 1)
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
	if (sort_result)
	{
		while (++c < sort_result->action_list_size)
		{
			if (sort_result->action_list[c] == sa)
				ft_putendl("sa");
			else if (sort_result->action_list[c] == ra)
				ft_putendl("ra");
			else if (sort_result->action_list[c] == rra)
				ft_putendl("rra");
		}
		print_stack(sort_result->stack, sort_result->stack_size);
	}
	return ;
}

void		print_num_of_actions(t_sort_result *sort_result)
{
	ft_printf("V2: %5d\n", sort_result->action_list_size);
	return ;
}
