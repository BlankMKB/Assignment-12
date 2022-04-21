#include "graph.h"

//private methods (ends on line 38)
int graph::size() const {
    //return size of matrix
    return this->n * this->n;
}

int graph::at(const std::string& name) const {
    //search for id given city name
    for(int i = 0; i < this->n; i++) {
        //if curr name matches city name
        if(this->v[i].city == name) {
            return this->v[i].id;
        }
    }
    
    //if not found, return -1
    return -1;
}

bool graph::hasBFSPath(const int& start, const int& end) {
    //true: nonzero value at [start][end]
    //false: zero at [start][end]
    return (this->adjMat[start][end]).first != 0;
}

bool compare(const edge& e1, const edge& e2) {
    //true: weight 1 < weight 2
    //false: weight 1 >= weight 2
    return (e1.weight < e2.weight);
}

bool sortByDist(const std::pair<vertex, int>& d1, const std::pair<vertex, int>& d2) {
    //true: dist 1 < dist 2
    //false: dist 1 >= dist 2
    return (d1.second < d2.second);
}
//end of private methods

//constructor
graph::graph(const int& n) : n(n){
    //new array of <distance, edge type> pointers
    this->adjMat = new std::pair<int, int>*[this->n];

    //new 2d array(matrix) of <distance, edge type>
    for(int i = 0; i < this->n; i++) {
        this->adjMat[i] = new std::pair<int, int>[n];
        for(int j = 0; j < this->n; j++) {
            //mark all edges as undiscovered(UN)
            (this->adjMat[i][j]).second = -1;
        }
    }
    
    //new array of vertices
    this->v = new vertex[n];
    
    //0: seattle
    //1: san francisco
    //2: denver
    //3: chicago
    //4: boston
    //5: new york
    //6: los angeles
    //7: kansas city
    //8: atlanta
    //9: dallas
    //10: houston
    //11: miami
    for(int i = 0; i < n; i++) {
        this->v[i].id = i;
        this->v[i].city = this->cities[i];
        this->v[i].visited = false;
    }
}
//end of constructor

//destructor
graph::~graph() {
    //delete matrix
    for(int i = 0; i < this->n; i++) {
        delete[] this->adjMat[i];
    }

    //delete array of pointers
    delete[] this->adjMat;
    
    //delete vertex array
    delete[] this->v;
}
//end of destructor

//addEdge()
void graph::addEdge(const int& start, const int& end, const int& weight) {
    //add weight to both [start][end] and [end][start]
    (this->adjMat[start][end]).first = weight;
    (this->adjMat[end][start]).first = weight;
}
//end of addEdge()

//BFS
std::vector<edge> graph::BFS(const std::string& name) {
    //start id
    int start = this->at(name);
    
    //visited vector to keep track of edges that have been visited
    std::vector<bool> visited(this->size(), false);
    
    //vector of edges: stores all discovered edges in BFS order
    std::vector<edge> info;
    
    //set start vertex to visited
    visited[start] = true;
    this->v[start].visited = true;
    
    //push back start vertex with distance 0
    this->order.push_back(std::make_pair(this->v[start], 0));
    
    //number of vertices in previous levels
    size_t size = 0;
    
    //iterate through each vertex at a given level
    int j = 0;
    
    //while all cities haven't been visited
    while(this->order.size() < this->n) {
        //set current vertex to first element in the order vector
        int curr = this->order[j].first.id;
        
        //for all adjacent edges to vertex curr
        for(int i = 0; i < this->n; i++) {
            //if curr has an edge connecting curr and i
            if(hasBFSPath(curr, i) != 0) {
                //the vertex hasn't been visited
                if(!(visited[i])) {
                    //add edge to info vector
                    info.push_back(edge(this->v[curr], this->v[i], (this->adjMat[curr][i]).first));
                    
                    //add vertex and distance to order vector
                    this->order.push_back(std::make_pair(this->v[i], (this->adjMat[curr][i]).first));
                    
                    //set current vertex to visited
                    this->v[curr].visited = true;
                    
                    //set edge at [curr][i] to discovered(DI)
                    (this->adjMat[curr][i]).second = (this->adjMat[i][curr]).second = 1;
                    
                    //set i'th visited vector to true
                    visited[i] = true;
                }
            }
        }
        
        //sort info vector excluding start distance (0)
        if(size == 0) {
            std::sort(info.begin(), info.end(), compare);
        }
        else {
            std::sort(info.begin() + (size - 1), info.end(), compare);
        }
        
        //sort the current "level" of the order vector
        std::sort(this->order.begin() + size, this->order.end(), sortByDist);
        
        //add current vertices to size to "skip" to the next level on the next sort
        size = this->order.size();
        
        //iterate j to BFS visit all vertices in the next "level"
        j++;
    }
    
    //all nonzero edges that were undiscovered are cross edges
    for(int i = 0; i < this->n; i++) {
        for(int j = 0; j < this->n; j++) {
            if((this->adjMat[i][j]).first != 0 && (this->adjMat[i][j]).second == -1) {
                (this->adjMat[j][i]).second = (this->adjMat[i][j]).second = 0;
            }
        }
    }
    
    //set discoveredEdges to point to info
    this->discoveredEdges = info;
    
    //return info vector
    return info;
}
//end of BFS

//printAdjMatrix()
void graph::printAdjMatrix() {
    //for each element in the adjacency matrix
    for(int i = 0; i < this->n; i++) {
        for(int j = 0; j < this->n; j++) {
            
            //set edgeType
            std::string edgeType;
            switch((adjMat[i][j]).second) {
                //undiscovered
                case -1:
                    edgeType = "UN";
                    break;
                //cross
                case 0:
                    edgeType = "CR";
                    break;
                //discovered
                case 1:
                    edgeType = "DI";
                    break;
                //error
                default:
                    edgeType = "error";
                    break;
            }
            //print in format [distance, edge type]
            //setw(4) to make matrix uniform: left justified
            std::cout << "[" << std::setw(4) << std::left << std::setfill(' ') << (adjMat[i][j]).first << ", " << edgeType << "] ";
        }
        //2 lines of space between rows
        std::cout << std::endl << std::endl << std::endl;
    }
}
//end of printAdjMatrix()

//prints order of cities to visit using BFS
void graph::printOrder() {
    //order
    int i = 1;
    //print order vector (cities)
    for(auto& x : this->order) {
        std::cout << i << ": " << x.first.city << std::endl;
        i++;
    }
    
    std::cout << std::endl;
    
}
//end of printOrder()

//printDiscoveredEdges()
void graph::printDiscoveredEdges() {
    //adding distances string
    std::string addition = "";
    
    //total distance traveled
    int sum = 0;
    
    //iterate through dists vector
    for(const auto& x : this->discoveredEdges) {
        //print distance between start and end city
        std::cout << x.start.city << " and " << x.end.city << ": " << x.weight << " mi" << std::endl;
        
        //add weight to total distance
        sum += x.weight;
        
        //add weight to total distance string
        addition += std::to_string(x.weight) + " + ";
    }
    //omit extraneous " + "
    addition = addition.substr(0, addition.length() - 3);
    
    //set distanceInfo to addition string and total distance
    this->distanceInfo = std::pair(addition, sum);
    
    std::cout << std::endl;
}
//end of printDiscoveredEdges()

//printCrossEdges()
void graph::printCrossEdges() {
    //map of cross edges
    std::vector<int> visited;
    for(int i = 0; i < this->n; i++) {
        for(int j = 0; j < this->n; j++) {
            if(((this->adjMat[i][j]).second == 0) && (std::find(visited.begin(), visited.end(), (this->adjMat[i][j]).first) == visited.end())) {
                visited.push_back((this->adjMat[i][j]).first);
                std::cout << (this->v[i]).city << " and " << (this->v[j]).city << ": " << (this->adjMat[i][j]).first << " mi" << std::endl;
            }
        }
    }
    
    std::cout << std::endl;
}
//end of printCrossEdges()

//printLvlOrder()
void graph::printLvlOrder() {
    //lvl
    int lvl = 0;
    for(int i = 0; i < this->order.size(); i++) {
        std::cout << "level " << lvl << ": " << this->order[i].first.city << std::endl;
        if(this->order[i].first.city == "Dallas" || this->order[i].first.city == "Los Angeles" || this->order[i].first.city == "New York") {
            lvl++;
        }
    }
    std::cout << std::endl;
}
//end of printLvlOrder()

//printTotalDist()
void graph::printTotalDist() {
    //print addition string and total distance taveled
    std::cout << this->distanceInfo.first << std::endl;
    std::cout << "total distance traveled: " << this->distanceInfo.second << " mi" << std::endl;
}
//end of printTotalDist()

//ASSIGNMENT 12
//minDistance()
int graph::minDistance(int dist[], bool sptSet[]) {
    int min = INT_MAX;
    int minIndex = -1;
    
    for(int i = 0; i < this->n; i++) {
        if((sptSet[i] == false) && dist[i] <= min) {
            min = dist[i];
            minIndex = this->v[i].id;
        }
    }
    
    return minIndex;
}
//end of minDistance()

//djikstra()
void graph::djikstra(const std::string& name) {
    int start = this->at(name);
    
    //distance from start to vertex i
    int dist[this->n];
    
    //true if vertex is in shortest path tree, false otherwise
    bool sptSet[this->n];
    
    //array to store djikstra path
    int path[this->n];
    
    //initialize arrays to infinity and false respectively
    for(int i = 0; i < this->n; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = false;
        path[i] = -1;
    }
    
    //distance from start to itself is 0
    dist[start] = 0;
    
    //shortest path for all vertices
    for(int i = 0; i < this->n - 1; i++) {
        //minimum distance vertex by calling helper function minDistance()
        int temp = this->minDistance(dist, sptSet);
        
        //set picked vertex as true
        sptSet[temp] = true;
        
        //update distance value of adjacent vertices of the picked vertex
        for(int j = 0; j < this->n; j++) {
            //update dist[j] if:
            //it's not in stpSet
            //there's an edge from temp to j
            //the total weight of the path from temp to j is shorter than the current dist[j]
            if(!(sptSet[j]) && (this->adjMat[temp][j]).first && (dist[temp] != INT_MAX) && (dist[temp] + (this->adjMat[temp][j]).first < dist[j])) {
                //add vertex id to path
                path[j] = this->v[temp].id;
                
                //add distance to current
                dist[j] = dist[temp] + (this->adjMat[temp][j]).first;
            }
        }
    }
    
    //print djikstra order and path starting at [start city]
    printDjikstra(dist, name, path);
}
//end of djikstra()

//printDjikstra()
void graph::printDjikstra(const int dist[], const std::string& name, int path[]) {
    //iterate through dist array
    for(int i = 0; i < this->n; i++) {
        //reset path string
        std::string pathStr = "";
        
        //format: [start city] to [end city]: [shortest distance] mi
        std::cout << name << " to " << this->v[i].city << ": " << dist[i] << " mi" << std::endl;
        
        //recursively build path from [start city] to [end city]
        printPath(path, i, pathStr);
        
        //format: path from [start city] to [end city]: [start->next->next->...->end]
        std::cout << "path from " << name << " to " << this->v[i].city << ": " << pathStr.substr(0, pathStr.length() - 2) << std::endl << std::endl;
    }
}

void graph::printPath(int path[], int i, std::string& pathStr) {
    //BASE CASE
    //if id is start city
    if(i == -1) {
        return;
    }
    //RECURSIVE CASE
    else {
        //recursively build path
        printPath(path, path[i], pathStr);
        //add to path string
        //format: [start]->[next]->...->[end]
        pathStr += (this->v[i].city + "->");
    }
    return;
}
