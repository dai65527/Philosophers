/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_free_ret.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 13:20:46 by dnakano           #+#    #+#             */
/*   Updated: 2021/01/04 21:09:10 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "philo_three.h"

/*
**	Function: philo_free_ret
**
**	Free allocatated memory for philo, philo_thread and return value of ret.
*/

int			philo_free_ret(t_philo *philo, pid_t *pid, int ret)
{
	free(philo);
	free(pid);
	philo_sem_close();
	philo_sem_unlink();
	return (ret);
}
