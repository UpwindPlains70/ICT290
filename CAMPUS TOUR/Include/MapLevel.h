#pragma once
class LevelMap
{
private:
	// 0 = empty, 1 = wall, 2 = ally, 3 = enemy.
	int** array;
	int X;
	int Z;
	void CopyMap(const LevelMap& copy);
public:
	//LevelMap();
	LevelMap(int x, int z);
	int GetX() const;
	int GetZ() const;
	int GetValue(int x, int z) const;
	void SetValue(int x, int z, int value);
	LevelMap(const LevelMap& copy);
	~LevelMap();
	const LevelMap& operator =(const LevelMap& copy);
};

