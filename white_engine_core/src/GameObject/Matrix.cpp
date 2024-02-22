#include "Matrix.h"
#include <string.h> 

Matrix::Matrix()
{
	vertex = new Vertex();
	indices = new Indices();
}

Matrix::~Matrix()
{
	delete vertex->v_array;
	delete indices->i_array;
	delete vertex;
	delete indices;
}

void Matrix::SetVertex(float* newVertex, unsigned int newv_size)
{	
	if(vertex->v_array != NULL)
		delete vertex->v_array;
	vertex->v_array = new float[newv_size]();
	vertex->v_size = newv_size;
	memcpy(vertex->v_array, newVertex, sizeof(float) * newv_size);
}

Vertex Matrix::GetVertex()
{
	return *vertex;
}

void Matrix::SetIndices(unsigned int* newIndices, unsigned int newi_size)
{	
	delete indices->i_array;
	indices->i_array = new unsigned int[newi_size];
	indices->i_size = newi_size;
	memcpy(indices->i_array, newIndices, sizeof(float) * newi_size);
}

Indices Matrix::GetIndices()
{
	return *indices;
}
