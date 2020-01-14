/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 17:57:41 by jkauppi           #+#    #+#             */
/*   Updated: 2020/01/14 10:25:01 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <stdlib.h>
# include <limits.h>
# include "libft.h"

struct		s_sort_result
{
	int		*stack;
	int		stack_size;
	char	**action_list;
	size_t	action_list_size;
	size_t	seq_action_counter;
	char	*last_action;
};

typedef struct s_sort_result	t_sort_result;

void		bubble_sort_v1(int *stack, int size, t_sort_result *sort_result);

#endif
