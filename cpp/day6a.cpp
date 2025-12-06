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
	std::vector<std::vector<int>> nums;

	while (std::getline(file, line)) {
		if (line[0] == '+' || line[0] == '*')
			break;

		std::vector<int> lineNums;
		std::istringstream lineStream(line);
		int num;
		while (lineStream >> num) {
			std::cout << "Got: " << num << std::endl;
			lineNums.push_back(num);
		}
		nums.push_back(lineNums);
	}

	std::string op;
	int i = 0;
	long long total = 0;
	std::istringstream lineStream(line);
	while (lineStream >> op) {
		if (op == "+") {
			long long ans = 0;
			for (int j = 0; j < nums.size(); j++) {
				ans += nums[j][i];
			}
			std::cout << "Row " << i << " ans: " << ans << "\n";
			total += ans;
		} else if (op == "*") {
			long long ans = 1;
			for (int j = 0; j < nums.size(); j++) {
				ans *= nums[j][i];
			}
			std::cout << "Row " << i << " ans: " << ans << "\n";
			total += ans;
		} else {
			std::cerr << "Unknown operator!: " << op << std::endl;
			return 1;
		}
		i++;
	}

	std::cout << "ANS: " << total << "\n";

	return 0;
}
