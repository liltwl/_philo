/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaouil <otaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 16:03:14 by otaouil           #+#    #+#             */
/*   Updated: 2021/12/09 22:16:08 by otaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_all	t_all;

typedef struct s_fork
{
	int				philo;
	int				new_philo;
	pthread_mutex_t	flock;
	struct s_fork	*next;
}				t_fork;

typedef struct s_philo
{
	int				id;
	int				statu;
	pthread_t		trd_id;
	int				t_eat;
	unsigned int	t_stop_eat;
	int				fork;
	int				fork1;
	unsigned int	t0;
	struct s_philo	*next;
	t_all			*data;
}				t_philo;

typedef struct s_all
{
	int				philo_num;
	t_philo			*philo;
	t_fork			*fork;
	pthread_mutex_t	lock;
	pthread_mutex_t	lk;
	unsigned int	t_to_sleep;
	int				i;
	unsigned int	t_to_die;
	unsigned int	t_to_eat;
	int				t_must_eat;
}				t_all;

int				ft_putchar_fd(char c, int fd);
unsigned int	get_time_mls(void);
void			ft_close(int i, t_all *data);
int				ft_putnbr_fd(unsigned int n, int fd);
void			ft_print(char *str, t_philo *philo, unsigned int i, int w);
int				ft_atoi(const char *str);
t_philo			*ft_lstlast(t_philo *lst);
void			ft_lstadd_back(t_philo **alst, t_philo *new);
t_fork			*ft_lastfork(t_fork *lst);
void			ft_addfork_back(t_fork **alst, t_fork *new);
void			ft_philo_init(t_all *data, int *i, t_philo *philo);
void			ft_addlst(t_all *data);
int				ft_init(int ac, char **av, t_all *data);
t_philo			*get_philo(t_all *data, int philo_id);
t_fork			*get_fork(t_all *data, int id);
int				is_readyto_eat(t_all *data, t_philo *philo);
void			free_fork(t_all *data, t_philo *philo);
void			ft_statu_up(t_philo *philo, t_all *data);
void			is_philo_dead(t_philo *philo, t_all *data);
void			smart_sleep(unsigned int time, t_philo *philo, t_all *data);
void			ft_checkstatus(t_philo *philo, t_all *data);
void			*ft_start(void *arg);
void			ft_philoinit(t_philo *philo, t_all *data);
void			ft_philo(t_all *data);
void			ft_freeall(t_all *data);

#endif