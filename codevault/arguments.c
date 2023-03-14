#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void *routine(void * arg)
{
	int	index = *(int *)arg;
	printf("%d ", primes[index]);
	return (arg);
}

int main (void)
{
	pthread_t th[10];
	int i;
	int *arg;

	i = 0;
	while (i < 10)
	{
		arg = malloc(sizeof(int));
		*arg = i;
		if(pthread_create(&th[i], NULL, &routine, arg) != 0)
			perror("Failled to create thread");
		i++;
	}
	i = 0;
	while (i < 10)
	{
		if(pthread_join(th[i], NULL) != 0)
			perror("Failled to join thread");
		i++;
	}
	return (0);
}
