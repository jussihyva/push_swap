/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstswap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:51:46 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/12 16:53:12 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void					ft_lstswap(t_list *elem1, t_list *elem2)
{
	elem2->prev = elem1->prev;
	if (elem1->prev)
		elem1->prev->next = elem2;
	elem1->next = elem2->next;
	elem1->prev = elem2;
	if (elem2->next)
		elem2->next->prev = elem1;
	elem2->next = elem1;
	return ;
}
