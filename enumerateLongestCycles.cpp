#include <bits/stdc++.h>

// Unsafe because no defined behaviour if character = 0. ctz and clz work with 32 bit numbers.
#define unsafePrev(character, current) (__builtin_ctz(character) - current >= 0 ? -1 : current -__builtin_clz((character) << (32 - current)) - 1)

#define prev(character,current) (character ? unsafePrev(character,current) : -1)

using namespace std;

const int nb_bits=64;
#define MAXVERTICES 64
#define MAXEDGES MAXVERTICES*MAXVERTICES

int getNumberOfVertices(string graphString) 
{
	if(graphString.size() == 0){
        printf("Error: String is empty.\n");
        abort();
    }
    else if((graphString[0] < 63 || graphString[0] > 126) && graphString[0] != '>') {
    	printf("Error: Invalid start of graphstring.\n");
    	abort();
    }

	int index = 0;
	if (graphString[index] == '>') { // Skip >>graph6<< header.
		index += 10;
	}

	if(graphString[index] < 126) { // 0 <= n <= 62
		return (int) graphString[index] - 63;
	}

	else if(graphString[++index] < 126) { 
		int number = 0;
		for(int i = 2; i >= 0; i--) {
			number |= (graphString[index++] - 63) << i*6;
		}
		return number;
	}

	else if (graphString[++index] < 126) {
		int number = 0;
		for (int i = 5; i >= 0; i--) {
			number |= (graphString[index++] - 63) << i*6;
		}
		return number;
	}

	else {
		printf("Error: Format only works for graphs up to 68719476735 vertices.\n");
		abort();
	}
}

void loadGraph(string graphString, int numberOfVertices, long long adjacencyList[]) {
	int startIndex = 0;
	if (graphString[startIndex] == '>') { // Skip >>graph6<< header.
		startIndex += 10;
	}
	if (numberOfVertices <= 62) {
		startIndex += 1;
	}
	else if (numberOfVertices <= MAXVERTICES) {
		startIndex += 4;
	}
	else {
		printf("Error: Program can only handle graphs with %d vertices or fewer.\n",MAXVERTICES);
		abort();
	}

	for (int vertex = 0; vertex < numberOfVertices; vertex++) { //Initialize adjacencyList.
		adjacencyList[vertex] = 0;
	}

	int currentVertex = 1;
	int sum = 0; 
	for (int index = startIndex; index<graphString.size(); index++) {
		int i;
		for (i = prev(graphString[index] - 63, 6); i != -1; i = prev(graphString[index] - 63, i)) {
			while(5-i+(index-startIndex)*6 - sum >= 0) {
				sum += currentVertex;
				currentVertex++;
			}
			sum -= --currentVertex;
			int neighbour = 5-i+(index - startIndex)*6 - sum;
            adjacencyList[currentVertex]|=(1LL<<neighbour);
            adjacencyList[neighbour]|=(1LL<<currentVertex);
		}
	}
}

#define left_shifted(n,x) ((n)<<(x))
#define set_bit(n,i) ((n)|=left_shifted(1LL,i))
#define count_bits(n) (__builtin_popcountll((n)))
//#define index_rightmost_bit(n) (count_bits((n)^(n-1))-1)
#define index_rightmost_bit(n) (__builtin_ctzll(n))
#define rightmost_bit_removed(n) ((n)&((n)-1))

//  Check if set is empty.
#define isEmpty(set) ((set) == 0)

//  Returns the size of the set.
#define sz(set) (__builtin_popcountll(set))

//	Loops over all elements of the set. 
#define forEach(element, set) for (int element = next((set), -1); (element) != -1; (element) = next((set), (element)))

//	Loops over all elements of the set starting from start (not included). 
#define forEachAfterIndex(element, set, start) for (int element = next((set), (start)); (element) != -1; (element) = next((set), (element)))

//  Returns -1 if the set is empty. Otherwise it executes unsafeNext(set, current).
#define next(set, current)  (isEmpty(set) ? -1 : unsafeNext((set), (current)) ) //the builtin clz and ctz compiler functions have unexpected behavior at zero.

// Returns the first element after current in the set. If there are no more elements after current, it returns -1. 
// Unsafe because the behaviour when the set is empty is not guaranteed.
#define unsafeNext(set, current) (__builtin_clzll(set) + (current) >= 63 ? -1 : (current) + __builtin_ctzll((set) >> ((current) + 1)) + 1)

#define complement(set, sizeOfUniverse) (~(set) << (64-(sizeOfUniverse)) >> (64-(sizeOfUniverse)))

int n;
int nb_edges;
long long adjacencyList[MAXVERTICES];
int edgeIndex[MAXVERTICES][MAXVERTICES];

int edgeIncluded[MAXEDGES];
long long visitedVertices;

int circumference;
int max_degree;

long long numberBest;
long long bestLength;

int skip_hamiltonian=1;

vector< vector<int> > allLongestCycles;
vector<int> currentCycle;

void go(int end1, int end2, int lowestVertex, int length)
{
    // option 1: end1 and end2 are neighbors
    if(left_shifted(1LL,end1)&adjacencyList[end2])
    {
        if(length>bestLength)
        {
            bestLength=length;
            numberBest=0;
            allLongestCycles.clear();
        }
        if(length==bestLength)
        {
            numberBest+=1;
            allLongestCycles.push_back(currentCycle);
        }
        if(bestLength==n && skip_hamiltonian==1)
        {
            numberBest=1e9;
            return;
        }
    }
    // if end1 has no unvisited neighbors left, stop recursing
    long long unvisitedNeighborsEnd1=(adjacencyList[end1]&complement(visitedVertices,n));
    if(unvisitedNeighborsEnd1<=left_shifted(1LL,lowestVertex)) return;

    // option 2: extend end2
    long long unvisitedNeighbors=(adjacencyList[end2]&complement(visitedVertices,n));
    forEachAfterIndex(neigh,unvisitedNeighbors,lowestVertex)
    {
        visitedVertices=(visitedVertices^(left_shifted(1LL,neigh)));
        edgeIncluded[edgeIndex[end2][neigh]]=1;
        currentCycle.push_back(neigh);
        go(end1,neigh,lowestVertex,length+1);
        currentCycle.pop_back();
        if(bestLength==n && skip_hamiltonian==1)
        {
            numberBest=1e9;
            return;
        }
        edgeIncluded[edgeIndex[end2][neigh]]=0;
        visitedVertices=(visitedVertices^(left_shifted(1LL,neigh)));
    }
}

void countLongestCycles()
{
    numberBest=0;
    bestLength=-1;
    int edge_idx_ctr=0;
    allLongestCycles.clear();
    currentCycle.clear();
    for(int i=0; i<n; i++)
    {
        forEachAfterIndex(neigh,adjacencyList[i],i)
        {
            //cerr << i << " " << neigh << endl;
            edgeIndex[i][neigh]=edgeIndex[neigh][i]=edge_idx_ctr++;
        }
    }
    nb_edges=edge_idx_ctr;
    for(int i=0; i<nb_edges; i++) edgeIncluded[i]=0;
    for(int start=0; start<n; start++)
    {
        forEachAfterIndex(neigh1,adjacencyList[start],start)
        {
            forEachAfterIndex(neigh2,adjacencyList[start],neigh1)
            {
                // path: neigh1 -> start -> neigh2
                visitedVertices=(left_shifted(1LL,start)|left_shifted(1LL,neigh1)|left_shifted(1LL,neigh2));
                edgeIncluded[edgeIndex[start][neigh1]]=edgeIncluded[edgeIndex[start][neigh2]]=1;
                currentCycle.push_back(neigh1);
                currentCycle.push_back(start);
                currentCycle.push_back(neigh2);
                go(neigh1,neigh2,start,3);
                currentCycle.clear();
                if(bestLength==n && skip_hamiltonian==1)
                {
                    numberBest=1e9;
                    return;
                }
                edgeIncluded[edgeIndex[start][neigh1]]=edgeIncluded[edgeIndex[start][neigh2]]=0;
            }
        }
    }
}

// reads a list of graphs in graph6 format and outputs each graph (in graph6 format and ajacency matrix format), followed by a line containing two integers c (the number of longest cycles) and d (the length of the longest cycles). Then c lines follow each containing d integers representing all longest cycles of the graph.
// By default, hamiltonian graphs are skipped. This default setting can be overwritten by passing the parameter "0" to the executable
int main(int argc, char *argv[])
{
    if(argc > 2)
    {
        cerr << "Wrong number of arguments." << endl;
    }
    if(argc==2)
    {
        skip_hamiltonian=atoi(argv[1]); // if no argument is provided, the default is 1.
    }
    ios::sync_with_stdio(false);
    cin.tie(0);
    long long nb_graphs_read_from_input=0;
    string line;
    while(getline(cin,line))
    {
        //line+="\n";
        nb_graphs_read_from_input++;
        n = getNumberOfVertices(line);
        //if(n>32) continue;
        loadGraph(line,n,adjacencyList);
        countLongestCycles();
        cout << line << endl;
        cout << n << endl;
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                if(adjacencyList[i]&(1LL<<j)) cout << "1";
                else cout << "0";
            }
            cout << endl;
        }
        int nbLongestCycles=allLongestCycles.size();
        int lenCycle=-1;
        if(nbLongestCycles>=1) lenCycle=allLongestCycles[0].size();
        cout << nbLongestCycles << " " << lenCycle << endl;
        for(vector<int> cyc : allLongestCycles)
        {
            for(int x : cyc)
            {
                cout << x << " ";
            }
            cout << endl;
        }
        //cout << numberBest << endl;
    }
    return 0;
}
