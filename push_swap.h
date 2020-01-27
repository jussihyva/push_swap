/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 17:57:41 by jkauppi           #+#    #+#             */
/*   Updated: 2020/01/27 21:32:44 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <stdlib.h>
# include <limits.h>
# include "libft.h"
# include "ft_printf.h"
# include <stdio.h>

typedef enum	e_move_action
{
	null = 0,
	sa  = 0x001,
	ra  = 0x002,
	rra = 0x004,
	pb  = 0x008,
	v0  = 0x010,
	v1  = 0x020,
	v2  = 0x040,
	v11 = 0x080,
	pa  = 0x100,
	v31 = 0x200
}				t_move_action;

typedef struct	s_stack_ptr
{
	int		*top;
	t_list	*top_a;
	t_list	*top_b;
	int		*next;
	t_list	*next_a;
	t_list	*next_b;
	int		*bottom;
	t_list	*bottom_a;
	t_list	*bottom_b;
	int		*bottom_1;
	t_list	*bottom_1_a;
	t_list	*bottom_1_b;
	int		*smallest_int;
	int		*smallest_int_a;
	int		*smallest_int_b;
}				t_stack_ptr;

typedef struct	s_input_data
{
	int				argc;
	char			**argv;
	int				*int_array;
	size_t			int_array_size;
	t_list			*int_list;
	int				min;
	int				max;
	int				average;
	int				median;
}				t_input_data;

typedef struct	s_sort_result
{
	int				*stack;
	size_t			stack_size;
	t_list			*stack_a;
	t_list			*stack_b;
	int				min;
	int				max;
	int				average;
	int				median;
	t_move_action	*action_list;
	size_t			action_list_size;
	size_t			seq_action_counter;
	t_move_action	last_action;
	size_t			total_num_of_actions;
	t_stack_ptr		stack_ptr;
}				t_sort_result;

int				ft_printf(const char *format, ...);
void			bubble_sort_v1(t_sort_result *sort_result,
									t_list **result_array, size_t *max_actions);
void			bubble_sort_v2(t_sort_result *sort_result,
									t_list **result_array, size_t *max_actions);
void			bubble_sort_v3(t_sort_result *sort_result,
									t_list **result_array, size_t *max_actions);
void			insertion_sort_v1(t_sort_result *sort_result,
									t_list **result_array, size_t *max_actions);
void			random_sort_v1(t_sort_result *sort_result,
									t_list **result_array, size_t *max_actions);
void			random_sort_v2(t_sort_result *sort_result,
									t_list **result_array, size_t *max_actions);
void			random_sort_v3(t_sort_result *sort_result,
									t_list **result_array, size_t *max_actions);
void			optimize_last_actions(t_sort_result *sort_result);
void			add_action(t_sort_result *sort_result, t_move_action action);
void			print_stack(int *stack, int size);
void			print_action_list(t_list **result_array);
void			print_num_of_actions(t_sort_result *sort_result);
void			ft_int_swap(int *ptr1, int *ptr2);
void			execute_action(t_sort_result *sort_result,
														t_move_action action);
void			step_prt_down(t_sort_result *sort_result);
void			step_prt_up(t_sort_result *sort_result);
void			init_sort_result(t_sort_result *sort_result);
int				*ft_intcpy(int const *array, size_t size);
t_move_action	*ft_int_array_dup(t_move_action *array, size_t size);
void			ft_intswap(int *ptr1, int *ptr2);
void			ft_arraydel(char **array);
int				*ft_intsort(int const *array, size_t size);
void			create_action_order(t_sort_result *sort_result,
						t_move_action *valid_actions, t_move_action last_action,
															t_move_action rule);
void			create_action_order_v11(t_sort_result *sort_result,
						t_move_action *valid_actions, t_move_action last_action);
int				*count_max_average(int *array, size_t size);
int				*ft_intdup(int const *array, size_t size);
void			save_result(t_sort_result *sort_result, size_t *max_actions,
														t_list **result_array);
void			move_to_stack(t_sort_result *sort_result, t_move_action action);
void			create_action_order_v31(t_sort_result *sort_result,
						t_move_action *valid_actions, t_move_action last_action);

#endif
