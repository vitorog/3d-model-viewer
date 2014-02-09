#include "model.h"

#include <iostream>
#include <fstream>
#include <cmath>

Model::Model()
{
}

int Model::Load(const std::string &path)
{
    double min_x=0,min_y=0,min_z=0,max_x=0,max_y=0,max_z=0;
    int ret = 0;
    std::ifstream file(path.c_str());
    if(file.is_open()){
        std::string line;
        while( std::getline(file, line) ){
            std::vector<std::string> tokens = Split(line, ' ');
            if(!tokens.empty()){
                std::string line_id = tokens.at(0);
                tokens.erase(tokens.begin());
                //Material file line
                if( line_id == "mtllib" ){
                    if(tokens.empty()){
                        ret = -1;
                        break;
                    }
                    materials_id_.insert(std::pair<std::string, int>(tokens.at(0),materials_id_.size()));
                    Material mat;

                    model_dir_ = GetFilePath(path);
                    std::string material_path;
                    material_path.append(model_dir_);
                    material_path.append(tokens.at(0));

                    if( mat.Load(material_path) != 0){
                        ret = -1;
                        break;
                    }
                    materials_.push_back(mat);
                }
                //Vertice line
                if( line_id == "v" ){
                    if(tokens.size() != 3){
                        ret = -1;
                        break;
                    }
                    double x = atof(tokens.at(0).c_str());
                    double y = atof(tokens.at(1).c_str());
                    double z = atof(tokens.at(2).c_str());
                    if(x <= min_x){
                        min_x = x;
                    }
                    if(x >= max_x){
                        max_x = x;
                    }
                    if(y <= min_y){
                        min_y = y;
                    }
                    if(y >= max_y){
                        max_y = y;
                    }
                    if(z <= min_z){
                        min_z = z;
                    }
                    if(z >= max_z){
                        max_z = max_z;
                    }

                    glm::vec3 vertice((float)x,(float)y,(float)z);
                    vertices_.push_back(vertice);
                }
                //Vertice normal line
                if( line_id == "vn" ){
                    if(tokens.size() != 3){
                        ret = -1;
                        break;
                    }
                    glm::vec3 normal(atof(tokens.at(0).c_str()),
                                     atof(tokens.at(1).c_str()),
                                     atof(tokens.at(2).c_str()));
                    normals_.push_back(normal);
                }
                //Vertice texture coordinate line
                if( line_id == "vt" ){
                    if(tokens.size() != 2){
                        ret = -1;
                        break;
                    }
                    glm::vec2 text_coord(atof(tokens.at(0).c_str()),
                                         atof(tokens.at(1).c_str()));
                    text_coords_.push_back(text_coord);
                }
                //Face line
                if( line_id == "f" ){
                    if(tokens.size() == 3){
                        tri_faces_ = true;
                    }else if(tokens.size() == 4){
                        tri_faces_ = false;
                    }else{
                        ret = -1;
                        break;
                    }
                    //The "Face" line contains the indexes of the
                    //vertices, normals and texture coordinates,
                    //separated by a '/' character
                    std::vector<std::string>::iterator it = tokens.begin();
                    for(; it != tokens.end(); it++){
                        std::vector<std::string> face_tokens = Split((*it), '/');
                        if(face_tokens.size() != 3){
                            ret = -1;
                            goto EndLoop;
                        }
                        vertices_index_.push_back(atoi(face_tokens.at(0).c_str()));
                        text_coords_index_.push_back(atoi(face_tokens.at(1).c_str()));
                        normals_index_.push_back(atoi(face_tokens.at(2).c_str()));
                    }
                }
            }
        }
EndLoop:
        file.close();
        double center_x = (max_x + min_x)/2.0f;
        double center_y = (max_y + min_y)/2.0f;
        double center_z = (max_z + min_z)/2.0f;

        center_ = glm::vec3(center_x,center_y,center_z);

    }else{
        ret = -1;
    }
    return ret;
}
