//23-Ntu-CS-1167 Kashmir Jamshaid  
//Write a C program that calculates array sum using multiple threads:
//1.  Create an array of 20 integers: {1, 2, 3, ..., 20}
//2.  Create 4 threads, each calculating sum of 5 elements:   Thread 1: elements 0-4 (sum of 1 to 5)
  // Thread 2: elements 5-9 (sum of 6 to 10)
  //Thread 3: elements 10-14 (sum of 11 to 15)
  // Thread 4: elements 15-19 (sum of 16 to 20)
//Pass the starting index and count to each thread using a structure:
//4.  Each thread prints its partial sum
//5.  Main thread collects all return values and calculates total sum
#include <stdio.h>
#include <pthread.h>   // used when we want to make threads.
 
struct ThreadData {
    int start_index;
    int count;
};
int array[20];

void* sum_function(void* arg){
    struct ThreadData* data = (struct ThreadData*)arg;
    int* result ;  
    int start = data->start_index;
    int count = data->count;
    int sum = 0;

    for (int i=start; i < start+count; i++){
        sum += array[i];
    }
    printf("Thread elemnets from   %d to %d partial sum = %d\n", start, start+count-1, sum);
    // Return sum as pointer
    *result = sum;
    pthread_exit(result);
}


int main() {
    pthread_t thread[4];
    int total_sum = 0;
    struct ThreadData threadData[4];
    // Declare and initialized an array 
    for(int i=0; i<20; i++){
        array[i] = i+1;
    }
    // Creating Threads and passing values to it as arrguments:
    for (int i=0; i<4; i++){
        threadData[i].start_index = i * 5; 
        threadData[i].count = 5;
        pthread_create(&thread[i],NULL, sum_function, &threadData[i]);
    }
    // wait for all thread completion 
    for (int i=0; i<4; i++){
        int* partialSum;
        pthread_join(thread[i], (void**)&partialSum);
        total_sum += *partialSum;
        
    }
    printf("Sum of All  array elements = %d\n",total_sum);
    return 0;
}
