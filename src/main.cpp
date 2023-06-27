#include <iostream>
#include <vector>

int main () {
    std::vector<int> vec;
    vec.push_back(34);
    vec.push_back(34);
    vec.push_back(34);
    vec.push_back(34);
    
    for (size_t x = 0; x < vec.size(); x++) {
        std::cout << vec[x] << std::endl;
    }
}
