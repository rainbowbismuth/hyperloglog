#include <iostream>
#include <assert.h>
#include "hyperloglog.h"

int main() {
    {
        // Silly test that shouldn't work that well
        std::string s("Hello, world!");
        auto distinct = emi::HyperLogLog(s.begin(), s.end());
        assert(distinct >= 9.0 && distinct <= 11.0);
    }

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