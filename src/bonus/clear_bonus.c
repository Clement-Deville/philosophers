/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:51:23 by cdeville          #+#    #+#             */
/*   Updated: 2024/07/03 16:43:33 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

void	clean_init_error(t_philo_param *param)
{
	destroy_error(param);
	free(param->pid_tab);
	free(param->forks);
	free(param->philo_tab);
}
