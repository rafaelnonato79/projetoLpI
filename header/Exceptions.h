#pragma once
#include <stdexcept>
#include <string>

class DuplicateEntry : public std::runtime_error {
public:
  explicit DuplicateEntry(const std::string &msg) : std::runtime_error(msg) {}
};

class NotFound : public std::runtime_error {
public:
  explicit NotFound(const std::string &msg) : std::runtime_error(msg) {}
};

class ValidationError : public std::runtime_error {
public:
  explicit ValidationError(const std::string &msg) : std::runtime_error(msg) {}
};
