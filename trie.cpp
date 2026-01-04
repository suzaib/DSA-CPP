/*
Since we may need to create many classes for different types of Trie, according to different questions, we will be naming everyone Trie only
This is to save time and avoid using names like Trie2, Trie3
Pick the class Which suits your problem, and use it
We are doing it only to reduce our headache and it is harmless since we won't run this file 

Now back to topic


Trie is one of the toughest questions that can be asked in an interview
There are three types of queries
1) Insert the given word say "apple" into the list or whatever
2) Look for a word say "hello" in the list (hello word should exist, and so if something like hellow is there, it won't count)
3) Look if a word starts with say "hel" in the list

We will first use an example to understand the insert functionality of the trie data structure
Consider the words to be apple, apps, apxl, bac, bat

Generally the trie data structure is a class or a struct having two member functions
Assuming all characters to be lowercase */

// trie{
//     vector<int> a(26); //We should not use vector here, remember vectors are a good choice when array is dynamic, and here array size is fixed, so use array
//     bool flag=false;
// }

/*
This is what the trie data structure looks like
There will also be a root of the trie 

Further explanation is better understood visually so please watch video (Lecture 1 of trie series by striver)
*/

#include<bits/stdc++.h>
using namespace std;

class Node{
    public:
        Node* links[26]={nullptr};
        bool flag=false;
        
        bool containsChar(char ch){
            return links[ch-'a']!=nullptr;
        }

        void put(char ch,Node* node){
            links[ch-'a']=node;
        }

        Node* get(char ch){
            return links[ch-'a'];
        }

        void setEnd(){
            flag=true;
        }

        bool isEnd(){
            return flag;
        }
};

class Trie{
    private:
        Node* root;
    public:
        //Initialize your data structure here
        Trie(){
            root=new Node();
        }

        //Insert a word into the trie
        void insert(const string& word){
            Node* node=root;
            for(int i=0;i<word.size();i++){
                if(!node->containsChar(word[i])){
                    node->put(word[i],new Node());
                }

                //Moves to the reference trie
                node=node->get(word[i]);
            }

            node->setEnd();
        }
        //If n is the length of word, then code will run for n times
        //Time Complexity will be O(n)

        //Returns if a word is in the trie
        bool search(const string& word){
            Node* node=root;
            for(int i=0;i<word.size();i++){
                if(!node->containsChar(word[i])) return false;
                node=node->get(word[i]);
            }

            return node->isEnd();
        }
        //Time Complexity will be O(n)

        //Returns if there is a word in the trie that starts with the given prefix
        bool startsWith(const string& prefix){
            Node* node=root;
            for(int i=0;i<prefix.size();i++){
                if(!node->containsChar(prefix[i])) return false;
                node=node->get(prefix[i]);
            }

            return true;
        }
        //Time Complexity will be O(n)
};


//The previous Trie can't keep track of multiple elements insertions
//Therefore this time we will create one that can
//We will use a flag variable to denote the count of words
class Node{
    public:
        Node* links[26]={nullptr};
        int endsWith=0;
        int prefixCnt=0;
        void put(char ch, Node* node){
            links[ch-'a']=node;
        }

        Node* get(char ch){
            return links[ch-'a'];
        }

        bool containsChar(char ch){
            return links[ch-'a']!=nullptr;
        }

};

class Trie{
    private:
        Node* root;
    public:
        Trie(){
            root=new Node();
        }

        void insert(const string& word){
            int n=word.size();
            Node* node=root;
            for(int i=0;i<n;i++){
                if(!node->containsChar(word[i])) node->put(word[i],new Node());
                node=node->get(word[i]);
                node->prefixCnt++;
            }
            node->endsWith++;
        }
        //Time Complexity will be O(n)

        //Count the number of words ending with the given prefix
        int countPrefix(const string& prefix){
            int n=prefix.size();
            Node* node=root;
            for(int i=0;i<n;i++){
                if(!node->containsChar(prefix[i])) return 0;
                node=node->get(prefix[i]);
            }
            return node->prefixCnt;
        }
        //Time Complexity will be O(n)

        //Count the number of Words
        int countWords(const string& word){
            int n=word.size();
            Node* node=root;
            for(int i=0;i<n;i++){
                if(!node->containsChar(word[i])) return 0;
                node=node->get(word[i]);
            }
            return node->endsWith;
        }
        //Time Complexity will be O(n)

        //Erase a particular word from the trie
        //One thing to be noted here, we first need to confirm if the word exists or not
        void erase(const string& word){
            if(search(word)==false) return;
            int n=word.size();
            Node* node=root;
            for(int i=0;i<n;i++){
                node=node->get(word[i]);
                node->prefixCnt--;
            }
            node->endsWith--;
        }
        //Time Complexity will be O(n)

        //Search if a word exists or not
        bool search(const string& word){
            return countWords(word)>0;
        }
        //Time Complexity will be O(n)

        //See if a words start a given prefix
        bool startsWith(const string& prefix){
            return countPrefix(prefix)>0;
        }
        //Time Complexity will be O(n)

};


//Longest Word With all Prefixes
class Node{
    public:
        Node* links[26]={nullptr};
        bool flag=false;

        bool containsChar(char ch){
            return links[ch-'a']!=nullptr;
        }

        void put(char ch,Node* node){
            links[ch-'a']=node; 
        }

        Node* get(char ch){
            return links[ch-'a'];
        }

        void setEnd(){
            flag=true;
        }

        bool isEnd(){
            return flag;
        }
};

class Trie{
    private:
        Node* root;

    public:
        Trie(){
            root=new Node();
        }

        void insert(string &word){
            int n=word.size();
            Node* node=root;
            for(int i=0;i<n;i++){
                if(!node->containsChar(word[i])) node->put(word[i],new Node());
                node=node->get(word[i]);
            }
            node->setEnd();
        }

        bool search(string &word){
            int n=word.size();
            Node* node=root;
            for(int i=0;i<n;i++){
                if(!node->containsChar(word[i])) return false;
                node=node->get(word[i]);
            }
            return node->isEnd();
        }

        bool startsWith(const string &prefix){
            Node* node=root;
            int n=prefix.size();
            for(int i=0;i<n;i++){
                if(!node->containsChar(prefix[i])) return false;
                node=node->get(prefix[i]);
            }
            return true;
        }

        bool allPrefixExists(string &word){
            bool f1=true;
            Node* node=root;
            int n=word.size();
            for(int i=0;i<n;i++){
                if(node->containsChar(word[i])){
                    node=node->get(word[i]);
                    if(!node->isEnd()) return false;
                }
                else return false;
            }
            return true;
        }
};

string longestCompleteStr(vector<string> &arr){
    Trie t;

    int n=arr.size();
    for(int i=0;i<n;i++) t.insert(arr[i]);
    
    //Taking just maxLen won't work, since we need lexicographically smaller
    string longest="";

    for(auto &it:arr){
        if(t.allPrefixExists(it)){
            if(it.size()>longest.size()) longest=it;
            else if(it.size()==longest.size() && it<longest) longest=it;
        }
    }

    if(longest=="") return "NONE";
    return longest;
}


//Number of Distinct Substrings in a string
//Brute Force
//Use a loop and set to build and store unique strings
int noOfDistSubstr_brute(string &s){
    int n=s.size();
    unordered_set<string> st;
    for(int i=0;i<n;i++){
        string temp="";
        for(int j=i;j<n;j++){
            temp+=s[j];
            st.insert(temp);
        }
    }
    return st.size()+1;
}
//The for loop runs for about n2 times
//Inside the loop, adding temp+=str[i] makes it n3 in total due to string copying
//Space is taken by the unordered_set equal to the number of distinct substrings
//Time Complexity will be O(n3)
//Space Complexity will be O(m)

//Optimal Method
//This uses the same logic behind trie, but we won't need a complete trie, the trie node will do
class Node{
    public:
        Node* links[26]={nullptr};
        bool containsChar(char c){
            return links[c-'a']!=nullptr;
        }

        Node* get(char c){
            return links[c-'a'];
        }

        void put(char c,Node* node){
            links[c-'a']=node;
        }
};

int distSubstr(string &s){
    int n=s.size();
    Node* root=new Node();
    int cnt=0;
    for(int i=0;i<n;i++){
        Node* node=root;
        for(int j=i;j<n;j++){
            if(!node->containsChar(s[j])){
                cnt++;
                node->put(s[j],new Node());
            }
            node=node->get(s[j]);
        }
    }
    return cnt;
}
//Time Complexity will be O(n2)



//XOR Problems
//These are generally solved using tries
//Some steps should be remembered while solving them
//Step 1: Insert all the numbers in trie(bit wise)
//Step 2: Take the number x and find the max xor from array

//Given an array arr and a number x, find the maximum xor of x^y where y can be any element from arr
class Node{
    public:
        Node* links[2]={nullptr};
        bool containsKey(int bit){
            return links[bit]!=nullptr;
        }

        Node* get(int bit){
            return links[bit];
        }

        void put(int bit,Node* node){
            links[bit]=node;
        }
};

class Trie{
    private:
        Node* root;

    public:
        Trie(){
            root=new Node();
        }

        void insert(int n){
            Node* node=root;
            for(int i=31;i>=0;i--){
                int bit=(n>>i)&1;
                if(!node->containsKey(bit)) node->put(bit,new Node());
                node=node->get(bit);
            }
        }
        //The loop runs for 32 times
        //Time Complexity will be O(32)

        int getMax(int n){
            Node* node=root;
            int ans=0;
            for(int i=31;i>=0;i--){
                int bit=(n>>i)&1;
                if(node->containsKey(1-bit)){
                    ans=ans|(1<<i);
                    node=node->get(1-bit);
                }
                else node=node->get(bit);
            }

            return ans;
        }
        //The loop runs for 32 times
        //Time Complexity will be O(32)
};

//Now we solve our question
//Max XOR with array elements
int maxXOR(int x,vector<int> &arr){
    int n=arr.size();
    Trie t;
    for(int i=0;i<n;i++) t.insert(arr[i]);
    return t.getMax(x);
}
//The for loop runs for n times and the insert function runs for 32 times
//The getMax function runs for 32 times
//Time Complexity will be O(32n+32)



//XOR of elements taken from two arrays
int maxXORII(vector<int> &arr1,vector<int> &arr2){
    int n=arr1.size();
    int m=arr2.size();

    //First we insert all of arr1 elements in the trie
    Trie t;
    for(int i=0;i<n;i++) t.insert(arr1[i]);

    //Now we take each element from arr2 one by one and compare the XOR
    int ans=0;
    for(int i=0;i<m;i++){
        int maxi=t.getMax(arr2[i]);
        ans=max(ans,maxi);
    }
    return ans;
}
//The first for loop takes n time and 32 for insertion, totalling 32*n
//The second for loop runs for m*32 times (32 for the getMax function)
//Time Complexity will be O(32(m+n))





//Maximum XOR with offline Queries
//Brute Force
//Simply find the xor with all the elements lesser than a[i] and then find the max among them
vector<int> maxXORIII_brute(vector<int> &arr,vector<pair<int,int>> &queries){
    int n=arr.size();
    vector<int> ans;
    for(auto it:queries){
        int x=it.first;
        int y=it.second;
        int maxi=0;
        for(int i=0;i<n;i++){
            if(arr[i]>y) continue;
            maxi=max(maxi,x^arr[i]);
        }
        ans.push_back(maxi);
    }
    return ans;
}
//Let q be the size of the queries table
//The nested loop will run for nq times
//No space is needed to solve the question
//Time Complexity will be O(nq)
//Space Complexity will be O(q)

//Optimal Method
//We will use the trie made from the previous question
vector<int> maxXORIII(vector<int> &arr,vector<pair<int,int>> &queries){
    int n=arr.size();

    //First we need to sort our array
    sort(arr.begin(),arr.end());
    //Time Complexity will be O(nlogn)

    //Now lets create a new table to store queries with their original serial no
    vector<pair<int,pair<int,int>>> oQ;
    int q=queries.size();
    for(int i=0;i<q;i++) oQ.push_back({queries[i].second,{queries[i].first,i}});

    //Now we sort the newly made queries table
    sort(oQ.begin(),oQ.end());
    //Time Complexity will be O(qlogq)
    
    //Creating an ans array to store the answers
    vector<int> ans(q,0);

    int idx=0;
    Trie t;
    for(auto it:oQ){
        int y=it.first;
        int x=it.second.first;
        int qIdx=it.second.second;

        while(idx<n && arr[idx]<=y){

            t.insert(arr[idx]);
            //Insert function takes 32 time

            idx++;
        }
        //The while loop runs for n in total

        if(idx==0) ans[qIdx]=-1;
        else ans[qIdx]=t.getMax(x);
        //getMax function runs for O(32) time
    }

    //This loop runs for (q+n)*32

    return ans;
}
//The total time is qlogq + nlogn + 32(q+n)
//Space Complexity is quite complex to compute in case of tries
//Time Complexity will be O(qlogq+nlogn+32(q+n))


int main(){
    //Your code here
    return 0;
}

