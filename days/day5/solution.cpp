#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

const char *dataPath = "days/day5/data.txt";

using range = std::pair<long, long>;

std::pair<std::vector<range>, std::vector<long>> readData(char delim) {
	std::ifstream ifs(dataPath);
	std::string rangeBuf;
	std::vector<range> ranges;
	while (std::getline(ifs, rangeBuf, delim)) {
		if (rangeBuf.empty())
			break;
		auto pos = rangeBuf.find('-');
		range rg = {
			std::atol(rangeBuf.substr(0, pos).c_str()),
			std::atol(rangeBuf.substr(pos + 1).c_str()),
		};
		ranges.push_back(rg);
	}

	std::string avbuf;
	std::vector<long> available;
	while (std::getline(ifs, avbuf, delim)) {
		long av = std::atol(avbuf.c_str());
		available.push_back(av);
	}
	return std::pair<std::vector<range>, std::vector<long>>(ranges, available);
}

std::vector<range> compressRanges(std::vector<range> ranges) {
	std::vector<range> compressed = {};

	for (auto rg_raw : ranges) {
		bool intersect = false;
		for (auto &rg_comp : compressed) {
			// Intersect
			if (std::min(rg_raw.second, rg_comp.second) >=
				std::max(rg_raw.first, rg_comp.first) - 1) {
				intersect = true;
				auto new_comp = range{
					std::min(rg_raw.first, rg_comp.first),
					std::max(rg_raw.second, rg_comp.second),
				};
				rg_comp = new_comp;
			}
		}
		if (!intersect) {
			compressed.push_back(rg_raw);
		}
	}

	return compressed;
}

long solution(std::vector<range> freshRanges, std::vector<long> _) {
	auto compressed = compressRanges(freshRanges);

	while (true) {
		auto new_compressed = compressRanges(compressed);
		if (new_compressed == compressed)
			break;
		compressed = new_compressed;
	}

	std::sort(compressed.begin(), compressed.end());

	long res = 0;
	for (auto rg : compressed) {
		std::cout << rg.first << "-" << rg.second << std::endl;
		res += rg.second - rg.first + 1;
	}
	return res;
}

int main() {
	auto data = readData('\n');
	auto res = solution(data.first, data.second);
	std::cout << "Result: " << res << std::endl;
	return 0;
}
