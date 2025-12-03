#include <fstream>
#include <iostream>
#include <string>

int main() {
	std::ifstream file("./inputs/day3.txt");

	if (!file) {
		std::cerr << "Error opening input file!\n";
		return 1;
	}

	std::string line;
	int sum = 0;

	while (std::getline(file, line)) {
		std::cout << line << ": ";

		int out;

		char largest = line[0];
		int largestIndex = 0;

		for (int i = 1; i < line.size(); i++) {
			if (line[i] > largest) {
				largest = line[i];
				largestIndex = i;
			}
		}

		if (largestIndex == line.size() - 1) {
			char secondLargest = line[0];
			for (int i = 1; i < line.size() - 1; i++) {
				if (line[i] > secondLargest) {
					secondLargest = line[i];
				}
			}
			out = (secondLargest - '0') * 10 + (largest - '0');
		} else {
			char secondLargest = line[largestIndex + 1];
			for (int i = largestIndex + 2; i < line.size(); i++) {
				if (line[i] > secondLargest) {
					secondLargest = line[i];
				}
			}
			out = (largest - '0') * 10 + (secondLargest - '0');
		}
		std::cout << out << "\n";

		sum += out;
	}

	std::cout << "ANS: " << sum << "\n";

	return 0;
}
