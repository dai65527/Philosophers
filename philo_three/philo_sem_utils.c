/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sem_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 21:51:03 by dnakano           #+#    #+#             */
/*   Updated: 2021/01/04 21:06:37 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <semaphore.h>
#include <stddef.h>
#include "philo_three.h"

void		philo_sem_unlink(void)
{
	sem_unlink(SEM_FORK);
	sem_unlink(SEM_FORK_ACCS);
	sem_unlink(SEM_FLG_GETFORK);
	sem_unlink(SEM_WRITE);
}

void		philo_sem_close(void)
{
	if (g_sem_fork)
		sem_close(g_sem_fork);
	if (g_sem_fork_accs)
		sem_close(g_sem_fork_accs);
	if (g_sem_flg_getfork)
		sem_close(g_sem_flg_getfork);
	if (g_sem_write)
		sem_close(g_sem_write);
}

int			philo_sem_open(long n_philo)
{
	philo_sem_unlink();
	g_sem_fork = NULL;
	g_sem_fork_accs = NULL;
	g_sem_flg_getfork = NULL;
	g_sem_write = NULL;
	if ((g_sem_fork = sem_open(SEM_FORK, O_CREAT, 0777, n_philo)) == SEM_FAILED
		|| (g_sem_fork_accs = sem_open(SEM_FORK_ACCS, O_CREAT, 0777, 1))
																== SEM_FAILED
		|| (g_sem_write = sem_open(SEM_WRITE, O_CREAT, 0777, 1)) == SEM_FAILED
		|| (g_sem_flg_getfork = sem_open(SEM_FLG_GETFORK, O_CREAT, 0777, 1))
																== SEM_FAILED)
	{
		philo_sem_close();
		philo_sem_unlink();
		return (-1);
	}
	return (0);
}
