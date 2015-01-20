#ifndef GRAPH_H
#define GRAPH_H

#define UNVISITED -1

//Graph ADT
class Graph{
private :
	void operator =(const Graph&) {}
	Graph(const Graph&){}
public :
	Graph(){}
	virtual ~Graph(){}
	//Initialize a graph of n vertices
	virtual void Init(int n) = 0;
	
	//Return: the number of vertices and edges
	virtual int n() = 0;
	virtual int e() = 0;

	//Return v's first neighbor
	virtual int first(int v) = 0;

	//Return v's next neighbor
	virtual int next(int v, int w) = 0;

	//Set the weight for an edge
	//v1, v2:The vertices
	//wgt: Edge weight
	virtual void setEdge(int v1, int v2, int wght) = 0;

	//Delete an edge
	//v1, v2: The vertices
	virtual void delEdge(int v1, int v2) = 0;

	//Determine if an edge is in the graph
	//v1, v2:The vertices
	//Return: true if edge v1, v2 has non-zero weight
	virtual bool isEdge(int v1, int v2) = 0;

	//Return an edge's weight
	//v1, v2:The vertices
	//Return: The weight of edge v1, v2, or zero
	virtual int weight(int v1, int v2) = 0;

	//Get and Set the mark value for a vertex
	//v: The vertex
	//val: The value to set
	virtual int getMark(int v) = 0;
	virtual void setMark(int v, int val) = 0;
};

//Implementation for the adjecency matrix representation
class Graphm : public Graph{
private:
	int numVertex, numEdge;
	int **matrix;
	int *mark;
public:
	Graphm(int numVert){ Init(numVert); }
	~Graphm(){
		delete[] mark;
		for (int i = 0; i < numVertex; i++)
			delete[] matrix[i];
		delete[] matrix;
	}
	void Init(int n){
		int i;
		numVertex = n;
		numEdge = 0;
		mark = new int[n];
		for (i = 0; i < numVertex; i++) mark[i] = UNVISITED;
		matrix = (int**) new int*[numVertex];
		for (i = 0; i < numVertex; i++) matrix[i] = new int[numVertex];
		for (i = 0; i < numVertex; i++){
			for (int j = 0; j < numVertex; j++) matrix[i][j] = 0;
		}
	}
	int n(){ return numVertex; }
	int e(){ return numEdge; }

	int first(int v){
		for (int i = 0; i < numVertex; i++){
			if (matrix[v][i] != 0) return i;
		}
		return numVertex; //return n if none
	}

	int next(int v, int w){
		for (int i = w + 1; i < numVertex; i++){
			if (matrix[v][i] != 0) return i;
		}
		return numVertex;
	}
	void setEdge(int v1, int v2, int wt){
		if (wt <= 0) return;
		if (matrix[v1][v2] == 0) numEdge++;
		matrix[v1][v2] = wt;
	}
	void delEdge(int v1, int v2){
		if (matrix[v1][v2] != 0) numEdge--;
		matrix[v1][v2] = 0;
	}
	bool isEdge(int i, int j){ return matrix[i][j] != 0; }
	int weight(int v1, int v2) { return matrix[v1][v2]; }
	int getMark(int v) { return mark[v]; }
	void setMark(int v, int val){ mark[v] = val; }
};

#endif