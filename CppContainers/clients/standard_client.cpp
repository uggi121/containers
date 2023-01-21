#include "../containers/vector_container.h"
#include "../containers/list_container.h"

void run_test() {
	list_container<int> vec;

	for (int i = 0; i < 100; i++) {
		try {
			vec.push_front(i);
		}
		catch (const std::out_of_range& exc) {
			std::cout << exc.what() << std::endl;
		}
	}

	while (vec.size() > 0) {
		auto x = vec.pop_front();
		std::cout << "Popped: " << x << std::endl;
	}
}

int main() {
	run_test();
}