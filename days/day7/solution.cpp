#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <unordered_map>
#include <vector>

const char *dataPath = "days/day7/data.txt";

using range = std::pair<long, long>;

std::vector<std::string> readData(char delim) {
	std::ifstream ifs(dataPath);
	std::string buf;
	std::vector<std::string> lines;
	while (std::getline(ifs, buf, delim)) {
		lines.push_back(buf);
	}
	return lines;
}

void printme(std::unordered_map<size_t, size_t> m, int len) {
	for (int i = 0; i < len; i++) {
		if (m.count(i)) {
			std::cout << m[i];
		} else {
			std::cout << '.';
		}
	}
	std::cout << std::endl;
}

long solution(std::vector<std::string> data) {
	size_t init_c_idx = data[0].find('S');
	std::unordered_map<size_t, size_t> prev_idxs;
	prev_idxs[init_c_idx] = 1;

	for (size_t idx = 2; idx < data.size(); idx += 2) {
		std::unordered_map<size_t, size_t> new_idxs;
		auto row = data[idx];
		for (size_t cidx = 0; cidx < row.length(); cidx++) {
			if (row[cidx] == '^' && prev_idxs.count(cidx)) {
				new_idxs[cidx - 1] += prev_idxs[cidx];
				new_idxs[cidx + 1] += prev_idxs[cidx];
			} else if (prev_idxs.count(cidx)) {
				new_idxs[cidx] += prev_idxs[cidx];
			}
		}
		prev_idxs = new_idxs;
		// printme(prev_idxs, data[0].length());
	}

	size_t res = 0;
	for (auto n : prev_idxs) {
		res += n.second;
	}
	return res;
}

int main() {
	auto data = readData('\n');
	auto res = solution(data);
	std::cout << "Result: " << res << std::endl;
	return 0;
}
