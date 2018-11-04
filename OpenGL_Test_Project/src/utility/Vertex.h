#pragma once
#include "utility\Vectors.h"

struct Vertex
{
	unsigned long index;
	Vector3 vertex;
	Vector3 normal;

	Vertex(Vector3 vertex, Vector3 normal, unsigned long index)
		: index(index), normal(normal), vertex(vertex)
	{
		
	}
};

