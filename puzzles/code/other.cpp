
TEST_CASE("16_18_pattern_matching") {
    // the pattern string consists of just letters a and b.
    // "catcatgocatgo" matches "aabab", "ab", "a" and "b"

    string val     = "catcatgocatgo";
    string pattern = "aabab";

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
    //Злодей си е намислил едно число между 1 и RAND_MAX. Може да го питаш въпроси от рода на "числото ти едно от тези ли е?".
    //Той обаче може в отговора си да те лъже. Но не повече от 9 последователни пъти.
    //Може да те лъже хиляди пъти, но не и 10 поредни. Може да ти казва истината колкото пъти иска.
    //Ето ти примерен код за злодей: https://pastebin.com/ZBmh7g1K
    //Задачата е да напишеш алгоритъм, който да сведе възможните числа за неговото до 512.
    //В примерния код да извикаш final_guess функцията и тя да върне true

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
    //Имаш начален стринг съставен от а и б и краен стринг съставен от а и б. Имаш два вида валидни операции
    //х) Добавяш а в края на стринга
    //у) Обръщаш стринга и му добавяш б в края
    //Можеш ли да получиш началния от крайния?
    //
    //Примерно
    //вход: аб, баба
    //изход: ДА! (щото ако почнеш от първия с операции y и после x успяваш)
    //
    //вход аб, бааба
    //изход: НЕ! (не може от този начален стринг да получиш този краен с операции х и у)

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
    //Имаш стринг (например helloworld) и речник (например {hell, o, world, hello, hellow, ld} ) дай
    //бройката начини по които може да се образува изречение с думи от речника което изцяло използва входа.
    //
    //С примерните данни е: 2
    //(hell o world  и  hello world)
    //
    //Друг пример dodoremi {do, re, mi, fa, sol, dodo}: 2
    //( do do re mi и dodo re mi )
    //
    //Търси се бройката, а не конкретните изречения. Забележи че бройката може да е някакво гигантско число
    //примерно в xxxx (1000 Пъти) и речник {x, xx, xxx, xxxx, …. } има някакви бразилиони възможни изречения

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
    // Обърни едносвързан списък struct elem { elem* next; }; next e nullptr за последния елемент.
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
