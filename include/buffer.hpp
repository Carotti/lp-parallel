#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <deque>

#include "event.hpp"

class LogicalProcess;

class Buffer {
public:
    Buffer(const char* _name, double _delay,
        LogicalProcess& from, LogicalProcess& to);

    double get_delay() const;

    void push(Event e);

    void pop();

    const Event& peek() const;

    bool empty() const;

    void print();

    double get_last_time() const;
private:
    const char* name;
    double delay;
    bool modified;

    std::deque<Event> buf;
};

#endif
