/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   est.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 18:43:01 by mkaraden          #+#    #+#             */
/*   Updated: 2023/02/24 13:03:13 by mkaraden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_est(void *rls)
{
	t_rules	*rules;

	rules = (t_rules *)rls;
	

	return NULL;
}


void *p_eat(void *philo)
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
	p_sleep(philo);
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
	p_think(philo);
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
	p_eat(philo);
	// usleep(100 * 10000);
	return NULL;
}