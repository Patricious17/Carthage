#ifndef EVENT_SYSTEM
#define EVENT_SYSTEM
#include <string>
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <deque>

namespace evSys {

const size_t MAX_QUEUE_SIZE = 2000; 

class BareEvent {
public:
	BareEvent(std::string name) : name_(name) {}
	std::string getName() { return name_; }
private:
	std::string name_;
};

template <class topicType>
class Event : public BareEvent {
public:
	Event(std::string name, topicType msg)
	: BareEvent(name), message_(msg) {}

	topicType getMessage() { return message_; }
private:
	topicType message_;
};

class EventQueue {
public:
	EventQueue() : maxSize_(MAX_QUEUE_SIZE) {};
	EventQueue(size_t maxSize) : maxSize_(std::min(MAX_QUEUE_SIZE, maxSize)) {};
	size_t size() { return evQ_.size(); }
	BareEvent * pop();
	bool push(BareEvent *);
	BareEvent * front();
	std::vector<std::string> getEventNames();
private:
	std::size_t maxSize_;
	std::deque<BareEvent *> evQ_;
};


class EventDispatcher {
public:
	void registerCallback(const std::string&, void (*)(void *));
	void dispatchEvent();
	void dispatchAllEvents();
	bool reportEvent(BareEvent * ev);
	int getNumSockets() { return numSockets_; }
	void showUndispatchedEvents();
private:
	std::map<std::string, std::set<void (*)(void *)>> sockets_;
	EventQueue eventQueue_;
	int numSockets_;
};

} // namespace evSys

#endif