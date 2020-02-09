/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 16:22:03 by jkauppi           #+#    #+#             */
/*   Updated: 2020/01/12 17:57:01 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static t_input_data	*initialize_checker(void)
{
	t_input_data		*input_data;
	char			*parameter_array;

	return (input_data);
}

static void		read_input_data(t_input_data input_data, int argc, char **argv)
{
	int			valid_opt_flags;

	valid_opt_flags = f;
	parameter_array = read_attributes(valid_opt_flags, argc, argv);
}

int			main(int argc, char **argv)
{
	t_input_data		*input_data;
	t_validation_result	result;
	int			return_code;

	input_data = initialize_checker();
	read_input_data(input_data, argc, argv);
	result = validate_instructions(input_data);
	return_code = print_result(result);
	return (error_code);
}
