#type vertex
#version 450 core

layout(std140, binding = 0) uniform Camera
{
	mat4 u_ViewProjection;
    mat4 u_View;
    mat4 u_Projection;
};

out vec3 nearPoint;
out vec3 farPoint;
out mat4 fragView;
out mat4 fragProj;

vec3 gridPlane[6] = vec3[] (
    vec3(1, 1, 0), vec3(-1,  1, 0), vec3(-1, -1, 0),
    vec3(-1, -1, 0),  vec3(1, -1, 0), vec3(1,  1, 0)
);

vec3 UnprojectPoint(float x, float y, float z, mat4 view, mat4 projection) {
    mat4 viewInv = inverse(view);
    mat4 projInv = inverse(projection);
    vec4 unprojectedPoint =  viewInv * projInv * vec4(x, y, z, 1.0);
    return unprojectedPoint.xyz / unprojectedPoint.w;
}

void main() {
    vec3 p = gridPlane[gl_VertexID].xyz;
    nearPoint = UnprojectPoint(p.x, p.y, 0.0, u_View, u_Projection).xyz;
    farPoint = UnprojectPoint(p.x, p.y, 1.0, u_View, u_Projection).xyz;
    fragView = u_View;
    fragProj = u_Projection;
    gl_Position = vec4(p, 1.0);
}

#type pixel
#version 450 core

float near = 0.01; //0.01
float far = 100.; //100

in vec3 nearPoint;
in vec3 farPoint;

in mat4 fragView;
in mat4 fragProj;

layout(location = 0) out vec4 outColor;
layout(location = 1) out int ID;

vec4 grid(vec3 fragPos3D, float scale, bool drawAxis) {
    vec2 coord = fragPos3D.xz * scale;
    vec2 derivative = fwidth(coord);
    vec2 grid = abs(fract(coord - 0.5) - 0.5) / derivative;
    float line = min(grid.x, grid.y);
    float minimumZ = min(derivative.y, 1);
    float minimumX = min(derivative.x, 1);
    vec4 color = vec4(0.125, 0.125, 0.125, 1.0 - min(line, 1.0));
    // z axis
    if(fragPos3D.x > -0.1 * minimumX && fragPos3D.x < 0.1 * minimumX)
        color.z = 1.0;
    // x axis
    if(fragPos3D.z > -0.1 * minimumZ && fragPos3D.z < 0.1 * minimumZ)
        color.x = 1.0;
    return color;
}

float computeDepth(vec3 pos) {
	vec4 clipSpacePos = fragProj * fragView * vec4(pos.xyz, 1.0);

	float clipSpcaeDepth = clipSpacePos.z / clipSpacePos.w;

	float far = gl_DepthRange.far;
	float near = gl_DepthRange.near;

	float depth = (((far-near) * clipSpcaeDepth) + near + far) / 2.0;

	return depth;
}

float computeLinearDepth(vec3 pos) {
    vec4 clipSpacePos = fragProj * fragView * vec4(pos.xyz, 1.0);
    float clipSpcaeDepth = (clipSpacePos.z / clipSpacePos.w) * 2.0 - 1.0;
    float linearDepth = (2.0 * near * far) / (far + near - clipSpcaeDepth * (far - near));
    return linearDepth / far; // normalize
}

void main() {
    float t = -nearPoint.y / (farPoint.y - nearPoint.y);
    if (t < 0.)
        discard;
    vec3 fragPos3D = nearPoint + t * (farPoint - nearPoint);
    //if(abs(fragPos3D.x)>10. || abs(fragPos3D.z)>10. ) discard;
    gl_FragDepth = computeDepth(fragPos3D);

    float linearDepth = computeLinearDepth(fragPos3D);
    float fading = max(0, (0.5 - linearDepth));

    vec4 gridSmall = (grid(fragPos3D, 1., true) + grid(fragPos3D, 1, true))* float(t > 0);
    gridSmall.a *= smoothstep(0.2, 0., linearDepth);
    vec4 gridBig = (grid(fragPos3D, 1./10., true) + grid(fragPos3D, 1./10., true))* float(t > 0);
    
    outColor = (gridBig+gridSmall);
    outColor.a *= fading;
    if(outColor.a < .1) discard;

    ID = -1;
}
