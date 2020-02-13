/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_result.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 14:31:01 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/13 20:06:07 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void		print_action(t_move_action action)
{
	if (action == sa)
		ft_putendl("sa");
	else if (action == sb)
		ft_putendl("sb");
	else if (action == pa)
		ft_putendl("pa");
	else if (action == pb)
		ft_putendl("pb");
	else if (action == ra)
		ft_putendl("ra");
	else if (action == rb)
		ft_putendl("rb");
	else if (action == rra)
		ft_putendl("rra");
	else if (action == rrb)
		ft_putendl("rrb");
	else if (action == rr)
		ft_putendl("rr");
	else if (action == rrr)
		ft_putendl("rrr");
	else if (action == ss)
		ft_putendl("ss");
	return ;
}

void			print_action_list(t_list **result_array)
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
		else if (((t_sort_result *)elem->content)->action_list_size <=
												sort_result->action_list_size)
			sort_result = (t_sort_result *)elem->content;
		elem = elem->next;
	}
	c = -1;
	if (sort_result)
	{
		while (++c < sort_result->action_list_size)
			print_action(sort_result->action_list[c]);
	}
	return ;
}

void			print_num_of_actions(t_sort_result *sort_result)
{
	ft_printf("V2: %5d\n", sort_result->action_list_size);
	return ;
}
