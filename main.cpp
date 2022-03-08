#include "algorithms.hpp"
#include "testing_module.hpp"

int main() {
    int n = 5000;
    util::timer<util::precision_us> timer;
//    test::test_run(sorts::shell_sort, util::random_array(n), n, timer);
//    test::benchmark_run(sorts::insertion_sort, util::ascending_array(n), n, timer);
    test::benchmark_sequence(sorts::shell_sort, n, timer);
    return 0;
}
