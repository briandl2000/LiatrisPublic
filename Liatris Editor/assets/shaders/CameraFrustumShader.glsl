#type vertex
#version 450 core

vec3 gridPlane[8] = vec3[] (
    vec3(-1., -1., 1.), vec3(1., -1., 1.), 
    vec3(1., 1., 1.), vec3(-1., 1., 1.),

    vec3(-1., -1., -1.), vec3(1., -1., -1.), 
    vec3(1., 1., -1.), vec3(-1.,  1., -1.)
);

int indices[8*4] = int[] (
    0, 1, 1, 2, 2, 3, 3, 0,
    0, 4, 4, 7, 7, 3, 3, 0,
    1, 5, 5, 6, 6, 2, 2, 1,
    4, 5, 5, 6, 6, 7, 7, 4
);

layout(std140, binding = 0) uniform Camera
{
	mat4 u_ViewProjection;
    mat4 u_View;
    mat4 u_Projection;
};

layout(std140, binding = 3) uniform CameraObject
{
	uniform mat4 u_CameraView;
    uniform mat4 u_CameraProjection;
};

void main()
{
    vec3 pos = gridPlane[indices[gl_VertexID]].xyz;
    gl_Position = u_ViewProjection * (u_CameraView *inverse(u_CameraProjection)) * vec4(pos, 1.0);
}

#type pixel
#version 450 core
layout(location = 0) out vec4 OutColor;
layout(location = 1) out int ID;

void main()
{
    OutColor = vec4(.8, .8, .8, 1.);
    ID = -1;
}