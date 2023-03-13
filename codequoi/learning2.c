#include <pthread.h>
#include <stdio.h>

# define TIMES_TO_COUNT 21000
# define RESET "\e[0m"
# define BYLW "\e[1;33m"
# define YLW "\e[33m"
# define RED "\e[31m"
# define GREEN "\e[32m"

// flags para compilação
// -pthread
// cc -pthread -fsanitize=thread learning2.c -o learning2 && ./learning2

// criando um nova thread protótipo
// int pthread_create(pthread_t *restrict thread, const pthread_attr_t *restrict attr, void *(*start_routine)(void *), void *restrict arg);
// thread - ponteiro para uma variável do tipo pthread_t;
// attr - argumento que nos permite alterar os atributos padrão da nova thread. No momento usaresmos NULL.
// start_routine - função onde a thread irá iniciar a sua execução.
// arg - ponteiro para um argumento para ser passado para start_routine, se quisermos passar vários parâmetros para a função precisamos criar uma struct.
// RETORNA 0 em sucesso ou um código de erro para fracasso.


// joining threads - bloqueia a execução de uma thread até o acabamento de uma outra thread - ver learning.c
// int phtread_join(pthread_t thread, void **retval);
// thread - o ID da thread pelo qual este deve esperar
// retval: um ponteiro para uma variável que pode conter o valor de retorno da função de rotina da thread (start_routine). Por enquanto NULL.
// RETORNA 0 em sucesso ou um código de erro para fracasso.

// detach threads - não bloquear a thread, dar detach para dizer ao sistema que ele pode recuperar imediatamente os seus recursos
// int pthread_detach(phtread_t thread);
// RETORNA 0 em sucesso ou um código de erro para fracasso.


// função incovada pela criação da thread. A thread finaliza no final dessa função.
void	*thread_routine(void *data)
{
	pthread_t tid;
	unsigned int *count;
	unsigned int i;

	tid = pthread_self();
	count = (unsigned int *) data;
	printf("%sThread [%ld]: Count at thread start = %u.%s\n", YLW, tid, *count, RESET);
	i = 0;
	while (i < TIMES_TO_COUNT)
	{
		(*count)++;
		i++;
	}
	printf("%sThread [%ld]: Final count  = %u.%s\n", BYLW, tid, *count, RESET);
	return (NULL);
}

int	main(void)
{
	pthread_t	tid1;
	pthread_t	tid2;
	unsigned int count;

	count = 0;

	pthread_create(&tid1, NULL, thread_routine, &count);
	printf("Main: Created first thread [%ld]\n", tid1);
	pthread_create(&tid2, NULL, thread_routine, &count);
	printf("Main: Created second thread [%ld]\n", tid2);
	pthread_join(tid1, NULL);
	printf("Main: Joining first thread [%ld]\n", tid1);
	pthread_join(tid2, NULL);
	printf("Main: Joining second thread [%ld]\n", tid2);
	if (count != (2 * TIMES_TO_COUNT))
		printf("%sMain: ERROR! Total count is %u%s\n", RED, count, RESET);
	else
		printf("%sMain: OK. Total count is %u%s\n", GREEN, count, RESET);
	return (0);

}
