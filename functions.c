#include "functions.h"
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

int left(int i)
{
	return i*2;
}
int right(int i){
	return i*2+1;
}

int parent(int i){
	return i/2;
}

	 

void heapSort(int* a) {
    // at each iteration extract the max item from the heap
		
}

void maxHeapify(int* a,int len) {
	int i=0;
    for (i = (len-1)/2; i >=1; i--) {
		siftDown(a,i,len);
	}
}

void siftDown(int* a,int i,int len) {
	// replaces ith node with the max between its children and itself
	// condition of heap is parent>= child
	int l = left(i);
	int r = right(i);
	
	int largestIndex=i;
	if(l<len && a[l]>a[largestIndex])
		largestIndex = l;
	
	if(r<len && a[r]>a[largestIndex])
		largestIndex = r;
		
	// swap
	if(largestIndex != i){
		int temp = a[i];
		a[i] = a[largestIndex];
		a[largestIndex] = temp;
		siftDown(a, largestIndex,len);
	}
}