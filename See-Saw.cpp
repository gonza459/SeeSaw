#include <iostream>
#include <pthread.h>
#include <fstream>
#include <semaphore.h>
#include <unistd.h>
#define T_NUM 2

using namespace std;

sem_t fredUp;
sem_t wilmaUp;

float fredVelocity = 1;
float wilmaVelocity = 1.5;
float max_height = 7;
float min_height = 1;

float fredHeight = 1;
float wilmaHeight = 7;

void *fredSee(void*){

    sem_wait(&fredUp); // fred wait()

    while (fredHeight < max_height && wilmaHeight > min_height){
      cout<< "Wilma's height: " << wilmaHeight << endl;
      cout<< "Fred's height: " << fredHeight << endl;
      cout << endl;
      fredHeight += fredVelocity;
      wilmaHeight -= fredVelocity;
      sleep (1);
    }

  sem_post (&wilmaUp); //signal() wilma to move up
  pthread_exit(NULL);

//}

void *wilmaSaw(void*){

    sem_wait(&wilmaUp); //wilma wait()

    while (fredHeight > min_height && wilmaHeight < max_height){
      cout<< "Wilma's height: " << wilmaHeight << endl;
      cout<< "Fred's height: " << fredHeight << endl;
      cout << endl;
      wilmaHeight += wilmaVelocity;
      fredHeight -= wilmaVelocity;
      sleep(1);

    }
    sem_post(&fredUp); //signal() fred to move up
  pthread_exit(NULL);

}

int main(int argc, char* argv[]){

  sem_init(&fredUp, 1, 1);
  sem_init(&wilmaUp, 1, 0);

  pthread_t thread1;
  pthread_t thread2;

//for(int i=0; i<= 10; i++){
  pthread_create(&thread1, NULL, fredSee, NULL);
  pthread_join(thread1, NULL);

  pthread_create(&thread2, NULL, wilmaSaw, NULL);
  pthread_join(thread2, NULL);
}
  return 0;

}
