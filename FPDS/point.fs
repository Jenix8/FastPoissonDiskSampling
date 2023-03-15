#version 330 core
out vec4 FragColor;
uniform vec3 color;

void main()
{
	vec3 N;
	N.xy = gl_PointCoord - vec2(0.5);
	float mag = dot(N.xy, N.xy);
	if (mag > 0.25) discard;
	N.z = sqrt(1.0 - mag);

	FragColor = vec4(color, 1.0f);
}