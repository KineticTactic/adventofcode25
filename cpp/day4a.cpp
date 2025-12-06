#include <fstream>
#include <iostream>
#include <vector>

int getCell(std::vector<std::string> &lines, int x, int y) {
	if (x >= 0 && x < lines[0].size() && y >= 0 && y < lines.size())
		return lines[x][y] == '@' ? 1 : 0;
	return 0;
}

int countNeighbours(std::vector<std::string> &lines, int x, int y) {
	int count = 0;
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (i == 0 && j == 0)
				continue;
			count += getCell(lines, x + i, y + j);
		}
	}

	return count;
}

int main() {
	std::ifstream file("./inputs/day4.txt");

	if (!file) {
		std::cerr << "Error opening input file!\n";
		return 1;
	}

	std::vector<std::string> lines;
	std::string line;
	while (std::getline(file, line)) {
		lines.push_back(line);
	}

	int count = 0;

	for (int i = 0; i < lines.size(); i++) {
		std::cout << "'" << lines[i] << "'\n";

		for (int j = 0; j < lines[0].size(); j++) {
			if (lines[i][j] == '.')
				continue;
			if (countNeighbours(lines, i, j) < 4) {
				count++;
			}
		}
	}

	std::cout << "ANS: " << count << "\n";

	return 0;
}
