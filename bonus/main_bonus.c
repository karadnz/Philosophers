/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 13:51:16 by mkaraden          #+#    #+#             */
/*   Updated: 2023/03/06 15:50:55 by mkaraden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	sem_wait(rules->stop);
	while (i < rules->philo_count)
	{
		rules->philos[i]->last_ate = timestamp();
		rules->philos[i]->pid = fork();
		if (rules->philos[i]->pid == 0)
		{
			ft_est(rules->philos[i]);
			exit(0);
		}
		i++;
		usleep(100);
	}
	//p_exit(rules, rules->philos);
	sem_wait(rules->stop);
	i = -1;
	while (++i < rules->philo_count)
	{
		kill(rules->philos[i]->pid, SIGKILL);
	}
	return (0);
}

void	p_exit(t_rules *rules, t_philo **philos)
{
	int	i;

	i = -1;
	while (++i < rules->philo_count)
	{
		waitpid(rules->philos[i]->pid, NULL, 0);
	}
	i = -1;
	sem_close(rules->meal_check);
	sem_close(rules->writing);
	sem_close(rules->forks);
	sem_unlink("death");
	sem_unlink("writing");
	sem_unlink("forks");
	free(rules->philos);
	free(rules);
}
