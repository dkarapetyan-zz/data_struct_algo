#include <stdio.h>
#include <stdlib.h>
void merge_sort(int array[], int start, int end);
void merge(int array[], int start, int pivot, int end);

int main()
{
	int my_array[] =
	{ 1, 17, 5, 3, 4, 10 };
	merge_sort(my_array, 0, 5);
	for (int i = 0; i <= 5; i++)
	{
		printf("%d ", my_array[i]);
	}
	return 0;
}

void merge_sort(int array[], int start, int end)
{
	if (start < end)
	{
		int pivot = (start + end) / 2;
		merge_sort(array, start, pivot);
		merge_sort(array, pivot + 1, end);
		merge(array, start, pivot, end);
	}

}

void merge(int array[], int start, int pivot, int end)
{

	if (start < end)
	{
		// declare temporary array for merging two sorted arrays
		int temp[end - start + 1];
		int i = start;
		int j = pivot + 1;
		int k = 0;

		// compare everything before pivot with everything after

		while (i <= pivot && j <= end)
		{
			if (array[i] < array[j])
				temp[k++] = array[i++];
			else
				temp[k++] = array[j++];
		}
		// we have reached the end of the left subarray or the right.
		// Dump remaining entries into temp

		while (i <= pivot)
			temp[k++] = array[i++];

		while (j <= end)
			temp[k++] = array[j++];

		// copy temp into starting array
		for (i = start, j = 0; i <= end; i++)
			array[i] = temp[j++];
	}
}

