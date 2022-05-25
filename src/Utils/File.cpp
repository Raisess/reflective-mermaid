#include "File.h"

std::string Utils::File::read() {
  this->fdata = "";
  this->rfstream.open(this->path);

  std::string tmp;

  while (std::getline(this->rfstream, tmp)){
    this->fdata.append(tmp.append("\n"));
  }

  this->rfstream.close();

  return this->fdata;
}

void Utils::File::write(std::string data) {
  this->wfstream.open(this->path);
  this->wfstream << data << std::endl;
  this->wfstream.close();
}
