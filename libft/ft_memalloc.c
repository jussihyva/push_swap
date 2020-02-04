/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 08:45:35 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/04 10:17:19 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*mem_area;

	if ((mem_area = malloc(size)))
	{
		((char *)mem_area)[size - 1] = 0;
		((char *)mem_area)[0] = 0;
	}
	return (mem_area);
}
