#include <iostream>

#include "buffer.hpp"
#include "logical_process.hpp"

Buffer::Buffer(const char* _name, double _delay,
     LogicalProcess& from, LogicalProcess& to) :
        name(_name),
        delay(_delay),
        modified(false)
{
    from.add_output_buffer(this);
    to.add_input_buffer(this);
}

double Buffer::get_delay() const
{
    return delay;
}

void Buffer::push(Event e)
{
    buf.push_front(e);
    modified = true;
}

void Buffer::pop()
{
    buf.pop_back();
    modified = true;
}

bool Buffer::empty() const
{
    return buf.empty();
}

const Event& Buffer::peek() const
{
    return buf.back();
}

void Buffer::print()
{
    if (!modified)
        return; // Only print buffers which have been modified

    std::cout << name << "={";
    bool first = true;
    for (const Event& e : buf) {
        if (!first) // Print commas between each element
            std::cout << ",";
        e.print();
        first = false;
    }
    std::cout << "}";
    modified = false;
}

double Buffer::get_last_time() const
{
    if (buf.empty())
        return -1.0;
    else
        return buf.back().get_logical_time();
}
