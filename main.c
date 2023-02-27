/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 13:12:34 by mkaraden          #+#    #+#             */
/*   Updated: 2023/02/27 15:44:33 by mkaraden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	int		i;
	t_rules	*rules;

	if (!(is_args_valid(argc, argv)))
	{
		write(2, "Error at arguments!", 19);
		return (0);
	}
	i = 0;
	rules = (t_rules *)malloc(sizeof(t_rules));
	init_rules(argc, argv, rules);
	rules->first_timestamp = timestamp();
	while (i < rules->philo_count)
	{
		if (pthread_create(&(rules->philos[i]->thread_id), NULL, ft_est,
				rules->philos[i]))
			exit(1);
		rules->philos[i]->last_ate = timestamp();
		i++;
	}
	check_is_dead(rules, rules->philos);
	p_exit(rules, rules->philos);
	return (0);
}

void	p_exit(t_rules *rules, t_philo **philos)
{
	int	i;

	i = -1;
	while (++i < rules->philo_count)
	{
		pthread_join(philos[i]->thread_id, NULL);
		free(rules->philos[i]);
	}
	i = -1;
	while (++i < rules->philo_count)
		pthread_mutex_destroy(&(rules->forks[i]));
	pthread_mutex_destroy(&(rules->writing));
	pthread_mutex_destroy(&(rules->meal_check));
	free(rules->philos);
	free(rules);
}
