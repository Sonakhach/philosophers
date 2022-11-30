/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokhacha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 20:27:36 by sokhacha          #+#    #+#             */
/*   Updated: 2022/11/29 20:42:35 by sokhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	ft_atoi(char	*str)
{
	int		i;
	int		j;
	long	res;

	i = 0;
	res = 0;
	j = 1;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
			i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			j = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return (res * j);
}

void	my_sleep(int ms)
{
	struct timeval	now;
	struct timeval	start;

	gettimeofday(&start, 0);
	gettimeofday(&now, 0);
	while ((now.tv_sec - start.tv_sec) * 1000
		+ (now.tv_usec - start.tv_usec) / 1000 < ms)
	{
		usleep(50);
		gettimeofday(&now, 0);
	}
}

unsigned long	get_time(void)
{
	struct timeval		curent_time;
	unsigned long long	ml_sec;

	gettimeofday(&curent_time, NULL);
	ml_sec = curent_time.tv_sec * 1000 + curent_time.tv_usec / 1000;
	return (ml_sec);
}
