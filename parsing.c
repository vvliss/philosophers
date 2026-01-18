/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilisson <wilisson@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 14:00:10 by wilisson          #+#    #+#             */
/*   Updated: 2026/01/18 23:26:13 by wilisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * sign);
}

void	init_args(int ac, char **av, t_table *table)
{
	table->num_philos = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		table->must_eat_count = ft_atoi(av[5]);
	else
		table->must_eat_count = -1;
}

int	parse_args(int ac, char **av, t_table *table)
{
	init_args(ac, av, table);
	if (table->num_philos <= 0)
		return (EXIT_FAILURE);
	if (table->time_to_die <= 0)
		return (EXIT_FAILURE);
	if (table->time_to_eat <= 0)
		return (EXIT_FAILURE);
	if (table->time_to_sleep <= 0)
		return (EXIT_FAILURE);
	if (ac == 6 && table->must_eat_count <= 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
