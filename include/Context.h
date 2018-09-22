#ifndef CONTEXT_H
#define CONTEXT_H

#include <glad/glad.h>

#include <functional>
#include <map>
#include <optional>
#include <string>

#include "./Shader.h"
#include "./Texture.h"

class Context {
private:
    std::map<GLuint, Shader> _shaders;
    std::map<std::string, Texture> _textures;

public:
    Context();

    std::optional<Texture> getTexture(std::string& name);

    std::optional<Shader> getShader(GLuint num);

    void addTexture(std::string& name, Texture const& texture);
    void addShader(GLuint num, Shader const& shader);
};

Context::Context() {}

void Context::addTexture(std::string& name, Texture const& texture)
{
    this->_textures.insert(std::make_pair(name, texture));
}

void Context::addShader(GLuint num, Shader const& shader)
{
    this->_shaders.insert(std::make_pair(num, shader));
}

std::optional<Texture> Context::getTexture(std::string& name)
{
    auto found = this->_textures.find(name);
    if (found != this->_textures.end()) {
        return found->second;
    }

    return std::nullopt;
}

std::optional<Shader> Context::getShader(GLuint num)
{
    auto found = this->_shaders.find(num);
    if (found != this->_shaders.end()) {
        return found->second;
    }

    return std::nullopt;
}

#endif /* CONTEXT_H */
