#include "piksel/model.hh"

#include "piksel/shader.hh"

#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stdexcept>
#include <vector>

namespace piksel
{
  glm::mat4 getNodeTransform(const tinygltf::Node& node);
  Model::Model(std::string_view filepath)
  {
    tinygltf::Model model;

    tinygltf::TinyGLTF loader;
    std::string err;
    std::string warn;

    bool res = loader.LoadBinaryFromFile(&model, &err, &warn, filepath.data());

    if (!res)
      throw std::runtime_error("Failed to load model");

    auto scene=model.scenes[model.defaultScene];
    for(auto node_index : scene.nodes)
    {
      bindModelNodes(model,model.nodes[node_index],glm::mat4(1.f));
    }
  }

  void Model::bindModelNodes(
      const tinygltf::Model& model,
      const tinygltf::Node& node,
      const glm::mat4& transform)
  {
    glm::mat4 trans=getNodeTransform(node)*transform;

    if (node.mesh >= 0)
    {
      const tinygltf::Mesh& mesh = model.meshes[node.mesh];

      std::vector<piksel::Mesh::Vertex> vertices;
      std::vector<unsigned int> indices;

      for (const auto& primitive : mesh.primitives)
      {
        if (primitive.mode != TINYGLTF_MODE_TRIANGLES)
          throw std::runtime_error("TYLKO TROJKATY");

        auto posIt = primitive.attributes.find("POSITION");
        if (posIt == primitive.attributes.end())
          throw std::runtime_error("TYLKO TROJKATY");

        const tinygltf::Accessor& posAccessor =
          model.accessors[posIt->second];
        const tinygltf::BufferView& posView =
          model.bufferViews[posAccessor.bufferView];
        const tinygltf::Buffer& posBuffer =
          model.buffers[posView.buffer];

        size_t stride = posAccessor.ByteStride(posView);
        if (stride == 0) stride = sizeof(float) * 3;

        const unsigned char* posData =
          posBuffer.data.data() +
          posView.byteOffset +
          posAccessor.byteOffset;

        uint32_t baseVertex = static_cast<uint32_t>(vertices.size());

        for (size_t v = 0; v < posAccessor.count; ++v)
        {
          const float* p =
            reinterpret_cast<const float*>(posData + stride * v);

          piksel::Mesh::Vertex vert{};
          vert.pos = { p[0], p[1], p[2] };
          vert.uv  = { 0.0f, 0.0f };

          vertices.push_back(vert);
        }

        if (primitive.indices < 0)
          continue;

        const tinygltf::Accessor& idxAccessor =
          model.accessors[primitive.indices];
        const tinygltf::BufferView& idxView =
          model.bufferViews[idxAccessor.bufferView];
        const tinygltf::Buffer& idxBuffer =
          model.buffers[idxView.buffer];

        const unsigned char* idxData =
          idxBuffer.data.data() +
          idxView.byteOffset +
          idxAccessor.byteOffset;

        for (size_t i = 0; i < idxAccessor.count; ++i)
        {
          uint32_t index = 0;

          switch (idxAccessor.componentType)
          {
          case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT:
            index = reinterpret_cast<const uint16_t*>(idxData)[i];
            break;
          case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT:
            index = reinterpret_cast<const uint32_t*>(idxData)[i];
            break;
          default:
            throw std::runtime_error("Unsupported index type");
          }

          indices.push_back(index + baseVertex);
        }
      }

      this->meshes_.emplace_back(vertices, indices,trans);
    }


    for (int childIndex : node.children)
    {
      bindModelNodes(model, model.nodes[childIndex],trans);
    }
  }

  glm::mat4 getNodeTransform(const tinygltf::Node& node)
  {
    glm::mat4 T(1.f);
    glm::mat4 R(1.f);
    glm::mat4 S(1.f);

    if(node.translation.size()==3)
      T=glm::translate(glm::mat4(1.f),{
          node.translation[0],node.translation[1],node.translation[2]});

    if(node.rotation.size()==4)
      R=glm::mat4_cast(glm::quat{
          (float)node.rotation[3],
          (float)node.rotation[0],
          (float)node.rotation[1],
          (float)node.rotation[2]
          });

    if(node.scale.size()==3)
      S=glm::scale(glm::mat4(1.f),{
          node.scale[0],node.scale[1],node.scale[2]
          });

    return (T*R*S);
  }
  void Model::draw(Shader& shader) const
  {
    for(const auto& mesh : meshes_)
    {
      // TODO
      // It all should be in render Grahpics::render()
      glm::mat4 mesh_transform=mesh.getTransform();
      glm::mat4 transform=this->getTransform()*mesh_transform;
      glUniformMatrix4fv(
          glGetUniformLocation(shader.get(),"trans"),
          1,GL_FALSE,glm::value_ptr(transform));
      glUniform3f(
          glGetUniformLocation(shader.get(),"color"),
          color.r(),color.g(),color.b());
      mesh.draw(shader);
    }
  }
}
