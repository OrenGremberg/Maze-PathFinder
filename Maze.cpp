//
// Created by oren Gremberg on 2/3/20.
//

#include "Maze.hpp"

Maze::Maze(string inputFileName) {
    mazeStream.open(inputFileName, ios_base::in);
    if (!mazeStream.is_open()) {
        std::cout << "Unable to open the input file ->" << inputFileName << "<- that contains pairs of words.\n";
        exit(2);
    }
    cout << "file opened successfully" << inputFileName << endl;
    //initiate string var and use it to add rows into vector
    string word;
    vector<string> rows;
    while (mazeStream >> word) {
        for (int i = 0; i < word.size(); i++) {
            rows.push_back(string(1, word.at(i)));
        }
        maze.push_back(rows);
        rows.clear();

    }
    for(int i = 0; i < maze.size(); i++){
        vector<bool> usedrow;
        for(int j = 0; j < maze[1].size(); j++)
            usedrow.push_back(false);
        used.push_back(usedrow);
    }
}


vector<tuple<int, int>> Maze::Start_End() {
    vector<tuple<int, int>> startendpts;
    //cout << "here are the start and end pts of the maze:" << endl;
    //check first row
    for (int i = 0; i < maze[0].size(); i++) {
        if (maze[0].at(i) == "0")
            //maze[0].at(i) = "S";
            startendpts.push_back(make_tuple(0, i));
        //cout << maze[0][i];
    }
    //cout << endl;
    //check last row
    for (int i = 0; i < maze[maze.size() - 1].size(); i++) {
        if (maze[maze.size() - 1].at(i) == "0")
            //maze[maze.size() - 1].at(i) = "S";
            startendpts.push_back(make_tuple(maze.size()-1, i));
        //cout << maze[maze.size() - 1][i];
    }
    //cout << endl;
    for (int i = 0; i < maze.size(); i++) { //check every row
        if (maze.at(i)[0] == "0")
            startendpts.push_back(make_tuple(i,0));

        }
        //cout << maze.at(i)[0];

    //cout << endl;
    //check last col
    for (int i = 0; i < maze.size(); i++) { //check every row
            if (maze.at(i)[maze.at(0).size() - 1] == "0")
                //maze.at(i)[maze.at(0).size() - 1] = "S";
                startendpts.push_back(make_tuple(i,maze.at(i).size() - 1));
        }
        //cout << maze.at(i)[maze.at(0).size() - 1];
    for(int i  = 0; i < startendpts.size() - 1; i++)
        used.at(get<1>(startendpts[i])) [get<1>(startendpts[i])] = true;

    return startendpts;
}

tuple<int, int> Maze::isadjacent(tuple<int, int>startpt) {
    // find the adjacent cells , use x for row and y for column
    //start by looking right
    //test: cout<< "here is the next cell in the path"<< endl;
    int right_x = get<0>(startpt);
    int right_y = get<1>(startpt) + 1;
    if (right_y > maze[0].size())
        right_y -= 1;
    //look up next
    int up_x = get<0>(startpt) - 1;
    if (up_x < 0)
        up_x += 1;
    int up_y = get<1>(startpt);
    //look left
    int left_x = get<0>(startpt);
    int left_y = get<1>(startpt) - 1;
    if (left_y < 0)
        left_y += 1;
    // finally look down
    int down_x = get<0>(startpt) + 1;
    if (down_x > maze.size())
        down_x -= 1;
    int down_y = get<1>(startpt);

    //check the adjacent cells right, up, left, down
    //right
    // then check to make sure it wast used as well as eqaul to 0.
    if (maze.at(right_x)[right_y] == "0" and !used.at(right_x)[right_y]) {
        used.at(right_x)[right_y] = true;
        return make_tuple(right_x, right_y);
    }
    if (maze.at(up_x)[up_y] == "0" and !used.at(up_x)[up_y]) {
        used.at(up_x)[up_y] = true;
        return make_tuple(up_x, up_y);
    }
    if (maze.at(left_x)[left_y] == "0" and !used.at(left_x)[left_y]) {
        used.at(left_x)[left_y] = true;
        return make_tuple(left_x, left_y);
    }
    if (maze.at(down_x)[down_y] == "0" and !used.at(down_x)[down_y]) {
        used.at(down_x)[down_y] = true;
        return make_tuple(down_x, down_y);
    }
    return make_tuple(0, 0);
}

vector<tuple<int, int>> Maze::Pathfromto(tuple<int, int>){
    // logic of this function should be similar to lab 1 but not the same
    //start by clearing thepath and reseting all used. path is like our ladder.
    thepath.clear();
    Resetused();
    //intiatiate start point and push it into the path
    startendpts = Start_End();
    thepath.push_back(startendpts[0]);
    // make used at first point equal to true.
    used[get<1>(startendpts[0])][get<0>(startendpts[0])] = true;
    //must do a fail check
    tuple<int, int>wall =  make_tuple(0,0);
    //start going through the path. make sure to check for current = target and that nxt cell is clear
    // while our last element is not equal to our target element
    while(thepath.back() != startendpts[1]) {
        tuple<int, int> nxtcell = isadjacent(thepath.back());
        //check if wall. if it is then pop back until we return to point and find new successor.
        while (nxtcell == wall) {
            thepath.pop_back();
            nxtcell = isadjacent(thepath.back());
            //check empty path and return if it is.
            if (thepath.empty())
                return thepath;
        }
        //if not a wall add it to thepath
        thepath.push_back(nxtcell);
    }
    //finally return the final path.
    return thepath;

}

void Maze::Resetused(){
    for(int i = 0; i < used.size(); i++){
        for(int j = 0; j< used[i].size(); j++){
            used[i][j] = false;
        }
    }

}

void Maze::printMaze(){

    for( int i = 0; i < maze.size(); i++) {
        for (int j = 0; j < maze[i].size(); j++) {
            cout <<  maze.at(i)[j];
        }
        cout << endl;
    }
}

void Maze::PrintSolvedMaze(){
    cout << "here is the solved maze: " << endl;
    for( int i = 0; i < thepath.size(); i++) {
        maze[get<0>(thepath[i])] [get<1>(thepath[i])] = " ";
        }
    printMaze();

}


Maze::~Maze(){
    if(mazeStream.is_open())
        mazeStream.close();

}


