/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 18:26:35 by mkaraden          #+#    #+#             */
/*   Updated: 2023/02/25 15:44:44 by mkaraden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_args_valid(int argc, char **argv)
{
	int	i;

	if (argc != 5 && argc != 6)
		return (0);
	i = 1;
	while (i < argc)
	{
		if (!is_valid_num(argv[i]))
			return (0);
		i++;
	}
	if (argc == 6 && ft_atoi(argv[5]) == 0)
		return (0);
	return (1);
}

int	is_valid_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

void	init_rules(int argc, char **argv, t_rules *rules)
{
	rules->philo_count = ft_atoi(argv[1]);
	rules->time_death = ft_atoi(argv[2]);
	rules->time_eat = ft_atoi(argv[3]);
	rules->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		rules->max_eat = ft_atoi(argv[5]);
	else
		rules->max_eat = -1;
	rules->is_dead = 0;
	rules->all_ate = 0;
	rules->philos = (t_philo **)malloc(sizeof(t_philo *) * rules->philo_count);
	init_philos(rules);
	init_mutex(rules);
	return ;
}

void	init_philos(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->philo_count)
	{
		rules->philos[i] = (t_philo *)malloc(sizeof(t_philo));
		rules->philos[i]->id = i;
		rules->philos[i]->lf_id = i;
		rules->philos[i]->rf_id = (i + 1) % rules->philo_count;
		rules->philos[i]->last_ate = 0;
		rules->philos[i]->rules = rules;
		rules->philos[i]->eat_count = 0;
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
