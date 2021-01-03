/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_store_argv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:34:55 by dnakano           #+#    #+#             */
/*   Updated: 2021/01/03 15:41:09 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "philo_utils.h"

/*
**	Sub function: arg_is_number
**
**	Check if argument string contains only digit charactor.
**	Returns 1 if true and 0 if not.
*/

static int	arg_is_number(char *arg)
{
	while (*arg)
	{
		if (!ft_isdigit(*arg))
			return (0);
		arg++;
	}
	return (1);
}

/*
**	Sub function: check_val
**
**	Check valiable of argc and argv.
**	Put error message and return 1 if any error found otherwise return 0.
*/

static int	check_val(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (philo_puterr_and_return("Invalid argument", 1));
	while (*(++argv))
	{
		if (!arg_is_number(*argv))
			return (philo_puterr_and_return("Invalid argument", 1));
	}
	return (0);
}

static void	convert_argv(char **argv, t_philo *philo, long n_philo,
																long n_to_eat)
{
	long	index;

	philo[0].index = 0;
	philo[0].n_philo = n_philo;
	philo[0].time_to_die = ft_atol(argv[2]);
	philo[0].time_to_eat = ft_atol(argv[3]);
	philo[0].time_to_sleep = ft_atol(argv[4]);
	philo[0].n_to_eat = n_to_eat;
	index = 1;
	while (index < n_philo)
	{
		memcpy(&philo[index], &philo[0], sizeof(t_philo));
		philo[index].index = index;
		index++;
	}
}

/*
**	Function: philo_store_argv
**
**	Check if command line arguments is valid and store them to philo and n.
**	If any invalid argument found or any error occured, put error message and
**	return -1. Otherwise, return 0.
**
**	List of command line arguments
**	  - argv[1]: number_of_philosophers
**	  - argv[2]: time_to_die	(ms)
**	  - argv[3]: time_to_eat	(ms)
**	  - argv[4]: time_to_sleep	(ms)
**	  - argv[5]: number_of_times_each_philosopher_must_eat (optional)
*/

int			philo_store_argv(int argc, char **argv, t_philo **philo)
{
	long	n_philo;
	long	n_to_eat;

	if (check_val(argc, argv))
		return (-1);
	if ((n_philo = ft_atol(argv[1])) < 2)
		return (philo_puterr_and_return("Invalid argument", -1));
	if (argc == 6 && (n_to_eat = ft_atol(argv[5])) < 1)
		return (philo_puterr_and_return("Invalid argument", -1));
	else if (argc != 6)
		n_to_eat = -1;
	if (!((*philo) = (t_philo *)malloc(sizeof(t_philo) * n_philo)))
		return (philo_puterr_and_return("Cannot allocate memory", -1));
	convert_argv(argv, *philo, n_philo, n_to_eat);
	return (0);
}
