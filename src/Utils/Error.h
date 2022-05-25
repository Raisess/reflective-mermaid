#pragma once

#include <iostream>
#include <sstream>
#include <vector>

namespace Utils {

class Error {
  public:
    Error(std::vector<std::string> msgs, int code = 1) {
      std::ostringstream ostr;
      for (std::string msg : msgs) {
        ostr << msg;
      }

      std::cout << "Error: " << ostr.str() << std::endl;
      exit(code);
    }
};

}
