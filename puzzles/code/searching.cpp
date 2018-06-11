TEST_CASE("quicksort") {
    vector<int> a = {6, 7, 10, 20, 3, 80, 4, 3, 2, 70, 55, 50, 60, 70, 80};

    // 1 2 1 3 1

    // https://github.com/careercup/ctci/blob/master/c%2B%2B/Chapter%2011/Chapter11.h

    auto partition = [&](int l, int r) {
        int mid = (l + r) / 2;
        int pivot = a[mid];

        while(l <= r) {
            while(l < r && a[l] < pivot)
                ++l;
            while(r > l && a[r] > pivot)
                --r;
            //if()
            //if()
            swap(a[l], a[r]);
        }

        //for(int i = l; i <= r; ++i) {
        //}

        return mid;
    };

    function<void(int, int)> sort = [&](int l, int r) {
        if(l >= r)
            return;

        int idx = partition(l, r);
        sort(l, idx - 1);
        sort(idx + 1, r);
    };

    //sort(0, a.size() - 1);

    print_container(a);
}

TEST_CASE("search_in_v_shaped_sorted_array") {
    // find the lowest element in a vector which is sorted in the following way:
    // - first elements begin in a descending order, then they become ascending
    // - no 2 elements next to each other are the same

    //template <typename T>
    //size_t min_elem(const vector<T>& vec, size_t begin, size_t end) {
    //    if(begin + 1 == end)
    //        return begin;

    //    auto mid_idx = (begin + end) / 2;

    //    if(mid_idx > begin && vec[mid_idx] > vec[mid_idx - 1])
    //        return min_elem(vec, begin, mid_idx);

    //    return min_elem(vec, mid_idx, end);
    //}
}

TEST_CASE("iterative_binary_search") {
    vector<int> a = {1, 3, 4, 5, 6, 7, 7, 8, 9, 12, 13};

    auto find = [&](int n) {
        int low  = 0;
        int high = a.size() - 1;
        while(low <= high) {
            int mid = (low + high) / 2;
            if(a[mid] == n)
                return mid;
            if(a[mid] < n)
                low = mid + 1;
            else
                high = mid - 1;
        }
        return -1;
    };

    cout << find(9) << endl;
}

TEST_CASE("10_11_peaks_and_valleys") {
    // a peak is an element which is bigger or equal to its adjacent elements.
    // a valley is an element which is smaller or equal to its adjacent elements.
    // example: {5, 8, 6, 2, 3, 4, 6} - {8, 6} are peaks and {5, 2} are valleys
    // given an array - sort it into an alternating sequence of peaks and valleys
    
    vector<int> a = {6, 7, 10, 20, 3, 80, 4, 3, 2, 70, 55, 50, 60, 70, 80};

    auto sort = [&]() {
        bool up = true;
        for(size_t i = 1; i < a.size(); ++i) {
            if(a[i - 1] > a[i] && up)
                swap(a[i - 1], a[i]);
            if(a[i - 1] < a[i] && !up)
                swap(a[i - 1], a[i]);
            up = !up;
        }
    };

    sort();

    print_container(a);
}

TEST_CASE("10_1_sorted_merge") {
    // given 2 sorted arrays A and B - merge them in A (provided A has capacity for both its own contents + those of B)
    
    vector<int> a = {1, 3, 4, 5, 6, 7, 7, 8, 9, 12, 13};
    vector<int> b = {3, 4, 10, 12, 13, 15};
    int back_a = a.size() - 1;
    int back_b = b.size() - 1;
    int back = back_a + back_b + 1;

    for(size_t i = 0; i < b.size(); ++i)
        a.push_back(-1);

    while(back_b >= 0) {
        if(b[back_b] > a[back_a]) {
            a[back--] = b[back_b--];
            continue;
        }
        a[back--] = a[back_a--];
    }
    
    print_container(a);
}

TEST_CASE("10_5_sparse_search") {
    // implement searching into a sparse sorted array
    vector<string> a = {"at", "", "", "", "ball", "", "", "car", "", "", "dad", "", ""};

    function<int(string, int, int)> find = [&](string n, int l, int r) {
        if(r < l)
            return -1;

        int mid = (l + r) / 2;
        if(a[mid] == "") {
            int left  = mid - 1;
            int right = mid + 1;
            while(true) {
                if(left < l && right > r)
                    return -1;
                if(left >= l && a[left] != "") {
                    mid = left;
                    break;
                }
                if(right <= r && a[right] != "") {
                    mid = right;
                    break;
                }
                left--;
                right++;
            }
        }
        if(a[mid] == n)
            return mid;
        if(a[mid] < n)
            return find(n, mid + 1, r);
        return find(n, l, mid - 1);
    };

    cout << find("ball", 0, a.size() - 1) << endl;
}

TEST_CASE("10_4_sorted_search_no_size") {
    struct Listy
    {
        vector<int> data = {1, 3, 4, 5, 7, 8, 11, 20, 21, 22, 24, 25, 31, 45, 49, 50, 54, 60};

        int operator[](int idx) { return idx >= int(data.size()) ? -1 : data[idx]; }
    } a;

    auto find = [&](int n) {
        function<int(int, int, int)> find_impl = [&](int n, int l, int r) {
            if(r < l)
                return -1;

            int mid = (l + r) / 2;
            if(n == a[mid])
                return mid;

            if(n < a[mid] || a[mid] < 0)
                return find_impl(n, l, mid - 1);

            return find_impl(n, mid + 1, r);

        };

        int r = 1;
        while(a[r] >= 0)
            r *= 2;

        return find_impl(n, 0, r);
    };

    cout << find(45) << endl; // 13
}

TEST_CASE("10_3_search_in_sorted_array") {
    // write a search function given a sorted array of integers that has then been rotated an unknown number of times

    vector<int> a = {15, 16, 19, 20, 25, 1, 3, 4, 5, 7, 10, 14};

    function<int(int, int, int)> find = [&](int n, int l, int r) {
        if(r < l)
            return -1;

        int mid = (l + r) / 2;
        if(a[mid] == n)
            return mid;

        if(a[l] < a[mid]) {
            // if left is normally ordered
            if(a[mid] > n && a[l] <= n)
                return find(n, l, mid - 1);
            else
                return find(n, mid + 1, r);
        } else if(a[mid] < a[l]) {
            // if right is normally ordered
            if(a[mid] < n && a[r] >= n)
                return find(n, mid + 1, r);
            else
                return find(n, l, mid - 1);
        } else if(a[l] == a[mid]) {
            // left or right half is all repeats
            if(a[mid] != a[r]) {
                return find(n, mid + 1, r);
            } else {
                // search both sides
                int res_left = find(n, l, mid - 1);
                return res_left < 0 ? find(n, mid + 1, r) : res_left;
            }
        }

        return -1;
    };

    // usage
    cout << find(5, 0, a.size() - 1) << endl;
}

TEST_CASE("10_10_rank_from_stream") {
    // implement a structure that can answer queries like "how many integers are below X"
    // given that X is present - essentialy the rank of X

    // implementation
    struct Node {
        Node* left  = nullptr;
        Node* right = nullptr;
        int left_count = 0;
        int data;

        Node(int n)
                : data(n) {}
    };

    Node* root = nullptr;

    auto track = [&](int n) {
        function<void(int, Node*)> track_impl = [&](int n, Node* root) {
            if(root->data > n) {
                if(root->left)
                    track_impl(n, root->left);
                else
                    root->left = new Node(n);
                root->left_count++;
            } else if(root->data < n) {
                if(root->right)
                    track_impl(n, root->right);
                else
                    root->right = new Node(n);
            } else {
                // duplicate
            }
        };

        if(root)
            track_impl(n, root);
        else
            root = new Node(n);
    };

    function<int(int, Node*)> getRankOfNum = [&](int n, Node* root) {
        if(!root)
            return -1;

        if(root->data == n)
            return root->left_count;
        if(root->data > n)
            return getRankOfNum(n, root->left);

        auto right_rank = getRankOfNum(n, root->right);
        return right_rank < 0 ? -1 : right_rank + root->left_count + 1;
    };

    // usage
    vector<int> a = {5, 3, 4, 2, 1, 10, 6, 7, 9, 8};

    for(auto& curr : a)
        track(curr);
    
    cout << getRankOfNum(1, root) << endl;
    cout << getRankOfNum(3, root) << endl;
    cout << getRankOfNum(4, root) << endl;
    cout << getRankOfNum(8, root) << endl;
    cout << getRankOfNum(100, root) << endl;

    // cleanup
    function<void(Node*)> freeTree = [&](Node* root) {
        if(!root)
            return;
        freeTree(root->left);
        freeTree(root->right);
        delete root;
    };

    freeTree(root);
}
