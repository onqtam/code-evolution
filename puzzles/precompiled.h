#include "doctest.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <memory>
#include <algorithm>
#include <functional>
#include <cstdlib>
#include <cassert>
#include <ctime>
#include <climits>
#include <numeric>

using namespace std;
using namespace std::string_literals;

#define countof(x) (sizeof(x) / sizeof(x[0]))

#define print_container(a)                                                                         \
    for(auto& curr : a)                                                                            \
        cout << curr << " ";                                                                       \
    cout << endl
