/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 18:59:22 by smuramat          #+#    #+#             */
/*   Updated: 2022/09/07 21:11:58 by smuramat         ###   ########.fr       */
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

struct s_philo_pub;

typedef struct s_philo_personal
{
	long long		ideal_time;
	long long		last_eat_time;
	long long		first_time;
	size_t			id;
	pthread_t   th;
	struct s_philo_pub *pub; 			
}					t_p_philo;

typedef struct s_philo_pub
{
	size_t			num_philo;
	size_t			fork;
	size_t			time_die;
	size_t			time_eat;
	size_t			time_sleep;
	size_t			num_must_eat;
	size_t			total_num_eat;
	pthread_mutex_t	writing;
	pthread_mutex_t	*mutex;
	t_p_philo 	philo_personal[200];
}					t_philo;

int			ps_error(void);
void	take_fork(t_p_philo *p);
void	eating(t_p_philo *p);
void		sleeping(t_p_philo *philo);
void		thinking(t_p_philo *philo);
void	check_die(t_p_philo *p);
void		init_philo(int argc, char **argv, t_philo *p);
long long	timestamp_ms(void);
size_t		cnv_ms(size_t ms);
void		free_and_exit(t_philo *p);
void		ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(int nb, int fd);
void	one_philo(t_philo *p, size_t num_p);
void *ft_ins(void *p);
void	finalize(t_philo *p);

#endif