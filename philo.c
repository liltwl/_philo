/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaouil <otaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 04:09:13 by otaouil           #+#    #+#             */
/*   Updated: 2021/12/09 22:54:54 by otaouil          ###   ########.fr       */
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
	if (fork->new_philo != -1 && fork1->new_philo != -1)
	{
		philo->fork = 0;
		philo->fork1 = 0;
		fork->new_philo = -1;
		fork1->new_philo = -1;
		return ;
	}
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
		{
			is_philo_dead(philo, philo->data);
			ft_statu_up(philo, philo->data);
		}
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
		usleep(20);
		if (data->philo_num == 1)
		{
			get_fork(data, philo->id)->new_philo = philo->id;
			philo->statu = 0;
			ft_print("has taken a fork", philo, 0, 1);
		}
		else if (philo->id % 2 != 0 && data->philo_num != philo->id)
			ft_philoinit(philo, data);
		else
			philo->statu = 0;
			ft_print("can't create thread", philo, 0, 1);
		philo->t0 = get_time_mls();
		philo->t_stop_eat = get_time_mls();
		err = pthread_create(&philo->trd_id, NULL, &ft_start, philo);
		if (err != 0)
			ft_print("can't create thread", NULL, 0, 6);
		philo = philo->next;
	}
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
	pthread_mutex_lock(&data1.lk);
	ft_freeall(&data1);
}
