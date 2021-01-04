/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 12:57:20 by dnakano           #+#    #+#             */
/*   Updated: 2021/01/04 23:42:55 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include "philo_three.h"

static pid_t	create_philo_process(t_philo *philo)
{
	pid_t	pid;

	if ((pid = fork()) < 0)
		return (-1);
	else if (pid == 0)
	{
		philo_activity(philo);
		return (-1);
	}
	else
		return (pid);
}

static int		wait_philo_process(pid_t *pid, long n_philo)
{
	long		i;
	int			status;

	i = 0;
	while (i < n_philo)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) == 1)
		{
			i = 0;
			while (i < n_philo)
				kill(pid[i++], SIGINT);
			return (1);
		}
		i++;
	}
	return (0);
}

int				main(int argc, char **argv)
{
	long		i;
	long		n_philo;
	int			ret;
	pid_t		*pid;
	t_philo		*philo;

	if (philo_store_argv(argc, argv, &philo) < 0)
		return (1);
	n_philo = philo[0].n_philo;
	if (philo_init(&pid, n_philo) < 0)
		return (philo_free_ret(philo, NULL, 1));
	i = 0;
	while (i < n_philo)
	{
		if ((pid[i] = create_philo_process(&philo[i])) < 0)
		{
			while (--i >= 0)
				kill(pid[i], SIGINT);
			return (philo_free_ret(philo, pid, 1));
		}
		i++;
	}
	ret = wait_philo_process(pid, n_philo);
	return (philo_free_ret(philo, pid, ret));
}
