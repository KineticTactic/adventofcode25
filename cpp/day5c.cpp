#include <algorithm>
#include <charconv>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <vector>

int main() {
	std::ifstream file("./inputs/day5.txt");

	if (!file) {
		std::cerr << "Error opening input file!\n";
		return 1;
	}

	std::string line;
	std::vector<std::pair<long long, long long>> intervals;
	long long min = -1, max = -1;

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

		if (min == -1) {
			min = start;
			max = end;
		}

		if (start < min) {
			min = start;
			std::cout << "Setting minimum: " << min << "\n";
		}
		if (end > max)
			max = end;

		// std::cout << start << ", " << end << "\n";
	}

	long long count = 0;
	long long curr = min;
	long long jump = 1;
	while (curr <= max) {
		std::cout << "Current: " << curr << ", Count: " << count << "\n";
		auto it = std::find_if(intervals.begin(), intervals.end(),
							   [curr](const auto &p) {
								   return p.first <= curr && p.second >= curr;
							   });
		if (it == intervals.end()) {
			jump *= 2;
			auto it = std::find_if(
				intervals.begin(), intervals.end(),
				[curr, jump](const auto &p) {
					return (curr <= p.first && p.first <= curr + jump) ||
						   (curr <= p.second && p.second <= curr + jump);
				});

			if (it != intervals.end())
				jump = 1;
			curr += jump;
		} else {
			count += (it->second - curr + 1);
			curr = it->second + 1;
		}
		// usleep(1000000);
	}
	std::cout << "ANS: " << count << "\n";

	return 0;
}
