#include <iostream>
#include <string>
#include <fstream>
#include <ostream>
#include <string>
#include <utility>
#include <vector>
#include <cstdlib>
#include <sstream>


const char *dataPath = "days/day2/data.txt";


using range = std::pair<long, long>;

std::vector<range> readData(char delim){
    std::ifstream ifs(dataPath);
    std::string rangeBuf;
    std::vector<range> result;
    while (std::getline(ifs, rangeBuf, delim)){
        auto pos = rangeBuf.find('-');
        range rg = {
            std::atol(rangeBuf.substr(0, pos).c_str()),
            std::atol(rangeBuf.substr(pos+1).c_str()),
        };
        result.push_back(rg);
    }
    return result;
}


void printVec(std::vector<std::string> vec) {
    for (auto s : vec) {
        std::cout << s << '\n';
    }
}

bool checkNumInvalid(long num) {
    auto snum = std::to_string(num);
    if (snum.length() % 2 == 1) return false;
    if (
        snum.substr(0, snum.length()/2) == 
        snum.substr(snum.length()/2)
    ) {
        std::cout << "+ " << num << std::endl;
        return true;
    }
    return false;
}

std::string repeat(int n, std::string s) {
    std::ostringstream os;
    for(int i = 0; i < n; i++)
        os << s;
    return os.str();
}

bool checkNumInvalid2(long num) {
    auto snum = std::to_string(num);

    for (size_t step = 1; step <= snum.length()/2; step++) {
        auto target = snum.substr(0, step);
        if (repeat(snum.length()/step, target) == snum) return true;
    }
    return false;
}

long solution(std::vector<range> data) {
    long out = 0;
    for (auto rg : data){
        std::cout << "Range: " << rg.first << "-" << rg.second << std::endl;
        for (auto num = rg.first; num <= rg.second; num++){
            if (checkNumInvalid2(num)) {
                out += num;
            }
        }
    }
    return out;
}


int main() {
    auto data = readData(',');
    std::cout << solution(data) << std::endl;
    return 0;
}
