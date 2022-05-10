#version 330

in  vec3 exColour;

out vec4 fragColor;

uniform float opacity;

void main()
{
	fragColor = vec4(exColour, opacity);

}