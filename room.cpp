//implementation of the room class
#include "room.h"

Room::Room()
{
	roomNumber = 0;
	north = 0;
	south = 0;
	east = 0;
	west = 0;
	visited = 0;
	parent = 0;
	level = -1;
}

void Room::setRoomNumber(int x)
{
	roomNumber = x;
}

void Room::setPathNumber(int x)
{
	pathNumber = x;
}

void Room::setNorth(bool x)
{
	north = x;
}

void Room::setSouth(bool x)
{
	south = x;
}

void Room::setEast(bool x)
{
	east = x;
}

void Room::setWest(bool x)
{
	west = x;
}

void Room::setVisited(bool x)
{
	visited = x;
}

void Room::setParent(int x)
{
	parent = x;
}

void Room::setLevel(int x)
{
	level = x;
}

int Room::getRoomNumber()
{
	return roomNumber;
}

int Room::getPathNumber()
{
	return pathNumber;
}

bool Room::getNorth()
{
	return north;
}

bool Room::getSouth()
{
	return south;
}

bool Room::getEast()
{
	return east;
}

bool Room::getWest()
{
	return west;
}

bool Room::getVisited()
{
	return visited;
}

int Room::getParent()
{
	return parent;
}

int Room::getLevel()
{
	return level;
}