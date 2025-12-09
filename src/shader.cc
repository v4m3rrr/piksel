#include "piksel/shader.hh"

#include <fstream>
#include <ios>
#include <stdexcept>
#include <iostream>
#include <memory>

namespace piksel
{
  Shader::Shader(
    const char* vertex_shader_src_path, 
    const char* fragment_shader_src_path
  )
  {
    std::string src=loadShaderSrc(vertex_shader_src_path);
    CompileShader vertex_sh(src,ShaderType::VertexType);

    src=loadShaderSrc(fragment_shader_src_path);
    CompileShader frag_sh(src,ShaderType::FragmentType);

    program_=glCreateProgram();
    glAttachShader(program_,vertex_sh.get());
    glAttachShader(program_,frag_sh.get());

    glLinkProgram(program_);

    glDetachShader(program_,vertex_sh.get());
    glDetachShader(program_,frag_sh.get());

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

  std::string Shader::loadShaderSrc(const char* src_path) const
  {
    std::ifstream fin(src_path,std::ios_base::in|std::ios_base::ate | std::ios_base::binary);
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

  Shader::~Shader() noexcept
  {
    if(program_!=0)
      glDeleteProgram(program_);
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
