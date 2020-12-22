/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 12:57:20 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/22 19:16:28 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philo_one.h"

int		main(int argc, char **argv)
{
	long		n_philo;
	t_philo		*philo;

	if (philo_store_argv(argc, argv, &philo, &n_philo) < 0)
		return (1);
	return (0);
}
