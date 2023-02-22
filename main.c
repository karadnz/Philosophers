/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 13:12:34 by mkaraden          #+#    #+#             */
/*   Updated: 2023/02/22 16:08:28 by mkaraden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void init_philo(t_philo *philo, int i);

long long st = 0;

int main()
{
	t_rules *rules = (t_rules *)malloc(sizeof(t_rules));
	init_rules(rules);

	st = timestamp();

	for (int i = 0; i < 10; i++) // yeme sayisi
	{
		for (int j = 0; j < rules->philo_count; j++)
		{
			if ((i + j) % 2 == 0)
			{
				pthread_create(&(rules->philos[j]->thread_id), NULL, eat, rules->philos[j]);
			}
			else
				pthread_create(&(rules->philos[j]->thread_id), NULL, p_sleep, rules->philos[j]);
			
		}
		
		
		for (int j = 0; j < rules->philo_count; j += 2)
		{
			pthread_join(rules->philos[j]->thread_id, NULL);
		}

		printf("\n");

	
	}
}

void *eat(void *philo)
{
	t_philo *phil = (t_philo *)philo;

	long long diff = time_diff(st, timestamp());
	printf("%lld : %d is eating \n", diff , phil->id);
	usleep(100 * 10000);
	return NULL;
}

void *p_sleep(void *philo)
{
	t_philo *phil = (t_philo *)philo;

	long long diff = time_diff(st, timestamp());
	printf("%lld : %d is sleeping \n", diff , phil->id);
	usleep(100 * 10000);
	return NULL;
}

void init_rules(t_rules *rules)
{
	rules->philo_count = 10;
	rules->time_death = 100;
	rules->time_eat = 10;
	rules->time_sleep = 10;
	rules->eat_count = 10;
	rules->first_timestamp = timestamp();
	// rules->is_dead = 0;
	// rules->all_Ate = 0;

	rules->philos = (t_philo **)malloc(sizeof(t_philo *) * rules->philo_count);
	init_philos(rules);
}
void init_philos(t_rules *rules)
{
	int i;

	i = 0;
	while (i < rules->philo_count)
	{
		rules->philos[i] = (t_philo *)malloc(sizeof(t_philo));
		rules->philos[i]->id = i;
		rules->philos[i]->lf_id = i;
		rules->philos[i]->rf_id = (i + 1) % rules->philo_count;
		rules->philos[i]->last_ate = 0;
		rules->philos[i]->prules = rules;
		i++;
	}
}