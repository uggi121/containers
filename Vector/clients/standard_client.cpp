#include "vector_container.h"

void run_test() {
	vector_container<int> vec(10);

	for (int i = 0; i < 100000; i++) {
		try {
			vec.push_front(i);
		}
		catch (const std::out_of_range& exc) {
			std::cout << exc.what() << std::endl;
		}
	}

	while (vec.size() > 0) {
		auto x = vec.pop_front();
	}
}

int main() {
	run_test();
}