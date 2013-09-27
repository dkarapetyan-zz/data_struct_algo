#include <iostream>
#include <list>
using std::list;

bool cyclicopt(list<int> my_list);

int main() {
	list<int> my_list;

	std::cout << cyclicopt(my_list);
	return 0;
}



bool cyclicopt(list<int> my_list) { // check to see if list is cyclic. O(n) algorithm using two pointers
	std::list::iterator slow = my_list.begin();
	auto fast = ++my_list.begin();

	while (fast != slow)  // do we reach null first, or fast==slow
	{

if (fast == my_list.end() || fast + 1 == my_list.end())  //base case
			return false;

		else { // advance pointers
			++slow;
			fast += 2;
		}
	}
	return true; // if we exit while loop without a return, then fast == slow, which implies cyclic
}
