/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 13:12:44 by mkaraden          #+#    #+#             */
/*   Updated: 2023/02/23 17:08:54 by mkaraden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h> //*

typedef struct s_philo
{
	int			id;
	int			eat_count;
	int			lf_id;
	int			rf_id;
	long long	last_ate;
	struct s_rules		*rules;
	pthread_t	thread_id;


}				t_philo;

typedef struct s_rules
{
	int					philo_count;
	int					time_death;
	int					time_eat;
	int					time_sleep;
	int					max_eat;
	int					is_dead;
	int					all_ate;
	long long			first_timestamp;
	pthread_mutex_t		meal_check;
	pthread_mutex_t		forks[300];
	pthread_mutex_t		writing;
	t_philo				**philos;
}						t_rules;



//tmp

void *p_eat(void *philo);
void init_rules(int argc, char **argv, t_rules *rules);
void init_philos(t_rules *rules);
long long	timestamp(void);
long long	time_diff(long long past, long long pres);
void *p_sleep(void *philo);
void *p_think(void *philo);
int	ft_atoi(const char *str);


# endif
