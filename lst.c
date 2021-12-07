/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaouil <otaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 03:49:00 by otaouil           #+#    #+#             */
/*   Updated: 2021/12/07 03:50:45 by otaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*ft_lstlast(t_philo *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back(t_philo **alst, t_philo *new)
{
	t_philo	*last;

	if (alst)
	{
		if (*alst)
		{
			last = ft_lstlast(*alst);
			last->next = new;
		}
		else
			*alst = new;
	}
}

t_fork	*ft_lastfork(t_fork *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	ft_addfork_back(t_fork **alst, t_fork *new)
{
	t_fork	*last;

	if (alst)
	{
		if (*alst)
		{
			last = ft_lastfork(*alst);
			last->next = new;
		}
		else
			*alst = new;
	}
}

t_fork	*get_fork(t_all *data, int id)
{
	t_fork	*fork;

	fork = data->fork;
	while (fork)
	{
		if (fork->philo == id)
			return (fork);
		fork = fork->next;
	}
	return (NULL);
}
