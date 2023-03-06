/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 13:51:50 by mkaraden          #+#    #+#             */
/*   Updated: 2023/03/06 16:45:14 by mkaraden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
		rules->max_eat = ((ft_atoi(argv[5])) * 1);//rules->philo_count
	else
		rules->max_eat = -1;
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

char *get_name(int i)
{
	char	*rt;
	int		j;

	j = 0;
	rt = malloc((sizeof(char) * 3) + get_len(i) + 1);
	rt[0] = 'i';
	rt[1] = '_';
	rt[2] = 'a';
	while (j < get_len(i))
	{
		rt[3 + j] = 'a' + (i % 10);
		i /= 10;
		j++;
	}
	rt[3 + j] = '\0';
	return (rt);
}

	
int	init_mutex(t_rules *rules)
{
	sem_unlink("meal_check");
	sem_unlink("writing");
	sem_unlink("forks");
	sem_unlink("stop");
	rules->is_ate = (sem_t **)malloc(sizeof(sem_t *) * rules->philo_count);

	for (int i = 0; i < rules->philo_count; i++)
	{
		char *str = get_name(i + 1);
		sem_unlink(str);
		//printf("%s HIT \n\n",str);
		rules->is_ate[i] = rules->stop = sem_open(str, O_CREAT, 0600, 1);
		free(str);
	}
	rules->stop = sem_open("stop", O_CREAT, 0600, 1);
	rules->meal_check = sem_open("meal_check", O_CREAT, 0600, 1);
	rules->writing = sem_open("writing", O_CREAT, 0600, 1);
	rules->forks = sem_open("forks", O_CREAT, 0600,
			rules->philo_count);
}
