/*
* Rahul Gautam
* Indian Statistical Institute
* Comparison of heapsort, mergesort, quicksort
* and their iterative versions
* 09th Mar 2019
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "functions.h"


TRIPLE (*fun_ptr_arr[])(int*, int,int ) = {quickSortIF, quickSortIterativeIF, mergeSortIF,
                                         mergeSortIterativeIF, heapSortIF,heapSortIterativeIF}; 

char* nameArr[] = {"QuickSort.dat","QuickSortIterative.dat","MergeSort.dat",
                    "MergeSortIterative.dat","HeapSort.dat","HeapSortIterative.dat"};


// takes a function pointer and the
// name of the function
// profiles it and writes its data on 
// corresponding dat file

void profileFunction(int n)
{
    int arrSize = START_SIZE;
    int i=0;
    
    FILE *fptr;

    fptr = fopen(nameArr[n], "w");
    if(fptr == NULL)
    {
      printf("Error!");
      exit(1);
    }
    TRIPLE t;
    int swaps = 0,comp = 0;
    double time = 0;

    while(arrSize<END_SIZE)
    {
        

        for(i=0;i<ITERATION_FOR_AVG;i++)
        {
            int* arr = generateRandArr(arrSize);
            t = fun_ptr_arr[n](arr,0,arrSize-1);

            comp += t.compCount;
            swaps += t.swapCount;
            time+=t.time;

            #ifdef DEBUG
            assert(verifySorted(arr,arrSize));
            #endif
            free(arr);
        }
      
        comp /= ITERATION_FOR_AVG;
        swaps /= ITERATION_FOR_AVG;
        time /=ITERATION_FOR_AVG;

        // write in a file for plotting purpose
        fprintf(fptr,"%d %d %lf %d\n",comp,swaps,time,arrSize);
        #ifdef DEBUG
            fprintf(stdout,"%d %d %lf %d\n",comp,swaps,time,arrSize);
        #endif
        
        arrSize+=INCREMENT_SIZE;
    }
    fclose(fptr);
}

int main()
{
    /*
    quickSort(arr,0,sizeof(arr)/sizeof(int)-1);
    
    qsVqsItr();
    printf("Done\n");
    msVmsItr();printf("Done\n");
    hsVhsItr();printf("Done\n");
    qsVmsVhs();printf("Done\n");
    qsVmsVhsItr();printf("Done\n");
    
    qsVmsVhsVIsItr();
    */
    int i=0;
    for( i = 0; i < 6; i++)
    {
        printf("%s\n",nameArr[i]);
        profileFunction(i);
    }
    
}
