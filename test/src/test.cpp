#include <gtest/gtest.h>
#include "../../src/include/eventSystem.hpp"

using customMsgType = std::string;

TEST(TestEvent, Test1){
	customMsgType msg("messageContent");
	Event<customMsgType> * ev = new Event<customMsgType>("stringTestEvent", msg);
	EXPECT_NE("", ev->getName());
	EXPECT_EQ("stringTestEvent", ev->getName());
	EXPECT_EQ(ev->getMessage(), msg);
	BareEvent *bEv = ev;
	Event<customMsgType> * ev2; ev2 = static_cast<decltype(ev2)>(bEv);
	EXPECT_EQ (ev2->getMessage(), msg);
	delete ev;
}

customMsgType stringTest1Output = "Empty";
void stringTestEventSocket(void * bEv) {
	Event<customMsgType> * ev;
	ev = static_cast<decltype(ev)>(bEv);
	stringTest1Output = ev->getMessage();
};

TEST(EventDispatcherTest, Basics) {
	eventName testEvent1 = "testEvent1";
	customMsgType msg("messageContent");
	Event<customMsgType> * ev = new Event<customMsgType>(testEvent1, msg);
	EventDispatcher * dsp = new EventDispatcher();

	dsp->registerCallback(ev->getName(), &stringTestEventSocket);
	dsp->registerCallback(ev->getName(), &stringTestEventSocket);
	EXPECT_EQ(dsp->getNumSockets(), 1);

	auto itSockets = dsp->sockets_[testEvent1].begin();
	EXPECT_EQ(*itSockets, &stringTestEventSocket);

	EXPECT_NE(msg, stringTest1Output);
	(*itSockets)(ev);
	EXPECT_EQ(msg, stringTest1Output);

	stringTest1Output = "Empty";
	EXPECT_NE(msg, stringTest1Output);
	dsp->reportEvent(ev);
	dsp->dispatchEvent();
	EXPECT_EQ(msg, stringTest1Output);

	delete dsp; delete ev;
}

TEST(EventDispatcherTest, MultipleSocketsBasics) {
	const int numEventNames = 100;
	std::vector<std::string> eventNames;
	for (int i = 1; i <= numEventNames; i++) eventNames.push_back(std::string("Event") + std::to_string(i));
	//for ()
}

GTEST_API_ int main(int argc, char **argv) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
