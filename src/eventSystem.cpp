#include "eventSystem.hpp"

namespace evSys {
BareEvent * EventQueue::pop() {
	if (evQ_.empty()) return nullptr;
	auto ev = evQ_.front(); evQ_.pop_front();
	return ev;
}

bool EventQueue::push(BareEvent * ev){
	if (evQ_.size() >= maxSize_) return false;
	evQ_.push_back(ev);
	return true;
}

std::vector<std::string> EventQueue::getEventNames(){
	std::vector<std::string> names;
	for (auto& ev : evQ_)
		names.push_back(ev->getName());
	return names;
}

BareEvent * EventQueue::front() {
	if (evQ_.empty()) return nullptr;
	return evQ_.front();
}

void EventDispatcher::registerCallback(const std::string& evName, void (* callback)(void *)) {
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

void EventDispatcher::showUndispatchedEvents(){
	std::cout << "\nList of undispatched events:\n";
	for (auto& name : eventQueue_.getEventNames())
		std::cout << name << std::endl;
	std::cout << std::endl;
}

} // namespace evSys