#include <iostream>
#include <vector>

using namespace std;

// template <typename T>
// uint64_t binarySearch3Branches(vector<T> &set, uint64_t low, uint64_t high, T x) {
// 	while (low <= high)
// 	{
// 		// int mid = low + (high - low) / 2;
//         int mid = (high + low)/2;

// 		if (set[mid] == x)
// 			return mid;

// 		if (set[mid] < x)
// 			low = mid + 1;

// 		else
// 			high = mid - 1;
// 	}

//     if (low > set.size() - 1){
//         return high;
//     }
//     if (high < 0){
//         return low;
//     }
//     return low;
// }

template <typename T>
uint64_t binarySearch3Branches(T &set, uint64_t low, uint64_t high, uint64_t x) {
	while (low <= high)
	{
		// int mid = low + (high - low) / 2;
        int mid = (high + low)/2;

		if (set[mid] == x)
			return mid;

		if (set[mid] < x)
			low = mid + 1;

		else
			high = mid - 1;
	}

    if (low > set.size() - 1){
        return high;
    }
    if (high < 0){
        return low;
    }
    return low;
}

// template <typename T>
// uint64_t binarySearch2Branches(vector<T> &set, uint64_t low, uint64_t high, T x){
//     long long int mid;
//     while (low < high){
//         mid = (low + high)/2; 
//         if (x <= set[mid]){
//             high = mid; 
//         }
//         else {
//             low = mid+1;
//         }
//     }
//     if (set[low] == x)
//         return low;
//     if (low > set.size()-1)
//         return high;
//     return low;
// }

template <typename T>
uint64_t binarySearch2Branches(T &set, uint64_t low, uint64_t high, uint64_t x){
    long long int mid;
    while (low < high){
        mid = (low + high)/2; 
        if (x <= set[mid]){
            high = mid; 
        }
        else {
            low = mid+1;
        }
    }
    if (set[low] == x)
        return low;
    if (low > set.size()-1)
        return high;
    return low;
}

// template <typename T>
// uint64_t exponentialSearch(vector<T> &set, T x, uint64_t initial_position) { 
//     uint64_t n = set.size();
//     if (set[initial_position] == x) 
//         return initial_position; 
//     if (set[initial_position] > x)
//         return initial_position;
//     if (set[n-1] < x)
//         return n-1;
  
//     uint64_t i = initial_position + 1; 
//     while (i < n && set[i] <= x) 
//         i = i*2; 
//     return binarySearch2Branches<T>(set, i/2, min(i, n-1), x); 
// }

template <typename T>
uint64_t exponentialSearch(T &set, uint64_t x, uint64_t initial_position) { 
    uint64_t n = set.size();
    if (set[initial_position] == x) 
        return initial_position; 
    if (set[initial_position] > x)
        return initial_position;
    if (set[n-1] < x)
        return n-1;
  
    uint64_t i = initial_position + 1; 
    while (i < n && set[i] <= x) 
        i = i*2; 
    return binarySearch2Branches<T>(set, i/2, min(i, n-1), x); 
}