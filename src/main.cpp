#include <iostream>

int main(int argc, char* argv[]) {
  std::cout << "Hello, world!" << std::endl;

  argc = argc - 1;

  if (argc >= 1) {
    std::cout << "arguments: " << argc << std::endl;

    for (int i = 1; i <= argc; i++) {
      std::cout << "argument " << i - 1 << ": " << argv[i] << std::endl;
    }
  }

  return 0;
}
