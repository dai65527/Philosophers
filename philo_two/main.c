/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 12:57:20 by dnakano           #+#    #+#             */
/*   Updated: 2021/01/04 09:38:45 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <pthread.h>
#include "philo_two.h"

int		main(int argc, char **argv)
{
	long		i;
	long		n_philo;
	t_philo		*philo;
	pthread_t	*philo_pthread;

	if (philo_store_argv(argc, argv, &philo) < 0)
		return (1);
	n_philo = philo[0].n_philo;
	if (philo_init(&philo_pthread, n_philo) < 0)
		return (philo_free_ret(philo, NULL, 1));
	i = 0;
	while (i < n_philo)
	{
		pthread_create(&philo_pthread[i], NULL, philo_activity, &philo[i]);
		i++;
	}
	i = 0;
	while (i < n_philo)
		pthread_join(philo_pthread[i++], NULL);
	return (philo_free_ret(philo, philo_pthread, 1));
}
