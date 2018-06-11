//interval_map<K,V> is a data structure that efficiently associates intervals of keys of type K with values of
//type V. Your task is to implement the assign member function of this data structure, which is outlined below.
//Each key-value-pair (k,v) in the m_map member means that the value v is
//associated to the interval from k (including) to the next key (excluding) in m_map.
//
//Example: the std::map (0,'A'), (3,'B'), (5,'A') represents the mapping
//
//0 -> 'A'
//1 -> 'A'
//2 -> 'A'
//3 -> 'B'
//4 -> 'B'
//5 -> 'A'
//6 -> 'A'
//7 -> 'A'
//... all the way to numeric_limits<key>::max()
//The representation in m_map must be canonical, that is, consecutive map entries must not have
//the same value: ..., (0,'A'), (3,'A'), ... is not allowed. Initially, the whole range of K is
//associated with a given initial value, passed to the constructor.
//
//Key type K
//- besides being copyable and assignable, is less-than comparable via operator<
//- is bounded below, with the lowest value being std::numeric_limits<K>::lowest()
//- does not implement any other operations, in particular no equality comparison or arithmetic operators
//
//Value type V
//- besides being copyable and assignable, is equality-comparable via operator==
//- does not implement any other operations

//
//Your task is to implement the function "assign". Your implementation is graded by these criteria in this order:
//
//Correctness (of course): In particular, pay attention to the validity of iterators. It is illegal to dereference end iterators. Consider using a checking STL implementation such as the one shipped with Visual C++.
//Simplicity: Simple code is easy to understand and maintain, which is important in large projects. To write a simple solution, you need to exploit the structure of the problem. Use functions of std::map wherever you can.
//Running time: Imagine your implementation is part of a library, so it should be big-O optimal. In addition:
//Do not make big-O more operations on K and V than necessary, because you do not know how fast operations on K/V are; remember that constructions, destructions and assignments are operations as well.
//Do not make more than two operations of amortized O(log N), in contrast to O(1), running time, where N is the number of elements in m_map. Any operation that needs to find a position in the map "from scratch", without being given a nearby position, is such an operation.
//Otherwise favor simplicity over minor speed improvements.
//Time to turn in the solution: You should not take longer than 9 hours, but you may of course be faster. Do not rush, we would not give you this assignment if it were trivial.
//You must develop the solution yourself. You may not let others help you or search for existing solutions. Of course you may use any documentation of the C++ language or the C++ Standard Library. Do not give your solution to others or make it public. It will entice others into sending in plagiarized solutions. If you use an online compiler, make sure that the privacy settings are set to private. Publishing the task description is considered cheating and will void your application.
//
//When you are done, please complete the form and click Submit. Please do not send your solution by email, we will be automatically notified when you submit it here. You can resubmit improved solutions as often as you like. We will take the last submission as your final solution.
//
//Please submit your solution until 20:55 UTC.


template<class K, class V>
class interval_map {
	//friend void IntervalMapTest();

private:
	std::map<K, V> m_map;

public:
	// constructor associates whole range of K with val by inserting (K_min, val)
	// into the map
	interval_map(V const& val) {
		m_map.insert(m_map.begin(), std::make_pair(std::numeric_limits<K>::lowest(), val));
	}

	// Assign value val to interval [keyBegin, keyEnd). 
	// Overwrite previous values in this interval. 
	// Do not change values outside this interval.
	// Conforming to the C++ Standard Library conventions, the interval 
	// includes keyBegin, but excludes keyEnd.
	// If !( keyBegin < keyEnd ), this designates an empty interval, 
	// and assign must do nothing.
	void assign(K const& keyBegin, K const& keyEnd, V const& val) {
		// Here are a few notes about this solution:
		// 1. I'm not happy with all the branches and complexity, but figured it was too late to change direction after committing 3-4 hours.
		//    Probably some branches can be removed... Also better naming
		// 2. With the current interface/definition (which is excluding the end key from the intervals) it is impossible to set a
		//    different value than the one from the constructor for the max possible key, which is std::numeric_limits<K>::max()
		// 3. Using the insert() overloads with iterator hints everywhere for performance.

		if (!(keyBegin < keyEnd))
			return;

		auto it_low = m_map.lower_bound(keyBegin);

		// check to see if the range start is bigger than any other in the map - in which case we would be at the end
		if (it_low == m_map.end()) {
			auto it_low_prev = std::prev(it_low);
			// ensure canonical ranges - insert only if the value is different from the one of the previous range
			if (!(it_low_prev->second == val)) {
				m_map.insert(m_map.cend(), { keyBegin, val });
				m_map.insert(m_map.cend(), { keyEnd, it_low_prev->second });
			}
			return; // early return to avoid extra indentation - we are done here!
		}

		// used to defer the assignment of the new value for the low iterator
		// (otherwise we would need to make a copy of the value of the discontinued range)
		bool should_assign_val_to_low = false;
		// will point to a key which is previous to the inserted low one - the range we have discontinued (if any)
		typename std::map<K, V>::iterator discontinued_range = m_map.end();

		// check to see if there is overlap with the previous range
		if (keyBegin < it_low->first) {
			// get the previous key - we have a guarantee (because of the overlap) that there is such because by
			// default the first key is the minimum possible value of the key type and we are obviously past it
			auto it_low_prev = std::prev(it_low);
			// check the value of the previous key - to ensure canonical ranges
			if (it_low_prev->second == val) {
				// since the value is the same - we won't be inserting a new key - we will just set the start of our new range
				it_low = it_low_prev;
			} else {
				// if the previous key has a different value - we insert our new key with its value
				it_low = m_map.insert(it_low, {keyBegin, val});
				discontinued_range = it_low_prev;
			}
		} else {
			// we have found the exact key - check to see if the value is different (nothing otherwise)
			if (!(it_low->second == val)) {
				// if the value of the exact key we have found is different from what we want to set we
				// must check the value of the previous key with our new value to ensure canonical ranges
				if (it_low != m_map.begin()) {
					// get the previous key if we haven't found the beginning of the map
					auto it_low_prev = std::prev(it_low);
					// check the value of the previous key - to ensure canonical ranges
					if (it_low_prev->second == val) {
						// since the value is the same - we won't be inserting a new key - we will just set the start of our new range
						it_low = it_low_prev;
					} else {
						// since the previous key has a different value - we just update the value of our currently found key (deferred)
						should_assign_val_to_low = true;
					}
				} else {
					// since there is no key before this and the value is different - we just change the value (deferred)
					should_assign_val_to_low = true;
				}
			}
		}
		
		// now lets work on the end of the range - 1 behind what 'upper_bound' returns
		auto it_up_orig = m_map.upper_bound(keyEnd);
		auto it_up = std::prev(it_up_orig);

		// check to see if our end iterator is equal to the beginning of our new range
		if (it_up == it_low) {
			// if we have either discontinued a range by updating the value for a key (which is actually deferred so we don't copy the value)
			// OR if we have discontinued a range by inserting a new key
			if (should_assign_val_to_low || discontinued_range != m_map.end()) {
				it_up = m_map.insert(it_up_orig, { keyEnd, should_assign_val_to_low ? it_low->second : discontinued_range->second });
			} else {
				// use the upper bound we have found
				it_up = it_up_orig;
			}
		} else {
			// check to see if the end of the range we are about to assign is after the start of a previous range
			if (it_up->first < keyEnd) {
				if (it_up->second == val) {
					// if the previous range is for the same value as the newly assigned range - use the original upper bound
					it_up = it_up_orig;
				} else {
					// we need to split that range by introducing another start of a range which will be our end iterator for erasing
					it_up = m_map.insert(it_up_orig, { keyEnd, it_up->second });
				}
			} else {
				// we have found an exact key match for the end of the range
				if (it_up->second == val) {
					// if the value of the next range is the same as the one for the range we are assigning - use the original upper bound
					it_up = it_up_orig;
				}
			}
		}

		if(should_assign_val_to_low)
			it_low->second = val;

		// erase all keys which are between the start and end of our newly assigned range
		m_map.erase(std::next(it_low), it_up);
	}

	// look-up of the value associated with key
	V const& operator[](K const& key) const {
		return (--m_map.upper_bound(key))->second;
	}
};

TEST_CASE("IntervalMapTest") {
	interval_map<int, char> m('a');

	m.assign(0, 3, 'b');

	m.assign(6, 9, 'c');

	m.assign(4, 7, 'd');

	m.assign(6, 9, 'd');


	//m.assign(0, 3, 'b');
	//m.assign(3, 6, 'c');
	//m.assign(6, 8, 'b');
	//m.assign(8, 20, 'a');
	//m.assign(20, 10000, 'g');

	//m.assign(5, 20, 'b');
	//m.assign(6, 18, 'k');
	//m.assign(8, 20, 'b');

	//m.assign(9, 10, 'a');
	//
	//m.assign(4, 6, 'q');
	//
	//m.assign(3, 4, 'b');
	//
	////m.assign(11, 13, 'j');
	//
	////m.assign(-10, 30, 'w');
	//
	//m.assign(2000, 300000, 'f');
	//
	//m.assign(7, 1999, 'a');
	//
	//m.assign(-20, 1999, 'a');
	//
	//m.assign(200000, std::numeric_limits<int>::max(), 'z');
	//m.assign(std::numeric_limits<int>::min(), -666, '/');

	//for (auto& it : m.m_map)
	//	std::cout << std::setw(5) << it.first << " -> " << it.second << std::endl;

	std::cout << std::endl << std::endl;

#define TEST_ELEMENT(x) std::cout << std::setw(5) << #x << " " << m[x] << std::endl

	//TEST_ELEMENT(-100);
	//TEST_ELEMENT(0);
	//TEST_ELEMENT(1);
	//TEST_ELEMENT(2);
	//TEST_ELEMENT(3);
	//TEST_ELEMENT(20);
}
