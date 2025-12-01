#include <iostream>
#include <fstream>
#include <string>
#include <charconv>
#include <cmath>

int main() {
	std::ifstream file("./inputs/day1a.txt");

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
		std::from_chars_result res = std::from_chars(line.data() + 1, line.data() + line.size(), val);

		if (res.ec == std::errc::invalid_argument) {
			std::cerr << "Failed to parse integer! Line: " << line << "\n";
			return 1;
		}

		int prevCount = count; // This is purely for debugging

		// We are doing integer division to find which multiple of 100 it is. This does not account for zeroes.
		int newSum = sum + sign * val;
		count += std::abs(newSum) / 100 - sum / 100;
		// If we land on a zero, increment
		if (newSum == 0) count++; 
		// If we CROSS zero while going from positive to negative, increment once.
		if (sum != 0 && newSum < 0) count++;

		std::cout << "From: " << sum << ", To: " << (sum + sign * val) << ", count: " << (count - prevCount) << "\n";

		sum = newSum;
		sum %= 100;
		if (sum < 0) sum += 100;
	}

	std::cout << count << "\n";

	return 0;
}
