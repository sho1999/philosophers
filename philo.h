/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 18:59:22 by smuramat          #+#    #+#             */
/*   Updated: 2022/09/08 12:32:22 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>

# define STDERR 2
# define END_ABNORMAL 1
# define END_NORMAL 0
# define P_FORK "has taken a fork\n"
# define P_EAT "is eating\n"
# define P_THINK "is thinking\n"
# define P_SLEEP "is sleeping\n"
# define P_DEAD "is died\n"
# define USAGE	"[usage]: ./philo <philos> <die> <eat> <sleep> (<must>)"
# define NOTE_NUM "Put more than 0 and less than or equal to int max"
# define MALLOC_ERR "An error has occurred near malloc"
# define PHILO_OVER "The number of philo should be less than 200"

typedef struct s_philo_data
{
	size_t			num_philo;
	size_t			fork;
	size_t			time_eat;
	size_t			time_sleep;
	size_t			num_must_eat;
	size_t			total_num_eat;
	size_t			time_die;
	size_t			*ideal_time;
	size_t			*last_eat_time;
	size_t			*start_time;
	pthread_mutex_t	mutex[200];
	pthread_mutex_t	writing;
}					t_philo;

int			philo_error(char *s);
void		take_fork(size_t num_philo, t_philo *philo);
void		eating(size_t num_p, t_philo *p);
void		sleeping(size_t num_philo, t_philo *philo);
void		thinking(size_t num_philo, t_philo *philo);
void		check_die(size_t num_p, t_philo *p);
void		init_philo(int argc, char **argv, t_philo *p);
size_t		timestamp_ms(void);
size_t		cnv_ms(size_t ms);
void		free_and_exit(t_philo *p);
void		ft_putstr_fd(char *s, int fd);
void		ft_putchar_fd(char c, int fd);
void		ft_putnbr_fd(int nb, int fd);
void		one_philo(t_philo *p, size_t num_p);
void		*ft_ins(void *p);
void		finalize(t_philo *p, size_t flag);
int			philo_atoi(char *str);

#endif