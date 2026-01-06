//Recursion and Backtracking


//Recursion happens when a function calls itself

#include<bits/stdc++.h>
using namespace std;

//Create a function that prints 1
void print1(){
    cout<<1<<"\n";
}

//Creating a function that executes infinitely and prints 1
//Such a function causes a segmentation error and this condition is also called stack overflow
void print1Inf(){
    cout<<1<<"\n";

    //Here we call the function inside itself, A very basic example of recursion
    print1Inf();
}

//To prevent such infinite recursion we must give a terminating condition (base condition)

//With a base condition
void printCount(int count=1){
    cout<<count<<"\n";
    count++;
    if(count==10){
        return;
    }
    else {
        printCount(count);
    }
}


//Now we will do some questions on recursions

//Print Name n times
//This has time complexity O(n) and stack space (space complexity) is also O(n) as n functions are waiting in the stack to be executed
void printName(int i=0,int n=5){
    if(i>n){
        return;
    }
    cout<<"Raj\n";
    printName(i+1,n);
}

//Print linearly from 1 to n
void printFirstN(int i=1,int n=5){
    if(i>n){
        return;
    }
    cout<<i<<"\n";
    printFirstN(i+1,n);
}

//Print linearly from n to 1
void printFirstN_Reverse(int i=1,int n=5){
    if(i>n){
        return;
    }
    printFirstN_Reverse(i+1,n);
    cout<<i<<"\n";
}

//Calculate the sum of first n natural numbers
//My method
int sumToN(int n){
    if(n==0){
        return 0;
    }
    return n+sumToN(n-1);
}
//method 2
void sumToN_striverMethod(int n,int sum){
    if(n<1){
        cout<<sum<<"\n";
        return;
    }
    sumToN_striverMethod(n-1,sum+n);
}


//Calculate factorial of n
//My method
int factorial(int n){
    if(n==1){
        return 1;
    }
    return n*factorial(n-1);
}
//method 2
void factorial_striverMethod(int n,int fac){
    if(n==1){
        cout<<fac<<"\n";
        return;
    }
    factorial_striverMethod(n-1,fac*n);
};


//Count Good Numbers
//A number that has even numbers at even indices and prime numbers at odd indices
//We will be given n, and we need to tell, how many numbers of that length are good numbers
//Brute Force
//We make some helper functions
bool isPrime(int n){
    if(n<=1) return false;
    for(int i=2;i*i<=n;i++){
        if(n%i==0) return false;
    }
    return true;
}
bool isGood(int x){
    string s=to_string(x);
    int n=s.size();
    for(int i=0;i<n;i++){
        int y=s[i]-'0';
        if(i%2==0 && y%2!=0) return false;
        if(i%2!=0 && !isPrime(y)) return false;
    } 
    return true;
}
int countGood_brute(int n){
    int start=pow(10,n-1);
    int end=pow(10,n)-1;
    int cnt=0;
    for(int i=start;i<=end;i++){
        if(isGood(i)) cnt++;
    }
    return cnt;
}
//The for loop in countGood runs for about z times where z is 10^n - 10^(n-10) which is about pow(10,n)
//The loop in is good runs for n times
//the isPrime runs the loop for max 5 times since this many times it has to check
//Calculating total time will be pow(10,n)*n*5
//No extra space is used to solve the question
//Time Complexity will be n*10^n
//Space Complexity will be O(1)

//Optimal Method
//This time we will form the good numbers from the start
//In case the digit allows leading zeroes, change the initial cnt to 5
int countGood(int n){

    //If n==1 we can just return 5 (1,3,5,7,9)
    if(n==1) return 5;

    int cnt=4;
    for(int i=1;i<n;i++){
        if(i%2==0) cnt=cnt*5;
        else cnt=cnt*4;
    }
    return cnt;
}
//The code runs for n times
//No extra space is needed
//Time Complexity will be O(n)
//Space Complexity will be O(1)


//Reverse an array 
//My Method
void revArray(int currArr[],int n){
    if(n==-1){
        return;
    }
    cout<<currArr[n]<<"\n";
    revArray(currArr,n-1);
}
//Striver's Method
void revArray_striver(int arr[],int i,int n){
    if(i>=n/2){
        return;
    }
    swap(arr[i],arr[n-i-1]);
    revArray_striver(arr,i+1,n);
}


//Test for palindrome
//My Method
bool palindromeTest(string str,int n,int i){
    if(i>=n/2){
        return true;
    }
    if(str[i]!=str[n-i-1]){
        return false;
    }
    return palindromeTest(str,n,i+1);
}



//Recursive Implementation of atoi
// atoi is a built in function that converts strings to integer
int atoiHelper(string &str,int idx){
    if(idx==0) return str[0]-'0';
    int lastChar=str[idx]-'0';
    return atoiHelper(str,idx-1)*10+lastChar;
}
int recursiveAtoI(string &str){
    int n=str.size();
    if(n==0) return -1;
    return atoiHelper(str,n-1);
}
//Time Complexity will be O(n)
//Space Complexity will be O(n)


//Recursive Implementation of pow(x,n) function
double powerHelper(double x,int n){
    if(n==0) return 1.00;
    if(n%2==0) return powerHelper(x*x,n/2);
    else return 1.0*x*powerHelper(x,n-1);
}
double power(double x,int n){
    if(n==0) return 1.00;
    bool sign=n>0;
    int abs_n=abs(n);
    double ans=powerHelper(x,abs_n);
    if(sign) return ans;
    ans=(1.00)/(1.00*ans);
    return ans;
}
//Time Complexity will be O(log n)



//Functions with multiple recursions calls
//A thing to be noted in multiple recursion calls is that for eg: return = recursion1 + recursion2 , then only after
//recursion1 is fully completed , recursion2 takes place
//Print the nth fibonacci's term
//This is a problem where the recursion will be called twice since f(n)=f(n-1) + f(n-2)
int fibonacciTerm(int n){
    if(n<=1){
        return n;
    }
    return (fibonacciTerm(n-1) + fibonacciTerm(n-2));
}

void printF(int ind,vector<int> &temp,vector<int> arr,int n){
    if(ind==n){
        for(auto it:temp) cout<<it<<",";
        if(temp.size()==0) cout<<"{}";
        cout<<"\n";
        return;
    }
    
    //Not picking the element
    printF(ind+1,temp,arr,n);

    //Take or pick the particular index into the sequence
    temp.push_back(arr[ind]);
    printF(ind+1,temp,arr,n);
    temp.pop_back();
}

void allSubseq(vector<int> arr){
    int n=arr.size();
    vector<int> temp;
    printF(0,temp,arr,n);
}
//Time Complexity will be O((pow(2,n)*n)) since total subsets are 2^n and n for printing the subsets
//Space Complexity will be O(n) , make the recursion tree, and see the no. of levels , it is 3 therefore 3 recusion calls waiting at a moment, which is equal to arrays length

void printFx(int ind,vector<int> &temp,int sum,int k,vector<int> arr){
    int n=arr.size();
    if(ind==n){
        if(k==sum){
            for(auto it:temp) cout<<it<<",";
            cout<<"\n";
        }
        return;
    }

    //Not picking the element 
    printFx(ind+1,temp,sum,k,arr);

    //picking the element
    sum+=arr[ind];
    temp.push_back(arr[ind]);
    printFx(ind+1,temp,sum,k,arr);
    temp.pop_back();
    sum-=arr[ind];

}

void subSeqsWithSumK(vector<int> arr,int k){
    vector<int> temp;
    printFx(0,temp,0,k,arr);
}
//Time Complexity will be about the same as previous(pow(2,n)*n)

//What if the question asks us to print only or anyone subsequence with the given sum
//A smart trick would be to declare a global variable bool flag=false (global means declared outside int main()) and as modifying the code inside the if condition as 
// if(k==sum && flag==false) then inside the if statement doing flag=true. This way , as soon as the if statement in executed for the first time, the flag is set to false, never repeating the if again
bool flag=false;
void printF2(int ind,vector<int> temp,int sum,int k,vector<int> arr){
    int n=arr.size();
    if(ind==n){
        if(sum==k && flag==false){
            for(auto it:temp) cout<<it<<",";
            if(temp.size()==0) cout<<"{}";
            cout<<"\n";
            bool flag=true;
        }
        return;
    }

    //Not picking the element
    printF2(ind+1,temp,sum,k,arr);

    //Picking the element
    sum+=arr[ind];
    temp.push_back(arr[ind]);
    printF2(ind+1,temp,sum,k,arr);
    temp.pop_back();
    sum-=arr[ind];

}
void subSeqWithSumK_brute(vector<int> arr,int k){
    vector<int> temp;
    printF2(0,temp,0,k,arr);
}
//Same Time complexity as previous one

//This is however not preferred because of the use of global variables
//We will try having a condition in the base case and the subsequent function will be executed only if the condition is met
bool printF3(int ind,int sum,vector<int> temp,vector<int> arr,int k){
    int n=arr.size();
    if(ind==n){
        if(sum==k){
            for(auto it:temp) cout<<it<<",";
            if(temp.size()==0) cout<<"{}";
            cout<<"\n";
            return true; //Returning true, means the pattern is printed once
        }
        return false; //Returning false, means the pattern in not printed yet
    }

    //Not picking the element, but this time, we will make sure that the function does not proceed further in case the condition is fullfilled
    if(printF3(ind+1,sum,temp,arr,k)==true) return true;

    //Picking the element with the condition as previous
    temp.push_back(arr[ind]);
    sum+=arr[ind];
    if(printF3(ind+1,sum,temp,arr,k)==true) return true;
    sum-=arr[ind];
    temp.pop_back();
    return false;
}
void subSeqWithSumK(vector<int> arr,int k){
    vector<int> temp;
    printF3(0,0,temp,arr,k);
}
//Time Complexity will be the somewhat lesser than the previous pow(2,n)*n but maybe almost the same

//Next is counting the number of subsequences with sum k
//This time we won't we needing a temp array to store the elements, since we are not going to print them
//In such question, we return 1 if the condition is met and 0 if the condition is not met

int printF4(int ind,int sum,vector<int> arr,int k){
    if(sum>k) return 0;
    int n=arr.size();
    if(n==ind){
        if(sum==k) return 1;
        return 0;
    }

    //Not picking the element
    int x=printF4(ind+1,sum,arr,k);

    //Picking the element
    sum+=arr[ind];
    int y=printF4(ind+1,sum,arr,k);
    sum-=arr[ind];
    return (x+y);
}
int countSubSeqsWithSumK(vector<int> arr,int k){
    return printF4(0,0,arr,k);
}
//Time complexity will be pow(2,n) (similar to previous but the time for printing is not there)


//Combination sum
//Print all subsequences with sum == k
void printF5(int idx,int currSum,vector<int> arr,vector<int> &temp,int reqSum){
    int n=arr.size();
    if(idx==n){
        if(currSum==reqSum){
            for(auto it:temp) cout<<it<<",";
            if(temp.size()==0) cout<<"{}";
            cout<<"\n";
        }
        return;
    }

    //Passing function without selecting element
    printF5(idx+1,currSum,arr,temp,reqSum);

    //Pushing the element
    temp.push_back(arr[idx]);
    currSum+=arr[idx];
    printF5(idx+1,currSum,arr,temp,reqSum);

    temp.pop_back();
    currSum-=arr[idx];
    return ;
}
void combinationSum(vector<int> arr,int k){
    int n=arr.size();
    vector<int> temp;
    printF5(0,0,arr,temp,k);
}
//Time Complexity will be about pow(2,n)
//Space will also be used to store answers to print them, can't pinpoint SC since it will depend on the number of combinations, but say k (if k is the average combination length)
//Then Space Complexity will be k*x (k : avg length of combinations, x : total combinations)



//Combination Sum II
//Only unique pairs, and the pairs must be in sorted order, lexicographically
//Brute Force implies use of set's property to store only unique elements, therefore we first sort the array to solve the problem
void fCSII_brute(int idx, int sum, int k, vector<int> arr, vector<int> &temp, set<vector<int>> &ans){
    int n=arr.size();
    if(idx==n){
        if(sum==k) ans.insert(temp);
        return;
    }
    //Not picking the element
    fCSII_brute(idx+1,sum,k,arr,temp,ans);

    //Picking the element
    temp.push_back(arr[idx]);
    fCSII_brute(idx+1,sum+arr[idx],k,arr,temp,ans);
    temp.pop_back();
}

set<vector<int>> combinationSumII_brute(vector<int> arr, int k){
    vector<int> temp;
    sort(arr.begin(),arr.end());
    set<vector<int>> ans;
    fCSII_brute(0,0,k,arr,temp,ans);
    return ans;
}


//Optimal Method 
//Look video for detailed explanation

void fCSII(int idx, int k, vector<int> &arr, vector<int> &temp, vector<vector<int>> &ans){
    int n=arr.size();
    if(k==0){
        ans.push_back(temp);
        return;
    }
    for(int i=idx;i<n;i++){
        if(i>idx && arr[i]==arr[i-1]) continue;
        if(arr[i]>k) break;
        temp.push_back(arr[i]);
        fCSII(i+1,k-arr[i],arr,temp,ans);
        temp.pop_back();
    }
}
vector<vector<int>> combinationSumII(vector<int> &arr, int k){
    sort(arr.begin(),arr.end());
    vector<vector<int>> ans;
    vector<int> temp;
    fCSII(0,k,arr,temp,ans);
    return ans;
}


//Subset Sum I
//Find sum of all subsets
void allSubsets(int idx,vector<int> &arr,vector<int> &temp,vector<vector<int>> &listOfSubsets){
    int n=arr.size();
    if(idx==n){
        listOfSubsets.push_back(temp);
        return;
    }

    //Not Picking the element
    allSubsets(idx+1,arr,temp,listOfSubsets);

    //Picking the element
    temp.push_back(arr[idx]);
    allSubsets(idx+1,arr,temp,listOfSubsets);
    temp.pop_back();
}

int subsetSumI(vector<int> arr){
    vector<vector<int>> listOfSubsets;
    vector<int> temp;

    //We first find all the subsets
    allSubsets(0,arr,temp,listOfSubsets);

    //Now we sum them up
    int sum=0;
    int n=listOfSubsets.size();
    for(auto it:listOfSubsets){
        for(auto s:it) sum+=s;
    }
    return sum;
}


//Subset Sum II 
//This time, give the sums in an array, for eg for set {1,2} the ans would be : {0,1,2,3}
void fxSSII(int idx,int sum,vector<int> &arr,vector<int> &ans){
    int n=arr.size();
    if(idx==n){
        ans.push_back(sum);
        return;
    }

    //Not picking the element
    fxSSII(idx+1,sum,arr,ans);

    //Picking the element
    fxSSII(idx+1,sum+arr[idx],arr,ans);
}
vector<int> subsetSumI_variationII(vector<int> arr){
    vector<int> ans;
    fxSSII(0,0,arr,ans);
    sort(ans.begin(),ans.end());
    return ans;
}



//Subset Sum II 
//Return all unique subsets
void ssIIbHelper(int idx,int n,vector<int> arr,vector<int> &temp,set<vector<int>> &ans){
    if(idx==n){
        ans.insert(temp);
        return;
    }

    //Pick the element 
    temp.push_back(arr[idx]);
    ssIIbHelper(idx+1,n,arr,temp,ans);
    temp.pop_back();
    
    //Not Picking the element
    ssIIbHelper(idx+1,n,arr,temp,ans);
}
vector<vector<int>> subsetSumII_brute(vector<int> arr){
    int n=arr.size();
    set<vector<int>> st;
    vector<int> temp;
    ssIIbHelper(0,n,arr,temp,st);

    vector<vector<int>> ans;
    for(auto it:st){
        vector<int> temp;
        for(auto p:it) temp.push_back(p);
        ans.push_back(temp);
    }
    return ans;
}

//Optimal Method
//Similar to Combination Sum II
void ssIIHelper(int idx,int n,vector<int> &arr,vector<int> &temp,vector<vector<int>> &ans){
    ans.push_back(temp);
    for(int i=idx;i<n;i++){
        if(i>idx && arr[i]==arr[i-1]) continue;
        temp.push_back(arr[i]);
        ssIIHelper(i+1,n,arr,temp,ans);
        temp.pop_back();
    }
}
vector<vector<int>>subsetSumII(vector<int> arr){
    int n=arr.size();
    vector<int> temp;
    vector<vector<int>> ans;
    sort(arr.begin(),arr.end());
    ssIIHelper(0,n,arr,temp,ans);
    return ans;
}
//Time Complexity will be O(pow(2,n)*n)
//We are going to store atmost pow(2,n) subsets in the worst case so that much space is required
//Also considering avg length of each subset will be k
//Space Complexity will be O(pow(2,n)*k)



//All Permutations of a String or Array
//Brute Force
//This method uses some extra space
void allPermIHelper(int n,vector<int> &temp,vector<bool> &vis,vector<int> &arr,vector<vector<int>> &ans){
    if(temp.size()==n){
        ans.push_back(temp);
        return;
    }
    for(int i=0;i<n;i++){
        if(vis[i]) continue;
        vis[i]=true;
        temp.push_back(arr[i]);
        allPermIHelper(n,temp,vis,arr,ans);
        temp.pop_back();
        vis[i]=false;
    }
    
}
vector<vector<int>> allPermutations_brute(vector<int> &arr){
    int n=arr.size();
    vector<vector<int>> ans;
    vector<int> temp;

    //We keep a track of visited elements
    vector<bool> vis(n,false);
    allPermIHelper(n,temp,vis,arr,ans);
    return ans;
}
//We are generating n factorial permutations and we are also running the loop n times
//Time Complexity will be O(n!*n)
//Space Complexity will be O(n+n+n) (n for recursion stack space)

//Optimal Method
//We use the swap method, and hence we can avoid using the visited array
void permutationsHelper(int idx,int n,vector<int> &arr,vector<vector<int>> &ans){
    if(idx==n){
        ans.push_back(arr);
        return;
    }

    for(int i=idx;i<n;i++){
        swap(arr[i],arr[idx]);
        permutationsHelper(idx+1,n,arr,ans);
        swap(arr[i],arr[idx]);
    }
}
vector<vector<int>> allPermutations(vector<int> &arr){
    int n=arr.size();
    vector<vector<int>> ans;
    permutationsHelper(0,n,arr,ans);
    return ans;
}
//n! factorial permutations are generated and a loop of n is run through
//A n stack space is used as recursion stack space
//Time Complexity will be O(n!*n)
//Space Complexity will be O(n)
//N Queens Problem
void solveQueen(int col,vector<string> &board,vector<vector<string>> &ans,vector<int> &leftRow,vector<int> &upperDiagonal,vector<int> &lowerDiagonal,int n){
    if(col==n){
        ans.push_back(board);
        return;
    }
    for(int row=0;row<n;row++){
        if(leftRow[row]==0 && lowerDiagonal[row+col]==0 && upperDiagonal[n-1+col-row]==0){
            board[row][col]='Q';
            leftRow[row]=1;
            lowerDiagonal[row+col]=1;
            upperDiagonal[n-1+col-row]=1;
            solveQueen(col+1,board,ans,leftRow,upperDiagonal,lowerDiagonal,n);
            board[row][col]='.';
            leftRow[row]=0;
            lowerDiagonal[row+col]=0;
            upperDiagonal[n-1+col-row]=0;
        }
    }
}
vector<vector<string>> nQueens(int n){
    vector<vector<string>> ans;
    vector<string> board(n);
    string s(n,'.');
    for(int i=0;i<n;i++) board[i]=s;
    vector<int> leftRow(n,0);
    vector<int> upperDiagonal(2*n-1,0);
    vector<int> lowerDiagonal(2*n-1,0);
    solveQueen(0,board,ans,leftRow,upperDiagonal,lowerDiagonal,n);
    return ans;
}

//Sudoku Solver
//Brute Force
bool checkForValidity(int k,int i,int j,vector<vector<char>> &board){
    //Check for Column Validity
    int col=(i/3)*3;
    int row=(j/3)*3;
    for(int x=row;x<row+3;x++){
        for(int y=col;y<col+3;y++){
            if(board[x][y]==k+'0') return false;
        }
    }

    //Check for row validity
    for(int x=0;x<9;x++){
        if(board[i][x]==k+'0') return false;
    }

    //Check for column validity
    for(int y=0;y<9;y++){
        if(board[y][j]==k+'0') return false;
    }

    return true;
}
void sudokuHelper(vector<vector<char>> &board,bool &isSolved){
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if(board[i][j]!='.') continue;
            for(int k=1;k<=9;k++){
                if(!checkForValidity(k,i,j,board)) continue;
                board[i][j]=k+'0';
                sudokuHelper(board,isSolved);
                if(isSolved) return;
                board[i][j]='.';
            }
            return;
        }
    }
    isSolved=true;
}
void sudokuSolver_brute(vector<vector<char>> &board){
    bool isSolved=false;
    int n=9;
    int m=9;
    sudokuHelper(board,isSolved);
}

//Optimal Code's intution is almost same, but the validity function, instead of using 3 loops, does the job in just one
//Also the code is somewhat more readable
bool isValid(vector<vector<char>> &board,int row,int col,char c){
    for(int i=0;i<9;i++){
        if(board[i][col]==c) return false;
        if(board[row][i]==c) return false;
        if(board[3*(row/3) + i/3][3*(col/3)+i%3]==c) return false;
    }
    return true;
}
bool solve(vector<vector<char>> &board){
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if(board[i][j]=='.'){
                for(char c='1';c<='9';c++){
                    if(isValid(board,i,j,c)){
                        board[i][j]=c;

                        if(solve(board)) return true;
                        else board[i][j]='.';
                    }
                }
                return false;
            }
        }
    }
    return true;
}

void sudokuSolver(vector<vector<char>> &board){
    solve(board);
}
//Three loops in solve fxn => 9*9*9 and the isValid fxn also has a loop running 9 times so total of 9^4
//The above logic is wrong, since this is backtracking, and hence the loop runs much more than visible
//We can think of it like that, for every empty cell, it has 9 ways the recursion would run, so if there are m empty cell the recursion would run 9^m times
//Since in the worst case all the cells can be empty, therefore m=81, hence the recursion would run for 9^81 times
//Only recursion stack space is being used, which is equal to m(no of empty cells)
//Time Complexity will be O(9^m)
//Space Complexity will be O(m)



//M-Coloring Graph
//Similar to bipartite graph problem, but here we have to colour with m colours, such that no two adjacent cells have the same colour
//We can denote colours via numbers
//We just have to tell whether or not we can colour the graph or not
//We will use the adjacency matrix this time instead of adjacency list/array
bool isSafeCol(int node,int col,int n,int m,vector<int> &color,vector<vector<int>> &adj){
    for(int k=0;k<n;k++){
        if(k==node) continue;
        if(adj[k][node]==1 && color[k]==col) return false;
    }
    return true;
}

bool mColHelper(int node,vector<int> &color,int m,int n,vector<vector<int>> &adj){
    if(node==n) return true;
    for(int i=1;i<=m;i++){
        if(isSafeCol(node,i,n,m,color,adj)){
            color[node]=i;
            if(mColHelper(node+1,color,m,n,adj)) return true;
            color[node]=0;
        }
    }
    return false;
}
bool mColorGraph(int n,vector<vector<int>> &edges,int m){
    if(n<=m) return true;
    vector<vector<int>> adj(n,vector<int> (n));
    for(auto it:edges){
        adj[it[0]][it[1]]=1;
        adj[it[1]][it[0]]=1;
    }
    vector<int> color(n,0);
    if(mColHelper(0,color,m,n,adj)) return true;
    return false;
}
//We are trying m colours at every node(n in total)=> n^m
//Time Complexity will be O(n^m)
//Space Complexity will be O(n+n)(excluding the space used for adjacency matrix)



//Palindrome Partitioning
//Watch Video for better explanation
bool isPartitionAllowed(string &str,int start,int end){
    while(start<=end){
        if(str[start++]!=str[end--]) return false;
    }
    return true;
}
void palindromePartitionHelper(int idx,string &str,vector<string> &path,vector<vector<string>> &res){
    if(idx==str.size()){
        res.push_back(path);
        return;
    }
    for(int i=idx;i<str.size();i++){
        if(isPartitionAllowed(str,idx,i)){
            path.push_back(str.substr(idx,i-idx+1));
            palindromePartitionHelper(i+1,str,path,res);
            path.pop_back();
        }
    }
}
vector<vector<string>> palindromePartition(string str){
    vector<vector<string>> res;
    vector<string> path;
    palindromePartitionHelper(0,str,path,res);
    return res;
}
//Recursion stack space of n will be used and n space will be used for pushing path to res
//Time Complexity will be O(2^(n-1))
//Space Complexity will be O(n)+O(n)


//Rat in a Maze
//Rat can move UP(U),DOWN(D),RIGHT(R),LEFT(L)
//The matrix has 0 and 1, a rat can't move through 0
//We need to return all the paths and that too in lexicographical order
//The matrix is n*n size
//The rat will start from (0,0) and need to go to (n-1,n-1)
void mazeHelper(int i,int j,int n,vector<vector<int>> &mat,vector<vector<int>> &vis,string &temp,vector<string> &ans){
    if(i==n-1 && j==n-1){
        ans.push_back(temp);
        return;
    }

    //Moving in four directions
    //We move in order : D then L then R then U, so to maintain lexicographical order
    vector<int> dx={1,0,0,-1};
    vector<int> dy={0,-1,1,0};
    string dir="DLRU";
    for(int k=0;k<4;k++){
        int ni=i+dx[k];
        int nj=j+dy[k];
        if(ni>=0 && ni<n && nj>=0 && nj<n && mat[ni][nj]==1 && vis[ni][nj]==false){
            char c=dir[k];
            temp.push_back(c);
            vis[ni][nj]=true;
            mazeHelper(ni,nj,n,mat,vis,temp,ans);
            temp.pop_back();
            vis[ni][nj]=false;
        }
    }
}
vector<string> ratInAMaze(vector<vector<int>> &mat){
    int n=mat.size();
    vector<string> ans;
    string temp="";
    vector<vector<int>> vis(n,vector<int> (n,0));
    vis[0][0]=true;
    mazeHelper(0,0,n,mat,vis,temp,ans);
    return ans;
}
//At each point we have 4 choices, and there are total of n*n such cells therefore the code will run for 4^(n*n) times
//A vis array means a space of n*n, temp uses n, and recursion stack space is n2
//Time Complexity will be O(4^(n2))
//Space Complexity will be O(n2+n+n2)


//Kth Permutation
//Find out the permutation that appears in kth number if all the permutations are arranged in increasing order
//You will be given n and k, if n=3 and k=2 then the kth permutation is 132(first is 123)
//Brute Force 
//Generate all the permutations, store them in a vector<string> then sort the vector
//Sorting will happen in lexicographical order, but if digits are same then lexicographical sort = numeric sort

//Optimal Method
//Same concept as the one question in mathematics where we used to find the position of a word in dictionary
//Indexing starts at 0, therefore first permuation is 0th and hence we need to find the (k-1)th permutation
string kthPermutation(int n,int k){
    int fact=1;
    vector<int> numbers;
    for(int i=1;i<n;i++){
        fact=fact*i;
        numbers.push_back(i);
    }
    numbers.push_back(n);
    string ans="";
    k=k-1;//Due to 0 based indexing

    while(true){
        ans=ans+to_string(numbers[k/fact]);
        numbers.erase(numbers.begin()+k/fact);
        if(numbers.size()==0) break;
        k=k%fact;
        fact=fact/numbers.size();
    }
    return ans;
}
//Time Complexity will be O(n2)
//Space Complexity wiill be O(n)

int main(){

    //Your code here
    return 0;
}
