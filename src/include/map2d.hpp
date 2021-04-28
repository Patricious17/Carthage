#ifndef HEADER_MAP2D
#define HEADER_MAP2D

#include <iostream>

#include "basicTypes.hpp"

class Map2D {
public:
	Map2D();
	~Map2D();
private:
};

template <class T>
class OccupancyGrid : public Map2D {
public:

private:
Matrix<T> grid;
};

using OccupancyGridBool = OccupancyGrid<bool>;
using OccupancyGridFloat  = OccupancyGrid<float>;
using OccupancyGridInt = OccupancyGrid<int>;
#endif 
