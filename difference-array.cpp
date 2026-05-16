/*
Difference Array Technique solves some similar problems and hence may be confused with the segment trees
However they are still very much different from the segment trees
The DAT(Difference Array Technique) uses the same concept as lazy propagation of segment trees where we just update the concerned index and leave the rest as we progress
*/

/*
A Classic Problem can be this
Consider an array [0,0,0,0,0]
We are given 3 queries on it
(2,[2,4]), (1,[0,2]), and (1,[1,2]);
The query is that the first element is the increment value and the second pair is the index which needs to be incremented by the said value
Both the index are inclusive
Let's try doing it

--> 1st Query
Array becomes : [0,0,2,2,2]

--> 2nd Query
Array becomes : [1,1,3,2,2]

--> 3rd Query
Array becomes : [1,2,4,2,2]

A general code for this type of problem would be like this
*/

void update(vector<int> &nums,vector<pair<int,pair<int,int>>> queries){
    int n=nums.size();

    for(auto q:queries){
        int x=q.first;
        int i=q.second.first;
        int j=q.second.second;

        for(int k=i;k<=j;k++) nums[k]+=x;
    }
}
//The code runs two loops, one for q times and the other for n times
//No extra space is used
//Time Complexity will be O(nq)
//Space Complexity will be O(1)

/*
As you see, the time it takes is around O(qn) in the worst case when the index range is [0,n-1] everytime
We can do better than that using the difference array technique
It is similar to lazy propagation

Consider the same array again : [0,0,0,0,0]
Now the first query has index [2,4] with an increment of 2
We only go to the 2nd index and increment the value by 2 and then go the the (4+1)th index and decrement the value by 2
In case the (4+1)th index doesn't exist, we just leave it right away

--> After the first query
Array becomes : [0,0,2,0,0]

--> After the second query
Array becomes : [1,0,2,-1,0]

--> After the third query 
Array becomes : [1,1,2,-2,0]

Now the last step of the difference array technique is to take the prefix sum for each index
Array becomes : [1,2,4,2,2]
Compare this with the earlier array, you will see it is the same


In the previous example we intentionally took an array that was all 0 as our beginning array
However in the case in which this is not so, we first need to make a difference array
The difference array is made as per the following rules : 
diff[0]=arr[0] and diff[i]=arr[i]-arr[i-1]
Therefore for an array say : [2,3,1,2,3]
The corresponding difference array would be : [2,1,-2,1,1]
Now we need to apply the difference array technique on this array only and the result will be the same
*/

#include<bits/stdc++.h>
using namespace std;


/*
Minimum Moves to make array complementary
For explanation refer to Leetcode Problem 1674
Intuition : consider the array [1,2,4,3], with limit 4
Consider pair (1,3) the sum is 4, so if the required sum is 4, that can be achieved in only 0 changes
However if the required sum is different than 4 we may need some changes
What is the range which we can alter the sum in , if we change only one element. Try to observe the minimum this sum can be taken to will be min(a,b)+1
That will be when we preserve the minimal element and change the maximum of the two to 1
The maximum can be max(a,b)+limit, when we preserve the max element of the two and change the other one to limit
What if we change both, in that case the minimum can be 2 when both are changed to 1 and maximum can be 2*limit when both are changed to limit

Method : We will create an array from 0 to all the way 2*limit and put how many moves can we reach that sum, and in the end we will just take the minimum */

//Brute Force 
int minMoves_brute(vector<int> &arr,int limit){
    int n=arr.size();
    vector<int> sum(2*limit+1,0);

    for(int i=2;i<=2*limit;i++){
        for(int j=0;j<n/2;j++){
            int a=arr[j];
            int b=arr[n-j-1];
            int agg=a+b;

            int low=min(a,b)+1;
            int high=max(a,b)+limit;

            if(i==agg) continue;
            if(i>=low && i<=high) sum[i]++;
            else sum[i]+=2;
        }
    }

    int ans=INT_MAX;
    for(int i=2;i<=2*limit;i++) ans=min(ans,sum[i]);

    return ans;
}
//The code runs for two loops of 2*limit and n/2
//The total time taken by both the loops is n*limit
//Space is used by the sum array which is of size 2*limit
//Time Complexity will be O(nl)
//Space Complexity will be O(limit)

//Optimisation : We try to use the difference array technique since this question is similar to range updates
//We will fill the array with 2 and subtract one each time we can get it in lesser sums
//Since we may need last+1 index as the subtraction happens after the last index, we will create an array with one extra size for buffer
//This will save us the case to check if the index was last of not
//Optimal Method
int minMoves(vector<int> &nums,int limit){
    int n=nums.size();
    vector<int> diff(2*limit+2,0);
    
    for(int i=0;i<n/2;i++){
        int a=nums[i];
        int b=nums[n-i-1];
        int sum=a+b;
        
        int low=min(a,b)+1;
        int high=max(a,b)+limit;

        //Fill the array with 2 using DAT
        diff[2]+=2;
        diff[2*limit+1]-=2;

        //Now we start subtracting one if the sum can be reached in one change
        diff[low]+=(-1);
        diff[high+1]-=(-1);

        //We decrease it further by 1 if the sum can be reached by 0 changes
        diff[sum]+=(-1);
        diff[sum+1]-=(-1);
    }

    int ans=INT_MAX;
    int curr=0;

    //Now we iterate through the diff array and pick the minimum prefix sum
    for(int i=2;i<=2*limit;i++){
        curr+=diff[i];
        ans=min(ans,curr);
    }

    return ans;
}
//The code runs for two loops one is n/2 and the other is 2*limit
//Space is used by the diff array
//Time Complexity will be O(n+l)
//Space Complexity will be O(l)


//Variation 2
//This time instead of adding or incrementing for a given pair of indices, we will take xor
//Consider the query : (1,[2,4]) , this means, replace a[i] by a[i]^1 for all i=2 to i=4
//First we do it by brute force as well

//Brute Force
int minXOR_brute(vector<int> &nums,vector<pair<int,pair<int,int>>> &queries){
    int n=nums.size();

    for(auto q:queries){
        int x=q.first;
        int i=q.second.first;
        int j=q.second.second;

        for(int k=i;k<=j;k++) nums[k]^=x;

    }

    int ans=INT_MAX;
    for(int i=0;i<n;i++) ans=min(ans,nums[i]);
    return ans;
}
//The code runs for a total of q*n times in worst case when the range of indices is n length each time
//No extra space is used to solve the problem
//Time Complexity will be O(qn)
//Space Complexity will be O(1)

//Optimisation : We use the same method as difference array technique. Earlier we added the increment value at starting index and subtracted the value at end+1 index
//We use the same logic, also remember, the oppposite of addition was subtraction and the opposite of xor is xor itself
//Then at last we take the prefix xor and output the minimum among all
//However for this, we first need to create the difference array for the xor operations
//Difference array only needs to be created when the array is non-null
//If the array is like [0,0,0..,0] then there is no need to create any separate difference array, as was shown by previous question
//But for this time, we will need to create a separate difference array
//Optimal Method
int minXOR(vector<int> &nums,vector<pair<int,pair<int,int>>> &queries){
    int n=nums.size();
    vector<int> diff(n,0);
    diff[0]=nums[0];
    for(int i=1;i<n;i++) diff[i]=nums[i]^nums[i-1];

    for(auto q:queries){
        int x=q.first;
        int i=q.second.first;
        int j=q.second.second;

        diff[i]^=x;
        if(j+1<n) diff[j+1]^=x;
    }

    int curr=0;
    int ans=INT_MAX;
    for(int i=0;i<n;i++){
        curr^=diff[i];
        ans=min(ans,curr);
    }

    return ans;
}
//The code runs for 3 loops of n+q+n times
//Space is used by the difference array we create to solve the problem
//Time Complexity will be O(n+q)
//Space Complexity will be O(n)

int main(){
    //Your code here
    return 0;
}
