#ifndef SORTS_HH
#define SORTS_HH
#include "film.hh"
#include <vector>

/*!
*   \brief  Library of sorts algorithms. 
            merge sort | quick sort | bucket sort

*/

/*!
*   \brief  Function used in mergeSort. Main body of algorithm.
*   \param array  array to sort
*   \param left  left edge of array, first index
*   \param mid  middle index of array
*   \param right  right edge od array, last index
*/
void merge(film array[],const int left, const int mid, const int right);

/*!
*   \brief Function invoked recursively. Algorithm of merge sort.
*   \param array array to sort
*   \param begin first index of array
*   \param end last index of array
*/
void mergeSort(film array[], const int begin, const int end);

/*!
*   \brief Algorithm of bucket sort.
*   \param array array to sort
*   \param how_many number of elements to sort
*/
void bucketSort(film array[], const int how_many);

/*!
*   \brief Function used in quickSort. Sorts used pivot - middle of the array
    \return index of pivot - middle of the array
    \param array array to sort
    \param left index of left edge of the array
    \param right index of right edge of the array
*/
int partition(film array[], const int left, const int right);


/*!
*   \brief Algorithm of quick sort.
    \param array array to sort
    \param left index of left edge of the array
    \param right index of right edge of the array
*/
void quickSort(film array[], const int left, const int right);






#endif