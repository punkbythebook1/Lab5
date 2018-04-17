#include <stdio.h>
#include <pthread.h>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>

#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <getopt.h>

#include <iostream>

pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
unsigned int fact = 1;
unsigned int max_val = 0;
unsigned int cur_val = 1; 
unsigned int mod = 0;
void* factorial(void* args){
    while(cur_val <= max_val){
    pthread_mutex_lock(&mut); 
      fact*=cur_val;
      cur_val+=1;    
    pthread_mutex_unlock(&mut);
    }

} 

int main(void)
{
    int thnum = 4;
    mod = 400;
    max_val = 30;
    
    pthread_t *threads =(pthread_t*)malloc(sizeof(pthread_t) * thnum); 
    for(int i = 0;i < thnum;i++){
     if (pthread_create(&threads[i], NULL, factorial,
            NULL) != 0) {
         perror("pthread_create");
         exit(1);
  }
  
  }
  for (int i = 0; i < thnum; i++) {
    pthread_join(threads[i],NULL);
  }
  free(threads);
  unsigned int f_m = fact%mod; 
 // printf("Factorial po modulu = %d\n",fact);
   std::cout<<"Factorial po modulu = "<<f_m<<std::endl;
   return 0; 
}
