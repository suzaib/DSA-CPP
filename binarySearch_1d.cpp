//Binary Search
#include<bits/stdc++.h>
using namespace std;

//TC is Time Complexity and SC is space Complexity 
//Unless mentioned otherwise : TC is O(n) and SC is O(1)

//Some Functions that are needed downwards

//For finding the maximum element in an array
int maxInArr(vector<int> arr){
    int n=arr.size();
    int ans=arr[0];
    for(int i=1;i<n;i++){
        ans=max(arr[i],ans);
    }
    return ans;
}

//For finding the minimum element in an array
int minInArr(vector<int> arr){
    int n=arr.size();
    int ans=arr[0];
    for(int i=1;i<n;i++){
        ans=min(ans,arr[i]);
    }
    return ans;
}

//For finding the total of all elements in an array
int sumOfArr(vector<int> arr){
    int n=arr.size();
    int sum=0;
    for(int i=0;i<n;i++){
        sum+=arr[i];
    }
    return sum;
}


//For finding the total time taken by koko to eat bananas
int timeTakenByKoko(vector<int> arr,int bph){
    //bph is bananas eaten per hour
    int n=arr.size();
    int totalTime=0;
    for(int i=0;i<n;i++){
        totalTime+=arr[i]/bph;
        if(arr[i]%bph!=0) totalTime+=1;
    }
    return totalTime;
}

//For finding the total bouquet made in nth day
int totalBouqInMDays(vector<int> arr,int day,int m){
    int n=arr.size();
    int Bq=0;
    int count=0;
    for(int i=0;i<n;i++){
        if(arr[i]<=day){
            count++;
        }
        else{
            Bq=Bq+count/m;
            count=0;
        }
    }
    Bq=Bq+count/m;
    return Bq;
}

//Consider the array : {2,3,1,5,3}, when we divide every element by div say 4 we get (1+1+1+2+1) => 6. This is what the function returns
int sumOfQuotCeil(vector<int> arr,int div){
    int n=arr.size();
    int sum=0;
    for(int i=0;i<n;i++){
        sum=sum+arr[i]/div;
        if(arr[i]%div!=0) sum+=1;
    }

    return sum;
}

//A ship has max weight capacity of 'cap'. Days taken to ship loads denoted in the arr.
int daysTakenToShip(vector<int> arr,int cap){
    int n=arr.size();
    int days=1;
    int load=0;
    for(int i=0;i<n;i++){
        if(load+arr[i]>cap){
            days=days+1;
            load=arr[i];
        }
        else{
            load=load+arr[i];
        }
    }
    return days;
}

//For aggressive cows question. tells if cows can be placed at distance 'dist' or not
bool canWePlace(vector<int> &stalls,int dist,int cows){
    int cntCows=1;
    int last=stalls[0];
    for(int i=1;i<stalls.size();i++){
        if(stalls[i]-last>=dist){
            cntCows++;
            last=stalls[i];
        }
        if(cntCows>=cows) return true;
    }
    return false;
}

//For allocation of books problem.
int stuAllotedBooks(vector<int> books,int maxPages){
    int n=books.size();
    int pageCount=0;
    int stuCount=0;
    for(int i=0;i<n;i++){
        pageCount+=books[i];
        if(pageCount>maxPages){
            stuCount++;
            pageCount=0;
            i--;
        }
    }
    stuCount++;
    return stuCount;
}

//Needed for the split arrays with max sum question
int totalSubarr(vector<int> arr,int sum){
    int n=arr.size();
    int currSum=0;
    int cnt=1;
    for(int i=0;i<n;i++){
        currSum+=arr[i];
        if(currSum>sum){
            cnt++;
            currSum=arr[i];
        }
    }
    return cnt;
}

//Needed for the painter's partition problem
int paintersNeeded(vector<int> arr,int k){
    int n=arr.size();
    int cnt=1;
    int area=0;
    for(int i=0;i<n;i++){
        area+=arr[i];
        if(area>k){
            cnt++;
            area=arr[i];
        }
    }
    return cnt;
}


//In Binary Search the given array will always be sorted and will often unique elements
//Here onwards the TC will be O(n) for iterative case, and O(logn) for binary search(log with base 2)

//Find a given element in an array
int findElement_iterative(vector<int> arr,int k){
    int n=arr.size();
    int low=0;
    int high=n-1;
    while(low<=high){
        int mid=(low+high)/2;
        if(arr[mid]>k) high=mid-1;
        else if(arr[mid]<k) low=mid+1;
        else return mid;
    }
    return -1;
}
//TC=logn

//Recursion can be used as well
int findElement_recursive(vector<int> arr,int low,int high,int k){
    if(low>high){
        return -1;
    }
    int mid=(low+high)/2;
    if(arr[mid]==k){
        return mid;
    }
    else if(k>arr[mid]){
        return findElement_recursive(arr,mid+1,high,k);
    }
    return findElement_recursive(arr,low,mid-1,k);
}
//Time Complexity will be O(log2(N)) (since it is being divided by 2)
//There exists a overflow case: consider if the vector size is from 0 to INT_MAX and k is at INT_MAX position , then at the last step when we compute mid
// we will do operation : low+high)/2 since low==high therefore: INT_MAX + INT_MAX , not this will overflow since the value is bigger than INT_MAX
//For such case we should write mid=low + (high-low)/2 (try yourself)


//Find Lower Bound
int lowerBound(vector<int> arr,int k){
    int n=arr.size();
    int low=0;
    int high=n-1;
    int ans=n;
    while(low<=high){
        int mid=(low+high)/2;
        if(arr[mid]>=k){
            ans=mid;
            high=mid-1;
        }
        else{
            low=mid+1;
        }
    }
    return ans;
}
//Time Complexity will be O(log2(N)) 


//Find Upper Bound
// Upper bound is just similar to lower bound but just remove the equal sign
// That is you need to find the number > than the given number and return its index
int upperBound(vector<int> arr,int k){
    int n=arr.size();
    int low=0;
    int high=n-1;
    int ans=n;
    while(low<=high){
        int mid=(low+high)/2;
        if(arr[mid]>k){
            ans=mid;
            high=mid-1;
        }
        else{
            low=mid+1;
        }
    }
    return ans;
}
//Time Complexity will be O(log2(N))


//Find the largest number in the array <=x
int floor(vector<int> arr,int k){
    int n=arr.size();
    int low=0;
    int high=n-1;
    int ans=-1;
    while(low<=high){
        int mid=(low+high)/2;
        if(arr[mid]<=k){
            ans=mid;
            low=mid+1;
        }
        else{
            high=mid-1;
        }
    }
    return ans;
}
//Time Complexity will be O(log2(N))


//First and last occurence of an element x
// Consider array [1,2,3,4,4,4,5] , if x=4 return {3,5}, if x=2 , return {1,1} , if x=6 return {-1,-1}
//We can combine our upperBound and lowerBound functions to do this, but there are a few cases where they fail
pair<int,int> firstAndLastOcc(vector<int> arr,int k){
    int n=arr.size();
    int lb=lowerBound(arr,k);
    if(lb==n || arr[lb]!=k) return {-1,-1};
    return {lb,upperBound(arr,k)-1}; 
}
//Time Complexity will be 2*O(log2(N))

//Sometimes the interviewer may ask us to solve this question without using the functions for upper and lower bound
//First we create a function to find first occurence
int firstOcc(vector<int> arr,int k){
    int n=arr.size();
    int low=0;
    int high=n-1;
    int first=-1;
    while(low<=high){
        int mid=(low+high)/2;
        if(arr[mid]==k){
            first=mid;
            high=mid-1;
        }
        else if(arr[mid]<k) low=mid+1;
        else high=mid-1;
    }
    return first;
}
//Time Complexity will be O(log2(N)) 


int lastOcc(vector<int> arr,int k){
    int n=arr.size();
    int low=0;
    int high=n-1;
    int last=-1;
    while(low<=high){
        int mid=(low+high)/2;
        if(arr[mid]==k){
            last=mid;
            low=mid+1;
        }
        else if(arr[mid]<k) low=mid+1;
        else high=mid-1;
    }
    return last;
}
//Time Complexity will be O(log2(N)) 


pair<int,int> firstAndLastOcc_scratch(vector<int> arr,int k){
    int first=firstOcc(arr,k);
    if(first==-1) return {-1,-1};
    int last=lastOcc(arr,k);
    return {first,last};
}
//Time Complexity will be O(2*log2(N)) 



//Count Occurences
int totalOcc(vector<int> arr,int k){
    pair<int,int> p=firstAndLastOcc_scratch(arr,k);
    if(p.first==-1) return 0;
    else{
        int ans=p.second-p.first+1;
        return ans;
    }
}
//Time Complexity will be O(*log2(N)) 


//Search in rotated array
int searchInRotatedArr(vector<int> arr,int k){
    int n=arr.size();
    int low=0;
    int high=n-1;
    while(low<=high){
        int mid=(low+high)/2;
        if(arr[mid]==k) return mid;
        else if(arr[high]>=arr[mid]){
            if(k>arr[mid] && k<=arr[high]) low=mid+1;
            else high=mid-1;
        }
        else{
            if(k>=arr[low] && k<arr[mid]) high=mid-1;
            else low=mid+1;
        }
    }
    return -1;
}
//The Time Complexity of all such questions which imploy binary search once is O(log2(N))


//Test of Occurence of an element in a rotated sorted array having duplicates
bool testOcc(vector<int> arr,int k){
    int n=arr.size();
    int low=0;
    int high=n-1;
    while(low<=high){
        int mid=(low+high)/2;
        if(arr[mid]==k) return true;
        
        //Below is the condition where the previous code fails,
        //It is a trick , when you are asked to deal with an array containing duplicates , think first, how would the solution look like if the array contained only unique elements
        //Then identify where the method fails in array with duplicates, Just incorporate that case in the previous code.
        else if(arr[low]==arr[mid]==arr[high]){
            low=low+1;
            high=high-1;
            continue;
        }
        else if(arr[high]>=arr[mid]){
            if(k>arr[mid] && k<=arr[high]) low=mid+1;
            else high=mid-1;
        }
        else{
            if(k>=arr[low] && k<arr[mid]) high=mid-1;
            else low=mid+1;
        }
    }
    return false;
}
//Worst case occurs in arrays like : [3,3,1,3,3,3,3]
//Time Complexity for such case will be O(n/2)


//Find the minimum in rotated array (unique elements)
int minInRotatedArr(vector<int> arr){
    int n=arr.size();
    int low=0;
    int high=n-1;
    int mini=INT_MAX;
    while(low<=high){
        int mid=(low+high)/2;
        if(arr[low]<=arr[high]){
            mini=min(mini,arr[low]);
            return mini;
        }
        if(arr[high]>=arr[mid]){
            mini=min(mini,arr[mid]);
            high=mid-1;
        }
        else{
            mini=min(mini,arr[low]);
            low=mid+1;
        }
    }
    return mini;
}
//Time Complexity will be O(log2(N))


//Do ques 9 when arr has duplicates as well
//We just need to handle some special cases , like when arr[low]=arr[high]=arr[mid]
int minInRotatedArrHavingDuplicates(vector<int> arr){
    int n=arr.size();
    int low=0;
    int high=n-1;
    int mini=INT_MAX;
    while(low<=high){
        int mid=(low+high)/2;
        if(arr[low]==arr[high]){
            mini=min(mini,arr[low]);
            low++;
            high--;
            continue;
        }
        if(arr[low]<=arr[high]){
            mini=min(mini,arr[low]);
            return mini;
        }
        if(arr[high]>=arr[mid]){
            mini=min(mini,arr[mid]);
            high=mid-1;
        }
        else{
            mini=min(mini,arr[low]);
            low=mid+1;
        }
    }
    return mini;
}
//Time Complexity will be O(log2(N)) 


//Find the Number of times the array has been rotated 
//==> Find the index of the minimum element
int noOfRotations(vector<int> arr){
    int n=arr.size();
    int low=0;
    int high=n-1;
    int minIdx=0;
    int mini=INT_MAX;
    while(low<=high){
        int mid=(low+high)/2;
        if(arr[low]<=arr[high]){
            if(arr[low]<=mini){
                minIdx=low;
                mini=arr[low];
            }
            return minIdx;
        }
        if(arr[high]>=arr[mid]){
            if(arr[mid]<=mini){
                minIdx=mid;
                mini=arr[mid];
            }
            high=mid-1;
        }
        else{
            if(arr[low<=mini]){
                mini=arr[low];
                minIdx=low;
            }
            low=mid+1;
        }
    }
    return minIdx;
}
//Time Complexity will be O(log2(N)) 


//Find the only single element appearing in an array of duplexes(all but one element appears twice)
int findSingle_brute(vector<int> arr){
    int n=arr.size();

    //Since the array is sorted , all the element appearing twice will be next to each other, hence the element that appers once , will have both the neighbours different
    if(n==1) return arr[0];
    for(int i=0;i<n;i++){
        if(i==0){
            if(arr[i]!=arr[i+1]) return arr[i];
        }
        else if(i==n-1){
            if(arr[i]!=arr[i-1]) return arr[i];
        }
        else if(arr[i]!=arr[i+1] && arr[i]!=arr[i-1]) return arr[i];
    }
    return -1;
}
//Time Complexity will be O(N)
//Since this array is sorted , hence binary search should be implemented

int findSingle(vector<int> arr){
    int n=arr.size();
    if(n==1) return arr[0];
    if(arr[n-1]!=arr[n-2]) return arr[n-1];
    if(arr[0]!=arr[1]) return arr[0];
    int low=1;
    int high=n-2;
    while(low<=high){
        int mid=(low+high)/2;
        if(arr[mid]!=arr[mid+1] && arr[mid]!=arr[mid-1]) return arr[mid];
        if((mid%2==1 && arr[mid]==arr[mid-1]) || (mid%2==0 && arr[mid]==arr[mid+1])) low=mid+1;
        else high=mid-1;
    }
    return -1;
}
//Time Complexity will be O(log2(N)) 


//Find any peak element(a local maxima) 
//Consider an array : [1,2,3,4,5,4,3,4,5,6,4,3] has two local maxima 5 and 6 
//Just tell any one local maxima, If local maxima doesn't exist ,tell the largest element
//Also , for first and last element (since they don't have two neighbours, we say that the array starts and ends with -inf)
int peakElement(vector<int> arr){
    int n=arr.size();
    if(n==1) return arr[0];
    if(arr[0]>arr[1]) return arr[0];
    if(arr[n-1]>arr[n-2]) return arr[n-1];
    int low=1;
    int high=n-2;
    while(low<=high){
        int mid=(low+high)/2;
        if(arr[mid]>arr[mid-1] && arr[mid]>arr[mid+1]) return arr[mid];
        else if(arr[mid]>arr[mid-1] && arr[mid]<arr[mid+1]) low=mid+1;
        else high=mid-1;
    }
    return -1;
} 
//Time Complexity will be O(log2(N)) 


//Find Square root of a number
int squareRoot_brute(int n){
    int ans=1;
    for(int i=2;i<n;i++){
        if(i*i<=n) ans=i;
        else break;
    }
    return ans;
}
//Time Complexity will be O(n);

// Now consider n=26 so form an array of 26 elements , and apply binary search , the mid element will be 13 , since we know that 13*13 >25 therefore eliminate the part after 13 and so on
int squareRoot(int n){
    int low=1;
    int high=n;
    int ans=1;
    while(low<=high){
        int mid=(low+high)/2;
        if((mid*mid)<=n){//Calculating mid*mid may lead to overflow, hence it will be better to mid<=x/mid
            ans=mid;
            low=mid+1;
        }
        else high=mid-1;
    }
    return ans;
}
//Time Complexity will be O(log2(N)) 


//Find the nth rooth of a number
int nthRoot_overflow(int m,int n){
    int low=1;
    int high=m;
    while(low<=high){
        int mid=(low+high)/2;
        int val=pow(mid,n);
        if(val==m) return mid;
        else if(val<m) low=mid+1;
        else high=mid-1;
    }
    return -1;
}
//Time Complexity will be O(log2(N)) 
//This method does overflow since we are computing mid^n which can be very high for bigger values, a better way will be to keep checking while we raise power , that if at any moment mid^i > m
//We will make a function for that

int func(int mid,int n,int m){
    int ans=1;
    for(int i=1;i<=n;i++){
        ans=ans*mid;
        if(ans>m) return 2;
    }
    if(ans==m) return 1;
    return 0;
}
//Time Complexity will be O(n) 

//Now we write the code again using this function
int nthRoot(int m,int n){
    int low=1;
    int high=m;
    while(low<=high){
        int mid=(low+high)/2;
        int val=func(mid,n,m);
        if(val==1) return mid;
        else if(val==2) high=mid-1;
        else low=mid+1;
    }
    return -1;
}
//Time Complexity will be O(log2(N)) 


//Koko eating bananas (Search same on leetcode for explanation of question)
int kokoEatingBananas_brute(vector<int> arr,int t){
    int n=arr.size();
    int totalTime=0;
    for(int i=1;i<INT_MAX;i++){//Instead of INT_MAX we can use the maximum element in the array
        totalTime=0;
        for(int j=0;j<n;j++){
            totalTime=totalTime+arr[j]/i;
            if(arr[j]%i!=0) totalTime+=1;
        }
        if(totalTime<=t){
            return i;
        }
    }
    return -1;
}
//Time Complexity will be O(log2(N)) 

//We can employ a similar strategy as we did in square root problem, eliminate the section that can't be answers
int kokoEatingBananas(vector<int> arr,int t){
    int n=arr.size();
    int m=maxInArr(arr);
    int low=0;
    int high=m-1;
    while(low<=high){
        int mid=(low+high)/2;
        int timeTaken=timeTakenByKoko(arr,mid);
        if(timeTaken<=t) high=mid-1;
        else low=mid+1;
    }
    return low;
}
//Time Complexity will be O(N) (for max in array function) + O(N) (timeTakenByKoko function) + O(log2(M)) (M is the maximum element in array)


//Minimum days to make n bouquet of m flowers each (see leetcode for detailed ques)
int minDaysToMakeMBouquet(vector<int> arr,int n,int m){
    int low=minInArr(arr);
    int high=maxInArr(arr);
    int ans;
    if(n*m>arr.size()) return -1;
    while(low<=high){
        int mid=(low+high)/2;
        int Bq=totalBouqInMDays(arr,mid,m);
        if(Bq<n) low=mid+1;
        else if(Bq>=n){
            ans=mid;
            high=mid-1;
        }
    }
    return ans;
}
//Time Complexity will be O(n) + O(n) (for min and max in array) and + O(log2 n) 

//Smallest Divisor given a threshold
//Take a number i(>=1) and divide all the elements of the array(take ceiling of the divisors) and sum up all the values you get, the value should not exceed the threshold
int minDivGivenAThreshold(vector<int> arr,int th){
    int low=1;
    int high=maxInArr(arr);
    if(arr.size()>th) return -1;//The least sum of divisors can be equal to arr.size() , if the threshold is even lesser than that , then ques has no solution
    while(low<=high){
        int mid=(low+high)/2;
        int sum=sumOfQuotCeil(arr,mid);
        if(sum>th) low=mid+1;
        else high=mid-1;
    }
    return low;
}
//Time complexity will be Log2(maximum element in arr) *  n(no of elements in array)


//Minimum Capacity of ship to deliver all packages within D days
int minCapacityToDeliverInDDays(vector<int> arr,int D){
    int low=maxInArr(arr);//The ship should have at least capacity to ship the highest package
    int high=sumOfArr(arr);//The highest capacity we will need when we want to ship all the packages in one day. The capacity would be equal to the sum of all the packages
    while(low<=high){
        int mid=(low+high)/2;
        int daysTaken=daysTakenToShip(arr,mid);
        if(daysTaken>D) low=mid+1;
        else{
            high=mid-1;
        }
    }
    return low;
}
//Time Complexity will be O(n)+O(n)+O(log2 N)*O(n);

//Kth missing number 
int KthMissingNumber_brute(vector<int> arr,int K){
    int n=arr.size();
    for(int i=0;i<n;i++){
        if(arr[i]<=K){
            K++;
        }
        else{
            return K;
        }
    }
    return K;
}
//Time Complexity can be again optimised from O(n) to O(logN)

int KthMissingNumber_optimal(vector<int> arr,int K){
    int n=arr.size();
    int low=0;
    int high=n-1;
    while(low<=high){
        int mid=(low+high)/2;
        if((arr[mid]-(mid+1))<K) low=mid+1;
        else high=mid-1;
    }
    //Now the low and high are pointing to neighbours between which the number lies
    int ans=K+high+1;
    return ans;
}
//Time Complexity will be O(log2(N)) 


//Aggressive Cows
int aggressiveCows(vector<int> stalls,int cows){

    //We are expecting the stalls array to be sorted, if its not, then please sort it using:sort(stalls.begin(),stalls.end())
    int n=stalls.size();
    int low=1;
    int high=stalls[n-1]-stalls[0];
    while(low<=high){
        int mid=(low+high)/2;
        if(canWePlace(stalls,mid,cows)){
            low=mid+1;
        }
        else{
            high=mid-1;
        }
    }
    return high;
}
//Time Complexity will be O(log2(N))*O(N) 


//Allocate Books to n students
int allocateBooks(vector<int> books,int s){
    int n=books.size();
    if(n<s) return -1;
    
    //to make sure that everyperson can hold one book we need to start from the max value 
    int low=maxInArr(books);
    
    //The next extreme case will be when all the books go to one student , in that case 
    int high=sumOfArr(books);

    while(low<=high){
        int mid=(low+high)/2;
        int stu=stuAllotedBooks(books,mid);
        if(stu>s){
            low=mid+1;
        }
        else{
            high=mid-1;
        }
    }
    return low;
}
//Time Complexity will be O(log2(N))*O(N) + O(N)+O(N)


//Q.23) Painter's Partition
//Solution is same as allocate books
int paintersPartition(vector<int> arr,int k){
    int n=arr.size();
    if(k>n) return -1;
    int low=maxInArr(arr);
    int high=sumOfArr(arr);
    while(low<=high){
        int mid=(low+high)/2;
        int painters=paintersNeeded(arr,mid);
        if(painters>k) low=mid+1;
        else high=mid-1;
    }
    return low;
}
//Time complexity is the same as previous


//Q.24) Split Array so that max sum of each sub arr is minimum
//Solution is same as allocate books
int splitArrWithMaxSum(vector<int> arr,int k){
    int n=arr.size();
    if(k>n) return -1;
    int low=maxInArr(arr);
    int high=sumOfArr(arr);
    while(low<=high){
        int mid=(low+high)/2;
        int noOfArr=totalSubarr(arr,mid);
        if(noOfArr>k) low=mid+1;
        else high=mid-1;
    }
    return low;
}
//Time Complexity is same as book allocation


//Q.25) Minimise Max Distance Between gas stations (The array will be sorted)
//Watch video for better understanding
//Brute force solution
long double minMaxDistBwGasStations_brute(vector<int> arr,int k){
    int n=arr.size();
    vector<int> howMany(n-1,0);
    for(int gasStat=1;gasStat<=k;gasStat++){
        long double maxSection=-1;
        int maxIdx=-1;
        for(int i=0;i<n;i++){
            long double diff=arr[i+1]-arr[i];
            long double sectionLength=diff/((long double)(howMany[i]+1));
            if(sectionLength>maxSection){
                maxSection=sectionLength;
                maxIdx=i;
            }
        }
        howMany[maxIdx]++;
    }
    long double maxAns=-1;
    for(int i=0;i<n;i++){
        long double diff=arr[i+1]-arr[i];
        long double sectionLength=diff/((long double)(howMany[i]+1));
        maxAns=max(maxAns,sectionLength);
    }
    return maxAns;
}
//Time Complexity will be O(n^2)+O(n)

//Better solution uses the priority queue which stores the maximum element at top
//The push operation in priority queue takes logN time complexity
long double minMaxDistBwGasStations_better(vector<int> arr,int k){
    int n=arr.size();
    vector<int> howMany(n-1,0);
    priority_queue<pair<long double,int>> pq;
    for(int i=0;i<n;i++){
        pq.push({arr[i+1]-arr[i],i});
    }

    for(int gasStat=1;gasStat<=k;gasStat++){
        auto tp=pq.top();
        pq.pop();
        long double secIdx=tp.second;
        howMany[secIdx]++;
        long double iniDiff=arr[secIdx+1]-arr[secIdx];
        long double secLen=iniDiff/((long double)(howMany[secIdx]+1));
        pq.push({secLen,secIdx});
    }
    return pq.top().first;
}
//Time Complexity will be O(N*LogN)+O(k)

//Function to calculate the number of gas stations required
int numberOfGasStationsReq(long double dist,vector<int> arr){
    int cnt=0;
    int n=arr.size();
    for(int i=1;i<n;i++){
        int numberInBw=((arr[i]-arr[i-1])/dist);
        if((arr[i]-arr[i-1])/dist == numberInBw*dist) numberInBw--;
        cnt+=numberInBw;
    }
    return cnt;
}
//Time complexity will be O(N)

//The most optimal solution employs binary search
long double minMaxDistBwGasStations(vector<int> arr,int k){
    int n=arr.size();
    long double low=0;
    long double high=0;
    for(int i=0;i<n-1;i++){
        high=max(high,(long double)(arr[i+1]-arr[i]));
    }

    long double diff=1e-6;
    while(high-low>diff){
        long double mid=(low+high)/(2.0);
        int cnt=numberOfGasStationsReq(mid,arr);
        if(cnt>k) low=mid;
        else high=mid;
    }
    return high;
}
//Time Complexity will be : O(n)+O(nLogn)

//Median of two sorted arrays
//We can first create a new arrays using the double pointer method and then finding the median of the merged array would be easier
double medianOf2SortedArr_brute(vector<int> a,vector<int> b){
    int n=a.size();
    int m=b.size();
    vector<int> mergedArr;
    int i=0;
    int j=0;
    while(i<n && j<m){
        if(a[i]>b[j]){
            mergedArr.push_back(b[j]);
            j++;
        }
        else{
            mergedArr.push_back(a[i]);
            i++;
        }
    }
    while(i<n){
        mergedArr.push_back(a[i]);
        i++;
    }
    while(j<m){
        mergedArr.push_back(b[j]);
        j++;
    }

    int s=mergedArr.size();
    double median;
    if(s%2!=0){
        median=(1.0)*mergedArr[s/2];
    }
    else{
        median=mergedArr[s/2]+mergedArr[(s/2)-1];
        median=median/(2.0);
    }
    return median;
}
//Time complexity will be O(n+m) 
//Space Complexity will be O(n+m)

double medianOf2SortedArr_better(vector<int> a,vector<int> b){
    int n=a.size();
    int m=b.size();
    int s=(n+m);
    if(s==0) return -1;
    int idx1=(s/2)-1;
    int idx2=(s/2);
    int el1;
    int el2;
    int i=0;
    int j=0;
    int cnt=0;
    while(i<n && j<m){
        if(a[i]>b[j]){
            if(cnt==idx1) el1=b[j];
            else if(cnt==idx2) el2=b[j];
            cnt++;
            j++;
        }
        else {
            if(cnt==idx1) el1=a[i];
            else if(cnt==idx2) el2=a[i];
            cnt++;
            i++;
        }
    }

    while(i<n){
        if(cnt==idx1) el1=a[i];
        else if(cnt==idx2) el2=a[i];
        cnt++;
        i++;
    }

    while(j<m){
        if(cnt==idx1) el1=b[j];
        else if(cnt==idx2) el2=b[j];
        cnt++;
        j++;
    }

    double med;
    if(s%2==1) return el2;
    else {
        med=(1.0)*(el1+el2)/(2.0);
    }
    return med;
}
//Time Complexity will be O(n+m)

//Watch video for better explanation
double medianOf2SortedArr_optimal(vector<int> a,vector<int> b){
    int n1=a.size();
    int n2=b.size();
    if(n1>n2) return medianOf2SortedArr_optimal(b,a);
    int low=0;
    int high=n1;
    //Remember you need to find how many elements to take from one array, then how many from the second array would be known automatically
    //Therefore it is good that we start taking elements from the smaller array, in this way range of our binary search would be less

    int left=((n1+n2+1)>>1);
    int n=n1+n2;
    while(low<=high){
        int mid1=((low+high)>>1);
        int mid2=left-mid1;
        int l1=INT_MIN;
        int l2=INT_MIN;
        int r1=INT_MAX;
        int r2=INT_MAX;
        if(mid1<n1) r1=a[mid1];
        if(mid2<n2) r2=b[mid2];
        if(mid1-1>=0) l1=a[mid1-1];
        if(mid2-1>=0) l2=b[mid2-1];
        if(l1<=r2 && l2<=r1){
            if(n%2==1) return max(l1,l2);
            return ((double)(max(l1,l2)+min(r1,r2)))/(2.0);
        }
        else if(l1>r2) high=mid1-1;
        else low=mid1+1;
    }

    return 0;
}
//Time Complexity will be O(Log n)


//Kth element of two sorted arrays
//Similar to the above question
//Brute force : We create a new merged array using two pointer approach, then find the kth element
int kthElementOf2SortedArr_brute(vector<int> a,vector<int> b,int k){
    int n=a.size();
    int m=b.size();
    if(k>(n+m)) return -1;
    vector<int> merged;
    int i=0;
    int j=0;
    while(i<n && j<m){
        if(a[i]>b[j]){
            merged.push_back(b[j]);
            j++;
        }
        else{
            merged.push_back(a[i]);
            i++;
        }
    }

    while(i<n){
        merged.push_back(a[i]);
        i++;
    }

    while(j<m){
        merged.push_back(b[j]);
        j++;
    }

    return merged[k-1];
}
//Time Complexity will be O(n+m)
//Space Complexity will be O(n+m)

//Better approach, we will avoid using any extra approach
int kthElementOf2SortedArr_better(vector<int> a,vector<int> b,int k){
    int n=a.size();
    int m=a.size();
    if(k>(n+m)) return -1;
    int cnt=0;
    int i=0;
    int j=0;
    int curr;
    while(i<n && j<m){
        if(a[i]>b[j]){
            cnt++;
            curr=b[j];
            j++;
        }
        else {
            cnt++;
            curr=a[i];
            i++;
        }
        if(cnt==k) return curr;
    }

    while(i<n){
        cnt++;
        curr=a[i];
        if(cnt==k) return curr;
        i++;
    }

    while(j<n){
        cnt++;
        curr=b[j];
        if(cnt==k) return curr;
        j++;
    }
    return -1;
}
//Time Complexity will be O(n+m) 

//An even better solution, if exists, would have to be binary search
int kthElementOf2SortedArr_optimal(vector<int> a,vector<int> b,int k){
    int n=a.size();
    int m=b.size();
    int t=n+m;
    if(k>t) return -1;
    if(n>m) return kthElementOf2SortedArr_optimal(b,a,k);
    int low=max(0,k-m);
    int high=min(k,n);
    int left=k;
    while(low<=high){
        int mid1=((low+high)>>1);
        int mid2=(left-mid1);
        int l1=INT_MIN;
        int l2=INT_MIN;
        int r1=INT_MAX;
        int r2=INT_MAX;
        if(mid1<n) r1=a[mid1];
        if(mid2<m) r2=b[mid2];
        if(mid1-1>=0) l1=a[mid1-1];
        if(mid2-1>=0) l2=b[mid2-1];
        if(l1<=r2 && l2<=r1) return max(l1,l2);
        else if(l1>r2) high=mid1-1;
        else low=mid1+1;
    }
    return 0;
}
//Time Complexity will be O(log n)

int main(){

    //Your function here
    
    return 0;
}
