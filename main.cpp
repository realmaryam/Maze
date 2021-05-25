#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "room.h"


int getAdjacentRoom(int roomNumber, int size);
int mazeRow(int roomNumber, int size);
int mazeColumn(int roomNumber, int size);
void openDoors(Room *room1, Room *room2, int size);
bool checkComplete(Room **maze, int size);
void updatePaths(Room **maze, int size, int oldPath, int newPath);
void DFS(Room **maze , int size);
std::vector<Room>& nextPath(Room **maze, int size , std::pair<int,int> , std::vector<Room>& way );

int main(){
	int size;
    //srand((unsigned)time(0));
	std::cout << "Input the desired side length for the maze (-1 for random): ";
	std::cin >> size;

	while(size <= 3 && size != -1){
		std::cin.clear();
		std::cin.ignore();
		std::cout << "Invalid size. Size must be a positive integer greater";
		std::cout << " than 3: ";
		std::cin >> size;
	}
	if(size == -1){
		srand((unsigned)time(0));
		size = rand() % 20 + 4;
		std::cout << "Size randomly selected to be " << size << "\n";
	} 

	// create 2D array to be our maze
	Room** maze = new Room*[size];
	for(int i = 0; i < size; i++){
		maze[i] = new Room[size];
	}

	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			maze[i][j].setRoomNumber((i * size) + j);
			maze[i][j].setPathNumber((i * size) + j);
		}
	}

	while(!checkComplete(maze, size))
	{
		int roomCount = size * size;
		int room = rand() % roomCount;
		int adjacentRoom = getAdjacentRoom(room, size);
		int row1 = mazeRow(room, size);
		int col1 = mazeColumn(room, size);
		int row2 = mazeRow(adjacentRoom, size);
		int col2 = mazeColumn(adjacentRoom, size);
		if(maze[row1][col1].getPathNumber()!= maze[row2][col2].getPathNumber())
		{
			openDoors(&maze[row1][col1], &maze[row2][col2], size);
			if(maze[row1][col1].getPathNumber() > maze[row2][col2].getPathNumber())
			{
				updatePaths(maze, size, maze[row1][col1].getPathNumber(),
				maze[row2][col2].getPathNumber());
			}
			else {
				updatePaths(maze, size, maze[row2][col2].getPathNumber(),
				maze[row1][col1].getPathNumber());
			}
		}
	} 
	// Open the north door of Room 0 and the South door of the last room
	maze[0][0].setNorth(1);
	maze[size - 1][size - 1].setSouth(1);
	
	std::cout << "\nCurrent Maze:\n";

	for(int i = 0; i < size; i++){
		if(maze[0][i].getNorth() == 0){
			std::cout << "+---";
		} else {
			std::cout << "+   ";
		}
	}
	std::cout << "+\n";
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			if(maze[i][j].getWest() == 0){
				std::cout << "|   ";	
			} else {
				std::cout << "    ";
			}
		}
		std::cout << "|\n";
		for(int j = 0; j < size; j++){
			if(maze[i][j].getSouth() == 0){
				std::cout << "+---";
			} else {
				std::cout << "+   ";
			}
		}
		std::cout << "+\n";
	}
	
	DFS(maze , size);

	for(int i = 0; i < size; i++){
		delete[] maze[i];
	}
	delete[] maze;
	
	return 0;
}

int getAdjacentRoom(int roomNumber, int size){
	int adj, maxNumber, delta, addSub;
	bool valid = 0;
	maxNumber = (size * size) - 1;

	while(valid == 0){
		valid = 1;
		delta = rand() % 2;
		addSub = rand() % 2;
		if (delta == 0){
			delta = size;
		}
		if(addSub == 1){
			adj = roomNumber + delta;
		} else {
			adj = roomNumber - delta;
		}
		// 4 special cases where it would not be adjacent
		if((adj - roomNumber == 1) && (adj % size == 0)){
			valid = 0;
		}
		if((roomNumber - adj == 1) && (roomNumber % size == 0)){
			valid = 0;
		}
		if((adj < 0) || (adj > maxNumber)){
			valid = 0;
		}
	}
	return adj;
}

int mazeRow(int roomNumber, int size){
	return roomNumber / size;
}

int mazeColumn(int roomNumber, int size){
	return roomNumber % size;
}

void openDoors(Room *room1, Room *room2, int size){
	if(room1->getRoomNumber() - room2->getRoomNumber() == 1){
		room1->setWest(1);
		room2->setEast(1);
	}
	if(room2->getRoomNumber() - room1->getRoomNumber() == 1){
		room2->setWest(1);
		room1->setEast(1);
	}
	if(room1->getRoomNumber() - room2->getRoomNumber() == size){
		room1->setNorth(1);
		room2->setSouth(1);
	}
	if(room2->getRoomNumber() - room1->getRoomNumber() == size){
		room2->setNorth(1);
		room1->setSouth(1);
	}
}

bool checkComplete(Room **maze, int size){
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			if(maze[i][j].getPathNumber() != 0){
				return false;
			}
		}
	}
	return true;
}

void updatePaths(Room **maze, int size, int oldPath, int newPath){
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			if(maze[i][j].getPathNumber() == oldPath){
				maze[i][j].setPathNumber(newPath);
			}
		}
	}
}

void DFS( Room** maze , int size )
{
    std::vector<Room> way;
    int x {} , y {};
	way.push_back(maze[0][0]);
    way = nextPath( maze, size , {0 ,0} , way );
    
	std::cout << "\nDFS method solved Maze:\n"<<way.size()<<std::endl;

	int check {};
	for(int i = 0; i < size; i++){
		if(maze[0][i].getNorth() == 0){
			std::cout << "+---";
		} else {
			std::cout << "+ * ";
		}
	}
	std::cout << "+\n";
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++)
		{	
			check =0;
			for( auto it : way)
			{	
				if(it == maze[i][j])
				{
					check =1;
					if(maze[i][j].getWest() == 0)
					{
						std::cout << "| * ";	
					} else {
						std::cout << "  * ";
					}
					break;
				}
			}
			if(!check)
			{
				if(maze[i][j].getWest() == 0)
				{

					std::cout << "|   ";	
				} else {
					std::cout << "    ";
				}
			}
		}
		std::cout << "|\n";
		for(int j = 0; j < size; j++)
		{
			for( auto it : way)
			{	
				check =1;
				if(it == maze[i][j])
				{
					if(maze[i][j].getSouth() == 0)
					{
						std::cout << "+---";
					} else {
						std::cout << "+ * ";
					}
					break;
				}
			}
			if(!check)
			{
				if(maze[i][j].getSouth() == 0)
				{
					std::cout << "+---";
				} else {
					std::cout << "+   ";
				}
			}
		}
		std::cout << "+\n";
	}





}

std::vector<Room>& nextPath(Room **maze , int size, std::pair<int,int> location , std::vector<Room>& way )
{
    int x {} , y {};
    y = location.first;
    x = location.second;
	int final { way.back().getRoomNumber()};
    maze[y][x].setVisited(1);
    // if( x == size-1 && y == size-1 )
    // {
	// 	std::cout<<"im in final\n";

    //     return way;
    // }
	if(final ==(size*size)-1)
	{
		//std::cout<<"swwww\n";
		return way;
	}
		
	if(final !=(size*size)-1)
	{
	    if( y!=0 && maze[y][x].getNorth() && !maze[y-1][x].getVisited() )
	    {
		//std::cout<<"im in0\n";
	        maze[y-1][x].flag = 0;
	        way.push_back(maze[y-1][x]);
	        way = nextPath(maze , size , {y-1 , x},way );
			if(way.back().getRoomNumber()==(size*size)-1)
				return way;
	    }

    	if( x!=size-1 && maze[y][x].getEast() && !maze[y][x+1].getVisited() )
    	{
			//std::cout<<"im in1\n";
        	maze[y][x+1].flag = 1 ; 
        	way.push_back(maze[y][x+1]);
        	way = nextPath(maze, size , {y , x+1}, way );
			if(way.back().getRoomNumber()==(size*size)-1)
				return way;
    	}

    	if( y!=size-1 && maze[y][x].getSouth() && !maze[y+1][x].getVisited() )
    	{
			//std::cout<<"im in2\n";
        	maze[y+1][x].flag = 2 ; 
        	way.push_back(maze[y+1][x]);
        	way = nextPath(maze, size , {y+1 , x}, way );
			if(way.back().getRoomNumber()==(size*size)-1)
				return way;
    	}
    

    	if( x!=0 && maze[y][x].getWest() && !maze[y][x-1].getVisited() )
    	{
			//std::cout<<"im in3\n";
        	maze[y+1][x].flag = 3 ; 
        	way.push_back(maze[y][x-1]);
        	way = nextPath(maze, size , {y , x-1}, way );
			if(way.back().getRoomNumber()==(size*size)-1)
				return way;
    	}
    	// else{ std::cout<<"im in pop\n";
		// 	if(std::cout<<"else if0\n";y==0 && maze[y][x-1].getVisited() && maze[y+1][x].getVisited() && maze[y][x+1].getVisited())
		// 		{std::cout<<"else if0\n";
		// 			way.pop_back();
		// 			return way;
		// 		}
		// 	if(std::cout<<"else if1\n";y==size-1 && maze[y][x-1].getVisited() && maze[y-1][x].getVisited() && maze[y][x+1].getVisited())
		// 		{std::cout<<"else if1\n";
		// 			way.pop_back();
		// 			return way;
		// 		}
		// 	if(std::cout<<"else if2\n";x==0 && maze[y-1][x].getVisited() && maze[y+1][x].getVisited() && maze[y][x+1].getVisited())
		// 		{std::cout<<"else if2\n";
		// 			way.pop_back();
		// 			return way;
		// 		}
		// 	if(std::cout<<"else if3\n";x==size-1 && maze[y][x-1].getVisited() && maze[y+1][x].getVisited() && maze[y-1][x].getVisited())
		// 		{std::cout<<"else if3\n";
		// 			way.pop_back();
		// 			return way;
		// 		}
		// 	else if (std::cout<<"im in else";  maze[y][x-1].getVisited() && maze[y+1][x].getVisited() &&
        // 		            maze[y][x+1].getVisited() && maze[y-1][x].getVisited())
		
    		{
				//std::cout<<"im in5\n";
        		way.pop_back();
				return way;
        // if(maze[y][x].flag==0)
        // {
        //     way = nextPath(maze, size , {y+1 , x}, way);
        // }
        // if(maze[y][x].flag==1)
        //     way = nextPath(maze, size , {y , x-1}, way);
        // if(maze[y][x].flag==2)
        //     way = nextPath(maze, size , {y-1 , x}, way);
        // if(maze[y][x].flag==3)
        //     way = nextPath(maze, size , {y , x+1}, way);
    	//	}
		}
	}
}