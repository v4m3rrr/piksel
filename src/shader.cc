#include "piksel/shader.hh"

#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <ios>
#include <stdexcept>
#include <iostream>
#include <memory>

namespace piksel
{
  Shader::Shader(
    std::string_view vertex_shader_src_path, 
    std::string_view fragment_shader_src_path)
    :
      Shader(
          CompileShader(loadShaderSrc(
              vertex_shader_src_path.data()),ShaderType::VertexType),
          CompileShader(loadShaderSrc(
              fragment_shader_src_path.data()),ShaderType::FragmentType))
  {
  }

  Shader::Shader(CompileShader vertex_shader, CompileShader fragment_shader)
  {
    program_=glCreateProgram();
    glAttachShader(program_,vertex_shader.get());
    glAttachShader(program_,fragment_shader.get());

    glLinkProgram(program_);

    glDetachShader(program_,vertex_shader.get());
    glDetachShader(program_,fragment_shader.get());

    glValidateProgram(program_);

    GLint success;
    glGetProgramiv(program_,GL_VALIDATE_STATUS,&success);
    if(success==GL_FALSE)
    {
      GLint log_info_len;
      glGetProgramiv(program_,GL_INFO_LOG_LENGTH,&log_info_len);

      auto info_log=std::make_unique<GLchar[]>(log_info_len);
      glGetProgramInfoLog(program_,log_info_len,NULL,info_log.get());

      std::cerr<<"Failed validate shader:\n"<<info_log<<std::endl;
      throw std::runtime_error("Failed failed validate shader");
    }
  }

  Shader::Shader(Shader&& other)
    :
      program_(other.program_)
  {
    other.program_=0;
  }

  Shader& Shader::operator=(Shader&& other)
  {
    program_=other.program_;

    other.program_=0;

    return *this;
  }

  Shader::~Shader() noexcept
  {
    if(program_!=0)
      glDeleteProgram(program_);
  }

  GLuint Shader::get() noexcept
  {
    return program_;
  }

  void Shader::use()
  {
    glUseProgram(program_);
  }

  void Shader::set(std::string_view name, int value)
  {
    glUniform1i(glGetUniformLocation(get(),name.data()),value);
  }

  void Shader::set(std::string_view name, const glm::mat4& value)
  {
    glUniformMatrix4fv(
        glGetUniformLocation(get(),name.data()),
        1,GL_FALSE,glm::value_ptr(value));
  }

  void Shader::set(std::string_view name, const glm::vec3& vec)
  {
    glUniform3f(
        glGetUniformLocation(get(),name.data()),
        vec.x,vec.y,vec.z);
  }

  std::string Shader::loadShaderSrc(const char* src_path)
  {
    std::ifstream fin(
        src_path,
        std::ios_base::in|std::ios_base::ate | std::ios_base::binary);
    if(!fin)
    {
      throw std::runtime_error("Failed to open shader source file");
    }

    auto size=static_cast<std::streamoff>(fin.tellg());
    std::string source(size+1,'\0');
    fin.seekg(0, std::ios_base::beg);
    if(!fin.read(source.data(), size))
      throw std::runtime_error("Failed to read shader source file");

    return source;
  }

  Shader::CompileShader::CompileShader(std::string_view src, ShaderType type)
  {
    shader_=glCreateShader((GLuint)type);
    
    auto* p=src.data();
    glShaderSource(shader_,1,&p,NULL);
    glCompileShader(shader_);

    GLint success;
    glGetShaderiv(shader_,GL_COMPILE_STATUS,&success);
    if(success==GL_FALSE)
    {
      GLint log_info_len;
      glGetShaderiv(shader_,GL_INFO_LOG_LENGTH,&log_info_len);

      auto info_log=std::make_unique<GLchar[]>(log_info_len);
      glGetShaderInfoLog(shader_,log_info_len,NULL,info_log.get());

      std::cerr<<"Failed compiling shader:\n"<<info_log<<std::endl;
      throw std::runtime_error("Failed compiling shader");
    }
  }

  GLuint Shader::CompileShader::get() noexcept
  {
    return shader_;
  }

  Shader::CompileShader::~CompileShader() noexcept
  {
    if(shader_!=0)
      glDeleteShader(shader_);
  }
}
