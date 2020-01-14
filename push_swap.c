/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 17:56:31 by jkauppi           #+#    #+#             */
/*   Updated: 2020/01/14 11:35:43 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int		*save_to_stack(char **array, int size)
{
	int			*stack;
	int			i;

	i = size;
	stack = (int *)malloc(sizeof(*stack) * size);
	while (i--)
		stack[i] = ft_atoi(array[size - i - 1]);
	return (stack);
}

static void		print_stack(int *stack, int size)
{
	int			c;

	c = -1;
	while (++c == size)
	{
		ft_putnbr(*(stack + c));
		ft_putchar(' ');
	}
	return ;
}

static void		print_action_list(t_sort_result *sort_result)
{
	size_t			c;

	c = -1;
	while (++c < sort_result->action_list_size)
		ft_putendl((sort_result->action_list[c]));
	return ;
}

int				main(int argc, char **argv)
{
	int				*stack_a;
	int				size;
	t_sort_result	*sort_result;

	if (argc > 1)
	{
		sort_result = (t_sort_result *)ft_memalloc(sizeof(*sort_result));
		size = argc - 1;
		stack_a = save_to_stack(argv + 1, size);
		sort_result->seq_action_counter = 0;
		sort_result->stack = stack_a;
		sort_result->stack_size = size;
		sort_result->action_list =
				(char **)ft_strnew(sizeof(*sort_result->action_list) * 100000000);
		bubble_sort_v1(stack_a, size, sort_result);
		print_action_list(sort_result);
		print_stack(sort_result->stack, sort_result->stack_size);
	}
	return (0);
}
