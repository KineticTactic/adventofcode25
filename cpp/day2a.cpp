#include <fstream>
#include <iostream>
#include <string>

void print_bytes_hex(const std::string &s) {
	for (unsigned char c : s)
		printf("%02X ", c);
	printf("\n");
}

long long pow10(int x) {
	long long r = 1;
	while (x-- > 0)
		r *= 10;
	return r;
}

int main() {
	std::ifstream file("inputs/day2.txt");

	if (!file) {
		std::cerr << "File not found!\n";
		return 1;
	}

	std::string pair;
	long long total = 0;

	while (std::getline(file, pair, ',')) {
		if (pair.back() == '\n')
			pair.pop_back();
		if (pair.back() == '\r')
			pair.pop_back();

		size_t pos = pair.find('-');
		std::string startStr = pair.substr(0, pos);
		std::string endStr = pair.substr(pos + 1);
		long long start = std::stoll(startStr);
		long long end = std::stoll(endStr);

		std::cout << start << ", " << end << "\n";

		for (int l = startStr.size(); l <= endStr.size(); l++) {
			if (l % 2 == 1)
				continue;
			long long intervalStart, intervalEnd;

			if (l == startStr.size())
				intervalStart = start;
			else
				intervalStart = pow10(l - 1);

			if (l == endStr.size())
				intervalEnd = end;
			else
				intervalEnd = pow10(l) - 1;

			long long firstHalf = intervalStart / pow10(l / 2);

			while (true) {
				long long num = firstHalf * pow10(l / 2) + firstHalf;
				if (num >= intervalStart && num <= intervalEnd) {
					total += num;
					std::cout << num << " ";
				} else if (num > intervalEnd)
					break;
				firstHalf++;
			}
			std::cout << "\n";
		}
	}
	std::cout << "TOTAL: " << total << "\n";

	return 0;
}
