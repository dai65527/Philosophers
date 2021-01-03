/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 09:29:56 by dnakano           #+#    #+#             */
/*   Updated: 2021/01/03 14:33:30 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <pthread.h>
#include "philo_one.h"

static int	finish_eating(t_philo *philo)
{
	int		flgend;

	flgend = 0;
	pthread_mutex_lock(&g_mutex_fork);
	g_fork[philo->index] = 0;
	g_fork[(philo->index + 1) % philo->n_philo] = 0;
	pthread_mutex_unlock(&g_mutex_fork);
	if (philo->n_to_eat > 0)
	{
		philo->n_to_eat--;
		if (philo->n_to_eat == 0)
		{
			pthread_mutex_lock(&g_mutex_n_finished);
			g_n_finished++;
			if (g_n_finished == philo->n_philo)
			{
				pthread_mutex_lock(&g_mutex_flgend);
				g_flgend = 1;
				pthread_mutex_unlock(&g_mutex_flgend);
				flgend = 1;
			}
			pthread_mutex_unlock(&g_mutex_n_finished);
		}
	}
	return (flgend);
}

static int	fork_is_available(t_philo *philo)
{
	if (!g_fork[philo->index] && !g_fork[(philo->index + 1) % philo->n_philo]
		&& (g_fork_rsvd_by[philo->index] == philo->index
			|| g_fork_rsvd_by[philo->index] == -1)
		&& (g_fork_rsvd_by[(philo->index + 1) % philo->n_philo] == philo->index
			|| g_fork_rsvd_by[(philo->index + 1) % philo->n_philo] == -1))
		return (1);
	if (g_fork_rsvd_by[philo->index] == -1)
		g_fork_rsvd_by[philo->index] = philo->index;
	if (g_fork_rsvd_by[(philo->index + 1) % philo->n_philo] == -1)
		g_fork_rsvd_by[(philo->index + 1) % philo->n_philo] = philo->index;
	return (0);
}

static int	get_fork(t_philo *philo)
{
	long	time_taken_fork;

	pthread_mutex_lock(&g_mutex_fork);
	if (fork_is_available(philo))
	{
		time_taken_fork = philo_gettime();
		g_fork[philo->index] = 1;
		philo_putstatus(philo->index, time_taken_fork, PHILO_S_TAKENFORK);
		g_fork_rsvd_by[philo->index] = -1;
		g_fork[philo->index % philo->n_philo + 1] = 1;
		philo_putstatus(philo->index, time_taken_fork, PHILO_S_TAKENFORK);
		g_fork_rsvd_by[(philo->index + 1) % philo->n_philo] = -1;
		pthread_mutex_unlock(&g_mutex_fork);
		return (1);
	}
	pthread_mutex_unlock(&g_mutex_fork);
	return (0);
}

long		philo_eat(t_philo *philo, long time_start_eating)
{
	while (!get_fork(philo))
	{
		if (philo_check_dead(philo, time_start_eating))
			return (-1);
		usleep(PHILO_WHILE_INTERVAL_USEC);
	}
	if ((time_start_eating = philo_gettime()) < 0)
		return (-1);
	philo_putstatus(philo->index, time_start_eating, PHILO_S_EATING);
	while (!philo_has_finished(time_start_eating, philo->time_to_eat))
	{
		if (philo_check_dead(philo, time_start_eating))
			return (-1);
		usleep(PHILO_WHILE_INTERVAL_USEC);
	}
	if (finish_eating(philo) < 0)
		return (-1);
	return (time_start_eating);
}
