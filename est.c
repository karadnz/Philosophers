/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   est.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 18:43:01 by mkaraden          #+#    #+#             */
/*   Updated: 2023/02/24 19:42:18 by mkaraden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_est(void *phil)
{
	t_philo	*philo;

	philo = (t_philo *)phil;
	if (philo->id % 2)
		usleep(15000);
	while(!(philo->rules->is_dead))
	{
		p_eat(philo);
		if (philo->rules->is_dead)
			break ;
		if (philo->rules->max_eat != -1 && philo->rules->all_ate)
			break ;
		if (philo->rules->max_eat != -1 && philo->eat_count >= philo->rules->max_eat)
			break ;
		p_print(philo->rules, philo->id, "is sleeping");
		u_sleep(philo->rules->time_sleep, philo->rules);
		p_print(philo->rules, philo->id, "is thinking");
	}
	
	return NULL;
}

void p_eat(t_philo *philo)
{
	t_rules	*rules;

	rules = philo->rules;
	pthread_mutex_lock(&(rules->forks[philo->lf_id]));
	p_print(philo->rules, philo->id, "has taken a fork");
	pthread_mutex_lock(&(rules->forks[philo->rf_id]));
	p_print(philo->rules, philo->id, "has taken a fork");
	pthread_mutex_lock(&(rules->meal_check));
	p_print(rules, philo->id, "is eating");
	philo->last_ate = timestamp();
	pthread_mutex_unlock(&(rules->meal_check));
	u_sleep(rules->time_eat, rules);
	(philo->eat_count)++;
	pthread_mutex_unlock(&(rules->forks[philo->lf_id]));
	pthread_mutex_unlock(&(rules->forks[philo->rf_id]));
}



void	check_is_dead(t_rules *rules, t_philo **philos)
{
	int	i;
	int	j;

	while(!(rules->all_ate))
	{
		
		i = 0;
		while (i < rules->philo_count && !(rules->is_dead))
		{
			
			pthread_mutex_lock(&(rules->meal_check));
			//printf("diff %lld  td: %d \n", time_diff(philos[i]->last_ate, timestamp()), rules->time_death);
			if (time_diff(philos[i]->last_ate, timestamp() ) > rules->time_death)
			{
				printf("HIT\n \n\n");
				p_print(rules, i, "died");
				rules->is_dead = 1;
				j = 0;
				while (j < rules->philo_count)
				{
					pthread_mutex_unlock(&(rules->forks[j]));
					j++;
				}
			}
			pthread_mutex_unlock(&(rules->meal_check));
			usleep(100);
			i++;
		}
		if (rules->is_dead)
			break;
		eat_check(rules, philos);
	}
}

void eat_check(t_rules *rules, t_philo **philos)
{
	int	i;

	i = 0;
	while (rules->max_eat != -1 && i < rules->philo_count && philos[i]->eat_count >= rules->max_eat)
		i++;
	if (i == rules->philo_count)
		rules->all_ate = 1;
	
}



