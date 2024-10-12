#pragma once

#include "../config.hpp"


class TextureFactory {

public:

    //unsigned int make_texture(const char* filename);

    void start_texture_array(int layers);

    void load_into_array(const char* filename, int layer);

    unsigned int finalize_texture_array();


private:
    unsigned int texture;
};