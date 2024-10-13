#pragma once
#include <cmath>

struct Vector4 {
	float x, y, z, w;
};
struct Vector3 {
	float x, y, z;
};
struct viewMatrix {
	float matrix[16];
};


class Maths
{
public:

	Vector3 screen;

	bool WorldToScreen(Vector3 pos, Vector3& screen, viewMatrix vmatrix, int windowWidth, int windowHeight) {
		float matrix[16];
		for (int i = 0; i < 16; ++i) {
			matrix[i] = vmatrix.matrix[i];
		}
		// Matrix-vector Product, multiplying world(eye) coordinates by projection matrix = clipCoords
		Vector4 clipCoords;
		clipCoords.x = pos.x * matrix[0] + pos.y * matrix[4] + pos.z * matrix[8] + matrix[12];
		clipCoords.y = pos.x * matrix[1] + pos.y * matrix[5] + pos.z * matrix[9] + matrix[13];
		clipCoords.z = pos.x * matrix[2] + pos.y * matrix[6] + pos.z * matrix[10] + matrix[14];
		clipCoords.w = pos.x * matrix[3] + pos.y * matrix[7] + pos.z * matrix[11] + matrix[15];

		if (clipCoords.w < 0.1f)
			return false;

		// perspective division, dividing by clip.W = Normalized Device Coordinates
		Vector3 NDC;
		NDC.x = clipCoords.x / clipCoords.w;
		NDC.y = clipCoords.y / clipCoords.w;
		NDC.z = clipCoords.z / clipCoords.w;

		this->screen.x = (windowWidth / 2 * NDC.x) + (NDC.x + windowWidth / 2);
		this->screen.y = -(windowHeight / 2 * NDC.y) + (NDC.y + windowHeight / 2);
		return true;
	}
	float GetDistance3D(Vector3 m_pos, Vector3 en_pos)
	{
		return (float)(sqrt(((en_pos.x - m_pos.x) * (en_pos.x - m_pos.x)) + ((en_pos.y - m_pos.y) * (en_pos.y - m_pos.y)) + ((en_pos.z - m_pos.z) * (en_pos.z - m_pos.z))));
	}

private:

};



/*
namespace maths {
	bool WorldToScreen(vec3d_f pos, vec3d_f& screen, float matrix[16], int windowWidth, int windowHeight)
	{

		Mathematics::clipCoords.x = pos.x * matrix[0] + pos.y * matrix[4] + pos.z * matrix[8] + matrix[12];
		Mathematics::clipCoords.y = pos.x * matrix[1] + pos.y * matrix[5] + pos.z * matrix[9] + matrix[13];
		Mathematics::clipCoords.z = pos.x * matrix[2] + pos.y * matrix[6] + pos.z * matrix[10] + matrix[14];
		Mathematics::clipCoords.w = pos.x * matrix[3] + pos.y * matrix[7] + pos.z * matrix[11] + matrix[15];

		if (clipCoords.w < 0.1f)
		{
			return false;
		}

		Mathematics::NDC.x = clipCoords.x / clipCoords.w;
		Mathematics::NDC.y = clipCoords.y / clipCoords.w;
		Mathematics::NDC.z = clipCoords.z / clipCoords.w;

		Mathematics::screen.x = (windowWidth / 2 * NDC.x) + (NDC.x + windowWidth / 2);
		Mathematics::screen.y = -(windowHeight / 2 * NDC.y) + (NDC.y + windowHeight / 2);

		return true;
	}
}*/