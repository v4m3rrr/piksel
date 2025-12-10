#include "piksel/model.hh"
#include "piksel/shader.hh"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <glm/gtc/type_ptr.hpp>

#include <stdexcept>
#include <vector>

namespace piksel
{
  Mesh processMesh(aiMesh * mesh, const aiScene * scene, aiMatrix4x4 model);
  glm::mat4 aiToGlm(const aiMatrix4x4& m);

  Model::Model(std::string_view filepath)
  {
    Assimp::Importer importer;
    const aiScene* scene = 
      importer.ReadFile(
          filepath.data(),
          aiProcess_Triangulate|aiProcess_FlipUVs);	
	
    if(!scene||scene->mFlags&AI_SCENE_FLAGS_INCOMPLETE||!scene->mRootNode) 
    {
      throw std::runtime_error("Failed to load model");
    }

    processNode(scene->mRootNode, scene,aiMatrix4x4());
  }

  void Model::processNode(aiNode * node, const aiScene * scene, aiMatrix4x4 global_trans)
  {
    global_trans=global_trans*node->mTransformation;
    for(unsigned int i=0;i<node->mNumMeshes;i++){
      aiMesh *mesh=scene->mMeshes[node->mMeshes[i]];
      meshes_.push_back(processMesh(mesh,scene,global_trans));
    }

    for(unsigned int i=0;i<node->mNumChildren;i++){
      processNode(node->mChildren[i],scene,global_trans);
    }
  }

  Mesh processMesh(aiMesh * mesh, const aiScene *, aiMatrix4x4 model)
  {
    // TODO
    // Load textures.
  
    std::vector<Mesh::Vertex> vertices;
    std::vector<unsigned int> indices;

    for(unsigned int i=0;i<mesh->mNumVertices;i++)
    {
      Mesh::Vertex vertex;

      auto ai_pos=mesh->mVertices[i];
      vertex.pos.x=ai_pos.x;
      vertex.pos.y=ai_pos.y;
      vertex.pos.z=ai_pos.z;

      vertex.uv.x=0.f;
      vertex.uv.y=0.f;

      vertices.push_back(std::move(vertex));
    }

    for(unsigned int i=0;i<mesh->mNumFaces;i++)
    {
      aiFace face=mesh->mFaces[i];
      for(unsigned int j=0;j<face.mNumIndices;j++)
      {
        indices.push_back(face.mIndices[j]);
      }
    }

    Mesh new_mesh(std::move(vertices),std::move(indices));
    new_mesh.translate=aiToGlm(model);

    return new_mesh;
  }

  glm::mat4 aiToGlm(const aiMatrix4x4& m)
  {
      return glm::mat4(
          m.a1, m.b1, m.c1, m.d1,
          m.a2, m.b2, m.c2, m.d2,
          m.a3, m.b3, m.c3, m.d3,
          m.a4, m.b4, m.c4, m.d4
      );
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
