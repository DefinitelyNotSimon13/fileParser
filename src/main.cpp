#include <fstream>
#include <iostream>
#include <sstream>
#include <stdint.h>
#include <stdio.h>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>

#include "functions.hpp"

void checkTerminalSize();

int main(int argc, char *argv[]) {
  checkTerminalSize();

  std::ifstream file(argv[1]);

  // Check if file is open
  checkFile(file);

  // Get file length and line Nr.
  const uint32_t length = getFileLength(file);
  const uint16_t lines = length != 0 ? length / 16 + 1 : 0;

  // Display status
  std::string display = length > 1000 ? std::to_string(length / 1000) + "MB"
                                      : std::to_string(length) + " bytes";
  std::cout << "The file is " << display << " long.\n";
  std::cout << "This will result in an output with " << lines << " lines!\n\n";
  std::cout << "\e[3mLegend:\n\t\"EN | -\" = Enter\n\t\"NA | .\" = Not ASCII "
               "(one symbol "
               "can result in multiple characters)\e[0m\n\n";

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
    int8_t linePosition = 0;

    for (uint8_t y = 0; linePosition < 16; ++y) {
      ++linePosition;

      uint32_t position = y + (i * 16);
      if (position >= length - 1) {
        break;
      }
      char c = getCharAtPosition(file, position);

      if (processEnter(c, hexStream, charStream)) {
        continue;
      }
      if (processToSmall(c, hexStream, charStream)) {
        continue;
      }
      if (processToBig(c, hexStream, charStream)) {
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

void checkTerminalSize() {

  uint16_t cols = 0;
#ifdef TIOCGSIZE
  struct ttysize ts;
  ioctl(STDIN_FILENO, TIOCGSIZE, &ts);
  cols = ts.ts_cols;
#elif defined(TIOCGWINSZ)
  struct winsize ts;
  ioctl(STDIN_FILENO, TIOCGWINSZ, &ts);
  cols = ts.ws_col;
#endif /* TIOCGSIZE */
  if (cols < 80) {
    std::cout << "\e[31mYour terminal is to small (" << cols << "cols)!\n"
              << "Please restart the application in a bigger terminal\e[0m\n";
    std::exit(1);
  }
}
