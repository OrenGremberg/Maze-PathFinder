//
// Created by oren Gremberg on 2/3/20.
//

#ifndef UNTITLED_MAZE_H
#define UNTITLED_MAZE_H
#include<iostream>
#include<fstream>
#include<vector>
#include<tuple>
using namespace std;

class Maze{
public:
    Maze(string inputFileName);
    vector<tuple<int, int>> Start_End();
    tuple<int, int>isadjacent(tuple<int, int>);
    vector<tuple<int, int>>Pathfromto(tuple<int, int>);
    void PrintSolvedMaze();
    void Resetused();
    void printMaze();




    ~Maze();


private:
    // our maze
    vector<vector<string>> maze;
    // holds two ints row and col
    vector<tuple< int, int>> startendpts;
    // holds true false for each pt. in maze
    vector<vector<bool>> used;
    // stores the path as a vector of points.
    vector<tuple<int, int>> thepath;
    ifstream mazeStream;






    //void printMaze();


};




#endif //UNTITLED_MAZE_H
