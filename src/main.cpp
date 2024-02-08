#include <fstream>
#include <iostream>
#include <sstream>
#include <stdint.h>
#include <stdio.h>
#include <string>

#include "functions.hpp"

int main(int argc, char *argv[]) {
  std::ifstream file(argv[1]);

  // Check if file is open
  checkFile(file);

  // Get file length and line Nr.
  const uint32_t length = getFileLength(file);
  const uint16_t lines = length / 16 + 1;

  // Display status
  std::cout << "The file is " << length << " bytes long.\n";
  std::cout << "This will result in an output with " << lines << " lines!\n\n";
  std::cout << "\e[3mLegend:\n\t\"EN | -\" = Enter\n\t\"NA | .\" = Not ASCII (one symbol "
               "can result in multiple characters)\e[0m\n";

  uint16_t firstColumn = 0;
  std::string divider = "-----------------------------------------------------";

  // Print table header
  std::cout << std::endl;
  printf("\e[0m\e[1m|%10s| %-47s | %-17s|\n", "Something", "Hexadecimal",
         "Characters");
  printf("|%.10s+%.49s+%.18s|\n\e[0m", divider.c_str(), divider.c_str(),
         divider.c_str());

  // Print table contents
  for (uint32_t i = 0; i < lines; ++i) {
    std::stringstream hexStream;
    std::stringstream charStream;
    bool first = true;
    int8_t linePosition = 0;

    for (uint8_t y = 0; linePosition < 16; ++y) {
      ++linePosition;

      uint32_t position = y + (i * 16);
      char c = getCharAtPosition(file, position);

      if (processToSmall(c, hexStream, charStream)) {
        continue;
      }
      if (processToBig(c, hexStream, charStream)) {
        continue;
      }
      if (processEnter(c, hexStream, charStream)) {
        continue;
      }
      processASCII(c, hexStream, charStream);
    }
    

    std::string stringHexes = hexStream.str();
    std::string stringChars = charStream.str();

    printf("| %08u |%-48s | %-16s |\n", firstColumn, stringHexes.c_str(),
           stringChars.c_str());
    firstColumn += 10;
  }

  printf("|%.10s+%.49s+%.18s|\n\e[0m", divider.c_str(), divider.c_str(),
         divider.c_str());

  return 0;
}
