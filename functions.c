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
int partition(int *arr,int l,int r)
{
    int pivot = arr[r];
    int t =0;
    int i=l;
    int idx = l;
    //printf("B: ");printRange(arr,l,r);
    for(i=l;i<r;i++)
    {
        if(arr[i]<=pivot)
        { //swap
            t = arr[idx];
            arr[idx++] = arr[i];
            arr[i] = t;
        }
    }
    // finally swap pivot and 
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

void quickSortItr(int* arr, int len)
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

        pivotIdx = partition(arr,peekIdx,popIdx);
        if(pivotIdx==popIdx)
        {
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
    free(stack);
}

void quickSort(int* arr,int l,int r)
{
    if(l<r)
    {
        int i = partition(arr,l,r);
        quickSort(arr,l,i-1);
        quickSort(arr,i+1,r);
    }
}

void merge(int* arr,int l,int m,int r)
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
    }

    for(i=0;i<rSize;i++)
    {
        rArray[i] = arr[m+1+i];
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

int min(int a,int b)
{
    return a>b?b:a;
}
void mergeSortIter(int* arr,int l, int r)
{
    int mergeSize = 1; 
    int temp=l;
    while(mergeSize<r-l+1)
    {
        // merge all "mergeSize" arrrays
        temp = l;
        while(temp<r)
        {
            merge(arr,temp,min(r,temp+mergeSize-1),min(r,temp+2*mergeSize-1));
            temp = temp+2*mergeSize;
        }

        mergeSize*=2;
    }
}

void mergeSort(int* arr,int l, int r)
{
    /*
    if(l!=r)
        printf("%d %d\n",l,r);
    */
    if(l<r)
    {
        int m = (l+r)/2;
        mergeSort(arr,l,m);
        mergeSort(arr,m+1,r);

        merge(arr,l,m,r);
    }
}



int* generateRandArr(int size)
{
    srand(time(NULL));
    
    int i=0;
    int* arr = (int*)malloc(size*sizeof(int));
    assert(arr!=NULL);
    for(i=0;i<size;i++){
        arr[i]=(rand()%101);
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

	 


void siftDown(int* a,int i,int len) {
	// replaces ith node with the max between its children and itself
	// condition of heap is parent>= child
	int l = left(i,len);
	int r = right(i,len);
	
	int largestIndex=i;
	if(l!=-1 && a[l]>a[largestIndex])
		largestIndex = l;
	
	if(r!=-1 && a[r]>a[largestIndex])
		largestIndex = r;
		
	// swap
	if(largestIndex != i){
		int temp = a[i];
		a[i] = a[largestIndex];
		a[largestIndex] = temp;
		siftDown(a, largestIndex,len);
	}
}
// moves the element conseptually high in the tree if suitable
void siftUp(int* arr,int i,int len)
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

int extractMax(int* arr,int len)
{
    int ret = -1;
    if(len>0)
    {
        ret = arr[0];
        arr[0] = arr[len-1];
        siftDown(arr,0,len-1);
    }
    return ret;
}

void heapSort(int* a,int len) {
    // at each iteration extract the max item from the heap
	maxHeapify(a,len);
    int i;
    //printArr(a,len);
    // run n-1 times
    int save = len;
    for(i=0;i<save-1;i++)
    {
        int k = extractMax(a,len);
        len = len-1;
        a[save-1-i] = k;
        //printArr(a,save);
    }

}

void maxHeapify(int* a,int len) {
	int i=0;
    for (i = (len)/2; i >=0; i--) {
		siftDown(a,i,len);
	}
}

/********************************* iterative implementation below ******************************/
void siftDownIter(int* a,int i,int len) {
	// replaces ith node with the max between its children and itself
	// condition of heap is parent>= child
	while(1)
    {
        int l = left(i,len);
        int r = right(i,len);
        
        int largestIndex=i;
        if(l!=-1 && a[l]>a[largestIndex])
            largestIndex = l;
        
        if(r!=-1 && a[r]>a[largestIndex])
            largestIndex = r;
            
        // swap
        if(largestIndex == i)
            break;
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

int extractMaxIter(int* arr,int len)
{
    int ret = -1;
    if(len>0)
    {
        ret = arr[0];
        arr[0] = arr[len-1];
        siftDownIter(arr,0,len-1);
    }
    return ret;
}

void maxHeapifyIter(int* a,int len) {
	int i=0;
    for (i = (len)/2; i >=0; i--) {
		siftDownIter(a,i,len);
	}
}

void heapSortIter(int* a,int len) {
    // at each iteration extract the max item from the heap
	maxHeapifyIter(a,len);
    int i;
    //printArr(a,len);
    // run n-1 times
    int save = len;
    for(i=0;i<save-1;i++)
    {
        int k = extractMaxIter(a,len);
        len = len-1;
        a[save-1-i] = k;
        //printArr(a,save);
    }

}