#ifndef EVENT_SYSTEM
#define EVENT_SYSTEM
#include <string>
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <queue>

using eventName = const std::string;

class BareEvent {
public:
	BareEvent(eventName& name) : name_(name) {}
	eventName getName() { return name_; }
private:
	eventName name_;
};

template <class messageType>
class Event : public BareEvent {
public:
	Event(eventName name, messageType msg) 
	: BareEvent(name), message_(msg) {}

	messageType getMessage() { return message_; }
private:
	messageType message_;
};

class EventQueue {
public:
	EventQueue(size_t maxSize = 2) : maxSize_(maxSize) {};
	size_t size() { return evQ_.size(); }
	BareEvent * pop();
	bool push(BareEvent *);
	BareEvent * front();
private:
	std::size_t maxSize_;
	std::queue<BareEvent *> evQ_;
};


class EventDispatcher {
public:
	void registerCallback(const eventName&, void (*)(void *));
	void dispatchEvent();
	void dispatchAllEvents();
	bool reportEvent(BareEvent * ev);
	int getNumSockets() { return numSockets_; }
private:
	std::map<eventName, std::set<void (*)(void *)>> sockets_;
	EventQueue eventQueue_;
	int numSockets_;
};

#endif