#ifndef FUNCTIONS_HPP_TEST
#define FUNCTIONS_HPP_TEST

#include <fstream>
#include <sstream>
#include <stdint.h>

extern void checkFile(const std::ifstream &file);
extern const uint32_t getFileLength(std::ifstream &file);
extern char getCharAtPosition(std::ifstream &file, uint32_t position);
extern void processASCII(char c, std::stringstream &hexStream,
                         std::stringstream &charStream);
extern bool processEnter(char c, std::stringstream &hexStream,
                         std::stringstream &charStream);
extern bool processToSmall(char c, std::stringstream &hexStream,
                           std::stringstream &charStream);
extern bool processToBig(char c, std::stringstream &hexStream,
                         std::stringstream &charStream);
#endif
