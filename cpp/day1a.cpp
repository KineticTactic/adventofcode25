#include <charconv>
#include <fstream>
#include <iostream>
#include <string>

int main() {
	std::ifstream file("./inputs/day1.txt");

	if (!file) {
		std::cerr << "Failed to open input file!\n";
		return 1;
	}

	std::string line;
	int sum = 50;
	int count = 0;

	while (std::getline(file, line)) {
		int sign = line[0] == 'L' ? -1 : 1;
		int val;

		// We could've used std::atoi but I wanted to explore newer C++17/20
		// methods Using std::from_chars we do not create any copy of the string
		std::from_chars_result res =
			std::from_chars(line.data() + 1, line.data() + line.size(), val);

		if (res.ec == std::errc::invalid_argument) {
			std::cerr << "Failed to parse integer! Line: " << line << "\n";
			return 1;
		}

		// Add and loop back to [0, 99]
		sum += sign * val;
		sum %= 100;
		if (sum < 0)
			sum += 100;

		// Increment
		if (sum == 0)
			count++;
	}

	std::cout << count << "\n";

	return 0;
}
