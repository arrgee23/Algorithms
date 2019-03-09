#include <stdio.h>
#include <stdlib.h>

#define BIG_INT 99999999

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

int main()
{
    int arr[] = {1,2};
    quickSort(arr,0,sizeof(arr)/sizeof(int)-1);
    //quickSortIter(arr,0,sizeof(arr)/sizeof(int)-1);
    printArr(arr,sizeof(arr)/sizeof(int));

}