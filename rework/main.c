/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addzikow <addzikow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 11:23:00 by addzikow          #+#    #+#             */
/*   Updated: 2021/11/08 11:32:25 by addzikow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	parse_arguments(t_data *data, char **argv)
{
	data->arg.nb_philo = ft_atol(argv[1]);
	data->arg.time_to_die = ft_atol(argv[2]);
	data->arg.time_to_eat = ft_atol(argv[3]);
	data->arg.time_to_sleep = ft_atol(argv[4]);
	if (argv[5] != NULL)
		data->arg.meals_per_philo = ft_atoi(argv[5]);
	if (data->arg.nb_philo < 0 || data->arg.nb_philo > 2147483647)
		return (1);
	else if (data->arg.time_to_die < 0 || data->arg.time_to_die > 2147483647)
		return (1);
	else if (data->arg.time_to_eat < 0 || data->arg.time_to_eat > 2147483647)
		return (1);
	else if (data->arg.time_to_sleep < 0 || data->arg.time_to_sleep > 2147483647)
		return (1);
	else if (data->arg.meals_per_philo < 0 || data->arg.meals_per_philo > 2147483647)
		return (1);
	return (0);
}

char	*get_state(const char *str, int state)
{
	char	*buffer;

	if (state == FORK)
		buffer = ft_strjoin(str, "\thas taken a fork\n");
	else if (state == EAT)
		buffer = ft_strjoin(str, "\tis eating\n");
	else if (state == SLEEP)
		buffer = ft_strjoin(str, "\tis sleeping\n");
	else if (state == THINK)
		buffer = ft_strjoin(str, "\tis thinking\n");
	else if (state == DIE)
		buffer = ft_strjoin(str, "\tdied\n");
	else
		return (NULL);
	return (buffer);
}

int printer(long timer, int philo, int state)
{
	char *timestamp;
	char *philo_number;
	char *tmp;
	char *buff;

	timestamp = ft_itoa(timer);
	philo_number = ft_itoa(philo);
	tmp = ft_strjoin(timestamp, philo_number);
	buff = get_state(tmp, state);
	if (buff == NULL)
		return (1);
	write(1, buff, ft_strlen(buff));
	free(timestamp);
	free(philo_number);
	free(tmp);
	free(buff);
	return (0);
}


void init_dinner(t_data *data, long start_time)
{
	int	parity;
	int	i;
	int control;

	control = 0;
	parity = data->arg.nb_philo % 2;
	i = 0;
	while (i < data->arg.nb_philo)
	{
		if (data->philo[i].i % 2 == ODD)
		{
			printer(get_time() - start_time, data->philo[i].i, FORK);
			printer(get_time() - start_time, data->philo[i].i, FORK);
			printer(get_time() - start_time, data->philo[i].i, EAT);
			ft_sleep(data->arg.time_to_eat);
		}
		else
		{
			printer(get_time() - start_time, data->philo[i].i, THINK);
			ft_sleep(100);
		}
		i++;
	}
}

void	*schedule(void *data)
{
	long start_time;

	start_time = get_time();
	init_dinner(data, start_time);
	//while (1)
	//{
	//	eating(data, get_time() - start_time);
	//	sleeping(data, get_time() - start_time);
	//	thinking(data, get_time() - start_time);
	//}
}

int	create_philo(t_data *data)
{
	int		i;

	i = 0;
	data->philo = malloc(sizeof(t_ph) * data->arg.nb_philo);
	if (data->philo == NULL)
		return (1);
	while (i < data->arg.nb_philo)
	{
		data->philo[i].i = i + 1;
		if (pthread_create(&data->philo[i].philosoph, NULL, &schedule, (void *)data))
		{
			free(data->philo);
			return (1);
		}
		data->philo[i].fork_in_use = false;
		data->philo[i].alive = true;
		data->state = NOT_INIT;
		i++;
	}
	return (0);
}

int	join_philo(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->arg.nb_philo)
	{
		if (pthread_join(data->philo[i].philosoph, NULL))
		{
			free(data->philo);
			return (1);
		}
		i++;
	}
	return (0);
}

int main(int argc, char *argv[])
{
    t_data data;

    if (argc > 6 || argc < 5)
        return (1);
    if (parse_arguments(&data, argv))
        return (1);
    if (data.arg.nb_philo == 0)
        return (0);
    if (create_philo(&data))
        return (1);
    if (join_philo(&data))
        return (1);
    return (0);
}
