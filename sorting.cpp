//Sorting

#include<bits/stdc++.h>
using namespace std;

 //lets first write our code for the swap function
 //when we pass arguments as reference, the changes happen to the original values
 void swap(int &n1,int &n2){
    int temp=n1;
    n1=n2;
    n2=temp;
}

//Selection sort
//Find the minimum element and put it at the first, (the element at that first position gets swapped with the minumum element's place)
void sortBySelectionSort(int arr[],int n){
    //n is the size of array
    int minIdx;
    for(int i=0;i<n;i++){
        minIdx=i;
        for(int j=i;j<n;j++){
            if(arr[j]<arr[minIdx]){
                minIdx=j;
            }
            swap(arr[i],arr[minIdx]);
        }
    }

}
//Time complexity of selection sort is about O(N*N)


//Bubble Sort
//Keep swapping any two elemnents that are in the wrong order
//After swapping one complete tiem across the array , the greatest element is at the last (see for yourself)
//So now the new array will be from starting to second last element and so on...

//We will also optimize our code by counting the number of swaps that happened
//Suppose that there was an array that was already sorted , so after first walkthrough the number of swaps will be 0 ,
//this means we don't need to do any further calculations and can return from there only
void sortByBubbleSort(int arr[],int n){
    int didSwap;
    for(int i=n-1;i>=0;i--){
        didSwap=0;
        for(int j=0;j<=i-1;j++){
            if(arr[j]>arr[j+1]){
                swap(arr[j],arr[j+1]);
                didSwap++;
            }
        }
        if(didSwap==0){
            break;
        }
    }
}


//Insertion Sort
//Takes an element and places it at its correct order
void sortByInsertionSort(int arr[],int n){
    for(int i=1;i<n;i++){
        int j=i;
        while(j>0 && arr[j-1]>arr[j]){
            swap(arr[j],arr[j-1]);
            j--;
        }
    }
}



//Merge sort (should know recursion)
//All the other 3 sorting methods take O(N*N) time complexity 
//Mege sort is a much more optimized method 
//Just remember in merge sort we divide and merge

//Explanation of merge sort can't be explained by simple words , a video tutorial is recommended
//Consider an array {3,2,4,1,3}
//Initially we take the whole of array and hence low should be passes as o and high should be passed as the last index

void merge(vector<int> &arr,int low,int mid,int high){
    vector<int>temp;
    int left=low;
    int right=mid+1;
    while(left<=mid && right<=high){
        if(arr[left]<=arr[right]){
            temp.push_back(arr[left]);
            left++;
        }
        else{
            temp.push_back(arr[right]);
            right++;
        }
    }

    while(left<=mid){
        temp.push_back(arr[left]);
        left++;
    }
    
    while(right<=high){
        temp.push_back(arr[right]);
        right++;
    }

    for(int i=low;i<=high;i++){
        arr[i]=temp[i-low];
    }
}
void mS(vector<int> &arr,int low,int high){
    if(low==high){
        return;
    }
    int mid=(low+high)/2;
    //We could also use right shift operator 
    mS(arr,low,mid);
    mS(arr,mid+1,high);
    merge(arr,low,mid,high);
}

void mergeSort(vector <int> &arr){
    int n=arr.size();
    mS(arr,0,n-1);
}
//Whenever division is happening by x the time complexity is logx N (x is base)
//The time complexity for the worst case of merging is N
//So the total time complexity is N * log2 N


//Quick Sort
//Merge sort has Time Complexity of N*log N and uses an extra temporary array so the space complexity is O(N)
//Quick Sort on the other hand has the same time complexity but doesn't uses any extra array so the space complexity is O(1)
//Both of them do use recursion stack space

//Steps for Quick Sort
//1. Pick any element as a pivot (We will chose first element)
//2. Place the chosen pivot element in the correct place(the place where it would be in a sorted array)
//3. Now go through each remaining element and put the elements smaller than the pivot on its left and the elements larger than it on the right
//4. The pivot is obviously at its correct (Step 2). Now we have two parts of array. On the left and on the right of the pivot. Repeat above steps on each part

//The catch is in step 2. How would you know what is the correct place for the pivot ?
//Take pointers i(at the start of array) and j(at the end of array) and move (moving i towards right and j towards left) 
//When you find an element at i which is bigger than pivot and an element at j which is smaller than pivot , swap them.
//Keep doing this until j becomes less than i 
//After j is smaller than i and then you find the required elements(element at i is larger than pivot and element at j is smaller than pivot) swap the element at j with the pivot
//This puts the pivot at its required position

int partition(vector<int> &arr,int low,int high){
    int pivot=arr[low];
    int i=low;
    int j=high;
    while(i<j){
        while(arr[i]<=pivot && i<=high-1){
            i++;
        }
        while(arr[j]>pivot && j>=low+1){
            j--;
        }
        if(i<j){
            swap(arr[i],arr[j]);
        }
    }
    swap(arr[low],arr[j]);
    return j;
}

void qS(vector<int> &arr,int low,int high){
    if(low<high){
        int pIdx=partition(arr,low,high);
        qS(arr,low,pIdx-1);
        qS(arr,pIdx+1,high);
    }
}

vector<int> quickSort(vector<int> arr){
    qS(arr,0,arr.size()-1);
    return arr;
}

int main(){
    return 0;
}
