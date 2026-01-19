/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilisson <wilisson@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 19:30:16 by wilisson          #+#    #+#             */
/*   Updated: 2026/01/18 22:06:51 by wilisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	destroy_forks(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	free(table->forks);
	return (EXIT_SUCCESS);
}

int	destroy_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		pthread_mutex_destroy(&table->philos[i].meal_mutex);
		i++;
	}
	free(table->philos);
	return (EXIT_SUCCESS);
}

int	cleanup_table(t_table *table)
{
	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(&table->sim_mutex);
	return (EXIT_SUCCESS);
}
