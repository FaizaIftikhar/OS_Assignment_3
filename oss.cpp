

#include <iostream>
#include <pthread.h>
#include <time.h>
#define size 10
#define thread_size 2    //My systyem processor is having 2 cores so thread size is 2
using namespace std;

int arr[size];
int temp_val = 0;
void mixed(int first, int mid_val, int end)
{
   int* start = new int[mid_val - first + 1];
   int* last = new int[end - mid_val];
   int temp_a = mid_val - first + 1;
   int temp_b = end - mid_val;
   int i, j;
   int k = first;
   for(i = 0; i < temp_a; i++){
      start[i] = arr[i + first];
   }
   for (i = 0; i < temp_b; i++){
      last[i] = arr[i + mid_val + 1];
   }
   i = j = 0;
   while(i < temp_a && j < temp_b){
      if(start[i] <= last[j]){
         arr[k++] = start[i++];
      }
      else{
         arr[k++] = last[j++];
      }
   }
   while (i < temp_a){
      arr[k++] = start[i++];
   }
   while (j < temp_b){
      arr[k++] = last[j++];
   }
}

void merge(int first, int end)
{
   int mid_val = first + (end - first) / 2;
   if(first < end)
   {
      merge(first, mid_val);
      merge(mid_val + 1, end);
      mixed(first, mid_val, end);
   }
}
void* merge(void* arg)
{
   int set_val = temp_val++;
   int first = set_val * (size / 2);
   int end = (set_val + 1) * (size / 2) - 1;
   int mid_val = first + (end - first) / 2;
   if (first < end)
   {
       merge(first, mid_val);
      merge(mid_val + 1, end);
      mixed(first, mid_val, end);
   }
   return 0;
}


int main()
{
   for(int i = 0; i < size; i++)
   {
      cout<<"enter the elements of array"<<endl;   //entering the elements of array
      cin>>arr[i];
   }
   pthread_t P_TH[thread_size];
   for(int i = 0; i < thread_size; i++)
   {
      pthread_create(&P_TH[i], NULL, merge, (void*)NULL);  //creating 2 threads via loop because our cores are 2
   }
   for(int i = 0; i < 2; i++)
   {
      pthread_join(P_TH[i], NULL);
   }
   mixed(0, (size / 2 - 1) / 2, size / 2 - 1);           //sorting the array by calling function of merge sort
   mixed(size / 2, size/2 + (size-1-size/2)/2, size - 1);
   mixed(0, (size - 1)/2, size - 1);
   cout<<"Merge Sorted array is: ";
   for (int i = 0; i < size; i++)
   {
      cout << arr[i] << " ";
   }
   return 0;
}

