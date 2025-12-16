#include <memory>
#include <stdexcept>
#include <vector>
#include <piksel/config.hh>
#include <string>
#include <iostream>

#define private public
#include <piksel/mesh.hh>
#include <piksel/model.hh>
#undef private

#include "piksel/window.hh"
#include "piksel/camera.hh"
#include "piksel/graphics.hh"
#include "piksel/camera.hh"
#include "piksel/color.hh"

std::shared_ptr<piksel::Model> g_model=std::make_shared<piksel::Model>();

void printMap(const std::map<std::string,int>& myMap) {
    std::cout << "--- Range-Based For Loop ---" << std::endl;
    for (const auto& pair : myMap) {
        std::cout << "Key: " << pair.first << ", Value: " << pair.second << std::endl;
    }
}

void BindModelNodes(const tinygltf::Model& model, const tinygltf::Node& node)
{
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

        g_model->meshes_.emplace_back(vertices, indices);
    }

    // Recurse into children
    for (int childIndex : node.children)
    {
        BindModelNodes(model, model.nodes[childIndex]);
    }
}

int main()
{
  constexpr float cam_speed=10.f; 
  piksel::Window wnd("Model load test", 1280,720);
  piksel::Camera cam({0.f,0.f,10.f},{0.f,0.f,0.f});
  piksel::Graphics gfx(
      wnd,cam,SHADERS_PATH"/single_color.vert",SHADERS_PATH"/single_color.frag");
  gfx.setBackground(piksel::Color::Blue);
  //constexpr const char*  filename=ASSETS_PATH"/models/tor.glb";
  constexpr const char*  filename=ASSETS_PATH"/models/F1_bolid.glb";
  //constexpr const char*  filename="Box.glb";
  tinygltf::Model model;

  tinygltf::TinyGLTF loader;
  std::string err;
  std::string warn;

  bool res = loader.LoadBinaryFromFile(&model, &err, &warn, filename);
  if (!warn.empty()) {
    std::cout << "WARN: " << warn << std::endl;
  }

  if (!err.empty()) {
    std::cout << "ERR: " << err << std::endl;
  }

  if (!res)
    std::cout << "Failed to load glb: " << filename << std::endl;
  else
    std::cout << "Loaded glb: " << filename << std::endl;


  auto scene=model.scenes[model.defaultScene];
  for(auto node_index : scene.nodes)
  {
    BindModelNodes(model,model.nodes[node_index]);
  }

  double scale_factor=0.25;

  gfx.addObject(g_model);
  
  float last=glfwGetTime();
  piksel::Window::MousePos prev_mouse_pos=wnd.getMousePos();
  while(wnd)
  {
    float right_now=glfwGetTime();
    float dt=right_now-last;
    last=right_now;

    if(wnd.getKey(GLFW_KEY_ESCAPE)==piksel::Window::KeyState::Press)
      wnd.close();
    
    if(wnd.getKey(GLFW_KEY_W)==piksel::Window::KeyState::Press){
      cam.moveLongitudinal(cam_speed*dt);
    }
    if(wnd.getKey(GLFW_KEY_S)==piksel::Window::KeyState::Press){
      cam.moveLongitudinal(-cam_speed*dt);
    }

    if(wnd.getKey(GLFW_KEY_A)==piksel::Window::KeyState::Press){
      cam.moveLateral(-cam_speed*dt);
    }
    if(wnd.getKey(GLFW_KEY_D)==piksel::Window::KeyState::Press){
      cam.moveLateral(cam_speed*dt);
    }

    piksel::Window::MousePos mouse_pos=wnd.getMousePos();
    cam.rotateYaw((prev_mouse_pos.x-mouse_pos.x)*dt/3.f);
    prev_mouse_pos.x=mouse_pos.x;
    cam.rotatePitch((prev_mouse_pos.y-mouse_pos.y)*dt/3.f);
    prev_mouse_pos.y=mouse_pos.y;

    gfx.render();
    wnd.update();
  }
  return res;
}
