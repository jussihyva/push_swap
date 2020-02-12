/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_add_algorithms.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 13:27:57 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/12 15:01:13 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void			add_bubble_sort_algorithms(t_list **sort_function_list)
{
	t_sort_function			sort_function;

	sort_function.num_of_actions = 0;
	sort_function.sort_function = (void *)bubble_sort_v1;
	ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
	sort_function.sort_function = (void *)bubble_sort_v2;
	ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
	sort_function.sort_function = (void *)bubble_sort_v3;
	ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
	// sort_function.sort_function = (void *)bubble_sort_v2_1;
	// ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
	// sort_function.sort_function = (void *)bubble_sort_v2_2;
	// ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
	// sort_function.sort_function = (void *)bubble_sort_v2_3;
	// ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
	// sort_function.sort_function = (void *)bubble_sort_v2_4;
	// ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
	// sort_function.sort_function = (void *)bubble_sort_v2_5;
	// ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
	// sort_function.sort_function = (void *)bubble_sort_v3_1;
	// ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
	return ;
}

void			add_random_algorithms(t_list **sort_function_list)
{
	t_sort_function			sort_function;

	sort_function.num_of_actions = 0;
	sort_function.sort_function = (void *)random_sort_v1;
	ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
	// sort_function.sort_function = (void *)random_sort_v2;
	// ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
	// sort_function.sort_function = (void *)random_sort_v3;
	// ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
	return ;
}

void			add_insertion_algorithms(t_list **sort_function_list)
{
	t_sort_function			sort_function;

	sort_function.num_of_actions = 0;
	sort_function.sort_function = (void *)insertion_sort_v1;
	ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
	return ;
}

void			add_less_moves_sort_algorithms(t_list **sort_function_list)
{
	t_sort_function			sort_function;

	sort_function.num_of_actions = 0;
	(void)sort_function_list;
	// 	sort_function.sort_function = (void *)less_moves_sort_v1_1;
	// 	ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
	// 	sort_function.sort_function = (void *)less_moves_sort_v1_2;
	// 	ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
	// 	sort_function.sort_function = (void *)less_moves_sort_v1_3;
	// 	ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
	// 	sort_function.sort_function = (void *)less_moves_sort_v1_4;
	// 	ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
	// 	sort_function.sort_function = (void *)less_moves_sort_v2_1;
	// 	ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
	// 	sort_function.sort_function = (void *)less_moves_sort_v3_1;
	// 	ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
	// 	sort_function.sort_function = (void *)less_moves_sort_v3_2;
	// 	ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
	// 	sort_function.sort_function = (void *)less_moves_sort_v3_3;
	// 	ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
	// 	sort_function.sort_function = (void *)less_moves_sort_v3_4;
	// 	ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
	sort_function.sort_function = (void *)less_moves_sort_v4_1;
	ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
	sort_function.sort_function = (void *)less_moves_sort_v4_2;
	ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
	sort_function.sort_function = (void *)less_moves_sort_v4_3;
	ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
	sort_function.sort_function = (void *)less_moves_sort_v4_4;
	ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
	return ;
}

void			add_sort_algorithms(t_list **sort_function_list)
{
	add_bubble_sort_algorithms(sort_function_list);
	add_random_algorithms(sort_function_list);
	add_insertion_algorithms(sort_function_list);
	add_less_moves_sort_algorithms(sort_function_list);
	return ;
}
