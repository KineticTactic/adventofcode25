#include <fstream>
#include <iostream>
#include <set>
#include <string>

int main() {
	std::ifstream file("./inputs/test.txt");

	if (!file) {
		std::cerr << "Error opening input file!\n";
		return 1;
	}

	std::string line;
	std::set<int> beams;

	std::getline(file, line);
	beams.insert(line.find('S'));

	int splitCounter = 0;

	while (std::getline(file, line)) {
		std::set<int> splitBeams;
		std::cout << line << "\n";
		for (int beam : beams) {
			if (line[beam] == '^') {
				splitBeams.insert(beam - 1);
				splitBeams.insert(beam + 1);
				splitCounter++;
			} else {
				splitBeams.insert(beam);
			}
		}
		beams = splitBeams;
	}

	std::cout << "ANS: " << splitCounter << std::endl;

	return 0;
}
