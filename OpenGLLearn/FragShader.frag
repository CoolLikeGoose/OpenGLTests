#version 410 core

in vec3 _color;
in vec2 _texCoord;

uniform sampler2D _texture;

out vec4 color;

void main()
{
	color = texture(_texture, _texCoord) * vec4(_color, 1.0f);
}