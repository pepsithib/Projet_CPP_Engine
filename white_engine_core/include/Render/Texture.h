#pragma once
class Texture
{
public:
	Texture(const char* texturePath);
	~Texture();

	unsigned int textureId;
};

