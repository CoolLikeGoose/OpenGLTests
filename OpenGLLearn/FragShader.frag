#version 410 core

in vec3 _color;
in vec2 _texCoord;

uniform sampler2D _texture1;
uniform sampler2D _texture2;

out vec4 color;

void main()
{
	color = mix(texture(_texture1, _texCoord), texture(_texture2, _texCoord), 0.2);
}