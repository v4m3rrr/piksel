#define private public
#include "piksel/model.hh"
#undef private

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include <stdexcept>
#include <vector>
#include <iostream>

namespace piksel
{
  Mesh processMesh(aiMesh * mesh, const aiScene * scene);

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
      return;
    }

    processNode(scene->mRootNode, scene);
    std::cout<<"# of meshes: "<<meshes_.size()<<std::endl;

    int num_vert=0;
    int num_ind=0;
    for(const auto& mesh:meshes_)
    {
      num_ind+=mesh.indices_.size();
      num_vert+=mesh.vertices_.size();
    }
    std::cout<<"# of indices: "<<num_ind<<std::endl;
    std::cout<<"# of vertices: "<<num_vert<<std::endl;
  }

  void Model::processNode(aiNode * node, const aiScene * scene)
  {
    for(unsigned int i=0;i<node->mNumMeshes;i++){
      aiMesh *mesh=scene->mMeshes[node->mMeshes[i]];
      meshes_.push_back(processMesh(mesh,scene));
    }

    for(unsigned int i=0;i<node->mNumChildren;i++){
      processNode(node->mChildren[i],scene);
    }
  }

  Mesh processMesh(aiMesh * mesh, const aiScene * )
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

    return Mesh(std::move(vertices),std::move(indices));
  }

  void Model::draw(Shader& shader) const
  {
    for(const auto& mesh : meshes_)
    {
      mesh.draw(shader);
    }
  }
}
