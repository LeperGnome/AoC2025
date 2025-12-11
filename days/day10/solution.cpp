#include <cstdlib>
#include <deque>
#include <fstream>
#include <iostream>
#include <ostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

const char *dataPath = "days/day10/data.txt";

std::vector<std::string> split_string(const std::string &str, char delim) {
	std::vector<std::string> tokens;
	std::stringstream ss(str);
	std::string token;
	while (std::getline(ss, token, delim)) {
		tokens.push_back(token);
	}
	return tokens;
}

using lights = std::vector<int>;
using button = std::vector<size_t>;
using joltage = std::vector<size_t>;

void print_lights(const lights &lights) {
	std::cout << '[';
	for (size_t i = 0; i < lights.size(); ++i) {
		if (lights[i] == 1) {
			std::cout << '#';
		} else {
			std::cout << '.';
		}
	}
	std::cout << ']' << ' ';
}

void print_buttons(const std::vector<button> &buttons) {
	for (const auto &btn : buttons) {
		std::cout << '(';
		for (size_t i = 0; i < btn.size(); ++i) {
			std::cout << btn[i];
			if (i < btn.size() - 1) {
				std::cout << ',';
			}
		}
		std::cout << ')' << ' ';
	}
}

void print_joltage(const joltage &joltage_levels) {
	std::cout << '{';
	for (size_t i = 0; i < joltage_levels.size(); ++i) {
		std::cout << joltage_levels[i];
		if (i < joltage_levels.size() - 1) {
			std::cout << ',';
		}
	}
	std::cout << '}' << ' ';
}

struct machine {
	lights target_lights;
	std::vector<button> buttons;
	joltage target_joltage;

	void print() {
		print_lights(target_lights);
		print_buttons(buttons);
		print_joltage(target_joltage);
		std::cout << std::endl;
	}
};

lights parse_lights(const std::string &lights_str) {
	lights lights;
	for (char c : lights_str) {
		if (c == '#') {
			lights.push_back(1);
		} else if (c == '.') {
			lights.push_back(-1);
		}
	}
	return lights;
}

joltage parse_joltage(const std::string &joltage_str) {
	joltage levels;
	auto parts = split_string(
		joltage_str.substr(1, joltage_str.length() - 2), // remove { brackets }
		',');
	for (const auto &part : parts) {
		levels.push_back(std::stoul(part));
	}
	return levels;
}

std::vector<button> parse_buttons(const std::vector<std::string> &button_strs) {
	std::vector<button> buttons;
	for (const auto &btn_str : button_strs) {
		button btn;
		auto parts = split_string(
			btn_str.substr(1, btn_str.length() - 2), // remove ( brackets )
			',');
		for (const auto &part : parts) {
			btn.push_back(std::stoul(part));
		}
		buttons.push_back(btn);
	}
	return buttons;
}

std::vector<machine> readData(char delim) {
	std::ifstream ifs(dataPath);
	std::string buf;
	std::vector<machine> lines;
	while (std::getline(ifs, buf, delim)) {
		auto parts = split_string(buf, ' ');
		auto target_lights = parse_lights(parts[0]);
		machine m = {target_lights,
					 parse_buttons(std::vector<std::string>(parts.begin() + 1,
															parts.end() - 1)),
					 parse_joltage(parts[parts.size() - 1])};
		lines.push_back(m);
	}
	return lines;
}

long minButtonPressesPt1(const machine &machine) {
	long n_presses = 0;

	auto initial_state = lights(machine.target_lights.size(), -1);

	auto seen = std::set<lights>();
	std::deque<std::pair<lights, long>> q{{initial_state, 0}};

	for (; !q.empty(); q.pop_front()) {
		auto el = q.front();
		auto lights_state = el.first;
		auto depth = el.second;

		if (seen.contains(lights_state)) {
			continue;
		}

		if (lights_state == machine.target_lights) {
			return depth;
		}

		seen.insert(lights_state);

		for (const auto &btn : machine.buttons) {
			auto new_light_state = lights_state;
			for (const auto lidx : btn) {
				new_light_state[lidx] *= -1;
			}
			q.push_back({new_light_state, depth + 1});
		}
	}
	return n_presses;
}

long minButtonPressesPt2(const machine &machine) {
	long n_presses = 0;

	auto initial_state = joltage(machine.target_joltage.size(), 0);

	auto seen = std::set<joltage>();
	std::deque<std::pair<joltage, long>> q{{initial_state, 0}};

	for (; !q.empty(); q.pop_front()) {
		auto el = q.front();
		auto joltage_state = el.first;
		auto depth = el.second;

		if (seen.contains(joltage_state)) {
			continue;
		}

		// if (depth % 100 == 0) {
		//     std::cout << "Target ";
		//     print_joltage(machine.target_joltage);
		//     std::cout<< "; Current joltage ";
		//     print_joltage(joltage_state);
		//     std::cout << std::endl;
		// }

		if (joltage_state == machine.target_joltage) {
			return depth;
		}

		seen.insert(joltage_state);

		for (const auto &btn : machine.buttons) {
			auto new_joltage_state = joltage_state;
			for (const auto idx : btn) {
				new_joltage_state[idx]++;
				if (machine.target_joltage[idx] < new_joltage_state[idx]) {
					goto skip;
				}
			}
			q.push_back({new_joltage_state, depth + 1});
		skip:;
		}
	}
	return n_presses;
}

long solution(std::vector<machine> machines) {
	long total = 0;
	for (auto machine : machines) {
		machine.print();
		total += minButtonPressesPt2(machine);
	}
	return total;
}

int main() {
	auto data = readData('\n');
	auto res = solution(data);
	std::cout << "Result: " << res << std::endl;
	return 0;
}
