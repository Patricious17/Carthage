//#include "map2d.hpp"
#include "basicTypes.hpp"
#include "eventSystem.hpp"
#include <iostream>

void testInitializations(){
	Vector<int> vInt;
	Vector<double> vDbl;
	vInt.push_back(4); vInt.push_back(5);
	vDbl.push_back(7.0);
	std::cout << vInt[0] << " " << vDbl[0] << std::endl;

	Matrix<int> mInt; mInt.push_back(vInt);
	std::cout << mInt[0][0];
}

void messageDisplay(void * bEv) {
	evSys::Event<std::string> * ev;
	ev = static_cast<decltype(ev)>(bEv);
    std::cout << "| " << ev->getMessage() << " |" << std::endl;
};

int main () {
	//testInitializations();
	//test1();
	//testDispatcher1();
	std::string messageTransmitted = "messageTransmitted";
	std::string msg("messageContent");
	evSys::Event<std::string> * ev = new evSys::Event<std::string>(messageTransmitted, msg);
	evSys::EventDispatcher * dsp = new evSys::EventDispatcher();

	dsp->registerCallback(msg, &messageDisplay);
	std::cout << "Exit plannerMain";
	return 1;
}
