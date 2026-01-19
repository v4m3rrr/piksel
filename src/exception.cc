#include "piksel/exception.hh"

#include <sstream>

namespace piksel
{
  Exception::Exception(
        Type type,
        const std::string& msg, 
        const std::source_location location)
    :
      type_(type),msg_(msg),location_(location)
  {
  }

  const char* Exception::what() const noexcept 
  {
    buffer_=getFormattedMessage();
    return buffer_.data();
  }

  Exception::Type Exception::getType() const noexcept
  {
    return type_;
  }

  std::string_view Exception::getFile()const noexcept
  {
    return location_.file_name();
  }

  unsigned int Exception::getLine()const noexcept
  {
    return location_.line();
  }

  std::string Exception::getFormattedMessage() const
  {
    std::stringstream ss;
    ss<<"Piksel exception"<<std::endl;
    ss<<"Type: "<<getTypeString(getType())<<std::endl;
    ss<<"File: "<<getFile()<<std::endl;
    ss<<"Line: "<<getLine()<<std::endl;
    ss<<"Message: "<<msg_;

    return ss.str();
  }

  std::string_view Exception::getTypeString(Exception::Type type)
  {
    switch(type)
    {
      case Type::WindowError:
        return "WindowError";
      case Type::GraphicsError:
        return "GraphicsError";
      case Type::GuiManagerError:
        return "GuiManagerError";
      case Type::GltfExtractorError:
        return "GltfExtractorError";
    }

    return "";
  }
}
