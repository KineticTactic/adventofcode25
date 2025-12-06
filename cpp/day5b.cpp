#include <charconv>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>

#define START 97
#define END 98

void insertInterval(std::map<long long, char> &intervals, long long start,
					long long end) {
	if (intervals.lower_bound(end) == intervals.begin() ||
		intervals.lower_bound(start) == intervals.end()) {
		intervals[start] = START;
		intervals[end] = END;
		return;
	}

	auto startLBound = intervals.lower_bound(start);
	auto endLBound = intervals.lower_bound(end);

	std::cout << "lower_bound(" << start << ") -> ";
	if (startLBound == intervals.end())
		std::cout << "end\n";
	else
		std::cout << startLBound->first << "\n";

	std::cout << "lower_bound(" << end << ") -> ";
	if (endLBound == intervals.end())
		std::cout << "end\n";
	else
		std::cout << endLBound->first << "\n";

	if (startLBound != endLBound) {
		if (startLBound->second == END)
			startLBound = std::next(startLBound);
		if (endLBound->second == END) {
			endLBound = std::prev(endLBound);
		}

		// std::cout << "Erasing!: " << (endLBound - startLBound) << "\n";
		// if (startLBound != endLBound)
		// 	intervals.erase(startLBound, endLBound);
		if (startLBound != endLBound && endLBound->first >= end) {
			std::cout << "Erasing keys in range: [";
			if (startLBound == intervals.end())
				std::cout << "end";
			else
				std::cout << startLBound->first;

			std::cout << ", ";

			if (endLBound == intervals.end())
				std::cout << "end";
			else
				std::cout << endLBound->first;

			std::cout << ")\n";

			intervals.erase(startLBound, endLBound);
		}
	}

	startLBound = intervals.lower_bound(start);
	endLBound = intervals.lower_bound(end);

	if (startLBound == endLBound) {
		intervals[start] = START;
		intervals[end] = END;
	} else if (startLBound->second == END &&
			   std::prev(endLBound) == startLBound) {
		intervals.erase(startLBound);

	} else if (startLBound->second == START &&
			   std::prev(endLBound) == startLBound) {
		intervals.erase(startLBound);
	} else if (startLBound->second == END &&
			   std::prev(endLBound)->second == START) {
		intervals.erase(startLBound);
		intervals.erase(std::prev(endLBound));
	} else {
		std::cout << "WTF!\n";
		std::cout << "Start: " << start << ", End: " << end << "\n";
		std::cout << "SLB: " << startLBound->first << "[" << startLBound->second
				  << "]\n";
		std::cout << "ELB: " << endLBound->first << "[" << endLBound->second
				  << "]\n";
		std::cout << "Are equal: " << (startLBound == endLBound) << "\n";
	}
}

long long coutTotal()

	int main() {
	std::ifstream file("./inputs/test.txt");

	if (!file) {
		std::cerr << "Error opening input file!\n";
		return 1;
	}

	std::string line;
	std::map<long long, char> intervals;
	long long count = 0;

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

		insertInterval(intervals, start, end + 1);

		std::cout << start << ", " << end << "\n";
	}

	std::cout << "MERGED INTERVALS:" << intervals.size() << "\n";

	for (auto it = intervals.begin(); it != intervals.end(); it++) {
		long long start = it->first;
		it++;
		long long end = it->first;
		count += end - start;
		std::cout << start << ", " << end << "\n";
	}

	std::cout << "ANS: " << count << "\n";

	return 0;
}
