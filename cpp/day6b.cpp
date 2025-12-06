#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main() {
	std::ifstream file("./inputs/day6.txt");

	if (!file) {
		std::cerr << "Error opening input file!\n";
		return 1;
	}

	std::string line;
	std::vector<std::string> lines;

	while (std::getline(file, line)) {
		lines.push_back(line);
	}

	std::vector<int> columnSeparators;
	std::vector<char> operators;

	for (int i = 0; i < lines[0].size(); i++) {
		bool allSpaces = true;
		for (int j = 0; j < lines.size(); j++) {
			if (lines[j][i] != ' ') {
				allSpaces = false;
				break;
			}
		}
		if (allSpaces)
			columnSeparators.push_back(i);
		char lastChar = lines[lines.size() - 1][i];
		if (lastChar == '+' || lastChar == '*') {
			operators.push_back(lastChar);
		}
	}
	columnSeparators.push_back(lines[0].size());

	long long total = 0;
	for (int i = 0; i < columnSeparators.size(); i++) {
		std::cout << "Col seprator[" << i << "]: " << columnSeparators[i]
				  << std::endl;

		int startIndex = i > 0 ? columnSeparators[i - 1] + 1 : 0;
		int endIndex = columnSeparators[i];

		long long columnAns = operators[i] == '+' ? 0 : 1;
		for (int j = startIndex; j < endIndex; j++) {
			int num = 0;
			for (int k = 0; k < lines.size() - 1; k++) {
				char c = lines[k][j];
				if (lines[k][j] == ' ')
					continue;
				int digit = c - '0';
				num = num * 10 + digit;
			}

			std::cout << "Num: " << num << std::endl;

			if (operators[i] == '+')
				columnAns += num;
			else
				columnAns *= num;
		}

		total += columnAns;
	}

	std::cout << "ANS: " << total << "\n";

	return 0;
}
