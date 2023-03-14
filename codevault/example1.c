#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void *routine(void * arg)
{
	int	index = *(int *)arg;
	int sum = 0;
	int i = 0;
	while (i < 5)
	{
		sum += primes[index + i];
		i++;
	}
	*(int *) arg = sum;
	return (arg);
}

int main (void)
{
	pthread_t th[2];
	int i;
	int *arg;

	i = 0;
	while (i < 2)
	{
		arg = malloc(sizeof(int));
		*arg = i * 5;
		if(pthread_create(&th[i], NULL, &routine, arg) != 0)
			perror("Failled to create thread");
		i++;
	}
	i = 0;
	int global_sum = 0;
	while (i < 2)
	{
		int *r;
		if(pthread_join(th[i],(void **) &r) != 0)
			perror("Failled to join thread");
		i++;
		global_sum += *r;
		free(r);
	}
	printf("global_sum: %d\n", global_sum);
	return (0);
}
