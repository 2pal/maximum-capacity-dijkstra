
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <bits/stdc++.h>

// Do not change this definition
#define INT_MAX 1000


using namespace std;

class Graph{
public:
	int node_count;
	int edge_count;
	int** adjacency_matrix;
	Graph();
	void read_file(char* filename);
	void print_adjacency_matrix(); // in case you need
	int weight(int i, int j){return this->adjacency_matrix[i][j];}
	~Graph();
};

Graph::Graph(){
    
}

Graph::~Graph(){
	for(int i = 0; i < node_count; i++){
		delete [] adjacency_matrix[i];
	}
}


void Graph::print_adjacency_matrix(){	
	// Prints the adjacency matrix
	for(int i = 0; i < this->node_count; i++){
		for(int j = 0; j < this->node_count; j++){
			cout<<this->adjacency_matrix[i][j]<<", ";
		}
		cout<<endl;
	}
}

void Graph::read_file(char* filename){
	
	ifstream filehandler(filename);
    filehandler >> node_count;
    adjacency_matrix = new int*[node_count];
    for(int i = 0; i < node_count; i++)
        adjacency_matrix[i] = new int[node_count];
   
    for(int i = 0; i < node_count; i++){
        for(int j = 0; j < node_count; j++)
            adjacency_matrix[i][j] = 0;
    }
    int count=0;

    while(true){
        int a,b,c;
        filehandler>>a>>b>>c;
        adjacency_matrix[a][b] = c;
        adjacency_matrix[b][a] = c;
        count++;
        if(filehandler.eof()){
            break;
        }
    }
    
    edge_count = count;
}
bool there_fringes(int a[],int x){
    for(int i=0; i<x; i++){
        if(a[i]==1)
            return true;
    }
    return false;
}


void Modified_Dijkstra(Graph* graph){

	
    int node_count = graph->node_count;
    int edge_count = graph->edge_count;
    
    int status[node_count];
    int wt[node_count];
    int dad[node_count];

    for(int i=0; i<node_count; i++){
        status[i]=0;
        wt[i]=-1;
        dad[i]=-1;
    }
    
    status[0] = 2;
    wt[0] = INT_MAX;
    for (int i=0; i< node_count; i++) {
        if(graph->adjacency_matrix[0][i] !=0){
            status[i]=1;
            wt[i]=graph->weight(0,i);
            dad[i]=0;
        }
    }
    
    while(there_fringes(status,node_count)){
        int v;
        int max_wt =0;
        for(int i=0; i<node_count; i++){
            if(status[i]==1 && wt[i]>max_wt){
                v=i;
                max_wt = wt[i];
            }
        }
        status[v]=2;
        for (unsigned i=0; i< node_count; i++) {
            if(graph->adjacency_matrix[v][i] != 0){
                 int w = i;
                 if(status[w] == 0){
                    status[w] =1;
                    wt[w] = min(wt[v] , graph->weight(v,w));
                    dad[w] = v;
                }else if(status[w] == 1 && (wt[w] < min(wt[v], graph->weight(v,w)))){
                    wt[w] = min(wt[v],graph->weight(v,w));
                    dad[w] = v;
                }
            }
        }
    }
	for(int i=0; i<node_count; i++){
        cout << dad[i] << " ";
    }
	
	// The following line prints wt array (or vector).
	// Do not change anything in the following lines.
	cout<<"###########RESULTS###########"<<endl;
	cout<<endl;
	
	cout<<"1. WT ARRAY"<<endl;
	cout<<"------------------------"<<endl;
	cout<<"  ";
	for(int i = 0; i < graph->node_count - 1; i++){
		cout << wt[i] << ", ";
	}
	cout << wt[graph->node_count - 1] << endl;
	
	// The following lines print the final path.
	// Do not change anything in the following lines.
	int iterator = graph->node_count - 1;
	vector<int> path_info;
	path_info.push_back(iterator);
	while(iterator != 0){
		path_info.push_back(dad[iterator]);
		iterator = dad[iterator];
	}
	cout<<endl;
	cout<<"2. MAXIMUM CAPACITY PATH"<<endl;
	cout<<"------------------------"<<endl;
	cout<<"  ";
	vector<int>::iterator it;
    for (it = path_info.end() - 1; it > path_info.begin(); it--)
        cout << *it << " -> ";
    cout<<*path_info.begin()<<endl;
    
    cout<<endl;
    cout<<"3. MAXIMUM CAPACITY"<<endl;
    cout<<"------------------------"<<endl;
    cout<<"  ";
    cout<<wt[graph->node_count - 1]<<endl;
    cout<<"#############################"<<endl;
    
    return;
}

int main(int argc, char **argv){
	Graph* graph = new Graph();
    char* c = "test1.txt";
	graph->read_file(c);
	Modified_Dijkstra(graph);
	
	return 0;	
}
