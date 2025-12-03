#include <fstream>
#include <iostream>
#include <string>

long long findMax(std::string &line, int n) {
	int curLargestIndex = 0;
	char curLargest = line[0];
	long long out = 0;
	for (int i = 0; i < n; i++) {
		for (int j = curLargestIndex; j <= line.size() - n + i; j++) {
			if (line[j] > curLargest) {
				curLargest = line[j];
				curLargestIndex = j;
			}
		}
		out = out * 10 + (curLargest - '0');

		curLargestIndex++;
		curLargest = line[curLargestIndex];
	}
	return out;
}

int main() {
	std::ifstream file("./inputs/day3.txt");

	if (!file) {
		std::cerr << "Error opening input file!\n";
		return 1;
	}

	std::string line;
	int sum = 0;

	while (std::getline(file, line)) {
		int out = findMax(line, 2);
		std::cout << line << ": " << out << "\n";
		sum += out;
	}

	std::cout << "ANS: " << sum << "\n";

	return 0;
}
