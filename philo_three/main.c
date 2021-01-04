/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 12:57:20 by dnakano           #+#    #+#             */
/*   Updated: 2021/01/04 21:51:13 by dnakano          ###   ########.fr       */
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
		exit(0);
	}
	else
		return (pid);
}

int				main(int argc, char **argv)
{
	long		i;
	long		n_philo;
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
	while (--i >= 0)
		waitpid(pid[i], NULL, 0);
	return (philo_free_ret(philo, pid, 0));
}
