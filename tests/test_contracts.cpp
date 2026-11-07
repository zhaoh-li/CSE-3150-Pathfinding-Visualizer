// Owner: A. Runs every owner's contract checks. A failed assert stops the program,
// so CI marks the pull request as failing.
#include "contracts/Contracts.h"

#include <cstdio>

int main() {
    pf::contractsA();
    pf::contractsB();
    pf::contractsC();
    pf::contractsD();
    pf::contractsE();
    std::puts("All contract checks passed.");
    return 0;
}
