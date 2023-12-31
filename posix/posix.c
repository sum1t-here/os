#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int sum;

/* This sum data is shared by the thread(s) */
/* Threads call this function */
void *runner(void *param);

int main(int argc, char *argv[]) {
   pthread_t tid; /* The thread identifier */
   /* Set of thread attributes */
   pthread_attr_t attr;

   if (argc != 2) {
      fprintf(stderr, "usage: a.out\n");
      return -1;
   }
   if (atoi(argv[1]) < 0) {
      fprintf(stderr, "%d must be >= 0\n", atoi(argv[1]));
      return -1;
   }
   /* Get the default attributes */
   pthread_attr_init(&attr); /* Create the thread */
   pthread_create(&tid, &attr, runner, argv[1]);
   /* Wait for the thread to exit */
   pthread_join(tid, NULL);
   printf("sum = %d\n", sum);
}

/* The thread will now begin control in this function */
void *runner(void *param) {
   int i, upper = atoi(param);
   sum = 0;
   for (i = 1; i <= upper; i++)
      sum += i;
   pthread_exit(NULL);
}
