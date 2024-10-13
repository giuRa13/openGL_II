#include "texture_factory.hpp"
#include "../stb_image.h"


void TextureFactory::start_texture_array(int layers)
{
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D_ARRAY, texture);
    glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, GL_RGBA8, 1024, 1024, layers);//target, n levels, format, w, h, n layers
    // all textures IMAGE need to be same dimension
}

void TextureFactory::load_into_array(const char* filename, int layer) 
{
    // load image
    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(filename, &width, &height, &channels, STBI_rgb_alpha);
	
    //upload to GPU
    glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, //base level
        0, 0, layer,//x, y, z offsets 
        width, height, 1, //depth (1 layer)
        GL_RGBA, GL_UNSIGNED_BYTE, data);

	stbi_image_free(data);
}


unsigned int TextureFactory::finalize_texture_array()
{
    //Configure sampler
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_R, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D_ARRAY);

    return texture;
}


unsigned int TextureFactory::build_cubemap(std::vector<const char*> filenames)
{
    //make texture
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
    glTexStorage2D(GL_TEXTURE_CUBE_MAP, 1, GL_RGBA8, 1024, 1024);

    //load images
    stbi_set_flip_vertically_on_load(true);
    for(int i = 0; i < 6; ++i)
    {
        // load image
        int width, height, channels;
        unsigned char* data = stbi_load(filenames[i], &width, &height, &channels, STBI_rgb_alpha);

        // to GPU
        //concention posX - negX - posY - negY - posZ - negZ (with + i)
        glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i , 0, 
            0, 0, width, height,
            GL_RGBA, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
    }

    return texture;
}


/*unsigned int TextureFactory::make_texture(const char* filename) 
{
    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(
        filename, &width, &height, &channels, STBI_rgb_alpha);

	//make the texture
    unsigned int texture;
	glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
	
    //load data
    glTexImage2D(GL_TEXTURE_2D, 
        0, GL_RGBA, width, height, 0,
        GL_RGBA, GL_UNSIGNED_BYTE, data);

    //free data
	stbi_image_free(data);

    //Configure sampler
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);

    return texture;
}*/