//Hashing
//First we will tell why we need hashing
//Imagine a problem where we are given an array and we have to find whether a particular set of numbers exist in it or not

#include<bits/stdc++.h>
using namespace std;

//We will check for an element n in an array arr
int checkForElement(int arr[],int size,int n){
    int count=0;
    for(int i=0;i<size;i++){
        if(arr[i]==n){
            count++;
        }
    }
    return count;
}
//The time complexity for this code is O(n) when we have to check for one element, suppose we have to check for q elements , Then the time complexity will be 
// O(qn) , Now suppose q=10^5 and n=10^5 then total time will be 10^10 which will amount to 100 seconds( 1 sec for 10^8) 
//Obviously this is very much time(more than a minute)
//Hashing makes it more faster

//Hashing here means prestoring and then fetching when required

//Here's what we will do : 
//First we create an array containing all 0 with a size of n ( where n is the maximum value that can exist in our original array)
int countElement(int arr[],int el,int s){
    int hashedArray[1000];
    for(int i=0;i<1000;i++){
        hashedArray[i]=0;
    }
    //Now we will iterate over our original array , suppose the first element is 2, then we go to index 2 of our hashed array and increase 0 by 1
    //When we encounter another 2 we again increase the count of 1 by 2
    for(int i=0;i<s;i++){
        hashedArray[arr[i]]++;
    }
    return hashedArray[el];
}
//The max size of an array that can be declared is 1e6 inside main() , 
//outside main() , outside any function, it can have a size of 1e7

//Character Hashing
//For this we assume a to be 0 , b to be 1, c to be 2 and so on....
//for this we will use the ASCII values 
//Now small 'a' is 97 and 'z' is 122
//when we do 'f' - 'a' we get 102-97 = 5 which is exactly what we want
int countChar(string st,char c,int s){
    int hashedArr[26];
    for(int i=0;i<26;i++){
        hashedArr[i]=0;
    }
    for(int i=0;i<s;i++){
        hashedArr[st[i]-'a']++;
    }
    return hashedArr[c-'a'];
}

//When uppercase characters are also involved
//this time instead of storing a at 0 , b at 1 .. just store a at its respective ASCII value

int countChar_involvingUpperCase(string st,char c,int s){
    int hashedArr[255];
    for(int i=0;i<255;i++){
        hashedArr[i]=0;
    }
    for(int i=0;i<s;i++){
        hashedArr[st[i]]++;
    }
    return hashedArr[c];
}

//Now coming back to our earlier problem of hashing integers, suppose the maximum number that you need to check for is 1e10 , since an array can only store upto 1e7,
//the earlier concept won't work, For such cases we use map or unordered map from Standard template library

int countElementUsingMap(int arr[],int n,int s){
    map<int,int>mpp;
    for(int i=0;i<s;i++){
        mpp[arr[i]]++;
    }
    return mpp[n];
}

//Using the map for character hashing
int countCharUsingMap(string st,char c,int size){
    map<char,int>mpp;
    for(int i=0;i<size;i++){
        mpp[st[i]]++;
    }
    return mpp[c];
}

//However , the time complexity of any operation of fetching or storing inside a map is O(logN)
//We also have unordered map which can help

//just add unordered before map in the previous code
int countCharUsingUnorderedMap(string st,char c,int size){
    unordered_map<char,int>mpp;
    for(int i=0;i<size;i++){
        mpp[st[i]]++;
    }
    return mpp[c];
}

//In unordered map the average and best case time complexity for storing and fetching is O(1) (constant time complexity) whereas for worst case it is O(N);
//Therefore our first choice will be unordered map, but if it says time limit exceeded then only switch to map(that is for the worst case)

//Another difference between map and unordered map is that in map any data set (even pair) can become a key , but in unordered map , it allows only some data sets like char,string,int etc(google more)

int main(){
    return 0;
}
