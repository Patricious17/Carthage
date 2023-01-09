#include "eventSystem.hpp"

BareEvent * EventQueue::pop() {
	if (evQ_.empty()) return nullptr;
	auto ev = evQ_.front(); evQ_.pop();
	return ev;
}

bool EventQueue::push(BareEvent * ev){
	if (evQ_.size() >= maxSize_) return false;
	evQ_.push(ev);
	return true;
}

BareEvent * EventQueue::front() {
	if (evQ_.empty()) return nullptr;
	return evQ_.front();
}

void EventDispatcher::registerCallback(const eventName& evName, void (* callback)(void *)) {
	if (   sockets_.find(evName) != sockets_.end() 
		&& sockets_[evName].find(callback) != sockets_[evName].end()) return;
	sockets_[evName].insert(callback);
	numSockets_++;
}

void EventDispatcher::dispatchEvent() {
	auto ev = eventQueue_.pop();
	if (ev == nullptr) return;
	for (auto& socket : sockets_[ev->getName()]) (*socket)(ev);
}

void EventDispatcher::dispatchAllEvents() {
	while(eventQueue_.size() > 0) dispatchEvent();
}

bool EventDispatcher::reportEvent(BareEvent * ev) {
	return eventQueue_.push(ev);
}
