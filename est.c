/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   est.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 18:43:01 by mkaraden          #+#    #+#             */
/*   Updated: 2023/02/24 13:36:16 by mkaraden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_est(void *phil)
{
	t_philo	*philo;

	philo = (t_philo *)phil;

	while(!(philo->rules->is_dead))
	{
		p_eat(philo);
		if (philo->rules->is_dead)
			break ;
		if (philo->rules->max_eat != -1 && philo->rules->all_ate)
			break ;
		if (philo->rules->max_eat != -1 && philo->eat_count > philo->rules->max_eat)
			break ;
		p_print(philo->rules, philo->id, "is sleeping");
		u_sleep(philo->rules->time_sleep, philo->rules);
		p_print(philo->rules, philo->id, "is thinking");
	}
	
	return NULL;
}

void *p_eat(void *phil)
{
	t_rules	*rules;
	t_philo *philo;

	
	philo = (t_philo *)phil;
	rules = philo->rules;
	if (philo->eat_count >= philo->rules->max_eat)
		return NULL;
	long long in = timestamp();

	long long diff = time_diff(philo->rules->first_timestamp, in);
	printf("%lld : %d is eating \n", diff, philo->id);

	while (timestamp() - in < philo->rules->time_eat)
	{
		usleep(10);
	}
	philo->eat_count++;
	return NULL;
}

void *p_eat2(void *philo)
{
	t_philo *phil = (t_philo *)philo;
	if (phil->eat_count >= phil->rules->max_eat)
		return NULL;
	long long in = timestamp();

	long long diff = time_diff(phil->rules->first_timestamp, in);
	printf("%lld : %d is eating \n", diff, phil->id);

	while (timestamp() - in < phil->rules->time_eat)
	{
		usleep(10);
	}
	phil->eat_count++;
	return NULL;
}

void *p_sleep(void *philo)
{
	t_philo *phil = (t_philo *)philo;
	long long in = timestamp();

	long long diff = time_diff(phil->rules->first_timestamp, in);
	printf("%lld : %d is sleeping\n", diff, phil->id);
	
	while (timestamp() - in < phil->rules->time_sleep)
	{
		usleep(10);
	}
	// usleep(100 * 10000);
	return NULL;
}

void *p_think(void *philo)
{
	t_philo *phil = (t_philo *)philo;
	long long in = timestamp();

	long long diff = time_diff(phil->rules->first_timestamp, in);
	printf("%lld : %d is thinking \n\n", diff, phil->id);
	
	while (timestamp() - in < phil->rules->time_eat)
	{
		usleep(10);
	}
	// usleep(100 * 10000);
	return NULL;
}