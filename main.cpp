#include <iostream>
#include "hyperloglog.h"

int main() {
    emi::HyperLogLogCtx<std::string> ctx;
    std::string input;
    while (std::cin) {
        std::getline(std::cin, input);
        ctx.add(input);
    }
    auto distinct = ctx.finish();
    std::cout << "Distinct: " << distinct << std::endl;
    return 0;
}