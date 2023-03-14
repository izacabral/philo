#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int mails = 0;
pthread_mutex_t mutex;

void *routine()
{
	int i = 0;
	while (i < 10000) //cada thread faz a sua iteração... o resultado vai ser 10000 vezes a quantidade de threads
	{
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
		i++;
	}
	return (NULL);
}

int main (void)
{
	pthread_t th[8];
	int i;
	pthread_mutex_init(&mutex, NULL);
	i = 1;
	while (i <= 8)
	{
		if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
			return (1);
		printf("Thread %d has started\n", i);
		i++;
	}
	i = 1;
	while (i <=8)
	{
		if (pthread_join(th[i], NULL) != 0)
			return (2);
		printf("Thread %d has finished execution\n", i);
		i++;
	}
	pthread_mutex_destroy(&mutex);
	printf("Number of mails: %d\n", mails);
	return (0);
}
