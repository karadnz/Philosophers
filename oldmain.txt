/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oldmain.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 13:12:34 by mkaraden          #+#    #+#             */
/*   Updated: 2023/02/24 15:51:42 by mkaraden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{

	if (argc != 5 && argc != 6)
	{
		printf("Argument count not valid!");
		return (0);
	}
	
	t_rules *rules = (t_rules *)malloc(sizeof(t_rules));
	init_rules(argc, argv, rules);

	for (int i = 0; i < rules->eat_count; i++) // yeme sayisi
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

void *p_eat(void *philo)
{
	t_philo *phil = (t_philo *)philo;
	long long in = timestamp();

	long long diff = time_diff(phil->rules->first_timestamp, in);
	printf("%lld : %d is eating \n", diff, phil->id);

	while (timestamp() - in < phil->rules->time_eat)
	{
		usleep(10);
	}
	return NULL;
}

void *p_sleep(void *philo)
{
	t_philo *phil = (t_philo *)philo;
	long long in = timestamp();

	long long diff = time_diff(phil->rules->first_timestamp, in);
	printf("%lld : %d is sleeping \n", diff, phil->id);
	
	while (timestamp() - in < phil->rules->time_eat)
	{
		usleep(10);
	}
	// usleep(100 * 10000);
	return NULL;
}


void init_rules(int argc, char **argv, t_rules *rules)
{
	rules->philo_count = ft_atoi(argv[1]);
	rules->time_death = ft_atoi(argv[2]);
	rules->time_eat = ft_atoi(argv[3]);
	rules->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		rules->eat_count = ft_atoi(argv[5]);
	// rules->is_dead = 0;
	// rules->all_Ate = 0;

	rules->philos = (t_philo **)malloc(sizeof(t_philo *) * rules->philo_count);
	init_philos(rules);
	rules->first_timestamp = timestamp();
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
		rules->philos[i]->rules = rules;
		i++;
	}
}



void *p_eat2(t_philo *philo)
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
