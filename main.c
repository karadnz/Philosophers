/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 13:12:34 by mkaraden          #+#    #+#             */
/*   Updated: 2023/02/24 19:52:14 by mkaraden         ###   ########.fr       */
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
	rules->first_timestamp = timestamp();
	for (int i = 0; i < rules->philo_count; i++)
	{
		printf("i: %d id: %d, lf: %d, rf: %d, la: %lld",i,rules->philos[i]->id,rules->philos[i]->lf_id,rules->philos[i]->rf_id,rules->philos[i]->last_ate);
	}
	
	pause()
	for (int i = 0; i < rules->philo_count; i++) // yeme sayisi
	{
		pthread_create(&(rules->philos[i]->thread_id), NULL, ft_est, rules->philos[i]);
		rules->philos[i]->last_ate = timestamp();
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
		pthread_join(philos[i]->thread_id, NULL);
	i = -1;
	while (++i < rules->philo_count)
		pthread_mutex_destroy(&(rules->forks[i]));
	pthread_mutex_destroy(&(rules->writing));
}





