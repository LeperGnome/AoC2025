#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <ostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

const char *dataPath = "days/day9/data_example.txt";

struct tile {
	long x;
	long y;

	bool operator==(const tile &other) const {
		return x == other.x && y == other.y;
	}

	bool operator<(const tile &other) const {
		return std::tie(x, y) < std::tie(other.x, other.y);
	}
};

std::vector<std::string> split_string(const std::string &str, char delim) {
	std::vector<std::string> tokens;
	std::stringstream ss(str);
	std::string token;
	while (std::getline(ss, token, delim)) {
		tokens.push_back(token);
	}
	return tokens;
}

void drawMap(std::vector<tile> tiles) {
	long minx = std::numeric_limits<long>::max(),
		 miny = std::numeric_limits<long>::max();
	long maxx = 0, maxy = 0;
	for (auto t : tiles) {
		minx = std::min(t.x, minx);
		maxx = std::max(t.x, maxx);
		miny = std::min(t.y, miny);
		maxy = std::max(t.y, maxy);
	}

	std::set<tile> tileset(tiles.begin(), tiles.end());

	std::cout << minx << " x " << maxx << " ; " << miny << " y " << maxy
			  << std::endl;
	const auto off = 3;
	for (auto y = miny - off; y <= maxy + off; y++) {
		for (auto x = minx - off; x <= maxx + off; x++) {
			// std::cout << x << ";" << y << " ";
			if (tileset.contains(tile(x, y))) {
				std::cout << '#';
			} else {
				std::cout << '.';
			}
		}
		std::cout << std::endl;
	}
}

std::vector<tile> readData(char delim) {
	std::ifstream ifs(dataPath);
	std::string buf;
	std::vector<tile> lines;
	while (std::getline(ifs, buf, delim)) {
		auto nums = split_string(buf, ',');
		tile t = {
			std::stol(nums[0]),
			std::stol(nums[1]),
		};
		lines.push_back(t);
	}
	return lines;
}

std::vector<std::pair<tile, tile>>
compose_all_pairs(const std::vector<tile> &data) {
	std::vector<std::pair<tile, tile>> res;
	for (size_t i = 0; i < data.size() - 1; i++) {
		for (size_t j = 0; j < data.size(); j++) {
			res.push_back({data[i], data[j]});
		}
	}
	return res;
}

long area(tile t1, tile t2) {
	return std::abs(t1.x - t2.x + 1) * std::abs(t1.y - t2.y + 1);
}

void printTile(const tile t) {
	std::cout << '(' << t.x << ", " << t.y << ')' << std::endl;
}

long solution(std::vector<tile> data) {
	drawMap(data);
	std::vector<std::pair<tile, tile>> all_pairs = compose_all_pairs(data);

	std::cout << "All pairs " << all_pairs.size() << std::endl;
	long res = 0;

	long minx = std::numeric_limits<long>::max(),
		 miny = std::numeric_limits<long>::max();
	long maxx = 0, maxy = 0;
	for (auto t : data) {
		minx = std::min(t.x, minx);
		maxx = std::max(t.x, maxx);
		miny = std::min(t.y, miny);
		maxy = std::max(t.y, maxy);
	}

	for (auto p : all_pairs) {
		res = std::max(res, area(p.first, p.second));
	}
	return res;
}

int main() {
	auto data = readData('\n');
	auto res = solution(data);
	std::cout << "Result: " << res << std::endl;
	return 0;
}
