//
// Created by Emily Bellows on 1/4/16.
//

#ifndef HYPERLOGLOG_HYPERLOGLOG_H
#define HYPERLOGLOG_HYPERLOGLOG_H

#include <array>
#include <algorithm>
#include <cmath>

namespace emi {

    template<typename T, typename Hash=std::hash<T>, int b=7>
    class HyperLogLogCtx {
        static constexpr int m = 1 << b;
        static constexpr int mask = m - 1;
        static constexpr double a_m() {
            if (m <= 31) {
                return 0.673;
            }
            if (m <= 63) {
                return 0.697;
            }
            if (m <= 127) {
                return 0.709;
            }
            return 0.7213 / (1 + 1.079 / m);
        }
        static constexpr double mSquared = m * m;

        Hash hash;
        std::array<uint32_t, m> registers;

    public:
        HyperLogLogCtx() noexcept {
            registers.fill(0);
        }

        void add(const T &t) noexcept {
            uint32_t x = hash(t);
            uint32_t j = x & mask;
            uint32_t w = __builtin_clz(x | mask);
            registers[j] = std::max(registers[j], w);
        }

        double finish() const noexcept {
            double sum = 0;
            for (int i = 0; i < m; ++i) {
                sum += std::pow(2, -registers[i]);
            }
            double e = a_m() * mSquared * std::pow(sum, -1);

            if (e <= (5.0 / 2.0) * m) {
                double v = std::count(registers.begin(), registers.end(), 0);
                if (v != 0) {
                    return m * std::log(m / v);
                } else {
                    return e;
                }
            } else if (e <= (1.0 / 30.0) * std::pow(2.0, 32.0)) {
                return e;
            } else {
                return std::pow(-2.0, 32.0) * std::log(1 - e / std::pow(2.0, 32.0));
            }
        }
    };

    template<typename InputIterator, typename Hash=std::hash<typename InputIterator::value_type>, int b=7>
    double HyperLogLog(InputIterator first, InputIterator last) {
        HyperLogLogCtx<typename InputIterator::value_type, Hash, b> ctx;
        std::for_each(first, last, [&](auto &i) { ctx.add(i); });
        return ctx.finish();
    };

};

#endif //HYPERLOGLOG_HYPERLOGLOG_H
