/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_e.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 08:10:44 by jkauppi           #+#    #+#             */
/*   Updated: 2019/11/10 15:52:20 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_e(t_list **alst, t_list *new)
{
	t_list	*elem;

	if (*alst)
	{
		elem = *alst;
		while (elem->next)
			elem = elem->next;
		elem->next = new;
	}
	else
		*alst = new;
	return ;
}
