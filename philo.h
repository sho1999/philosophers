/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 18:59:22 by smuramat          #+#    #+#             */
/*   Updated: 2022/09/03 13:25:46 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>
#include "libft/libft.h"

# define STDERR 2


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
	pthread_mutex_t	mutex;
	long long		last_eat_time;
	long long		first_time;
}					t_philo;

int	ps_error(void);
size_t take_fork(size_t num_philo, t_philo *philo);
long long eating(size_t num_philo, t_philo *philo);
void sleeping(size_t num_philo, t_philo *philo);
void thinking(size_t num_philo, t_philo *philo);
void check_die(size_t num_philo, t_philo *philo, long long last_time);
void init_philo(int argc, char **argv, t_philo *p);
long long	timestamp_ms(void);
size_t cnv_ms(size_t ms);
void free_and_exit(t_philo *p);
