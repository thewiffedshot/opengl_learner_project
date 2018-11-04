#pragma once

struct Vector2
{
	float x, y;

	Vector2 operator+(Vector2 vec)
	{
		return { x + vec.x, y + vec.y };
	}

	Vector2 operator-()
	{
		return { -x, -y };
	}

	Vector2 operator-(Vector2 vec)
	{
		return { x - vec.x, y - vec.y };
	}

	void operator+=(Vector2 vec)
	{
		this->x += vec.x;
		this->y += vec.y;
	}

	void operator-=(Vector2 vec)
	{
		this->x -= vec.x;
		this->y -= vec.y;
	}
};

struct Vector3
{
	float x, y, z;

	Vector3 operator+(Vector3 vec)
	{
		return { x + vec.x, y + vec.y, z + vec.z };
	}

	Vector3 operator-()
	{
		return { -x, -y, -z };
	}

	Vector3 operator-(Vector3 vec)
	{
		return { x - vec.x, y - vec.y, z - vec.z };
	}

	void operator+=(Vector3 vec)
	{
		this->x += vec.x;
		this->y += vec.y;
		this->z += vec.z;
	}

	void operator-=(Vector3 vec)
	{
		this->x -= vec.x;
		this->y -= vec.y;
		this->z -= vec.z;
	}
};

struct Vector4
{
	float x, y, z, w;

	Vector4 operator+(Vector4 vec)
	{
		return { x + vec.x, y + vec.y, z + vec.z, w + vec.w };
	}

	Vector4 operator-()
	{
		return { -x, -y, -z, -w };
	}

	Vector4 operator-(Vector4 vec)
	{
		return { x - vec.x, y - vec.y, z - vec.z, w - vec.w };
	}

	void operator+=(Vector4 vec)
	{
		this->x += vec.x;
		this->y += vec.y;
		this->z += vec.z;
		this->w += vec.w;
	}

	void operator-=(Vector4 vec)
	{
		this->x -= vec.x;
		this->y -= vec.y;
		this->z -= vec.z;
		this->w -= vec.w;
	}
};