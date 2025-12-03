#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

const char *dataPath = "days/day3/data.txt";

std::vector<std::string> readData(char delim) {
	std::ifstream ifs(dataPath);
	std::string rangeBuf;
	std::vector<std::string> result;
	while (std::getline(ifs, rangeBuf, delim)) {
		result.push_back(rangeBuf);
	}
	return result;
}

long getMaxJolts(std::string bank) {
	std::string res;
	int pow = 11;
	size_t prev_idx = 0;

	for (auto p = pow; p >= 0; p--) {
		int mx = 0;
		size_t mx_idx = 0;

		for (size_t idx = 0; idx < bank.length() - p; idx++) {
			int num = std::atoi(std::string{bank[idx]}.c_str());
			if (num > mx && (idx > prev_idx || p == pow)) {
				mx = num;
				mx_idx = idx;
			}
		}

		res.push_back(bank[mx_idx]);
		prev_idx = mx_idx;
	}
	std::cout << res << std::endl;
	return std::atol(res.c_str());
}

long solution(std::vector<std::string> data) {
	long out = 0;
	for (auto bank : data) {
		std::cout << bank << std::endl;
		out += getMaxJolts(bank);
	}
	return out;
}

int main() {
	auto data = readData('\n');
	auto res = solution(data);
	std::cout << "Result: " << res << std::endl;
	return 0;
}
