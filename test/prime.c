/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prime.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addzikow <addzikow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 10:20:52 by addzikow          #+#    #+#             */
/*   Updated: 2021/11/03 10:38:05 by addzikow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int primes[10] = {2,3,5,7,11,13,17,19,23,29};

void *routine(void *arg)
{
	int index;

	index = *(int*)arg;
	printf("thread %d = %d\n",index, primes[index]);

}

int main(int ac, char *av[])
{
	pthread_t th[10];
	int i;
	int *ibis;

	i = 0;
	while (i < 10)
	{
		ibis = malloc(sizeof(int));
		*ibis = i;
		if (pthread_create(&th[i], NULL, &routine, ibis) != 0)
			perror("Failed to create thread");
		i++;
	}
	i = 0;
	while (i < 10)
	{
		if (pthread_join(th[i], NULL) != 0)
			perror("Failed to join thread");
		i++;
	}


	return (0);
}