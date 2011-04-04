#include "Predecls.h"

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

Track::Track(b2World *m_world, char* track_path){
    k_restitution = 0.4f;
    world = m_world;
    b2BodyDef bd;
    bd.position.Set(0.0f, 0.0f);
    ground = world->CreateBody(&bd);
    sandfield= world->CreateBody(&bd);
    
    std::ifstream myfile (track_path);
    std::vector<float> vec;
    while ( ! GetNextVectorFromFile<float>(&vec,&myfile, 4))
        walls_list.push_back(new Wall(vec[0], vec[1], vec[2],vec[3],ground));
    
    int count = 3;
    while (! GetNextVectorFromFile<float>(&vec,&myfile, count * 2)){
        b2Vec2 *vertices = (b2Vec2*) malloc(count * sizeof(b2Vec2));
        for (int i = 0; i < count; i++){
            vertices[i].Set(vec[2*i],vec[2*i+1]);
            printf("==%f %f\n", vec[2*i], vec[2*i+1]);
        }
        sandfields_list.push_back(new SandField(vertices,count,this));
    }
}
