#include "Font.h"

MyFont::MyFont()
{
  // Use a relative path to the font file. The path should be valid with respect to the current working directory.
  // If your file is located at '<project_root>/fonts/Tylko-Regular.ttf',
  // and your working directory is '<project_root>/cmake-build-debug',
  // then the correct relative path would be '../fonts/Tylko-Regular.ttf'.
  // You can also change the working directory in the Run/Debug Configurations settings in CLion
  // to the project root directory to make your relative path './fonts/Tylko-Regular.ttf' valid.

  // Path to the font file for Windows and Linux
  std::string fontFilePath = "../fonts/Tylko-Regular.ttf";

#ifdef __APPLE__
  // If the operating system is MacOS, change the font file path
  fontFilePath = "../fonts/MAC_Tylko-Regular.ttf";
#endif

  if (!font.loadFromFile(fontFilePath)) {
    throw std::runtime_error("Failed to load font file '" + fontFilePath + "'");
  }
}


sf::Font& MyFont::get()
{
    return font;
}
