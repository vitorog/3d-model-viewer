#include "material.h"

#include <fstream>

Material::Material()
{
}

int Material::Load(const std::string &path)
{
    int ret = 0;
    std::ifstream file(path.c_str());
    if(file.is_open()){
        std::string line;
        while( std::getline(file, line) ){
            std::vector<std::string> tokens = Split(line, ' ');
            if(!tokens.empty()){
                std::string line_id = tokens.at(0);
                tokens.erase(tokens.begin());
                //Name
                if( line_id == "newmtl" ){
                    if(tokens.empty()){
                        ret = -1;
                        break;
                    }
                    name_ = tokens.at(0);
                }
                //Ka line
                if(line_id == "Ka"){
                    if(tokens.size() != 3){
                        ret = -1;
                        break;
                    }
                    ka_ = glm::vec3(atof(tokens.at(0).c_str()),
                                    atof(tokens.at(1).c_str()),
                                    atof(tokens.at(2).c_str()));

                }
                //Kd line
                if(line_id == "Kd"){
                    if(tokens.size() != 3){
                        ret = -1;
                        break;
                    }
                    kd_ = glm::vec3(atof(tokens.at(0).c_str()),
                                    atof(tokens.at(1).c_str()),
                                    atof(tokens.at(2).c_str()));

                }
                //Ks line
                if(line_id == "Ks"){
                    if(tokens.size() != 3){
                        ret = -1;
                        break;
                    }
                    ks_ = glm::vec3(atof(tokens.at(0).c_str()),
                                    atof(tokens.at(1).c_str()),
                                    atof(tokens.at(2).c_str()));

                }
                //Tr line
                if(line_id == "Tr"){
                    if(tokens.empty()){
                        ret = -1;
                        break;
                    }
                    tr_ = atof(tokens.at(0).c_str());
                }
                //Diffuse texture
                if(line_id == "map_Kd"){
                    if(tokens.empty()){
                        ret = -1;
                        break;
                    }
                    map_kd_ = tokens.at(0);
                }
            }

        }
        file.close();
    }else{
        ret = -1;
    }

    return ret;
}
