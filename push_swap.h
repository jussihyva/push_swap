/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 17:57:41 by jkauppi           #+#    #+#             */
/*   Updated: 2020/01/19 10:46:22 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <stdlib.h>
# include <limits.h>
# include "libft.h"
# include "ft_printf.h"

struct		s_stack_index
{
	size_t	top;
	size_t	next;
	size_t	bottom;
};

typedef struct s_stack_index	t_stack_index;

struct		s_sort_result
{
	int				*stack;
	size_t			stack_size;
	int				min;
	int				max;
	int				average;
	int				median;
	char			**action_list;
	size_t			action_list_size;
	size_t			seq_action_counter;
	char			*last_action;
	t_stack_index	stack_index;
};

typedef struct s_sort_result	t_sort_result;

int			ft_printf(const char *format, ...);
void		bubble_sort_v1(t_sort_result *sort_result);
void		bubble_sort_v2(t_sort_result *sort_result);
void		bubble_sort_v3(t_sort_result *sort_result);
void		optimize_last_actions(t_sort_result *sort_result);
void		add_action(t_sort_result *sort_result, char *action_string);
void		print_stack(int *stack, int size);
void		print_action_list(t_sort_result *sort_result);
void		ft_int_swap(int *ptr1, int *ptr2);

#endif
