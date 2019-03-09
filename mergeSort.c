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

void merge(int* arr,int l,int m,int r)
{
    printf("%d %d %d\n",l,m,r);
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
            merge(arr,temp,temp+mergeSize-1,min(r,temp+2*mergeSize-1));
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

int main()
{
    int arr[] = {21,-3,4};
    //mergeSort(arr,0,sizeof(arr)/sizeof(int)-1);
    mergeSortIter(arr,0,sizeof(arr)/sizeof(int)-1);
    printArr(arr,sizeof(arr)/sizeof(int));

}