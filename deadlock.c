#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
pthread_mutex_t A = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t B = PTHREAD_MUTEX_INITIALIZER;

void* test1(void* args){
    for(int i =0;i < 500000;i++){
    pthread_mutex_lock(&A);
    printf("test 1 block A\n");
    pthread_mutex_lock(&B);
    printf("test 1 block B\n");
    //
    printf("test 1 unblock B\n"); 
    pthread_mutex_unlock(&B);   
    printf("test 1 unblock A\n");
    pthread_mutex_unlock(&A);

}

}

void* test2(void* args){
    for(int i =0;i < 500000;i++){
    pthread_mutex_lock(&B);
    printf("test 2 block B\n");
    pthread_mutex_lock(&A);
    printf("test 2 block A\n");
    //
    printf("test 2 unblock A\n"); 
    pthread_mutex_unlock(&A);
  
    printf("test 2 unblock B\n");
    pthread_mutex_unlock(&B); 
}

}


int main(void)
{
    pthread_t thread1,thread2;
    if(pthread_create(&thread1, NULL, test1,
            NULL) != 0 || pthread_create(&thread2, NULL, test2,
            NULL)) {
         perror("pthread_create");
         exit(1);
  }
  pthread_join(thread1,NULL);
  pthread_join(thread2,NULL);
  
    printf("hello, world\n");
}