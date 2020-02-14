/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 14:44:30 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/14 08:46:37 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "checker.h"

void					activate_linked_list_loop(t_list *int_lst)
{
	t_list					*elem;

	elem = int_lst;
	if (elem)
	{
		while (elem && elem->next)
			elem = elem->next;
		int_lst->prev = elem;
		elem->next = int_lst;
	}
	return ;
}

static int				next_attr(t_attr_flags opt, int *argc, char ***argv)
{
	(*argc)--;
	(*argv)++;
	return (opt);
}

int						read_optional_attributes(int valid_opt_flags, int *argc,
									char ***argv, t_opt_attr *opt_attr)
{
	int			result;

	opt_attr->attr_flags = 0;
	opt_attr->instruction_file = NULL;
	result = 1;
	if ((valid_opt_flags & instruction_file) && *argc &&
													ft_strequ(*argv[0], "-f"))
	{
		opt_attr->attr_flags |= next_attr(0, argc, argv);
		if (*argc > 0)
		{
			opt_attr->instruction_file = ft_strdup(*argv[0]);
			opt_attr->attr_flags |= instruction_file;
			opt_attr->attr_flags |= next_attr(0, argc, argv);
		}
		else
			result = 0;
	}
	if ((valid_opt_flags & verbose) && *argc && ft_strequ(*argv[0], "-v"))
		opt_attr->attr_flags |= next_attr(verbose, argc, argv);
	if ((valid_opt_flags & leaks_pause) && *argc && ft_strequ(*argv[0], "-l"))
		opt_attr->attr_flags |= next_attr(leaks_pause, argc, argv);
	return (result);
}

int						read_integer_values(t_input_data *input,
														int argc, char **argv)
{
	t_validation_result		result;
	char					*integer_string;

	input->int_array_size = 0;
	input->int_array = NULL;
	input->int_list = NULL;
	if (argc)
	{
		integer_string = merge_args(argv, argc);
		result = string_to_array(integer_string, input);
		ft_strdel(&integer_string);
	}
	else
		result = no_param;
	return (result);
}

int						print_result(t_validation_result result)
{
	int			return_code;

	return_code = 0;
	if (result == no_param)
		;
	else if (result == ok)
		ft_dprintf(1, "OK\n");
	else if (result == ko)
		ft_dprintf(1, "KO\n");
	else if (result == error)
	{
		ft_dprintf(2, "Error\n");
		return_code = 1;
	}
	return (0);
}
