/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_puterr_and_return.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 18:22:12 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/22 18:37:03 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philo_utils.h"

/*
**	Function: philo_puterr_and_return
**
**	Put error message which consist of "Philosopher: " and str and return ret.
*/

int			philo_puterr_and_return(const char *str, int ret)
{
	char	buf[256];

	ft_strlcpy(buf, "Philosopher: ", sizeof(buf));
	ft_strlcat(buf, str, sizeof(buf));
	ft_strlcat(buf, "\n", sizeof(buf));
	write(1, buf, ft_strlen(buf));
	return (ret);
}
