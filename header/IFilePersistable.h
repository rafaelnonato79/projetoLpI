#pragma once
#include <string>

class IFilePersistable {
public:
  virtual ~IFilePersistable() = default;

  virtual std::string toFileString() const = 0;

  virtual bool fromFileString(const std::string &line) = 0;
};
