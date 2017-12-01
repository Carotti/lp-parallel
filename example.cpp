#include <iostream>

#include "logical_process.hpp"
#include "event.hpp"
#include "buffer.hpp"

int main()
{
    LogicalProcess A("A", 0.0);
    LogicalProcess B("B", 4.0);
    LogicalProcess C("C", 3.0);
    LogicalProcess D("D", 3.0);

    Buffer AB("AB", 1.0, A, B);
    Buffer BD("BD", 1.0, B, D);
    Buffer CB("CB", 1.0, C, B);
    Buffer CD("CD", 1.0, C, D);
    Buffer DA("DA", 1.0, D, A);
    Buffer DC("DC", 1.0, D, C);

    Event three(3.0);
    Event four(4.0);

    BD.push(four);
    DA.push(three);

    for (int i = 0; i < 3; i++) {
        A.run_to_block();
        B.run_to_block();
        C.run_to_block();
        D.run_to_block();
    }

}
