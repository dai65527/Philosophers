/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_activity.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 12:50:21 by dnakano           #+#    #+#             */
/*   Updated: 2021/01/03 10:43:25 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <pthread.h>
#include "philo_one.h"
#include <stdio.h>  //

static int	get_digit(long num)
{
	int		digit;

	digit = (num < 0) ? 2 : 1;
	while (num >= 10L)
	{
		num /= 10L;
		digit++;
	}
	return (digit);
}

static void	cat_number(char *buf, long num)
{
	int		digit;

	while (*buf)
		buf++;
	digit = get_digit(num);
	buf[digit] = '\0';
	while (digit > 0)
	{
		buf[digit - 1] = (char)(num % 10L) + '0';
		num /= 10;
		digit--;
	}
}

void		philo_putstatus(long philo_index, long time_ms, int philo_status)
{
	char		buf[256];

	buf[0] = '\0';
	cat_number(buf, time_ms);
	ft_strlcat(buf, " ", sizeof(buf));
	cat_number(buf, philo_index);
	if (philo_status == PHILO_STATUS_TAKENFORK)
		ft_strlcat(buf, " has taken a fork\n", sizeof(buf));
	else if (philo_status == PHILO_STATUS_EATING)
		ft_strlcat(buf, " is eating\n", sizeof(buf));
	else if (philo_status == PHILO_STATUS_SLEEPING)
		ft_strlcat(buf, " is sleeping\n", sizeof(buf));
	else if (philo_status == PHILO_STATUS_THINKING)
		ft_strlcat(buf, " is thinking\n", sizeof(buf));
	else if (philo_status == PHILO_STATUS_DEAD)
		ft_strlcat(buf, " died\n", sizeof(buf));
	else
		ft_strlcat(buf, " is in undefined status\n", sizeof(buf));
	pthread_mutex_lock(&g_mutex_write);
	write(1, buf, ft_strlen(buf));
	pthread_mutex_unlock(&g_mutex_write);
}

static int	finish_eating(t_philo *philo)
{
	int		flgend;

	flgend = 0;
	pthread_mutex_lock(&g_mutex_fork);
	g_fork[philo->index] = 0;
	g_fork[philo->index % philo->n_philo + 1] = 0;
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
	pthread_mutex_unlock(&g_mutex_fork);
	return (flgend);
}

static int	get_fork(t_philo *philo)
{
	long	time_taken_fork;

	pthread_mutex_lock(&g_mutex_fork);
	if (!g_fork[philo->index] && !g_fork[philo->index % philo->n_philo + 1])
	{
		time_taken_fork = philo_gettime();
		g_fork[philo->index] = 1;
		philo_putstatus(philo->index, time_taken_fork, PHILO_STATUS_TAKENFORK);
		g_fork[philo->index % philo->n_philo + 1] = 1;
		philo_putstatus(philo->index, time_taken_fork, PHILO_STATUS_TAKENFORK);
		pthread_mutex_unlock(&g_mutex_fork);
		return (1);
	}
	pthread_mutex_unlock(&g_mutex_fork);
	return (0);
}

int			philo_check_dead(t_philo *philo, long time_start_eating)
{
	long	time_now;

	pthread_mutex_lock(&g_mutex_flgend);
	if (g_flgend)
	{
		pthread_mutex_unlock(&g_mutex_flgend);
		return (1);
	}
	if ((time_now = philo_gettime()) >= 0 &&
			time_now - time_start_eating > philo->time_to_die)
	{
		g_flgend = 1;
		pthread_mutex_unlock(&g_mutex_flgend);
		philo_putstatus(philo->index, time_now, PHILO_STATUS_DEAD);
	}
	pthread_mutex_unlock(&g_mutex_flgend);
	return (0);
}

int			has_finished(long time_start, long time_to_do)
{
	long	time_now;

	if ((time_now = philo_gettime()) < 0)
		return (1);
	if (time_now - time_start >= time_to_do)
		return (1);
	return (0);
}

void		*philo_activity(void *philo_arg)
{
	t_philo	*philo;
	long	time_start_eating;
	long	time_start_sleeping;
	long	time_start_thinking;

	philo = (t_philo *)philo_arg;
	if ((time_start_eating = philo_gettime()) < 0)
		return (NULL);
	if (philo->index % 2)
		usleep(200);
	while (1)
	{
		while (!get_fork(philo))
		{
			if (philo_check_dead(philo, time_start_eating))
				return (NULL);
			usleep(PHILO_WHILE_INTERVAL_USEC);
		}
		if ((time_start_eating = philo_gettime()) < 0)
			return (NULL);
		philo_putstatus(philo->index, time_start_eating, PHILO_STATUS_EATING);
		while (!has_finished(time_start_eating, philo->time_to_eat))
		{
			if (philo_check_dead(philo, time_start_eating))
				return (NULL);
			usleep(PHILO_WHILE_INTERVAL_USEC);
		}
		if (finish_eating(philo))
			return (NULL);
		if ((time_start_sleeping = philo_gettime()) < 0)
			return (NULL);
		philo_putstatus(philo->index, time_start_sleeping, PHILO_STATUS_SLEEPING);
		while (!has_finished(time_start_sleeping, philo->time_to_sleep))
		{
			if (philo_check_dead(philo, time_start_eating))
				return (NULL);
			usleep(PHILO_WHILE_INTERVAL_USEC);
		}
		if ((time_start_thinking = philo_gettime()) < 0)
			return (NULL);
		philo_putstatus(philo->index, time_start_thinking, PHILO_STATUS_THINKING);
	}
	return (NULL);
}
