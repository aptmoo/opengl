#include "texture.h"

#include "vendor/stb_image.h"

Texture::Texture(const std::string& path)
    : gl_ID(0), p_LocalBuffer(nullptr), gl_Width(0), gl_Height(0), gl_BPP(0)
{
    // Make sure the images are flipped correctly
    stbi_set_flip_vertically_on_load(true);

    p_LocalBuffer = stbi_load(path.c_str(), &gl_Width, &gl_Height, &gl_BPP, 4);

    // Generate and bind textures
    GLCall( glGenTextures(1, &gl_ID) );
    GLCall( glBindTexture(GL_TEXTURE_2D, gl_ID));

    GLCall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR) );
    GLCall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR) );
    GLCall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT) );
    GLCall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT) );

    GLCall( glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, gl_Width, gl_Height, 0,  GL_RGBA, GL_UNSIGNED_BYTE, p_LocalBuffer) );
    GLCall( glBindTexture(GL_TEXTURE_2D, 0) );

    if(p_LocalBuffer)
        stbi_image_free(p_LocalBuffer);
}

Texture::~Texture()
{
    GLCall( glDeleteTextures(1, &gl_ID) );
}

void Texture::Bind(unsigned int slot) const
{
    GLCall( glActiveTexture(GL_TEXTURE0 + slot) );
    GLCall( glBindTexture(GL_TEXTURE_2D, gl_ID));
}

void Texture::Unbind() const
{
    GLCall( glBindTexture(GL_TEXTURE_2D, 0) );
}