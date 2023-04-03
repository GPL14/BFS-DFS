#include<iostream>
#include<vector>;
#include <fstream>
#include <bits/stdc++.h>
using namespace std;
// display graph in adjacency matrix
void display(vector<int> adj[], int n){
    for(int i=1;i<n;i++){
        cout<<i<<" -> ";
        for(auto x: adj[i]){
        	cout << x << " ";
		}
		cout << '\n';
    }
}

// for checking the bipartite or not
bool bfs(int start, int V, vector<int> adj[], int color[]){
	queue<int> q;
	q.push(start);
	color[start] = 0;

	while(!q.empty()){
		int node = q.front();
		q.pop();


		for(auto i: adj[node]){
			if(color[i] == -1){
				color[i] = !color[node];
				q.push(i);
			}
			else if(color[i] == color[node]){
				return false;
			}
		}
	}
	return true;
}

bool isBipartite(int V, vector<int> adj[]){
	int color[V];
	for(int i=1;i<V;i++){
		color[i] = -1;

	}

	for(int i=1;i<V;i++){
		if(color[i] == -1){
			if(bfs(i, V, adj, color) == false){
				return false;
			}
		}
	}
	return true;
}

// for checking the components and travers the graph
void dfs(int V, vector<int> adj[], int vis[]){
	vis[V] = 1;
	cout << V << " ";
	for(auto i: adj[V]){
		if(!vis[i]){
			dfs(i, adj, vis);
		}
	}
}

void numberOfcomponents(int s, vector<int> adj[], int V){
	int vis[V] = {0};
	for(int i=s;i<V;i++){
		if(!vis[i]){
			dfs(i, adj, vis);
			cout << '\n';
		}
	}
}

// print the matrix
void printMatrix(vector<vector<int> > adj, int V)
{
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            cout << adj[i][j] << "   ";
        }
        cout << endl;
    }
    cout << endl;
}

//convert the list to matrix
vector<vector<int>> convert(vector<int> adj[], int V)
{
    vector<vector<int> > matrix(V, vector<int>(V, 0));

    for (int i = 0; i < V; i++) {
        for (auto j : adj[i])
            matrix[i][j] = 1;
    }
    return matrix;
}

//BFS traversal of the graph
void BFS(int s, int vis[], int V, vector<int> adj[]){

    vis[s] = 1;

    queue<int> q;
    q.push(s);

    while(!q.empty()) {
        int node = q.front();
        cout << node << " ";
        q.pop();

        // traverse for all its neighbours
        for(auto it : adj[node]) {
            if(!vis[it]) {
                vis[it] = 1;
                q.push(it);
            }
        }
    }
}
// components
void cc(int s, int V, vector<int> adj[]){
	int vis[V] = {0};
	for(int i=s;i<V;i++){
		if(!vis[i]){
			BFS(i, vis, V, adj);
		}
	}
}

int main(){
 	ifstream text_file("asn.a.txt");

	if(!text_file){
		cout << "File not created";
	}
	else{

 	vector<int> adj[14];

 	string row_data, word;
 	int u = 1;
 	while(getline(text_file, row_data)){
			stringstream str(row_data);
            while(getline(str,word,',')){
                stringstream s(word);
                int n;
                s>>n;
                adj[u].push_back(n);
            }
            u++;
		}
	cout << "Adjacency List =>" << endl;
	display(adj, 14);

	cout << "Matrix =>"<< endl;
	vector<vector<int>> matrix = convert(adj, 14);
	printMatrix(matrix,14);
//	bool ans = isBipartite(14, adj);cout << ans;cc(9, 14, adj);
	 while(1){
        cout<<endl<<"1. BFS\t"<<"2: DFS\t"<<"3: isBipartite\t"<<"4: exit\t"<<endl;
        cout<<"Make your wish!! "<<endl;
        int ch;cin>>ch;
        switch(ch){
            case 1:
                {
                    cout<<"Enter the vertex at which you want to start the BFS: ";
                    int v;cin>>v;
                    cc(v, 14, adj);
                }
                break;
            case 2:
                {
                    cout<<"Enter the node where you want to start the DFS at: ";
                    int n;cin>>n;
                    numberOfcomponents(n, adj, 14);
                    cout<<endl;
                }
                break;
            case 3:
                {   bool ans = isBipartite(14, adj);
                    ans == 1?cout<<"yes! it is bipartite!"<<endl:cout<<"no! it is not bipartite!!"<<endl;
                }
                break;
            default:
                exit(0);
        }
    }
	return 0;
 }
}
