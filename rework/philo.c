/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addzikow <addzikow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 11:23:00 by addzikow          #+#    #+#             */
/*   Updated: 2021/11/08 14:08:32 by addzikow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	parse_arguments(t_data *data, int argc, char **argv)
{
	data->arg.nb_philo = ft_atol(argv[1]);
	data->arg.time_to_die = ft_atol(argv[2]);
	data->arg.time_to_eat = ft_atol(argv[3]);
	data->arg.time_to_sleep = ft_atol(argv[4]);
	if (argc < 5 || argc > 6)
	{
		ft_putstr("Error\n");
		return (1);
	}
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

long int		actual_time_in_ms(void)
{
	long int			time;
	struct timeval		current_time;

	time = 0;
	if (gettimeofday(&current_time, NULL) == -1)
		ft_putstr_fd("Gettimeofday returned -1\n", 1);
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000); //temps en millisecondes
	return (time);
}

void	ft_usleep(long int time_in_ms)
{
	long int	start_time;

	start_time = 0;
	start_time = actual_time_in_ms();
	while ((actual_time_in_ms() - start_time) < time_in_ms)
		usleep(time_in_ms / 10);
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
			printer(actual_time_in_ms() - start_time, data->philo[i].i, FORK);
			printer(actual_time_in_ms() - start_time, data->philo[i].i, FORK);
			printer(actual_time_in_ms() - start_time, data->philo[i].i, EAT);
			ft_usleep(data->arg.time_to_eat);
		}
		else
		{
			printer(actual_time_in_ms() - start_time, data->philo[i].i, THINK);
			ft_usleep(100);
		}
		i++;
	}
}

void	*schedule(void *data)
{
	long start_time;

	start_time = actual_time_in_ms();
	init_dinner(data, start_time);
	//while (1)
	//{
	//	eating(data, actual_time_in_ms() - start_time);
	//	sleeping(data, actual_time_in_ms() - start_time);
	//	thinking(data, actual_time_in_ms() - start_time);
	//}
	return (0);
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
    if (parse_arguments(&data, argc, argv))
        return (1);
    if (data.arg.nb_philo == 0)
        return (0);
    if (create_philo(&data))
        return (1);
    if (join_philo(&data))
        return (1);
    return (0);
}
