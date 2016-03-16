#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NUM_THREADS 5


struct thread_data{
   long  thread_id;
   };

int SharedVariable = 0;
        void* SimpleThread(void *args) {

        struct thread_data *info = (struct thread_data *) args;
        int num, val;
        for(num = 0; num < 20; num++) {
        if (random() > RAND_MAX / 2)
        usleep(500);
        val = SharedVariable;
        printf("*** thread %ld sees value %d\n", info->thread_id, val);
        SharedVariable = val + 1;
        }
        val = SharedVariable;
        printf("Thread %ld sees final value %d\n", info->thread_id, val);


        }


        int isNumeric (const char * s)
        {
            if (s == NULL || *s == '\0' || isspace(*s))
                return 0;
            char * p;
            strtod (s, &p);
            return *p == '\0';
        }

int main(int argc, char *argv[]){

    int nt = 0;
    if (!isNumeric(argv[1])) {
        printf ("\nThe argument you passed is not an integer\n");
        }else {
            nt = atoi(argv[1]);
    }
   pthread_t threads[nt];
   struct thread_data td[nt];
   int rc;
   long t;
   for (t=0; t<nt; t++){
            td[t].thread_id=t;
        }
   for(t=0; t<nt; t++){
      printf("In main: creating thread %ld\n", t);
      rc = pthread_create(&threads[t], NULL, SimpleThread, (void *)&td[t]);
      if (rc){
         printf("ERROR; return code from pthread_create() is %d\n", rc);
         exit(-1);
      }
   }

 /* Wait for the threads to end */
 for(t=0; t<nt; t++)
       pthread_join(threads[t], NULL);

   /* Last thing that main() should do */
   pthread_exit(NULL);
}
