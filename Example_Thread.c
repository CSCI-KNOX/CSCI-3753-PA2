#include <stdio.h> // contains printf()
#include <string.h>	// contains strerror()
#include <pthread.h> // thread functions
#include <unistd.h>	// contains sleep()
#include <stdlib.h> // contains atoi()

pthread_t tid[10];
	
void* doSomeThing(void *arg)
{
	unsigned long i = 0;
	int thread_no = 0;
	
	pthread_t id = pthread_self();
	
	// which thread is this??
	for (thread_no=0 ; thread_no < 10 ; thread_no++)
		if ( pthread_equal(id,tid[thread_no]) )
			break; // break out of loop, found the thread

	printf("\n Thread %d – active\n", thread_no);
	
	for(i=0 ; i < (0x0FFFFFFF * (thread_no+1)) ; i++)
		;	// loop for a long time?
			printf("\n Thread %d – active\n", thread_no);

	
	printf("\n Thread %d exiting\n", thread_no);

	return NULL;
}


int main(int argc, char* argv[])
{
	int i = 0;
	int n_threads;
	int err;
	int arg;

	printf ("The parameters are:\n");
	for (arg=0 ; arg < argc ; arg++)
		printf ("\t%3d: [%s]\n", arg, argv[arg]);
		
	n_threads = atoi(argv[1]);
	if (n_threads > 10)
		n_threads = 10;
	
	while (i < n_threads)
	{
		err = pthread_create(&(tid[i]), NULL, &doSomeThing, NULL);
	
		if (err != 0)
			printf("\nError thread :[%s]", strerror(err));
		else
			printf("\n Thread %d created\n", i);
		i++;
	} 
	
	sleep(15);
	printf("\n Main thread exiting\n");
	return 0;
}
