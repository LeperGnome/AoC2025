#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

const char *dataPath = "days/day4/data.txt";

const char ROLL_SIG = '@';
const char EMPTY_SIG = '.';

std::vector<std::string> readData(char delim) {
	std::ifstream ifs(dataPath);
	std::string line;
	std::vector<std::string> result;
	while (std::getline(ifs, line, delim)) {
		result.push_back(line);
	}
	return result;
}

size_t getAndRmAdjacentRollsCount(std::vector<std::string> map, int x, int y) {
	size_t count = 0;
	int dc[3] = {-1, 0, 1};
	for (auto dx : dc) {
		for (auto dy : dc) {
			int nx = dx + x;
			int ny = dy + y;
			if (nx < 0 || nx >= int(map.size()) || ny < 0 ||
				ny >= int(map[nx].length()))
				continue;
			if (dx == 0 && dy == 0)
				continue;
			auto c = map[nx][ny];
			if (c == ROLL_SIG) {
				count++;
			}
		}
	}
	return count;
}

long solution(std::vector<std::string> data) {
	long out = 0;
	bool got = false;
	do {
		got = false;
		for (size_t ridx = 0; ridx < data.size(); ridx++) {
			auto row = data[ridx];
			std::cout << row << std::endl;
			for (size_t cidx = 0; cidx < row.length(); cidx++) {
				if (row[cidx] != ROLL_SIG)
					continue;
				auto arc = getAndRmAdjacentRollsCount(data, ridx, cidx);
				if (arc < 4) {
					out++;
					got = true;
					data[ridx][cidx] = EMPTY_SIG;
				}
			}
		}
	} while (got);
	return out;
}

int main() {
	auto data = readData('\n');
	std::cout << data.size() << std::endl;
	auto res = solution(data);
	std::cout << "Result: " << res << std::endl;
	return 0;
}
