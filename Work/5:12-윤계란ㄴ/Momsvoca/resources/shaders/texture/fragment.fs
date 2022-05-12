#version 330

in  vec2 outTexCoord;
out vec4 fragColor;

uniform sampler2D texture_sampler;
uniform float opacity;

void main()
{
    fragColor = texture(texture_sampler, outTexCoord);

    fragColor.w = fragColor.w*opacity;

    if(fragColor.w < 0.02)
        discard;
}