#include "functions.h"

void qsVqsItr()
{

}
// heapsort normal vs iterative
void hsVhsItr()
{
    clock_t start, end;
    double time;
    int arrSize = 100;
    int i=0;
    
    
    while(arrSize<MAX_ARR_SIZE)
    {
        // take avg time for five runs
        double time1=0,time2=0;
        
        for(i=0;i<ITERATION_FOR_AVG;i++)
        {
            int* arr = generateRandArr(arrSize);
            
            start = clock();
            heapSort(arr,arrSize);

            end = clock();
            time = ((double) (end - start)) / CLOCKS_PER_SEC;
            time1 += time;

            #ifdef DEBUG
            assert(verifySorted(arr,arrSize));
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
            assert(verifySorted(arr,arrSize));
            #endif
            free(arr);
        }
        
        
        time1 = time1/ITERATION_FOR_AVG;
        time2 = time2/ITERATION_FOR_AVG;

        #ifdef DEBUG
        printf("size=%d heapSort=%lf heapSortIterative=%lf\n",arrSize,time1,time2);
        #endif
        
        arrSize*=10;
    }
    
   /*
    int* arr = generateRandArr(15);
    printArr(arr,15);
    heapSort(arr,15);
    printArr(arr,15);
    */

}

void qsVmsVhs()
{

}

// quicksort vs mergesort vs heapsort.. all iterative
void qsVmsVhsItr()
{
    clock_t start, end;
    double time;
    int arrSize = 100;
    int i=0;
    
    
    while(arrSize<MAX_ARR_SIZE)
    {
        // take avg time for five runs
        double time1=0,time2=0;
        
        for(i=0;i<ITERATION_FOR_AVG;i++)
        {
            int* arr = generateRandArr(arrSize);
            
            start = clock();
            quickSortItr(arr,arrSize);

            end = clock();
            time = ((double) (end - start)) / CLOCKS_PER_SEC;
            time1 += time;

            #ifdef DEBUG
            assert(verifySorted(arr,arrSize));
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
            assert(verifySorted(arr,arrSize));
            #endif
            free(arr);
        }
        
        
        time1 = time1/ITERATION_FOR_AVG;
        time2 = time2/ITERATION_FOR_AVG;

        #ifdef DEBUG
        printf("size=%d quicksortIterative=%lf heapSortIterative=%lf\n",arrSize,time1,time2);
        #endif
        
        arrSize*=10;
    }
    
   /*
    int* arr = generateRandArr(15);
    printArr(arr,15);
    heapSort(arr,15);
    printArr(arr,15);
    */

}
//Mergesort recursive vs iterative
void msVmsItr()
{
    clock_t start, end;
    double time;
    int arrSize = 100;
    int i=0;
    
    while(arrSize<MAX_ARR_SIZE)
    {
        // take avg time for five runs
        double time1=0,time2=0;
        
        for(i=0;i<ITERATION_FOR_AVG;i++)
        {
            int* arr = generateRandArr(arrSize);
            
            start = clock();
            mergeSort(arr,0,arrSize);
            end = clock();
            time = ((double) (end - start)) / CLOCKS_PER_SEC;
            time1 += time;

            #ifdef DEBUG
            assert(verifySorted(arr,arrSize));
            #endif
            free(arr);
        }

        for(i=0;i<ITERATION_FOR_AVG;i++)
        {
            int* arr = generateRandArr(arrSize);
            
            start = clock();
            mergeSortIter(arr,0,arrSize);
            end = clock();
            time = ((double) (end - start)) / CLOCKS_PER_SEC;
            time2 += time;

            #ifdef DEBUG
            assert(verifySorted(arr,arrSize));
            #endif
            free(arr);
        }
        time1 = time1/ITERATION_FOR_AVG;
        time2 = time2/ITERATION_FOR_AVG;

        #ifdef DEBUG
        printf("size=%d mergeSort=%lf mergesortRecursive=%lf\n",arrSize,time1,time2);
        #endif
        
        arrSize*=10;
    }
}


int main()
{
    //quickSort(arr,0,sizeof(arr)/sizeof(int)-1);
    qsVmsVhsItr();
    //printArr(arr,sizeof(arr)/sizeof(int));

    hsVhsItr();

    
		

}
