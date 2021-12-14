/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaouil <otaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 03:50:11 by otaouil           #+#    #+#             */
/*   Updated: 2021/12/14 09:07:55 by otaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_philo_init(t_all *data, int *i, t_philo *philo)
{
	philo = (t_philo *)malloc(sizeof(*philo));
	philo->id = *i;
	philo->statu = 0;
	philo->trd_id = NULL;
	philo->t_eat = 0;
	philo->data = data;
	philo->fork = 0;
	philo->fork1 = 0;
	philo->t0 = 0;
	philo->t_stop_eat = get_time_mls();
	philo->next = NULL;
	ft_lstadd_back(&data->philo, philo);
	(*i)++;
}

void	ft_addlst(t_all *data)
{
	t_philo	*philo;
	t_fork	*fork;
	int		i;

	i = 1;
	philo = NULL;
	while (i <= data->philo_num)
		ft_philo_init(data, &i, philo);
	i = 1;
	while (i <= data->philo_num)
	{
		fork = (t_fork *)malloc(sizeof(*fork));
		fork->philo = i++;
		fork->new_philo = -1;
		fork->next = NULL;
		if (pthread_mutex_init(&fork->flock, NULL) != 0)
			ft_print("error :\nmutex init failed", NULL, 0, 6);
		ft_addfork_back(&data->fork, fork);
	}
	if (pthread_mutex_init(&data->lock, NULL) != 0)
		ft_print("error :\nmutex init failed", NULL, 0, 6);
}

int	ft_init(int ac, char **av, t_all *data)
{
	data->fork = NULL;
	data->philo = NULL;
	if (ac < 5 || ac > 6)
		return (-1);
	data->philo_num = ft_atoi(av[1]);
	if (data->philo_num < 1)
		ft_print("error : Invalid arguments", NULL, 0, 7);
	data->t_to_die = ft_atoi(av[2]);
	data->t_to_eat = ft_atoi(av[3]);
	data->t_to_sleep = ft_atoi(av[4]);
	data->i = 1;
	if (pthread_mutex_init(&data->lk, NULL) != 0)
		ft_print("error :\nmutex init failed", NULL, 0, 6);
	pthread_mutex_lock(&data->lk);
	if (av[5])
		data->t_must_eat = ft_atoi(av[5]);
	else
		data->t_must_eat = -1;
	return (0);
}

void	ft_philoinit(t_philo *philo, t_all *data)
{
	t_fork	*fork;

	fork = get_fork(data, philo->id);
	fork->new_philo = philo->id;
	pthread_mutex_lock(&fork->flock);
	fork = get_fork(data, philo->id + 1);
	fork->new_philo = philo->id;
	pthread_mutex_lock(&fork->flock);
	philo->statu = 1;
	philo->fork = 1;
	philo->fork1 = 1;
	philo->t_eat++;
	ft_print("has taken a fork", philo, 0, 1);
	ft_print("has taken a fork", philo, 0, 1);
}
