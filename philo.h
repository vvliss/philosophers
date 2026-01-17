/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilisson <wilisson@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 14:00:39 by wilisson          #+#    #+#             */
/*   Updated: 2026/01/17 20:55:23 by wilisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>

# define WRONGINPUT "Error: Wrong input arguments\n"

typedef struct s_philo t_philo;

typedef struct s_table
{
	long			num_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			must_eat_count;
	long long		start_time;
	bool			simulation_running;
	pthread_t		monitor_thread;
	pthread_mutex_t	sim_mutex; 	//access to the simulation_running flag
	pthread_mutex_t	print_mutex; //makes sure only one thread prints to the terminal
	pthread_mutex_t	*forks;
	t_philo			*philos;	
}                   t_table;

typedef struct s_philo
{
	int					id;
	int					eat_count;
	long long			last_meal_time;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		meal_mutex;
	t_table			   	*table;
}                      	t_philo;

long long	current_time_ms(void);
int 		check_death(t_philo *philo);
void 		sleep_check(long long duration_ms, t_table *table);
int			ft_atoi(char *str);
void		init_args(int ac, char **av, t_table *table);
int			parse_args(int ac, char **av, t_table *table);
long long	current_time_ms(void);
void 		sleep_check(long long duration_ms, t_table *table);
void    	eat(t_philo *philo);
void    	sleep_and_think(t_philo *philo);
void    	*odd_philo_routine(void *arg);
void    	*non_odd_philo_routine(void *arg);
int 		destroy_forks(t_table *table);
int 		destroy_philos(t_table *table);
int 		cleanup_table(t_table *table);
int 		init_forks(t_table *table);
int 		init_philo(t_table *table, t_philo *philo);
int			init_table(t_table *table);
void 		monitor_routine(void *arg);


#endif