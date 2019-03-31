/*
* Rahul Gautam
* Indian Statistical Institute
* Comparison of heapsort, mergesort, quicksort
* and their iterative versions
* 09th Mar 2019
*/

#include "functions.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>


int min(int a,int b)
{
    return a>b?b:a;
}

void printArr(int* arr,int n)
{
    int i =0;
    printf("\n");
    for(i=0;i<n;i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
}
void printRange(int* arr,int l,int r)
{
    int i =0;
    printf("\n");
    for(i=l;i<=r;i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
}

// returns pivot index
int partition(int *arr,int l,int r,TRIPLE* t)
{
    int pivot = arr[r];
    int tmp =0;
    int i=l;
    int idx = l;
    //printf("B: ");printRange(arr,l,r);
    for(i=l;i<r;i++)
    {
        t->compCount++;
        if(arr[i]<=pivot)
        {   //swap
            t->swapCount++;
            tmp = arr[idx];
            arr[idx++] = arr[i];
            arr[i] = tmp;
        }
    }
    // finally swap pivot and last
    t->swapCount++;
    arr[r] = arr[idx];
    arr[idx] = pivot;
    //printf("A: ");printRange(arr,l,r);
    
    return idx;
}

int push(int* stack,int* top,int n)
{
    stack[(*top)++] = n;
}

int pop(int* stack,int* top)
{
    int n = stack[--(*top)];
    return n;
}

int peek(int* stack,int top)
{
    return stack[--top];
}

void quickSortItr(int* arr, int len,TRIPLE* t)
{
    int* stack  = (int*) malloc(len* sizeof(int));
    int top = 0;
    int i=0;
    
    push(stack,&top,0);
    push(stack,&top,len-1);
    
    int popIdx,peekIdx,pivotIdx;
    
    // invariant: top two will contain the unsorted part intervals ascending ex: 0..3, 5..7
    for(i=0;i<len;i++)
    {
        //printArr(stack,top);
        popIdx = pop(stack,&top);
        peekIdx = peek(stack,top);

        pivotIdx = partition(arr,peekIdx,popIdx,t);

       
        t->compCount++;
        if(pivotIdx==popIdx)
        {
            t->compCount++;
            if(pivotIdx!=peekIdx)
            {
                // push pivot - 1
                push(stack,&top,pivotIdx-1);
            }
            else
            {
                // pop
                pop(stack,&top);
            }
            
        }else if(pivotIdx==peekIdx) // pivot = 11, peek = 11
        {
            t->compCount++;
            if(pivotIdx!=popIdx) //  pop = 98
            {
                // pop
                pop(stack,&top);

                // push pivot + 1
                push(stack,&top,pivotIdx+1);
                // push popIdx
                push(stack,&top,popIdx);
            }
            else
            {
                // pop
                pop(stack,&top);
            }
        }else  // pivot != peek or pop
        {
            push(stack,&top,pivotIdx-1);
            push(stack,&top,pivotIdx+1);
            push(stack,&top,popIdx);
        }
        
    }
    //free(stack);
}

/* Function to sort an array using insertion sort*/
void insertionSort(int arr[], int n) 
{ 
   int i, key, j; 
   for (i = 1; i < n; i++) 
   { 
       key = arr[i]; 
       j = i-1; 
  
       /* Move elements of arr[0..i-1], that are 
          greater than key, to one position ahead 
          of their current position */
       while (j >= 0 && arr[j] > key) 
       { 
           arr[j+1] = arr[j]; 
           j = j-1; 
       } 
       arr[j+1] = key; 
   } 
} 

void quickSort(int* arr,int l,int r,TRIPLE* t)
{
    t->compCount++;
    if(l<r)
    {
        int i = partition(arr,l,r,t);
        quickSort(arr,l,i-1,t);
        quickSort(arr,i+1,r,t);
    }
}


void merge(int* arr,int l,int m,int r,TRIPLE* t)
{
    //printf("%d %d %d\n",l,m,r);
    int lSize = m-l+1+1;
    int rSize = r-m+1;

    int* lArray = malloc(lSize*sizeof(int));
    int* rArray = malloc(rSize*sizeof(int));

    // copy two arrays 
    int i=0;
    for(i=0;i<lSize;i++)
    {
        lArray[i] = arr[l+i];
        t->swapCount++;
    }

    for(i=0;i<rSize;i++)
    {
        rArray[i] = arr[m+1+i];
        t->swapCount++;
    }
    // add sentinel elements to the end
    lArray[lSize-1] = BIG_INT;
    rArray[rSize-1] = BIG_INT;

    // copy the elements back to original array in sorted order
    int count = 0;
    int lptr = 0;
    int rptr = 0;
    while(count<r-l+1)
    {   
        t->compCount++;
        t->compCount++;
        if(lArray[lptr]<rArray[rptr])
        {
            arr[l+count] = lArray[lptr++];
        }
        else
        {
            arr[l+count] = rArray[rptr++];
        }
        
        count++;
    }

}

void mergeSortIter(int* arr,int l, int r,TRIPLE* t)
{
    int mergeSize = 1; 
    int temp=l;
    while(mergeSize<r-l+1)
    {
        t->compCount++;
        // merge all "mergeSize" arrrays
        temp = l;
        while(temp<r)
        {
            t->compCount++;
            // for 2 min calls
            t->compCount+=2;
            merge(arr,temp,min(r,temp+mergeSize-1),min(r,temp+2*mergeSize-1),t);
            temp = temp+2*mergeSize;
        }

        mergeSize*=2;
    }
}

void mergeSort(int* arr,int l, int r,TRIPLE* t)
{
    /*
    if(l!=r)
        printf("%d %d\n",l,r);
    */
   t->compCount++;
    if(l<r)
    {
        int m = (l+r)/2;
        mergeSort(arr,l,m,t);
        mergeSort(arr,m+1,r,t);

        merge(arr,l,m,r,t);
    }
}



int* generateRandArr(int size)
{
    srand(time(NULL));
    
    int i=0;
    int* arr = (int*)malloc(size*sizeof(int));
    assert(arr!=NULL);
    for(i=0;i<size;i++){
        arr[i]=(rand()%100000);
    }
    return arr;
}



int verifySorted(int* arr,int n)
{
    for(int i=0;i<n-1;i++)
    {
        if(arr[i]>arr[i+1])
            return 0;
    }
    return 1;
}



int left(int i,int len)
{
    
	return i*2+1>=len?-1 : i*2+1;
}
int right(int i,int len){
	return i*2+2>=len ? -1: i*2+2;
}

int parent(int i){
	return (i-1)/2 >= 0 ? (i-1)/2: 0;
}

	 


void siftDown(int* a,int i,int len,TRIPLE* t) {
	// replaces ith node with the max between its children and itself
	// condition of heap is parent>= child
	int l = left(i,len);
	int r = right(i,len);
	
	int largestIndex=i;
	t->compCount++;
    if(l!=-1 && a[l]>a[largestIndex])
		largestIndex = l;
	
    t->compCount++;
	if(r!=-1 && a[r]>a[largestIndex])
		largestIndex = r;
		
	// swap
    t->compCount++;
	if(largestIndex != i){
        t->swapCount++;
		int temp = a[i];
		a[i] = a[largestIndex];
		a[largestIndex] = temp;
		siftDown(a, largestIndex,len,t);
	}
}
// moves the element conseptually high in the tree if suitable
void siftUp(int* arr,int i,int len,TRIPLE* t)
{
    int temp = -1;
    // max heap
    
    while(arr[i]>=arr[parent(i)])
    {
        t->compCount++;
        //swap
        t->swapCount++;
        temp = arr[i];
        arr[i] = arr[parent(i)];
        arr[parent(i)] = temp;

        i = parent(i);
        // we have reached the top
        t->compCount++;
        if(i==0)
            break;
    }
}

int extractMax(int* arr,int len,TRIPLE* t)
{
    int ret = -1;
    t->compCount++;
    if(len>0)
    {
        t->swapCount++;

        ret = arr[0];
        arr[0] = arr[len-1];
        siftDown(arr,0,len-1,t);
    }
    return ret;
}

void heapSort(int* a,int len,TRIPLE* t) {
    // at each iteration extract the max item from the heap
	maxHeapify(a,len,t);
    int i;
    //printArr(a,len);
    // run n-1 times
    int save = len;
    for(i=0;i<save-1;i++)
    {
        int k = extractMax(a,len,t);
        len = len-1;
        a[save-1-i] = k;
        t->swapCount++;
        //printArr(a,save);
    }

}

void maxHeapify(int* a,int len,TRIPLE* t) {
	int i=0;
    for (i = (len)/2; i >=0; i--) {
		siftDown(a,i,len,t);
	}
}

/********************************* iterative implementation below ******************************/
void siftDownIter(int* a,int i,int len,TRIPLE* t) {
	// replaces ith node with the max between its children and itself
	// condition of heap is parent>= child
	while(1)
    {
        int l = left(i,len);
        int r = right(i,len);
        
        int largestIndex=i;
        t->compCount++;
        if(l!=-1 && a[l]>a[largestIndex])
            largestIndex = l;
        
        t->compCount++;
        if(r!=-1 && a[r]>a[largestIndex])
            largestIndex = r;
            
        // swap
        t->compCount++;
        if(largestIndex == i)
            break;
        t->swapCount++;
        int temp = a[i];
        a[i] = a[largestIndex];
        a[largestIndex] = temp;
        i = largestIndex;
	}
}
/* moves the element conseptually high in the tree if suitable
void siftUpIter(int* arr,int i,int len)
{
    int t = -1;
    // max heap
    while(arr[i]>=arr[parent(i)])
    {
        //swap
        int t = arr[i];
        arr[i] = arr[parent(i)];
        arr[parent(i)] = t;

        i = parent(i);
        // we have reached the top
        if(i==0)
            break;
    }
}
*/

int extractMaxIter(int* arr,int len,TRIPLE* t)
{
    int ret = -1;
    t->compCount++;
    if(len>0)
    {
        t->swapCount++;
        ret = arr[0];
        arr[0] = arr[len-1];
        siftDownIter(arr,0,len-1,t);
    }
    return ret;
}

void maxHeapifyIter(int* a,int len,TRIPLE* t) {
	int i=0;
    for (i = (len)/2; i >=0; i--) {
		siftDownIter(a,i,len,t);
	}
}

void heapSortIter(int* a,int len,TRIPLE* t) {
    // at each iteration extract the max item from the heap
	maxHeapifyIter(a,len,t);
    int i;
    //printArr(a,len);
    // run n-1 times
    int save = len;
    for(i=0;i<save-1;i++)
    {
        int k = extractMaxIter(a,len,t);
        t->swapCount++;
        len = len-1;
        a[save-1-i] = k;
        //printArr(a,save);
    }

}

// main interface function
TRIPLE quickSortIF(int* arr,int l,int r)
{
    TRIPLE* t= (TRIPLE*)calloc(1,sizeof(TRIPLE));
    clock_t start, end;
    double time;

    start = clock();
    quickSort(arr,l,r,t);
    end = clock();

    time = ((double) (end - start)) / CLOCKS_PER_SEC;

    t->time =  time;

    return *t;
}

TRIPLE quickSortIterativeIF(int* arr,int l,int r)
{
    TRIPLE* t= (TRIPLE*)calloc(1,sizeof(TRIPLE));
    clock_t start, end;
    double time;

    start = clock();
    quickSortItr(arr,r+1,t);
    end = clock();

    time = ((double) (end - start)) / CLOCKS_PER_SEC;

    t->time =  time;
    return *t;
}
TRIPLE mergeSortIF(int* arr,int l,int r)
{
    TRIPLE* t= (TRIPLE*)calloc(1,sizeof(TRIPLE));
    clock_t start, end;
    double time;

    start = clock();
    mergeSort(arr,l,r,t);
    end = clock();

    time = ((double) (end - start)) / CLOCKS_PER_SEC;

    t->time =  time;
    return *t;
}
TRIPLE mergeSortIterativeIF(int* arr,int l,int r)
{
    TRIPLE* t= (TRIPLE*)calloc(1,sizeof(TRIPLE));
    clock_t start, end;
    double time;

    start = clock();
    mergeSortIter(arr,l,r,t);
    end = clock();

    time = ((double) (end - start)) / CLOCKS_PER_SEC;

    t->time =  time;
    return *t;
}
TRIPLE heapSortIF(int* arr,int l,int r)
{
    TRIPLE* t= (TRIPLE*)calloc(1,sizeof(TRIPLE));
    clock_t start, end;
    double time;

    start = clock();
    heapSort(arr,r+1,t);
    end = clock();

    time = ((double) (end - start)) / CLOCKS_PER_SEC;

    t->time =  time;
    return *t;
}
TRIPLE heapSortIterativeIF(int* arr,int l,int r)
{
    TRIPLE* t= (TRIPLE*)calloc(1,sizeof(TRIPLE));
    clock_t start, end;
    double time;

    start = clock();
    heapSortIter(arr,r+1,t);
    end = clock();

    time = ((double) (end - start)) / CLOCKS_PER_SEC;

    t->time =  time;
    return *t;
}