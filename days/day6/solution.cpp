#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

const char *dataPath = "days/day6/data.txt";

struct problem {
	std::vector<int> numbers;
	char operation;
};

void printProblem(problem p) {
	for (auto n : p.numbers) {
		std::cout << n << ' ';
	}
	std::cout << p.operation << std::endl;
}

// Trim from the start (in place)
inline void ltrim(std::string &s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
				return !std::isspace(ch);
			}));
}

// Trim from the end (in place)
inline void rtrim(std::string &s) {
	s.erase(std::find_if(s.rbegin(), s.rend(),
						 [](unsigned char ch) { return !std::isspace(ch); })
				.base(),
			s.end());
}

std::vector<problem> readData() {
	std::ifstream filestream(dataPath);
	std::stringstream full_file_string_stream;
	full_file_string_stream << filestream.rdbuf();
	auto full_file_string = full_file_string_stream.str();

	auto nrows =
		std::count(full_file_string.begin(), full_file_string.end(), '\n');

	auto first_row = full_file_string.substr(0, full_file_string.find('\n'));
	auto clean_row = std::regex_replace(first_row, std::regex(" +"), " ");
	ltrim(clean_row);
	rtrim(clean_row);
	auto problems_count =
		std::count(clean_row.begin(), clean_row.end(), ' ') + 1;

	std::vector<problem> problems(problems_count);

	full_file_string_stream.seekg(0);
	std::string linebuffer;
	std::vector<std::string> lines;
	int line_n = 0;
	while (std::getline(full_file_string_stream, linebuffer, '\n')) {
		if (line_n == nrows - 1) {
			// Parsing operations.
			auto problem_idx = 0;
			for (auto c : linebuffer) {
				if (c != ' ') {
					problems[problem_idx].operation = c;
					problem_idx++;
				}
			}
			break;
		}
		lines.push_back(linebuffer);
		line_n++;
	}

	size_t problem_idx = 0;

	for (size_t col = 0; col < lines[0].length(); col++) {
		std::string buf;
		bool is_empty = true;

		for (size_t line_n = 0; line_n < lines.size(); line_n++) {
			auto c = lines[line_n][col];
			if (c != ' ') {
				is_empty = false;
				buf.push_back(c);
			}
		}
		if (!is_empty) {
			long num = std::atol(buf.c_str());
			problems[problem_idx].numbers.push_back(num);
		} else {
			problem_idx++;
		}
	}
	return problems;
}

long solution(std::vector<problem> problems) {
	long res = 0;
	for (auto p : problems) {
		printProblem(p);
		if (p.operation == '+') {
			long pres = 0;
			for (auto num : p.numbers) {
				pres += num;
			}
			res += pres;
		} else {
			long pres = 1;
			for (auto num : p.numbers) {
				pres *= num;
			}
			res += pres;
		}
	}
	return res;
}

int main() {
	auto data = readData();
	auto res = solution(data);
	std::cout << "Result: " << res << std::endl;
	return 0;
}
