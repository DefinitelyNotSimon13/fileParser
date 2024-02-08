#include "functions.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

void checkFile(const std::ifstream &file) {
  if (!file.is_open()) {
    std::cout << "\e[31mFile could not be opened!\e[0m\n";
    std::cout << "Exiting...\n";
    std::exit(1);
  }
}

const uint32_t getFileLength(std::ifstream &file) {
  file.seekg(0, std::ios::end);
  uint32_t length = file.tellg();
  file.seekg(0, std::ios::beg);
  return length;
}

char getCharAtPosition(std::ifstream &file, uint32_t position) {
  char c = -1;
  file.seekg(position);
  file.get(c);
  return c;
}

void processASCII(char c, std::stringstream &hexStream,
                  std::stringstream &charStream) {
  hexStream << " " << std::setfill('0') << std::setw(2) << std::hex << (int)c;
  charStream << c;
}

bool processEnter(char c, std::stringstream &hexStream,
                  std::stringstream &charStream) {
  if (c != 10) {
    return false;
  }
  hexStream << " "
            << "EN";
  charStream << "-";
  return true;
}

bool processToSmall(char c, std::stringstream &hexStream,
                    std::stringstream &charStream) {
  if (c >= 0) {
    return false;
  }
  hexStream << " "
            << "NA";
  charStream << c << ".";
  return true;
}

bool processToBig(char c, std::stringstream &hexStream,
                  std::stringstream &charStream) {
  if (c <= 127) {
    return false;
  }
  hexStream << " "
            << "NA";
  charStream << c << ".";
  return true;
}
