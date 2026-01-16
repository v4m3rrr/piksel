#pragma once

#include <glad/glad.h>
#include <glm/mat4x4.hpp>

#include <string>

namespace piksel
{
  class Shader
  {
  public:
    enum class ShaderType : GLuint
    {
      VertexType=GL_VERTEX_SHADER,
      FragmentType=GL_FRAGMENT_SHADER
    };

    class CompileShader
    {
    public:
      CompileShader(std::string_view src, ShaderType type);

      CompileShader(const CompileShader&)=delete;
      CompileShader& operator=(const CompileShader&)=delete;

      CompileShader(CompileShader&& other)noexcept=delete;
      CompileShader& operator=(CompileShader&& other) noexcept=delete;

      ~CompileShader() noexcept;

      GLuint get() noexcept;
    private:
      GLuint shader_=0;
    };
  public:
    Shader(
      std::string_view vertex_shader_src_path, 
      std::string_view fragment_shader_src_path);
    Shader(
        CompileShader vertex_shader,
        CompileShader fragment_shader);
    Shader(const Shader&)=delete;
    Shader(Shader&& other);

    Shader& operator=(const Shader&)=delete;
    Shader& operator=(Shader&&);

    ~Shader() noexcept;

    GLuint get() noexcept;

    void use();
    void set(std::string_view name,int value);
    void set(std::string_view name, const glm::vec3& vec);
    void set(std::string_view name,const glm::mat4& matrix);
  public:
    static std::string loadShaderSrc(const char* src_path);
  private:
    GLuint program_=0;
  };

}
