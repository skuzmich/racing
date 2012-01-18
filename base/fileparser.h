// Copyright (C) 2011-2012 Kuzmich Svyatoslav <svatoslav1@gmail.com>
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_FILEPARSER_H_
#define BASE_FILEPARSER_H_

#include <string>
#include <vector>
#include "../physics/predecls.h"

std::string GetLine(std::ifstream *myfile);

std::vector<std::string> &Split(const std::string &s,
    char delim, std::vector<std::string> &elems);

std::vector<std::string> Split(const std::string &s, char delim);

template <class T>
bool FromStringg(T& t, const std::string& s,
    std::ios_base& (*f)(std::ios_base&));

int ReadFloatVector(std::vector<float> *ret, std::ifstream *myfile, int size);

float ReadFloat(std::ifstream *myfile);
int   ReadInt(std::ifstream *myfile);
b2Vec2 Readb2Vec2(std::ifstream *myfile);

#endif  // BASE_FILEPARSER_H_
