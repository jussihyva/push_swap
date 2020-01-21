/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 17:57:41 by jkauppi           #+#    #+#             */
/*   Updated: 2020/01/21 14:42:34 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <stdlib.h>
# include <limits.h>
# include "libft.h"
# include "ft_printf.h"

enum		e_move_action
{
	null = 0,
	sa = 0x01,
	ra = 0x02,
	rra = 0x04
};

typedef enum e_move_action		t_move_action;

struct		s_stack_ptr
{
	int		*top;
	int		*next;
	int		*bottom;
	int		*smallest_int;
};

typedef struct s_stack_ptr		t_stack_ptr;

struct		s_input_data
{
	int		argc;
	char	**argv;
	int		*int_array;
	size_t	int_array_size;
	int		min;
	int		max;
	int		average;
	int		median;
};

typedef struct s_input_data		t_input_data;

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
	t_stack_ptr		stack_ptr;
};

typedef struct s_sort_result	t_sort_result;

int				ft_printf(const char *format, ...);
void			bubble_sort_v1(t_sort_result *sort_result, t_list **result_array);
void			bubble_sort_v2(t_sort_result *sort_result, t_list **result_array);
void			bubble_sort_v3(t_sort_result *sort_result, t_list **result_array);
void			insertion_sort_v1(t_sort_result *sort_result, t_list **result_array);
void			random_sort_v1(t_sort_result *sort_result, t_list **result_array);
void			optimize_last_actions(t_sort_result *sort_result);
void			add_action(t_sort_result *sort_result, char *action_string);
void			print_stack(int *stack, int size);
void			print_action_list(t_list **result_array);
void			print_num_of_actions(t_sort_result *sort_result);
void			ft_int_swap(int *ptr1, int *ptr2);
void			execute_action(t_sort_result *sort_result, char *action_string);
void			step_prt_down(t_sort_result *sort_result);
void			save_result(t_sort_result *sort_result);
t_sort_result	*init_sort_result(void);
int				*ft_intcpy(int const *array, size_t size);
char			**ft_str_array_dup(char **array, size_t size);

#endif
