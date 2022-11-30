/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokhacha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 19:35:07 by sokhacha          #+#    #+#             */
/*   Updated: 2022/11/29 20:26:16 by sokhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h" 

int	error(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	if (ac > 6 || ac < 5)
		return (1);
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] == '-' || (av[i][j] != 32 &&
					!(av[i][j] >= '0' && av[i][j] <= '9')))
				return (1);
			j++;
		}
		if (ft_atoi(av[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	death_check(t_main *info)
{
	int			i;
	long long	time;
	int			count_eat_all_philos;

	count_eat_all_philos = 0;
	i = 0;
	while (i < info->number_of_philo)
	{		
		time = get_time();
		if (info->phillos[i].count_eat == info->number_of_times_each_p_must_eat)
		{
			count_eat_all_philos++;
			if (count_eat_all_philos == info->number_of_philo)
				return (2);
		}		
		if (time - info->phillos[i].eat_time > info->phillos[i].time_to_die)
		{
			printf("%llu philos %d died\n", time - info->phillos[i].eat_time,
				info->phillos[i].index);
			return (2);
		}		
		i++;
	}
	return (0);
}

void	death_check_checkin(char **av, t_main *data)
{
	int	i;

	i = 0;
	while (i < ft_atoi(av[1]))
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->forks);
	free(data->phillos);
	free(data->th);
	free(data);
}

void	mutex_init_fun(char **av, t_main *data)
{
	int	i;

	i = 0;
	while (i < ft_atoi(av[1]))
	{
		pthread_mutex_init(&data -> forks[i], NULL);
		i++;
	}
}
