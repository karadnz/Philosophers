/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 13:12:34 by mkaraden          #+#    #+#             */
/*   Updated: 2023/02/23 18:26:59 by mkaraden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void init_philo(t_philo *philo, int i);

int main(int argc, char **argv)
{

	if (argc != 5 && argc != 6)
	{
		printf("Argument count not valid!");
		return (0);
	}
	
	t_rules *rules = (t_rules *)malloc(sizeof(t_rules));
	init_rules(argc, argv, rules);

	for (int i = 0; i < rules->philo_count; i++) // yeme sayisi
	{
		pthread_create(&(rules->philos[i]->thread_id), NULL, p_eat, rules->philos[i]);
	}

	for (int j = 0; j < rules->philo_count; j++)
	{
		pthread_join(rules->philos[j]->thread_id, NULL);
	}
	return (0);
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



int main2(int argc, char **argv)
{

	if (argc != 5 && argc != 6)
	{
		printf("Argument count not valid!");
		return (0);
	}
	
	t_rules *rules = (t_rules *)malloc(sizeof(t_rules));
	init_rules(argc, argv, rules);

	for (int i = 0; i < rules->max_eat; i++) // yeme sayisi
	{
		for (int j = 0; j < rules->philo_count; j++)
		{
			if ((i + j) % 2 == 0)
			{
				pthread_create(&(rules->philos[j]->thread_id), NULL, p_eat, rules->philos[j]);
			}
			else
				pthread_create(&(rules->philos[j]->thread_id), NULL, p_sleep, rules->philos[j]);
		}

		for (int j = 0; j < rules->philo_count; j++)
		{
			pthread_join(rules->philos[j]->thread_id, NULL);
		}

		printf("\n");
	}
	return (0);
}