/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addzikow <addzikow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 17:00:44 by addzikow          #+#    #+#             */
/*   Updated: 2021/11/03 15:50:46 by addzikow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_exit(char *str)
{
	ft_putstr_fd(str, 2);
	return (EXIT_FAILURE);
}

//Initialise les valeurs des arguments d'entree.
void init_party(t_party *party)
{
	party->arg.nb_philo = 0;
	party->arg.die = 0;
	party->arg.eat = 0;
	party->arg.sleep = 0;
	party->arg.nb_eat = 0;
}


//Reparti les arguments d'entree.
int parse_args(int ac, char **av, t_party *party)
{
	if (ac != 5)
	{
		ft_putstr_fd("Error args.\n", 2);
		return (1);
	}
	party->arg.nb_philo = ft_atoi(av[1]);
	party->arg.die = ft_atoi(av[2]);
	party->arg.eat = ft_atoi(av[3]);
	party->arg.sleep = ft_atoi(av[4]);
	if (ac == 6)
		party->arg.nb_eat = ft_atoi(av[5]);
	return (0);
}

//Permet de connaitre le temps actuel en millisecondes avec gettimeofday.
long int		actual_time_in_ms(void)
{
	long int			time;
	struct timeval		current_time;

	time = 0;
	if (gettimeofday(&current_time, NULL) == -1)
		ft_exit("Gettimeofday returned -1\n");
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000); //temps en millisecondes
	return (time);
}


//Permet d'avoir un usleep plus precis que la fonction de base.
void	ft_usleep(long int time_in_ms)
{
	long int	start_time;

	start_time = 0;
	start_time = actual_time_in_ms();
	while ((actual_time_in_ms() - start_time) < time_in_ms)
		usleep(time_in_ms / 10);
}

void	init_philos(t_party *party)
{
	int i;
	pthread_mutex_t *mutex;

	party->philo = malloc(sizeof(t_philo) * party->arg.nb_philo);
	if (!party->philo)
		return (ft_exit("Malloc issue for party->philo."));
	mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(&mutex, NULL);
	i = 0;
	while (i < party->arg.nb_philo)
	{
		party->philo[i].id = i;
		party->philo[i].thread_id = i;
		pthread_mutex_init(&party->philo[i].fork_left, NULL);
		party->philo[i].fork_right = mutex;	
	}
}

int main(int argc, char **argv)
{
	t_party party;

	init_party(&party);
	parse_args(argc, argv, &party);
	printf("party philo = %d\n", party.arg.nb_philo);
	return (0);
}