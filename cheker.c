/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cheker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaouil <otaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 03:58:38 by otaouil           #+#    #+#             */
/*   Updated: 2021/12/14 09:57:49 by otaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_readyto_eat(t_all *data, t_philo *philo)
{
	t_fork	*fork;
	t_fork	*fork1;

	fork = get_fork(data, philo->id);
	if (philo->id == data->philo_num)
		fork1 = get_fork(data, 1);
	else
		fork1 = get_fork(data, philo->id + 1);
	pthread_mutex_lock(&fork->flock);
	if (fork->new_philo == -1 && !philo->fork)
	{
		philo->fork = 1;
		ft_print("has taken a fork", philo, get_time_mls(), 1);
		fork->new_philo = philo->id;
	}
	/*else
		pthread_mutex_unlock(&fork->flock);*/
	pthread_mutex_lock(&fork1->flock);
	if (fork1->new_philo == -1 && !philo->fork1)
	{
		ft_print("has taken a fork", philo, get_time_mls(), 1);
		philo->fork1 = 1;
		fork1->new_philo = philo->id;
	}
	/*else
		pthread_mutex_unlock(&fork1->flock);*/
	return (philo->fork1 && philo->fork);
}

void	ft_statu_up(t_philo *philo, t_all *data)
{
	if (philo->statu == 0 || philo->statu == 3)
		while (data->i && philo->statu != 1)
			philo->statu = is_readyto_eat(data, philo);
	else if (philo->statu == 1)
	{	
		free_fork(data, philo);
		philo->t_eat++;
		philo->statu = 2;
	}
	else if (philo->statu == 2)
		philo->statu = 3;
}

void	ft_checkstatus(t_philo *philo, t_all *data)
{
	
	if (philo->statu == 1)
	{
		philo->t_stop_eat = get_time_mls();
		ft_print("is eating", philo, get_time_mls(), 1);
		smart_sleep(philo->data->t_to_eat, data);
	}
	else if (philo->statu == 2)
	{
		ft_print("is sleeping", philo, get_time_mls(), 1);
		smart_sleep(philo->data->t_to_sleep, data);
	}
	else if (philo->statu == 3)
		ft_print("is thinking", philo, get_time_mls(), 1);
}

void	is_philo_dead(t_philo *philo, t_all *data)
{
	t_philo	*phi;

	phi = data->philo;
	if (philo && (get_time_mls() - philo->t_stop_eat) >= data->t_to_die)
	{
		ft_print("died", philo, get_time_mls(), 1);
		data->i = 0;
		pthread_mutex_unlock(&data->lk);
	}	
}
