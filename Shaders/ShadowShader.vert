#version 330

layout (location = 0) in vec3 vPos;
layout(location = 1) in vec3 vCol;
layout (location = 2) in vec3 vNormal;
layout (location = 3) in vec2 vTexCoords;

out VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
} vs_out;

uniform mat4 view;
uniform mat4 model;
uniform mat4 lightSpaceMatrix;

void main()
{    
    vs_out.FragPos = vec3(model * vec4(vPos, 1.0));
    vs_out.Normal = transpose(inverse(mat3(model))) * vNormal;
    vs_out.TexCoords = vTexCoords;
    vs_out.FragPosLightSpace = lightSpaceMatrix * vec4(vs_out.FragPos, 1.0);
    gl_Position = view * vec4(vs_out.FragPos, 1.0);
}