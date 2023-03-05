/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   est_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 13:51:39 by mkaraden          #+#    #+#             */
/*   Updated: 2023/03/05 19:46:55 by mkaraden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*ft_bonus_death(void *phil)
{
	t_philo	*philo;
	int		j;

	philo = (t_philo *)phil;
	while(1)
	{
		sem_wait(philo->rules->meal_check);
		if (time_diff(philo->last_ate, timestamp()) > philo->rules->time_death)
		{
			p_print(philo->rules, philo->id, "died");
			
			//philo->rules->is_dead = 1;
				j = -1 ;
			
				//while (++j < rules->philo_count)
					//pthread_mutex_unlock(&(rules->forks[j]));
				/*while (++j < philo->rules->philo_count)
				{
					printf("%D\n\n", philo->rules->philos[j]->pid);
					if(philo->rules->philos[j]->pid != philo->pid)
						kill(philo->rules->philos[j]->pid, SIGKILL);
				}*/
				//kill(philo->pid, SIGINT);
			sem_post(philo->rules->meal_check);
			sem_post(philo->rules->stop);
			break ;

		}
		sem_post(philo->rules->meal_check);
		usleep(500);

	}

	return NULL;

}
void	*ft_est(void *phil)
{
	t_philo		*philo;
	pthread_t	death;

	philo = (t_philo *)phil;
	pthread_create(&death, NULL, ft_bonus_death, philo);
	pthread_detach(death);
	/*if (philo->id % 2)
		usleep(15000);*/
	while (1) //!philo->rules->is_dead
	{
		//printf("YEMEK\n\n\n");
		p_eat(philo);
		/*if (philo->rules->is_dead)
			break ;*/
		if (philo->rules->max_eat != -1 && philo->rules->all_ate)
			break ;
		if (philo->rules->max_eat != -1
			&& philo->eat_count >= philo->rules->max_eat)
			break ;
		p_print(philo->rules, philo->id, "is sleeping");
		u_sleep(philo->rules->time_sleep, philo->rules);
		p_print(philo->rules, philo->id, "is thinking");
	}
	return (NULL);
}

void	p_eat(t_philo *philo)
{
	t_rules	*rules;

	rules = philo->rules;
	sem_wait((rules->forks));
	
	p_print(philo->rules, philo->id, "has taken a fork");
	sem_wait((rules->forks));
	p_print(philo->rules, philo->id, "has taken a fork");
	sem_wait((rules->meal_check));
	p_print(rules, philo->id, "is eating");
	philo->last_ate = timestamp();
	sem_post((rules->meal_check));
	u_sleep(rules->time_eat, rules);
	(philo->eat_count)++;
	sem_post((rules->forks));
	sem_post((rules->forks));
}

void	check_is_dead(t_rules *rules, t_philo **philos)
{
	int	i;
	int	j;

	while (!(rules->all_ate))
	{
		i = 0;
		while (i < rules->philo_count && !(rules->is_dead))
		{
			sem_wait((rules->meal_check));
			if (time_diff(philos[i]->last_ate, timestamp()) > rules->time_death)
			{
				p_print(rules, i, "died");
				rules->is_dead = 1;
				j = -1 ;
				//while (++j < rules->philo_count)
					//pthread_mutex_unlock(&(rules->forks[j]));
				/*while (++j < rules->philo_count)
				{
					kill(rules->philos[j]->pid, SIGKILL);
				}*/
			}
			sem_post((rules->meal_check));
			usleep(100);
			i++;
		}
		if (rules->is_dead)
			break ;
		eat_check(rules, philos);
	}
}

void	eat_check(t_rules *rules, t_philo **philos)
{
	int	i;

	i = 0;
	while (rules->max_eat != -1 && i < rules->philo_count
		&& philos[i]->eat_count >= rules->max_eat)
		i++;
	if (i == rules->philo_count)
		rules->all_ate = 1;
}
