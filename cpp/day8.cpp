#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

class UF {
  private:
	std::vector<int> tree;

	int root(int n) {
		int cur = n;
		while (tree[cur] >= 0) {
			if (tree[tree[cur]] >= 0)
				tree[cur] = tree[tree[cur]];
			cur = tree[cur];
		}
		return cur;
	}

  public:
	UF(int n) : tree(n, -1) {}

	void join(int n, int m) {
		int nRoot = root(n);
		int mRoot = root(m);
		if (nRoot == mRoot)
			return;

		if (tree[nRoot] <= tree[mRoot]) {
			tree[nRoot] += tree[mRoot];
			tree[mRoot] = nRoot;
		} else {
			tree[mRoot] += tree[nRoot];
			tree[nRoot] = mRoot;
		}
	}
	int find(int n) { return root(n); }
	int connected(int n, int m) { return (root(n) == root(m)); }

	std::vector<int> sizes() {
		std::vector<int> ret;
		for (int i = 0; i < tree.size(); i++) {
			if (tree[i] < 0)
				ret.push_back(-tree[i]);
		}
		return ret;
	}
};

struct Box {
	int x, y, z;
	void print() { std::cout << "(" << x << ", " << y << ", " << z << ")"; }
};

double dist(const Box &a, const Box &b) {
	double dx = (double)a.x - b.x;
	double dy = (double)a.y - b.y;
	double dz = (double)a.z - b.z;
	return dx * dx + dy * dy + dz * dz;
}

int main() {
	std::ifstream file("./inputs/day8.txt");

	if (!file) {
		std::cerr << "Failed to open input file!\n";
		return 1;
	}

	std::vector<Box> boxes;
	std::string line;

	while (std::getline(file, line)) {
		Box box;
		auto comma1 = line.find_first_of(',');
		auto comma2 = line.find_last_of(',');
		std::string x = line.substr(0, comma1);
		std::string y = line.substr(comma1 + 1, comma2);
		std::string z = line.substr(comma2 + 1);
		box.x = std::stoi(x);
		box.y = std::stoi(y);
		box.z = std::stoi(z);
		boxes.push_back(box);
	}

	std::vector<std::pair<int, int>> boxPairs;

	for (int i = 0; i < boxes.size(); i++) {
		std::cout << "Box " << i << ": " << boxes[i].x << ", " << boxes[i].y
				  << ", " << boxes[i].z << "\n";

		for (int j = i + 1; j < boxes.size(); j++) {

			boxPairs.emplace_back(i, j);
		}
	}

	std::sort(boxPairs.begin(), boxPairs.end(),
			  [&boxes](const std::pair<int, int> &a,
					   const std::pair<int, int> &b) -> bool {
				  return dist(boxes[a.first], boxes[a.second]) <
						 dist(boxes[b.first], boxes[b.second]);
			  });

	UF uf(boxes.size());

	int connectionsToBeMade = 1000;
	long long ans1, ans2;
	for (int i = 0; i < boxPairs.size(); i++) {
		std::cout << i << ": ";
		boxes[boxPairs[i].first].print();
		std::cout << ", ";

		boxes[boxPairs[i].second].print();
		std::cout << "  ";
		std::cout << boxPairs[i].first << ", " << boxPairs[i].second << "\t"
				  << dist(boxes[boxPairs[i].first], boxes[boxPairs[i].second])
				  << "\n";

		uf.join(boxPairs[i].first, boxPairs[i].second);

		std::vector<int> sizes = uf.sizes();
		if (i == connectionsToBeMade) {
			std::vector<int> sizes = uf.sizes();
			std::sort(sizes.begin(), sizes.end(), std::greater<>());
			ans1 = sizes[0] * sizes[1] * sizes[2];
		}

		if (sizes.size() == 1) {
			ans2 = (long long)boxes[boxPairs[i].first].x *
				   (long long)boxes[boxPairs[i].second].x;
			break;
		}
	}

	std::cout << "ANS 1: " << ans1 << "\n";
	std::cout << "ANS 2: " << ans2 << "\n";

	return 0;
}
