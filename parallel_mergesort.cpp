//Parallel Merge sort

#include<iostream>
#include<stdlib.h>
#include<omp.h>

using namespace std;

void merge(int a[], int l, int m, int r)
{
    int temp[100], i = l, j = m + 1, k = 0;

    while(i <= m && j <= r)
    {
        if(a[i] < a[j])
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
    }

    while(i <= m)
        temp[k++] = a[i++];

    while(j <= r)
        temp[k++] = a[j++];

    for(i = l, k = 0; i <= r; i++, k++)
        a[i] = temp[k];
}

void mergesort(int a[], int l, int r)
{
    if(l < r)
    {
        int m = (l + r) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            mergesort(a, l, m);

            #pragma omp section
            mergesort(a, m + 1, r);
        }

        merge(a, l, m, r);
    }
}

int main()
{
    int n;

    cout << "Enter number of elements: ";
    cin >> n;

    int a[n];

    cout << "Enter elements: ";

    for(int i = 0; i < n; i++)
        cin >> a[i];

    mergesort(a, 0, n - 1);

    cout << "Sorted array: ";

    for(int i = 0; i < n; i++)
        cout << a[i] << " ";

    return 0;
}



//g++ parallel_mergesort.cpp -fopenmp -o mergesort
//./mergesort
