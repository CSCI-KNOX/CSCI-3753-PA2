#include<stdio.h> // contains printf()
#include<string.h>  // contains strerror()
#include<pthread.h> // thread functions
#include<unistd.h>  // contains sleep()

pthread_t tid[2];

void* doSomeThing(void *arg)
{
  unsigned long i = 0;
  int thread_no = 0;
  
  pthread_t id = pthread_self();
  
  if ( pthread_equal(id,tid[0]) )
    thread_no = 0;
  else
    thread_no = 1;
  printf("\n Thread %d – active\n", thread_no);
  
  for(i=0 ; i < (0x4FFFFFFF * (thread_no+1)) ; i++)
    ;  // loop for a long time?
  
  printf("\n Thread %d exiting\n", thread_no);

  return NULL;
}


int main(void)
{
  int i = 0;
  int err;

  while (i < 2)
  {
    err = pthread_create(&(tid[i]), NULL, &doSomeThing, NULL);
    
    if (err != 0)
      printf("\nError thread :[%s]", strerror(err));
    else
      printf("\n Thread %d created\n", i);
    i++;
  } 
  
  sleep(5);
  printf("\n Main thread exiting\n");
  return 0;
}
