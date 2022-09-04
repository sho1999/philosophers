/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 18:59:22 by smuramat          #+#    #+#             */
/*   Updated: 2022/09/04 15:39:51 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include "libft/libft.h"

# define STDERR 2
# define P_FORK "has taken a fork\n"
# define P_EAT "is eating\n"
# define P_THINK "is thinking\n"
# define P_SLEEP "is sleeping\n"
# define P_DEAD "is died\n"



typedef struct s_philo_data
{
	size_t			num_philo;
	size_t			num_philo2;
	size_t			fork;
	size_t			time_die;
	size_t			time_eat;
	size_t			time_sleep;
	size_t			num_must_eat;
	size_t			total_num_eat;
	pthread_mutex_t	mutex[200];
	pthread_mutex_t	writing;
	long long		last_eat_time;
	long long		first_time;
}					t_philo;

int			ps_error(void);
void		take_fork(size_t num_philo, t_philo *philo);
long long	eating(size_t num_philo, t_philo *philo);
void		sleeping(size_t num_philo, t_philo *philo);
void		thinking(size_t num_philo, t_philo *philo);
int	check_die(size_t num_p, t_philo *p, long long last_t);
void		init_philo(int argc, char **argv, t_philo *p);
long long	timestamp_ms(void);
size_t		cnv_ms(size_t ms);
void		free_and_exit(t_philo *p);
void		ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(int nb, int fd);

#endif