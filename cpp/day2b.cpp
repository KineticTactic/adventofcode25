#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>

long long pow10(int x) {
	long long r = 1;
	while (x-- > 0)
		r *= 10;
	return r;
}

long long repeated(int n, int l, int k) {
	long long sum = 0;
	for (int i = 0; i < k; i++) {
		sum = sum * pow10(l) + n;
	}
	return sum;
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
			long long intervalStart, intervalEnd;

			if (l == startStr.size())
				intervalStart = start;
			else
				intervalStart = pow10(l - 1);

			if (l == endStr.size())
				intervalEnd = end;
			else
				intervalEnd = pow10(l) - 1;

			std::unordered_set<long long> found;

			for (int x = 2; x <= l; x++) {
				if (l % x != 0)
					continue;

				long long firstFrac = intervalStart / pow10(l - l / x);

				std::cout << x << ": ";

				while (true) {
					long long num = repeated(firstFrac, l / x, x);
					if (num >= intervalStart && num <= intervalEnd) {
						std::cout << num << " ";
						found.insert(num);
					} else if (num > intervalEnd)
						break;
					firstFrac++;
				}
				std::cout << "\n";
			}
			std::cout << "\n";

			for (const auto &i : found)
				total += i;
		}
	}
	std::cout << "TOTAL: " << total << "\n";

	return 0;
}
