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

int			main(int argc, char **argv)
{
	t_sort_result		*sort_result;
	int			error_code;

	sort_result = initialize_checker();
	read_optional_parameters(sort_result, argc, argv);
	read_input_data(sort_result);
	validate_instructions(sort_result);
	error_code = print_result(sort_result);
	return (error_code);
}
