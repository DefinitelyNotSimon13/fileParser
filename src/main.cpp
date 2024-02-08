#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {
  std::cout << "Hello World\n";
  // std::string fileName = argv[1];
  std::string fileName = "file.txt";
  std::ifstream file;
  std::stringstream sstream;
  file.open(fileName, std::ios::in);
  std::vector<std::string> lines;
  std::string line;
  while (std::getline(file, line)) {
    std::string symbols;
    for(char c : line){
      symbols += std::to_string((int)c) + " ";
    }
    std::cout << &line << " | " << symbols << " | " << line << "\n";
  }
  std::string data = sstream.str();
  std::cout << data << std::endl;
  return 0;
}
