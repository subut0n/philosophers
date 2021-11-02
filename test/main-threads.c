/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main-threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addzikow <addzikow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 10:11:00 by addzikow          #+#    #+#             */
/*   Updated: 2021/11/02 11:28:35 by addzikow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int mails = 0;
pthread_mutex_t mutex;

void *routine()
{
	for (int i = 0; i < 1000000; i++)
	{
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
		//read mails
		// increment
		// write mails
	}
}


int main(int ac, char *av[])
{
	pthread_t t[4];
	int i;

	pthread_mutex_init(&mutex, NULL);
	i = 0;
	while (i < 4)
	{
		if (pthread_create(&t[i], NULL, &routine, NULL) != 0)
		{
			perror("Failed to create a thread.\n");
			return (1);
		}
		printf("Thread %d has started\n", i);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		if (pthread_join(t[i], NULL) != 0)
			return (2);
		printf("Thread %d has finished execution.\n", i);
		i++;
	}

	pthread_mutex_destroy(&mutex);
	printf("Number of mails : %d\n", mails);
	return (0);
}