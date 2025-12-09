#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

const char *dataPath = "days/day8/data.txt";

// const auto CONN = 1000;

struct jbox {
	double x;
	double y;
	double z;

	bool operator==(const jbox &other) const {
		return x == other.x && y == other.y && z == other.z;
	}

	bool operator<(const jbox &other) const { return x < other.x; }
};

void print_jbox(const jbox &jb) {
	std::cout << '\t' << jb.x << ',' << jb.y << ',' << jb.z << std::endl;
}

using circuit = std::set<jbox>;

void print_circuit(circuit cs) {
	std::cout << "Circuit: [" << std::endl;
	for (auto const &c : cs) {
		print_jbox(c);
	}
	std::cout << "]" << std::endl;
}

double get_distance(const jbox jb1, const jbox jb2) {
	return std::sqrt(std::pow(jb1.x - jb2.x, 2) + std::pow(jb1.y - jb2.y, 2) +
					 std::pow(jb1.z - jb2.z, 2));
}

std::vector<std::string> split_string(const std::string &str, char delim) {
	std::vector<std::string> tokens;
	std::stringstream ss(str);
	std::string token;
	while (std::getline(ss, token, delim)) {
		tokens.push_back(token);
	}
	return tokens;
}

std::vector<jbox> readData(char delim) {
	std::ifstream ifs(dataPath);
	std::string buf;
	std::vector<jbox> lines;
	while (std::getline(ifs, buf, delim)) {
		auto nums = split_string(buf, ',');
		jbox jb = {
			std::stod(nums[0]),
			std::stod(nums[1]),
			std::stod(nums[2]),
		};
		lines.push_back(jb);
	}
	return lines;
}

std::vector<std::pair<jbox, jbox>>
compose_all_pairs(const std::vector<jbox> &data) {
	std::vector<std::pair<jbox, jbox>> res;
	for (size_t i = 0; i < data.size() - 1; i++) {
		for (size_t j = i + 1; j < data.size(); j++) {
			res.push_back({data[i], data[j]});
		}
	}
	return res;
}

int is_part_of_circuit(const std::vector<circuit> &circuits, const jbox jb) {
	for (size_t i = 0; i < circuits.size(); i++) {
		auto c = circuits[i];
		if (c.contains(jb)) {
			return i;
		}
	}
	return -1;
}

long solution(std::vector<jbox> data) {
	std::set<jbox> dataset;
	dataset.insert(data.begin(), data.end());

	std::vector<std::pair<jbox, jbox>> all_pairs = compose_all_pairs(data);

	std::cout << "All pairs " << all_pairs.size() << std::endl;
	std::sort(all_pairs.begin(), all_pairs.end(),
			  [](const std::pair<jbox, jbox> a, const std::pair<jbox, jbox> b) {
				  return get_distance(a.first, a.second) <
						 get_distance(b.first, b.second);
			  });

	std::vector<circuit> circuits;

	// for (auto i = 0; i < CONN; i++) {
	for (size_t i = 0; i < all_pairs.size(); i++) {
		auto closest_pair = all_pairs[i];
		auto cidx_f = is_part_of_circuit(circuits, closest_pair.first);
		auto cidx_s = is_part_of_circuit(circuits, closest_pair.second);

		if (cidx_f == -1 && cidx_s == -1) {
			// both are not in circuits
			circuits.push_back({closest_pair.first, closest_pair.second});
		} else if (cidx_f == -1) {
			// only first is not in circuits
			circuits[cidx_s].insert(closest_pair.first);
		} else if (cidx_s == -1) {
			// only second is not in circuits
			circuits[cidx_f].insert(closest_pair.second);
		} else if (cidx_f == cidx_s) {
			// both are is the same circuit
		} else {
			// each is in a separate circuit
			auto sset = circuits[cidx_s];
			circuits[cidx_f].insert(sset.begin(), sset.end());
			circuits.erase(circuits.begin() + cidx_s);
		}

		// Part 2
		if (circuits.size() == 1 && circuits[0].size() == dataset.size()) {
			print_circuit(circuits[0]);
			return closest_pair.first.x * closest_pair.second.x;
		}
	}
	return 0;

	/* Part 1
	std::sort(circuits.begin(), circuits.end(),
			  [](circuit a, circuit b) { return a.size() > b.size(); });

	long res = 1;
	for (size_t i = 0; i < 3; i++) {
		print_circuit(circuits[i]);
		res *= circuits[i].size();
	}
	return res;
	*/
}

int main() {
	auto data = readData('\n');
	auto res = solution(data);
	std::cout << "Result: " << res << std::endl;
	return 0;
}
