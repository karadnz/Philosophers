/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 13:51:16 by mkaraden          #+#    #+#             */
/*   Updated: 2023/03/08 02:46:49 by mkaraden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	int			i;
	t_rules		*rules;
	pthread_t	checker;

	i = -1;
	rules = (t_rules *)malloc(sizeof(t_rules));
	init_rules(argc, argv, rules);
	rules->first_timestamp = timestamp();
	sem_wait(rules->stop);
	while (++i < rules->philo_count)
	{
		rules->philos[i]->last_ate = timestamp();
		rules->philos[i]->pid = fork();
		if (rules->philos[i]->pid == 0)
		{
			ft_est(rules->philos[i]);
			exit(0);
		}
		usleep(10);
	}
	pthread_create(&checker, NULL, ft_eat_checker, rules);
	pthread_detach(checker);
	sem_wait(rules->stop);
	p_exit(rules, rules->philos);
	return (0);
}
/*
if (rules->philos[i]->pid == 0)
		{
			ft_est(rules->philos[i]);
			exit(0);
		}
*/

void	*ft_eat_checker(void *arg)
{
	int		i;
	t_rules	*rules;

	rules = (t_rules *)arg;
	i = 0;
	while (i < rules->philo_count)
	{
		sem_wait(rules->is_ate[i]);
		i++;
	}
	usleep(100);
	i = 0;
	while (i < rules->philo_count)
	{
		sem_wait(rules->is_ate[i]);
		i++;
	}
	sem_post(rules->stop);
}

void	p_exit(t_rules *rules, t_philo **philos)
{
	int	i;

	i = -1;
	while (++i < rules->philo_count)
	{
		kill(rules->philos[i]->pid, SIGKILL);
	}
	sem_close(rules->meal_check);
	sem_close(rules->writing);
	sem_close(rules->forks);
	sem_unlink("meal_check");
	sem_unlink("writing");
	sem_unlink("forks");
	sem_unlink("stop");
	i = 0;
	while (i < rules->philo_count)
	{
		free(rules->philos[i]);
		i++;
	}
	free(rules->philos);
	free(rules->is_ate);
	free(rules);
}

int	get_len(int i)
{
	int	rt;

	rt = 0;
	while (i > 0)
	{
		i = i / 10;
		rt++;
	}
	return (rt);
}

char	*get_name(int i)
{
	char	*rt;
	int		j;
	int		len;

	len = get_len(i);
	j = 0;
	rt = malloc((sizeof(char) * 3) + len + 1);
	rt[0] = 'i';
	rt[1] = '_';
	rt[2] = 'a';
	while (j < len)
	{
		rt[3 + j] = 'a' + (i % 10);
		i /= 10;
		j++;
	}
	rt[3 + j] = '\0';
	return (rt);
}
