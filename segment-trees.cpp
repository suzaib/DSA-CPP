#include<bits/stdc++.h> 
using namespace std;

/*
Segment Trees

Use Case: consider and array [0,2,1,2,5], and we have to find max in range [1,4] (these are indices), the max value between index 1 and 4 is 5, similar minimum value is 1
We can also be asked to this step for n times, say n queuries, having different indices
Brute force solution will be to run a loop from low range to high range, which can be n at worst case
If there are a total of n queries, then applying the brute force, we will have to run the loop for n*n times

Segment Trees can do this in logn time compare to n2
Consider array : [2,1,0,4,3,7]
Form a index node which denotes range from 0-5 index, keep splitting it like the merge sort, similar to binary trees
0-5 splits to 0-2 and 3-5, 0-2 splits in 0-1 and 2-2, 0-1 splits to 0-0 and 1-1, this is where our base case is
0-0 node will be filled by min value occuring in range arr[0] to arr[0] which is arr[0]=2, similarly 1-1 will be filled with 1
Now taking from these two the min value, we can fill the above node 0-1, which will get value 1(min of child nodes)
Keep doing the same thing and your visual segment tree is formed

Now let's draw this tree in code, we will use a similar concept to heaps, just like heaps were also binary tree which were denoted through arrays, we do the same here
The first node will be node 0 and will be stored at index 0 of the segment array
The left child will be 2*idx+1 and the right child will be 2*idx+2
For memory, just start numbering the nodes from 0, level wise, and skip the numbers if the nodes aren't there

We also need to know how much longer array would we need for storing the full segment tree
There's a proof that shows to store the segment tree we will need an array of size O(4n), which will always have enough space
The proof is quite long and hence we will not discuss it. n in the above is the size of the array

First up is building the segment tree
The basic recursion will look like:
f(idx,low,high){
    if(low==high) return seg[idx]=arr[low]
    int mid=(low+high)>>1
    f(2*mid+1,low,mid)
    f(2*mid+2,mid+1,high)
    seg[idx]=min(seg[2*mid+1],seg[2*mid+2])
}
Time Complexity can be at max 4n since this segment array will be at max 4n nodes and we also know that each node will be traversed
Time Complexity will be O(4n) in worst case, but most often we can say it will be around O(n)



Now dealing with the queries
Below we are talking about the overlap between the node index and range
For eg a node indexed 0, and we are looking at a range of say index 2 to 4(careful, each node also has a range associated with it, we are not talking about the node's range, this is the range of the query, the question)
1) Partial Overlap  : return (min(leftNode,rightNode))
Consider the query is to find the range within 2-4 and the node has the range associated with it as 0-5, this is a partial overlap
Since the node's range has some part overlapping, this is partial overlap. In this case return min(leftNode,rightNode)
The query being 2-4 and the node's range being 1-2 is also partial overlap

2) No Overlap : return INT_MAX (since we are looking for min value)
If the query is 2-4 and we have a node whose range is 0-1, this is no overlap, in this case return INT_MAX

3) full Overlap
If the query is 2-4 and the node's range is 3-3, return seg[idx] in this case of full overlap

Let us tell by an example
Consider the array [1,3,2,0,4,5] we always start from the 0th node which will have the range as 0-5 (6 elements in total)
Consider the query to be 2-4, 0th node in that case is having partial overlap therefore it will return (min(leftNode,rightNode))
The left node is 0-2 and the right node is 3-5 both of which again have partial overlap
Now consider the 0-2 return min(leftNode,rightNode), its left node will be 0-1, this will return INT_MAX since no overlap(and hence it contributes nothing) 
And the right node would be 2-2 which is a full overlap
Therefore the right node will return seg[idx]
This will keep happening

Now consider l and r be the query range and low and high denote the range associated with the node
Then our three cases would be :
No overlap       : if r<low || high<l
full Overlap : low>=l && high<=r
Partial Overlap  : no need for condition, will be handled by the else case

Types of Queries
1) One is the normal one where we say find the min in range [l,r]
2) This asks us to update the val of a given idx, so we have to change the whole segment tree as well

Point Update
For the second type of query, something like the point update comes in
Consider we have to change the value at index 2, start from 0-5, which way does the index lie? left side, 0-2, right side 2-2, here update the value
After you have updated the value, again take the min(left,right) and keep doing that till you reach the index 0 node
This was the point update
The code will look similar to below one, where _idx is the index which needs to be replace with value val
update(idx,low,high,_idx,val){
    if(low==high){
        //this is the moment where we have reached the _idx, so change value here 
        seg[low]=val
        return
    }
    mid=(low+high)/2
    if(_idx<=mid){
        //This case means we need to move left
        update(2*mid+1,low,mid,_idx,val)
    }
    else update(2*mid+2,low,mid_idx,val)
    //Now that we have traversed left and right, we must update the min values
    seg[idx]=min(seg[2*mid+1],seg[2*mid+2])



We will now discuss the time complexity for queries
In case of full or no overlap, we simply return, therefore time taken O(1)
So we need to study the time taken in case of partial overlap only

First let's consider small range, in that case most time we will get no overlap due to small range of query, and mostly we will have to travel to deepest point for only some time
Therefore in case of small query range, time taken will be logn (time taken to reach the depth of tree)

Incase of very large query range, most of the cases will be of full overlap so we return mostly, again we can say that at max logn will be the time taken
Incase of medium overlap we can also say that at max the depth of the tree will be covered since partial overlaps won't be that much
Therefore Time Complexity will be O(logn), this can be 2logn or 3logn etc



Solving a problem
Consider two array arr1 and arr2 and we have to find min in l1,r1 and l2,r2 (1 refers to arr1 and 2 refers to arr2), and then give the overall minimum value
Or we have to update the value of a particular index
The first type of query is denoted by 1 and given as 1 (l1,r1),(l2,r2)
The second type of query is denoted by 2 and given as 2 arrNo , ind, val (arrNo denoted in which arr we have to do the change)
The obvious solution to the problem is to create two segment array for each tree and solve the problem individually for each tree and then find the minimum of both the answers (for query 1)
For query type 2, we can update the segment arr of that particular tree, that's all

A better way is to create a class template and create two objects, object1 and object2

Therefore we will be creating a class and inside that we will put all our code
*/

#include<bits/stdc++.h>
using namespace std;
class SGTree{
    public:
        vector<int> seg;
        SGTree(int n){
            seg.resize(4*n+1); //Just for safety reasons
        }
        //Build function for segment trees
        void build(int idx,int low,int high,vector<int> &arr){
            if(low==high){
                seg[idx]=arr[low];
                return;
            }
            int mid=(low+high)>>1;
            build(2*idx+1,low,mid,arr);
            build(2*idx+2,mid+1,high,arr);
            seg[idx]=min(seg[2*idx+1],seg[2*idx+2]);
        }

        //The query function
        int query(int idx,int low,int high,int l,int r){

            //No Overlap
            if(l>high || r<low) return INT_MAX;

            //full Overlap
            if(l<=low && r>=high) return seg[idx];

            //Partial Overlap
            int mid=(low+high)>>1;
            int left=query(2*idx+1,low,mid,l,r);
            int right=query(2*idx+2,mid+1,high,l,r);
            return min(left,right);
        }

        //The update code
        void update(int idx,int low,int high,int _idx,int val){
            if(low==high){
                seg[idx]=val;
                return;
            }
            int mid=(low+high)>>1;
            if(_idx<=mid) update(2*idx+1,low,mid,_idx,val);
            else update(2*idx+2,mid+1,high,_idx,val);
            seg[idx]=min(seg[2*idx+1],seg[2*idx+2]);
        }

        //The solve function 
        void solve(){
            int n;
            cin>>n;
            vector<int> arr(n);
            for(int i=0;i<n;i++) cin>>arr[i];
            build(0,0,n-1,arr);
            int q;
            cin>>q;
            while(q--){
                int type;
                cin>>type;
                if(type==1){
                    int l,r;
                    cin>>l>>r;
                    cout<<query(0,0,n-1,l,r)<<"\n";
                }
                else{
                    int i,val;
                    cin>>i>>val;
                    update(0,0,n-1,i,val);
                    arr[i]=val;
                }
            }
        }
};
//We will write a function for the type of question when we have two arrays
void solve2(){
    int n1;
    cin>>n1;
    vector<int> arr1(n1);
    for(int i=0;i<n1;i++) cin>>arr1[i];
    SGTree sg1(n1);
    sg1.build(0,0,n1-1,arr1);

    int n2;
    cin>>n2;
    vector<int> arr2(n2);
    for(int i=0;i<n2;i++) cin>>arr2[i];
    SGTree sg2(n2);
    sg2.build(0,0,n2-1,arr2);

    int q;
    cin>>q;
    while(q--){
        int type;
        cin>>type;
        if(type==1){
            int l1,r1,l2,r2;
            cin>>l1>>r1>>l2>>r2;
            int min1=sg1.query(0,0,n1-1,l1,r1);
            int min2=sg2.query(0,0,n2-1,l2,r2);
            cout<<min(min1,min2)<<"\n";
        }
        else{
            int arrNo,i,val;
            cin>>arrNo>>i>>val;
            if(arrNo==1){
                sg1.update(0,0,n1-1,i,val);
                arr1[i]=val;
            }
            else{
                sg2.update(0,0,n2-1,i,val);
                arr2[i]=val;
            }
        }
    }
}


//Xenia and Bit operations
//Drawing the tree structure is very important
class SGTree{
    public:
        vector<int> seg;
        SGTree(int n){
            seg.resize(4*n+1);
        }

        void build(int idx,int low,int high,vector<int> &arr, bool flag){
            if(low==high){
                seg[idx]=arr[low];
                return;
            }
            int mid=(low+high)>>1;
            build(2*idx+1,low,mid,arr,!flag);
            build(2*idx+2,mid+1,high,arr,!flag);
            if(flag) seg[idx]=seg[2*idx+1]|seg[2*idx+2];
            else seg[idx]=seg[2*idx+1]^seg[2*idx+2];
        }

        void update(int idx,int low,int high,int pos,int val,bool flag){
            if(low==high){
                seg[idx]=val;
                return;
            }
            int mid=(low+high)>>1;
            if(pos<=mid) update(2*idx+1,low,mid,pos,val,!flag);
            else update(2*idx+2,mid+1,high,pos,val,!flag);
            if(flag) seg[idx]=seg[2*idx+1]|seg[2*idx+2];
            else seg[idx]=seg[2*idx+1]^seg[2*idx+2];
        }
};

//The upper class is to be used here
int XeniaAndBits(){
    int n,m;
    cin>>n>>m;
    int el=1<<n;
    bool flag=(n%2!=0);
    vector<int> arr(el);
    for(int i=0;i<el;i++) cin>>arr[i];
    SGTree sg(el);
    sg.build(0,0,el-1,arr,flag);

    while(m--){
        int i,val;
        cin>>i>>val;

        //In codeforces problem, the indexing used is 1 based, so we decrease value of i by one
        i--;

        sg.update(0,0,el-1,i,val,flag);
        cout<<sg.seg[0]<<"\n";
    }
}


//Codeforces Problem 380C : Sereja and Brackets
class Node{
    public:
        int open;
        int closed;
        int full;

        Node(int open,int closed,int full){
            this->open=open;
            this->closed=closed;
            this->full=full;
        }

        Node(){
            this->open=0;
            this->closed=0;
            this->full=0;
        }

};

class SGTree{
    public:

        vector<Node> seg;
        SGTree(int n){
            seg.resize(4*n+1);
        }

        Node merge(Node left, Node right){
            Node curr=Node(0,0,0);
            curr.open=left.open+right.open-min(left.open,right.closed);
            curr.closed=left.closed+right.closed-min(left.open,right.closed);
            curr.full=left.full+right.full+min(left.open,right.closed);
            return curr; 
        }

        void build(int idx,int low,int high,string &str){
            if(low==high){
                seg[idx]=Node(str[low]=='(',str[low]==')',0);
                return;
            }

            int mid=(low+high)>>1;
            build(2*idx+1,low,mid,str);
            build(2*idx+2,mid+1,high,str);
            seg[idx]=merge(seg[2*idx+1],seg[2*idx+2]);
        }

        Node query(int idx,int low,int high,int l,int r){

            //Complete Overlap
            if(low>=l && high<=r) return seg[idx];

            //No Overlap
            else if(low>r || high<l) return Node();

            //Partial Overlap
            int mid=(low+high)>>1;
            Node left=query(2*idx+1,low,mid,l,r);
            Node right=query(2*idx+2,mid+1,high,l,r);
            return merge(left,right);
        }
};

void SerejaAndBrackets(){
    string s;
    cin>>s;
    int q;
    cin>>q;
    int n=s.size();
    SGTree sg(n);
    sg.build(0,0,n-1,s);
    while(q--){
        int l,r;
        cin>>l>>r;

        //The question has 1 based indexing therefore we reduce the value by one unit
        l--;
        r--;
        Node node=sg.query(0,0,n-1,l,r);
        cout<<node.full*2<<"\n";
    }
}



//Range Query
//This time instead of giving the max or min element, we need to give the sum of all elements in that range
class SGTree{
    public:
        vector<int> seg;

        SGTree(int n){
            seg.resize(4*n+1);
        }

        void build(int idx,int low,int high,vector<int> &arr){
            if(low==high){
                seg[idx]=arr[low];
                return;
            }
            int mid=(low+high)>>1;
            build(2*idx+1,low,mid,arr);
            build(2*idx+2,mid+1,high,arr);
            seg[idx]=seg[2*idx+1]+seg[2*idx+2];
        }

        void update(int idx,int low,int high,int i,int val){
            if(low==high){
                seg[idx]=val;
                return;
            }
            int mid=(low+high)>>1;
            if(i<=mid) update(2*idx+1,low,mid,i,val);
            else update(2*idx+2,mid+1,high,i,val);
            seg[idx]=seg[2*idx+1]+seg[2*idx+2];
        }

        int query(int idx,int low,int high,int l,int r){
            //Complete Overlap
            if(low>=l && high<=r) return seg[idx];

            //No Overlap
            if(l>high || r<low) return 0;

            //Partial Overlap
            int mid=(low+high)>>1;
            int left=query(2*idx+1,low,mid,l,r);
            int right=query(2*idx+2,mid+1,high,l,r);
            return (left+right);
        }
};

void rangeSumQuery(){
    int n;
    cin>>n;
    vector<int> arr(n);
    SGTree sg(n);
    for(int i=0;i<n;i++) cin>>arr[i];

    int q;
    cin>>q;
    while(q--){
        int type;
        cin>>type;
        if(type==1){
            int l,r;
            cin>>l>>r;
            int ans=sg.query(0,0,n-1,l,r);
            cout<<ans<<"\n";
        }
        else{
            int i,val;
            cin>>i>>val;
            sg.update(0,0,n-1,i,val);
            arr[i]=val;
        }
    }

}


//Count Inversions
//This can also be done using the same trick as merge sort
//But we will do it using segment trees
void countInversions(){
    int n;
    cin>>n;
    vector<int> arr(n);
    int mx=0;
    for(int i=0;i<n;i++){
        cin>>arr[i];
        mx=max(mx,arr[i]);
    }
    mx++;
    vector<int> freq(mx,1);
    SGTree sg(mx);
    sg.build(0,0,mx-1,freq);
    int cnt=0;
    for(int i=0;i<n;i++){
        freq[arr[i]]--;
        sg.update(0,0,mx-1,arr[i],-1)

        cnt+=sg.query(0,0,mx-1,1,arr[i]-1);
    }
}

void countInversion(){
    int n;
    cin>>n;
    vector<int> arr(n);
    int mx=0;
    for(int i=0;i<n;i++){
        cin>>arr[i];
        mx=max(mx,arr[i]);
    }
    mx++;
    vector<int> freq(mx,0);
    for(int i=0;i<n;i++) freq[arr[i]]++;
    SGTree sg(mx);
    sg.build(0,0,mx-1,freq);
    int cnt=0;
    for(int i=0;i<n;i++){
        freq[arr[i]]--;
        sg.update(0,0,mx-1,arr[i],freq[arr[i]]);
        cnt+=sg.query(0,0,mx-1,0,arr[i]-1);
    }
    cout<<cnt<<"\n";
}

/*

A Video is recommended for the below topic

Handling Range Updates
Earlier we only used to update point in the segment tree
Now we will be given a range k and we need to update it
Brute Force
Loop from l to r and update using the concept of point update
Point update takes logn time so this will take klogn time
The optimal method to do this is called lazy propagation in segment trees

Lazy Propagation
Step 1 : Update the node when you see it
Step 2 : After updating, propagate the update downwards

Doing Range Updates
Increase the value by val(given)

Some Rules to follow
Traverse the tree and you will get three conditions
1)Complete Overlap : Update the node, lazy propagate down and return
2)No Overlap : Just return, no need to do anything
3)Partial Overlap : Call left, call right and then use node=left+right

Doing Range Queries

Some Rules to follow
First complete any previous updates if remaining
1) Complete Overlap : return seg[idx] value
2) No Overlap : return 0
3) Partial Overlap : go left, go right, bring the sum and return left+right


*/

class SGTree{
    public:
        vector<int> seg,lazy;

        SGTree(int n){
            seg.resize(4*n+1);
            lazy.resize(4*n+1);
        }
        //Time Complexity will be O(8n)

        void build(int idx,int low,int high,vector<int> &arr){
            if(low==high){
                seg[idx]=arr[low];
                return;
            }

            int mid=(low+high)>>1;
            build(2*idx+1,low,mid,arr);
            build(2*idx+2,mid+1,high,arr);
            seg[idx]=seg[2*idx+1]+seg[2*idx+2];
        }
        //Every node is visited once, total of 4n nodes
        //Time Complexity will be O(4n)

        void update(int idx,int low,int high,int l,int r,int val){
            //In this we first check if there is a previous update remaining
            //If yes, then we first take care of that
            if(lazy[idx]!=0){
                seg[idx]+=(high-low+1)*lazy[idx];

                //Now we propagate downwards for the remaining elements
                //The node will have children only when low!=high
                if(low!=high){
                    lazy[2*idx+1]+=lazy[idx];
                    lazy[2*idx+2]+=lazy[idx];
                }
                lazy[idx]=0;
            }

            //Now we handle our overlap cases
            //No Overlap : Simply return
            if(high<l || r<low) return;

            //Complete Overlap
            if(low>=l && high<=r){
                seg[idx]+=(high-low+1)*val;
                if(low!=high){
                    lazy[2*idx+1]+=val;
                    lazy[2*idx+2]+=val;
                }
                return;
            }

            //Partial Overlap
            int mid=(low+high)>>1;
            update(2*idx+1,low,mid,l,r,val);
            update(2*idx+2,mid+1,high,l,r,val);
            seg[idx]=seg[2*idx+1]+seg[2*idx+2];
        }
        //Time Complexity will be O(logn)

        int query(int idx,int low,int high,int l,int r){

            //First we check if there's a previous update remaining
            if(lazy[idx]!=0){
                seg[idx]+=(high-low+1)*lazy[idx];
                
                //If children exists, propagate downwards
                if(low!=high){
                    lazy[2*idx+1]+=lazy[idx];
                    lazy[2*idx+2]+=lazy[idx];
                }
                
                //As we have done updation, reset lazy node value to 0
                lazy[idx]=0;
            }

            //Now we check for overlapping cases
            //Case I : No overlap
            //Simply return 0
            if(l>high || r<low) return 0;

            //Case II : Complete Overlap
            //Simply return seg[idx]
            if(low>=l && high<=r) return seg[idx];

            //Case III : Partial Overlap
            //Go left and right and then return left+right
            int mid=(low+high)>>1;
            int left=query(2*idx+1,low,mid,l,r);
            int right=query(2*idx+2,mid+1,high,l,r);
            return (left+right);
        }
}

//This solve3 function is in respect to the above tree
void solve3(){
    int n;
    cin>>n;
    vector<int> arr(n);
    for(int i=0;i<n;i++) cin>>arr[i];
    SGTree sg(n);
    sg.build(0,0,n-1,arr);

    //Taking the queries
    int q;
    cin>>q;
    while(q--){
        int type;
        cin>>type;
        if(type==1){
            int l,r;
            cin>>l>>r;
            cout<<sg.query(0,0,n-1,l,r)<<"\n";
        }
        else{
            int l,r,val;
            cin>>l>>r>>val;
            sg.update(0,0,n-1,l,r,val);
        }
    }
}


//Range Min query and update
class SGTree{
    public:
        vector<int> seg;
        vector<int> lazy;
        
        SGTree(int n){
            seg.resize(4*n+1);
            lazy.resize(4*n+1);
        }

        void build(int idx,int low,int high,vector<int> &arr){
            if(low==high){
                seg[idx]=arr[low];
                return;
            }
            
            int mid=(low+high)>>1;
            build(2*idx+1,low,mid,arr);
            build(2*idx+2,mid+1,high,arr);
            seg[idx]=min(seg[2*idx+1],seg[2*idx+2]);
        }
        //Every node is visited once
        //Time Complexity will be O(n)


        void update(int idx,int low,int high,int l,int r,int val){
            if(lazy[idx]!=0){
                seg[idx]+=lazy[idx];

                if(low!=high){
                    lazy[2*idx+1]+=lazy[idx];
                    lazy[2*idx+2]+=lazy[idx];
                }
                lazy[idx]=0;
            }

            //No Overlap
            if(high<l || r<low) return;

            //Complete Overlap
            if(low>=l && high<=r){
                seg[idx]+=val;

                if(low!=high){
                    lazy[2*idx+1]+=val;
                    lazy[2*idx+2]+=val;
                }
                return;
            }

            //Partial Overlap
            int mid=(low+high)>>1;
            update(2*idx+1,low,mid,l,r,val);
            update(2*idx+2,mid+1,high,l,r,val);
            seg[idx]=min(seg[2*idx+1],seg[2*idx+2]);
        }
        //Time Complexity will be O(logn)


        int query(int idx,int low,int high,int l,int r){
            if(lazy[idx]!=0){
                seg[idx]+=lazy[idx];

                //If children exists, propagate downwards
                if(low!=high){
                    lazy[2*idx+1]+=lazy[idx];
                    lazy[2*idx+2]+=lazy[idx];
                }

                lazy[idx]=0;
            }

            //No Overlap
            if(high<l || r<low) return INT_MAX;
            
            //Complete Overlap
            if(low>=l && high<=r) return seg[idx];

            //Partial Overlap
            int mid=(low+high)>>1;
            int left=query(2*idx+1,low,mid,l,r);
            int right=query(2*idx+2,mid+1,high,l,r);
            return min(left,right);
        }
        //Time Complexity will be O(logn)

}



//Question 
//Given an array say : [1,1,0,0,1,0,1] , here 1=head and 0=tails and we will be given two types of queries
//Type 1 : range [l,r] : Tell how many heads are in range l,r 
//Type 2 : flip the coin, that is head becomes tails and tails becomes head so the array will look like : [0,0,1,1,0,1,0]

//We will again use lazy propagation
//The lazy node will store a value which will indicate the number of flips
//Since a coin has only two sides, therefore two flips=no flip or same as previous
//In the update function we will return the sum of the below nodes as we need to give the number of heads
class SGTree{
    public:
        vector<int> seg;
        vector<int> lazy;

        SGTree(int n){
            seg.resize(4*n+1);
            lazy.resize(4*n+1);
        }

        //First we build the segment tree
        void build(int idx,int low,int high,vector<int> &arr){
            if(low==high){
                seg[idx]=arr[low];
                return;
            }

            int mid=(low+high)>>1;
            build(2*idx+1,low,mid,arr);
            build(2*idx+2,mid+1,high,arr);
            seg[idx]=seg[2*idx+1]+seg[2*idx+2];
        }
        //Each node is visited once
        //Time Complexity will be O(n)

        //The update function flips the coins
        void update(int idx,int low,int high,int l,int r){

            //Before doing anything, we must check if the current node needs to be updated
            //That will only happen if the lazy node has an odd value
            if(lazy[idx]%2!=0){
                int tails=(high-low+1)-seg[idx];

                seg[idx]=tails;
                
                if(low!=high){
                    lazy[2*idx+1]+=1;
                    lazy[2*idx+2]+=1;
                }

                //Reset the lazy node
                lazy[idx]=0;
            }

            //Now we take care of our cases

            //No Overlap
            if(r<low || l>high) return;

            //Complete Overlap
            if(low>=l && high<=r){
                int tails=(high-low+1)-seg[idx];
                seg[idx]=tails;

                if(low!=high){
                    lazy[2*idx+1]+=1;
                    lazy[2*idx+2]+=1;
                }

                return;
            }

            int mid=(low+high)>>1;
            update(2*idx+1,low,mid,l,r);
            update(2*idx+2,mid+1,high,l,r);
            seg[idx]=(seg[2*idx+1]+seg[2*idx+2]);
        }
        //Time Complexity will be O(logn)

        //Function to handle query
        int query(int idx,int low,int high,int l,int r){
            if(lazy[idx]%2!=0){
                int tails=(high-low+1)-seg[idx];
                seg[idx]=tails;

                if(low!=high){
                    lazy[2*idx+1]+=1;
                    lazy[2*idx+2]+=1;
                }

                lazy[idx]=0;
            }

            //No Overlap
            if(r<low || high<l) return 0;

            //Complete Overlap
            if(low>=l && high<=r) return seg[idx];

            //Partial Overlap
            int mid=(low+high)>>1;
            int left=query(2*idx+1,low,mid,l,r);
            int right=query(2*idx+2,mid+1,high,l,r);
            return left+right;
        }
        //Time Complexity will be O(logn)
}

int main(){
    //Your function
    return 0;
}
