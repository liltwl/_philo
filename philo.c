/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaouil <otaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 04:09:13 by otaouil           #+#    #+#             */
/*   Updated: 2021/12/14 10:00:32 by otaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_fork(t_all *data, t_philo *philo)
{
	t_fork	*fork;
	t_fork	*fork1;

	fork = get_fork(data, philo->id);
	if (fork->new_philo == -1)
		return ;
	if (philo->id < data->philo_num)
		fork1 = get_fork(data, philo->id + 1);
	else
		fork1 = get_fork(data, 1);
	pthread_mutex_unlock(&fork1->flock);
	philo->fork1 = 0;
	fork1->new_philo = -1;	
	pthread_mutex_unlock(&fork->flock);
	philo->fork = 0;
	fork->new_philo = -1;
	return ;
}

void	*ft_start(void *arg)
{
	t_philo	*philo;
	t_all	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	while (data->i)
	{
		ft_checkstatus(philo, data);
		if (data->i)
			ft_statu_up(philo, philo->data);
	}
	return (NULL);
}

void	ft_philo(t_all *data)
{
	t_philo	*philo;
	int		err;

	philo = data->philo;
	while (philo)
	{
		if (data->philo_num == 1)
		{
			get_fork(data, philo->id)->new_philo = philo->id;
			philo->statu = 9;
			ft_print("has taken a fork", philo, 0, 1);
		}
		else if (philo->id % 2 != 0 && data->philo_num != philo->id)
			ft_philoinit(philo, data);
		else
			philo->statu = 0;
		philo->t0 = get_time_mls();
		philo->t_stop_eat = get_time_mls();
		philo = philo->next;
	}
	philo = data->philo;
	while (philo)
	{
		err = pthread_create(&philo->trd_id, NULL, &ft_start, philo);
		philo = philo->next;
		usleep(10);
	}
}

int	ft_chekph(t_all *data)
{
	t_philo *phi;

	usleep(60);
	phi = data->philo;
	while (phi)
	{
		if (phi && (get_time_mls() - phi->t_stop_eat) >= data->t_to_die && phi->statu != 1)
		{
			ft_print("died", phi, get_time_mls(), 1);
			data->i = 0;
			pthread_mutex_unlock(&data->lk);
			return (0);
		}
		phi = phi->next;
	}
	phi = data->philo;
	if (data->t_must_eat != -1)
	{
		while (phi)
		{
			if (phi->t_eat < data->t_must_eat)
				return (1);
			phi = phi->next;
		}
	}
	else
		return (1);
	data->i = 0;
	pthread_mutex_unlock(&data->lk);
	return (0);
}
int	main(int ac, char **av)
{
	t_all	data1;
	int		i;

	i = 0;
	if (ft_init(ac, av, &data1) == -1)
		return (0);
	ft_addlst(&data1);
	ft_philo(&data1);
	//if (data1.t_must_eat != -1)
		while (ft_chekph(&data1));
	pthread_mutex_lock(&data1.lk);
	ft_freeall(&data1);
}
