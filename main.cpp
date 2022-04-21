#include "graph.h"
//N is the number of cities, in this case 12
#define N 12

int main() {
    //graph with N(12) vertices
    graph g(N);

    //build graph
    g.addEdge(0, 1, 807);
    g.addEdge(0, 2, 1331);
    g.addEdge(0, 3, 2097);
    
    g.addEdge(1, 2, 1267);
    g.addEdge(1, 6, 381);
    
    g.addEdge(2, 3, 1003);
    g.addEdge(2, 6, 1015);
    g.addEdge(2, 7, 599);
    
    g.addEdge(3, 4, 983);
    g.addEdge(3, 5, 787);
    g.addEdge(3, 7, 533);
    
    g.addEdge(4, 5, 214);

    g.addEdge(5, 7, 1260);
    g.addEdge(5, 8, 888);
    
    g.addEdge(6, 7, 1663);
    g.addEdge(6, 9, 1435);
    
    g.addEdge(7, 8, 864);
    g.addEdge(7, 9, 496);
    
    g.addEdge(8, 9, 781);
    g.addEdge(8, 10, 810);
    g.addEdge(8, 11, 661);
    
    g.addEdge(9, 10, 239);
    
    g.addEdge(10, 11, 1187);
    
    //ASSIGNMENT 12
    
    std::cout <<
    "**************************************************************************************" << std::endl <<
    "Assignment 12 - Djikstra's Algorithm & MST (Minimum Spanning Tree)" << std::endl <<
    "--------------------------------------------------------------------------------------" << std::endl <<
    "This program has two parts." << std::endl <<
    "In Part A, we use Djikstra's Algorithm to determine the" << std::endl <<
    "shortest path from Dallas to all the other cities. This algorithm uses an adjacency" << std::endl <<
    "matrix representation of a graph." << std::endl <<
    "In Part B, we determine the MST (minimum spanning tree) starting at Dallas, identifying" << std::endl <<
    "all edges and total mileage." << std::endl <<
    "--------------------------------------------------------------------------------------" << std::endl <<
    "PROCESSING" << std::endl <<
    "--------------------------------------------------------------------------------------" << std::endl <<
    "graph - used for part A of the assignment (Djikstra's)" << std::endl << std::endl <<

    "OUTPUT" << std::endl <<
    "--------------------------------------------------------------------------------------" << std::endl <<
    "(see below)" << std::endl <<
    "--------------------------------------------------------------------------------------" << std::endl <<
    "CS1D  MW 2:30 - 5 PM Lebowitz" << std::endl <<
    "Programmed by : Warren Kim & Cyrus Azad" << std::endl <<
    "04-25-22" << std::endl <<
    "**************************************************************************************" << std::endl << std::endl <<std::endl;
    
    std::cout << "============================" << std::endl;
    std::cout << "PART A: Djikstra's Algorithm" << std::endl;
    std::cout << "============================" << std::endl << std::endl;

    //call djikstra's algorithm
    g.djikstra("Dallas");
    //END OF ASSIGNMENT 12

    //ASSIGNMENT 11
    /*
    //print adjacency matrix before BFS
    std::cout << "adjacency matrix before BFS:" << std::endl;
    g.printAdjMatrix();
    
    //perform BFS
    std::cout << "performing BFS starting at Dallas:" << std::endl
              << "(chooses edge with the smallest mileage)" << std::endl << std::endl;
    g.BFS("Dallas");
    
    //print adjacency matrix after BFS
    std::cout << "adjacency matrix after BFS:" << std::endl;
    g.printAdjMatrix();
    
    //print BFS order
    std::cout << "BFS order of cities" << std::endl;
    g.printOrder();
    
    //print BFS level order
    std::cout << "BFS level order of cities" << std::endl;
    g.printLvlOrder();
    
    //print discovered edges info
    std::cout << "outputting discovered edges:" << std::endl
              << "(format: \"[start city] and [end city]: [edge weight]\" mi)" << std::endl;
    g.printDiscoveredEdges();
    
    //print all cross edges
    std::cout << "outputting all cross edges:" << std::endl
              << "(format: \"[start city] and [end city]: [edge weight]\" mi)" << std::endl;
    g.printCrossEdges();
    
    //print distance info
    std::cout << "outputting total distance:" << std::endl;
    g.printTotalDist();
    */
    //END OF ASSIGNMENT 11
    
    return 0;
}
/*
 OUTPUT ASSIGNMENT 12
 
 **************************************************************************************
 Assignment 12 - Djikstra's Algorithm & MST (Minimum Spanning Tree)
 --------------------------------------------------------------------------------------
 This program has two parts.
 In Part A, we use Djikstra's Algorithm to determine the
 shortest path from Dallas to all the other cities. This algorithm uses an adjacency
 matrix representation of a graph.
 In Part B, we determine the MST (minimum spanning tree) starting at Dallas, identifying
 all edges and total mileage.
 --------------------------------------------------------------------------------------
 PROCESSING
 --------------------------------------------------------------------------------------
 graph - used for part A of the assignment (Djikstra's)

 OUTPUT
 --------------------------------------------------------------------------------------
 (see below)
 --------------------------------------------------------------------------------------
 CS1D  MW 2:30 - 5 PM Lebowitz
 Programmed by : Warren Kim & Cyrus Azad
 04-25-22
 **************************************************************************************


 ============================
 PART A: Djikstra's Algorithm
 ============================

 Dallas to Seattle: 2426 mi
 path from Dallas to Seattle: Dallas->Kansas City->Denver->Seattle

 Dallas to San Francisco: 1816 mi
 path from Dallas to San Francisco: Dallas->Los Angeles->San Francisco

 Dallas to Denver: 1095 mi
 path from Dallas to Denver: Dallas->Kansas City->Denver

 Dallas to Chicago: 1029 mi
 path from Dallas to Chicago: Dallas->Kansas City->Chicago

 Dallas to Boston: 1883 mi
 path from Dallas to Boston: Dallas->Atlanta->New York->Boston

 Dallas to New York: 1669 mi
 path from Dallas to New York: Dallas->Atlanta->New York

 Dallas to Los Angeles: 1435 mi
 path from Dallas to Los Angeles: Dallas->Los Angeles

 Dallas to Kansas City: 496 mi
 path from Dallas to Kansas City: Dallas->Kansas City

 Dallas to Atlanta: 781 mi
 path from Dallas to Atlanta: Dallas->Atlanta

 Dallas to Dallas: 0 mi
 path from Dallas to Dallas: Dallas

 Dallas to Houston: 239 mi
 path from Dallas to Houston: Dallas->Houston

 Dallas to Miami: 1426 mi
 path from Dallas to Miami: Dallas->Houston->Miami
 */