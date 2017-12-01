# Parallel LP Simulator
Simulate the order of simulation of parallel logical processes using the Chandy-Misra-Bryant algorithm.

Define `LogicalProcess`s, their `Buffer`s and `Event`s. Then `run_to_block` until the simulation is 'complete', or however many iterations of the algorithm you want to do.

`LogicalProcess`s can specify the lookahead delay for each buffer. Also can specify the initial time for a `LogicalProcess`, defaults to `0.0` and must be positive.
