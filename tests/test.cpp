#include <string>
#include <typeinfo>

#include "gtest/gtest.h"

#include "../src/eventSystem.hpp"

namespace es = evSys;


TEST(TestEvent, TestGetMessage){
	std::string msg("messageContent");
	es::Event<std::string> * ev = new es::Event<std::string>("stringTestEvent", msg);
	EXPECT_NE("", ev->getName());
	EXPECT_EQ("stringTestEvent", ev->getName());
	EXPECT_EQ(ev->getMessage(), msg);
	es::BareEvent *bEv = ev;
	es::Event<std::string> * ev2;
    ev2 = static_cast<decltype(ev2)>(bEv);
	EXPECT_EQ (ev2->getMessage(), msg);
	delete ev;
}

std::string msg("");

void messageDisplay(void * bEv) {
	es::Event<std::string> * ev;
	ev = static_cast<decltype(ev)>(bEv);
    std::cout << "| " << ev->getMessage() << " |" << std::endl;
    msg = ev->getMessage();
};

TEST(EventDispatcherTest, Basics) {
	std::string messageTransmitted = "messageTransmitted";
	es::Event<std::string> * ev = new es::Event<std::string>(messageTransmitted, "messageContent");
	es::EventDispatcher * dsp = new es::EventDispatcher();

	dsp->registerCallback(ev->getName(), &messageDisplay);
	dsp->registerCallback(ev->getName(), &messageDisplay);
	EXPECT_EQ(dsp->getNumSockets(), 1);

	std::string stringTest1Output = "Empty";
	EXPECT_NE("messageContent", msg);
	dsp->reportEvent(ev);
    dsp->showUndispatchedEvents();
	dsp->dispatchEvent();
    dsp->showUndispatchedEvents();
	EXPECT_EQ("messageContent", msg);

	// delete dsp; delete ev;
}

// TEST(EventDispatcherTest, MultipleSocketsBasics) {
// 	const int numEventNames = 100;
// 	std::vector<std::string> eventNames;
// 	for (int i = 1; i <= numEventNames; i++) eventNames.push_back(std::string("Event") + std::to_string(i));
// 	//for ()
// }

GTEST_API_ int main(int argc, char **argv) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}