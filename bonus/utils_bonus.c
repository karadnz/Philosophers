/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 13:52:10 by mkaraden          #+#    #+#             */
/*   Updated: 2023/03/10 17:49:49 by mkaraden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

long long	time_diff(long long past, long long pres)
{
	return (pres - past);
}

void	u_sleep(long long time, t_rules *rules)
{
	long long	i;

	i = timestamp();
	while (!(rules->all_ate))
	{
		if (time_diff(i, timestamp()) >= time)
			break ;
		usleep(500);
	}
}

void	p_print(t_rules *rules, int id, char *msg)
{
	sem_wait((rules->writing));
	printf("%lli ", timestamp() - rules->first_timestamp);
	printf("%i ", id + 1);
	printf("%s\n", msg);
	sem_post((rules->writing));
	return ;
}

int	ft_atoi(const char *str)
{
	long int	n;
	int			sign;

	n = 0;
	sign = 1;
	while ((*str <= 13 && *str >= 9) || *str == 32)
		str++;
	if (*str == '-')
		return (-1);
	else if (*str == '+')
		str++;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			n = n * 10 + (*str++ - '0');
		else
			return (-1);
	}
	return ((int)(n * sign));
}
