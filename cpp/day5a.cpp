#include <charconv>
#include <fstream>
#include <iostream>
#include <vector>

int main() {
	std::ifstream file("./inputs/day5.txt");

	if (!file) {
		std::cerr << "Error opening input file!\n";
		return 1;
	}

	std::string line;
	std::vector<std::pair<long long, long long>> intervals;

	while (std::getline(file, line)) {
		if (line.size() == 0)
			break;
		std::string_view view = line;
		auto pos = view.find("-");
		std::string_view startStr = view.substr(0, pos);
		std::string_view endStr = view.substr(pos + 1);
		long long start, end;
		std::from_chars(startStr.data(), startStr.data() + startStr.size(),
						start);
		std::from_chars(endStr.data(), endStr.data() + endStr.size(), end);
		intervals.push_back({start, end});

		std::cout << start << ", " << end << "\n";
	}

	int count = 0;

	while (std::getline(file, line)) {
		std::cout << line;
		long long num;
		std::from_chars(line.data(), line.data() + line.size(), num);

		for (const auto &[start, end] : intervals) {
			if (start <= num && num <= end) {
				count++;
				std::cout << " OK";
				break;
			}
		}
		std::cout << "\n";
	}
	std::cout << "ANS: " << count << "\n";

	return 0;
}
