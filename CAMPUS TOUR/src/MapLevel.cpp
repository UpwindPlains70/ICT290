#include "MapLevel.h"

LevelMap::LevelMap(int x, int z)
{
	X = x;
	Z = z;
	array = new int* [X];
	for (int i = 0; i < X; i++)
	{
		array[i] = new int[Z];
	}
	/*
	for (int i = 0; i < X; i++)
	{
		for (int j = 0; j < Z; j++)
		{
			array[i][j] = 0;
		}
	}
	*/
}

/*LevelMap::LevelMap()
{
	array = nullptr;
}*/

int LevelMap::GetX() const
{ 
	return X;
}

int LevelMap::GetZ() const
{ 
	return Z; 
}

int LevelMap::GetValue(int x, int z) const 
{ 
	return array[x][z]; 
}

void LevelMap::SetValue(int x, int z, int value)
{ 
	array[x][z] = value; 
}

LevelMap::LevelMap(const LevelMap& copy)
{
	if(this != &copy)
		*this = copy;
}

void LevelMap::CopyMap(const LevelMap& copy)
{
	X = copy.GetX();
	Z = copy.GetZ();
	array = new int* [X];
	for (int i = 0; i < X; i++)
	{
		array[i] = new int[Z];
	}
	for (int i = 0; i < X; i++)
	{
		for (int j = 0; j < Z; j++)
		{
			array[i][j] = copy.array[i][j];
		}
	}
}

const LevelMap& LevelMap::operator =(const LevelMap& copy)
{
	if (this != &copy)
	{
		CopyMap(copy);
	}
	return *this;
}

LevelMap::~LevelMap()
{
	if (array == nullptr)
	{
		return;
	}
	for (int i = 0; i < X; i++)
	{
		delete[] array[i];
	}
	delete[] array;
}