/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 13:12:34 by mkaraden          #+#    #+#             */
/*   Updated: 2023/02/24 13:04:26 by mkaraden         ###   ########.fr       */
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