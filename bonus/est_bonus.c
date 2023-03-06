/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   est_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 13:51:39 by mkaraden          #+#    #+#             */
/*   Updated: 2023/03/06 15:56:07 by mkaraden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*ft_bonus_death(void *phil)
{
	t_philo	*philo;
	int		j;

	philo = (t_philo *)phil;
	while (1)
	{
		sem_wait(philo->rules->meal_check);
		if (time_diff(philo->last_ate, timestamp()) > philo->rules->time_death)
		{
			p_print(philo->rules, philo->id, "died");
			sem_post(philo->rules->meal_check);
			sem_post(philo->rules->stop);
			break ;
		}
		sem_post(philo->rules->meal_check);
		usleep(100);
		sem_wait(philo->rules->meal_check);
		if (philo->rules->max_eat != -1
			&& philo->eat_count >= philo->rules->max_eat)
		{
			sem_post(philo->rules->meal_check);
			sem_post(philo->rules->stop);
			break ;
		}
		sem_post(philo->rules->meal_check);
		usleep(100);
	}
	return (NULL);
}

void	*ft_est(void *phil)
{
	t_philo		*philo;
	pthread_t	death;

	philo = (t_philo *)phil;
	pthread_create(&death, NULL, ft_bonus_death, philo);
	pthread_detach(death);
	while (1)
	{
		p_eat(philo);
		/*if (philo->rules->max_eat != -1
			&& philo->eat_count >= philo->rules->max_eat)
			break ;*/
		p_print(philo->rules, philo->id, "is sleeping");
		u_sleep(philo->rules->time_sleep, philo->rules);
		p_print(philo->rules, philo->id, "is thinking");
	}
	return (NULL);
}

void	p_eat(t_philo *philo)
{
	t_rules	*rules;

	rules = philo->rules;
	sem_wait((rules->forks));
	p_print(philo->rules, philo->id, "has taken a fork");
	sem_wait((rules->forks));
	p_print(philo->rules, philo->id, "has taken a fork");
	sem_wait((rules->meal_check));
	p_print(rules, philo->id, "is eating");
	philo->last_ate = timestamp();
	sem_post((rules->meal_check));
	u_sleep(rules->time_eat, rules);
	(philo->eat_count)++;
	sem_post((rules->forks));
	sem_post((rules->forks));
}
