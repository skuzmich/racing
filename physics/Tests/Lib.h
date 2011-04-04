#ifndef LIB_H
#define LIB_H

#define IS_CAR_BODY     -1
#define IS_WHEEL        1
#define IS_SAND_FIELD   2
#define IS_WALL         3
#define IS_DYNAMIC_OBJ  4
#define IS_SPECIAL      5

struct ObjData{
    int type;
    int level;
    //int someFlag...; ???
};

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while(std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    return split(s, delim, elems);
}

template <class T>
bool from_string(T& t, 
                 const std::string& s, 
                 std::ios_base& (*f)(std::ios_base&))
{
  std::istringstream iss(s);
  return !(iss >> f >> t).fail();
}

template <class T>
int GetNextVectorFromFile(std::vector<T> *ret,std::ifstream *myfile, int size){
    std::string line;
    ret->clear();
    if (myfile->is_open())
    {
        std::vector<std::string> vec ;
        if ( myfile->good() )
        {
            std::getline (*myfile,line);
            vec = split(line,' ');
            
            if (vec.size() != size){
                return 1;
                printf("\n\nERROR vec.size() != size!!!\n\n");
            }

            for(unsigned int i = 0; i < vec.size(); i++ ){
                T f;
                if(from_string<T>(f, vec[i], std::dec))
                {
                    ret->push_back(f);
                    std::cout << f << std::endl;
                }
                else
                {
                    return 1;
                    std::cout << "from_string failed" << std::endl;
                }
            }
        } else return 1;
    }
    else {
        std::cout << "Unable to open file";
        return 1;
    }
    return 0;
}

#endif LIB_H