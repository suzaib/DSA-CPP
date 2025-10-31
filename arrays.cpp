// Questions on Arrays

// Notes
// When arrays are declared inside int main(){} :
    // They are initialized with some garbaze value
    // The maximum size can be 10^6

// When arrays are declared outside int main(){} (declared globally) :
    // They are initialized with initial value 0
    // The maximum size can be 10^7

//Arrays are by default passed by reference in functions
//In Vectors both the emplace_back and push_back do similar things with same Time Complexity (O(1)) still emplace_back should be preferred, because it is a bit faster in some complex cases

//Important Points
//*Unless Mentioned , the Space Complexity of the function is O(1) (no extra space is being utilised either to store the answer or solve the question)
//*Unless Mentioned, the Time Complexity of the function is O(N) (Only 1 iteration of loop of n size)
//I have mentioned the brute , better and optimal codes for each question as long as they exist and are not of very very high time complexity

#include<bits/stdc++.h>
using namespace std;

//Some Basic Functions Which will be helpful later on
void sortArr(int arr[],int n){
    int minIdx;
    for (int i = 0; i < n; i++){
        minIdx = i;
        for (int j = i; j < n; j++){
            if (arr[j] < arr[minIdx]){
                minIdx = j;
            }
        }
        swap(arr[i], arr[minIdx]);
    }
}

void sortVector(vector<int> &arr){
    int n = arr.size();
    int minIdx;
    for (int i = 0; i < n; i++){
        minIdx = i;
        for (int j = i; j < n; j++){
            if (arr[j] < arr[minIdx]){
                minIdx = j;
            }
        }
        swap(arr[i], arr[minIdx]);
    }
}

int fact(int n){
    if(n==1){
        return 1;
    }
    return n*fact(n-1);
}

int nPr(int n,int r){
    int ans=((fact(n))/(fact(n-r)));
    return ans;
}

int nCr(int n,int r){
    int k=min(r,n-r);
    int res=1;
    for(int i=0;i<k;i++){
        res=res*(n-i);
        res=res/(i+1);
    }
    return res;
}
//We can compute nCr using factorial simply but this takes much less time


//Level 1
// Q.1) Largest element in an array
//Brute Force : Sort the array in descending order and then return the element at the first / or sort in ascending order and return the element at the last
int findMaxEl_brute(vector<int> arr){
    sortVector(arr);
    int n=arr.size();
    return arr[n - 1];
}
//Time Complexity is O(N*N)

//Optimal Method : Traverse through the array, keeping track of the maximum element
int findMaxEl_optimal(vector<int> arr){
    int n=arr.size();
    int maxEl = arr[0];
    for (int i = 1; i < n; i++){
        if (arr[i] > maxEl){
            maxEl = arr[i];
        }
    }
    return maxEl;
}


// Q.2) Second largest element in an array
//Brute Force : Sort the array, then mark the last element as max1 then from back of array looking for the first element that is smaller than max1.(Using arr[n-2] is not sufficient , since array may have duplicates)
int findSecondMax_brute(vector<int> arr){
    int n=arr.size();
    sortVector(arr);
    int max1 = arr[n - 1];
    int max2;
    int i = n - 2;
    while (i >= 0){
        if (arr[i] != max1){
            max2 = arr[i];
            break;
        }
        i--;
    }
    return max2;
}
// Time complexity = O(N*N) (for sorting) and O(N) for one complete iteration of array in worst case(eg: [1,1,1,1,1,1,1,2]) ==> O(N^2 + N) ==> O(N^2)

//Better Method : In 1st loop find the max element and in second loop find the element that is smaller than max1 but greter than other elements
int findSecondMax_betterMethod(vector<int> arr){
    int n=arr.size();
    int max1 = arr[0];
    int max2 = INT_MIN;
    for (int i = 1; i < n; i++){
        if (arr[i] > max1){
            max1 = arr[i];
        }
    }
    for (int i = 0; i < n; i++){
        if (arr[i] > max2 && arr[i] < max1){
            max2 = arr[i];
        }
    }
    return max2;
}
// Time Complexity is O(N+N)(for two loops) ==> O(2N) 

//Optimal Method : Keep track of max1 and max2 at the same time, this way we can solve this in 1 iteration only
int findSecondMax_optimalMethod(vector<int> arr){
    int n=arr.size();
    int max1 = arr[0];
    int max2 = INT_MIN;
    for (int i = 1; i < n; i++){
        if (arr[i] > max2){
            if (arr[i] > max1){
                int temp = max1;
                max1 = arr[i];
                max2 = temp;
            }
            else if (arr[i] < max1){
                max2 = arr[i];
            }
        }
    }
    return max2;
}


// Q.3) Check if the array is sorted
//Optimal Method : Keep comparing neighbouring element till last
bool isSortedAsc_optimal(vector<int> arr){
    int n=arr.size();
    for (int i = 0; i < n - 1; i++){
        if (arr[i] > arr[i + 1]){
            return false;
        }
    }
    return true;
}

// Q.4) Count the number of Distinct elements in a sorted array
//Brute Force
int countDistinct_brute(vector<int> &arr){
    int curr = arr[0];
    for (int i = 1; i <arr.size(); i++){
        if (arr[i] == curr){
            arr.erase(arr.begin() + i);
            i--;
        }
        else{
            curr = arr[i];
        }
    }
    return arr.size();
}
//Time Complexity for erase function in worst case can be O(N) and for loop it is O(N) so totalling ===> O(N^2)
//Space Complexity is O(N) since we are making changes to the original array , it that's not considered then Space Complexity is O(1)

//Optimal Method : Two Pointer Approach :
//Keep i at beginning and j at beginning as well , then increase j to traverse through the array and increase i only when you find a different element.This approach works because array is sorted                                                    
int countDistinct_optimal(vector<int> &arr){
    int n=arr.size();
    int i = 0;
    for (int j = 1; j < n; j++){
        if (arr[i] != arr[j]){
            arr[i + 1] = arr[j];
            i++;
        }
    }
    return i + 1;
}
//Space Complexity is about O(N) since original array is being changed

// Q.5) Rotate an array by one place (We will Rotate to right)
void rightRotationBy1Place_brute(vector<int> &arr){
    int n=arr.size();
    vector<int> newArr;
    newArr.emplace_back(arr[n - 1]);
    int i = 0;
    while (i < n - 1){
        newArr.emplace_back(arr[i]);
        i++;
    }
    arr=newArr;
}
//Space Complexity is O(N) for extra vector used + O(N) since original array has been changed

void rightRotationBy1Place_better(vector<int> &arr){
    int n=arr.size();
    int temp1 = arr[0];
    arr[0] = arr[n - 1];
    int temp2;
    for (int i = 0; i < n - 1; i++){
        temp2 = arr[i + 1];
        arr[i + 1] = temp1;
        temp1 = temp2;
    }
}
//Space Complexity is O(1) since the original array has been changed

void rightRotationBy1Place_optimal(vector<int> &arr){
    int n=arr.size();
    int temp = arr[n-1];
    for (int i=n-1;i>0;i--){
        arr[i] = arr[i-1];
    }
    arr[0] = temp;
}
//Space Complexity is O(N) since the original array has been changed


// Q.6) Rotate array by k places (Left Rotation)
//By Applying similar method as above
void leftRotationByKPlaces_brute(vector<int> &arr, int k){
    int n=arr.size();
    k=k%n;
    vector<int> temp;
    for (int i = 0; i < k; i++){
        temp.push_back(arr[i]);
    }
    for (int i = k; i < n; i++){
        arr[i - k] = arr[i];
    }
    for (int i = 0; i < k; i++){
        arr[n - k + i] = temp[i];
    }
}
//Time Complexity is O(K) + O(N-K) + O(K) => O(N+K)
//Space Complexity is O(N) + O(K) => O(N+K) since we need to extra array of N elements and we also change the original array

// Optimal Method 
// Consider the array to be [1,2,3,4,5,6,7] to be rotated left by 3 places
// First look the two arrays [1,2,3] and [4,5,6,7]
// Reverse both the arrays : [3,2,1] and [7,6,5,4]
// Look both the arrays together : [3,2,1,7,6,5,4]
// Now reverse this array and see the magic !!!! : [4,5,6,7,1,2,3]
void leftRotationByKPlaces_optimal(vector<int> &arr, int k){
    int n=arr.size();
    k = k % n;
    reverse(arr.begin(),arr.begin()+k);
    reverse(arr.begin()+k,arr.end());
    reverse(arr.begin(),arr.end());
}
//Time Complexity is O(K) + O(N-K) + O(N) ==> O(2N)
//Space Complexity is O(N) since original array is being changed

// Remember that rotating left by 90 is same as rotating right by 270(360-90)
// So if the question asks to right rotate by 4 places , just left rotate by (n-4) places


// Q.7) Shift all the zeroes to the end
// Count the number of zeroes as you move through the array alongside , shifting non zero numbers to occupy the places where there were zeroes initially
void shiftZeroesToEnd_brute(vector<int> &arr){
    int n=arr.size();
    int count = 0;
    int currIdx = 0;
    for (int i = 0; i < n; i++){
        if (arr[i] == 0){
            count++;
        }
        else{
            arr[currIdx] = arr[i];
            currIdx++;
        }
    }
    for (int i = 0; i < count; i++){
        arr[n - count + i] = 0;
    }
}
//Time Complexity at the worst case can be O(2N)
//Space Complexity will be O(N) since original array is being changed

//This can be done by swapping 0 and and non zero numbers as you find them
void shiftZeroesToEnd_optimal(vector<int> &arr){
    int n=arr.size();
    int j = -1;
    for (int i = 0; i < n; i++){
        if (arr[i] == 0){
            j = i;
            break;
        }
    }

    if (j == -1){
        return;
    }

    for (int i = j + 1; i < n; i++){
        if (arr[i] != 0){
            swap(arr[i], arr[j]);
            j++;
        }
    }
}
//Time Complexity will be O(N) at the worst case
//Space Complexity is O(N) since original array is being changed


// Q.8) Linear search for first occurence
int linearSearchForFirstOccurence(vector<int> &arr, int x){
    int n = arr.size();
    for (int i = 0; i < n; i++){
        if (arr[i] == x){
            return i;
        }
    }
    return -1;
}


// Q.9) Linear Search for last occurence
int linearSearchForLastOccurence(vector<int> &arr, int x){
    int n = arr.size();
    for (int i = n - 1; i >= 0; i--){
        if (arr[i] == x){
            return i;
        }
    }
    return -1;
}

// Q.10) Linear Search For All Occurences
vector<int> linearSearchAllOccurence(vector<int> &arr, int x){
    int n = arr.size();
    vector<int> temp;
    for (int i = 0; i < n; i++){
        if (arr[i] == x){
            temp.push_back(i);
        }
    }
    return temp;
}

// Q.11) Union of Two arrays
vector<int> unionOfTwoSortedArr_brute(vector<int> a, vector<int> b){
    int n1 = a.size();
    int n2 = b.size();
    set<int> st;
    for (int i = 0; i < n1; i++){
        st.insert(a[i]);
    }
    for (int i = 0; i < n2; i++){
        st.insert(b[i]);
    }
    vector<int> temp;
    for (auto it : st){
        temp.push_back((it));
    }
    return temp;
}
// Time complexity for an insertion operation in a set is O(logN)
// Therefore total time complexity for the two loops is O(n1*logN) + O(n2*logN)
//Space Complexity will be O(M+N) (Incase all the elements are different)


//Using the two pointer approach
vector<int> unionOfTwoSortedArr_optimal(vector<int> a, vector<int> b){
    int n1 = a.size();
    int n2 = b.size();
    vector<int> unionArr;
    int i = 0;
    int j = 0;
    while (i < n1 && j < n2){
        if (a[i] <= b[j]){
            if (unionArr.size() == 0 || unionArr.back() != a[i]){
                unionArr.push_back(a[i]);
            }
            i++;
        }
        else{
            if (unionArr.size() == 0 || unionArr.back() != b[j]){
                unionArr.push_back(b[j]);
            }
            j++;
        }
    }

    while (i < n1){
        if (unionArr.size() == 0 || unionArr.back() != a[i]){
            unionArr.push_back(a[i]);
        }
        i++;
    }

    while (j < n2){
        if (unionArr.size() == 0 || unionArr.back() != b[j]){
            unionArr.push_back(b[j]);
        }
        j++;
    }

    return unionArr;
}
// Time complexity of this code is O(n1+n2) as we move through each element once only
// The space complexity is O(n1+n2) in the worst case(when each element is unique) and this space complexity is for returning the answer, not for solving it

// Q.12) Intersection of two sorted arrays
//Keeping track of visited array
vector<int> intersectionOfTwoSortedArr_brute(vector<int> a, vector<int> b){
    vector<int> ans;
    int n = a.size();
    int m = b.size();
    int vis[m] = {0};
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            if (a[i] == b[j] && vis[j] == 0){
                ans.push_back(a[i]);
                vis[j] = 1;
                break;
            }

            if (b[j] > a[i]){
                break;
            }
        }
    }

    return ans;
}
// Time complexity is O(n1*n2)
// Space complexity is O(n2) or O(n1) due to visited array (depending which array you take as your root)

// Take one array then for each of that array's element check if it can be found in the other array, if yes , insert the element in to the array
vector<int> intersectionOfTwoSortedArr_better(vector<int> a, vector<int> b){
    int n1 = a.size();
    int n2 = b.size();
    int currJ = 0;
    vector<int> intersectionArr;
    for (int i = 0; i < n1; i++){
        for (int j = currJ; j < n2; j++){
            if (b[j] == a[i]){
                intersectionArr.push_back(b[j]);
                currJ = j + 1;
                break;
            }
        }
    }

    return intersectionArr;
}
//Time Complexity is O(M*N) in worst case
//Space Complexity is O(min(M,N)) and that too for storing the answer

//The Two pointer approach
vector<int> intersectionOfTwoSortedArr_optimal(vector<int> a, vector<int> b){
    int n1 = a.size();
    int n2 = b.size();
    int i = 0;
    int j = 0;
    vector<int> intersectionArr;
    while (i < n1 && j < n2){
        if (a[i] == b[j]){
            intersectionArr.push_back(a[i]);
            i++;
            j++;
        }
        else if (a[i] < b[j]){
            i++;
        }
        else{
            j++;
        }
    }

    return intersectionArr;
}
// Time complexity is O(n1+n2) for worst case
// Space complexity is O(min(n1,n2)) in the worst case and that for storing the answer



// Q.13) Find the first missing integer in an array. We are given N (the range of numbers from which we have to find) (N=n+1)
// Looking for each element in the range of N
int findMissingNo_brute(vector<int> arr, int N){
    int n = arr.size();
    for (int i = 1; i < N; i++){
        int flag = 0;
        for (int j = 0; j < n; j++){
            if (arr[j] == i){
                flag = i;
                break;
            }
        }
        if (flag == 0){
            return i;
        }
    }
    return -1;
}
//Time Complexity is O(N*n)

//Using Array Hashing
int findMissingNo_better(vector<int> arr, int N){
    int n = arr.size();
    int hashedArr[N + 1] = {0};
    for (int i = 0; i < n; i++){
        hashedArr[arr[i]]++;
    }
    for (int i = 1; i <= N; i++){
        if (hashedArr[i] == 0){
            return i;
        }
    }
    return -1;
}
// The Time Complexity is O(N) + O(n) = 2N (if n and N are same)
// Space Complexity is O(N) since we need extra space of N

// This problem has two optimal solutions : The Sum Method and The XOR Method
// The Sum Method (Only valid when array has no duplicate element)
// Consider the array : [1,2,3,5] sum of numbers is 11
// Sum of natural numbers upto 5 is n*(n+1)/2 is 15
// The missing number is 15-11=4(expected sum-actual sum)
// If the elements repeat then this method fails

int findMissingNo_sumMethod(vector<int> arr, int N){
    int actualSum = 0;
    int n = arr.size();
    for (int i = 0; i < n; i++){
        actualSum+=arr[i];
    }
    int expectedSum = (N * (N + 1)) / 2;
    int missing = expectedSum-actualSum;
    return missing;
}

// XOR Method
// Basic Concepts(We will use ^ to denote XOR operations for the meantime)
// XOR(denoted by ^) of a number with itself is always 0 ie; 2^2=0 , 3^3^3^3=0^0=0(Make pairs of first two 3 and the last two 3)
// XOR of any number with 0 is the number itself
// Calculate 2^2^2^2^2: Make consecutive pairs: (2^2)^(2^2)^2 => 0^0^2 => (0^0)^2 => 0^2 =>2

// Concept for this question:
// Consider array [1,2,3,5] and N=5
// xor1 = 1^2^3^4^5 (xor of all numbers upto N)
// xor2 = 1^2^3^5 (xor of all numbers in the array)
// After doing xor1^xor2 => (1^1)^(2^2)^(3^3)^4^(5^5) which will eventually result in 4 since it will not have any pair
int findMissingNo_XORMethod(vector<int> arr, int N){
    int n = arr.size();
    int x1 = 0;
    int x2 = 0;
    for (int i = 0; i < n; i++){
        x1 = x1 ^ (i + 1);
        x2 = x2 ^ arr[i];
    }
    x1 = x1 ^ N;
    return x1 ^ x2;
}
// Why is xor method better even though the time complexity is the same
// since in the sum method we have to calculate n*(n+1) suppose if n was 10^5 , then n*(n+1) will go to 10^10 , for that we will have to store it in long int rather than just int
// I am not saying that long int will take any noticeable large space but still , xor method will be slightly better as it never goes beyond range

// Q.14) Find Maximum consecutive ones (We will be given an array of 0 and 1)
// eg: [1,1,0,0,0,1,1,1,0,1,1] ans is 3 as maximum consecutive ones are 3 in a row

// My Method
int maxConsecutiveOnes_optimal(vector<int> arr){
    int n = arr.size();
    int currCount = 0;
    int maxCount = 0;
    for (int i = 0; i < n; i++){
        if (arr[i] == 0){
            maxCount = max(maxCount, currCount);
            currCount = 0;
        }
        else{
            currCount++;
        }
    }
    maxCount = max(currCount, maxCount);
    return maxCount;
}

// Q.15) Find the numbers that appears once in a sorted array in which every but one number appears twice
int numAppearingOnce_brute(vector<int> arr){
    int n = arr.size();
    int prev = arr[0];
    int curr;
    for (int i = 1; i < n; i++){
        curr = arr[i];
        if (curr != prev){
            return i;
        }
        prev = arr[i];
    }
    return -1;
}

// Better Method: Hashing
int numAppearingOnce_better(vector<int> arr){
    int n=arr.size();
    unordered_map<int,int> mpp;
    for (int i = 0; i < n; i++){
        mpp[arr[i]]++;
    }
    for(auto it:mpp){
        if(it.second==2){
            return it.first;
        }
    }
    return -1;
}

// The time complexity is O(n/2 + 1) since every element is repeated twice but will have only one key in the map (the + 1 is for the single element)
// So the total time complexity is NlogM +O(n/2 + 1) (N is the length of array and M is the number of elements in map = n/2 +1)
// Space complexity will be O(n/1 + 1) (since a map with that many elements is being used)

// Where xor isn't 0 , that is the number appearing once
int numAppearingOnce_optimal(vector<int> arr){
    int n = arr.size();
    int x;
    for (int i = 0; i < n - 1; i++){
        x = arr[i] ^ arr[i + 1];
        if (x != 0){
            return i;
        }
        else{
            i++;
        }
    }
    return -1;
}

// Q.16) Return the length of the longest Subarray with sum K (With the original array having only positive elements)
// Form all subarrays possible and then see their sum
int lenOfLongestSubarrWithSumK_brute(vector<int> arr, int K){
    int n = arr.size();
    int sum = 0;
    int len = 0;
    for (int i = 0; i < n; i++){
        for (int j = i; j < n; j++){
            sum = 0;
            len = 0;
            for (int k = i; k <= j; k++){
                sum = sum + arr[k];
                if (sum == K){
                    len = max(len, j - i + i);
                }
            }
        }
    }
    return len;
}

// Using hashing : Prefix Sum Method
int lenOfLongestSubarrWithSumK_better(vector<int> arr, int K){
    int n = arr.size();
    map<int, int> preSumMap;
    int sum = 0;
    int maxLen = 0;
    for (int i = 0; i < n; i++){
        sum = sum + arr[i];
        if (sum == K){
            maxLen = max(maxLen, i + 1);
        }
        int rem = sum - K;
        if (preSumMap.find(rem) != preSumMap.end()){
            // preSumMap.find(rem) returns the iterator at which the key 'rem' is present. If no such key is present, then it returns preSumMap.end()
            int len = i - preSumMap[rem];
            maxLen = max(maxLen, len);
        }
        if (preSumMap.find(sum) == preSumMap.end()){
            preSumMap[sum] = i;
        }
    }

    return maxLen;
}
//Space Complexity is O(N)
// If the array has negatives as well as positives then this is the most optimal method
// However if the array has positives only then this can be optimised as well

// The two pointer approach
// Put pointer i at 0 and j at 0 (initially) , keep moving j until the required sum is either reached or exceeded
// If the sum exceeds the required sum , then move the i pointer(shrink the subarray)
// Every time you get the sum which is equal to the required sum, note down the lenth using j-i+1
int lenOfLongestSubarrWithSumK_optimal(vector<int> arr, int K){
    int n = arr.size();
    int left = 0;
    int right = 0;
    int sum = arr[0];
    int maxLen = 0;
    while (right < n){
        while (left <= right && sum > K){
            sum -= arr[left];
            left++;
        }
        if (sum == K){
            maxLen = max(maxLen, right - left + 1);
        }
        right++;
        if (right < n){
            sum += arr[right];
        }
    }
    return maxLen;
}
// Time Complexity of worst case is O(2N)


// Q.17) Given an array , tell if any two elements in that array add up to K (Yes or No)
// Suppose K is 12 , then we take the first element(say it's 3) and we it from K (12-3) , Now if 9 exists in the array return true, otherwise false
bool existenceOfAPairWithSumK_brute(vector<int> arr, int K){
    int n = arr.size();
    int reqSum;
    for (int i = 0; i < n - 1; i++){
        reqSum = K - arr[i];
        for (int j = i + 1; j < n; j++){
            if (arr[j] == reqSum){
                return true;
            }
        }
    }
    return false;
}
//Time taken will be due to two loops which are nested
//No space is required to solve the question 
//Time Complexity is O(n2)

//Better Method
//Using Hashing, and checking if the element we are looking for is available in the set or not
bool existenceOfAPairWithSumK_better(vector<int> &arr, int K){
    int n = arr.size();
    unordered_map<int, int> hashedMap;
    int req;
    for (int i = 0; i < n; i++){
        req = K - arr[i];
        if (hashedMap.find(req)!=hashedMap.end()){
            return true;
        }
        hashedMap[arr[i]] = i;
    }

    return false;
}
//For ordered Map Time Complexity will be O(N*logN)
//For unordered Map Time Complexity will be O(N*N) (though the worst case never occurs) and almost all operations happen in O(N) (the average time complexity)
//Unordered map takes average time of O(1) and only one loops run 
//The map can store all elements at worst
//Time Complexity will be O(n)
//Space Complexity will be O(2n)

//Optimal Method
//Sort the array then use two pointer approach
// This is slightly better than the better method(if the array is unsorted) since in this method we have to sort the array first
bool existenceOfAPairWithSumK(vector<int> &arr,int k){
    int n=arr.size();
    sort(arr.begin(),arr.end());
    int i=0;
    int j=n-1;
    while(i<j){
        int sum=arr[i]+arr[j];
        if(sum<k) i++;
        else if(sum>k) j--;
        else return true;
    }
    return false;
}
//Every element is checked once so n time along with the time needed for sorting the array
//The original array has been changed so in this case we say that n size is used
//Time Complexity will be O(n+nlogn)
//Space Complexity will be O(n)


// Q.18) Read Previous Question, This time , we are told that the pair does exists, and we have to find the indices of the two elements of the pair
pair<int, int> indexOfPairWithSumK_myMethod(vector<int> arr, int K){
    int n = arr.size();
    unordered_map<int, int> hashedMap;
    int req;
    for (int i = 0; i < n; i++){
        req = K - arr[i];
        if (hashedMap.find(req) != hashedMap.end()){
            return {i, hashedMap[req]};
        }
        hashedMap[arr[i]] = i;
    }
    return {-1, -1};
}
// For ordered Map Time Complexity will be O(N*logN)
// For unordered Map Time Complexity will be O(N*N) (though the worst case never occurs) and almost all operations happen in O(N) (the average time complexity)

// Q.19) Sort a given array that contains only 0,1 and 2
//Hashing
void sortArrOf012_brute(vector<int> &arr){
    vector<int> temp;
    int n = arr.size();
    int hashedArr[3] = {0};
    for (int i = 0; i < n; i++){
        hashedArr[arr[i]]++;
    }
    for (int i = 0; i < 3; i++){
        temp.insert(temp.end(), hashedArr[i], i);
    }
    arr=temp;
}
//Time Complexity is O(N)(for loop) + O(N) for n insertions ==> O(2N) 
//Space Complexity is O(3) 
vector<int> sortArrOf012_better(vector<int> &arr){
    int n = arr.size();
    int count0 = 0;
    int count1 = 0;
    int count2 = 0;
    for (int i = 0; i < n; i++){
        if (arr[i] == 0){
            count0++;
        }
        else if (arr[i] == 1){
            count1++;
        }
        else{
            count2++;
        }
    }
    for (int i = 0; i < count0; i++){
        arr[i] = 0;
    }
    for (int i = count0; i < count0 + count1; i++){
        arr[i] = 1;
    }
    for (int i = count0 + count1; i < count0 + count1 + count2; i++){
        arr[i] = 2;
    }
    return arr;
}
//Time Complexity is O(2N) 

// This is the Dutch National Flag Algorithm (for sorting an array containing only 3 elements)
vector<int> sortArrOf012_DNF(vector<int> &arr){
    int n = arr.size();
    int low = 0;
    int mid = 0;
    int high = n - 1;
    while (mid <= high){
        if (arr[mid] == 0){
            swap(arr[mid], arr[low]);
            low++;
            mid++;
        }
        else if (arr[mid] == 1){
            mid++;
        }
        else{
            swap(arr[mid], arr[high]);
            high--;
        }
    }
    return arr;
}
// Time Complexity is O(N) since in each step atleast one element is sorted so the loop runs n times for n elements

// Q.20) Find the majority element in an array
// Majority element: An element x is called a majority element of an array if it appears in the array more than n/2 (n is the size of array) times

// For each element maintain a count by going through an array each time, then see if the count was >n/2
int majorityElement_brute(vector<int> arr){
    int n = arr.size();
    for (int i = 0; i < n; i++){
        int count = 0;
        for (int j = 0; j < n; j++){
            if (arr[j] == arr[i]){
                count++;
            }
        }
        if (count > n / 2){
            return arr[i];
        }
    }
    return -1;
}
// Time Complexity is O(N*N)
// Space Complexity is O(1) since no extra space is being utilised

int majorityElement_better(vector<int> arr){
    int n = arr.size();
    map<int, int> hashedMap;
    for (int i = 0; i < n; i++){
        hashedMap[arr[i]]++;
    }
    for (auto it : hashedMap){
        int x = it.second;
        if (x > n / 2){
            return it.first;
        }
    }
    return -1;
}
// Time Complexity is N(for loop) * logN(for ordered map) : N*logN
// For unordered map for best and average case it is O(1) and hence total time complexity is O(N)
// Space Complexity is O(N)

// The Moore's Voting Algorithm
// Consider an array [7,7,5,7,5,1,5,7,5,5,7,7,5,5,5,5]. Start iterating over the array, with variables el and count
// When we go on the first element el=7 and count=1, Now if you came across any element that is !=7 decrease count by 1, if you came across 7 increase count by 1
// This goes on until came across index 5 where count=0 in this case when we go on the next element which is 5 , el=5 and count=1, Now keep repeating the above step
// This goes on and if at last there is any element left in el that will be 5
// Now again loop through the array checking if 5 is majority element or not(by maintaining) a count of its occurence, if it is then thats the answer, if its not then no majority element exists
int majorityElement_MVA(vector<int> &arr){
    int n = arr.size();
    int count = 0;
    int el;
    for (int i = 0; i < n; i++){
        if (count == 0){
            count++;
            el = arr[i];
        }
        else if (arr[i] == el){
            count++;
        }
        else{
            count--;
        }
    }
    int count1 = 0;
    for (int i = 0; i < n; i++){
        if (arr[i] == el){
            count++;
        }
    }
    if (count > n / 2){
        return el;
    }
    return -1;
}
// Time Complexity is O(2N) if we are told that the array may or maynot have a majority element , However
// if we are told that the array does have a majority element then we do not need to run the test condition(second loop) , in that case time complexity is O(N)

// Q.21) The subarray with the maximum sum
// Needless to say the array this time will involve negative elements as well since if it involves only positive elements the ans will be the complete array itself
int maxSumAmongSubArr_brute(vector<int> arr){
    int n = arr.size();
    int maxSum = INT_MIN;
    int sum;
    for (int i = 0; i < n; i++){
        for (int j = i; j < n; j++){
            sum = 0;
            for (int k = i; k <= j; k++){
                sum = sum + arr[k];
            }
            maxSum = max(maxSum, sum);
        }
    }
    return maxSum;
}
// The Time Complexity is almost O(N*N*N)

//The last loop is not needed in the previous solution
int maxSumAmongSubArr_striversMethod_betterMethod(vector<int> arr){
    int n = arr.size();
    int maxSum = INT_MIN;
    int sum;
    for (int i = 0; i < n; i++){
        sum = 0;
        for (int j = i; j < n; j++){
            sum = sum + arr[j];
            maxSum = max(maxSum, sum);
        }
    }
    return maxSum;
}
// Time Complexity is O(N*N)

//Kadane's Algorithm
int maxSumAmongSubArr_KadanesAlgorithm(vector<int> arr){
    int n = arr.size();
    int maxSum = INT_MIN;
    int sum = 0;
    for (int i = 0; i < n; i++){
        sum = sum + arr[i];
        maxSum = max(maxSum, sum);
        if (sum < 0){
            sum = 0;
        }
    }
    // Suppose if all the elements inside the array are negative , then the maximum sum will be of an empty array(sum=0 since no elements)
    // Therefore we return the maximum value since sum is equated to 0 the moment it is lesser than 0
    return max(sum, maxSum);
}

int maxSumAmongSubArr_ModifiedKadanesAlgorithm(vector<int> arr){
    int n = arr.size();
    int maxSum=arr[0];
    int currSum=arr[0];
    for(int i=0;i<n;i++){
        currSum=max(arr[i],arr[i]+currSum);
        maxSum=max(maxSum,currSum);
    }
    return maxSum;
}



// Q.22) Print any of the sub array with the maximum sum(any because there can be multiple subarrays with the same sum)
vector<int> subarrWithMaxSum_KadanesAlgorithm(vector<int> arr){
    int n = arr.size();
    vector<int> temp;
    int sum = 0;
    int maxSum = INT_MIN;
    int start;
    int ansStart = -1;
    int ansEnd = -1;
    for (int i = 0; i < n; i++){
        if (sum == 0){
            start = i;
        }
        sum = sum + arr[i];
        if (sum > maxSum){
            maxSum = sum;
            ansStart = start;
            ansEnd = i;
        }
        if (sum < 0){
            sum = 0;
        }
    }
    for (int i = ansStart; i <= ansEnd; i++){
        temp.push_back(arr[i]);
    }
    return temp;
}
// The Time Complexity is almost O(2N)
// There is also a variation of this question where we are asked to return the starting and ending indices of the subarray, In that case simply return ansStart and ansEnd

// Q.23) Best Way of Buying and Selling Stocks
// We are given an array [7,1,5,3,6,4] which gives prices of a stock on 6 days , we have to buy a stock and sell it such that the profit is maximum
// You may think we should buy when price is 1(at index 1) and sell it when price is 7(index 0), Wrong!!, To sell stock you must buy it first
// Hence the answer is buy it at price 1 and sell it at price 6
// We compare the difference between a element and each element before it and at last tell the maximum difference
int maxProfitBySellingStocks_brute(vector<int> arr){
    int n = arr.size();
    int start = 0;
    int profit;
    int maxProfit = INT_MIN;
    for (int i = 1; i < n; i++){
        for (int j = i - 1; j >= 0; j--){
            profit = arr[i] - arr[j];
            maxProfit = max(maxProfit, profit);
        }
    }
    return maxProfit;
}
// Time Complexity is almost O(N*N)

//Keeping the track of min element
int maxProfitBySellingStocks_optimal(vector<int> arr){
    int n = arr.size();
    int minEl = arr[0];
    int profit;
    int maxProfit = 0;
    for (int i = 1; i < n; i++){
        profit = arr[i] - minEl;
        maxProfit = max(maxProfit, profit);
        minEl = min(minEl, arr[i]);
    }
    return maxProfit;
}


// Q.23) Rearrange according to sign
// That is an array of equal negatives and positives [3,1,-2,-5,2,-4] is to be arranged with consecutive + and - sign (maintaining the order of same sign elements the same) ==> [3,-2,1,-5,2,-4]
// Make two arrays , one for positive and one for storing negative numbers , then append both these arrays one by one to form the new array
void arrInAlternateSign_brute(vector<int> &arr){
    int n = arr.size();
    vector<int> tempP;
    vector<int> tempN;
    for (int i = 0; i < n; i++){
        if (arr[i] > 0){
            tempP.push_back(arr[i]);
        }
        else{
            tempN.push_back(arr[i]);
        }
    }
    int j = 0;
    int k = 0;
    for (int i = 0; i < n; i++){
        if (i % 2 == 0){
            arr[i] = tempP[j];
            j++;
        }
        else{
            arr[i] = tempN[k];
            k++;
        }
    }
    return;
}
// Time Complexity will be O(N) + O(N/2) ==> O(3N/2)
// Space Complexity will be O(N) to store the elements in two arrays of size N/2

// We swap elements
void arrInAlternateSign_better(vector<int> &arr){
    int n = arr.size();
    int i = 0;
    int j;
    int temp;
    while (i < n - 1){
        j = i + 1;
        if (i % 2 == 0 && arr[i] < 0){
            while (j < n){
                if (arr[j] > 0){
                    temp = arr[j];
                    for (int k = j; k > i; k--){
                        arr[k] = arr[k - 1];
                    }
                    arr[i] = temp;
                    break;
                }
                j++;
            }
        }
        else if (i % 2 != 0 && arr[i] > 0){
            while (j < n){
                if (arr[j] < 0){
                    temp = arr[j];
                    for (int k = j; k > i; k--){
                        arr[k] = arr[k - 1];
                    }
                    arr[i] = temp;
                    break;
                }
                j++;
            }
        }
        i++;
    }
}


// Remember that positive elements occur at even indexes and negative elements occur at odd indexes , this way we go through each element once and assign it at the first positive index=0 then we increase the positive index by 2
void arrInAlternateSign_optimal(vector<int> &arr){
    int n = arr.size();
    vector<int> temp(n, 0);
    int posIdx = 0;
    int negIdx = 1;
    for (int i = 0; i < n; i++){
        if (arr[i] > 0){
            temp[posIdx] = arr[i];
            posIdx = posIdx + 2;
        }
        else{
            temp[negIdx] = arr[i];
            negIdx = negIdx + 2;
        }
    }
    arr=temp;
}
// Space Complexity is O(N) since we still need an array temp of element N

// Q.24) This time the same question as previous but difference is that there are not equal negatives and positives , suppose there are 3 negatives and 7 positives then arrange 3 negative and 3 positive as before and the remaining elements(4 positives) , just place them at the back of array in the same order
void arrInAlternateSignUnequalArr_brute(vector<int> &arr){
    int n = arr.size();
    vector<int> tempP;
    vector<int> tempN;
    for (int i = 0; i < n; i++){
        if (arr[i] > 0){
            tempP.push_back(arr[i]);
        }
        else{
            tempN.push_back(arr[i]);
        }
    }
    int i = 0;
    int j = 0;
    while (j <= tempP.size() && j <= tempN.size()){
        arr[i] = tempP[j];
        i++;
        arr[i] = tempN[j];
        i++;
        j++;
    }
    while (j <= tempP.size()){
        arr[i] = tempP[j];
        i++;
        j++;
    }
    while (j <= tempN.size()){
        arr[i] = tempN[j];
        i++;
        j++;
    }
    return;
}

// Strivers Method
void arrInAlternateSignUnequalArr_optimal(vector<int> &arr){
    int n = arr.size();
    vector<int> pos;
    vector<int> neg;
    for (int i = 0; i < n; i++){
        if (arr[i] > 0){
            pos.push_back(arr[i]);
        }
        else{
            neg.push_back(arr[i]);
        }
    }

    if (pos.size() > neg.size()){
        for (int i = 0; i < neg.size(); i++){
            arr[2 * i] = pos[i];
            arr[2 * i + 1] = neg[i];
        }
        int index = 2 * neg.size();
        for (int i = neg.size(); i < pos.size(); i++){
            arr[index] = pos[i];
            index++;
        }
    }
    else{
        for (int i = 0; i < pos.size(); i++){
            arr[2 * i] = pos[i];
            arr[2 * i + 1] = neg[i];
        }
        int index = 2 * pos.size();
        for (int i = pos.size(); i < neg.size(); i++){
            arr[index] = neg[i];
            index++;
        }
    }
}
// Time Complexity is O(N) for first loop + O(min(pos,neg)) + O(leftovers)
// This has the maximum Time Complexity of O(2N)
// Space Complexity is O(N) to store the N numbers

// Q.25) Next Permutation
// Suppose you are given the permutation 3 1 2 , the next permutation will be 3 2 1
// In case the given permutation is the last for eg 3 2 1 , then the next permutation will be the first , that is 1 2 3
//The next_permutation function provided in STL can be used as well
//Watch Video for optimal solution
vector<int> nextPermutation_optimal(vector<int> arr){
    int n = arr.size();
    int index = -1;
    for (int i = n - 2; i >= 0; i--){
        if (arr[i] < arr[i + 1]){
            index = i;
            break;
        }
    }
    if (index == -1){
        reverse(arr.begin(),arr.end());
        return arr;
    }
    for (int i = n - 1; i > index; i--){
        if (arr[i] > arr[index]){
            swap(arr[i], arr[index]);
            break;
        }
    }
    reverse(arr.begin(),arr.end());
    return arr;
}
// Time Complexity is O(N) + O(N) + O(N) ==> O(3N)
// Space Complexity is O(N) and that is to return the answer , we are not using any extra space to solve the question

// Q.26) Find Leaders in an array
// Leaders are elements on whose right every element is smaller for eg in [10,22,12,3,0,6] 22 is a leader since every number right to 22 is smaller, and obviously the last element is always the leader
// For each element traverse the array right to it to find if it is the leader
vector<int> leaders_brute(vector<int> arr){
    int n = arr.size();
    vector<int> temp;
    bool leader;
    for (int i = 0; i < n; i++){
        leader = true;
        for (int j = i + 1; j < n; j++){
            if (arr[j] > arr[i]){
                leader = false;
            }
        }
        if (leader == true){
            temp.push_back(arr[i]);
        }
    }
    return temp;
}
// Time Complexity is almost O(N*N)
// Space Complexity is O(N) at worst case(worst case happens when everyone is a leader) and that is only used to store the answer which is required since we have to return the array of leaders

// We go through the back keeping the track of maximum , the moment any element is bigger than the maximum , we know it is bigger than all the elements in the right, that is when we are sure , that it is a leader
vector<int> leaders_optimal(vector<int> arr){
    int n = arr.size();
    int maxEl = INT_MIN;
    vector<int> temp;
    for (int i = n - 1; i >= 0; i--){
        if (arr[i] > maxEl){
            temp.push_back(arr[i]);
        }
        maxEl = max(maxEl, arr[i]);
    }

    return temp;
}
// Space Complexity is O(N) at worst case
// If the question asks to return the answers in the pattern in which they appeared in the original array , just reverse the temp array and it will work


// Q.27) Length of longest consecutive sequence in an array
// For eg in array [102,100,1,101,3,2,4,1,1] the longest consecutive sequence is 1,2,3,4
// It doesn't matter if the numbers don't appear in order inside the array, but they should be there

// Go on the first element(say x) then search for x+1 by iterating through the entire array
// In case you find x+1 , increase the len of your sequence and find x+2 and so on
// In case you can't find the next element, move to the next element in the array
int lenOfLongestConsecutiveSeq_brute(vector<int> arr){
    int n = arr.size();
    int maxLen = 1;
    int count;
    int nextEl;
    int curr;
    for (int i = 0; i < n; i++){
        curr = arr[i];
        count = 1;
        while (linearSearchForFirstOccurence(arr, curr + 1) != -1){
            curr = curr + 1;
            count = count + 1;
        }
        maxLen = max(maxLen, count);
    }
    return maxLen;
}
// Time Complexity is about O(N*N)

//Sort the array and then proceed
int lenOfLongestConsecutiveSeq_better(vector<int> arr){
    int n = arr.size();
    sortVector(arr);
    int maxLen = INT_MIN;
    int prevEl = arr[0];
    int currLen = 1;
    for (int i = 0; i < n; i++){
        if (arr[i] - prevEl == 1){
            currLen++;
            maxLen = max(maxLen, currLen);
        }
        else if (arr[i] == prevEl){
            continue;
        }
        else{
            currLen = 1;
        }
        prevEl = arr[i];
    }
    return maxLen;
}

// Optimal Method
int lenOfLongestConsecutiveSeq_optimal(vector<int> arr){
    int n = arr.size();
    if (n == 0){
        return 0;
    }
    int longest = 1;
    unordered_set<int> st;
    for (int i = 0; i < n; i++){
        st.insert(arr[i]);
    }

    for (auto it : st){
        if (st.find(it - 1) == st.end()){
            int cnt = 1;
            int x = it;
            while (st.find(x + 1) != st.end()){
                x = x + 1;
                cnt = cnt + 1;
            }
            longest = max(longest, cnt);
        }
    }
    return longest;
}
// Time Complexity that set takes for insert function in average and best case is O(1) and O(N) in worst case(in case of collisions that is very rare),
// Therefore we can take O(1)*O(N) for the first loop
// For the second loop , it takes atmost 2N iterations (try yourself) , therefore :
// Time Complexity is O(3N)

// Q.28) Set Matrix 0s(Any row or column that has even 1 zero , make all of its columns and rows 0)
// Go on each tile, if there is a 0 turn all the elements of that particular row and column to -1 , then in the second iteration , turn all the -1 to 0
// If you turn them into 0 instead of -1 then the program will be confused between original 0s and the zeroes that we created , leading to all elements being 0, since the newly created 0s will again turn every element of their respective column and row to 0
void setMatrixZeroes_brute(vector<vector<int>> &arr){
    int rows = arr.size();
    int cols = arr[0].size();
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if (arr[i][j] == 0){
                for (int k = 0; k < cols; k++){
                    arr[i][k] = -1;
                }
                for (int k = 0; k < rows; k++){
                    arr[k][j] = -1;
                }
            }
        }
    }
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if (arr[i][j] == -1){
                arr[i][j] = 0;
            }
        }
    }
}
// Time Complexity of this code is (nxm)x(n+m)+(nxm) which is almost O(N*N*N)
// Space Complexity is O(1) since no extra array is being used to solve the question however since the original array is changed so with that respect we must tell space complexity as O(nxm)

void setMatrixZeroes_better(vector<vector<int>> &arr){
    int n = arr.size();
    int m = arr[0].size();
    vector<int> row(n, 0);
    vector<int> col(m, 0);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            if (arr[i][j] == 0){
                row[i] = 1;
                col[j] = 1;
            }
        }
    }
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            if (row[i] == 1 || col[j] == 1){
                arr[i][j] = 0;
            }
        }
    }
}
// Time Complexity is O(m*n) + O(m*n) ==> O(N*N) (almost)
// Space Complexity will be O(n) + O(m)

void setMatrixZeroes_optimal(vector<vector<int>> &arr){
    int n = arr.size();
    int m = arr[0].size();
    int col0 = 1;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            if (arr[i][j] == 0){
                arr[i][0] = 0;
                if (j != 0){
                    arr[0][j] = 0;
                }
                else{
                    col0 = 0;
                }
            }
        }
    }
    for (int i = 1; i < n; i++){
        for (int j = 1; j < m; j++){
            if (arr[i][j] != 0){
                if (arr[0][j] == 0 || arr[i][0] == 0){
                    arr[i][j] = 0;
                }
            }
        }
    }

    if (arr[0][0] == 0){
        for (int j = 0; j < m; j++){
            arr[0][j] = 0;
        }
    }

    if (col0 == 0){
        for (int i = 0; i < n; i++){
            arr[i][0] = 0;
        }
    }
}
// Time complexity is O(mn) + O(mn)

// Q.29) Rotate Matrix by 90 deg clockwise (we consider only a square matrix for now)
void rotateMatBy90_brute(vector<vector<int>> &mat){
    int n = mat.size();
    vector<vector<int>> temp(n, vector<int>(n));
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            temp[j][n - 1 - i] = mat[i][j];
        }
    }
    mat=temp;
}
// Time Complexity is O(n*n)
// Space Complexity is O(n*n)

// A Better Method
void rotateMatBy90_better(vector<vector<int>> &mat){
    int n = mat.size();
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if ((i + j) <= n / 2){
                swap(mat[i][j], mat[n - 1 - j][n - 1 - i]);
            }
        }
    }
    for (int i = 0; i < n / 2; i++){
        for (int j = 0; j < n; j++){
            swap(mat[i][j], mat[n - i - 1][j]);
        }
    }
    return;
}

// First take transpose and then reverse each row
void rotateMatBy90_optimal(vector<vector<int>> &mat){
    int n = mat.size();
    for (int i = 0; i <= n - 2; i++){
        for (int j = i + 1; j < n; j++){
            swap(mat[i][j], mat[j][i]);
        }
    }

    for (int i = 0; i < n; i++){
        reverse(mat[i].begin(), mat[i].end());
    }
}
// Time Complexity is O((n/2)*(n/2)) (for transposing) + O((n)*(n/2))

// Q.30) Printing Spiral of a Matrix
vector<int> spiralOfAMatrix_optimal(vector<vector<int>> mat){
    int n = mat.size();
    int m = mat[0].size();
    int left = 0;
    int right = m - 1;
    int top = 0;
    int bottom = n - 1;
    vector<int> ans;
    while (top <= bottom && left <= right){
        for (int i = left; i <= right; i++){
            ans.push_back(mat[top][i]);
        }
        top++;
        for (int i = top; i <= bottom; i++){
            ans.push_back(mat[i][right]);
        }
        right--;
        if (top <= bottom){
            for (int i = right; i >= left; i--){
                ans.push_back(mat[bottom][i]);
            }
            bottom--;
        }
        if (left <= right){
            for (int i = bottom; i >= top; i--){
                ans.push_back(mat[i][left]);
            }
            left++;
        }
    }
    return ans;
}
// Time Complexity is O(n*n) (since we traverse through every element once and only once)
// Space Complexity is O(n*n) (used for storing the answer, we could just print the answer itself to avoid this space, by using cout<<__ the particular element which we push_back in to the ans array

// Q.31) Number of subarrays with sum K
// Brute Force, Finding sum of all possible subarray, and increasing the count whenever the sum of any of those subarrays matches with the required sum
int noOfSubarrWithSumK_brute(vector<int> arr, int K){
    int n = arr.size();
    int sum=0;
    int count=0;
    for(int i=0;i<n;i++){
        for(int j=i;j<n;j++){
            sum=0;
            for(int k=i;k<=j;k++){
                sum+=arr[k];
            }
            if(sum==K){
                count++;
            }
        }
    }

    return count;
}
//Time Complexity is almost about O(n*n*n) , although the loop is not exactly running n cube times , but roughly speaking , that should be the time complexity

int noOfSubarrWithSumK_better(vector<int> arr,int K){
    int n=arr.size();
    int sum;
    int count=0;
    for(int i=0;i<n;i++){
        sum=0;
        for(int j=i;j<n;j++){
            sum=sum+arr[j];
            if(sum==K){
                count++;
            }
        }
    }
    return count;
}
//Time Complexity is almost about O(n*n)

//Using Prefix Sum 
int noOfSubarrWithSumK_optimal(vector<int> arr,int K){
    int n=arr.size();
    unordered_map<int,int> mpp;
    int count=0;
    int preSum=0;
    mpp[0]=1;
    for(int i=0;i<n;i++){
        preSum+=arr[i];
        int remove=preSum-K;
        count+=mpp[remove];
        mpp[preSum]++;
    }
    return count;
}
//Time Complexity is O(N) for loop + O(logN) for ordered map and O(1) best and average case for unordered map(happens 99% times) but for worst case it is O(N) 
//Space Complexity is O(N) for the worst case(when all the prefix sums are different)




//Level 3

//Q.30) Given the row , tell the element at the nth position in a Pascal Triangle
//Using nCr
int elAtPosXInPascalTriangle(int row,int x){
    //x th element in nth row is (n-1)C(r-1)
    int ans=nCr(row-1,x-1);
    return ans;
}
//Time Complexity will be O(k)


//Q.31) Print the entire row of a Pascal Triangle
//Using nCr
vector<int> rowOfPascalTriangle_brute(int row){
    vector<int> ans;
    int n=row-1;
    int element;
    for(int i=0;i<=n;i++){
        element=nCr(n,i);
        ans.push_back(element);
    }
    return ans;
}
//Time Complexity is O(n)*O(k)

//Optimising the same way as we optimised the nCr function in the beginning
vector<int> rowOfPascalTriangle_better(int row){
    vector<int> ans;
    int res=1;
    ans.push_back(res);
    for(int i=1;i<row;i++){
        res=res*(row-i);
        res=res/i;
        ans.push_back(res);
    }
    return ans;
}
//Time Complexity will be O(n)


//Q.32) Print the entire Pascal Triangle
//Using nCr
vector<vector<int>> pascalTriangle_optimal(int n){
    vector<int> temp;
    vector<vector<int>> ans;
    for(int i=1;i<=n;i){
        temp=rowOfPascalTriangle_better(i);
        ans.push_back(temp);
    }
    return ans;
}


//Q.33) Print the majority element(appearing more than n/3 times)
vector<int> majorityElement2_brute(vector<int> arr){
    int n=arr.size();
    vector<int> ans;
    int count;
    for(int i=0;i<n;i++){
        count=0;
        for(int j=0;j<n;j++){
            if(arr[j]==arr[i]){
                count++;
            }
        }
        if(count>n/3 && (ans.size()==0 || (ans.back()!=arr[i]))){
                ans.emplace_back(arr[i]);
        }
        if(ans.size()==2){
            break;
        }
    }
    return ans;
}
//Time Complexity will be O(n*n)
//Space Complexity will be O(2)

//Using Hashing
vector<int> majorityElement2_better(vector<int> arr){
    int n=arr.size();
    vector<int> ans;
    unordered_map<int,int> mpp;
    for(int i=0;i<n;i++){
        mpp[arr[i]]++;
    }
    for(auto it:mpp){
        if(it.second>n/3){
            ans.emplace_back(it.first);
        }
    }
    return ans;
}
//Time Complexity will be O(n) + O(1)(for best and average case or O(n) for worst case)
//Space Complexity will be O(n) + O(2)

//Using Moore's Voting Algorithm
vector<int> majorityElement2_MVA(vector<int> arr){
    vector<int> ans;
    int n=arr.size();
    int count1=0; 
    int count2=0;
    int el1;
    int el2;
    for(int i=0;i<n;i++){
        if(count1==0 && arr[i]!=el2){
            el1=arr[i];
            count1++;
        }
        else if(count2==0 && arr[i]!=el1){
            el2=arr[i];
            count2++;
        }
        else if(arr[i]==el1){
            count1++;
        }
        else if(arr[i]==el2){
            count2++;
        }
        else{
            count1--;
            count2--;
        }
    }
    count1=0;
    count2=0;
    for(int i=0;i<n;i++){
        if(arr[i]==el1){
            count1++;
        }
        else if(arr[i]==el2){
            count2++;
        }
    }
    if(count1>n/3){
        ans.emplace_back(el1);
    }
    if(count2>n/3){
        ans.emplace_back(el2);
    }
    return ans;
}
//Time Complexity is O(2N)
//Space Complexity is O(2)


//Q.34) 3 Sum Problem
//Part I
//First we only check if a triplet exists or not

//Brute Force 
//Form all the combinations
bool existenceOf3Sum_brute(vector<int> &arr,int k){
    int n=arr.size();
    for(int i=0;i<n;i++){
        int req=k-arr[i];
        for(int j=i+1;j<n;j++){
            int req2=req-arr[j];
            for(int k=j+1;k<n;k++){
                if(arr[k]==req2) return true;
            }
        }
    }
    return false;
}
//Three nested loops 
//Time Complexity will be O(n3)

//Better Method
//To use hashing
bool existenceOf3Sum_better(vector<int> &arr,int target){
    int n=arr.size();
    for(int i=0;i<n;i++){
        unordered_map<int,int> mp;
        for(int j=i+1;j<n;j++){
            int req=target-arr[i]-arr[j];
            if(mp.find(req)!=mp.end()) return true;
            mp[arr[j]]=j;
        }
    }
    return false;
}
//Only two loops this time
//Time Complexity will be O(n2)
//Space Complexity will be O(2n)

//Optimal Method
//Use the two pointer approach after sorting the array
bool threeSum(vector<int> &arr, int req) {
    int n = arr.size();
    sort(arr.begin(), arr.end());
    
    for(int i = 0; i < n - 2; i++) {
        int j = i + 1;
        int k = n - 1;
        
        while(j < k) {
            int sum = arr[j] + arr[k] + arr[i];
            if(sum > req) k--;
            else if(sum < req) j++;  // Compare with req, not k
            else return true;
        }
    }
    return false;
}
//Sorting takes time and the inner loop takes n2 time
//Since the original array is altered therefore this would add to the space complexity 
//Time Complexity will be O(n2+nlogn)
//Space Complexity will be O(n)


//Part II
//Find three unique triplets that sum up to k
//Naive Method
//Try all the possible combinations
vector<vector<int>> threeSum_naive(vector<int> arr,int target){
    set<vector<int>> st;

    int n=arr.size();
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n-1;j++){
            for(int k=j+1;k<n;k++){
                if(arr[i]+arr[j]+arr[k]==target){
                    vector<int> temp={arr[i],arr[j],arr[k]};

                    //Now we sort this so that similar triplets will automatically be removed
                    sort(temp.begin(),temp.end());
                    st.insert(temp);

                    //This break line optimised our code since any other value of k will be equal to target-(arr[i]+arr[j])
                    break;
                }
            }
        }
    }
    vector<vector<int>> ans(st.begin(),st.end());
    return ans;
}
//Three nested loops will run along with the time needed to insert and sort the element in the temp array, also the time taken at last to convert the set into vector
//Three nested loops mean n3, to insert in set takes logn and to sort takes nlogn and at last time taken will be 3m where m is the number of multilples
//Time Complexity will be O(n3*(logn+nlogn)+3m)
//Space Complexity will be O(3+3m)

//Brute Method
//Similar to using the hashing method to reduce the last loop
vector<vector<int>> threeSum_brute(vector<int> &arr,int target){
    int n=arr.size();
    set<vector<int>> st;
    for(int i=0;i<n;i++){
        unordered_set<int> hashSt;
        for(int j=i+1;j<n;j++){
            int req=target-(arr[i]+arr[j]);
            if(hashSt.find(req)!=hashSt.end()){
                vector<int> temp={arr[i],arr[j],req};
                sort(temp.begin(),temp.end());
                st.insert(temp);
            }
        }
    }

    vector<vector<int>> ans(st.begin(),st.end());
    return ans;

}
//Two nested loops, and inside sorting and inserting in set, and converting set to array
//Space is taken due to hashSt and temp array
//Time Complexity will be O(n2*(logn+nlogn)+3m)
//Space Complexity will be O(3+n+3m)

//Better Method
//Sort the array first then use two pointer approach
vector<vector<int>> threeSum_better(vector<int> &arr,int target){
    int n=arr.size();
    set<vector<int>> st;
    sort(arr.begin(),arr.end());
    for(int i=0;i<n;i++){
        int j=i+1;
        int k=n-1;
        while(j<k){
            int sum=arr[i]+arr[j]+arr[k];
            if(sum>target) k--;
            else if(sum<target) j++;
            else{
                vector<int> temp={arr[i],arr[j],arr[k]};
                st.insert(temp);
                j++;
                k--;
            }
        }
    }
    vector<vector<int>> ans(st.begin(),st.end());
    return ans;

}
//First we sort then use three pointer which takes n2 time and then we insert it inside taking logn time
//Time Complexity will be O(nlogn +n2*logn+3m)
//Space Complexity will be O(3+3m)

//Optimal Method
//We can further reduce the time and space if we are able to eliminate the set, and somehow storing the unique triplets without its help
vector<vector<int>> threeSum(vector<int> arr){
    int n=arr.size();
    sort(arr.begin(),arr.end());
    vector<vector<int>> ans;
    for(int i=0;i<n;i++){
        if(i>0 && arr[i]==arr[i-1]) continue;
        int j=i+1;
        int k=n-1;
        while(j<k){
            int sum=arr[i]+arr[j]+arr[k];
            if(sum<0) j++;
            else if(sum>0) k--;
            else{
                ans.push_back({arr[i],arr[j],arr[k]});
                j++;
                k--;
                while(j<k && arr[j]==arr[j-1]) j++;
                while(j<k && arr[k]==arr[k+1]) k--;
            }
        }
    }
    return ans;
}
//No space is used to solve the answer
//Time Complexity will be O(n2+nlogn) 

//Q.35) 4 Sum Problem
//Given an array and a sum k , return elements whose sum add up to k
//Testing all the combinations, brute force 
vector<vector<int>> fourSum_brute(vector<int> arr,int s){
    int n=arr.size();
    set<vector<int>> st;
    int sum;
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            for(int k=j+1;k<n;k++){
                for(int l=k+1;l<n;l++){
                    sum=arr[i]+arr[j]+arr[k]+arr[l];
                    if(sum==s){
                        vector<int> temp={arr[i],arr[j],arr[k],arr[l]};
                        sort(temp.begin(),temp.end());
                        st.insert(temp);
                        break;
                    }
                }
            }
        }
    }
    vector<vector<int>> ans(st.begin(),st.end());
    return ans;
}
//Time Complexity will be O(n**4)
//Space Complexity will be O(no. of unique quadruples x 2)

vector<vector<int>> fourSum_better(vector<int> arr,int s){
    int n=arr.size();
    set<int> hashSt;
    set<vector<int>> st;
    int fourth;
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            set<int> hashSt;
            for(int k=j+1;k<n;k++){
                fourth=s-(arr[i]+arr[j]+arr[k]);
                if(hashSt.find(fourth)!=hashSt.end()){
                    vector<int> temp={arr[i],arr[j],arr[k],fourth};
                    sort(temp.begin(),temp.end());
                    st.insert(temp);
                    break;
                }
                hashSt.insert(arr[k]);
            }
        }
    }
    vector<vector<int>> ans{st.begin(),st.end()};
    return ans;
}
//Time Complexity will be O(n*n*n) * O(logM) (M is the number of elements in the set which keeps on changing)
//Space Complexity will be O(n) 

//This time we sort the array first along with using two pointer approach
vector<vector<int>> fourSum_optimal(vector<int> arr,int s){
    int n=arr.size();
    vector<vector<int>> ans;
    sort(arr.begin(),arr.end());
    long long sum;
    for(int i=0;i<n;i++){
        if(i>0 && arr[i]==arr[i-1]) continue;
        for(int j=i+1;j<n;j++){
            if(j!=i+1 && arr[j]==arr[j-1]) continue;
            int k=j+1;
            int l=n-1;
            while(k<l){
                sum=arr[i]+arr[j]+arr[k]+arr[l];
                if(sum<s){
                    k++;
                }
                else if(sum>s){
                    l--;
                }
                else{
                    ans.push_back({arr[i],arr[j],arr[k],arr[l]});
                    k++;
                    l--;
                    while(j<k && arr[k]==arr[k-1]) k++;
                    while(j<k && arr[l]==arr[l+1]) l--;
                }
            }
        }
    }
    return ans;
}
//Time Complexity will be O(n*n) x O(n) (along with sorting)
//Space Complexity is O(1) since space is only being used to return the answer


//Q.36) Number of subarrays with xor k
//Testing all the subarrays
int subarrWithXORK_brute(vector<int> arr,int k){
    int n=arr.size();
    int count=0;
    int xr;
    for(int i=0;i<n;i++){
        for(int j=i;j<n;j++){
            xr=0;
            for(int k=i;k<=j;k++){
                xr=xr^arr[k];
            }
            if(xr==k){
                count++;
            }
        }
    }
    return count;
}
//Time Complexity will be O(n*n*n)

int subarrWithXORK_better(vector<int> arr,int k){
    int n=arr.size();
    int count=0;
    int xr;
    for(int i=0;i<n;i++){
        xr=0;
        for(int j=i;j<n;j++){
            xr=xr^arr[j];
            if(xr==k){
                count++;
            }
        }
    }
    return count;
}
//Time Complexity will be O(n*n)

//Remember if n^k=xr then after taking xor on both sides: n^k^k=xr^k(k^k=0 and n^0=n)
//==> n=xr^k;
int subarrWithXORK_optimal(vector<int> arr,int k){
    int n=arr.size();
    int count;
    int xr=0;
    int x;
    unordered_map<int,int> frontXor;
    frontXor[xr]++;
    for(int i=0;i<n;i++){
        xr=xr^arr[i];
        x=xr^k;
        count=count+frontXor[x];
        frontXor[xr]++;
    }
    return count;

}
//Time Complexity will be O(n)*O(1)(for unordered map in avg and best case)
//Space Complexity will be O(n) (for storing xor in hash map)


//Q.37) Merge Overlapping Subintervals
//Sorting the intervals first
vector<vector<int>> mergeOverlappingSubIntervals_brute(vector<vector<int>> arr){
    sort(arr.begin(),arr.end());
    vector<vector<int>> ans;
    int n=arr.size();
    int start;
    int end;
    for(int i=0;i<n;i++){
        start=arr[i][0];
        end=arr[i][1];
        if(!ans.empty() && end<=ans.back()[1]){
            continue;
        }
        for(int j=i+1;j<n;j++){
            if(arr[j][0]<=end){
                end=max(end,arr[j][1]);
            }
            else{
                break;
            }
        }
        ans.push_back({start,end});
    }
    return ans;
}
//Time Complexity will be O(2N) + O(NLogN)(For sorting)
//Space is only used for returning the answer

//This can be done in a single iteration
vector<vector<int>> mergeOverlappingSubIntervals_optimal(vector<vector<int>> arr){
    int n=arr.size();
    sort(arr.begin(),arr.end());
    vector<vector<int>> ans;
    for(int i=0;i<n;i++){
        if(ans.empty() || arr[i][0]>ans.back()[1]){
            ans.push_back(arr[i]);
        }
        else{
            ans.back()[1]=max(ans.back()[1],arr[i][1]);
        }
    }
    return ans;
}
//Time Complexity will be O(N)+ O(NlogN) (for sorting)
//Space is used for storing the answer


//Q.38) Merge two sorted arrays without using any extra space
//eg ==> consider a={1,3,5,7} b={0,2,6,8,9} then change the original arrays so that a={0,1,2,3} and b={5,6,7,8,9}
void mergeSortedArr_brute(vector<int> &a,vector<int> &b){
    int n=a.size();
    int m=b.size();
    int i=0;
    int j=0;
    vector<int> temp;
    while(i<n && j<m){
        if(a[i]>b[j]){
            temp.push_back(b[j++]);
        }
        else{
            temp.push_back(a[i++]);
        }
    }
    while(i<n){
        temp.push_back(a[i++]);
    }
    while(j<m){
        temp.push_back(b[j++]);
    }

    for(int k=0;k<n;k++){
        a[k]=temp[k];
    }
    for(int k=0;k<m;k++){
        b[k]=temp[n+k];
    }
}
//Time Complexity will be O(2*(n+m))

void mergeSortedArr_optimal1(vector<int> &a,vector<int> &b){
    int n=a.size();
    int m=b.size();
    int i=n-1;
    int j=0;
    while(i>=0 && j<m){
        if(a[i]>b[j]){
            swap(a[i],b[j]);
            i--;
            j++;
        }
        else{
            break;
        }
    }
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
}
//Time Complexity will be O(min(n,m)) + O(NlogN + MlogM)(for sorting)

//This time we have another optimal solution as well
void mergeSortedArr_optimal2(vector<int> &a,vector<int> &b){
    int n=a.size();
    int m=b.size();
    int len=(m+n);
    int left;
    int right;
    int gap=len/2 + len%2;
    while(gap>0){
        left=0;
        right=left+gap;
        while(right<len){
            if(left<n && right>=n){
                if(a[left]>b[right-n]){
                    swap(a[left],b[right-n]);
                }
            }
            else if(left>=n){
                if(b[left-n]>b[right-n]){
                    swap(b[left-n],b[right-n]);
                }
            }
            else{
                if(a[left]>a[right]){
                    swap(a[left],a[right]);
                }
            }
            left++;
            right++;
        }
        if(gap==1) break;
        gap=gap/2 + gap%2;
    }
}
//Time Complexity will be => O(log2(n+m) * (n+m))


//Q.39) Find Missing and repeating number
// We will be given for eg a k=6 and arr=[4,3,6,2,1,1] , tell the repeating number(1) and missing number(5)
vector<int> missingAndRepeating_brute(vector<int> arr,int n){
    vector<int> ans={0,0};
    int count;
    for(int i=1;i<=n;i++){
        count=0;
        for(int j=0;j<n;j++){
            if(arr[j]==i){
                count++;
            }
            if(count==2){
                ans[1]=arr[j];
                break;
            }
        }
        if(count==0){
            ans[0]=i;
        }
    }
    return ans;
}
//Time Complexity will be O(n*n)

//Using hashing
vector<int> missingAndRepeating_better(vector<int> arr,int n){
    int hashedArr[n+1]={0};
    vector<int> ans={0,0};
    for(int i=0;i<n;i++){
        hashedArr[arr[i]]++;
    }
    for(int i=1;i<=n;i++){
        if(hashedArr[i]==2){
            ans[1]=i;
        }
        else if(hashedArr[i]==0){
            ans[0]=i;
        }
    }
    return ans;
}
//Time Complexity will be O(2*n) 
//Space Complexity will be O(n) 

//Two optimal solutions
//Using Basic Maths
vector<int> missingAndRepeating_optimal1(vector<int> arr,int n){
    int Sn=(n*(n+1))/2;
    int S2n=(n*(n+1)*(2*n+1))/6;
    int S=0;
    int S2=0;
    for(int i=0;i<n;i++){
        S=S+arr[i];
        S2=S2+arr[i]*arr[i];
    }
    int x=((S-Sn) + ((S2-S2n)/(S-Sn)))/2;
    int y=(x-S+Sn);
    vector<int> ans={y,x};
    return ans;
}

//Using XOR Method(Not recommended for the interview)
vector<int> misssingAndRepeating_optimal2(vector<int> arr,int n){
    int xr=0;
    for(int i=0;i<n;i++){
        xr=xr^arr[i];
        xr=xr^(i+1);
    }
    int bit=0;
    while(1){
        if((xr&(1<<bit))!=0) break;
        bit++;
    }

    int zero=0;
    int one=0;
    for(int i=0;i<n;i++){
        //part of one club
        if(arr[i]&(1<<bit)!=0) one=one^arr[i];
        else zero=zero^arr[i];
    }

    for(int i=1;i<=n;i++){
        if(i & (1<<bit)!=0) one=one^i;
        else zero=zero^i;
    }

    int cnt=0;
    for(int i=0;i<n;i++){
        if(arr[i]==zero) cnt++;
    }
    int mis;
    int rep;
    if(cnt==0){
        mis=zero;
        rep=one;
    }
    else {
        mis=one;
        rep=zero;
    }
    vector<int> ans={mis,rep};
    return ans;
}

//Q.40) Count total inversions 
//Consider array=[5,3,2,4,1] , then any two pairs is descending order are called inverted pairs(the order in which the individual elements have to be taken should be the same as that in the array)
//eg (4,1) , (5,3) , (5,1)
//Testing all the pairs (brute force)
int countInversions_brute(vector<int> arr){
    int n=arr.size();
    int cnt=0;
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(arr[i]>arr[j]) cnt++;
        }
    }
    return cnt;
}

int divideSort(vector<int> &arr,int low,int mid,int high){
    vector<int> temp;
    int left=low;
    int right=mid+1;
    int cnt=0;

    while(left<=mid && right<=high){
        if(arr[left]<=arr[right]){
            temp.push_back(arr[left]);
            left++;
        }
        else{
            temp.push_back(arr[right]);
            cnt+=(mid-left+1);
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
    return cnt;
}

int divide(vector<int> &arr,int low,int high){
    int cnt=0;
    if(low>=high) return cnt;
    int mid=((low+high)>>1);
    cnt+=divide(arr,low,mid);
    cnt+=divide(arr,mid+1,high);
    cnt+=divideSort(arr,low,mid,high);
    return cnt;

}
int countInversions_optimal(vector<int> &arr){
    int n=arr.size();
    return divide(arr,0,n-1);
}


//Q.41) Reverse Pairs 
//Find pairs such that a[i]> 2*a[j] and j>i
//Testing all the pairs (brute force)
int reversePairs_brute(vector<int> arr){
    int n=arr.size();
    int count=0;
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(arr[i]>2*arr[j]){
                count++;
            }
        }
    }
    return count;
}
//Time Complexity will be O(n2)

//Optimal approach : Using recursion and the idea of merge sort

int f2(int low,int mid,int high,vector<int> &arr){
    int left=low;
    int right=mid+1;
    int cnt=0;
    while(left<=mid && right<=high){
        if(arr[left]>(2*arr[right])){
            cnt+=(mid-left+1);
            right++;
        }
        else left++;
    }

    left=low;
    right=mid+1;
    vector<int> temp;
    while(left<=mid && right<=high){
        if(arr[left]<arr[right]){
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

    return cnt;

}

int f1(int low,int high,vector<int> &arr){
    int cnt=0;
    if(low>=high) return cnt;
    int mid=((low+high)>>1);
    cnt+=f1(low,mid,arr);
    cnt+=f1(mid+1,high,arr);
    cnt+=f2(low,mid,high,arr);
    return cnt;
}
int reversePairs_optimal(vector<int> &arr){
    int n=arr.size();
    return f1(0,n-1,arr);
}
//Time Complexity will be O(2nlogn) (nlog n used to be the complexity for merge sort but now in the f2 function we do an additional step taking n time therefore : (n+n)logn)
//Space Complexity will be O(n) since the array is distorted
//Q.42) Maximum Product among all Sub arr
//Testing all the subarrays
int maxProdAmongSubarr_brute(vector<int> arr){
    int n=arr.size();
    int prod=1;
    int maxProd=INT_MIN;
    for(int i=0;i<n;i++){
        for(int j=i;j<n;j++){
            prod=1;
            for(int k=i;k<=j;k++){
                prod=prod*arr[k];
            }
            maxProd=max(prod,maxProd);
        }
    }
    return maxProd;
}
//Time complexity will be around O(n*n*n)


//Optimising a bit (as we really don't need the third loop)
int maxProdAmongSubarr_better(vector<int> arr){
    int n=arr.size();
    int prod=1;
    int maxProd=1;
    for(int i=0;i<n;i++){
        prod=1;
        for(int j=i;j<n;j++){
            prod=prod*arr[j];
            maxProd=max(maxProd,prod);
        }
    }
    return maxProd;
}
//Time Complexity will be O(n*n)


//Two Optimal solutions exists
int maxProdAmongSubarr_optimal(vector<int> arr){
    int n=arr.size();
    int pref=1;
    int suff=1;
    int ans=INT_MIN;
    for(int i=0;i<n;i++){
        if(pref==0) pref=1;
        if(suff==0) suff=1;
        pref=pref*arr[i];
        suff=suff*arr[n-i-1];
        ans=max(ans,max(pref,suff));
    }
    return ans;
}
//Time Complexity will be O(n)

//The other optimal solutions is by using kadane's algorithm but it is not discussed here since it is not much intuitive



int main(){
}

