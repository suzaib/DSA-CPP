//Graphs

//Types:
    //Undirected Graphs
    //Directed Graphs

//Terminology
    //Node/Vertex
    //Edge (in both direction in undirected graph) (in directed graph it is called a directed edge)
    //Path (Contain a lot of nodes/vertices and each of them are reachable) for if we have a path 123 then we must be able to reach all three 
    //nodes(1,2,3) via some edge(following arrays if they exist), also no node appears twice in a path.
    //Degree of a node
        //For undirected graph :(no.of edges attached to a node)
        //For Directed graph :
            //Indegree : No. of incoming edges to that node (arrow pointing towards node)
            //Outdegree : No. of outgoing edges to that node (arrow pointing away)
    //Degree of a graph
        //For Undirected Graph : Sum of individual degrees of all nodes OR 2*(total edges)
        //For Directed Graph
    //Edge Weight : They are assigned any value which seems fit for the problem, if they are not assigned , then we should take weight of each edge as unit weight , that is 1


//A Graph need not be an enclosed structure, even a binary tree is a graph, however if it is enclosed we call the enclosed version as a cycle
//A graph can have multiple cycles , if a graph has cycles, cyclic prefix is added to its name
//A closed directed graph is not necessary cyclic, cyclic means you get the same node from which you started (following the arrows if they are present)
//DAG(Directed Acyclic Graph)


//Representation
//We will be given n,m (n is the number of nodes and m is the number of edges) along with telling whether the graph is undirected or directed  
//(Suppose n=5 and m=6 )
//After this they will give the edges and their terminal nodes(without stating direction) as :
    // (2,1) (1,3) (2,4) (3,4) (2,5) (4,5)
//Therefore the input given will look like : (5,6) (2,1) (1,3) (2,4) (3,4) (2,5) (4,5) (first bracket of 5,6 represents the value of n and m)
//We need some way to store these edges, We can use a matrix or a list, For now we use Matrix , this matrix is called Adjacency Matrix
//Since highest value of node is 5 and they start from 1 therefore we need to have all indexes uptil 5 hence we declare an array like : adj[n+1][n+1]
//So we make a matrix mat[6][6] and we fill mat[2][1]=1 and mat[1][2]=1 (for(2,1)) and so on for each , rest we fill as 0 , the 1 filled at a particular place tells us that there's a edge between those two indices
//But for this we end up using NxM space which is quite much 

/*Some important Notes regarding time complexity
for(int i=0;i<n;i++){
    for(auto it:adj[i]){
        ....
        }
    }

This code takes time V+E for directed graph
And V+2E for undirected graph in worst case

*/

#include<bits/stdc++.h>
using namespace std;
vector<vector<int>> storeGraph_adjMatrix(int n,int m){
    vector<vector<int>> mat(n+1,vector<int>(m+1,0));
    for(int i=0;i<m;i++){
        int u;
        int v;
        cin>>u>>v;
        mat[u][v]=1;
        mat[v][u]=1; 
    }
    return mat;
}
//Space Complexity will be O(n*n)


//The other method of storing is using adjacency list which is nothing but 2d array;
//eg : [[],[3,4]] the 0th index has nothing but the 1st index has 3,4 , this means that the vertex named first is connected with 3 and 4
vector<vector<int>> storeGraph_list(int n,int m){
    vector<vector<int>> adj(n+1);
    for(int i=0;i<m;i++){
        int u,v;
        cin>>u,v;
        adj[u].push_back(v);

        //This second line is not needed if the graph is directed
        adj[v].push_back(u);
    }
    return adj;
}
//Space Complexity will be O(E) (for directed Graph) and O(2E) for undirected graph. E is the number of edges

/*
What if the graph has also edge weights? , In Adjacency Matrix,we put 1 wherever we found an intersection , instead of that one,just put the edge weight
In list instead of storing just single int, store pairs 

Connected Components (A video is recommended (striver's only)) , think of two different graphs, they can be the same graph ,just not connected 

Traversal Techniques in graphs:
BFS: (Breadth First Search)
We will be given a starting node, which will be considered at level 0 , we first write up this node, now the nodes connected directly to this will be at level 1, then we write them,(don't worry about the order),
now the nodes connected directly to the nodes of level 1 will be of level 2 , we write them now and so on......
*/

vector<int> levelOrderTraversal(int n,vector<vector<int>> adj){
    vector<int> vis(n,0);//Assuming 0 based indexing
    queue<int> q;
    vector<int> bfs;
    q.push(0);
    vis[0]=1;
    while(!q.empty()){
        int node=q.front();
        q.pop();
        bfs.push_back(node);

        //This for loop will run for total degrees, that is 2e
        for(auto it:adj[node]){
            if(!vis[it]){
                vis[it]=1;
                q.push(it);
            }
        }
    }
    return bfs;
}
//Time Complexity will be O(n + 2e) (n is number of nodes and e is edges)


//Depth First Search Traversal
//Using Recursion
//First we make a helper function
void dfsHelper(int node,vector<vector<int>> adj,vector<int> &vis,vector<int> &ans){
    vis[node]=1;
    ans.push_back(node);
    for(auto it:adj[node]){
        if(vis[it]==0) dfsHelper(it,adj,vis,ans);
    }
}
vector<int> dfs(int n,vector<vector<int>> adj){
    vector<int> vis(n,0);//Assuming 0 based indexing
    vector<int> ans;
    dfsHelper(0,adj,vis,ans);
    return ans;
}
//Time Complexity will be O(n+2e)
//Space Complexity will be O(n+n+n) (n for each visited array, stack space, and ans)


//Number Of Provinces
//Tell the number of connected components
//We will use dfs traversal for this
void doDfs(int src,vector<vector<int>> adj,vector<int> &vis){
    vis[src]=1;
    for(auto it:adj[src]){
        if(vis[it]==0) doDfs(it,adj,vis);
    }
}
int numberOfProvinces(int n,vector<vector<int>> adj){
    vector<int> vis(n,0); //Assuming 0 based indexing
    int cnt=0;
    for(int i=0;i<n;i++){
        if(vis[i]==0){
            cnt++;
            doDfs(i,adj,vis);
        }
    }
    return cnt;
}
//Time Complexity will be O(v+2e)
//Space Complexity will be O(n+n) for recursion stack space and visited array


//Number of Islands
//We will be using BFS(DFS can be used as well)
void checkAllNeighbours(int n,int m,vector<vector<int>> &land,vector<vector<bool>> &vis,queue<pair<int,int>> &q,pair<int,int> &p){
    vector<int> dx={-1,-1,-1,0,1,1,1,0};
    vector<int> dy={-1,0,1,1,1,0,-1,-1};

    for(int k=0;k<8;k++){
        int ni=p.first+dx[k];
        int nj=p.second+dy[k];

        if(ni>=0 && ni<n && nj>=0 && nj<m && !vis[ni][nj] && land[ni][nj]==1){
            vis[ni][nj]=true;
            q.push({ni,nj});
        }
    }
}
int numberOfIslands(vector<vector<int>> land){
    int n=land.size();
    int m=land[0].size();
    vector<vector<bool>> vis(n,vector<bool>(m,false));
    queue<pair<int,int>> q;
    int cnt=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(land[i][j]==1 && !vis[i][j]){
                q.push({i,j});
                vis[i][j]=true;
                cnt++;
                while(!q.empty()){
                    pair<int,int> p=q.front();
                    q.pop();
                    checkAllNeighbours(n,m,land,vis,q,p);
                }
            }
        }
    }
    return cnt;
}
//Time Complexity will be O(n2)
//Space Complexity will be O(2n2);


//Flood Fill Algorithm
//First We make a function to check 4 Neighbours
void check4Neighbours(int n,int m,vector<vector<int>> &grid,queue<pair<int,int>> &q,int nCol,int orgCol,pair<int,int> &p){
    vector<int> dx={-1,0,1,0};
    vector<int> dy={0,1,0,-1};
    for(int k=0;k<4;k++){
        int ni=p.first+dx[k];
        int nj=p.second+dy[k];

        if((ni>=0 && ni<n) && (nj>=0 && nj<m) && grid[ni][nj]==orgCol){
            grid[ni][nj]=nCol;
            q.push({ni,nj});
        }
    }
}
void floodFill_bfs(vector<vector<int>> &grid,int x,int y,int nCol){
    int n=grid.size();
    int m=grid[0].size();
    int orgCol=grid[x][y];
    if(orgCol==nCol) return;
    grid[x][y]=nCol;
    queue<pair<int,int>> q;
    q.push({x,y});
    while(!q.empty()){
        pair<int,int> p=q.front();
        q.pop();
        check4Neighbours(n,m,grid,q,nCol,orgCol,p);
    }
}

//We can also solve using dfs
void fxFFDFS(int row,int col,vector<vector<int>> &ans,vector<vector<int>> &image,int orgCol,int nCol,vector<int> delRow,vector<int> delCol){
    ans[row][col]=nCol;
    int n=image.size();
    int m=image[0].size();
    for(int i=0;i<4;i++){
        int nrow=row+delRow[i];
        int ncol=col+delCol[i];
        if(nrow>=0 && nrow<n && ncol>=0 && ncol<m && image[nrow][ncol]==orgCol && ans[nrow][ncol]!=nCol) fxFFDFS(nrow,ncol,ans,image,orgCol,nCol,delRow,delCol);
    }
}

vector<vector<int>> floodFill_dfs(vector<vector<int>>&image,int x,int y,int nCol){
    int orgCol=image[x][y];
    vector<vector<int>> ans=image;
    vector<int> delRow={-1,0,1,0};
    vector<int> delCol={0,1,0,-1};
    fxFFDFS(x,y,ans,image,orgCol,nCol,delRow,delCol);
    return ans;
}
//Time Complexity will be O(N2)
//Space Complexity will be O(2N2)
//In bfs technique , we used n2 for queue, and here we used for recursion stack space



//Rotten Oranges
void rottenOrangesHelper(int n,int m,int &fresh,vector<vector<int>> &oranges,pair<int,int> &p,queue<pair<int,int>> &q){
    vector<int> dx={-1,0,1,0};
    vector<int> dy={0,1,0,-1};

    for(int k=0;k<4;k++){
        int ni=p.first+dx[k];
        int nj=p.second+dy[k];

        if(ni>=0 && ni<n && nj>=0 && nj<m && oranges[ni][nj]==1){
            q.push({ni,nj});
            oranges[ni][nj]=2;
            fresh--;
        }
    }
}
int rottenOranges(vector<vector<int>> &oranges){
    int n=oranges.size();
    if(n==0) return 0;
    int m=oranges[0].size();
    
    //We also need to keep count of fresh oranges, since if no fresh oranges are there, ans will be 0
    int fresh=0;

    //First we store the coordinates of all rotten oranges
    queue<pair<int,int>> q;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(oranges[i][j]==2) q.push({i,j});
            else if(oranges[i][j]==1) fresh++;
        }
    }

    //Nothing to rot
    if(fresh==0) return 0;

    //Now we start rottening of ajdacent oranges
    int time=0;
    while(!q.empty() && fresh>0){
        int size=q.size();
        for(int k=0;k<size;k++){
            pair<int,int> p=q.front();
            q.pop();
            
            //Checking in 4 directions
            rottenOrangesHelper(n,m,fresh,oranges,p,q);
        }
        time++;
    }
    return fresh==0? time:-1;
}
//Time Complexity will be O(4mn+mn)
//Space Complexity will be O(mn)



//Detect a cycle in an undirected graph
//We use BFS first
bool detectCycleInUDG_bfs(int n,vector<vector<int>> adj){
    vector<int> vis(n,0);
    queue<pair<int,int>> q;
    q.push({0,-1});
    vis[0]=1;
    while(!q.empty()){
        pair<int,int> p=q.front();
        q.pop();
        for(auto it:adj[p.first]){
            if(it==p.second) continue;
            if(vis[it]!=0) return true;
            vis[it]=1;
            q.push({it,p.first});
        }
    }
    return false;
}
//Time Complexity will be O(n+2e)
//Space Complexity will be O(n+n) for queue and vis


//Doing the question for graphs which have non connected components
bool detect(int src,vector<vector<int>> adj,vector<int> &vis){
    queue<pair<int,int>> q;
    q.push({src,-1});
    vis[src]=1;
    while(!q.empty()){
        pair<int,int> p=q.front();
        q.pop();
        int parent=p.second;
        int node=p.first;
        for(auto it:adj[node]){
            if(vis[it]==0){
                vis[it]=1;
                q.push({it,node});
            }
            else if(it!=parent) return true;
        }
    }
    return false;
}
bool detectCycleInUDGII_bfs(int n,vector<vector<int>> adj){
    vector<int> vis(n,0);
    for(int i=0;i<n;i++){
        if(vis[i]==0){
            if(detect(i,adj,vis)) return true;
        }
    }
    return false;
}
//Time Complexity will be O(n+2e)
//Space Complexity will be O(n+n) for queue and vis



//Detect Cycle in an undirected graph 
//We use dfs this time
bool detectHelper(int node,int parent,vector<bool> &vis,vector<vector<int>> &adj){
    vis[node]=true;
    for(auto it:adj[node]){
        if(!vis[it]){
            if(detectHelper(it,node,vis,adj)==true) return true;
        }
        else if(it!=parent) return true;
    }
    return false;
}

bool detectCycleInUDG_dfs(int n,vector<vector<int>> adj){
    vector<bool> vis(n,false);
    for(int i=0;i<n;i++){
        if(vis[i]) continue;
        if(detectHelper(i,-1,vis,adj)) return true;
    }
    return false;
}
//Time Complexity will be O(N+2E)
//Space Compexity will be O(2N)



//Distance to Nearest One
void nearestOneHelper(int n,int m,vector<vector<int>> &ans,int dist,queue<pair<pair<int,int>,int>>&q,vector<vector<bool>> &vis,pair<int,int> &p){
    vector<int> dx={0,1,0,-1};
    vector<int> dy={-1,0,1,0};

    for(int k=0;k<4;k++){
        int ni=p.first+dx[k];
        int nj=p.second+dy[k];
        if(ni>=0 && ni<n && nj>=0 && nj<m && !vis[ni][nj]){
            vis[ni][nj]=true;
            q.push({{ni,nj},dist+1}); 
        }
    }
}
vector<vector<int>> distanceToNearestOne(vector<vector<int>> &matrix){
    int n=matrix.size();
    int m=matrix[0].size();
    vector<vector<int>> ans=matrix;
    vector<vector<bool>> vis(n,vector<bool> (m,false));
    queue<pair<pair<int,int>,int>> q;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(matrix[i][j]==1){
                q.push({{i,j},0});
                vis[i][j]=true;
            }
        }
    }

    while(!q.empty()){
        pair<int,int> p=q.front().first;
        int dist=q.front().second;
        q.pop();
        ans[p.first][p.second]=dist;

        //Mark Neighbours
        nearestOneHelper(n,m,ans,dist,q,vis,p);
    }
    return ans;
}
//Time Complexity will be O(NM + 4MN)
//Space Complexity will be O(NM)



//Sorrounded Regions : Replace O with X
//The logic is very simple, first go through all the boundary and mark all O and their connecting O's that are on the boundary as visited
//Now traverse once more and any O you encounter now will be sorrounded by X on all four sides (including its connecting Os), just convert these Os to X
void srHelper(int n,int m,vector<vector<bool>> &vis,vector<vector<char>> &matrix,pair<int,int> &p,stack<pair<int,int>> &st){
    vector<int> dx={-1,0,1,0};
    vector<int> dy={0,-1,0,1};

    for(int k=0;k<4;k++){
        int ni=p.first+dx[k];
        int nj=p.second+dy[k];

        if(ni>=0 && ni<n && nj>=0 && nj<m && !vis[ni][nj] && matrix[ni][nj]=='O'){
            vis[ni][nj]=true;
            st.push({ni,nj});
        }
    }
}
vector<vector<char>> sorroundedRegions(vector<vector<char>> matrix){
    int n=matrix.size();
    int m=matrix[0].size();
    vector<vector<bool>> vis(n,vector<bool>(m,false));
    stack<pair<int,int>> st;

    //Below is the nested loop, but since we need to visit only the border cells, we can optimise it a little(only a little)
    // for(int i=0;i<n;i++){
    //     for(int j=0;j<m;j++){
    //         if((i==0 || i==n-1 || j==0 || j==m-1) && !vis[i][j] && matrix[i][j]=='O'){
    //             vis[i][j]=true;
    //             st.push({i,j});
                
    //             //Mark all the connected O's as visited
    //             while(!st.empty()){
    //                 auto it=st.top();
    //                 st.pop();
    //                 srHelper(n,m,vis,matrix,it,st);
    //             }
    //         }
    //     }
    // }


    for(int i=0;i<n;i++){
        //first col
        if(!vis[i][0] && matrix[i][0]=='O'){
            vis[i][0]=true;
            st.push({i,0});

            while(!st.empty()){
                auto it=st.top();
                st.pop();
                srHelper(n,m,vis,matrix,it,st);
            }
        }

        if(!vis[i][m-1] && matrix[i][m-1]=='O'){
            vis[i][m-1]=true;
            st.push({i,m-1});

            while(!st.empty()){
                auto it=st.top();
                st.pop();
                srHelper(n,m,vis,matrix,it,st);
            }
        }
    }

    for(int j=0;j<m;j++){
        if(!vis[0][j] && matrix[0][j]=='O'){
            vis[0][j]=true;
            st.push({0,j});

            while(!st.empty()){
                auto it=st.top();
                st.pop();
                srHelper(n,m,vis,matrix,it,st);
            }
        }

        if(!vis[n-1][j] && matrix[n-1][j]=='O'){
            vis[n-1][j]=true;
            st.push({n-1,j});

            while(!st.empty()){
                auto it=st.top();
                st.pop();
                srHelper(n,m,vis,matrix,it,st);
            }

        }
    }

    //Now only the leftout zeroes have been marked unvisited
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(!vis[i][j] && matrix[i][j]=='O'){
                vis[i][j]=true;
                st.push({i,j});
                while(!st.empty()){
                    auto it=st.top();
                    matrix[it.first][it.second]='X';
                    st.pop();
                    srHelper(n,m,vis,matrix,it,st);
                }
            }
        }
    }
    return matrix;
}
//Time Complexity will be O(N+M+4MN)
//Space Complexity will be O(MN)




//Number of Enclaves
//First mark all the boundary 1s and the ones connected to them as visited
//Then just count the number of 1s left unvisited
void enclavesHelper(int n,int m,stack<pair<int,int>> &st,vector<vector<bool>> &vis,vector<vector<int>> &matrix){
    vector<int> dx={0,1,0,-1};
    vector<int> dy={-1,0,1,0};
    while(!st.empty()){
        pair<int,int> p=st.top();
        st.pop();

        for(int k=0;k<4;k++){
            int ni=p.first+dx[k];
            int nj=p.second+dy[k];

            if(ni>=0 && ni<n && nj>=0 && nj<m && !vis[ni][nj] && matrix[ni][nj]==1){
                vis[ni][nj]=true;
                st.push({ni,nj});
            }
        }

    }
}
int numberOfEnclaves(vector<vector<int>> &matrix){
    int n=matrix.size();
    int m=matrix[0].size();
    vector<vector<bool>> vis(n,vector<bool> (m,false));
    stack<pair<int,int>> st;
    for(int i=0;i<n;i++){
        int j=0;
        if(vis[i][j]) continue;
        if(matrix[i][j]){
            st.push({i,j});
            vis[i][j]=true;
            enclavesHelper(n,m,st,vis,matrix);
        }

        j=m-1;
        if(vis[i][j]) continue;
        if(matrix[i][j]){
            st.push({i,j});
            vis[i][j]=true;
            enclavesHelper(n,m,st,vis,matrix);
        }
    }

    for(int j=1;j<m-1;j++){
        int i=0;
        if(vis[i][j]) continue;
        if(matrix[i][j]){
            st.push({i,j});
            vis[i][j]=true;
            enclavesHelper(n,m,st,vis,matrix);
        }

        i=n-1;
        if(vis[i][j]) continue;
        if(matrix[i][j]){
            st.push({i,j});
            vis[i][j]=true;
            enclavesHelper(n,m,st,vis,matrix);
        }
    }

    //Now we just count the number of remaining 1s
    int cnt=0;
    for(int i=1;i<n-1;i++){
        for(int j=1;j<m-1;j++){
            if(!vis[i][j] && matrix[i][j]==1) cnt++;
        }
    }
    return cnt;
}
//Time Complexity will be O(4MN)
//Space Complexity will be O(MN)




//Number Of Distinct Islands
//Logic is to store the shape somehow in sets, then set.size() will give the answer
/*
Consider the matrix:
{{1,1,0,1,1}
 {1,0,0,0,0}
 {0,0,0,1,1}
 {1,1,0,1,0}
}
 here if you see the top left and bottom right islands their coordinates will be {(0,0),(0,1),(1,0)} and {(2,3),(2,4),(3,3)}
 now assume the intersection point as the base, then subtract the base coordinates from all the coordinates, for eg the first set, the base is (0,0)
 therefore subtracting all coordinates : the first set becomes : {(0,0),(0,1),(1,0)}. for second set, the base is (2,3), doing same operation the 
 second set also becomes {(0,0),(0,1),(1,0)}, see, and observe that they are identical, and therefore set data structure will only store one of them
*/
void distIslandsHelper(int row,int col,int n,int m,vector<vector<int>> &grid,vector<vector<int>> &vis,vector<pair<int,int>> &vec,int row0,int col0){
    vis[row][col]=1;
    vec.push_back({row-row0,col-col0});
    vector<int> dx={-1,0,1,0};
    vector<int> dy={0,-1,0,1};
    for(int k=0;k<4;k++){
        int ni=row+dx[k];
        int nj=col+dy[k];
        if(ni>=0 && ni<n && nj>=0 && nj<m && !vis[ni][nj] && grid[ni][nj]==1){
            distIslandsHelper(ni,nj,n,m,grid,vis,vec,row0,col0);
        }
    }

}
int countDistIslands(vector<vector<int>> &grid){
    int n=grid.size();
    int m=grid[0].size();
    vector<vector<int>> vis(n,vector<int> (m,0));
    set<vector<pair<int,int>>> st;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(!vis[i][j] && grid[i][j]==1){
                vector<pair<int,int>> vec;
                distIslandsHelper(i,j,n,m,grid,vis,vec,i,j);
                st.insert(vec);
            }
        }
    }
    return st.size();
}
//Bipartite Graph
//Logic : First of all if the graph doesn't have a cycle, it is always bipartite
//Then incase if it has a cycle then for it to be bipartite, the cycle's length must be even
//If the length of cycle is odd, then it is not a bipartite graph

//This however is the wrong logic, for eg imagine this case:
/*
 0——1——2
   \ | /
     3——4——5
        \  /
         6
The above concept will fail here
Therefore coloring the graph is the best way
*/

//Brute Force
//We will at first colour all the nodes, then in the second traversal check for condition
void colourGraph(int n,vector<vector<int>> &adj,unordered_map<int,bool> &mp){
    queue<int> q;
    vector<bool> vis(n,false);
    for(int i=0;i<n;i++){
        if(vis[i]) continue;
        q.push(i);
        vis[i]=true;
        bool flag=true;
        mp[i]=flag;
        while(!q.empty()){
            int node=q.front();
            q.pop();
            flag=mp[node];
            for(auto it:adj[node]){
                if(!vis[it]){
                    vis[it]=true;
                    if(mp.find(it)==mp.end()) mp[it]=(!flag);
                    q.push(it);
                }
            }
        }
    }
}

//Now we check for bipartite condition
bool checkForColour(int n,vector<vector<int>> &adj,unordered_map<int,bool> &mp){
    for(int i=0;i<n;i++){
        bool currColour=mp[i];
        for(auto it:adj[i]){
            int nextColour=mp[it];
            if(nextColour==currColour) return false;
        }
    }
    return true;
}
bool bipartiteGraph_bfs_brute(int n,vector<vector<int>> &adj){
    //We first colour the graph
    unordered_map<int,bool> mp;
    colourGraph(n,adj,mp);
    return checkForColour(n,adj,mp);
}
//Although this code is optimal, we can half the time by using a single traversal
//Also we can avoid using the map and just mark colours in the queue only

//Optimal Solution
bool bipartiteGraph_bfs(int n,vector<vector<int>> &adj){
    vector<int> vis(n,-1);
    queue<int> q;
    for(int i=0;i<n;i++){
        if(vis[i]!=-1) continue;
        q.push(i);
        vis[i]=1;
        while(!q.empty()){
            int node=q.front();
            int col=vis[node];
            q.pop();
            for(auto it:adj[node]){
                if(vis[it]==-1){
                    vis[it]=!(col);
                    q.push(it);
                }
                else if(vis[it]==col) return false;
            }
        } 
    }
    return true;
}


//Bipartite Graph : DFS
bool bipartite_dfs_helper(int i,vector<int> &vis,stack<int> &st,vector<vector<int>> &adj){
    vis[i]=0;
    st.push(i);
    while(!st.empty()){
        int node=st.top();
        st.pop();
        int col=vis[node];
        for(auto it:adj[node]){
            if(vis[it]==-1){
                vis[it]=!col;
                st.push(it);
            }
            else if(vis[it]==col) return false;
        }
    }
    return true;
}
bool bipartiteGraph_dfs(int n,vector<vector<int>> &adj){
    vector<int> vis(n,-1);
    stack<int> st;
    for(int i=0;i<n;i++){
        if(vis[i]!=-1) continue;
        if(!bipartite_dfs_helper(i,vis,st,adj)) return false;
    }
    return true;
}
//Time Complexity will be O(V+2E)
//Space Complexity will be O(2V)(visited array and stack space)



//M-Coloring Graph
//Similar to bipartite graph problem, but here we have to colour with m colours, such that no two adjacent cells have the same colour
//This question belongs to recursion, but we have also included it here, since graphs are involved
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



//Detect Cycle in a directed graph : DFS
bool dcidg(int node,vector<bool> &vis,vector<bool> &pathVis,vector<vector<int>> &adj){
    vis[node]=true;
    pathVis[node]=true;
    for(auto it:adj[node]){
        if(!vis[it]){
            if(dcidg(it,vis,pathVis,adj)) return true;
        }
        else if(pathVis[it]) return true;
    }
    pathVis[node]=false;
    return false;
}
bool detectCycleInDG_brute_dfs(int n,vector<vector<int>> &adj){
    vector<bool> vis(n,0);
    vector<bool> pathVis(n,0);
    for(int i=0;i<n;i++){
        if(vis[i]) continue;
        if(dcidg(i,vis,pathVis,adj)) return true;
    }
    return false;
}
//Time Complexity will be O(V+E)(in directed graph, every node has a single edge, therefore only v+e and not v+2e)
//Space Complexity will be O(2N)



//Eventual Safe States
//Any nodes that is not a part of cycle and that does not leads to a cycle, is safe node
bool safeStatesHelper(int node,vector<vector<int>> &adj,vector<int> &vis,vector<int> &pathVis,vector<int> &check){
    vis[node]=1;
    pathVis[node]=1;
    for(auto it:adj[node]){
        if(!vis[it]){
            if(safeStatesHelper(it,adj,vis,pathVis,check)){
                check[node]=0;
                return true;
            }
        }
        else if(pathVis[it]){
            check[node]=0;
            return true;
        }
    }
    check[node]=1;
    pathVis[node]=0;
    return false;
}
vector<int> safeStates(int n,vector<vector<int>> &adj){
    vector<int> vis(n,0);
    vector<int> pathVis(n,0);
    vector<int> check(n,0);
    vector<int> ans;
    for(int i=0;i<n;i++){
        if(vis[i]) continue;
        safeStatesHelper(i,adj,vis,pathVis,check);
    }
    for(int i=0;i<n;i++){
        if(check[i]==1) ans.push_back(i);
    }
    return ans;
}
//Time Compelexity will be O(V+2E)
//Space Compelexity will be O(2V)



//Topological Sort
//It only exists in DAG(Directed Acyclic Graphs)
void topoSortHelper(int node,vector<vector<int>> &adj,vector<bool> &vis,stack<int> &st){
    vis[node]=true;
    for(auto it:adj[node]){
        if(vis[it]) continue;
        topoSortHelper(it,adj,vis,st);
    }
    st.push(node);
}
vector<int> topoSort(int n,vector<vector<int>> &adj){
    vector<bool> vis(n,0);
    stack<int> st;
    vector<int> ans;
    for(int i=0;i<n;i++){
        if(vis[i]) continue;
        topoSortHelper(i,adj,vis,st);
    }

    while(!st.empty()){
        ans.push_back(st.top());
        st.pop();
    }
    return ans;
}


vector<int> kahnAlgorithm(int n,vector<vector<int>> &adj){
    vector<int> inDeg(n,0);
    for(int i=0;i<n;i++){
        for(auto it:adj[i]) inDeg[it]++;
    }

    queue<int> q;
    for(int i=0;i<n;i++){
        if(inDeg[i]==0) q.push(i);
    }
    vector<int> ans;
    while(!q.empty()){
        int node=q.front();
        q.pop();
        ans.push_back(node);
        for(auto it:adj[node]){
            inDeg[it]--;
            if(inDeg[it]==0) q.push(it);
        }
    }
    return ans;
}
//Time Complexity will be O(V+E)
//Space Complexity will be O(2V)



//Detect Cycle in a Directed Graph : BFS
bool detectCycleInDG_bfs(int n,vector<vector<int>> &adj){
    //We use kahn algorithm to get the topo sort
    //If topo sort size was less than n that means topo sort wasn't completed fully, reason ? a cycle existed(since the graph is directed)
    vector<int> topoSort=kahnAlgorithm(n,adj);
    if(topoSort.size()<n) return true;
    return false;
}
//Time and Space Complexities will be same as kahn Algorithm
//Time Complexity will be O(V+E)
//Space Complexity will be O(2V)



//Course Schedule I
//Check if courses can be performed or not
//Just check if a cycle exists or not
bool courseScheduleI(int n,vector<pair<int,int>> schedule){
    vector<vector<int>> adj(n);
    for(auto it:schedule){
        adj[it.first].push_back(it.second);
    }
    return (!(detectCycleInDG_bfs(n,adj)));
}
//Time Complexity will be O(V+E+V)
//Space Complexity will be O(2V)



//Course Schedule II
//Here you have to return the order of doing tasks as well
//Incase the tasks can't be performed, return an empty array
vector<int> courseScheduleII(int n,vector<pair<int,int>> schedule){
    vector<vector<int>> adj(n);
    for(auto it:schedule){
        adj[it.first].push_back(it.second);
    }
    vector<int> topo=kahnAlgorithm(n,adj);
    if(topo.size()==n) return topo;
    vector<int> ans;
    return ans;
}
//Time Complexity will be O(V+E+V)
//Space Complexity will be O(2V)


//Find Eventual Safe States 
//This time we will use bfs, and topological sort
//The intuition is this
//First reverse all the links of the directed graph
//After doing this the terminal node will have indegree 0(observe)
//Now apply the kahn's algorithm, pushing nodes with indeg 0 into queue, and when the queue is empty, those will be your safe states
//Sort the answer array since the nodes we get at the end may be randomly arranged
//First we create a function which reverses the links of a directed graph
vector<vector<int>> revLinks(vector<vector<int>> &adj){
    int n=adj.size();
    vector<vector<int>> revAdj(n);
    for(int i=0;i<n;i++){
        for(auto it:adj[i]) revAdj[it].push_back(i);
    }
    return revAdj;
}
//The nested loop runs for V+E times
//V is vertex which is same as n , nodes
vector<int> eventualSafeStates(int n,vector<vector<int>> &adj){
    vector<vector<int>> revAdj=revLinks(adj);

    //An indeg array stores the indeg(for reversed graph)
    vector<int> inDeg(n,0);
    //This also uses a time of O(N)

    //Now we loop through to set the indeg for various nodes
    //This block of code could be written in the reversing Links code so it will beneficial
    //But we have written it here since we wanted to conserve revLinks function only to reverse links
    //Otherwise it is better that we set indeg when we are traversing to reverse the links
    for(int i=0;i<n;i++){
        for(auto it:revAdj[i]) inDeg[it]++;
    }
    //This runs for O(V+E)
    queue<int> q;

    //Another loop to find out the nodes having indeg 0
    //We will push those nodes into the queue
    for(int i=0;i<n;i++){
        if(inDeg[i]==0) q.push(i);
    }
    //This runs for O(N)

    vector<int> ans;
    while(!q.empty()){
        int node=q.front();
        q.pop();
        ans.push_back(node);
        for(auto it:revAdj[node]){
            inDeg[it]--;
            if(inDeg[it]==0) q.push(it);
        }
    }
    //This kahn algorithm runs for O(V+E)

    sort(ans.begin(),ans.end());
    //The sort function runs for about O(NlogN)
    return ans;
}
//The helper function takes time V+E
//This function takes time of V+(V+E)+V+(V+E)+(VLogV)
//Space is used for revAdj (V+E) and ans(V) and inDeg(V) and queue(V)
//Time Complexity will be O(4V+2E+VlogV)
//Space Complexity will be O(4V+E)


//Alien Dictionary
//There can be many order of words, we can return any
//The problem is meaningless if there is a cyclic dependency
//Consider the words : abc, bca, cab
string alienDictionary(vector<string> &dict,int n){
    vector<vector<int>> adj(n);
    for(int i=1;i<dict.size();i++){
        string s1=dict[i-1];
        string s2=dict[i];

        int len=min(s1.size(),s2.size());
        //Check for incomplete dictionary
        if(s1.size()>s2.size() && s1.substr(0,len)==s2) return "";
        for(int j=0;j<len;j++){
            if(s1[j]!=s2[j]){
                adj[s1[j]-'a'].push_back(s2[j]-'a');
                break;
            }
        }
    }

    vector<int> topo=topoSort(n,adj);
    string ans="";
    for(int i=0;i<topo.size();i++){
        ans+=(char(topo[i]+'a'));
    }
    return ans;
}


//Shortest Path I
//Given a source node, find the shortest path to every other node
void dfs_sp(int node,vector<bool> &vis,stack<int> &st,vector<vector<pair<int,int>>> &adj){
    vis[node]=true;
    for(auto it:adj[node]){
        if(!vis[it.first]) dfs_sp(it.first,vis,st,adj);
    }
    st.push(node);
}
vector<int> shortestPathI(int n,int src,vector<vector<int>> &edges){
    vector<int> dist(n,1e9);
    stack<int> st;
    vector<vector<pair<int,int>>> adj(n);
    for(auto it:edges){
        int u=it[0];
        int v=it[1];
        int wt=it[2];
        adj[u].push_back({v,wt});
    }

    vector<bool> vis(n,0);
    for(int i=0;i<n;i++){
        if(vis[i]) continue;
        dfs_sp(i,vis,st,adj);
    }

    dist[src]=0;

    while(!st.empty()){
        int node=st.top();
        st.pop();
        if(dist[node]==1e9) continue;
        for(auto it:adj[node]){
            int adjNode=it.first;
            int newDist=it.second+dist[node];
            if(newDist<dist[adjNode]) dist[adjNode]=newDist;
        }
    }
    //This in total will run for n+m times(n is the number of nodes and m is the number of edges)

    return dist;
}
//Time Complexity will be O(n+m)
//Space Complexity will be O(n+m)   


//Shortest Path
//Given an undirected graph with unit edge weights, and a source, find the smallest distance to all the nodes from that source
//In this question, we assume that the graph won't have disconnected components, since reaching them would be impossible
//In case we come across a question that has disconnected components, just mark them with INT_MAX
vector<int> shortestPathII_brute(int n,int src,vector<vector<int>> &adj){
    vector<int> vis(n,0);

    queue<pair<int,int>> q;
    q.push({src,0});
    vis[src]=true;
    vector<int> ans(n,0);
    while(!q.empty()){
        int node=q.front().first;
        int dist=q.front().second;
        q.pop();
        for(auto it:adj[node]){
            if(vis[it]) continue;
            vis[it]=true;
            q.push({it,dist+1});
        }
        ans[node]=dist;
    }
    return ans;
}

//Optimal : Using the vis array to mark the distances as well
//Also let us solve it when instead of giving us the adjacency list, they have given us the edges
vector<int> shortestPathII(int n,int m,int src,vector<vector<int>> &edges){
    vector<vector<int>> adj(n);
    for(auto it:edges){
        adj[it[0]].push_back(it[1]);
        adj[it[1]].push_back(it[0]);
    }
    vector<int> dist(n,1e9);
    dist[src]=0;
    queue<int> q;
    q.push(src);
    while(!q.empty()){
        int node=q.front();
        q.pop();
        for(auto it:adj[node]){
            if(dist[node]+1<dist[it]){
                dist[it]=1+dist[node];
                q.push(it);
            }
        }
    }

    vector<int> ans(n,-1);
    for(int i=0;i<ans.size();i++){
        if(dist[i]!=1e9) ans[i]=dist[i];
    }
    return ans;
}



//Word Ladder I
void findNextWord(string word,int dist,unordered_set<string> &st,queue<pair<string,int>> &q){
    int n=word.size();
    for(int i=0;i<n;i++){
        for(char c='a';c<='z';c++){
            char orgChar=word[i];
            if(orgChar==c) continue;
            word[i]=c;
            if(st.find(word)!=st.end()){
                q.push({word,dist+1});
                st.erase(word);
            }
            word[i]=orgChar;
        }
    }
}
int wordLadderI(string startWord, string endWord, vector<string> &wordList){
    int n=wordList.size();

    //We would need to check if a particular word exists in the wordList, therefore to search efficiently we can use unordered_set
    unordered_set<string> st(wordList.begin(),wordList.end());
    st.erase(startWord);
    queue<pair<string,int>> q;
    q.push({startWord,1});
    while(!q.empty()){
        string word=q.front().first;
        int dist=q.front().second;
        q.pop();
        if(word==endWord) return dist;
        findNextWord(word,dist,st,q);
    }
    return 0;
}
//Each word will go into the queue once and it will done operations in the findNextWord in 26*l(length of word) times
//Set use space of n*l, and queue uses space of 2*n(in worst case where it holds all words) and temporary words are of size l(say)
//Time Complexity will be O(26*n*l)
//Space Complexity will be O(n*l+2*n+l)


//Word Ladder II
//We need to also return the chain of words of transformation
//This method discussed below is already quite optimised, and people won't bother asking a more optimised version
//Therefore this much is more than enough in interviews
//The only reason this is labelled as not the most optimal one, is because a cp based solution exists that is slightly better
void ladderIIHelper_brute(string &word,unordered_set<string> &st,queue<vector<string>> &q,vector<string> &temp,unordered_set<string> &elToDel){
    int n=word.size();
    for(int i=0;i<n;i++){
        char orgChar=word[i];
        for(char c='a';c<='z';c++){
            if(c==orgChar) continue;
            word[i]=c;
            if(st.find(word)!=st.end()){
                temp.push_back(word);
                q.push(temp);
                temp.pop_back();
                elToDel.insert(word);
            }
            word[i]=orgChar;
        }
    }
}

vector<vector<string>> wordLadderII_brute(string &startWord,string &endWord,vector<string> &wordList){

    //We would need to check if a particular word exists in the wordList, therefore to search efficiently we can use unordered_set
    unordered_set<string> st(wordList.begin(),wordList.end());
    if(!st.count(endWord)) return {};

    st.erase(startWord);

    queue<vector<string>> q;
    q.push({startWord});

    vector<vector<string>> ans;
    bool found=false;
    while(!q.empty() && !found){
        int s=q.size();
        unordered_set<string> elToDel;
        for(int i=0;i<s;i++){
            vector<string> temp=q.front();
            q.pop();
            string lastWord=temp.back();
            if(lastWord==endWord){
                ans.push_back(temp);
                found=true;
                continue;
            }
            ladderIIHelper_brute(lastWord,st,q,temp,elToDel);
        }
        for(auto it:elToDel) st.erase(it);
    }
    return ans;
}
//Predicting Time Complexity of this solution is quite difficult
//Space is used by queue, set, and eltoDel set as well

//Optimal Method
//This is cp based and uses a very simple intuition
//The logic is suppose you have two points A and B and you have to reach from A to B.(Draw a diagram alongwith explanation to understand clearly)
//Assume at start you have many ways that spread out, say path p1,p2... pn
//However over the course of journey, paths keep getting removed or left, since they weren't correct
//Say only a few paths reach point B, let's say only p2 and p7
//Now think for yourself if you had looked and started from point B, wouldn't it had been a lot easier to draw the paths
//Since this time you knew which paths led you to point A for sure
//It would have saved a lot of time
//Therefore in this method we will use backtracking
void backTrackingWord(string word,vector<string> &seq,string &startWord,vector<vector<string>> &ans,unordered_map<string,int> &mp){
    int n=word.size();
    if(word==startWord){
        reverse(seq.begin(),seq.end());
        ans.push_back(seq);
        reverse(seq.begin(),seq.end());
        return;
    }
    int steps=mp[word];
    for(int i=0;i<n;i++){
        char orgChar=word[i];
        for(char c='a';c<='z';c++){
            if(orgChar==c) continue;
            word[i]=c;
            if(mp.find(word)!=mp.end() && (mp[word]+1)==steps){
                seq.push_back(word);
                backTrackingWord(word,seq,startWord,ans,mp);
                seq.pop_back();
            }
        }
        word[i]=orgChar;
    }
}
vector<vector<string>> wordLadderII(string &startWord,string &endWord,vector<string> &wordList){
    unordered_map<string,int> mp;
    unordered_set<string> st(wordList.begin(),wordList.end());
    queue<string> q;
    q.push(startWord);
    st.erase(startWord);
    mp[startWord]=1;
    int s=startWord.size();
    while(!q.empty()){
        string word=q.front();
        q.pop();
        int steps=mp[word];
        if(word==endWord) break;
        for(int i=0;i<s;i++){
            char orgChar=word[i];
            for(char c='a';c<='z';c++){
                if(orgChar==c) continue;
                word[i]=c;
                if(st.find(word)!=st.end()){
                    q.push(word);
                    st.erase(word);
                    mp[word]=steps+1;
                }
            }
            word[i]=orgChar;
        }
    }

    //Now we do backtracking
    vector<vector<string>> ans;
    if(mp.find(endWord)==mp.end()) return {};
    vector<string> seq={endWord};
    backTrackingWord(endWord,seq,startWord,ans,mp);
    return ans;
}
//Time Complexity is again a bit too complex to be calculated in this case



//Dijkstra's Algorithm
//Dijktra's Algorithm is not applicable to any graph that has negative edge wt, since in code this will result in an infinite loop, try considering a graph like 1->2 with edge wt of -2 and src as 1
//Now try to implement dijktra's algorithm to find out. Practically if we are paid to go somewhere(negative wt), then we would just keep traversing that path for infinite money.

//Dijkstra's Algorithm using queues
//This is just a brute force algorithm as it uses the most time
vector<int> dijkstrasAlgorithm_brute(int n,vector<vector<pair<int,int>>> &adj,int src){
    vector<int> dist(n,1e9);
    queue<pair<int,int>> q;
    dist[src]=0;
    q.push({0,src});
    while(!q.empty()){
        int node=q.front().second;
        int dis=q.front().first;
        q.pop();
        for(auto it:adj[node]){
            int adjNode=it.first;
            int newDist=it.second+dis;
            if(newDist<dist[adjNode]){
                dist[adjNode]=newDist;
                q.push({newDist,adjNode});
            }
        }
    }
    return dist;
}
//The outer loop will run for V times(or may be 2V or 3V times) and the inner loop will run at most E times
//The Space is used by queue only, which can store all edges in worst case
//Time Complexity will be O(VE)
//Space Complexity will be O(E)

//In brute force we travel by all paths, however we can reduce that time, if we take the smaller path first, this is the idea behind dijkstra's algorithm
//Dijktra's Algorithm using priority queue
vector<int> dijkstrasAlgorithmI(int n,vector<vector<pair<int,int>>> &adj,int src){
    priority_queue<pair<int,int>,vector<pair<int,int>>, greater<pair<int,int>>> pq;
    vector<int> dist(n,1e9);
    dist[src]=0;
    pq.push({0,src});
    while(!pq.empty()){
        int dis=pq.top().first;
        int node=pq.top().second;
        pq.pop();
        for(auto it:adj[node]){
            int adjNode=it.first;
            int edgeWt=it.second;
            if(dis+edgeWt<dist[adjNode]){
                dist[adjNode]=dis+edgeWt;
                pq.push({dis+edgeWt,adjNode});
            }
        }
    }
    return dist;
}
//We know each node can enter the priority queue several times, say if total of 2V times, but that won't matter in time complexity so we can say time taken for this part is still V
//The pop function in priority queue takes log(heap_size) time
//The inner for loop in the worst case can run for number of edges of a node, which will be equal to ne(say)
//In the worst case, which is the case for the densest graph(assuming no self loops) ne=V-1
//Inside the for function, there is a push function which will take log(heap_size) time again
//Therefore total time taken will be V*(log(heap_size)+ne*(log(heap_size))) ==> V*(log(heap_size)*(ne+1)), now using ne=V-1, we get
//Time equals V*V*log(heap_size)
//Heap size can be in worse case equal to (n-1)+(n-1)+(n-1) ... => n2 in worst case(as discussed before)
//In most densest graph, number of edges = V2, therefore this gives a final shape to our time complexity
//Time Complexity will be O(ElogV)
//Space Complexity will be O(2E)

//Dijstra's Algorithm using set
//A set stores unique value and the smallest values at the top
//Since a set can erase arbitrary elements, something which the priority_queue couldn't do, therefore we can erase element instead of waiting for them to be traversed
//For bigger graphs, both method I and method II almost take same time
vector<int> dijkstrasAlgorithmII(int n,vector<vector<pair<int,int>>> &adj,int src){
    vector<int> dist(n,1e9);
    dist[src]=0;
    set<pair<int,int>> st;
    st.insert({0,src});
    while(!st.empty()){
        auto it=*(st.begin());
        int dis=it.first;
        int node=it.second;
        st.erase(st.begin());
        for(auto edge:adj[node]){
            int adjNode=edge.first;
            int edgeWt=edge.second;
            int newDist=edgeWt+dis;
            if(newDist<dist[adjNode]){
                if(dist[adjNode]!=1e9) st.erase({dist[adjNode],adjNode});
                dist[adjNode]=newDist;
                st.insert({dist[adjNode],adjNode});
            }
        }
    }
    return dist;
}
//Each operation in a set costs logV
//This time we are sure that a node can't be stored multiple times, therefore space taken will be V, that is we may end up storing all nodes once
//Time Complexity will be O((V+E)logV)
//Space Complexity wil be O(2V)


//Shortest Path in Weighted Graph
//Use Dijkstra with slight modification, since in this also we have to find the shortest path, but we have to give the path and not the distance as we did in dijkstra
//One thing to note here is that we this time have a 1 indexed graph 
vector<int> shortestPathIII(int n,vector<vector<int>> &edges,int src,int target){
    if(src==target) return {src};
    vector<vector<pair<int,int>>> adj(n+1);
    for(auto it:edges){
        int u=it[0];
        int v=it[1];
        int wt=it[2];
        adj[u].push_back({v,wt});
        adj[v].push_back({u,wt});
    }
    vector<int> dist(n+1,1e9);
    vector<int> parent(n+1);
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
    iota(parent.begin(),parent.end(),0);
    pq.push({0,src});
    dist[src]=0;
    while(!pq.empty()){
        int node=pq.top().second;
        int dis=pq.top().first;
        pq.pop();
        if(dis>dist[node]) continue;
        for(auto it:adj[node]){
            int adjNode=it.first;
            int edgeWt=it.second;
            int newDist=edgeWt+dis;
            if(newDist<dist[adjNode]){
                dist[adjNode]=newDist;
                pq.push({newDist,adjNode});
                parent[adjNode]=node;
            }
        }
    }
    if(dist[target]==1e9) return {-1};

    vector<int> ans;
    ans.push_back(target);
    while(parent[target]!=target){
        ans.push_back(parent[target]);
        target=parent[target];
    }
    reverse(ans.begin(),ans.end());
    return ans;
}
//Time taken will be equal to dijkstra's algorithm + extra due to path formation which can be at max consisting of all nodes in a linear graph
//Space will be used by adjacency list (V) , distance array (V), parent array (V), priority queue (V)
//Time Complexity will be O(ElogV+V)
//Space Complexity will be O(V)


//Shortest Path in a Binary Maze
//We can't move through a cell having 0
//Movement is only allowed in four directions, up, down, left and right
int binaryMaze(vector<vector<int>> &mat,pair<int,int> &src,pair<int,int> target){
    int n=mat.size();
    int m=mat[0].size();
    int i=src.first;
    int j=src.second;
    vector<vector<int>> dist(n,vector<int> (m,1e9));

    //Many people store distance as well, but since we have a distance array, we don't need to
    queue<pair<int,int>> q;
    q.push({i,j});
    dist[i][j]=0;
    vector<int> dx={0,1,0,-1};
    vector<int> dy={-1,0,1,0};
    while(!q.empty()){
        int x=q.front().first;
        int y=q.front().second;
        q.pop();
        if(x==target.first && y==target.second) return dist[x][y];
        for(int k=0;k<4;k++){
            int ni=x+dx[k];
            int nj=y+dy[k];
            if(ni>=0 && ni<n && nj>=0 && nj<m && dist[ni][nj]>dist[x][y]+1 && mat[ni][nj]==1){
                dist[ni][nj]=dist[x][y]+1;
                q.push({ni,nj});
            }
        }
    }
    return -1;
}


//Path with minimum effort
int pathWithMinEffort(vector<vector<int>> &mat){
    int n=mat.size();
    int m=mat[0].size();
    vector<vector<int>> dist(n,vector<int>(m,1e9));
    dist[0][0]=0;
    priority_queue<pair<int,pair<int,int>>, vector<pair<int,pair<int,int>>>, greater<pair<int,pair<int,int>>>> pq;
    pq.push({0,{0,0}});

    //Using arr to traverse neighbours
    vector<int> dx={-1,0,1,0};
    vector<int> dy={0,1,0,-1};

    while(!pq.empty()){
        int effort=pq.top().first;
        int i=pq.top().second.first;
        int j=pq.top().second.second;
        pq.pop();

        //For this particular problem, when we take out the destination from the pq, it will be the answer
        //Since any value taken out later on from the priority queue, will have a higher or at least equal diff with this so no point in moving forward
        if(i==n-1 && j==m-1) return effort;
        if(effort>dist[i][j]) continue;
        for(int k=0;k<4;k++){
            int ni=i+dx[k];
            int nj=j+dy[k];
            if(ni>=0 && ni<n && nj>=0 && nj<m){
                int heightDiff=abs(mat[i][j]-mat[ni][nj]);
                int newEffort=max(heightDiff,dist[i][j]);
                if(newEffort<dist[ni][nj]){
                    dist[ni][nj]=newEffort;
                    pq.push({newEffort,{ni,nj}});
                }
            }
        }
    }
    return dist[n-1][m-1];
}
//Time taken by dijkstra is ElogV as discussed before
//So time taken in this code will be around as well
//Edges in a grid are equal to n*m*4(4 neighbours)
//So E=4mn and V=mn
//Space will be used by priority queue(can hold 2 or three times the nodes at max) and dist table
//Time Complexity will be O(4mnlogmn)
//Space Complexity will be O(2mn)


//Cheapest Flights within K stops
//Modified Dijkstra
int cheapestFlight(int n,int src,int target,int k,vector<vector<int>> &flights){
    vector<vector<pair<int,int>>> adj(n);
    for(auto it:flights){
        int u=it[0];
        int v=it[1];
        int cost=it[2];
        adj[u].push_back({v,cost});
    }

    vector<int> cost(n,1e9);

    //Queue will store {stops,{node,distance}}
    queue<pair<int,pair<int,int>>> q;
    q.push({0,{src,0}});
    cost[src]=0;
    while(!q.empty()){
        auto it=q.front();
        q.pop();
        int stops=it.first;
        int node=it.second.first;
        int dist=it.second.second;

        if(stops>k) continue;
        for(auto it:adj[node]){
            int adjNode=it.first;
            int wt=it.second;
            if(dist+wt<cost[adjNode] && stops<=k){
                cost[adjNode]=dist+wt;
                q.push({stops+1,{adjNode,cost[adjNode]}});
            }
        }
    }

    if(cost[target]==1e9) return -1;
    return cost[target];
}


//Minimum Multiplications to reach end
int minMultiplicationsToReachEnd(int start,int end,vector<int> &arr){
    int n=arr.size();
    int modulo=1e5;
    queue<pair<int,int>> q;
    q.push({0,start});
    vector<int> dist(100000,1e9);
    dist[start]=0;
    while(!q.empty()){
        int node=q.front().second;
        int steps=q.front().first;
        q.pop();
        for(int i=0;i<n;i++){
            int num=(arr[i]*node)%modulo;
            if(steps+1<dist[num]){
                dist[num]=steps+1;
                if(num==end) return dist[num];
                q.push({dist[num],num});
            }
        }
    }
    return -1;
}
//Time Taken at max can be 1e5 since that many nodes will be taken out in the worst case
//Same for space complexity as the queue will store that many nodes
//However remember that is almost impossible, since the probability that you can generate all the numbers from 1 to 1e5 by just multiplcation from numbers given from arr
//That is next to impossible
//Therefore calcuation of time and space compelexity in this problem is not something we can do
//At max as we said, hypothetically, it can go up to 1e5 at max, space and time both


//Number of ways to arrive at destination
//Only count the ways which take the shortest time
int waysToArriveAtDest(int src,int tar,vector<vector<pair<int,int>>> &adj){
    int n=adj.size();
    vector<int> ways(n,0);
    vector<int> dist(n,1e9);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push({0,src});
    ways[src]=1;
    dist[src]=0;
    
    while(!pq.empty()){
        int node=pq.top().second;
        int dis=pq.top().first;
        pq.pop();
        if(dis>dist[node]) continue;
        for(auto it:adj[node]){
            int newDist=it.second+dis;
            int adjNode=it.first;
            if(newDist==dist[adjNode]) ways[adjNode]+=ways[node];
            else if(newDist<dist[adjNode]){
                ways[adjNode]=ways[node];
                dist[adjNode]=newDist;
                pq.push({newDist,adjNode});
            }
        }
    }
    if(dist[tar]==1e9) return -1;
    return ways[tar];
}
//Time Complexity for dijkstra is ElogV
//Space is occupied by the ways(V) and dist(V) and pq(E)
//Time Complexity will be O((E+V)logV)
//Space Complexity will be O(E+V)



//Bellman Ford Algorithm
//This is also used to find the shortest path, but it works where dijkstra's algorithm fails
//This can be used even when the edgeWts are negative
//This however works only for directed graphs. 
//Incase we want it for undirected graph, just convert the graph, for eg, 1->2 is a directed graph, convert this into 1 <=> 2, that is edge from 1 to 2 and from 2 to 1
//This will make the graph undirected in somesense, then apply Bellman Ford
//The edges in this case can be given in any order, they will be as (u,v,wt) that is edge from u->v and with a weight of wt
//First relax all the edges (n-1) times sequentially 
//Relaxing the edge means if dist[u]+wt<dist[v] then set dist[v]=dist[u]+wt and we have to do this n-1 times for each edge 
//Also return an array of -1 if there exists a negative cycle
//This method takes quadratic time but it works where dijkstra fails, therefore if it is known that all edge weights are positive then always go for dijkstra
vector<int> bellmanFordAlgorithm(int n,vector<vector<int>> &edges,int src){
    vector<int> dist(n,1e9);
    dist[src]=0;
    for(int i=0;i<n-1;i++){
        for(auto it:edges){
            int u=it[0];
            int v=it[1];
            int wt=it[2];
            if(dist[u]!=1e9 && dist[u]+wt<dist[v]) dist[v]=dist[u]+wt;
        }
    }
    
    //We also do an nth relaxation to check for a negative cycle
    //If in the nth cycle if any element in the distance array gets updated then the graph has a negative cycle
    for(auto it:edges){
        int u=it[0];
        int v=it[1];
        int wt=it[2];
        if(dist[u]!=1e9 && dist[u]+wt<dist[v]) return {-1};
    }

    return dist;
}
//The first loop runs for V*E times and the second runs for E times
//Distance array is only used to return the ans
//Time Complexity will be O(E(V+1))
//Space Complexity will be O(1)


//Multi Source Shortest Path
//In Dijkstra's and Bellman gives the shortest distance of a node from a source
//However this time we need to find out the shortest distance of each node from every other node
//One way is to use dijkstra's algorithm n times with each node as src
//That will be the optimal method only when the graph doesn't have negative edge weights
vector<vector<int>> multiSrcShortestPath_dijkstra(int n,vector<vector<pair<int,int>>> &adj){
    vector<vector<int>> ans;
    for(int i=0;i<n;i++){
        vector<int> dist=dijkstrasAlgorithmI(n,adj,i);
        ans.push_back(dist);
    }
    return ans;
}
//Time Complexity will be O(VE*logV)
//Space Complexity will be O(2E)


//Floyd Warshall Algorithm
//In case the graph has negative edge weights, the dijkstra fails and we need to use Floyd Warshall Algorithm
//It takes much more time than dijkstra, but we don't have a choice when the edge weights are negative
//Used for multisource shortest path and can also identify negative cycles
//Watch video, explanation is very simple
//Also to apply this method in a undirected graph, make the directed graph, bidirectional, then it will behave like undirected graph
vector<vector<int>> floydWarshallAlgorithm(int n,vector<vector<int>> &edges){

    //We will use a cost matrix, initialised with a big value
    vector<vector<int>> cost(n,vector<int> (n,1e9));
    //Time Complexity : O(n2)

    //To reach from node i to i, cost is 0, therefore cost[i][i]=0
    for(int i=0;i<n;i++) cost[i][i]=0;
    //Time Complexity : O(n)

    //The adjacency list has three elements as {u,v,wt} where the edge from u->v has weight wt
    for(auto it:edges){
        int u=it[0];
        int v=it[1];
        int wt=it[2];
        cost[u][v]=wt;

        //Incase the graph is undirected, just add cost[v][u]=wt
    }
    //Time Complexity : O(E)
    //After this our cost matrix is ready to be implemented

    for(int k=0;k<n;k++){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(cost[i][k]==1e9 || cost[k][j]==1e9) continue;
                cost[i][j]=min(cost[i][j],cost[i][k]+cost[k][j]);
            }
        }
    }
    //Time Complexity : O(n3)

    //We can detect a negative cycle if cost from node i to i itself is less than 0, that would mean there exists a negative cycle
    for(int i=0;i<n;i++){
        if(cost[i][i]<0) return {{-1}};
    }
    //Time Complexity : O(n)

    //We also need to put -1 in the cost matrix for the nodes which are unreachable
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(cost[i][j]==1e9) cost[i][j]=-1;
        }
    }
    //Time Complexity : O(n2)
    return cost;
}
//The total time will be 2n+2n2+E+n3, which will boil down to n3
//Space is used to return the answer, no space is used to solve the question
//Time Complexity will be O(n3)
//Space Complexity will be O(1)


//Find the city with the smallest number of neighbours at a threshold distance
//Incase more than one cities are there, give the largest numbered ciy
//Just typical use of Floyd Warshall Algorithm
//Make sure this time the edge is bidirectional, so fill the cost array both ways
int thresholdNeigbour(int n,vector<vector<int>> &edges,int threshold){

    //We will create the cost matrix similar to floyd Warshall algorithm
    vector<vector<int>> cost(n,vector<int> (n,1e9));
    for(int i=0;i<n;i++) cost[i][i]=0;
    for(auto it:edges){
        int u=it[0];
        int v=it[1];
        int wt=it[2];
        cost[u][v]=wt;
        cost[v][u]=wt;
    }
    //Takes m time

    for(int k=0;k<n;k++){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(cost[i][k]==1e9 || cost[k][j]==1e9) continue;
                cost[i][j]=min(cost[i][j],cost[i][k]+cost[k][j]);
            }
        }
    }
    //Takes n3 time

    int cntCity=n;
    int cityNo=-1;

    for(int city=0;city<n;city++){
        int cnt=0;
        for(int adjCity=0;adjCity<n;adjCity++){
            
            //Skip when adjCity and city are same
            if(city==adjCity) continue;
            if(cost[city][adjCity]<=threshold) cnt++;
        }
        if(cnt<=cntCity){
            cntCity=cnt;
            cityNo=city;
        }
    }
    //Takes n2 time

    return cityNo;
}
//The biggest loop runs for about n3 times
//Space is used by the cost matrix
//Time Complexity will be O(n3)
//Space Complexity will be O(n2)




//Spanning Tree : Concept
//A graph which has N nodes and N-1 edges and all nodes are reachable from each other, ie, the graph doesn't have disjoint components
//Search on internet for examples to better understand
//Minimum Spanning Tree
//We will be given a graph, and we have to sketch the the MST from it
//We can multiple spanning trees from a single graph
//Among all such trees, the tree in which the sum of all edges is the least, is called MST
//We need to sketch out the MST from a given graph
//The sum of edge weights is called MST weight of spanning tree's weight

//Prim's Algorithm
//Helps us to find the MST's weight and the MST itself
//We will require two things, first is a priority queue(min heap, storing : wt, node, parent), and the other is a visited array

//We have also calculated edgeWt in this function, in case we want to return edgeWt, we can just change the function and its return type
vector<pair<int,int>> primsAlgorithm(int n,vector<vector<pair<int,int>>> &adj){
    vector<pair<int,int>> mst;
    vector<int> vis(n,0);
    priority_queue<vector<int>,vector<vector<int>>,greater<vector<int>>> pq;
    //priority queue will store elements as wt,node,parent

    int sum=0;
    pq.push({0,0,-1});
    //We push the starting node with -1 as parent
    while(!pq.empty() && mst.size()<n-1){
        auto t=pq.top();
        int wt=t[0];
        int node=t[1];
        int parent=t[2];
        pq.pop();
        if(vis[node]) continue;
        sum+=wt;
        vis[node]=true;
        if(parent!=-1) mst.push_back({node,parent});
        for(auto it:adj[node]){
            int adjNode=it.first;
            int adjWt=it.second;
            if(vis[adjNode]) continue;
            pq.push({adjWt,adjNode,node});
        }
    }
    return mst;
}
//The pq can hold all the edges at max which is E, so the push and pop operations take logE time
//This makes a total of ElogE
//Since for a connected graph, E<=V2
//Therefore the time taken will be ElogV
//Visited array stores V element, so does mst array(2V), priority queue can hold at max E
//Time Complexity will be O(ElogV)
//Space Complexity will be O(3V+E)


/*
Disjoint Set
This is not a graph, this is a separate data structure
A video is recommended
Consider a graph with two components(disconnected from each other), as 1->2->3 and 5->6
If someone asks us to check if 1 and 2 are connected the only option we have is to traverse from 1 and see if we reach 5 or not
However this takes too much time O(V+E)
Disjoint Set concepts allows us to do so in constant time
Disjoint Sets are used for dynamic graphs which keeps on changing with time
Disjoint Sets gives two functionalities, one is to find the parent the other is to find the union(can be done in two methods, rank or size)
The union operation can be implemented in two ways, either by using the rank method or by using the size method

Base Code for Union Operation
Union(u,v){
    //Step 1). Find ultimate parent of u(say pu) and ultimate parent of v(say pv)
    //Step 2). Find rank of pu and pv
    //Step 3). Connect smaller rank to larger rank always (Incase they are equal, you can connect in any order)
}

The findParent() function as well as the union functiont takes time equal to 4*a(a is alpha), which is mathematically proven and has a very long proof. 
The value of a is extremely small and so the time is almost constant
Hence the whole of disjoint set data structure works in 4*a

There are two kinds of parent, think of a binary tree, when we say parent, we mean the node just above, but there is also a thing called ultimate parent
Ultimate parent means like the root, the person sitting at the top most level

Since we often need to find the ultimate parent, therefore we use path compression
Path compression is done using backtracking, a sample code is given as 
findParent(u){
    if(u==parent[u]) return u
    findParent(parent[u])
}

We will form a class so that our code can be used for multiple times
*/

class DisjointSet{
    public:
        vector<int> rank;
        vector<int> parent; 
        vector<int> count;
        DisjointSet(int n){
            rank.resize(n+1,0);//We are using n+1 size so that the data structure works for both one based and zero based indexing graphs
            count.resize(n+1,1);
            parent.resize(n+1);
            iota(parent.begin(),parent.end(),0);
        }

        int findUltimatePar(int node){
            if(node==parent[node]) return node;
            return parent[node]=findUltimatePar(parent[node]);//The path compression technique
        }

        void unionByRank(int u,int v){
            int pu=findUltimatePar(u);
            int pv=findUltimatePar(v);

            //If they belong to the same component, that is their ultimate parents are the same, no need to do anything, simply return
            if(pu==pv) return;

            //Now we reattach them on the basis of their rank
            if(rank[pu]<rank[pv]) parent[pu]=pv;
            else if(rank[pu]>rank[pv]) parent[pv]=pu;
            else{
                parent[pv]=pu;
                rank[pu]++;
            }
        }
        //Time Complexity will be O(4*a)

        void unionBySize(int u,int v){
            int pu=findUltimatePar(u);
            int pv=findUltimatePar(v);

            //If they have same ultimate parent, no need to do anything, simply return
            if(pu==pv) return;

            //Now we attach the component having a smaller size(count) to the one having larger size(count)
            if(count[pu]<count[pv]){
                parent[pu]=pv;
                count[pv]+=count[pu];
            }
            else{
                parent[pv]=pu;
                count[pu]+=count[pv];
            }
        }
        //Time Complexity will be O(4*a)
};


//Kruskal's Algorithm
//This algorithm is used to find the minimum spanning tree of a graph
//The algorithm is extremely easy, watch the video once
vector<pair<int,int>> kruskalsAlgorithm(int n,vector<vector<pair<int,int>>> &adj){
    vector<pair<int,pair<int,int>>> edges;
    for(int i=0;i<n;i++){
        for(auto it:adj[i]){
            int adjNode=it.first;
            int wt=it.second;
            int node=i;
            if(i<adjNode) edges.push_back({wt,{node,adjNode}});//This line is to avoid duplicate insertions in undirected graphs
        }
    }
    sort(edges.begin(),edges.end());
    //Uses mlogm time
    //Now we create a disjoing set with v vertices
    DisjointSet ds(n);
    vector<pair<int,int>> mst;
    int mstWt=0;

    //This takes m*4*a time
    for(auto it:edges){
        int wt=it.first;
        int u=it.second.first;
        int v=it.second.second;

        if(ds.findUltimatePar(u)!=ds.findUltimatePar(v)){
            ds.unionByRank(u,v);
            mst.push_back({u,v});
            mstWt+=wt;
        }
    }
    return mst;
}


//Number of provinces
//Count the number of unique ultimate parents or a better way to count the number of nodes which are same as their utimate parents
//We will use a adjacency matrix this time
//The graph is undirected
int numberOfProvincesII(int n,vector<vector<int>> &adj){
    DisjointSet ds(n);
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(adj[i][j]==1){
                int pu=ds.findUltimatePar(i);
                int pv=ds.findUltimatePar(j);
                if(pu==pv) continue;
                ds.unionByRank(pu,pv);
            }
        }
    }
    //This loop runs for n*n*4*a

    int cnt=0;
    for(int i=0;i<n;i++){
        if(ds.parent[i]==i) cnt++; //We could also use ds.findUltimatePar(i)==i, but this is more optimal
    }
    //This loop runs for n

    return cnt;
}
//Time Complexity will be O(n2)


//Number of operations to make network connected
//This is simple, first find out how many extra edges we have
//Then find out the number of connected components
int numberOfOperations(int n,vector<vector<int>> &edges){
    DisjointSet ds(n);

    //First we need to count how many extra edges do we have
    int extraEdges=0;
    for(auto it:edges){
        int u=it[0];
        int v=it[1];
        if(ds.findUltimatePar(u)==ds.findUltimatePar(v)) extraEdges++;
        else ds.unionByRank(u,v);
    }
    //This code will run about E*4*a

    //Now we need to do something very similar like the previous problem of finding the number of provinces
    int cnt=0;
    for(int i=0;i<n;i++){
        if(ds.parent[i]==i) cnt++;
    }
    //This will run for n times

    //To connect n components we would need n-1 edges, lets check if we have this many, otherwise return -1
    if(extraEdges<cnt-1) return -1;
    
    //Incase they are enough, just return cnt-1
    return cnt-1;
}


//Accounts Merge
vector<vector<string>> mergeAccounts(vector<vector<string>> &details){
    int n=details.size();
    DisjointSet ds(n);
    unordered_map<string,int> mp;
    for(int i=0;i<n;i++){
        for(int j=1;j<details[i].size();j++){
            string mail=details[i][j];
            if(mp.find(mail)==mp.end()) mp[mail]=i;
            else ds.unionByRank(i,mp[mail]);
        }
    }

    vector<vector<string>> merged(n);
    for(auto &p:mp){
        string mail=p.first;
        int par=ds.findUltimatePar(p.second);
        merged[par].push_back(mail);
    }

    vector<vector<string>> ans;
    for(int i=0;i<n;i++){
        if(merged[i].size()==0) continue;
        sort(merged[i].begin(),merged[i].end());
        vector<string> temp;
        temp.push_back(details[i][0]);
        for(auto it:merged[i]) temp.push_back(it);
        ans.push_back(temp);
    }
    return ans;
}
//Let n be the total number of people/accounts and m be the total number of mails
//Union takes : M*4*a
//Sorting takes : MlogM
//Space Used : M
//Time Complexity will be O(MlogM)
//Space Complexity will be O(M)


//Number of Islands II
//This is an online query type problem, where we will be given queries and we need to tell the answer after receiving each query
//For this problem we would need to convert 2D arr indices to 1D arr indices and vice versa
//Also the original matrix will be all 0s so only matrix order is given
vector<int> noOfIslandsII(int n,int m,vector<pair<int,int>> &operators){
    DisjointSet ds(n*m);

    //We would also need a table to keep track of visited elements
    vector<vector<bool>> vis(n,vector<bool> (m,0));
    int cnt=0;//count of islands initially

    vector<int> ans; //Stores the answers of all queries

    //To traverse the neighbours we would need the dx arrays
    vector<int> dx={-1,0,1,0};
    vector<int> dy={0,1,0,-1};

    for(auto it:operators){
        int i=it.first;
        int j=it.second;

        int node=m*i+j;

        //Incase this index is already visited, there would be no change in count of islands and we can push the answer of this query as is
        if(vis[i][j]){
            ans.push_back(cnt);
            continue;
        }

        //Incase it is not visited, first mark it visited and then increase the count of islands
        vis[i][j]=true;
        cnt++;

        //Now check its neighbours
        for(int k=0;k<4;k++){
            int ni=i+dx[k];
            int nj=j+dy[k];

            //We check if the neighbour is an island or not, if it is not an island, no need to do anything
            if(ni>=0 && ni<n && nj>=0 && nj<m && vis[ni][nj]==1){

                //Now we also need to check for connectivity, are they connected or not?
                //First let us get the convert the index
                int adjNode=m*ni+nj;
                if(ds.findUltimatePar(node)==ds.findUltimatePar(adjNode)) continue;
                else{   //We connect them
                    ds.unionByRank(node,adjNode);
                    cnt--;
                }
            }
        }
        ans.push_back(cnt);

    }

    return ans;
}
//The loop runs for q times where q is the number of queries
//The disjoint sets operations take 4a time
//There's also a loop that runs 4 times to calculate neighbours
//Time Complexity will be O(q*4*4a)


//Making a large island
int largeIsland(vector<vector<int>> &mat){
    int n=mat.size();
    int m=mat[0].size();

    //First let us do a simple check to see if there are all ones
    bool flag=false;
    for(int i=0;i<n;i++){
        if(flag==true) break;
        for(int j=0;j<m;j++){
            if(mat[i][j]==0){
                flag=true;
                break;
            }
        }
    }
    //Time Complexity will be O(mn)
    if(flag==false) return (m*n);

    DisjointSet ds(n*m);
    vector<int> dx={0,-1,0,1};
    vector<int> dy={1,0,-1,0};
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(mat[i][j]==0) continue;
            int node=m*i+j;
            for(int k=0;k<4;k++){
                int ni=i+dx[k];
                int nj=j+dy[k];
                if(ni>=0 && ni<n && nj>=0 && nj<m && mat[ni][nj]==1){
                    //Check if they are joined
                    int adjNode=m*ni+nj;
                    int pu=ds.findUltimatePar(node);
                    int pv=ds.findUltimatePar(adjNode);
                    if(pu==pv) continue;
                    ds.unionBySize(node,adjNode);
                }
            }
        }
    }
    //Time Complexity will be O(4mn)

    //Now we start by setting zeroes
    int maxi=1;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(mat[i][j]==1) continue;
            int islandCnt=1;
            unordered_set<int> st;
            for(int k=0;k<4;k++){
                int ni=i+dx[k];
                int nj=j+dy[k];
                if(ni>=0 && ni<n && nj>=0 && nj<m && mat[ni][nj]==1){
                    int adjNode=m*ni+nj;
                    int pu=ds.findUltimatePar(adjNode);
                    st.insert(pu);
                }
            }
            for(auto it:st){
                int cnt=ds.count[it];
                islandCnt+=cnt;
            }
            maxi=max(maxi,islandCnt);
        }
    }
    //Time Complexity will be O(4mn)
    return maxi;
}
//There are three loops in total which run about 4mn+4mn+mn time
//Space is occupied by the DisjointSet data structure which has been discussed before
//Time Complexity will be O(9mn)
//Space Complexity will be O(2mn)


//Most Stones removed with same row or column
//Video is recommended since the concept may seem easy, but is not
//The answer to this question is n-k (where n is the total number of stones and k is the total number of connected components)
//We are given the list of vectors which denotes the coordinates of stones
int stoneRemoval(int n,vector<vector<int>> &stones){

    //First we need to find out the grid size
    int maxRow=0;
    int maxCol=0;
    for(auto it:stones){
        maxRow=max(maxRow,it[0]);
        maxCol=max(maxCol,it[1]);
    }

    DisjointSet ds(maxRow+maxCol+1);//+1 for safety reasons
    unordered_map<int,int> stoneNodes;

    for(auto it:stones){
        int nodeRow=it[0];
        int nodeCol=it[1]+maxRow+1;
        ds.unionBySize(nodeRow,nodeCol);
        stoneNodes[nodeRow]=1;
        stoneNodes[nodeCol]=1;
    }

    int cnt=0;
    for(auto it:stoneNodes){
        if(ds.findUltimatePar(it.first)==it.first) cnt++;
    }
    return n-cnt;
}


//Strongly Connected Components
//SCCs are only valid in directed graphs
//We solve this using Kosaraju's Algorithm
//In interviews there can be two kind of question
//One type is to find the number of SCCs(Strongly Connected Components)
//The other type is to print those SCCs

//Kosaraju's Algorithm
//Intuition : We somehow need to separate the SCCs, since on normal traversal through the graph, we will end up going through each node and hence won't find SCCs
//Therefore if we can somehow stop the traversal from one SCC to another, that will be it
//Concept : If we reverse the edge connecting one scc to another, then we can stop that traversal
//How to find out which is the edge connecting two SCCs?
//Simple, reverse all the edges, since reversing edges inside SCC doesn't matter, try yourself
//Reverse all the edges and then count the number of components, that will be the number of SCCs
//However consider graphs as s1->s2->s3(where s1,s2,s3 are all SCCs) and after reversing we get s1<-s2<-s3
//This logic fails if src was in s3, then even after reversing we would still travel the whole graph as on component
//Hence the idea of arranging the edges may feel convenient
//Therefore we first do a dfs and store all the nodes in a stack

//A function to do dfs to store the nodes in stack
void SCCdfs(int node,stack<int> &st,vector<bool> &vis,vector<vector<int>> &adj){
    vis[node]=true;
    for(auto it:adj[node]){
        if(!vis[it]) SCCdfs(it,st,vis,adj);
    }
    st.push(node);
}

//A second helper function to handle the second dfs traversal
//New function since this time, we don't need to have a stack in arguments
void SCCdfsII(int node,vector<bool> &vis,vector<vector<int>> &adj){
    vis[node]=true;
    for(auto it:adj[node]){
        if(!vis[it]) SCCdfsII(it,vis,adj);
    }
}
int numberOfSCCs(vector<vector<int>> &adj){
    stack<int> st;
    int n=adj.size();

    //First we create a visited array to help us in the dfs
    vector<bool> vis(n,false);

    //Now we do a dfs and store the elements in the stack
    for(int i=0;i<n;i++){
        if(vis[i]) continue;
        SCCdfs(i,st,vis,adj);
    }

    //Next step is reversing the links using the previously created revLinks function
    adj=revLinks(adj);

    //Now we only have to find out the number of components
    //We can do a normal dfs or use the disjoint set for this part
    //Applying Disjoint set here can be overkill, as a simple traversal is much more easier and optimal
    //Therefore we apply a normal traversal, but lets first reset the visited array
    vis.assign(n,false);
    int cnt=0;
    while(!st.empty()){
        int node=st.top();
        st.pop();
        if(vis[node]) continue;
        cnt++;
        SCCdfsII(node,vis,adj);
    }
    return cnt;
}
//Time Complexity will be O(V+E)
//Space Complexity will be O(V+E)



//Bridges in a graph
//Tarjan's Algorithm
//A bridge is a link between two nodes such that if you remove that link, the graph(more specifically, that component) splits into two components
//We need to print the number of bridges
//We require two arrays for this, one will record time of insertion and the other will have the lowest time of insertion
//This is famously the Tarjan's Algorithm of Time in and low time
//The logic is this : if the node's time of insertion is lesser than the lowest time of it's adjacent, then the adjacent node can only be reached by the link
//There in that case that link is a bridge
//We will use a global variable for this problem
int timer=1;
void bridgeHelper(int node,int parent,vector<bool> &vis,vector<int> &in,vector<int> &least,vector<vector<int>> &adj,vector<vector<int>> &bridge){
    vis[node]=true;
    in[node]=least[node]=timer;
    timer++;
    for(auto it:adj[node]){
        if(it==parent) continue;
        if(!vis[it]){
            bridgeHelper(it,node,vis,in,least,adj,bridge);
            least[node]=min(least[it],least[node]);
            //Now we check can this link node-----it be a bridge
            if(in[node]<least[it]){
                bridge.push_back({node,it});
            }
        }
        else least[node]=min(least[node],least[it]);
    }
}
int cntBridges(vector<vector<int>> &adj){
    int n=adj.size();
    vector<int> in(n,0);
    vector<int> least(n,0);
    vector<bool> vis(n,false);
    vector<vector<int>> bridge;
    for(int i=0;i<n;i++){
        if(vis[i]) continue;
        bridgeHelper(i,-1,vis,in,least,adj,bridge);
    }
    return bridge.size();
}
//Time Complexity will be O(V+E)
//Space Complexity will be O(V+E)


//Articulation Point
//Same concept as bridges in a graph, but applied to nodes
//A node is an articulation point, if its removal splits the graph into more than one component

//First we need a dfs function and a global variable named cnt
int cnt=0;
void articulationPointDfs(int node,int parent,vector<bool> &vis,vector<int> &tin,vector<int> &low,vector<int> &hash,vector<vector<int>> &adj){
    vis[node]=true;
    tin[node]=low[node]=cnt;
    cnt++;
    int child=0;
    for(auto it:adj[node]){
        if(it==parent) continue;
        if(vis[it]) low[node]=min(low[node],tin[it]);
        else{
            articulationPointDfs(it,node,vis,tin,low,hash,adj);
            low[node]=min(low[node],low[it]);
            if(low[it]>=tin[node] && parent!=-1) hash[node]=1;

            //Increase the cnt of child, only inside the not visited component, otherwise a cycle will confuse the count
            child++;
        }
    }
    if(child>1 && parent==-1) hash[node]=1;
}
vector<int> articulationPoint(vector<vector<int>> &adj){
    int n=adj.size();
    vector<bool> vis(n,false);
    vector<int> tin(n,0);
    vector<int> low(n,0);
    vector<int> hash(n,0);
    for(int i=0;i<n;i++){
        if(vis[i]) continue;
        articulationPointDfs(i,-1,vis,tin,low,hash,adj);
    }
    vector<int> ans;
    for(int i=0;i<n;i++){
        if(hash[i]!=0) ans.push_back(i);
    }
    if(ans.size()==0) return {-1};
    return ans;
}
//Time Complexity will be O(V+E)
//Space Complexity will be O(V)




int main(){
    //Your Code here
    return 0;
}







