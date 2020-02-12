/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:54:47 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/12 16:55:38 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void		ft_lstsort(t_list **list, int cmp(t_list *elem1, t_list *elem2))
{
	t_list		*elem;
	int			is_sorted;

	is_sorted = 0;
	while (!is_sorted)
	{
		elem = *list;
		is_sorted = 1;
		while (elem)
		{
			if (elem->next && !cmp(elem, elem->next))
			{
				if (*list == elem)
					*list = elem->next;
				ft_lstswap(elem, elem->next);
				is_sorted = 0;
			}
			else
				elem = elem->next;
		}
	}
	return ;
}
