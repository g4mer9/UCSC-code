// C++ program to rotate an array by
// d elements
//modified code from 
//https://www.geeksforgeeks.org/array-rotation/
#include <iostream>
using namespace std;

/*Function to left Rotate arr[] of
size n by 1*/
void leftRotatebyOne(int arr[], int n)
{
	int temp = arr[0], i;
	for (i = 0; i < n - 1; i++)
		arr[i] = arr[i + 1];

	arr[n-1] = temp;
}

/*Function to left rotate arr[] of size n by d*/
void leftRotate(int arr[], int d, int n)
{
	for (int i = 0; i < d; i++)
		leftRotatebyOne(arr, n);
}

/* utility function to print an array */
void printArray(int arr[], int n)
{
	for (int i = 0; i < n; i++)
		cout << arr[i] << " ";
}

/* Driver program to test above functions */
int main()
{
	int arr[] = { 0,1,0,0 };//try various 4 bit values here
	int n = sizeof(arr) / sizeof(arr[0]);
	int rotateBy= 2;//2 is decimal for 0010 in 4 bits
	//try rotating left by various amounts between 0-15 as per lab1 requiremnts

	// Function calling and printing results
	printArray(arr, n);
	cout<< " rotated left by "<< rotateBy <<" gives ";
	leftRotate(arr, rotateBy, n);
	printArray(arr, n);

	return 0;
}
