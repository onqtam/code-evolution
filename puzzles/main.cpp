#include "precompiled.h"

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

#define CALL_TEST_CASE(x) context.addFilter("test-case", x)

int main() {
    doctest::Context context;

    //CALL_TEST_CASE("iterative_binary_search");
    CALL_TEST_CASE("8_4_all_subsets_of_set");

    auto out = context.run();

    system("pause");

    return out;
}
