#include <iostream>

#include "event.hpp"

Event::Event(double _logical_time, bool _null) :
    logical_time(_logical_time),
    null(_null)
{}

double Event::get_logical_time() const
{
    return logical_time;
}

bool Event::is_null() const
{
    return null;
}

void Event::print() const
{
    std::cout << logical_time;
    if (null)
        std::cout << "*";
}
