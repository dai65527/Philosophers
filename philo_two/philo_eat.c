/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 09:29:56 by dnakano           #+#    #+#             */
/*   Updated: 2021/01/04 10:18:33 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <pthread.h>
#include "philo_two.h"

static int	finish_eating(t_philo *philo)
{
	int		flgend;

	flgend = 0;
	if (philo->n_to_eat > 0)
	{
		philo->n_to_eat--;
		if (philo->n_to_eat == 0)
		{
			sem_wait(g_sem_n_finished);
			g_n_finished++;
			if (g_n_finished == philo->n_philo)
			{
				sem_wait(g_sem_flgend);
				g_flgend = 1;
				sem_post(g_sem_flgend);
				flgend = 1;
			}
			sem_post(g_sem_n_finished);
		}
	}
	return (flgend);
}

void		*deadtimer(void *timerinfo)
{
	int			flgend;
	long		philo_index;
	long		time_now;
	long		time_to_die;

	philo_index = ((t_timerinfo *)timerinfo)->philo->index;
	time_to_die = ((t_timerinfo *)timerinfo)->philo->time_to_die;
	while ((time_now = philo_gettime()) >= 0 &&
		time_now - ((t_timerinfo *)timerinfo)->time_start_eating < time_to_die)
	{
		sem_wait(g_sem_flg_getfork);
		sem_wait(g_sem_flgend);
		flgend = g_flg_getfork || g_flgend;
		sem_post(g_sem_flgend);
		sem_post(g_sem_flg_getfork);
		if (flgend)
			return (NULL);
		usleep(PHILO_WHILE_INTERVAL_USEC);
	}
	sem_wait(g_sem_flgend);
	if (!g_flgend)
		philo_putstatus(philo_index, time_now, PHILO_S_DEAD);
	g_flgend = 1;
	sem_post(g_sem_flgend);
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
	if (philo_check_dead(philo, 0))
		return (sem_post(g_sem_fork_accs) - 1);
	g_flg_getfork = 0;
	create_deadtimerthread(philo, time_start_eating);
	sem_wait(g_sem_fork);
	if ((time_now = philo_gettime()) < 0 || philo_check_dead(philo, 0))
		return (sem_post(g_sem_fork_accs) - 1);
	philo_putstatus(philo->index, time_now, PHILO_S_TAKENFORK);
	sem_wait(g_sem_fork);
	sem_wait(g_sem_flg_getfork);
	g_flg_getfork = 1;
	sem_post(g_sem_flg_getfork);
	if ((time_now = philo_gettime()) < 0 || philo_check_dead(philo, 0))
		return (sem_post(g_sem_fork_accs) - 1);
	sem_post(g_sem_fork_accs);
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
			return (-1);
		usleep(PHILO_WHILE_INTERVAL_USEC);
	}
	sem_post(g_sem_fork);
	sem_post(g_sem_fork);
	if (finish_eating(philo) < 0)
		return (-1);
	return (time_start_eating);
}
