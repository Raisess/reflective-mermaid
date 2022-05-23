#pragma once

#include <fstream>
#include <iostream>

class File {
  public:
    File(std::string path) {
      this->path = path;
    }

    std::string read();
    void write(std::string content);

  private:
    std::string path;
    std::string fdata;
    std::ifstream rfstream;
    std::ofstream wfstream;
};
