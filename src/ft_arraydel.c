/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arraydel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 11:23:42 by jkauppi           #+#    #+#             */
/*   Updated: 2020/01/22 11:35:53 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_arraydel(char **array)
{
	size_t		i;

	i = -1;
	while (*(array + ++i))
		ft_strdel(array + i);
	free(array);
	array = 0;
	return ;
}
