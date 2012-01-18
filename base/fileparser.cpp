// Copyright (C) 2011-2012 Kuzmich Svyatoslav <svatoslav1@gmail.com>
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "./fileparser.h"

std::vector<std::string> &Split(const std::string &s,
                                char delim,
                                std::vector<std::string> &elems) {
  std::stringstream ss(s);
  std::string item;
  while (std::getline(ss, item, delim)) {
    elems.push_back(item);
  }
  return elems;
}

std::vector<std::string> Split(const std::string &s, char delim) {
  std::vector<std::string> elems;
  return Split(s, delim, elems);
}

template <class T>
bool FromStringg(T& t,
                 const std::string& s,
                 std::ios_base& (*f)(std::ios_base&)) {
  std::istringstream iss(s);
  return !(iss >> f >> t).fail();
}

int ReadFloatVector(std::vector<float> *ret,
                    std::ifstream *myfile,
                    int size) {
  std::string line;
  std::vector<std::string> vec;
  ret->clear();
  if (myfile->is_open() && myfile->good()) {
    line = GetLine(myfile);
    vec = Split(line, ' ');

    if (vec.size() != size)
      return 1;

    for (unsigned int i = 0; i < vec.size(); i++) {
      float f;
      if (FromStringg<float>(f, vec[i], std::dec)) {
        ret->push_back(f);
      } else {
        std::cerr << "Error: Strin -> Float Vector" << std::endl;
        return 1;
      }
    }
  } else {
    std::cerr << "Error: Unable to open file";
    return 1;
  }
  return 0;
}

float ReadFloat(std::ifstream *myfile) {
  float val;
  std::string line;

  if (myfile->is_open() && myfile->good()) {
    std::vector<std::string> vec;
    line = GetLine(myfile);
    vec = Split(line, ' ');

    if (vec.size() < 1) {
      std::cerr << "Error: Unable to read float\n";
      return 1;
    }

    if (FromStringg<float>(val, vec[0], std::dec)) {
      return val;
    } else {
      std::cerr << "Error: Strin -> Float" << std::endl;
      return val;
    }
  } else {
    std::cerr << "Error: Unable to open file [1] "
              << myfile->is_open()
              << myfile->good()
              << std::endl;
    return val;
  }
}

int ReadInt(std::ifstream *myfile) {
  int val;
  std::string line;

  if (myfile->is_open() && myfile->good()) {
    std::vector<std::string> vec;
    line = GetLine(myfile);
    vec = Split(line, ' ');

    if (vec.size() < 1) {
      std::cerr << "Error: Unable to read int\n";
      return 1;
    }

    if (FromStringg<int>(val, vec[0], std::dec)) {
      return val;
    } else {
      std::cerr << "Error: Strin -> Int" << std::endl;
      return val;
    }
  } else {
    std::cerr << "Error: Unable to open file [2]" << std::endl;
    return val;
  }
}

b2Vec2 Readb2Vec2(std::ifstream *myfile) {
  b2Vec2 val = b2Vec2(1./0., 2./0.);
  std::string line;

  if (myfile->is_open() && myfile->good()) {
    std::vector<std::string> vec;
    line = GetLine(myfile);
    vec = Split(line, ' ');

    if (vec.size() < 2) {
      std::cerr << "Error: Unable to read b2Vec2\n";
      return val;
    }

    if (FromStringg<float>(val.x, vec[0], std::dec) &&
        FromStringg<float>(val.y, vec[1], std::dec)) {
      return val;
    } else {
      std::cerr << "Error: String -> b2Vec2" << std::endl;
      return val;
    }

  } else {
    std::cerr << "Error: Unable to open file [3] " << std::endl;
    return val;
  }
}

std::string GetLine(std::ifstream *myfile) {
  std::string line;

  for ( std::getline(*myfile, line);
        line.size() !=0;
        std::getline(*myfile, line)) {
    std::vector<std::string> vec;
    vec = Split(line, ' ');
    if ( vec.size() != 0 && vec[0][0] != '#' )
      return line;
  }
  return "";
}

