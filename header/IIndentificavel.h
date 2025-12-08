#pragma once
#include <cstddef>

class IIdentificavel {
public:
  virtual ~IIdentificavel() = default;
  virtual size_t getId() const = 0;
  virtual void setId(size_t id) = 0;
};
