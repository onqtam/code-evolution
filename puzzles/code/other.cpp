
TEST_CASE("largest_area_in_matrix") {
    int a[][6] = {
        {1, 3, 2, 2, 2, 4},
        {3, 3, 3, 2, 4, 4},
        {4, 3, 1, 2, 3, 3},
        {4, 3, 1, 3, 3, 1},
        {4, 3, 3, 3, 1, 1}};
    
    vector<vector<bool>> flags(countof(a));
    for(size_t i = 0; i < flags.size(); ++i)
        flags[i].resize(countof(a[0]), false);
    
    int curr;
    int curr_sum;
    int max_sum = 0;

    std::function<void(int,int)> visit = [&](int i, int j) {
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
                curr = a[i][j];
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
    
    struct Node {
        Node* next;
        int data;
    };

    Node* head = new Node{nullptr, 0};
    auto curr = head;
    for(auto& c : {3, 5, 8, 5, 10, 2, 1}) {
        curr->next =  new Node{nullptr, 3};
        curr = curr->next;
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
    int a[][5] =    {{ 1,  2,  3,  4,  5}
                    ,{ 6,  0,  8,  0, 10}
                    ,{11, 12, 13, 14, 15}
                    ,{16, 17, 18, 19,  0}
                    ,{ 0, 22, 23, 24, 25}
                    ,{26, 27, 28, 29, 30}};

    int max_dim = std::max(countof(a), countof(a[0]));

    enum to_clear {
        none = 0,
        row = 1,
        column = 2,
        both = 4
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

    int a[][4] =    {{ 1,  2,  3,  4}
                    ,{ 5,  6,  7,  8}
                    ,{ 9, 10, 11, 12}
                    ,{13, 14, 15, 16}};
    //int a[][5] =    {{ 1,  2,  3,  4,  5}
    //                ,{ 6,  7,  8,  9, 10}
    //                ,{11, 12, 13, 14, 15}
    //                ,{16, 17, 18, 19, 20}
    //                ,{21, 22, 23, 24, 25}};

    int size = countof(a);
    int last = size - 1;

    for(int d = 0; d < size / 2; ++d) {
        for(int i = d; i < size - d - 1; ++i) {
            auto temp = a[d][i];
            a[d][i] = a[last - i][d];
            a[last - i][d] = a[last - d][last - i];
            a[last - d][last - i] = a[i][last - d];
            a[i][last - d] = temp;
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
