/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 18:37:12 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/10 08:56:46 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "checker.h"

char			*merge_args(char **array, int size)
{
	char		*s;
	char		*tmp;
	int			c;

	c = 0;
	s = ft_strdup(array[c]);
	while (++c < size)
	{
		tmp = ft_strjoin(s, " ");
		ft_strdel(&s);
		s = ft_strjoin(tmp, array[c]);
		ft_strdel(&tmp);
	}
	return (s);
}

static void		add_to_list(t_list **list, int *integer)
{
	t_list		*elem;

	elem = ft_lstnew(integer, sizeof(integer));
	if (*list)
		ft_lstadd_e(list, elem);
	else
		*list = elem;
}

int				string_to_array(char *s, t_input_data *input)
{
	int			*stack;
	size_t		i;
	char		**str_array;
	char		*endptr;

	stack = NULL;
	endptr = NULL;
	if ((str_array = ft_strsplit(s, ' ')))
	{
		while (*(str_array + input->int_array_size))
			input->int_array_size++;
		i = input->int_array_size;
		stack = (int *)ft_memalloc(sizeof(*stack) * input->int_array_size);
		while (i--)
		{
			stack[i] = ft_strtoi(str_array[input->int_array_size - i - 1],
																&endptr, 10);
			if (errno || (endptr && *endptr))
				return (1);
			add_to_list(&input->int_list, stack + i);
		}
		ft_arraydel(str_array);
	}
	input->int_array = stack;
	return (0);
}
