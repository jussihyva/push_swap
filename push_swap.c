/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 17:56:31 by jkauppi           #+#    #+#             */
/*   Updated: 2020/01/13 11:23:21 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int		*save_to_stack(char **array, int size)
{
	int			*stack;
	int			c;

	stack = (int *)malloc(sizeof(*stack) * size);
	c = -1;
	while (++c < size)
		stack[c] = ft_atoi(array[c]);
	return (stack);
}

static void		print_stack(int *stack, int size)
{
	int			c;

	c = -1;
	while (++c < size)
	{
		ft_putnbr(*(stack + c));
		ft_putchar(' ');
	}
	ft_putchar('\n');
}

static void		swap_int(int *i1, int *i2)
{
	int		tmp;

	tmp = *i1;
	*i1 = *i2;
	*i2 = tmp;
}

static int		*bubble_sort_v1(int *stack, int size)
{
	int		is_sorted;
	int		c;

	is_sorted = 1;
	while (is_sorted)
	{
		is_sorted = 0;
		c = 0;
		while (++c < size)
		{
			if (stack[c] < stack[c - 1])
			{
				swap_int(&stack[c], &stack[c - 1]);
				is_sorted = 1;
			}
		}
	}
	return (stack);
}

int				main(int argc, char **argv)
{
	int			*stack_a;
	int			*sorted_stack_a;
	int			size;

	if (argc > 1)
	{
		size = argc - 1;
		stack_a = save_to_stack(argv + 1, size);
		sorted_stack_a = bubble_sort_v1(stack_a, size);
		print_stack(sorted_stack_a, size);
	}
	return (0);
}
