/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_puterr_and_return.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 18:22:12 by dnakano           #+#    #+#             */
/*   Updated: 2021/01/02 09:28:49 by dnakano          ###   ########.fr       */
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

	ft_strlcpy(buf, "Philosophers: ", sizeof(buf));
	ft_strlcat(buf, str, sizeof(buf));
	ft_strlcat(buf, "\n", sizeof(buf));
	write(1, buf, ft_strlen(buf));
	return (ret);
}
