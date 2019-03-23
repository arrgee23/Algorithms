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

// quicksort vs iterative quicksort
void qsVqsItr()
{
    clock_t start, end;
    double time;
    int arrSize = 10000;
    int i=0;
    
    FILE *fptr;

    fptr = fopen("qsVqsItr.dat", "w");
    if(fptr == NULL)
    {
      printf("Error!");
      exit(1);
    }

    while(arrSize<MAX_ARR_SIZE)
    {
        // take avg time for five runs
        double time1=0,time2=0,time3=0;
        
        for(i=0;i<ITERATION_FOR_AVG;i++)
        {
            int* arr = generateRandArr(arrSize);
            
            start = clock();
            quickSort(arr,0,arrSize-1);

            end = clock();
            time = ((double) (end - start)) / CLOCKS_PER_SEC;
            time1 += time;

            #ifdef DEBUG
            //assert(verifySorted(arr,arrSize));
            #endif
            free(arr);
        }
        
        for(i=0;i<ITERATION_FOR_AVG;i++)
        {
            int* arr = generateRandArr(arrSize);
            
            start = clock();
            quickSortItr(arr,arrSize);
            end = clock();
            time = ((double) (end - start)) / CLOCKS_PER_SEC;
            time2 += time;

            #ifdef DEBUG
            //assert(verifySorted(arr,arrSize));
            #endif
            free(arr);
        }
        
        time1 = time1/ITERATION_FOR_AVG;
        time2 = time2/ITERATION_FOR_AVG;
        
        // write in a file for plotting purpose
        fprintf(fptr,"%lf %lf %d\n",time1,time2,arrSize);
        #ifdef DEBUG
        printf("size=%d quickSort=%lf quickSortItr = %lf \n",arrSize,time1,time2);
        #endif
        
        arrSize+=INCREMENT_SIZE;
    }
    fclose(fptr);

}
// heapsort normal vs iterative
void hsVhsItr()
{
    clock_t start, end;
    double time;
    int arrSize = 10000;
    int i=0;
    
    FILE *fptr;

    fptr = fopen("hsVhsItr.dat", "w");
    if(fptr == NULL)
    {
      printf("Error!");
      exit(1);
    }

    while(arrSize<MAX_ARR_SIZE)
    {
        // take avg time for five runs
        double time1=0,time2=0,time3=0;
        
        for(i=0;i<ITERATION_FOR_AVG;i++)
        {
            int* arr = generateRandArr(arrSize);
            
            start = clock();
            heapSort(arr,arrSize);

            end = clock();
            time = ((double) (end - start)) / CLOCKS_PER_SEC;
            time1 += time;

            #ifdef DEBUG
            //assert(verifySorted(arr,arrSize));
            #endif
            free(arr);
        }
        
        for(i=0;i<ITERATION_FOR_AVG;i++)
        {
            int* arr = generateRandArr(arrSize);
            
            start = clock();
            heapSortIter(arr,arrSize);
            end = clock();
            time = ((double) (end - start)) / CLOCKS_PER_SEC;
            time2 += time;

            #ifdef DEBUG
            //assert(verifySorted(arr,arrSize));
            #endif
            free(arr);
        }
        
        time1 = time1/ITERATION_FOR_AVG;
        time2 = time2/ITERATION_FOR_AVG;
        
        // write in a file for plotting purpose
        fprintf(fptr,"%lf %lf %d\n",time1,time2,arrSize);
        #ifdef DEBUG
        printf("size=%d heapSort=%lf heapSortItr = %lf \n",arrSize,time1,time2);
        #endif
        
        arrSize+=INCREMENT_SIZE;
    }
    fclose(fptr);

}

void msVmsItr()
{
    clock_t start, end;
    double time;
    int arrSize = 10000;
    int i=0;
    
    FILE *fptr;

    fptr = fopen("msVmsItr.dat", "w");
    if(fptr == NULL)
    {
      printf("Error!");
      exit(1);
    }

    while(arrSize<MAX_ARR_SIZE)
    {
        // take avg time for five runs
        double time1=0,time2=0,time3=0;
        
        for(i=0;i<ITERATION_FOR_AVG;i++)
        {
            int* arr = generateRandArr(arrSize);
            
            start = clock();
            mergeSort(arr,0,arrSize-1);

            end = clock();
            time = ((double) (end - start)) / CLOCKS_PER_SEC;
            time1 += time;

            #ifdef DEBUG
            //assert(verifySorted(arr,arrSize));
            #endif
            free(arr);
        }
        
        for(i=0;i<ITERATION_FOR_AVG;i++)
        {
            int* arr = generateRandArr(arrSize);
            
            start = clock();
            mergeSortIter(arr,0,arrSize-1);
            end = clock();
            time = ((double) (end - start)) / CLOCKS_PER_SEC;
            time2 += time;

            #ifdef DEBUG
            //assert(verifySorted(arr,arrSize));
            #endif
            free(arr);
        }
        
        time1 = time1/ITERATION_FOR_AVG;
        time2 = time2/ITERATION_FOR_AVG;
        
        // write in a file for plotting purpose
        fprintf(fptr,"%lf %lf %d\n",time1,time2,arrSize);
        #ifdef DEBUG
        printf("size=%d mergeSort=%lf mergeSortItr = %lf \n",arrSize,time1,time2);
        #endif
        
        arrSize+=INCREMENT_SIZE;
    }
    fclose(fptr);

}

void qsVmsVhs()
{
    clock_t start, end;
    double time;
    int arrSize = 10000;
    int i=0;
    
    FILE *fptr;

    fptr = fopen("qsVmsVhs.dat", "w");
    if(fptr == NULL)
    {
      printf("Error!");
      exit(1);
    }

    while(arrSize<MAX_ARR_SIZE)
    {
        // take avg time for five runs
        double time1=0,time2=0,time3=0;
        
        for(i=0;i<ITERATION_FOR_AVG;i++)
        {
            int* arr = generateRandArr(arrSize);
            
            start = clock();
            quickSort(arr,0,arrSize-1);

            end = clock();
            time = ((double) (end - start)) / CLOCKS_PER_SEC;
            time1 += time;

            #ifdef DEBUG
            //assert(verifySorted(arr,arrSize));
            #endif
            free(arr);
        }
        
        for(i=0;i<ITERATION_FOR_AVG;i++)
        {
            int* arr = generateRandArr(arrSize);
            
            start = clock();
            mergeSort(arr,0,arrSize-1);
            end = clock();
            time = ((double) (end - start)) / CLOCKS_PER_SEC;
            time2 += time;

            #ifdef DEBUG
            //assert(verifySorted(arr,arrSize));
            #endif
            free(arr);
        }
        
        for(i=0;i<ITERATION_FOR_AVG;i++)
        {
            int* arr = generateRandArr(arrSize);
            
            start = clock();
            heapSort(arr,arrSize);
            end = clock();
            time = ((double) (end - start)) / CLOCKS_PER_SEC;
            time3 += time;

            #ifdef DEBUG
            //assert(verifySorted(arr,arrSize));
            #endif
            free(arr);
        }
        
        time1 = time1/ITERATION_FOR_AVG;
        time2 = time2/ITERATION_FOR_AVG;
        time3 = time3/ITERATION_FOR_AVG;
        
        // write in a file for plotting purpose
        fprintf(fptr,"%lf %lf %lf %d\n",time1,time2,time3,arrSize);
        #ifdef DEBUG
        printf("size=%d quicksort=%lf mergeSort = %lf heapSort=%lf\n",arrSize,time1,time2,time3);
        #endif
        
        arrSize+=INCREMENT_SIZE;
    }
    fclose(fptr);

}


// quicksort vs mergesort vs heapsort.. all iterative
void qsVmsVhsItr()
{
    clock_t start, end;
    double time;
    int arrSize = 10000;
    int i=0;
    
    FILE *fptr;

    fptr = fopen("qsVmsVhsItr.dat", "w");
    if(fptr == NULL)
    {
      printf("Error!");
      exit(1);
    }

    while(arrSize<MAX_ARR_SIZE)
    {
        // take avg time for five runs
        double time1=0,time2=0,time3=0;
        
        for(i=0;i<ITERATION_FOR_AVG;i++)
        {
            int* arr = generateRandArr(arrSize);
            
            start = clock();
            quickSortItr(arr,arrSize);

            end = clock();
            time = ((double) (end - start)) / CLOCKS_PER_SEC;
            time1 += time;

            #ifdef DEBUG
            //assert(verifySorted(arr,arrSize));
            #endif
            free(arr);
        }
        
        for(i=0;i<ITERATION_FOR_AVG;i++)
        {
            int* arr = generateRandArr(arrSize);
            
            start = clock();
            mergeSortIter(arr,0,arrSize-1);
            end = clock();
            time = ((double) (end - start)) / CLOCKS_PER_SEC;
            time2 += time;

            #ifdef DEBUG
            //assertassert(verifySorted(arr,arrSize));
            #endif
            free(arr);
        }
        
        for(i=0;i<ITERATION_FOR_AVG;i++)
        {
            int* arr = generateRandArr(arrSize);
            
            start = clock();
            heapSortIter(arr,arrSize);
            end = clock();
            time = ((double) (end - start)) / CLOCKS_PER_SEC;
            time3 += time;

            #ifdef DEBUG
            //assert(verifySorted(arr,arrSize));
            #endif
            free(arr);
        }
        
        time1 = time1/ITERATION_FOR_AVG;
        time2 = time2/ITERATION_FOR_AVG;
        time3 = time3/ITERATION_FOR_AVG;
        
        // write in a file for plotting purpose
        fprintf(fptr,"%lf %lf %lf %d\n",time1,time2,time3,arrSize);
        #ifdef DEBUG
        printf("size=%d quicksortItr=%lf mergeSortItr = %lf heapSortItr=%lf\n",arrSize,time1,time2,time3);
        #endif
        
        arrSize+=INCREMENT_SIZE;
    }
    fclose(fptr);

}

void qsVmsVhsVIsItr()
{
    clock_t start, end;
    double time;
    int arrSize = 10000;
    int i=0;
    
    FILE *fptr;

    fptr = fopen("foursort.dat", "w");
    if(fptr == NULL)
    {
      printf("Error!");
      exit(1);
    }

    while(arrSize<100001)
    {
        // take avg time for five runs
        double time1=0,time2=0,time3=0,time4 = 0;
        
        for(i=0;i<ITERATION_FOR_AVG;i++)
        {
            int* arr = generateRandArr(arrSize);
            
            start = clock();
            quickSortItr(arr,arrSize);

            end = clock();
            time = ((double) (end - start)) / CLOCKS_PER_SEC;
            time1 += time;

            #ifdef DEBUG
            //assert(verifySorted(arr,arrSize));
            #endif
            free(arr);
        }
        
        for(i=0;i<ITERATION_FOR_AVG;i++)
        {
            int* arr = generateRandArr(arrSize);
            
            start = clock();
            mergeSortIter(arr,0,arrSize-1);
            end = clock();
            time = ((double) (end - start)) / CLOCKS_PER_SEC;
            time2 += time;

            #ifdef DEBUG
            //assertassert(verifySorted(arr,arrSize));
            #endif
            free(arr);
        }
        
        for(i=0;i<ITERATION_FOR_AVG;i++)
        {
            int* arr = generateRandArr(arrSize);
            
            start = clock();
            heapSortIter(arr,arrSize);
            end = clock();
            time = ((double) (end - start)) / CLOCKS_PER_SEC;
            time3 += time;

            #ifdef DEBUG
            //assert(verifySorted(arr,arrSize));
            #endif
            free(arr);
        }

        for(i=0;i<ITERATION_FOR_AVG;i++)
        {
            int* arr = generateRandArr(arrSize);
            
            start = clock();
            insertionSort(arr,arrSize);
            end = clock();
            time = ((double) (end - start)) / CLOCKS_PER_SEC;
            time4 += time;

            #ifdef DEBUG
            //assert(verifySorted(arr,arrSize));
            #endif
            free(arr);
        }
        
        time1 = time1/ITERATION_FOR_AVG;
        time2 = time2/ITERATION_FOR_AVG;
        time3 = time3/ITERATION_FOR_AVG;
        time4 = time4/ITERATION_FOR_AVG;
        
        // write in a file for plotting purpose
        fprintf(fptr,"%lf %lf %lf %lf %d\n",time1,time2,time3,time4,arrSize);
        #ifdef DEBUG
        printf("size=%d quicksortItr=%lf mergeSortItr = %lf heapSortItr=%lf InsSort=%lf\n",arrSize,time1,time2,time3,time4);
        #endif
        
        arrSize+=INCREMENT_SIZE;
    }
    fclose(fptr);

}
//Mergesort recursive vs iterative



int main()
{
    /*
    quickSort(arr,0,sizeof(arr)/sizeof(int)-1);
    */
    qsVqsItr();
    printf("Done\n");
    msVmsItr();printf("Done\n");
    hsVhsItr();printf("Done\n");
    qsVmsVhs();printf("Done\n");
    qsVmsVhsItr();printf("Done\n");
    
    qsVmsVhsVIsItr();
}
