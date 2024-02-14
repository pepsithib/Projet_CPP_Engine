#pragma once
class File;

class Shader
{
public :

	Shader(File* vertexShaderFile, File* fragmentShaderFile);

	~Shader();

	unsigned int vertexShaderId;
	unsigned int fragmentShaderId;
	unsigned int programId;
};

