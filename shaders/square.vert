#version 330 core
layout (location = 0) in vec2 vertex; // <vec2 position>

uniform vec3 color;
uniform mat4 transform;
uniform mat4 projection;

out vec3 outColor;


void main()
{
    gl_Position = projection * transform * vec4(vertex.xy, 0.0, 1.0);
    outColor = color;
}
