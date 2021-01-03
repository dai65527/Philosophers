/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 09:29:56 by dnakano           #+#    #+#             */
/*   Updated: 2021/01/02 09:46:14 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "philo_one.h"

static int	get_fork(t_philo *philo)
{
	
	philo_put_status();
}

int			philo_eat(t_philo *philo)
{
	int		ret;

	while (((ret = get_fork(philo)) == 0))
		;
	if (ret == -1)
		return (1);
	if (eat() != 0)
		return (1);
	return (0);
}
