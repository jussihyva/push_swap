/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 17:57:41 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/05 18:43:36 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <stdlib.h>
# include <limits.h>
# include "libft.h"
# include "ft_printf.h"
# define MAX_ACTIONS 100000

typedef enum	e_sort_group
{
	group0 = 0,
	group1 = 1
}				t_sort_group;

typedef enum	e_move_action
{
	null = 0,
	sa  = 0x0001,
	ra  = 0x0002,
	rra = 0x0004,
	v0  = 0x0008,
	v1  = 0x0010,
	v2  = 0x0020,
	v11 = 0x0040,
	sb  = 0x0080,
	rb  = 0x0100,
	rrb = 0x0200,
	pa  = 0x0400,
	pb  = 0x0800,
	v31 = 0x1000,
	rr  = 0x2000,
	rrr = 0x4000,
	ss  = 0x8000
}				t_move_action;

typedef enum	e_stack_status
{
	source_stack_ready = 0x01,
	target_stack_ready = 0x02,
	stacks_ready = 0x03
}				t_stack_status;

typedef struct s_next_move
{
	t_list			*integer;
	t_move_action	source_stack_action;
	t_move_action	target_stack_action;
}				t_next_move;


typedef struct s_move_cost
{
	t_list		*integer;
	t_sort_group	sort_group;
	long		source_rx;
	long		source_rrx;
	long		target_asc_rx;
	long		target_asc_rrx;
	long		target_dec_rx;
	long		target_dec_rrx;
}				t_move_cost;

typedef struct s_stack
{
	t_list			*top;
	t_list			*int_lst;
	size_t			int_lst_size;
	int				min;
	int				max;
	int				average;
	int				median;
	t_move_cost		*move_cost;
	int				move_cost_size;
}				t_stack;

typedef struct	s_input_data
{
	int				argc;
	char			**argv;
	int				*int_array;
	size_t			int_array_size;
	t_list			*int_list;
	t_list			*int_list_sorted;
	int				min;
	int				max;
	int				average;
	int				median;
}				t_input_data;

typedef struct	s_sort_result
{
	t_stack			stack_a;
	t_stack			stack_b;
	int				*stack_array;
	t_move_action	*action_list;
	size_t			action_list_size;
	size_t			seq_action_counter;
	size_t			total_num_of_actions;
	t_next_move		next_move;
}				t_sort_result;

typedef struct	s_sort_function
{
	void	*(*sort_function)(t_sort_result *sort_result, t_list **result_array,
														size_t *max_actions);
}				t_sort_function;

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
void			step_prt_down_b(t_sort_result *sort_result);
void			step_prt_up(t_sort_result *sort_result);
void			step_prt_up_b(t_sort_result *sort_result);
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
void			split_one_stack_to_two_v1(t_sort_result *sort_result);
void			split_one_stack_to_two_v2(t_sort_result *sort_result);
void			split_one_stack_to_two_v3(t_sort_result *sort_result);
void			split_one_stack_to_two_v4(t_sort_result *sort_result);
void			split_one_stack_to_two_v5(t_sort_result *sort_result);
void			split_one_stack_to_two_v3_1(t_sort_result *sort_result);
void			move_all_to_stack_b_v1(t_sort_result *sort_result);
void			move_all_to_stack_b_v2(t_sort_result *sort_result);
void			move_all_to_stack_b_v3(t_sort_result *sort_result);
void			move_all_to_stack_b_v4(t_sort_result *sort_result);
void			bubble_sort_v2_1(t_sort_result *sort_result,
									t_list **result_array, size_t *max_actions);
void			bubble_sort_v2_2(t_sort_result *sort_result,
									t_list **result_array, size_t *max_actions);
void			bubble_sort_v2_3(t_sort_result *sort_result,
									t_list **result_array, size_t *max_actions);
void			bubble_sort_v2_4(t_sort_result *sort_result,
									t_list **result_array, size_t *max_actions);
void			bubble_sort_v2_5(t_sort_result *sort_result,
									t_list **result_array, size_t *max_actions);
void			bubble_sort_v3_1(t_sort_result *sort_result,
									t_list **result_array, size_t *max_actions);
void			less_moves_sort_v1_1(t_sort_result *sort_result,
									t_list **result_array, size_t *max_actions);
void			less_moves_sort_v1_2(t_sort_result *sort_result,
									t_list **result_array, size_t *max_actions);
void			less_moves_sort_v1_3(t_sort_result *sort_result,
									t_list **result_array, size_t *max_actions);
void			less_moves_sort_v1_4(t_sort_result *sort_result,
									t_list **result_array, size_t *max_actions);
void			less_moves_sort_v2_1(t_sort_result *sort_result,
									t_list **result_array, size_t *max_actions);
void			less_moves_sort_v3_1(t_sort_result *sort_result,
									t_list **result_array, size_t *max_actions);
void			less_moves_sort_v3_2(t_sort_result *sort_result,
									t_list **result_array, size_t *max_actions);
void			less_moves_sort_v3_3(t_sort_result *sort_result,
									t_list **result_array, size_t *max_actions);
void			less_moves_sort_v3_4(t_sort_result *sort_result,
									t_list **result_array, size_t *max_actions);
void			less_moves_sort_v4_1(t_sort_result *sort_result,
									t_list **result_array, size_t *max_actions);
void			min_max(t_sort_result *sort_result);
void			move_max_to_top(t_sort_result *sort_result, t_stack *stack,
												int max, t_move_action action);
void            count_move_cost_v1(t_sort_result *sort_result);
void            count_move_cost_v1_2(t_sort_result *sort_result);
void            count_move_cost_v2(t_sort_result *sort_result);
void            count_move_cost_v3_3(t_sort_result *sort_result);
void            count_move_cost_b_v3_3(t_sort_result *sort_result);

#endif
