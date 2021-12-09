/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaouil <otaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 03:53:47 by otaouil           #+#    #+#             */
/*   Updated: 2021/12/09 22:31:11 by otaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print(char *str, t_philo *philo, unsigned int i, int w)
{
	if (w != 7)
		pthread_mutex_lock(&philo->data->lock);
	if (w != 6 && w != 7)
	{
		ft_putnbr_fd(i - philo->t0, 1);
		write(1, " ", 1);
		ft_putnbr_fd((unsigned int)philo->id, 1);
		write(1, " ", 1);
	}
	write(1, str, strlen(str));
	write(1, "\n", 1);
	if (w == 7 || w == 6)
		exit(1);
	if (str[0] != 'd')
		pthread_mutex_unlock(&philo->data->lock);
}

unsigned int	get_time_mls(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	smart_sleep(unsigned int time, t_philo *philo, t_all *data)
{
	unsigned int	i;

	i = get_time_mls();
	while (data->i && get_time_mls() - i < time)
	{
		usleep(10);
		if (data->i && philo->statu != 1)
			is_philo_dead(philo, data);
	}
}

void	ft_freeall(t_all *data)
{
	t_fork	*fork;
	t_philo	*philo;

	while (data->philo)
	{
		philo = data->philo;
		data->philo = data->philo->next;
		pthread_detach(philo->trd_id);
		free (philo);
	}
	while (data->fork)
	{
		fork = data->fork;
		data->fork = data->fork->next;
		pthread_mutex_destroy(&fork->flock);
		free (fork);
	}
	pthread_mutex_destroy(&data->lock);
	pthread_mutex_destroy(&data->lk);
}

t_philo	*get_philo(t_all *data, int philo_id)
{
	t_philo	*philo;

	philo = data->philo;
	while (philo)
	{
		if (philo->id == philo_id)
			return (philo);
		philo = philo->next;
	}
	return (NULL);
}
