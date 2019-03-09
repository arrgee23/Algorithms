#include "functions.h"

void qsVqsItr()
{

}

void hsVhsItr()
{
    
}

void qsVmsVhs()
{

}

void qsVmsVhsItr()
{

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
    int arr[] = {1,2};
    //quickSort(arr,0,sizeof(arr)/sizeof(int)-1);
    //quickSortIter(arr,0,sizeof(arr)/sizeof(int)-1);
    //printArr(arr,sizeof(arr)/sizeof(int));

    msVmsItr();

    int[] a = {0,64,5,90,78,12,-5,39};
		maxHeapify(a);
		heapSort(a);

}
