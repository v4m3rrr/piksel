#pragma once

#include "piksel/piksel.hh"

#include <string>

namespace piksel
{
  class Shader
  {
  private:
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

      GLuint get() noexcept;

      CompileShader(CompileShader&& other)noexcept=delete;
      CompileShader& operator=(CompileShader&& other) noexcept=delete;

      ~CompileShader() noexcept;
    private:
      GLuint shader_=0;
    };
  public:
    Shader(
      const char* vertex_shader_src_path, 
      const char* fragment_shader_src_path);

    GLuint get() noexcept;

    void use();
    void set(std::string_view name,int value);

    ~Shader() noexcept;
  private:
    std::string loadShaderSrc(const char* src_path) const;
  private:
    GLuint program_=0;
  };

}
