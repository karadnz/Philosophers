/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 13:50:52 by mkaraden          #+#    #+#             */
/*   Updated: 2023/03/05 19:36:03 by mkaraden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_philo
{
	int					id;
	int					eat_count;
	int					lf_id;
	int					rf_id;
	long long			last_ate;
	struct s_rules		*rules;
	pid_t				pid;
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
	sem_t				*meal_check;
	sem_t				*forks;
	sem_t				*stop;
	sem_t				*writing;
	t_philo				**philos;

}						t_rules;

//****INIT*******//
void		init_rules(int argc, char **argv, t_rules *rules);
void		init_philos(t_rules *rules);
int			init_mutex(t_rules *rules);
int			is_valid_num(char *str);
int			is_args_valid(int argc, char **argv);
//****MAIN******//
void		p_exit(t_rules *rules, t_philo **philos);
//****UTILS****//
int			ft_atoi(const char *str);
long long	timestamp(void);
long long	time_diff(long long past, long long pres);
void		u_sleep(long long time, t_rules *rules);
void		p_print(t_rules *rules, int id, char *msg);
void		eat_check(t_rules *rules, t_philo **philos);
void		check_is_dead(t_rules *rules, t_philo **philos);
//****ERROR***//
//****EST****//
void		*ft_est(void *rls);
void		p_eat(t_philo *rls);
void		*p_sleep(void *philo);
void		*p_think(void *philo);
#endif