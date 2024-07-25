/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_arg_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:08:52 by cdeville          #+#    #+#             */
/*   Updated: 2024/07/25 18:15:45 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

static int	ft_isspace(int c)
{
	if ((c >= 8 && c <= 13) || c == 32)
		return (1);
	return (0);
}

static int	ft_isnum(int c)
{
	if ((c >= 48 && c <= 57))
		return (1);
	return (0);
}

t_bool	is_pos_int(char *arg)
{
	int	i;

	i = 0;
	while (ft_isspace(arg[i]))
		i++;
	if (arg[i] == '-')
		return (FALSE);
	if (arg[i] == '+')
		i++;
	if (ft_isnum(arg[i]) == FALSE)
		return (FALSE);
	while (ft_isnum(arg[i]))
	{
		i++;
	}
	return (TRUE);
}

int	number_size(char *number)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (ft_isspace(number[i]))
		i++;
	if (number[i] == '+')
		i++;
	while (number[i] == '0')
		i++;
	if (!number[i])
		return (1);
	while (ft_isnum(number[i]))
	{
		i++;
		size++;
	}
	return (size);
}

t_bool	is_valid_parameters(int argc, char *argv[])
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (is_pos_int(argv[i]) == FALSE)
			return (ft_putstr_fd("Error: Positive int needed\n", 2), FALSE);
		i++;
	}
	if (number_size(argv[1]) >= 5)
	{
		ft_putstr_fd("Error: max number of philo is set at 9999\n", 2);
		return (FALSE);
	}
	if (number_size(argv[2]) >= 7
		|| number_size(argv[3]) >= 7
		|| number_size(argv[4]) >= 7)
		return (ft_putstr_fd("Error: max time is set at 999999\n", 2)
			, FALSE);
	if (argc == 6 && number_size(argv[5]) >= 10)
	{
		ft_putstr_fd("Error: max of max eat is 999999999\n", 2);
		return (FALSE);
	}
	return (TRUE);
}
