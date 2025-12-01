#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>


const char *dataPath = "days/day1/data.txt";


std::vector<std::string> readData(){
    std::ifstream ifs(dataPath);
    std::string buf;
    std::vector<std::string> result;
    while (std::getline(ifs, buf)){
        result.push_back(buf);
    }
    return result;
}


void printVec(std::vector<std::string> vec) {
    for (auto s : vec) {
        std::cout << s << '\n';
    }
}

size_t solution(std::vector<std::string> data) {
    int pos = 50;
    size_t cnt = 0;

    for (auto line : data){
        char dir = line[0];
        int num = std::atoi(line.substr(1).c_str());

        cnt += num / 100;

        std::cout << pos << " --> " << line;
        bool from_zero = pos == 0;

        if (dir == 'L') {
            pos -= num % 100;
            if (pos < 0) {
                if (!from_zero) cnt++;
                pos += 100;
            }
        } else {
            pos += num % 100;
            if (pos >= 100) {
                pos -= 100;
                if (pos != 0) cnt++;
            }
        }

        if (pos == 0) cnt++;

        std::cout << " " << " --> " << pos << " (" << cnt << ")" << std::endl;
    }
    return cnt;
}


int main() {
    auto data = readData();
    std::cout << solution(data) << std::endl;
    return 0;
}
