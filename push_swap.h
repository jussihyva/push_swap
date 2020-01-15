/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 17:57:41 by jkauppi           #+#    #+#             */
/*   Updated: 2020/01/15 16:46:09 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <stdlib.h>
# include <limits.h>
# include "libft.h"
# include "ft_printf.h"

struct		s_sort_result
{
	int		*stack;
	int		stack_size;
	int		average;
	char	**action_list;
	size_t	action_list_size;
	size_t	seq_action_counter;
	char	*last_action;
};

typedef struct s_sort_result	t_sort_result;

int			ft_printf(const char *format, ...);
void		bubble_sort_v1(t_sort_result *sort_result);
void		bubble_sort_v2(int *stack, int size, t_sort_result *sort_result);
void		minimize_last_actions(t_sort_result *sort_result);
void		add_action(t_sort_result *sort_result, char *action_string);
void		swap_int(int *i1, int *i2);
void		print_stack(int *stack, int size);
void		print_action_list(t_sort_result *sort_result);

#endif
