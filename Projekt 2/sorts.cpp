#include "sorts.hh"




void bucketSort(film array[], const int how_many){

    vector<film> bucket[10];

    for(int i=0; i<how_many; i++){
        int value=static_cast<int>(array[i].value());
        bucket[value-1].push_back(array[i]);
    }

    int index=0;
    for(int i=0; i<10; i++){
        for(int j=0;j <bucket[i].size(); j++)
            array[index++]=bucket[i][j];
    }
}


int partition(film array[], const int left, const int right)
{
    int pivot = array[(left + right) / 2].value(), i = left, j = right; 

    while(true){

        while(array[j] > pivot) 
            j--;

        while (array[i] < pivot) 
            i++;

        if (i < j)  swap(array[i++], array[j--]);
        else return j;
    }
}



void quickSort(film array[], const int left, const int right)
{
    if (left < right)
    {
        int q = partition(array, left, right);
        quickSort(array, left, q);
        quickSort(array, q + 1, right);
    }
}



void merge(film array[],const int left, const int mid, const int right){

    const int num_in_left = mid-left+1;
    const int num_in_right = right-mid;

    film* left_array = new film[num_in_left];
    film* right_array = new film[num_in_right];

    /* rewriting arrays */
    for(int i=0; i<num_in_left; i++)
        left_array[i]=array[left+i];
    for(int i=0; i<num_in_right; i++)
        right_array[i]=array[mid+1+i];

    int left_index=0;
    int right_index=0;
    int begining=left;



    while(left_index < num_in_left && right_index < num_in_right){
        if(left_array[left_index] <= right_array[right_index]){
            array[begining]=left_array[left_index];
            left_index++;
        }
        else {
            array[begining] = right_array[right_index];
            right_index++;
        }
        begining++;
    }
    

    while(left_index < num_in_left){
        array[begining] = left_array[left_index];
        left_index++;
        begining++;
    }

    while(right_index < num_in_right){
        array[begining] = right_array[right_index];
        right_index++;
        begining++;
    }

    delete[] left_array;
    delete[] right_array;

}



void mergeSort(film array[], const int begin, const int end){

    if (begin >= end)
        return;

    int mid = begin + (end-begin)/2;
    mergeSort(array, begin, mid);
    mergeSort(array, mid+1, end);
    merge(array,begin,mid,end);
}
