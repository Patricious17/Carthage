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
static int NUM_MSG_DISP = 0;

void messageDisplay(void * bEv) {
	es::Event<std::string> * ev;
	ev = static_cast<decltype(ev)>(bEv);
    std::cout << "| " << ev->getMessage() << " |" << std::endl;
    msg = ev->getMessage();
	NUM_MSG_DISP++;
};

TEST(EventDispatcherTest, BasicTest) {
	std::string incomingMessage = "incomingMessage";
	es::Event<std::string> * ev = new es::Event<std::string>(incomingMessage, "messageContent");
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

	delete dsp; delete ev;
}

TEST(EventDispatcherTest, MultipleSocketsBasicTest) {
	const int numEventNames = 100;
	std::vector<es::Event<std::string> *> events(numEventNames, nullptr);
	for (size_t i = 0; i < numEventNames; i++) events[i] = new es::Event<std::string>("incomingMessage", std::string("message ") + std::to_string(i));

	es::EventDispatcher * dsp = new es::EventDispatcher();
	dsp->registerCallback("incomingMessage", &messageDisplay);
	EXPECT_EQ(dsp->getNumSockets(), 1);

	for (size_t i = 0; i < numEventNames; i++) dsp->reportEvent(events[i]);

	dsp->showUndispatchedEvents();

	NUM_MSG_DISP = 0;
	for (size_t i = 0; i < numEventNames; i++) dsp->dispatchEvent();

	EXPECT_EQ(NUM_MSG_DISP, 100);
}

GTEST_API_ int main(int argc, char **argv) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}