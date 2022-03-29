#include <iostream>
#include <ctime>
#include <fstream>
#include <chrono>
#include <stdlib.h>
#include <cstdint>
#include <thread>

#define MAX_ARRAY_SIZE 1000000
#define MAX_SORT_TIME 100000000
#define ITERATIONS_COUNT 5

using namespace std;

void merge(int *a, int left, int middle, int right)
{
    int subArray1 = middle - left + 1;
    int subArray2 = right - middle;
    int *leftArray = new int[subArray1];
    int *rightArray = new int[subArray2];

    for (int i = 0; i < subArray1; i++)
    {
        leftArray[i] = a[left + i];
    }
    for (int i = 0; i < subArray2; i++)
    {
        rightArray[i] = a[middle + 1 + i];
    }

    int indexSubArray1 = 0;
    int indexSubArray2 = 0;
    int indexMerged = left;

    while ((indexSubArray1 < subArray1) && (indexSubArray2 < subArray2))
    {
        if (leftArray[indexSubArray1] <= rightArray[indexSubArray2])
        {
            a[indexMerged] = leftArray[indexSubArray1];
            indexSubArray1++;
        }
        else
        {
            a[indexMerged] = rightArray[indexSubArray2];
            indexSubArray2++;
        }
        indexMerged++;
    }
    while (indexSubArray1 < subArray1) {
        a[indexMerged] = leftArray[indexSubArray1];
        indexSubArray1++;
        indexMerged++;
    }
    while (indexSubArray2 < subArray2) {
        a[indexMerged] = rightArray[indexSubArray2];
        indexSubArray2++;
        indexMerged++;
    }
}
void mergeRecurs(int *a, int begin, int end)
{
    if (begin >= end)
    {
        return;
    }
    int middle = begin + (end - begin) / 2;
    mergeRecurs(a, begin, middle); // завести дополнительную мержевскую функцию которая будет работать как мерж и рекурсивно вызываться
    mergeRecurs(a, middle+1, end); // если это сработает, то я буду в шоке
    merge(a, begin, middle, end);
}
void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}
void reheap(int *a, int _size, int i)
{
    bool done = false;
    int T = a[i];
    int parent = i;
    int child = 2*(i+1) - 1;
    while ((child < _size) && !done)
    {
        if (child < _size -1)
        {
            if (a[child] >= a[child+1])
            {
                child+=1;
            }
        }
        if (T < a[child])
        {
            done = true;
        }
        else
        {
            a[parent] = a[child];
            parent = child;
            child = 2*(parent+1)-1;
        }
    }
    a[parent] = T;
}
void inverheap(int *a, int _size, int i)
{
    bool done = false;
    int T = a[_size-1-i];
    int parent = i;
    int child = 2*(i+1)-1;
    while ((child<_size) && !done)
    {
        if (child<_size-1)
        {
            if (a[_size-1-child] <= a[_size-1-(child+1)])
            {
                child+=1;
            }
        }
        if (T > a[_size-1-child])
        {
            done = true;
        }
        else
        {
            a[_size-1-parent] = a[_size-1-child];
            parent = child;
            child = 2*(parent+1)-1;
        }
    }
    a[_size-1-parent] = T;
}

void quickSort(int* a, int _size)
{
    int last = _size-1;
    int first = 0;
    if (first < last)
    {
        int left = first;
        int right = last;
        int middle = a[_size / 2];

        do
        {
            while (a[left] < middle)
            {
                left++;
            }
            while (a[right] > middle)
            {
                right--;
            }

            if (left <= right)
            {
                int tmp = a[left];
                a[left] = a[right];
                a[right] = tmp;
                left++;
                right--;
            }
        } while (left <= right);
        if (right > 0)
        {
            quickSort(a, right+1);
        }
        if (left < _size)
        {
            quickSort(&a[left], _size-left);
        }
    }
}
void bubbleSort(int* a, int _size)
{
    for (int i = 0; i < _size; i++)
    {
        for (int j = i + 1; j < _size; j++)
        {
            if (a[i] > a[j])
            {
                int temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
}
void mergeSort(int* a, int _size)
{
    int begin = 0;
    int end = _size-1;
    //int middle = begin + (end - begin) / 2;
    mergeRecurs(a, begin, end);

}
void insertionSort(int* a,int _size){
    int counter=0;
    for(int i=1;i<_size;i++){
        for(int j=i; j>0 && a[j-1]>a[j];j--){
            counter++;
            int tmp=a[j-1];
            a[j-1]=a[j];
            a[j]=tmp;
        }
    }
}
void selectionSort(int* a, int _size)
{
    int min_index;
    for (int i = 0; i < _size-1; i++)
    {
        min_index = i;
        for (int j = i+1; j < +_size; j++)
        {
            if (a[j] < a[min_index])
            {
                min_index = j;
            }
            swap(&a[min_index], &a[i]);
        }
    }
}
void gnomeSort(int* a, int _size)
{
    int index = 0;
    while (index < _size)
    {
        if (index == 0)
        {
            index++;
        }
        if (a[index] >= a[index-1])
        {
            index++;
        }
        else
        {
            swap(a[index], a[index-1]);
            index--;
        }
    }
    return;
}
void hybridSort(int* a, int _size)
{
    std::thread thread1([a, _size]
    {
        for (int i = _size-1; i >= 0; i--)
        {
            reheap(a, _size, i);
        }
    });
    std::thread thread2([a, _size]
    {
        for (int i = _size-1; i >= 0; i--)
        {
            inverheap(a, _size, i);
        }
    });
    thread1.join();
    thread2.join();

    for (int j = 1; j < _size; j++) {
        int T = a[j];
        int i = j - 1;
        while (i >= 0 && a[i] > T) {
            a[i + 1] = a[i];
            i -= 1;
        }
        a[i + 1] = T;
    }
}

void randomFill(int* a, int _size)
{
    srand(time(nullptr));
    for (int i = 0; i < _size; i++)
        a[i] = abs(rand());
}

bool sortCompleted[7] = {false};

void (*pSort[7])(int *, int) = {quickSort, bubbleSort, mergeSort, insertionSort, selectionSort, gnomeSort, hybridSort};

const char* fileNames[7] = {"qsort.txt", "bubsort.txt", "mergesort.txt", "insertionsort.txt", "selectionSort.txt", "gnomeSort.txt", "hybridSort.txt"};
ofstream files[7];

void to_gnuplot()
{
    FILE* plot;

    if ((plot = _popen("C:\\gnuplot\\bin\\gnuplot.exe", "w")) == NULL)
    {
        fprintf(stderr, "Error opening pipe to gnuplot.\n");
        exit(1);
    }

    for (int i = 0; i < 7; i++)
    {
        fprintf(plot, "set terminal windows ");
        fprintf(plot, to_string(i).c_str());
        fprintf(plot, "\nset title \'");
        fprintf(plot, fileNames[i]);
        fprintf(plot, "\'\n");
        fprintf(plot, "set xlabel \"Number of a elements\"\nset ylabel \"Time (ns)\"\n");
        fprintf(plot, "plot \'");
        fprintf(plot, fileNames[i]);
        fprintf(plot, "\' using 1:2 with linespoints\n");
        //fprintf(plot, "set logscale x 10\n");

        fflush(plot);
    }

    fprintf(plot, "set terminal windows 9\n");
    fprintf(plot, "set xlabel \"Number of elements\"\n set ylabel \"Time (ns)\"\n");
    fprintf(plot, "set title \"SORTING ALGORITHMS\"\n");

    fprintf(plot, "plot \'");
    fprintf(plot, fileNames[0]);
    fprintf(plot, "\' using 1:2 with linespoints\n");
    fprintf(plot, "set logscale x 10\n");
    for (int i = 1; i < 7; i++)
    {

        fprintf(plot, "replot \'");
        fprintf(plot, fileNames[i]);
        fprintf(plot, "\' using 1:2 with linespoints\n");
        fprintf(plot, "set logscale x 10\n");

    }
    fflush(plot);

    system("pause");

    fprintf(plot, "exit\n");

    _pclose(plot);
}


int main(int argc, char* argv[])
{
    for (int i = 0; i < 7; i++)
    {
        files[i].open(fileNames[i], ios::out);
    }
    int *randArray = new int[MAX_ARRAY_SIZE];
    randomFill(randArray, MAX_ARRAY_SIZE);

    int* my_array;

    for (int size = 1000; size < MAX_ARRAY_SIZE; size+=1000)
    {
        my_array = new int[size];

        for (int i = 0; i <= 6; i++)
        {
            if (sortCompleted[i])
            {
                continue;
            }

            memcpy(my_array, randArray, size * sizeof(int));

            files[i] << size << "\t";
            unsigned long long time = 0;
            for (int j = 0; j < ITERATIONS_COUNT; ++j)
            {
                auto begin = chrono::high_resolution_clock::now();
                pSort[i](my_array, size);
                auto end = chrono::high_resolution_clock::now();
                time += chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
            }
            time /= ITERATIONS_COUNT;
            if (time >= MAX_SORT_TIME)
            {
                sortCompleted[i] = true;
            }
            files[i] << time << "\n";
        }
        delete[] my_array;
    }
    for (int i = 0; i < 7; i++)
    {
        files[i].close();
    }

    to_gnuplot();
    return 0;
}