#ifndef LOGICAL_PROCESS_HPP
#define LOGICAL_PROCESS_HPP

#include <vector>

#include "buffer.hpp"

class Buffer; // Forward declaration

class LogicalProcess {
public:
    LogicalProcess(const char* _name, double _logical_time = 0.0);

    // Simulates the specified event at this logical process
    void simulate(const Event& e);

    // Runs this logical process until it blocks
    void run_to_block();

    // Print the contents of all input/output buffers
    void print_buffers();

    void add_input_buffer(Buffer* buf);

    void add_output_buffer(Buffer* buf);
private:
    const char* name;

    // The current time being simulated by this logical process
    double logical_time;

    std::vector<Buffer*> inputs;
    std::vector<Buffer*> outputs;

    // The time of the last event sent to each output buffer
    std::vector<double> output_times;

    // Whether each input buffer has at least one event
    bool inputs_not_empty;

    // Event processing phase
    void process_inputs();

    // Deadlock avoidance phase
    void deadlock_avoidance();

    // Checks each input buffer and updates inputs_not_empty appropriately
    void check_inputs();

    // Returns the input buffer with the event with the smallest timestamp
    unsigned oldest_buffer() const;

    // Process the input from input buffer i
    void process_input(unsigned i);
};

#endif
