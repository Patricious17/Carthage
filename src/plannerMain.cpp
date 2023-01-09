#include "plannerMain.hpp"
//#include "map2d.hpp"
#include "basicTypes.hpp"
#include "eventSystem.hpp"

void testInitializations(){
	Vector<int> vInt;
	Vector<double> vDbl;
	vInt.push_back(4); vInt.push_back(5);
	vDbl.push_back(7.0);
	std::cout << vInt[0] << " " << vDbl[0] << std::endl;

	Matrix<int> mInt; mInt.push_back(vInt);
	std::cout << mInt[0][0];
}

int main () {
	//testInitializations();
	//test1();
	//testDispatcher1();
	return 1;
}
