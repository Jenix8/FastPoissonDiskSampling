#version 330 core
layout (location = 0) in vec2 aPos;

out float fragDepth;

void main()
{
   gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
   fragDepth = gl_Position.z / gl_Position.w;
   gl_PointSize = (1.0 - fragDepth) * 3;
}
