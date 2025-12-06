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

int remove(std::vector<std::string> &lines,
		   std::vector<std::string> &updatedLines) {
	int count = 0;
	for (int i = 0; i < lines.size(); i++) {
		for (int j = 0; j < lines[0].size(); j++) {
			updatedLines[i][j] = '.';
			if (lines[i][j] == '.')
				continue;
			if (countNeighbours(lines, i, j) < 4) {
				count++;
			} else {
				updatedLines[i][j] = '@';
			}
		}
	}
	std::cout << "Removed " << count << " rolls\n";
	return count + (count > 0 ? remove(updatedLines, lines) : 0);
}

int main() {
	std::ifstream file("./inputs/day4.txt");

	if (!file) {
		std::cerr << "Error opening input file!\n";
		return 1;
	}

	std::vector<std::string> lines;
	std::vector<std::string> updatedLines;
	std::string line;
	while (std::getline(file, line)) {
		lines.push_back(line);
		updatedLines.push_back(line);
	}

	int count = remove(lines, updatedLines);

	std::cout << "ANS: " << count << "\n";

	return 0;
}
