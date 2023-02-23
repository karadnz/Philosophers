/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 18:26:35 by mkaraden          #+#    #+#             */
/*   Updated: 2023/02/23 18:31:48 by mkaraden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void init_rules(int argc, char **argv, t_rules *rules)
{
	rules->philo_count = ft_atoi(argv[1]);
	rules->time_death = ft_atoi(argv[2]);
	rules->time_eat = ft_atoi(argv[3]);
	rules->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		rules->max_eat = ft_atoi(argv[5]);
	rules->is_dead = 0;
	rules->all_ate = 0;

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

int	init_mutex(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->philo_count)
	{
		if (pthread_mutex_init(&(rules->forks[i]), NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&(rules->writing), NULL))
		return (1);
	if (pthread_mutex_init(&(rules->meal_check), NULL))
		return (1);
	return (0);
}