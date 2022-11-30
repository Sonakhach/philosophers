/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokhacha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 19:09:48 by sokhacha          #+#    #+#             */
/*   Updated: 2022/11/29 19:34:18 by sokhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(t_rules *data)
{
	long long	cur_time;

	cur_time = get_time();
	if (data->index % 2 == 0)
		my_sleep(data->time_to_eat);
	while (1)
	{
		pthread_mutex_lock(data ->right);
		printf("%llu, %d has taken a right fork\n", get_time() - cur_time,
			data->index);
		pthread_mutex_lock(data ->left);
		data->count_eat++;
		printf("%llu, %d has taken a left fork\n", get_time() - cur_time,
			data->index);
		printf("%llu, %d is eating\n", get_time() - cur_time, data->index);
		data->eat_time = get_time();
		my_sleep(data->time_to_eat);
		pthread_mutex_unlock(data->left);
		pthread_mutex_unlock(data->right);
		printf("%llu, %d is sleeping\n", get_time() - cur_time, data->index);
		my_sleep(data->time_to_sleep);
	}
}

void	philos(char **ak, t_main *data)
{
	int	i;
	int	y;

	y = ft_atoi(ak[1]);
	i = 0;
	while (i < y)
	{
		data->phillos[i].count_eat = 0;
		data->number_of_philo = ft_atoi(ak[1]);
		data->phillos[i].time_to_die = ft_atoi(ak[2]);
		data->phillos[i].time_to_eat = ft_atoi(ak[3]);
		data->phillos[i].time_to_sleep = ft_atoi(ak[4]);
		data ->phillos[i].index = i + 1;
		data ->phillos[i].eat_time = get_time();
		if (ak[5])
			data->number_of_times_each_p_must_eat = ft_atoi(ak[5]);
		else
			data->number_of_times_each_p_must_eat = -1;
		i++;
	}
}

void	phillos_eat_proces(char **av, t_main *data)
{
	int	i;
	int	j;

	j = ft_atoi(av[1]);
	i = 0;
	while (i < j)
	{
		if (i == 0)
			data -> phillos[i].right = &data -> forks[j - 1];
		else
			data -> phillos[i].right = &data -> forks[i - 1];
		data -> phillos[i].left = &data -> forks[i];
		i++;
	}
}

void	insert_thread(char **av, t_main *data)
{			
	int	i;
	int	y;

	i = 0;
	y = ft_atoi(av[1]);
	data->th = (pthread_t *)malloc(sizeof(pthread_t) * y);
	while (i < y)
	{
		if (pthread_create(data->th + i, NULL, (void *)routine,
				&(data -> phillos[i])) != 0)
			perror("failed to create thread");
		i++;
	}
}

int	main(int ac, char **av)
{
	t_main	*data;	
	int		tmp;

	if (error(ac, av) == 1)
	{
		write(1, "error\n", 6);
		return (1);
	}
	data = malloc(sizeof(t_main));
	data->phillos = malloc(sizeof(t_rules) * ft_atoi(av[1]));
	data -> forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(av[1]));
	philos(av, data);
	mutex_init_fun(av, data);
	phillos_eat_proces(av, data);
	insert_thread(av, data);
	while (1)
	{
		tmp = death_check(data);
		if (tmp == 2)
		{
			death_check_checkin(av, data);
			return (-1);
		}
	}
	return (0);
}
