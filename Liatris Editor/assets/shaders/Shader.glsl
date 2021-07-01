#type vertex
#version 450 core

layout(location = 0) in vec3 POSITION;
layout(location = 1) in vec2 TEXCOORD_0;

layout(std140, binding = 0) uniform Camera
{
	mat4 u_ViewProjection;
    mat4 u_View;
    mat4 u_Projection;
};

layout(std140, binding = 1) uniform Model
{
    mat4 u_Model;
};

out vec2 v_uv;
out vec3 v_Normal;

void main()
{
    v_uv = TEXCOORD_0;
    gl_Position = u_ViewProjection * u_Model* vec4(POSITION, 1.0);
}

#type pixel
#version 450 core
layout(location = 0) out vec4 uv;
layout(location = 1) out int ID;

layout(std140, binding = 2) uniform Fragment
{
    int u_ID;
};

in vec2 v_uv;
in vec3 v_Normal;

void main()
{
    uv = vec4(v_uv, 0., 1.);
    ID = u_ID;
}