//Stacks

/* 
Stack is a data structure that stores a certain type of data(can be int,bool etc)
It follows the LIFO mechainism(last in first out)
We use push to add elements and pop to remove elements(pop removes the last element)
The top is used to see the top element(in a stack the element at the top is the one inserted most recently) 
We also have a size function to get the size(length) of stack
*/

//Queues

/*
Similar to stack but follows the FIFO mechanism(First in First out) just like in a queue
Also has similar function like:push,top,pop,size
Pop function removes the element entered first(like in a queue)
Top function also gives the first element entered in the array(not removes it, pop does it)
*/

//Syntax is like : stack<int> st and queue<int> q;

//Logic behind push, pop and top functions operations
//We will be using arrays to understand:
    /* We use a top variable initially with value -1 , if the element is pushed , then we increase top by 1 (now 0) and then push the element to the index it points
       If pop is used , we first delete the element at the place of top and then decrease top by 1
       If size is used we return top+1 */
#include<bits/stdc++.h>
using namespace std;

//Time Complexity, if not mentioned is either constant or very easy to figure out, most probably O(n) where n can be known by reading the function
//Space Complexity if not mentioned is constant, that is O(1)

//We can use a class to understand the operations of push ,pop etc:

//Implementing Stack using array
class StackImplementation{
    public:
        int top=-1;
        int st[10];
        void push(int x){
            top=top+1;
            if(top>10) cout<<"Out of bound";
            st[top]=x;
        }

        int topEl(){
            if(top==-1) return -1;
            else return st[top];
        }

        void pop(){
            if(top==-1) return;
            else top--;
        }

        int size(){
            return top+1;
        }

};



//Implementing Queue Using array
class QueueImplementation{
    int size=4;
    int start=-1;
    int end=-1;
    int queue[4];
    int currSize=0;
    void push(int x){
        if(currSize==size) cout<<"Out of bound";
        else if(currSize==0){
            start=0;
            end=0;
        }
        else{
            end=(end+1)%size;
        }
        queue[end]=x;
        currSize++;
    }

    int top(){
        if(currSize==0) return -1;
        return queue[start];
    }

    void pop(){
        int el;
        if(currSize==0) return;
        else if(currSize==1){
            el=queue[start];
            start=-1;
            end=-1;
        }
        else{
            el=queue[start];
            start=(start+1)%size;
        }
        currSize--;
        return;
    }

    int curSize(){
        return currSize;
    }

};


class Node{
    public:
        int data;
        Node* next;
        Node(int data1){
            this->data=data1;
            this->next=nullptr;
        }
};



//Implementing stack using Linked List
class stackImpUsingLL{
    public:
        Node* top;
        int size=0;
        void push(int x){
            Node* temp=new Node(x);
            temp->next=top;
            top=temp;
            size++;
        }

        void pop(){
            Node* temp=top;
            top=temp->next;
            delete temp;
            size--;
        }

        int topEl(){
            return top->data;
        }

        int currSize(){
            return size;
        }
};




//Implementing Queue Using Linked List
class queueImpUsingLL{
    public:
        Node* start;
        Node* end;
        int size=0;
        void push(int x){
            Node* temp=new Node(x);
            if(start==NULL){
                start=temp;
                end=temp;
            }
            else{
                end->next=temp;
            }
            size++;
        }

        void pop(){
            if(start==NULL) return;
            Node* temp=start;
            start=start->next;
            delete temp;
            size--;
        }

        int top(){
            if(start==NULL) return -1;
            return start->data;
        }

        int currSize(){
            return size;
        }
};




//Implementing Stack Using Queue
class stackImpUsingQueue{
    public:
        queue<int> q;
        void push(int x){
            int s=q.size();
            q.push(x);
            for(int i=1;i<s;i++){
                q.push(q.front());
                q.pop();
            }
        }

        void pop(){
            q.pop();
        }

        int top(){
            return q.front();
        }

        int size(){
            return q.size();
        }
};




//Implementing Queue Using Single Stack
class queueImpUsingStack{
    public:
        stack<int> s1;
        stack<int> s2;
        void push(int x){
            while(s1.size()){
                s2.push(s1.top());
                s1.pop();
            }
            s1.push(x);
            while(s2.size()){
                s1.push(s2.top());
                s2.pop();
            }
        }

        int top(){
            return s1.top();
        }

        void pop(){
            s1.pop();
        }
};



//Implementing Queue Using two Stacks
class queueImpUsingStack_method2{
    public:
        stack<int> s1;
        stack<int> s2;
        void push(int x){
            s1.push(x);
        }
        int top(){
            if(s2.size()==0){
                while(s1.size()){
                    s2.push(s1.top());
                    s1.pop();
                }
            }
            return s2.top();
        }

        void pop(){
            if(s2.size()==0){
                while(s1.size()){
                    s2.push(s1.top());
                    s1.pop();
                }
            }
            s2.pop();
        }
        int size(){
            int s=s1.size()+s2.size();
            return s;
        }
};


//Sort a stack
//The brute foce is the most optimal one
//Take out all elements, place them in a vector, sort them, and put them back
void sortStack(stack<int> &st){
    vector<int> arr;
    while(!st.empty()){
        arr.push_back(st.top());
        st.pop();
    }
    sort(arr.begin(),arr.end());
    int n=arr.size();
    for(int i=0;i<n;i++) st.push(arr[i]);
}
//The while loop runs for n times
//The sort function takes nlogn time
//The for loop runs for n times
//Space is used by the extra array which grows to a maximum of n size
//Time Complexity will be O(2n+nlogn)
//Space Complexity will be O(n)


//Valid Parenthesis
bool validParenthesis(string str){
    stack<char> st;
    int n=str.size();
    if(n%2!=0) return false;
    for(int i=0;i<n;i++){
        if(str[i]=='(' || str[i]=='{' || str[i]=='['){
            st.push(str[i]);
        }
        else{
            if(st.empty()==true) return false;
            char ch=st.top();
            if((str[i]==')' && ch!='(') || (str[i]=='}' && ch!='{') || (str[i]==']' && ch!='[')) return false;
        }
    }
    return true;
}
//Time Complexity will be O(n)
//Space Complexity will be O(n)



//Expression Conversions
//For this, we first need to understand the priority of operators

/*Priority Order of Operators
^,(*,/),(+,-);

Infix expression : (everything in between), for eg like : (x+y)-(p/q), see all the operators, +,-,/ etc are in between
Prefix expression : *+pq-mn (*+ before the variables)
Postfix expression : pq+mn-*

Postfix expressions are used heavily in stack based calculators
Prefix expressions are used in the language LISP and in tree data structure
*/


//Converting infix to postfix
//Consider : a+b*(c^d-e)
//First we make up a priority function 
int priority(char ch){
    if(ch=='^') return 3;
    else if(ch=='*' || ch=='/') return 2;
    else if(ch=='+' || ch=='-') return 1;
    else return -1;
};

//Infix to Postfix
string infixToPostfix(string str){
    int n=str.size();
    string ans="";
    stack<char> st;
    for(int i=0;i<n;i++){
        char ch=str[i];
        if((ch>=65 && ch<=90) || (ch>=97 && ch<=122) || (ch>=48 && ch<=57)) ans+=ch;
        else{
            if(ch=='(') st.push(ch);
            else if(ch==')'){
                while(st.top()!='('){
                    ans+=st.top();
                    st.pop();
                }
                st.pop();
            }
            else if(st.empty()) st.push(ch);
            else if(priority(ch)>priority(st.top())) st.push(ch);
            else{
                while(priority(st.top())>priority(ch)){
                    ans+=st.top();
                    st.pop();
                }
                st.push(ch);
            }
        }
    }
    while(!st.empty()){
        ans+=st.top();
        st.pop();
    }
    return ans;
}
//Since stack and ans both store 2n elements, therefore space used will be 2n
//Time Complexity will be O(2N) 
//Space Complexity will be O(2N) (stack and ans both store 2n elements at max)


//Infix to Prefix
//Consider : (A+B)*C-D+F
//Step 1 : Reverse the Infix string(make sure to inverse the ( and ) brackers as they will be like )( after reversing the string)
void revStrWithBrackets(string &str){
    int n=str.size();
    int i=0;
    int j=n-1;
    while(i<j){
        if(str[i]=='(') str[i]=')';
        else if(str[i]==')') str[i]='(';
        if(str[j]==')') str[j]='(';
        else if(str[j]=='(') str[j]=')';
        swap(str[i],str[j]);
        i++;
        j--;
    }
}
//Time Complexity will be O(n/2)

//Now a function to reverse string
void revStr(string &str){
    int n=str.size();
    int i=0;
    int j=n-1;
    while(i<j){
        swap(str[i],str[j]);
        i++;
        j--;
    }
}
//Time Complexity will be O(n/2)

//Step 2 : Use controlled conversion from infix to postfix
int priority2(char ch){
    if(ch=='^') return 2;
    else if(ch=='+' || ch=='-' || ch=='*' || ch=='/') return 1;
    else return -1;
}

//Controlled infix to postfix conversion
string controlledInfixToPostfix(string str){
    int n=str.size();
    stack<char> st;
    string ans="";
    for(int i=0;i<n;i++){
        char ch=str[i];
        if((ch>='A' && ch<='Z') || (ch>='a' && ch<='z') || (ch>='0' && ch<='9')) ans+=ch;
        else{
            if(st.empty()) st.push(ch);
            else{
                if(ch=='^'){
                    if(st.top()!='^') st.push(ch);
                    else{
                        ans+=st.top();
                        st.pop();
                        st.push(ch);
                    }
                }
                else if(ch=='(') st.push(ch);
                else if(ch==')'){
                    while(st.top()!='('){
                        ans+=st.top();
                        st.pop();
                    }
                    st.pop();
                }
                else{
                    if(st.top()=='^'){
                        ans+=st.top();
                        st.pop();
                        st.push(ch);
                    }
                    else st.push(ch);

                }
            }
        }
    }

    while(!st.empty()){
        ans+=st.top();
        st.pop();
    }
    return ans;
}
//Time complexity will be O(n)
//Space Complexity will be O(n)

//Step 3 : Reverse the string obtained, This is your answer
string infixToPrefix(string str){
    int n=str.size();
    revStrWithBrackets(str);
    string ans=controlledInfixToPostfix(str);
    revStr(ans);
    return ans;
}
//Time Complexity will be O(3n)
//Space Complexity will be O(n)


//Postfix to Infix
string postfixToInfix(string str){
    int n=str.size();
    stack<string> st;
    string t1="";
    string t2="";
    for(int i=0;i<n;i++){
        string ch=string(1,str[i]);
        if(ch=="+" || ch=="-" || ch=="*" || ch=="/" || ch=="^"){
            t1=st.top();
            st.pop();
            t2=st.top();
            st.pop();
            string temp="("+t2+ch+t1+")";
            st.push(temp);
        }
        else{
            st.push(ch);
        }
    }
    return st.top();
}
//Time used will be due to loop (n) and due to addition of strings which can take n at most
//Time Complexity will be O(2n)
//Space Complexity will be O(n)


//Prefix To Infix
string prefixToInfix(string str){
    int n=str.size();
    stack<string> st;
    for(int i=n-1;i>=0;i--){
        string ch=string(1,str[i]);
        if(str[i]=='+' || str[i]=='-' || str[i]=='*' || str[i]=='/' || str[i]=='^'){
            string t1=st.top();
            st.pop();
            string t2=st.top();
            st.pop();
            string temp="("+t1+str[i]+t2+")";
            st.push(temp);
        }
        else st.push(ch);
    }
    return st.top();
}
//Similar to previous case, time will be used for loop(n) and addition(n at worst)
//Time Complexity will be O(2n)
//Space Comlexity will be O(n) 


//Postfix to Prefix
string postfixToPrefix(string str){
    int n=str.size();
    stack<string> st;
    for(int i=0;i<n;i++){
        string ch=string(1,str[i]);
        if(ch=="+" || ch=="-" || ch=="*" || ch=="/" || ch=="^"){
            string t1=st.top();
            st.pop();
            string t2=st.top();
            st.pop();
            string temp=ch+t2+t1;
            st.push(temp);
        }
        else st.push(ch);
    }
    return st.top();
}
//Time Complexity will be O(2n)
//Space Complexity will be O(n)


//Prefix To Postfix
string prefixToPostfix(string str){
    int n=str.size();
    stack<string> st;
    for(int i=n-1;i>=0;i--){
        string ch=string(1,str[i]);
        if(ch=="+" || ch=="-" || ch=="*" || ch=="/" || ch=="^"){
            string t1=st.top();
            st.pop();
            string t2=st.top();
            st.pop();
            string temp=t1+t2+ch;
            st.push(temp);
        }
        else st.push(ch);
    }
    return st.top();
}
//Time Complexity will be O(2n)
//Space Complexity will be O(n)


//Min Stack : A stack that keeps track of the minimum element, uptill the particular element
class minStack_brute{
    public:
        stack<pair<int,int>> st;
        void push(int val){
            if(st.empty()) st.push({val,val});
            else st.push({val,min(val,st.top().second)});
            
        }

        int getMin(){
            return st.top().second;
        }

        int top(){
            return st.top().first;
        }
};
//Time is constant but stack stores pair, therefore 2n space
//Space Complexity will be O(2n)

//We can optimise the space
class minStack{
    public:
        stack<int> st;
        int minEl=INT_MAX;
        void push(int &val){
            if(st.empty()) minEl=val;
            else{
                if(val<=minEl){
                    int temp=minEl;
                    minEl=val;
                    val=2*val-temp;
                }
            }
            st.push(val);
        }

        int findMin(){
            return minEl;
        }

        int top(){
            if(st.empty()) return -1;
            int ans=st.top();
            if(ans<findMin()) return findMin();
            return ans;
        }

        void pop(){
            if(st.empty()) return;
            else{
                if(st.top()<minEl) minEl=2*findMin()-st.top();
            }
            st.pop();
        }
};
//Constant time but we now use only n space
//Space Complexity will be O(n)


//Monotonic Stack : Stack that stores element in some particular order, say increasing or decreasing etc
//Next greater element
void nextGreater_brute(vector<int> &arr){
    int n=arr.size();
    for(int i=0;i<n;i++){
        int nextGreater=-1;
        for(int j=i+1;j<n;j++){
            if(arr[j]>arr[i]){
                nextGreater=arr[j];
                break;
            }
        }
        arr[i]=nextGreater;
    }
}
//Time Complexity will be O(n2)

//Optimal Method
//Keep track of the greatest element from the back
void nextGreater(vector<int> &arr){
    int n=arr.size();
    vector<int> nge(n);
    stack<int> st;
    for(int i=n-1;i>=0;i--){
        while(!st.empty() && st.top()<=arr[i]) st.pop();
        if(st.empty()) nge[i]=-1;
        else nge[i]=st.top();
        st.push(arr[i]);
    }
    arr=nge;
}
//The inner loop runs at most n times, since it can remove a max of n elements, therefore the code runs at max 2n
//The stack may store all elements at worst
//Time Complexity will be O(2n) 
//Space Complexity will be O(n)


//Next Greater Element : Variation 2
//Keep the search going around in circular manner when you reach the end of array(begin at first element)
vector<int> nextGreaterII_brute(vector<int> arr){
    int n=arr.size();
    vector<int> ans(n);
    for(int i=0;i<n;i++){
        int nextGreater=-1;
        for(int j=i+1;j<n;j++){
            if(arr[j]>arr[i]){
                nextGreater=arr[j];
                break;
            }
        }
        if(nextGreater==-1){
            for(int k=0;k<i;k++){
                if(arr[k]>arr[i]){
                    nextGreater=arr[k];
                    break;
                }
            }
        }
        ans[i]=nextGreater;
    }
    return ans;
}
//Time Complexity will be O(n2)

//Better Method : Using Circular array concept
vector<int> nextGreaterII_better(vector<int> arr){
    int n=arr.size();
    vector<int> ans(n);
    int i=0;
    int j=i+1;
    for(int i=0;i<n;i++){
        int nextGreater=-1;
        for(int j=i+1;j<(n+i);j++){
            int idx=j%n;
            if(arr[idx]>arr[i]){
                nextGreater=arr[idx];
                break;
            }
        }
        ans[i]=nextGreater;
    }
    return ans;
}
//Time Complexity will be O(n2)

//Optimal Approach : Using monotonic stack option
vector<int> nextGreaterII(vector<int> arr){
    int n=arr.size();
    stack<int> st;
    vector<int> ans(n);
    for(int i=2*n-1;i>=0;i--){
        int idx=i%n;
        while(!st.empty() && st.top()<=arr[idx]) st.pop();
        if(i<n) ans[i]=st.empty()? -1:st.top();
        st.push(arr[idx]);
    }
    return ans;
}
//Time Complexity will be O(2n)
//Space Complexity will be O(n)


//Nearest Smaller Element
//Brute Force : Two loops
vector<int> nearestSmaller_brute(vector<int> arr){
    int n=arr.size();
    vector<int> ans;
    int smallest=-1;
    for(int i=0;i<n;i++){
        smallest=-1;
        for(int j=i-1;j>=0;j--){
            if(arr[j]<arr[i]){
                smallest=arr[j];
                break;
            }
        }
        ans.push_back(smallest);
    }
    return ans;
}
//Time Complexity will be O(n2)

//Optimal Approach : Using monotonic stack
vector<int> nearestSmaller(vector<int> arr){
    int n=arr.size();
    stack<int> st;
    vector<int> ans;
    for(int i=0;i<n;i++){
        while(!st.empty() && st.top()>=arr[i]) st.pop();
        if(st.empty()) ans.push_back(-1);
        else ans.push_back(st.top());
        st.push(arr[i]);
    }
    return ans;
}
//Time Complexity will be O(2N)
//Space Complexity will be O(N)



//Find Previous Smaller element
vector<int> findPSE(vector<int> &arr){
    int n=arr.size();
    vector<int> ans;
    stack<pair<int,int>> st;
    for(int i=0;i<n;i++){
        while(!st.empty() && st.top().first>=arr[i]) st.pop();
        if(st.empty()) ans.push_back(-1);
        else ans.push_back(st.top().second);
        st.push({arr[i],i});
    }
    return ans;
}
//Time Complexity will be O(2n)
//Space Complexity will be O(2n)



//Find Next Smaller Element
vector<int> findNSE(vector<int> &arr){
    int n=arr.size();
    vector<int> ans(n);
    stack<pair<int,int>> st;
    for(int i=n-1;i>=0;i--){
        while(!st.empty() && st.top().first>=arr[i]) st.pop();
        if(st.empty()) ans[i]=n;
        else ans[i]=(st.top().second);
        st.push({arr[i],i});
    }
    return ans;
}
//Time Complexity will be O(2n)
//Space Complexity will be O(2n)



//Find Next Greater Element
vector<int> findNGE(vector<int> &arr){
    int n=arr.size();
    stack<pair<int,int>> st;
    vector<int> ans(n);
    for(int i=n-1;i>=0;i--){
        while(!st.empty() && st.top().first<=arr[i]) st.pop();
        if(st.empty()) ans[i]=n;
        else ans[i]=st.top().second;
        st.push({arr[i],i});
    }
    return ans;
}
//Time Complexity will be O(2n)
//Space Complexity wil be O(2n)

//Find Previous Greater Element
vector<int> findPGE(vector<int> &arr){
    int n=arr.size();
    stack<pair<int,int>> st;
    vector<int> ans(n);
    for(int i=0;i<n;i++){
        while(!st.empty() && st.top().first<=arr[i]) st.pop();
        if(st.empty()) ans[i]=-1;
        else ans[i]=st.top().second;
        st.push({arr[i],i});
    }
    return ans;
}
//Time Complexity will be O(2n)
//Space Complexity will be O(2n)



//Count Number of NGEs to the right
//We will be given an array [3,4,2,7] and an indices array [0,2]
//You have to tell the count of how many element are to the right of index 0 and 5 which are greater
//For eg, at index 0 is 3 and nge to right of it are 2, similarly 1 for index 2
//Return [2,1]
vector<int> countNGE_brute(vector<int> &arr,vector<int> &indices){
    int n=arr.size();
    int m=indices.size();
    vector<int> ans;
    for(int i=0;i<m;i++){
        int cnt=0;
        for(int j=i+1;j<n;j++){
            if(arr[j]>arr[i]) cnt++;
        }
        ans.push_back(cnt);
    }
    return ans;
}

//Trapping Rainwater : Formula --> min(leftMaxElement,rightMaxElement)-height of building, this give the water logged on that building
//Naive Approach
//Add water logged on all the buildings to get the total trapped water
int trappingRainwater_naive(vector<int> arr){
    int n=arr.size();
    int leftMax=-1;
    int rightMax=-1;
    int totalWaterTrapped=0;
    for(int i=1;i<n-1;i++){
        leftMax=-1;
        rightMax=-1;
        for(int j=i-1;j>=0;j--) leftMax=max(leftMax,arr[j]);
        for(int j=i+1;j<n;j++) rightMax=max(rightMax,arr[j]);
        int waterTrapped=min(leftMax,rightMax)-arr[i];
        totalWaterTrapped+=(waterTrapped>0? waterTrapped:0);
    }
    return totalWaterTrapped;
}
//Time Complexity will be O(n2)

//We can create two arrays and keep track of left max and right max in them
//Brute Force Approach
int trappingRainwater_brute(vector<int> arr){
    int n=arr.size();
    int totalWaterLogged;
    vector<int> prefixMax=arr;
    vector<int> suffixMax=arr;
    for(int i=1;i<n;i++) prefixMax[i]=max(prefixMax[i],prefixMax[i-1]);
    for(int i=n-2;i>=0;i--) suffixMax[i]=max(suffixMax[i],suffixMax[i+1]);
    for(int i=1;i<n-1;i++){
        int waterLogged=(min(prefixMax[i],suffixMax[i])-arr[i]);
        totalWaterLogged+=(waterLogged>0? waterLogged:0);
    }
    return totalWaterLogged;
}
//Time Complexity will be O(3n)
//Space Complexity will be O(2n)

//We can just use a single array, since when we are calculating water trapped, we are traversing from 0 to n-1, therefore we can keep track of leftMax
//Better Method
int trappingRainwater_better(vector<int> &arr){
    int n=arr.size();
    int totalWaterTrapped=0;
    vector<int> suffixMax(n);
    suffixMax[n-1]=arr[n-1];
    for(int i=n-2;i>=0;i--) suffixMax[i]=max(suffixMax[i+1],arr[i]);
    int leftMax=-1;
    int rightMax;
    for(int i=0;i<n;i++){
        leftMax=max(leftMax,arr[i]);
        rightMax=suffixMax[i];
        int waterTrapped=min(leftMax,rightMax)-arr[i];
        totalWaterTrapped+=(waterTrapped>0 ? waterTrapped : 0);
    }
    return totalWaterTrapped;
}
//Time Complexity will be O(2n)
//Space Complexity will be O(n)

//Optimal Approach
int trappingRainwater(vector<int> arr){
    int n=arr.size();
    int totalWaterTrapped=0;
    int lMax=0;
    int rMax=0;
    int i=0;
    int j=n-1;
    while(i<j){
        lMax=max(lMax,arr[i]);
        rMax=max(rMax,arr[j]);
        int waterTrapped;
        if(lMax>rMax){
            waterTrapped=rMax-arr[j];
            j--;
        }
        else{
            waterTrapped=lMax-arr[i];
            i++;
        }
        totalWaterTrapped+=waterTrapped;
    }
    return totalWaterTrapped;
}
//Time Complexity will be O(n)


//Sum of Subarray minimum
//Form all possible subarrays, then find out the minimum element in each one of them, then sum all these minimum element
//Brute Force : Do as instructed above
int sumOfSubarrMin_brute(vector<int> arr){
    int n=arr.size();
    vector<vector<int>> a;
    for(int i=0;i<n;i++){
        vector<int> temp;
        for(int j=i;j<n;j++){
            temp.push_back(arr[j]);
            a.push_back(temp);
        }
    }
    int minSum=0;
    for(auto it:a){
        int minEl=INT_MAX;
        for(auto el:it) minEl=min(minEl,el);
        minSum+=minEl;
    }
    return minSum;
}
//Time Complexity will be O(2n2)
//Space Complexity O(n2)

//Same Approach can be written in better way
//Better Force
int sumOfSubarrMin_better(vector<int> arr){
    int n=arr.size();
    int sum=0;
    for(int i=0;i<n;i++){
        int mini=arr[i];
        for(int j=i;j<n;j++){
            mini=min(arr[j],mini);
            sum+=mini;
        }
    }
    return sum;
}
//The code runs for two loops therefore n2
//No space is occupied
//Time Complexity will be O(n2)


//Before moving ahead, we need some prerequisites 
//Ques: What is the number of subarrays(non empty) possbile from an array of length n
//Consider an array of size n, since we can't skip elements while forming a subarray, therefore the start can be anywhere from 0 to n-1 but the end point will depend on the start
//When start was 0, end can be from n-1 to 0(n ways)
//When start was 1, end can be from n-1 to 1(n-1 ways)
//When start was 2, end can be from n-1 to 2(n-2 ways)
//.
//.
//.
//When start was n-1, end can be from n-1 to n-1(1 way)
//Summing up : 1+2+...+n => (n*(n+1))/2
//This is the total number of subarrays possible


//Ques: Consider that there is a particular element at index k, which always needs to be included, what will be the number of subarrays now?
//In this case the start of subarray can be anywhere from 0 to k
//And the ending point can be anywhere from k to n-1
//Therefore, total choices will be (k+1)*(n-1)

//We will now solve using the Optimal Approach
//Try to count how many times will a particular element contribute to the total sum
//It will just be equal to the total numbers of subarrays formed, in which that particular element will be the smallest
//For eg consider the array : [1,4,6,7,3,7,8,1]



//Now let's try to find out how much contribution will 3 give
//We need to count only the subarrays where 3 will be the minimum
//Such subarray can start from 4, and end at 8.
//In all these subarrays, 3 will be smallest
//Index of 4 can be found out by using pse(Previous smaller element)
//Index of 8 can be found out by using nge(Next greater element)
//Therefore the total subarrays will be pse*nge
//This will the total number of subarrays formed in which 3 will be the smallest element. 
//Therefore this will be the contribution of 3
int sumOfSubarrMin(vector<int> &arr){
    int n=arr.size();
    int ans=0;
    vector<int> nse=findNSE(arr);
    vector<int> pse=findPSE(arr);
    for(int i=0;i<n;i++){
        int left=i-pse[i];
        int right=nse[i]-i;
        ans+=left*right*arr[i];
    }
    return ans;
}
//We can decrease the time complexity by doing the NSE and PSE array generation in a single loop, but this code is far more readable
//Time Complexity will be O(2n+2n+n)
//Space Complexity will be O(2n+2n)



//A function to form all subarrays
vector<vector<int>> formAllSubarr(vector<int> &arr){
    int n=arr.size();
    vector<vector<int>> ans;
    for(int i=0;i<n;i++){
        vector<int> temp;
        for(int j=i;j<n;j++){
            temp.push_back(arr[j]);
            ans.push_back(temp);//This operation takes time equal to temp.size(), that is at max O(N) time
        }
    }
    return ans;
}
//Total subarrays are n2 and some of them have n elements in total
//Time Complexity will be O(n3)
//Space Complexity will be O(n3)



//Sum of Subarray Maximum
//Form all subarrays and find the max element in each of them then sum all these elements
//Brute Force : Do as told above
int sumOfSubarrMax_brute(vector<int> &arr){
    int n=arr.size();
    int ans=0;
    vector<vector<int>> mat=formAllSubarr(arr);
    for(auto it:mat){
        int maxi=*max_element(it.begin(),it.end());
        ans+=maxi;
    }
    return ans;
}

//Better Method
//Doing the same thing in a better way
int sumOfSubarrMax_better(vector<int> &arr){
    int n=arr.size();
    int ans=0;
    for(int i=0;i<n;i++){
        int maxi=arr[i];
        for(int j=i;j<n;j++){
            maxi=max(maxi,arr[j]);
            ans+=maxi;
        }
    }
    return ans;
}
//Time Complexity will be O(n2)

//Optimal Method
int sumOfSubarrMax(vector<int> &arr){
    int n=arr.size();
    vector<int> nge=findNGE(arr);
    vector<int> pge=findPGE(arr);
    int ans=0;
    for(int i=0;i<n;i++){
        int left=i-pge[i];
        int right=nge[i]-i;
        ans+=(left*right*arr[i]);
    }
    return ans;
}
//Time Complexity will be O(2n+2n+n)
//Space Complexity will be O(2n+2n)



//Sum of Subarray Ranges
//Form all the subarrays and find the range of them and then sum up all the ranges
//Brute Force : Doing as told above

int sumOfSubarrRanges_brute(vector<int> &arr){
    int n=arr.size();
    vector<vector<int>> mat=formAllSubarr(arr);
    int ans=0;
    for(auto it:mat){
        int maxi=*max_element(it.begin(),it.end());
        int mini=*min_element(it.begin(),it.end());
        ans+=(maxi-mini);
    }
    return ans;
}
//Time Complexity will be O(n3+n2)
//Space Complexity will be O(n3)

//Better Method
//No need to generate all subarrays, we can keep track of max and min while traversing
int sumOfSubarrRanges_better(vector<int> &arr){
    int n=arr.size();
    int ans=0;
    for(int i=0;i<n;i++){
        int maxi=arr[i];
        int mini=arr[i];
        for(int j=i;j<n;j++){
            maxi=max(maxi,arr[j]);
            mini=min(mini,arr[j]);
            ans+=(maxi-mini);
        }
    }
    return ans;
}
//Time Complexity will be O(n2)

//Optimal Approach
//We can apply our brain and just subtract the sumOfSubarrMin and sumOfSubarrMax values
int sumOfSubarrRanges(vector<int> &arr){
    int maxi=sumOfSubarrMax(arr);
    int mini=sumOfSubarrMin(arr);
    return maxi-mini;
}


//Asteroid Collision
//Brute Force
vector<int> asteroidCollision_brute(vector<int> &arr){
    int n=arr.size();
    stack<int> st;
    vector<int> ans;
    int k=0;
    while(arr[k]<0){
        ans.push_back(arr[k]);
        k++;
    }
    //Runs for atmost O(n)

    for(int i=k;i<n;i++){
        if(arr[i]>0) st.push(arr[i]);
        else{
            if(!st.empty()){
                while(!st.empty() && abs(arr[i])>st.top()) st.pop();
                if(st.empty()){
                    ans.push_back(arr[i]);
                    continue;
                }
                if(abs(arr[i])==st.top()){
                    st.pop();
                    continue;
                }
            }
        }
    }
    //Runs for atmost O(2n) 

    vector<int> temp;
    while(!st.empty()) temp.push_back(st.top()); //O(n) time 
    reverse(temp.begin(),temp.end()); //O(n) time
    for(int i=0;i<temp.size();i++) ans.push_back(temp[i]); //O(n) time
    return ans;
}
//Time Complexity is almost O(6n)
//Space Complexity will be O(2n)

//Better Method
//Can be done by using only a stack
vector<int> asteroidCollision_better(vector<int> &arr){
    int n=arr.size();
    stack<int> st;
    vector<int> ans;
    for(int i=0;i<n;i++){
        if(arr[i]>0) st.push(arr[i]);
        else{
            while(!st.empty() && st.top()>0 && abs(arr[i])>st.top()) st.pop();
            if(!st.empty() && st.top()==abs(arr[i])) st.pop();
            else if(st.empty() || st.top()<0) st.push(arr[i]);
        }
    }
    while(!st.empty()){
        ans.push_back(st.top());
        st.pop();
    }
    reverse(ans.begin(),ans.end());
    return ans;
}
//Time Complexity will be O(3n)
//Space Complexity will be O(n)

//Optimal Approach
//Further Optimisation can be done if we use an array instead of a stack
vector<int> asteroidCollision(vector<int> &arr){
    int n=arr.size();
    vector<int> ans;
    for(int i=0;i<n;i++){
        if(arr[i]>0) ans.push_back(arr[i]);
        else{
            while(ans.size()>0 && ans.back()>0 && abs(arr[i])>ans.back()) ans.pop_back();
            if(ans.size()>0 && ans.back()==abs(arr[i])) ans.pop_back();
            else if(ans.size()==0 || ans.back()<0) ans.push_back(arr[i]);
        }
    }
    return ans;
}
//Time Complexity will be O(2n)
//No space is required to solve the question, to give the answer only we need the ans array so Space Complexity will be O(1)


//Area of Largest Rectangle in a Histogram
//Brute Force Approach
//Just try to count in leftwards and rightwards direction
int largestRectangle_brute(vector<int> &arr){
    int n=arr.size();
    int maxArea=0;
    for(int i=0;i<n;i++){
        int r=i;
        int l=i;
        while(r<n && arr[r]>=arr[i]) r++;
        while(l>=0 && arr[l]>=arr[i]) l--;
        int area=(r-l-1)*(arr[i]);
        maxArea=max(area,maxArea);
    }
    return maxArea;
}
//Time Complexity will be O(n2)

//Better Approach
//We can also use the concepts of pse and nse to solve this
int largestRectangle_better(vector<int> &arr){
    int n=arr.size();
    int maxArea=0;
    vector<int> nse=findNSE(arr);
    vector<int> pse=findPSE(arr);
    for(int i=0;i<n;i++){
        int l=pse[i];
        int r=nse[i];
        int area=(r-l-1)*arr[i];
        maxArea=max(maxArea,area);
    }
    return maxArea;
}
//Time Complexity will be O(2n+2n+n)
//Space Complexity will be O(2n+2n+n+n)

//Optimal Approach
//Quite Complex Approach hence video is recommended
int largestRectangle(vector<int> &arr){
    int n=arr.size();
    int maxArea=0;
    int nse,pse;
    stack<pair<int,int>> st;
    for(int i=0;i<n;i++){
        while(!st.empty() && arr[i]<st.top().second){
            nse=i;
            int x=st.top().second;
            st.pop();
            pse=(st.empty() ? -1 : st.top().first);
            maxArea=max((nse-pse-1)*x,maxArea);
        }
        st.push({i,arr[i]});
    }
    nse=n;
    while(!st.empty()){
        int x=st.top().second;
        st.pop();
        int pse=(st.empty()? -1:st.top().first);
        maxArea=max((nse-pse-1)*x,maxArea);
    }
    return maxArea;
}
//Time Complexity will be O(2n)
//Space Complexity will be O(2n)


//Maximal Rectangle
//This uses the previous question, largest histogram.
int maximalRectangle_brute(vector<vector<int>> &mat){
    int n=mat.size();
    if(n==0) return 0;
    int m=mat[0].size();
    vector<vector<int>> grid(n,vector<int> (m,0));
    for(int j=0;j<m;j++){
        int cnt=0;
        for(int i=0;i<n;i++){
            if(mat[i][j]==0) cnt=0;
            else{
                cnt+=mat[i][j];
                grid[i][j]=cnt;
            }
        }
    }
    int maxArea=0;
    for(auto it:grid){
        int area=largestRectangle(it);
        maxArea=max(maxArea,area);
    }
    return maxArea;
}
//Time Complexity will be O(2MN)
//Space Complexity will be O(MN)

//Optimal Method
//We can shrink down the space a bit
int maximalRectangle(vector<vector<int>> &mat){
    int n=mat.size();
    if(n==0) return 0;
    int m=mat[0].size();
    vector<int> hist(m,0);
    int maxArea=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++) hist[j]=(mat[i][j]==0? 0:hist[j]+1);
        maxArea=max(maxArea,largestRectangle(hist));
    }
    return maxArea;
}
//Time Complexity will be O(MN)*O(2N)(for largest Rectangle)
//Space Complexity will be O(M)+O(2N) (for largest Rectangle)


//Remove K digits to form the smallest number
string removeKDigits(string str,int k){
    int n=str.size();
    if(k>=n) return "0";
    string ans="";
    ans.push_back(str[0]);
    int i=1;
    while(i<n){
        while(k>0 && ans.size()>0 && ans.back()>str[i]){
            ans.pop_back();
            k--;
        } 
        ans.push_back(str[i]);
        i++;
    }

    while(k>0){
        ans.pop_back();
        k--;
    }
    int idx=0;
    while(idx<ans.size() && ans[idx]=='0') idx++;
    ans=ans.substr(idx);  
    if(ans.empty()) return "0";
    return ans;
}
//Time Complexity will be O(n)


//Stock Span Problem
class StockSpan_brute{
    vector<int> arr;
    StockSpan_brute(){
    }
    int next(int nextVal){
        arr.push_back(nextVal);
        int cnt=1;
        for(int i=arr.size()-2;i>=0;i--){
            if(arr[i]<=nextVal) cnt++;
            else break;
        }
        return cnt;
    }
};
//At each next function we traverse the whole array back, therefore total number of times the code runs will be O(k) where k is the number of days behind
//Space used will be equal to the number of next calls made, since at each next call, the array size is increased by one, therefore for three next calls, the size wouuld be 3
//Time Complexity will be O(k)  (k is the number of elements behind)
//Space Complexity will be O(m) (m is the number of next calls)

//Optimal Method
//Using the same concept as previous greater element
class StockSpan{
    public:
        stack<pair<int,int>> st;
        int cnt=0;
        StockSpan(){
            st=stack<pair<int,int>> ();
            cnt=0;
        }

        int next(int nextVal){
            while(!st.empty() && nextVal>=st.top().first) st.pop();
            int prevIdx=(st.empty()? -1:st.top().second);
            st.push({nextVal,cnt});
            int ans=cnt-prevIdx;
            cnt++;
            return ans;
        }
};
//In total across the gross operations, the time taken will be O(2n)
//Time Complexity will be O(2n)
//Space Complexity will be O(2n)


//Sliding Window Maximum
//The window will be of 3 length
//Brute Force
//Just compute the maximum in each window by running a loop
vector<int> slidingWindowMax_brute(vector<int> &arr){
    int n=arr.size();
    vector<int> ans;
    if(n==0) return ans;
    if(n==1){
        ans.push_back(arr[0]);
        return ans;
    }
    if(n==2){
        ans.push_back(max(arr[0],arr[1]));
        return ans;
    }

    int i=0;
    int j=2;
    while(j<n){
        int maxi=INT_MIN;
        for(int k=i;k<=j;k++) maxi=max(maxi,arr[k]);
        ans.push_back(maxi);
        j++;
        i++;
    }
    return ans;
}
//No space is used to solve the answer
//Time Complexity will be O(3n)

//Optimal Method
//In the upcoming questions, we will just assume that n>=k
vector<int> slidingWindowMax(vector<int> &arr){
    int n=arr.size();
    deque<int> dq;
    vector<int> ans;
    for(int i=0;i<n;i++){
        if(!dq.empty() && dq.front()<=i-3) dq.pop_front();
        while(!dq.empty() && arr[dq.back()]<=arr[i]) dq.pop_back();
        dq.push_back(i);
        if(i>=3-1) ans.push_back(arr[dq.front()]);
    }
    return ans;
}
//Time Complexity will be O(2n)
//Space Complexity will be O(3)



//Sliding Window Maximum
//Generalised Version
//K sized window
vector<int> slidingWindowMaxII_brute(vector<int> &arr,int k){
    int n=arr.size();
    //We will assume that n>=k

    int i=0;
    int j=k-1;
    vector<int> ans;
    while(j<n){
        int maxi=INT_MIN;
        for(int p=i;p<=j;p++) maxi=max(maxi,arr[p]);
        ans.push_back(maxi);
        i++;
        j++;
    }

    return ans;
}
//Time Complexity will be O(nk)

//Optimal Method
vector<int> slidingWindowMaxII(vector<int> &arr, int k){
    int n=arr.size();
    vector<int> ans;
    deque<int> dq;
    for(int i=0;i<n;i++){
        if(!dq.empty() && dq.front()<=i-k) dq.pop_front();
        while(!dq.empty() && arr[dq.back()]<=arr[i]) dq.pop_back();
        if(i>=k-1) ans.push_back(arr[dq.front()]);
    }
    return ans;
}
//Time Complexity will be O(2n)
//Space Complexity will be O(k)



//Celebrity Problem
//Persons say 1,2,3,4 and if one is celebrity then everyone knows 1 but 1 knows no one
//The expression mat[i][j]=1 represents i knows j
//We will take mat[i][i]=0
//Brute Force 
//Consider there are n people, and if 1 is celebrity then number of people who know 1 will be n-1(we assume 1 doesn't know himself)
//And the number of people whom 1 knows will be 0
//We declare two array, knowMe and Iknow arrays
int celebrityProblem_brute(vector<vector<int>> &mat){
    int n=mat.size();
    vector<int> knowMe(n,0);
    vector<int> iKnow(n,0);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i==j || mat[i][j]==0) continue;

            //(i,j) means j is known by someone therefore : 
            knowMe[j]++;

            //And that i knows someone
            iKnow[i]++;
        }
    }

    //Now we just need to find which element in knowMe array has n-1 and which element in iKnow array has 0
    for(int i=0;i<n;i++){
        if(knowMe[i]==n-1 && iKnow[i]==0) return i;
    }

    //In case of no celebrity
    return -1;
}
//Time Complexity will be O(n2 + n)
//Space Complexity will be O(2n)

//Better Method
//Find the row with all 0s 
//Let's create a function that checks whether an array has all 0s
bool isArrAll0(vector<int> &arr){
    int n=arr.size();
    for(int i=0;i<n;i++) if(arr[i]!=0) return false;
    return true;
}
//Time Complexity will be O(n)

int celebrityProblem_better(vector<vector<int>> &mat){
    int n=mat.size();//Obviously the matrix is a squared matrix

    //We are declaring this array only for the variation of the problem in which there can be no celebrity
    //In such case there can be 0 or more than 1 rows with all 0s
    vector<int> ans;
    for(int i=0;i<n;i++){

        //If there's a row which has all 0s then it means only two things, that row is the celebrity or there's no celebrity
        if(isArrAll0(mat[i])) ans.push_back(i);
        if(ans.size()==2) return -1;
    }
    //We can return -1 in case there is no celebrity.
    if(ans.size()==0) return -1;
    return ans[0];
}
//Time Complexity will be O(n2)

//Optimal Method
//Watch Video
int celebrityProblem(vector<vector<int>> &mat){
    int n=mat.size();
    int i=0;
    int j=n-1;
    while(i<j){
        if(mat[i][j]==1) i++;
        else if(mat[j][i]==1) j--;
        else{
            i++;
            j--;
        }
    }
    if(i>j) return -1;
    for(int k=0;k<n;k++){
        if(mat[i][k]==1) return -1;
        if(k!=i && mat[k][i]==0) return -1;
    }
    return i;
}
//Time Complexity will be O(2n)


//Implement LRU Cache
//LRU means least recently used
//We keep track of recently used cache
//We need a data structure that stores the order in which the element were inserted and also allows us to access any element
//Maps allow us to access any element, but they do not maintain the order
//To maintain the order we will use a doubly linked list
//We will need Doubly Linked List for this, so first we will create that
class NodeLRU{
    public:
        int key;
        int val;
        NodeLRU* prev;
        NodeLRU* next;

        NodeLRU(int key,int val){
            this->key=key;
            this->val=val;
            this->prev=nullptr;
            this->next=nullptr;
        }
};
class LRUCache{
    public:
        unordered_map<int,NodeLRU*> mpp;
        int capacity;
        NodeLRU* head;
        NodeLRU* tail;

        LRUCache(int capacity){
            this->capacity=capacity;
            mpp.clear();
            head=new NodeLRU(-1,-1);
            tail=new NodeLRU(-1,-1);
            head->next=tail;
            tail->prev=head;
        }

        void deleteNode(NodeLRU* node){
            NodeLRU* prevNode=node->prev;
            NodeLRU* nextNode=node->next;
            prevNode->next=nextNode;
            nextNode->prev=prevNode;
        }
        //Time Complexity will be O(1)
        //Space Complexity will be O(1)

        void insertAfterHead(NodeLRU* node){
            NodeLRU* nextNode=head->next;
            node->next=nextNode;
            node->prev=head;
            head->next=node;
            nextNode->prev=node;
        }
        //Time Complexity will be O(1)
        //Space Complexity will be O(1)

        void put(int key,int val){

            //If the map already has this, then just change the value
            if(mpp.find(key)!=mpp.end()){
                NodeLRU* node=mpp[key];
                node->val=val;
                deleteNode(node);
                insertAfterHead(node);
            }

            //Otherwise, there can be two conditions
            else{
                //In case the map is already full
                if(mpp.size()==capacity){
                    NodeLRU* lastUsed=tail->prev;
                    mpp.erase(lastUsed->key);
                    deleteNode(lastUsed);
                    delete lastUsed;
                }
                NodeLRU* newNode=new NodeLRU(key,val);
                mpp[key]=newNode;
                insertAfterHead(newNode);
            }
        }
        //Time Complexity will be O(1)
        //Space Complexity will be O(1)

        int get(int key){
            if(mpp.find(key)==mpp.end()) return -1;
            NodeLRU* node=mpp[key];
            deleteNode(node);
            insertAfterHead(node);
            return node->val;
        }
        //Time Complexity will be O(1)
        //Space Complexity will be O(1)
};


//LFU Cache
//Least Frequently Used element is to be kept tracked of
//First we create a node class since we need doubly linked list for this
class NodeLFU{
    public:
        int key;
        int val;
        int freq;
        NodeLFU* next;
        NodeLFU* prev;

        NodeLFU(int key,int val){
            this->key=key;
            this->val=val;
            this->freq=1;
            this->next=nullptr;
            this->prev=nullptr;
        }
};

class List{
    public:
        int size;
        NodeLFU* head;
        NodeLFU* tail;
        List(){
            head=new NodeLFU(0,0);
            tail=new NodeLFU(0,0);
            head->next=tail;
            tail->prev=head;
            size=0;
        }

        void addFront(NodeLFU* node){
            NodeLFU* temp=head->next;
            node->next=temp;
            node->prev=head;
            head->next=node;
            temp->prev=node;
            size++;
        }

        void removeNode(NodeLFU* delNode){
            NodeLFU* delPrev=delNode->prev;
            NodeLFU* delNext=delNode->next;
            delPrev->next=delNext;
            delNext->prev=delPrev;
            size--; 
        }

        //A destructor is needed to clean the nodes and list 
        ~List(){
            delete head;
            delete tail;
        }
};
class LFUCache{
    public:
        map<int,NodeLFU*> keyNode;
        map<int,List*> freqListMap;
        int maxSize;
        int minFreq;
        int currSize;
    
    public:
        LFUCache(int capacity){
            maxSize=capacity;
            minFreq=0;
            currSize=0;
        }

        void updateFreqListMap(NodeLFU* node){
            int oldFreq=node->freq;
            List* oldList=freqListMap[oldFreq];
            oldList->removeNode(node);

            //Cleaning if the list becomes empty
            if(oldList->size==0){
                delete oldList;
                freqListMap.erase(oldFreq);
                if(minFreq==oldFreq) minFreq++;
            }

            node->freq++;

            if(freqListMap.find(node->freq)==freqListMap.end()) freqListMap[node->freq]=new List();
            freqListMap[node->freq]->addFront(node);
        }

        int get(int key){
            if(keyNode.find(key)!=keyNode.end()){
                NodeLFU* node=keyNode[key];
                int val=node->val;
                updateFreqListMap(node);
                return val;
            }
            return -1;
        }
        //Time Complexity will be O(1)

        void put(int key,int val){
            if(maxSize==0) return;
            if(keyNode.find(key)!=keyNode.end()){
                NodeLFU* node=keyNode[key];
                node->val=val;
                updateFreqListMap(node);
            }
            else{
                if(currSize==maxSize){
                    List* list=freqListMap[minFreq];
                    NodeLFU* nodeToDel=list->tail->prev;
                    keyNode.erase(nodeToDel->key);
                    list->removeNode(nodeToDel);
                    delete nodeToDel;
                    currSize--;

                    //Delete empty frequency List
                    if(list->size==0){
                        delete list;
                        freqListMap.erase(minFreq);
                    }
                }
                currSize++;

                //New value has to be added which is not here previously
                minFreq=1;
                List* listFreq;
                if(freqListMap.find(minFreq)!=freqListMap.end()) listFreq=freqListMap[minFreq];
                else listFreq=new List();
                NodeLFU* node=new NodeLFU(key,val);
                listFreq->addFront(node);
                keyNode[key]=node;
                freqListMap[minFreq]=listFreq;
            }
        }
        //Time Complexity is O(1)

        //We also create a destructor so that when the object is deleted, the destructor will delete all the nodes and free up the memory
        ~LFUCache(){
            for(auto &it:keyNode) delete it.second;
            for(auto &it:freqListMap) delete it.second;
        }
};




int main(){
    //Your function here
    return 0;
}


