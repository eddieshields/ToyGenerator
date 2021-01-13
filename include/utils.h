#ifndef TOYGEN_UTILS_H
#define TOYGEN_UTILS_H

#include "msgservice.h"

#include <string>
#include <vector>

struct Utils
{
  Utils() = default;
  ~Utils() {}

  template<typename TYPE, typename... ARGS>
  static std::vector<TYPE> addVectors(std::vector<TYPE> vec1, std::vector<TYPE> vec2, ARGS... vecs)
  {
    vec1.insert(vec1.end(),vec2.begin(),vec2.end());
    addVectors(vec1,vecs...);
    return vec1;
  }

  template<typename TYPE>
  static std::vector<TYPE> addVectors(std::vector<TYPE> vec1, std::vector<TYPE> vec2)
  {
    vec1.insert(vec1.end(),vec2.begin(),vec2.end());
    return vec1;
  }

  template<typename TYPE>
  static void printVector(std::vector<TYPE> vec)
  {
    std::string tmp;
    std::string out;
    for (auto& entry : vec) {
      entry >> tmp;
      out += tmp+", ";
    }
    out.replace(out.size()-2,2,"");
    INFO(out);
  }
};

#endif