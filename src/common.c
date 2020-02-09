/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 18:37:12 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/09 20:32:57 by jkauppi          ###   ########.fr       */
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

static int		validity_check(char *string, int atoi_int, int *integer, size_t size)
{
	size_t		c;

	if (atoi_int > INT_MAX || atoi_int < INT_MIN)
		return (0);
	if (ft_strlen(string) == 1 && *string == '-')
		return (0);
	c = 0;
	if (*string == '-')
		c++;
	while (string[c] && ft_isdigit(string[c]))
		c++;
	if (string[c])
		return (0);
	c = 1;
	while (c < size && integer[c] != *integer)
		c++;
	if (c < size)
		return (0);
	if (ft_strlen(string) > 3 && *integer < 9 && *integer > -9)
		return (0);
	return (1);
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
	char		*string;
	int			atoi_int;

	stack = NULL;
	if ((str_array = ft_strsplit(s, ' ')))
	{
		while (*(str_array + input->int_array_size))
			input->int_array_size++;
		i = input->int_array_size;
		stack = (int *)ft_memalloc(sizeof(*stack) * input->int_array_size);
		while (i--)
		{
			string = str_array[input->int_array_size - i - 1];
			atoi_int = ft_atoi(string);
			stack[i] = atoi_int;
			if (!validity_check(string, atoi_int, &stack[i], input->int_array_size - i))
				return (1);
			add_to_list(&input->int_list, stack + i);
		}
		ft_arraydel(str_array);
	}
	input->int_array = stack;
	return (0);
}
