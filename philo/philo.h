/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokhacha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 20:48:52 by sokhacha          #+#    #+#             */
/*   Updated: 2022/11/29 20:53:02 by sokhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <time.h>
# include <sys/time.h>

typedef struct s_rules
{
	long long		time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				index;
	long long		die_time;
	long long		eat_time;
	long long		sleep_time;
	int				must_die;
	int				count_eat;
	pthread_mutex_t	*right;
	pthread_mutex_t	*left;
}	t_rules;

typedef struct s_main
{
	pthread_t		*th;
	int				number_of_times_each_p_must_eat;
	int				number_of_philo;
	t_rules			*phillos;
	pthread_mutex_t	*forks;
}t_main;

long int		ft_atoi(char *str);
int				error(int ac, char **av);
void			philos(char **ak, t_main *data);
void			phillos_eat_proces(char **av, t_main *data);
void			insert_thread(char **av, t_main *data);
unsigned long	get_time(void);
void			my_sleep(int ms);
int				death_check(t_main *info);
void			death_check_checkin(char **av, t_main *data);
void			mutex_init_fun(char **av, t_main *data);
#endif
