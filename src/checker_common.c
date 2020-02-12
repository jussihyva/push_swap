/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_common.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 14:43:05 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/12 09:30:30 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static int				str_to_rx_move_action(char *str, t_move_action *action)
{
	int						result;

	result = 1;
	if (ft_strequ(str, "ra"))
		*action = ra;
	else if (ft_strequ(str, "rb"))
		*action = rb;
	else if (ft_strequ(str, "rr"))
		*action = rr;
	else
		result = 0;
	return (result);
}

static int				str_to_rrx_move_action(char *str, t_move_action *action)
{
	int						result;

	result = 1;
	if (ft_strequ(str, "rra"))
		*action = rra;
	else if (ft_strequ(str, "rrb"))
		*action = rrb;
	else if (ft_strequ(str, "rrr"))
		*action = rrr;
	else
		result = 0;
	return (result);
}

static int				str_to_sx_move_action(char *str, t_move_action *action)
{
	int						result;

	result = 1;
	if (ft_strequ(str, "sa"))
		*action = sa;
	else if (ft_strequ(str, "sb"))
		*action = sb;
	else if (ft_strequ(str, "ss"))
		*action = ss;
	else
		result = 0;
	return (result);
}

static int				str_to_px_move_action(char *str, t_move_action *action)
{
	int						result;

	result = 1;
	if (ft_strequ(str, "pa"))
		*action = pa;
	else if (ft_strequ(str, "pb"))
		*action = pb;
	else
		result = 0;
	return (result);
}

t_validation_result		str_to_move_action(char *str, t_move_action *action)
{
	t_validation_result		result;

	result = ok;
	if (str_to_rx_move_action(str, action))
		;
	else if (str_to_rrx_move_action(str, action))
		;
	else if (str_to_sx_move_action(str, action))
		;
	else if (str_to_px_move_action(str, action))
		;
	else
		result = error;
	return (result);
}
