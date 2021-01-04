/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 09:29:56 by dnakano           #+#    #+#             */
/*   Updated: 2021/01/04 21:01:37 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include "philo_three.h"

static int	finish_eating(t_philo *philo)
{
	if (philo->n_to_eat > 0)
	{
		philo->n_to_eat--;
		if (philo->n_to_eat == 0)
			return (1);
	}
	return (0);
}

void		*deadtimer(void *timerinfo)
{
	long		time_now;

	while ((time_now = philo_gettime()) >= 0 &&
		time_now - ((t_timerinfo *)timerinfo)->time_start_eating
			<= ((t_timerinfo *)timerinfo)->philo->time_to_die)
	{
		sem_wait(g_sem_flg_getfork);
		if (g_flg_getfork)
		{
			sem_post(g_sem_flg_getfork);
			return (NULL);
		}
		sem_post(g_sem_flg_getfork);
		usleep(PHILO_WHILE_INTERVAL_USEC / 10);
	}
	philo_putstatus(((t_timerinfo *)timerinfo)->philo->index,
											time_now, PHILO_S_DEAD);
	kill(0, SIGINT);
	return (NULL);
}

static void	create_deadtimerthread(t_philo *philo, long time_start_eating)
{
	static pthread_t	thread_deadtimer;
	static t_timerinfo	timerinfo;

	timerinfo.philo = philo;
	timerinfo.time_start_eating = time_start_eating;
	pthread_create(&thread_deadtimer, NULL, deadtimer, &timerinfo);
	pthread_detach(thread_deadtimer);
}

static long	get_fork(t_philo *philo, long time_start_eating)
{
	long		time_now;

	sem_wait(g_sem_fork_accs);
	g_flg_getfork = 0;
	create_deadtimerthread(philo, time_start_eating);
	sem_wait(g_sem_fork);
	if ((time_now = philo_gettime()) < 0)
		kill(0, SIGINT);
	philo_putstatus(philo->index, time_now, PHILO_S_TAKENFORK);
	sem_wait(g_sem_fork);
	sem_wait(g_sem_flg_getfork);
	g_flg_getfork = 1;
	sem_post(g_sem_flg_getfork);
	sem_post(g_sem_fork_accs);
	if ((time_now = philo_gettime()) < 0)
		kill(0, SIGINT);
	philo_putstatus(philo->index, time_now, PHILO_S_TAKENFORK);
	return (time_now);
}

long		philo_eat(t_philo *philo, long time_start_eating)
{
	if ((time_start_eating = get_fork(philo, time_start_eating)) < 0)
		return (-1);
	philo_putstatus(philo->index, time_start_eating, PHILO_S_EATING);
	while (!philo_has_finished(time_start_eating, philo->time_to_eat))
	{
		if (philo_check_dead(philo, time_start_eating))
		{
			sem_post(g_sem_fork);
			sem_post(g_sem_fork);
			return (-1);
		}
		usleep(PHILO_WHILE_INTERVAL_USEC);
	}
	sem_post(g_sem_fork);
	sem_post(g_sem_fork);
	if (finish_eating(philo))
		return (-1);
	return (time_start_eating);
}
