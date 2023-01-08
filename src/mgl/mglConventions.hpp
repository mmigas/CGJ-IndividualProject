////////////////////////////////////////////////////////////////////////////////
//
// Shader Naming Conventions 
//
// (c)2022 by Carlos Martinho
//
////////////////////////////////////////////////////////////////////////////////

#ifndef MGL_CONVENTIONS_HPP
#define MGL_CONVENTIONS_HPP

#include <string>

namespace mgl {

////////////////////////////////////////////////////////////////////////////////

    const std::string MODEL_MATRIX = "ModelMatrix";
    const std::string NORMAL_MATRIX = "NormalMatrix";
    const std::string VIEW_MATRIX = "ViewMatrix";
    const std::string PROJECTION_MATRIX = "ProjectionMatrix";
    const std::string TEXTURE_MATRIX = "TextureMatrix";
    const std::string CAMERA_BLOCK = "Camera";
    const std::string MATERIAL_BLOCK = "Material";
    const std::string LIGHT_BLOCK = "Light";
    const int CAMERA_BLOCK_BINDING_POINT = 1;
    const int MATERIAL_BLOCK_BINDING_POINT = 2;
    const int LIGHT_BLOCK_BINDING_POINT = 3;

    const std::string POSITION_ATTRIBUTE = "inPosition";
    const std::string NORMAL_ATTRIBUTE = "inNormal";
    const std::string TEXCOORD_ATTRIBUTE = "inTexcoord";
    const std::string TANGENT_ATTRIBUTE = "inTangent";
    const std::string BITANGENT_ATTRIBUTE = "inBitangent";

    enum ShaderType {
        unlit, light
    };

////////////////////////////////////////////////////////////////////////////////
} // namespace mgl

#endif /* MGL_CONVENTIONS_HPP */
