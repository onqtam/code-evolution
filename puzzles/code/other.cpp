
TEST_CASE("8_7_permute_string") {
    // generate all possible permutations of the string of unique characters

    string data = "1234";

    function<void(const string&, string)> permute = [&](const string& str, string out) {
        for(size_t i = 0; i < str.size(); ++i) {
            auto sub = str;
            sub.erase(i, 1);
            permute(sub, out + str[i]);
        }
        if(str.size() == 0)
            cout << out << endl;
    };

    permute(data, "");
}

TEST_CASE("8_4_all_subsets_of_set") {
    // return all subsets of a set

    set<char> data = {'1', '2', '3', '4'};

    function<vector<set<char>>(set<char>)> recurse = [&](set<char> in) {
        if(in.size()) {
            // save a random element and remove it from the data set
            auto start = in.begin();
            auto taken_out = *start;
            in.erase(start);
            // generate all subsets of the remainder of the data set
            auto res = recurse(in);
            // copy that result
            auto out = res;
            // modify one of the 2 copies of the result by re-inserting the saved element from before in each of them
            for(auto& curr : res) {
                curr.insert(taken_out);
                out.push_back(curr);
            }
            // merge the 2 now different copies into a single set
            return out;
        } else {
            // return a vector with 1 set - the empty set
            return vector<set<char>>(1);
        }
    };

    auto res = recurse(data);
    for(auto& curr : res)
        print_container(curr);
}

TEST_CASE("8_3_magic_index") {
    // find an index i such that i == a[i] in an array with sorted distinct integers
    
    vector<int> a = {-3, -2, -1, 2, 3, 5, 7, 9};

    function<int(int, int)> search = [&](int left, int right) {
        if(left > right)
            return -1;

        int mid = (left + right) / 2;
        if(mid == a[mid])
            return mid;

        if(mid > a[mid])
            return search(mid + 1, right);
        return search(left, mid - 1);
    };

    cout << search(0, a.size() - 1) << endl;

    // followup - what if the integers are not unique?
    
    //    0   1   2  3  4  5   6   7   8   9  10  11  12  13  14
    a = {-3, -2, -1, 2, 3, 3, 12, 12, 12, 12, 12, 12, 12, 13, 15};

    //     0   1  2  3  4  5  6  7  8   9  10
    a = {-10, -5, 2, 2, 2, 3, 4, 8, 9, 12, 13};

    function<int(int, int)> search2 = [&](int left, int right) {
        if(left > right)
            return -1;

        int mid = (left + right) / 2;
        if(mid == a[mid])
            return mid;

        int res = search2(left, min(mid - 1, a[mid]));
        if(res == -1)
            res = search2(max(mid + 1, a[mid]), right);
        return res;
    };

    cout << search2(0, a.size() - 1) << endl;
}

TEST_CASE("8_2_robot_in_grid") {
    // a robot is on the left top corner of a grid and wants to find his way to the bottom right
    // he can move only down and right and there are obstacles - help him find a way

    vector<vector<int>> grid = {{0, 0, 0, 0}, //
                                {0, 1, 0, 1}, //
                                {0, 0, 0, 1}, //
                                {1, 0, 1, 0}, //
                                {1, 0, 0, 0}};
    
    int rows = grid.size();
    int cols = grid[0].size();

    vector<vector<int>> visited(rows);
    for(size_t i = 0; i < visited.size(); ++i)
        visited[i].resize(cols, false);

    function<bool(int, int)> go = [&](int r, int c) {
        if(grid[r][c] || visited[r][c])
            return false;
        visited[r][c] = true;
        if(r == rows - 1 && c == cols - 1)
            return true;
        
        if(r < rows - 1) {
            if(go(r + 1, c))
                return true;
        }
        if(c < cols - 1) {
            if(go(r, c + 1))
                return true;
        }
        return false;
    };

    cout << std::boolalpha << go(0,0) << endl;
}

TEST_CASE("8_1_tripple_step") {
    // there are n steps. you either make 1, 2 or 3 steps in one move
    // in how many different ways can you go through all n steps?

    int n = 6;

    vector<int> steps(n);
    steps[0] = 1;
    steps[1] = 2;
    steps[2] = 4;
    for(int i = 3; i < n; ++i)
        steps[i] = steps[i - 1] + steps[i - 2] + steps[i - 3];

    cout << steps[n - 1] << endl;
}

TEST_CASE("16_21_sum_swap") {
    // find a pair of values from the 2 arrays such that when swapped the sums of the 2 arrays are equal
    
    vector<int> a = {4, 1, 2, 1, 1, 2}; // 11
    vector<int> b = {3, 6, 3, 3}; // 15
    
    auto& smaller = a.size() < b.size() ? a : b;
    auto& bigger = a.size() < b.size() ? b : a;

    sort(smaller.begin(), smaller.end()); // or instead of sorting the shorter array and getting an O(S*log(S)) we might use a hash table
    
    int sum_sm = accumulate(smaller.begin(), smaller.end(), 0);
    int sum_bg = accumulate(bigger.begin(), bigger.end(), 0);
    assert((sum_bg - sum_sm) % 2 == 0);

    int diff = (max(sum_bg, sum_sm) - min(sum_bg, sum_sm)) / 2;

    for(auto& curr : bigger) {
        auto it = find(smaller.begin(), smaller.end(), curr + diff);
        if(it != smaller.end()) {
            cout << "found it! " << curr << " " << *it << endl;
            break;
        }
    }
}

TEST_CASE("16_24_pairs_with_sum") {
    // find all pairs of integers in an array that sum to a specific value

    int a[] = {6, 4, 2, 8, 2, 34, 12, 43, 21, 34, 23, 43, 18, 17, 26, 32, 10, 19, 17, 7, 2, 8, 6, 2, 5, 3, 9};

    // hash map - or the following...

    int target = 30;

    sort(a, a + countof(a));

    int first = 0;
    int last = countof(a) - 1;
    while(first < last) {
        int sum = a[first] + a[last];
        if(sum == target) {
            cout << a[first] << " " << a[last] << endl;
            first++;
            last--;
        } else {
            if(sum < target)
                first++;
            else
                last--;
        }
    }
}

TEST_CASE("16_26_calculator") {
    // evaluate simple expressions with +,-,*,/ and no parentheses

    string exp = "2*3+5/6*3+15";

    // TODO: https://en.wikipedia.org/wiki/Shunting-yard_algorithm

    //vector<double> numbers;
    //vector<char> ops;

    //auto rank = [](char c) {
    //    if(c == '+' || c == '-')
    //        return 0;
    //    return 1;
    //};

    //auto do_op = [](char c, double l, double r) {
    //    if(c == '+')
    //        return l + r;
    //    if(c == '-')
    //        return l - r;
    //    if(c == '*')
    //        return l * r;
    //    return l / r;
    //};

    //for(auto& c : exp) {
    //    if(c >= '0' && c <= '9') {
    //        numbers.push_back(c - '0');
    //    } else {
    //        //if(ops.size()) {
    //        vector<char> op_temp;
    //            while(ops.size() && rank(c) < rank(ops.back())) {
    //                op_temp.push_back(ops.back());
    //                ops.pop_back();
    //            }
    //            while(op_temp.size()) {
    //                auto num = numbers.back();
    //                numbers.pop_back();
    //                numbers.back() = do_op(op, numbers.back(), num);
    //            }
    //            ops.push_back(c);
    //        //} else {
    //        //    ops.push_back(c);
    //        //}
    //    }
    //}

    //while(ops.size()) {
    //    auto op = ops.back();
    //    ops.pop_back();

    //    auto num = numbers.back();
    //    numbers.pop_back();
    //    numbers.back() = do_op(op, numbers.back(), num);
    //}

    //cout << numbers.back() << endl;
}

TEST_CASE("16_18_pattern_matching") {
    // the pattern string consists of just letters a and b.
    // "catcatgocatgo" matches "aabab", "ab", "a" and "b"

    // TODO: optimize it further... think more - once we have picked an 'a' - we have automatically picked 'b' as well...

    string val     = "catcatgocatgo";
    string pattern = "aabab"; // TODO: make it work with inverted patterns - like "bbaba"

    for(size_t i = 0; i < val.size(); ++i) {
        // pick an 'a' from the start of the value string
        string a = val.substr(0, i + 1);

        // skip all consecutive 'a's based on the pattern
        size_t pi      = 1;
        size_t vi      = i + 1;
        bool   matches = true;
        while(pi < pattern.size() && pattern[pi] == pattern[pi - 1]) {
            if(val.substr(vi, a.size()) == a) {
                vi += a.size();
                pi++;
            } else {
                matches = false;
                break;
            }
        }

        // if not all consecutive 'a's were matched to parts of the value
        if(!matches)
            continue;

        bool reached_the_end = true;

        if(pi < pattern.size()) {
            reached_the_end = false;

            // time to match 'b's
            for(size_t k = vi; k < val.size() && !reached_the_end; ++k) {
                // pick a 'b'
                string b = val.substr(vi, k - vi + 1);

                // try to match 'a's and 'b's till the end
                size_t pi2 = pi;
                size_t vi2 = vi;
                while(true) {
                    if(pattern[pi2] == 'a') {
                        if(val.substr(vi2, a.size()) != a)
                            break;
                        vi2 += a.size();
                    } else {
                        if(val.substr(vi2, b.size()) != b)
                            break;
                        vi2 += b.size();
                    }
                    pi2++;
                    if(pi2 == pattern.size() && vi2 == val.size()) {
                        reached_the_end = true;
                        break;
                    }
                }
            }
        }

        if(reached_the_end) {
            cout << "its a match!" << endl;
            break;
        }
    }
}

TEST_CASE("16_17_contiguous_sequence_max_sum") {
    // find the largest sum of contiguous elements in an array

    int a[] = {2, -8, 3, -2, 4, -10};

    int max_sum = 0;
    int sum     = 0;

    for(int i = 0; i < countof(a); ++i) {
        sum += a[i];
        if(sum > max_sum)
            max_sum = sum;
        if(sum < 0)
            sum = 0;
    }

    cout << max_sum << endl;
}

TEST_CASE("16_16_sub_sort") {
    // find indexes M and N such that when you sort that range the entire array would be sorted (and minimize the distance between M and N)

    int a[] = {1, 2, 4, 7, 10, 11, 7, 12, 6, 7, 16, 18, 19};

    int f = 0;
    int l = countof(a) - 1;

    // get the extent of the already sorted begining and ending of the array
    while(f < l && a[f] <= a[f + 1])
        ++f;
    while(l > f && a[l] >= a[l - 1])
        --l;

    int min_idx = min_element(a + f, a + l + 1) - a;
    int max_idx = max_element(a + f, a + l + 1) - a;

    // contract those 2 sorted ranges until all elements between the 2 ranges are bigger than the
    // elements from the first range and smaller than the elements from the range at the end
    while(a[min_idx] < a[f - 1] && f > 0)
        f--;
    while(a[max_idx] > a[l + 1] && l < countof(a) - 1)
        l++;

    cout << f << " " << l
         << endl; // indexes are inclusive! meaning that the index to the last is not 1 past the last.. :D
    sort(a + f, a + l + 1);
    print_container(a);
}

TEST_CASE("16_15_mastermind") {
    // count the number of direct hits (guesses)
    // also count the number of pseudo hits (letters that exist but not at that specific position - hits cannot count as pseudo hits too!)

    string real = "GGRR";

    string opit = "RGBY";

    vector<int> hit_mask(real.size());

    int hits  = 0;
    int close = 0;
    for(size_t i = 0; i < opit.size(); ++i) {
        if(real[i] == opit[i]) {
            hits++;
            hit_mask[i] = 1;
        }
    }

    for(size_t i = 0; i < real.size(); ++i) {
        if(hit_mask[i])
            continue;

        for(size_t k = 0; k < real.size(); ++k) {
            if(hit_mask[k])
                continue;

            if(real[i] == opit[k]) {
                close++;
                break;
            }
        }
    }

    cout << hits << " " << close << endl;
}

TEST_CASE("16_1_inplace_number_swap") {
    int a = 6;
    int b = 41;

    b = a - b;
    a -= b;
    b = a + b;

    // and backwards - with XOR
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;

    cout << a << " " << b << endl;
}

TEST_CASE("16_11_planks") {
    // there are S short planks and L long ones (only 2 possible lengths)
    // find the maximum number of different lengths (when concatenated) of K planks

    const int S = 5;
    const int L = 4;

    int K = 6;

    assert(S + L >= K);

    int L_left = L - min(L, K);
    int S_left = S;
    if(L_left == 0)
        S_left -= K - L;

    while(L_left <= L && S_left >= 0) {
        cout << "short: " << S - S_left << " long: " << L - L_left << endl;
        L_left++;
        S_left--;
    }
}

TEST_CASE("16_10_living_people") {
    // given a list of birth/death ranges calculate in which year there were most people alive
    // if someone dies at year X and someone is born at that same year - both of them are in the count for that year

    vector<pair<int, int>> pairs = {{7, 10}, {8, 11}, {8, 10}, {6, 8}, {10, 12}, {9, 12}};

    map<int, pair<int, int>> yearly_changes;

    for(auto& curr : pairs) {
        yearly_changes[curr.first].first++;
        yearly_changes[curr.second].second++;
    }

    int curr_alive = 0;
    int max_alive  = 0;
    for(auto& curr : yearly_changes) {
        curr_alive += curr.second.first;
        max_alive = max(max_alive, curr_alive);
        curr_alive -= curr.second.second;
    }

    CHECK(max_alive == 5);
}

TEST_CASE("16_8_integer_to_words") {
    int n = 12765987;

    const char* small[] = {"one",     "two",     "three",     "four",     "five",    "six",      "seven",
                           "eight",   "nine",    "ten",       "eleven",   "twelve",  "thirteen", "fourteen",
                           "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
    const char* tens[]  = {"twenty", "thirty", "fourty", "fifty", "sixty", "seventy", "eighty", "ninety"};
    const char* big[]   = {"hundred", "thousand", "million"};

    int mils      = n / 1000000;
    int thousands = n / 1000 % 1000;
    int last      = n % 1000;

    auto print_up_to_999 = [&](int num) {
        assert(num < 1000);
        string out;

        if(num >= 100)
            out += small[num / 100 - 1] + " "s + big[0];

        int below_100 = num % 100;
        if(below_100 > 0) {
            if(!out.empty())
                out += " ";
            if(below_100 / 10 > 1)
                out += tens[below_100 / 10 - 2];

            int leftover = below_100 % (below_100 > 19 ? 10 : 20);
            if(leftover) {
                if(below_100 / 10 > 1)
                    out += " ";
                out += small[leftover - 1];
            }
        }

        return out;
    };

    string result;
    if(mils) {
        result += print_up_to_999(mils) + " "s + big[2];
        if(thousands)
            result += " ";
    }
    if(thousands) {
        result += print_up_to_999(thousands) + " "s + big[1];
        if(last)
            result += " ";
    }
    if(last)
        result += print_up_to_999(last);

    CHECK(result == "twelve million seven hundred sixty five thousand nine hundred eighty seven");
}

TEST_CASE("16_7_find_max_of_nums_without_conditionals_and_comparisons") {
    int a = 43;
    int b = 65;

    // no
}

TEST_CASE("16_6_smallest_diff") {
    // given 2 arrays of ints - find a pair of values (one from each array) such
    // that the difference is the smallest non-negative - and return the difference

    vector<int> a = {1, 2, 3, 11, 15};
    vector<int> b = {8, 19, 23, 127, 235};

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    size_t ai   = 0;
    size_t bi   = 0;
    int    diff = INT_MAX;

    while(ai < a.size() && bi < b.size()) {
        if(abs(a[ai] - b[bi]) < diff)
            diff = abs(a[ai] - b[bi]);

        if(a[ai] < b[bi])
            ++ai;
        else
            ++bi;
    }

    CHECK(diff == 3);
}

TEST_CASE("16_5_factorial_zeros") {
    // find the number of trailing 0's of N factorial

    auto find_num_trailing_zeroes_of_n_fact = [](int n) {
        int num_times_divisible_by_five = 0;
        for(int i = 1; i <= n; ++i) {
            auto temp = i;
            // there will be always more 2's dividing a number than 5's and therefore we need to only keep track of 5's
            while(temp % 5 == 0) {
                ++num_times_divisible_by_five;
                temp /= 5;
            }
        }
        return num_times_divisible_by_five;
    };

    CHECK(find_num_trailing_zeroes_of_n_fact(25) == 6);
}

TEST_CASE("largest_area_in_matrix") {
    int a[][6] = {{1, 3, 2, 2, 2, 4}, {3, 3, 3, 2, 4, 4}, {4, 3, 1, 2, 3, 3}, {4, 3, 1, 3, 3, 1}, {4, 3, 3, 3, 1, 1}};

    vector<vector<bool>> flags(countof(a));
    for(size_t i = 0; i < flags.size(); ++i)
        flags[i].resize(countof(a[0]), false);

    int curr;
    int curr_sum;
    int max_sum = 0;

    std::function<void(int, int)> visit = [&](int i, int j) {
        // check out of bounds
        if(i < 0 || i >= countof(a) || j < 0 || j >= countof(a[0]))
            return;
        // if not visited and also with the value of the currently checked value
        if(flags[i][j] == false && a[i][j] == curr) {
            // visit
            flags[i][j] = true;
            // increment number of occurrences
            curr_sum++;
            // visit the 4 neighbouring cells
            visit(i, j + 1);
            visit(i + 1, j);
            visit(i, j - 1);
            visit(i - 1, j);
        }
    };

    // for each cell of the matrix
    for(int i = 0; i < countof(a); ++i) {
        for(int j = 0; j < countof(a[0]); ++j) {
            // if unvisited
            if(flags[i][j] == false) {
                // initialize the variables for visitation
                curr     = a[i][j];
                curr_sum = 0;
                // visit
                visit(i, j);
                // check if the result is bigger than the current max
                if(curr_sum > max_sum)
                    max_sum = curr_sum;
            }
        }
    }

    cout << max_sum << endl;
}

TEST_CASE("2_4") {
    // UNSOLVED!!!

    struct Node
    {
        Node* next;
        int   data;
    };

    Node* head = new Node{nullptr, 0};
    auto  curr = head;
    for(auto& c : {3, 5, 8, 5, 10, 2, 1}) {
        curr->next = new Node{nullptr, 3};
        curr       = curr->next;
    }

    int p = 5;

    curr = head;
    while(curr) {
        auto next = curr->next;
    }
    //++curr;
    //while(curr != l.end()) {
    //    auto temp = curr->next;
    //    if(*curr < p) {

    //    }
    //}

    //for(auto& c : l)
    //    cout << c << " ";
    cout << endl;
}

TEST_CASE("2_2_return_kth_to_last_elem_from_singly_linked_list") {
    list<int> l;
    for(int i = 0; i < 100; ++i)
        l.push_back(i);

    int k = 20;

    list<int>::iterator front = l.begin();

    int i = 0;
    while(front != l.end() && i < k) {
        ++i;
        ++front;
    }

    if(i == k) {
        list<int>::iterator result = l.begin();
        while(front != l.end()) {
            ++result;
            ++front;
        }
        cout << *result << endl;
    } else {
        cout << "no can do! " << k << " " << l.size() << endl;
    }
}

TEST_CASE("1_8_zero_all_rows_and_columns_if_0_is_found") {
    int a[][5] = {{1, 2, 3, 4, 5},     {6, 0, 8, 0, 10},    {11, 12, 13, 14, 15},
                  {16, 17, 18, 19, 0}, {0, 22, 23, 24, 25}, {26, 27, 28, 29, 30}};

    int max_dim = std::max(countof(a), countof(a[0]));

    enum to_clear
    {
        none   = 0,
        row    = 1,
        column = 2,
        both   = 4
    };

    vector<to_clear> row_column_mapping_to_clear(max_dim);

    // FUCK THIS - not done

    for(int i = 0; i < countof(a); ++i) {
        for(int k = 0; k < countof(a[0]); ++k) {
            //if(a[i][k] == 0)
            //row_column_mapping_to_clear[]
        }
    }

    for(int i = 0; i < countof(a); ++i) {
        for(int k = 0; k < countof(a[0]); ++k) {
            cout << setw(2) << a[i][k] << " ";
        }
        cout << endl;
    }
}

TEST_CASE("1_7_rotate_nxn_matrix_by_90_degrees") {
    // rotate a NxN matrix by 90 degrees

    int a[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    //int a[][5] =    {{ 1,  2,  3,  4,  5}
    //                ,{ 6,  7,  8,  9, 10}
    //                ,{11, 12, 13, 14, 15}
    //                ,{16, 17, 18, 19, 20}
    //                ,{21, 22, 23, 24, 25}};

    int size = countof(a);
    int last = size - 1;

    for(int d = 0; d < size / 2; ++d) {
        for(int i = d; i < size - d - 1; ++i) {
            auto temp             = a[d][i];
            a[d][i]               = a[last - i][d];
            a[last - i][d]        = a[last - d][last - i];
            a[last - d][last - i] = a[i][last - d];
            a[i][last - d]        = temp;
        }
    }

    for(int i = 0; i < countof(a); ++i) {
        for(int k = 0; k < countof(a); ++k) {
            cout << setw(2) << a[i][k] << " ";
        }
        cout << endl;
    }
}

TEST_CASE("find_biggest_sum_of_2_non_overlapping_ranges") {
    // da se nameri MAX sumata na K i L posledovatelni nepokriva6ti se ranges
    // [4, 5, 3, 1, 9, 1, 1, 7, 8, 1, 1], K=5, L=2
    //  ^  ^  ^  ^  ^        ^  ^       37

    auto solution = [](const vector<int>& A, int K, int L) {
        int size = A.size();
        if(K + L > size)
            return -1;

        vector<int> rangeK(size, 0);
        vector<int> rangeL(size, 0);

        // prepass
        rangeK[0] = accumulate(A.begin(), A.begin() + K, 0);
        rangeL[0] = accumulate(A.begin(), A.begin() + L, 0);
        for(int i = 1; i < size; ++i) {
            if(i + K <= size)
                rangeK[i] = rangeK[i - 1] - A[i - 1] + A[i + K - 1];
            if(i + L <= size)
                rangeL[i] = rangeL[i - 1] - A[i - 1] + A[i + L - 1];
        }

        // find it
        int max = 0;
        for(int k = 0; k < size - K; ++k) {
            int max_l = 0;
            for(int l = 0; l <= size - L; ++l)
                if(l + L <= k || l >= k + K)
                    max_l = std::max(rangeL[l], max_l);
            max = std::max(rangeK[k] + max_l, max);
        }

        return max;
    };

    cout << solution({4, 5, 3, 1, 9, 1, 1, 7, 8, 1, 1}, 5, 2) << endl; // << 37
    cout << solution({5, 8, 3, 1, 9, 7, 4, 1, 1, 1, 1}, 5, 2) << endl; // << 37
}

TEST_CASE("find_smallest_positive_non_occurring_element") {
    //given an array A of N integers, find the smallest positive integer (greater than 0) that does not occur in A.
    //
    //For example, given A = [1, 3, 6, 4, 1, 2], the function should return 5.
    //Given A = [1, 2, 3], the function should return 4.
    //Given A = [-1, -3], the function should return 1.
    //
    //Assume that:
    //N is an integer within the range [1..100,000];
    //each element of array A is an integer within the range [-1,000,000..1,000,000].
    //
    //Complexity:
    //expected worst-case time complexity is O(N);
    //expected worst-case space complexity is O(N), beyond input storage (not counting the storage required for input arguments).

    vector<int> a = {1, 3, 6, 4, 1, 2};

    vector<int> histogram(a.size(), 0);
    for(auto& curr : a)
        if(curr < int(a.size()) && curr > 0)
            histogram[curr] = 1;

    int res = 0;
    for(int i = 1; i < int(a.size()); ++i) {
        if(histogram[i] == 0) {
            res = i;
            break;
        }
    }
    if(!res)
        res = a.size();
    cout << res << endl;
}

TEST_CASE("badass") {
    //Çëîäåé ñè å íàìèñëèë åäíî ÷èñëî ìåæäó 1 è RAND_MAX. Ìîæå äà ãî ïèòàø âúïðîñè îò ðîäà íà "÷èñëîòî òè åäíî îò òåçè ëè å?".
    //Òîé îáà÷å ìîæå â îòãîâîðà ñè äà òå ëúæå. Íî íå ïîâå÷å îò 9 ïîñëåäîâàòåëíè ïúòè.
    //Ìîæå äà òå ëúæå õèëÿäè ïúòè, íî íå è 10 ïîðåäíè. Ìîæå äà òè êàçâà èñòèíàòà êîëêîòî ïúòè èñêà.
    //Åòî òè ïðèìåðåí êîä çà çëîäåé: https://pastebin.com/ZBmh7g1K
    //Çàäà÷àòà å äà íàïèøåø àëãîðèòúì, êîéòî äà ñâåäå âúçìîæíèòå ÷èñëà çà íåãîâîòî äî 512.
    //Â ïðèìåðíèÿ êîä äà èçâèêàø final_guess ôóíêöèÿòà è òÿ äà âúðíå true

    //srand(time(NULL));

    struct Zlodey
    {
        bool is_num_there(const vector<int>& numbers) {
            bool is_it_really = find(numbers.begin(), numbers.end(), mynum) == numbers.end();

            if(lies == 9) // tell the truth
            {
                lies = 0;
                return is_it_really;
            }

            auto lie_this_time = rand() % 2;
            if(lie_this_time) {
                ++lies;
                return !is_it_really;
            } else {
                lies = 0;
                return is_it_really;
            }
        }

        bool final_guess(const vector<int>& nums) {
            if(nums.size() > 512)
                return false;
            lies = 9;
            return is_num_there(nums);
        }

    private:
        int lies  = 0;
        int mynum = rand() % RAND_MAX;
    };

    Zlodey z;

    // 1 2 3 4 5 6 7 8 9 10
}

TEST_CASE("granny") {
    //Èìàø íà÷àëåí ñòðèíã ñúñòàâåí îò à è á è êðàåí ñòðèíã ñúñòàâåí îò à è á. Èìàø äâà âèäà âàëèäíè îïåðàöèè
    //õ) Äîáàâÿø à â êðàÿ íà ñòðèíãà
    //ó) Îáðúùàø ñòðèíãà è ìó äîáàâÿø á â êðàÿ
    //Ìîæåø ëè äà ïîëó÷èø íà÷àëíèÿ îò êðàéíèÿ?
    //
    //Ïðèìåðíî
    //âõîä: àá, áàáà
    //èçõîä: ÄÀ! (ùîòî àêî ïî÷íåø îò ïúðâèÿ ñ îïåðàöèè y è ïîñëå x óñïÿâàø)
    //
    //âõîä àá, áààáà
    //èçõîä: ÍÅ! (íå ìîæå îò òîçè íà÷àëåí ñòðèíã äà ïîëó÷èø òîçè êðàåí ñ îïåðàöèè õ è ó)

    //string in = "ab";
    //string out = "baba";
    //string in = "ab";
    //string out = "baaba";
    string in  = "abb";
    string out = "bbababbabab";

    size_t range[] = {0, out.size() - 1};
    int    side    = 0;
    bool   found   = false;

    while(range[1] - range[0] >= in.size() && !found) {
        char c = out[range[side]];
        range[side] += side ? -1 : 1;
        if(c == 'b')
            side = side > 0 ? 0 : 1;

        auto sub     = out.substr(range[0], range[1] - range[0] + 1);
        auto sub_rev = sub;
        std::reverse(sub_rev.begin(), sub_rev.end());
        if(sub == in || sub_rev == in)
            found = true;

        //cout << sub << " " << sub_rev << endl;
    }

    cout << (found ? "yes!" : "no!") << endl;
}

TEST_CASE("construct_sentence") {
    //Èìàø ñòðèíã (íàïðèìåð helloworld) è ðå÷íèê (íàïðèìåð {hell, o, world, hello, hellow, ld} ) äàé
    //áðîéêàòà íà÷èíè ïî êîèòî ìîæå äà ñå îáðàçóâà èçðå÷åíèå ñ äóìè îò ðå÷íèêà êîåòî èçöÿëî èçïîëçâà âõîäà.
    //
    //Ñ ïðèìåðíèòå äàííè å: 2
    //(hell o world  è  hello world)
    //
    //Äðóã ïðèìåð dodoremi {do, re, mi, fa, sol, dodo}: 2
    //( do do re mi è dodo re mi )
    //
    //Òúðñè ñå áðîéêàòà, à íå êîíêðåòíèòå èçðå÷åíèÿ. Çàáåëåæè ÷å áðîéêàòà ìîæå äà å íÿêàêâî ãèãàíòñêî ÷èñëî
    //ïðèìåðíî â xxxx (1000 Ïúòè) è ðå÷íèê {x, xx, xxx, xxxx, . } èìà íÿêàêâè áðàçèëèîíè âúçìîæíè èçðå÷åíèÿ

    set<string> dict{"hell", "o", "world", "hello", "hellow", "ld", "wo", "r"};
    string      target{"helloworld"};

    // hell o world
    // hell o wo r ld
    // hello world
    // hello wo r ld
    // hellow o r ld

    //set<string> dict {"x", "xx", "xxx"};
    //string target {"xxxx"};

    // xxx x
    // xx xx
    // xx x x
    // x xx x
    // x x xx
    // x x x x
    // x xxx

    vector<int> vec(target.size(), 0);
    auto        idx     = -1;
    auto        idx_val = 1;

    // linear scan - propagation of values
    while(idx < int(target.size()) - 1) {
        // for each word - try to match it with the original string from the current index - and propagate the count if possible
        for(auto& curr : dict)
            if(target.compare(idx + 1, curr.size(), curr) == 0)
                vec[idx + curr.size()] += idx_val;

        // advance to the next position a word has reached
        idx++;
        while(vec[idx] == 0 && idx < int(vec.size()) - 1)
            idx++;
        idx_val = vec[idx];
    }

    // last entry is whatever got propagated
    cout << vec.back() << endl;

    //// slow and unoptimal ... "dynamic" programming...
    //map<string, int> cache;

    //function<int(const string&)> recursive = [&](const string& str) {
    //    auto it = cache.find(str);
    //    if(it != cache.end())
    //        return it->second;

    //    int accum = 0;
    //    for(auto& curr : dict) {
    //        if(str.substr(0, curr.size()) == curr) {
    //            if(curr.size() == str.size())
    //                accum++;
    //            auto res = recursive(str.substr(curr.size()));
    //            if(res)
    //                accum += res;
    //        }
    //    }

    //    if(it == cache.end())
    //        cache.insert({str, accum});

    //    return accum;
    //};

    //auto answer = recursive(target);
    //cout << answer << endl;
}

TEST_CASE("reverse_singly_linked_list") {
    // Îáúðíè åäíîñâúðçàí ñïèñúê struct elem { elem* next; }; next e nullptr çà ïîñëåäíèÿ åëåìåíò.
    struct elem
    {
        elem* next;
        int   data;
    };

    elem* head = new elem{nullptr, 0};
    auto  curr = head;
    for(int i = 1; i < 10; i++) {
        curr->next = new elem{nullptr, i};
        curr       = curr->next;
    }

    elem* prev = nullptr;
    while(head) {
        auto next  = head->next;
        head->next = prev;
        prev       = head;
        if(next)
            head = next;
        else
            break;
    }

    curr = head;
    while(curr) {
        cout << curr->data << endl;
        curr = curr->next;
    }
}


/*

// You have N slots to fill. You can't fill a slot if a slot next to it is already filled. What is the average number of filled slots for N?
// Example: for 100 slots the best fill is to have 50 filled slots - 1 in every 2, but the worse fill would be 34 if we fill the first slot in every 3 (making the other 2 unusable)

int func(int N) {
    bitset<bool> slots(N, 1);
    int freeSlots = N;
    int res = 0;

    auto fill = [&](int i) {
        int curr = 0;
        int num_free_so_far = 0;

        while(num_free_so_far < i) {
            if(slots[curr]) {
                num_free_so_far++;
            }
            ++curr;
        }
        --curr;

        slots[curr] = false;
        --freeSlots;
        if(curr > 0) {
            --freeSlots;
            slots[curr - 1] = false;
        }
        if(curr < N - 1) {
            --freeSlots;
            slots[curr + 1] = false;
        }
    };

    while(freeSlots) {
        fill(rand() % freeSlots);
        ++res;
    }

    return res;
}

float brute_force_simulation(int N, int iter) {
    int accum = 0;
    for(int i = 0; i < iter; )i) {
        accum += func(N);
    }
    return (float)accum / (iter);
}

void test() {
    CHECK(abs(other_func(2, 1000) - 1.f) < 0.0001f);

    // this is a rough constraint - come up with better
    CHECK(other_func(3, 1000) > 3 * 0.5f);
    CHECK(other_func(3, 1000) < 3 * 0.66666666666666666f);

    CHECK(other_func(4, 1000) > 3 * ..);
    // TODO: test it properly
}

*/

/*

// you have K number of streams (not necessarily equal in length) with sorted numbers. Merge them.

K = 3
1 2 2 2 3 4 4 4 4 4 5
5 5 6 7 7 7 8
2 3 5 5 6 7 7 7 8

struct NumberedStream {
    NumberedStream() = default;
    int pop();
    int peek() const;
    bool end() const;
};

struct PriorityQueue {
    PriorityQueue(comparator...);
    int peek() const;
    int pop();
    void push(int);

    bool empty() const;
};

// O(N * log(K))
void mergeStreamsVersion2(vector<NumberedStream>& streams) {
    auto comp = [&](size_t lhs, size_t rhs) {
        return streams[lhs].peek() < streams[rhs].peek();
    };

    PriorityQueue queue(comp);

    for(size_t i = 0; i < streams.size(); ++i) {
        if(!streams[i].end()) {
            queue.push(i);
        }
    }

    while(!queue.empty()) {
        auto curr_idx = queue.pop();
        cout << streams[curr_idx] << " ";
        if(!streams[curr_idx].empty())
            queue.push(curr_idx);
    }
}

// O(N * K)
void mergeStreams(vector<NumberedStream>& streams) {
    bool finished = false;

    while(!finished) {
        finished = true;
        int smallest = INT_MAX;
        size_t curr_smallest = 0; // << take care of this
        for(size_t i = 0; i < streams.size(); ++i) {
            if(!streams[i].end()) {
                finished = false;
                if(smallest >= streams[i].peek()) {
                    smallest = streams[i].peek();
                    curr_smallest = i;
                }
            }
        }
        if(!finished)
            cout << streams[curr_smallest].pop() << " ";
    }
}

// TODO: figure how to make this optimal...
bool isPowOf7(unsigned in) {
    while(in % 7 == 0) {
        in /= 7;
    }
    return in == 1;
}

*/

