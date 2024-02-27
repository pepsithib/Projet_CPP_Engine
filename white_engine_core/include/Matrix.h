#pragma once

struct Vertex {
	float* v_array;
	unsigned int v_size;
};
struct Indices {
	unsigned int* i_array;
	unsigned int i_size;
};

class Matrix
{
	

public:
	Matrix();
	~Matrix();

	void SetVertex(float* vertex, unsigned int v_size);
	Vertex GetVertex();

	void SetIndices(unsigned int* indices, unsigned int i_size);
	Indices GetIndices();

private:

	Vertex* vertex;
	Indices* indices;
};

