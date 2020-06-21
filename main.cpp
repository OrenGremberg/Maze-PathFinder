#include <iostream>
#include "Maze.hpp"

int main() {

    Maze testMaze("exampleMaze.txt");
    //print the maze
    cout << "here is the maze:" << endl;
    testMaze.printMaze();
    //returns the start and end of the maze
    cout << "here are the start and end pts of the maze:" << endl;
    vector<tuple<int, int>> startendpts = testMaze.Start_End();
    for(int i = 0; i < startendpts.size(); i++){
        cout << "(" << get<0>(startendpts[i]) << "," << get<1>(startendpts[i]) << ")" << endl;
    }
    //returns the successor
    cout<< "here is the next cell in the path"<< endl;
    tuple<int, int> nxtcell = testMaze.isadjacent(startendpts[0]);
    cout << "(" << get<0>(nxtcell) << "," << get<1>(nxtcell) << ")" << endl;
    //print the path as points
    cout << "here is my path" << endl;
    vector<tuple<int, int>> thepath = testMaze.Pathfromto(startendpts[0]);
    for(int i = 0; i < thepath.size(); i++){
        cout << "(" << get<0>(thepath[i]) << "," << get<1>(thepath[i]) << ")" << endl;
    }
    //print final maze

    testMaze.PrintSolvedMaze();


    return(0);
}
