#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

struct Node {
	int index; // Position of the node in the line
	std::vector<Node *> children;
	Node *sameAs = nullptr; // if it is same as another node
	long long count = -1; // store number of paths that arise from this node (to
						  // avoid recomputation)
};

void populate(Node *node, std::vector<std::string> &lines, int index,
			  std::unordered_map<uint64_t, Node *> &nodeMap) {
	for (int i = index; i < lines.size(); i++) {
		if (lines[i][node->index] == '^') {
			Node *a = new Node();
			Node *b = new Node();
			a->index = node->index + 1;
			b->index = node->index - 1;
			node->children.push_back(a);
			node->children.push_back(b);
			// If we already encountered a similar node once, then no need of
			// recalculating it
			uint64_t keyA = ((uint64_t)i << 32) | a->index;
			uint64_t keyB = ((uint64_t)i << 32) | b->index;
			if (nodeMap.find(keyA) != nodeMap.end())
				a->sameAs = nodeMap[keyA];
			else {
				populate(a, lines, i + 1, nodeMap);
				nodeMap[keyA] = a;
			}
			if (nodeMap.find(keyB) != nodeMap.end())
				b->sameAs = nodeMap[keyB];
			else {
				populate(b, lines, i + 1, nodeMap);
				nodeMap[keyB] = b;
			}
			break;
		}
	}
}

long long countPaths(Node *node) {
	if (node->sameAs != nullptr)
		return countPaths(node->sameAs);
	if (node->children.size() == 0)
		return 1;
	if (node->count != -1)
		return node->count;

	long long sum = 0;
	for (Node *child : node->children) {
		sum += countPaths(child);
	}
	node->count = sum;
	return sum;
}

int main() {
	std::ifstream file("./inputs/day7.txt");

	if (!file) {
		std::cerr << "Error opening input file!\n";
		return 1;
	}

	std::string line;
	std::vector<std::string> lines;

	std::getline(file, line);
	Node *head = new Node();
	head->index = line.find('S');

	while (std::getline(file, line)) {
		lines.push_back(line);
	}

	std::unordered_map<uint64_t, Node *> nodeMap;
	std::cout << "Populating tree...\n";
	populate(head, lines, 0, nodeMap);
	std::cout << "Counting paths...\n";
	long long ans = countPaths(head);

	std::cout << "ANS: " << ans << std::endl;

	return 0;
}
