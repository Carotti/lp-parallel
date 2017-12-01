#include <iostream>

#include "logical_process.hpp"

LogicalProcess::LogicalProcess(const char* _name, double _logical_time) :
    name(_name),
    logical_time(_logical_time),
    inputs_not_empty(false)
{
    if (logical_time < 0.0) {
        std::cerr << "Cannot have an LP with negative timestamp" << std::endl;
        exit(EXIT_FAILURE);
    }
}
void LogicalProcess::simulate(const Event& e)
{
    logical_time = e.get_logical_time();

    // Send a new event to each of the connected output buffers if e not null
    if (!e.is_null()) {
        for (unsigned i = 0; i < outputs.size(); i++) {
            outputs[i]->push(Event(logical_time + outputs[i]->get_delay()));
            output_times[i] = logical_time;
        }
    }
}

void LogicalProcess::run_to_block()
{
    process_inputs();
    deadlock_avoidance();
    std::cout << "\t" << "b@" << logical_time;
}

void LogicalProcess::print_buffers()
{
    for (Buffer* buf : inputs) {
        buf->print();
    }
    for (Buffer* buf : outputs) {
        buf->print();
    }
}

void LogicalProcess::add_input_buffer(Buffer* buf)
{
    inputs.push_back(buf);
    check_inputs();
}

void LogicalProcess::add_output_buffer(Buffer* buf)
{
    outputs.push_back(buf);
    output_times.push_back(buf->get_last_time());
}

void LogicalProcess::process_inputs()
{
    check_inputs();
    while(inputs_not_empty) {
        unsigned i = oldest_buffer();
        process_input(i);
    }
    for (unsigned i = 0; i < inputs.size(); i++) {
        if (!inputs[i]->empty()) {
            if (inputs[i]->peek().get_logical_time() <= logical_time)
                process_input(i);
        }
    }
}

void LogicalProcess::deadlock_avoidance()
{
    bool sent_null = false;
    for (unsigned i = 0; i < outputs.size(); i++) {
        if (output_times[i] < logical_time) {
            outputs[i]->push(Event(logical_time + outputs[i]->get_delay(), true));
            output_times[i] = logical_time;
            sent_null = true;
        }
    }
    if (sent_null) {
        std::cout << std::endl << name << "\tn@" << logical_time << "\t";
        print_buffers();
    }
}

void LogicalProcess::check_inputs()
{
    if (inputs.empty()) {
        inputs_not_empty = false;
        return;
    }

    for (const Buffer* buf : inputs) {
        if (buf->empty()) {
            inputs_not_empty = false;
            return;
        }
    }
    inputs_not_empty = true;
}

unsigned LogicalProcess::oldest_buffer() const
{
    unsigned buf = 0;
    double oldest = 0.0;
    bool found = false;

    for (unsigned i = 0; i < inputs.size(); i++) {
        if (inputs[i]->empty())
            return 0.0; // A buffer is empty, so we can't find the oldest

        double new_time = inputs[i]->peek().get_logical_time();
        if (new_time < oldest || !found) {
            buf = i;
            oldest = new_time;
            found = true;
        }
    }

    return buf;
}

void LogicalProcess::process_input(unsigned i)
{
    const Event& e = inputs[i]->peek();
    bool null = e.is_null();
    simulate(e);
    inputs[i]->pop();
    if (inputs[i]->empty())
        inputs_not_empty = false;
    std::cout << std::endl << name << "\te@" << logical_time;
    if (null)
        std::cout << "*";
    std::cout << "\t";
    print_buffers();
}
