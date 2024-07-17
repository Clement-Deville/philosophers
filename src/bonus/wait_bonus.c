/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:47:39 by cdeville          #+#    #+#             */
/*   Updated: 2024/07/17 11:31:34 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

int	kill_all_childs(t_philo_param *param)
{
	int	i;

	i = 0;
	sem_wait(param->sem_pid_tab);
	while (i < param->number_of_philosophers)
	{
		kill(param->pid_tab[i], SIGTERM);
		i++;
	}
	sem_post(param->sem_pid_tab);
	return (0);
}

int	check_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status) && WTERMSIG(status) != SIGTERM)
		return (-(WTERMSIG(status)));
	return (0);
}

void	print_error(int status)
{
	if (status < 0)
	{
		printf("CRITICAL ERROR: a child has been stopped cause of signal %s\n",
			strsignal(-status));
		return ;
	}
	else
	{
		printf("CRITICAL ERROR: a child has been encouter an error: %s\n",
			strerror(status));
		return ;
	}
}

int	wait_for_all(t_philo_param *param)
{
	int	i;
	int	status;

	i = 0;
	while (i < param->number_of_philosophers)
	{
		if (waitpid(0, &status, 0) == -1)
			return (perror(""), 1);
		status = check_status(status);
		if (status)
		{
			sem_wait(param->sem_print);
			kill_all_childs(param);
			print_error(status);
			sem_post(param->sem_print);
		}
		i++;
	}
	return (0);
}
