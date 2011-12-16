#include "../Header/matrix.h"

namespace cgl
{
	Matrix::Matrix()
	{
		LoadIdentity();							// Load the Identity matrix by default.
	}

	Matrix::Matrix(float matrix[16])
	{
		memcpy(m, matrix, sizeof(m));			// Copy the matrix.
	}

	void Matrix::LoadIdentity()
	{
		memset(m, 0, sizeof(m));				// Set everything to 0
		m[0] = m[5] = m[10] = m[15] = 1.0f;		// Make the diagonal filled with 1's, creating the identity matrix.
	}

	float *Matrix::GetMatrixf()
	{
		return m;								// Returns pointer to the actual matrix structure.
	}
	void Matrix::SetMatrixf(float matrix[16])
	{
		memcpy(m, matrix, sizeof(m));
	}

	Vector3f Matrix::GetRightVector()
	{
		return Vector3f(m[0], m[1], m[2]); 
	}

	Vector3f Matrix::GetUpVector()
	{
		return Vector3f(m[4], m[5], m[6]); 
	}

	Vector3f Matrix::GetForwardVector()
	{
		return Vector3f(m[8], m[9], m[10]); 
	}

	float& Matrix::operator[](int i) 
	{
		return m[i];
	}

	Vector3f Matrix::operator*(Vector3f v) const
	{
		float r[3];
		r[0] = m[0] * v[0] + m[4] * v[1] + m[8]  * v[2];
		r[1] = m[1] * v[0] + m[5] * v[1] + m[9]  * v[2];
		r[2] = m[2] * v[0] + m[6] * v[1] + m[10] * v[2];
		return Vector3f(r[0], r[1], r[2]);
	}

	Vector3f Matrix::operator*(float v[4]) const
	{
		float r[4];
		r[0] = m[0] * v[0] + m[4] * v[1] + m[8]  * v[2] + m[12] * v[3];
		r[1] = m[1] * v[0] + m[5] * v[1] + m[9]  * v[2] + m[13] * v[3];
		r[2] = m[2] * v[0] + m[6] * v[1] + m[10] * v[2] + m[14] * v[3];
		r[3] = m[3] * v[0] + m[7] * v[1] + m[11] * v[2] + m[15] * v[3];
		return Vector3f(r[0], r[1], r[2]);
	}

	Matrix Matrix::operator*(Matrix ma) const
	{
		float result[16];
		float *a = ma.GetMatrixf();

		result[0] = m[0]  * a[0]  + m[4] * a[1]  + m[8]  * a[2] + m[12]  * a[3];
		result[1] = m[1]  * a[0]  + m[5] * a[1]  + m[9]  * a[2] + m[13]  * a[3];
		result[2] = m[2]  * a[0]  + m[6] * a[1]  + m[10] * a[2] + m[14]  * a[3];
		result[3] = m[3]  * a[0]  + m[7] * a[1]  + m[11] * a[2] + m[15]  * a[3];

		result[4] = m[0]  * a[4]  + m[4] * a[5]  + m[8]  * a[6] + m[12]  * a[7];
		result[5] = m[1]  * a[4]  + m[5] * a[5]  + m[9]  * a[6] + m[13]  * a[7];
		result[6] = m[2]  * a[4]  + m[6] * a[5]  + m[10] * a[6] + m[14]  * a[7];
		result[7] = m[3]  * a[4]  + m[7] * a[5]  + m[11] * a[6] + m[15]  * a[7];

		result[8] = m[0]  * a[8]  + m[4] * a[9]  + m[8]  * a[10] + m[12] * a[11];
		result[9] = m[1]  * a[8]  + m[5] * a[9]  + m[9]  * a[10] + m[13] * a[11];
		result[10] = m[2] * a[8]  + m[6] * a[9]  + m[10] * a[10] + m[14] * a[11];
		result[11] = m[3] * a[8]  + m[7] * a[9]  + m[11] * a[10] + m[15] * a[11];

		result[12] = m[0] * a[12] + m[4] * a[13] + m[8]  * a[14] + m[12] * a[15];
		result[13] = m[1] * a[12] + m[5] * a[13] + m[9]  * a[14] + m[13] * a[15];
		result[14] = m[2] * a[12] + m[6] * a[13] + m[10] * a[14] + m[14] * a[15];
		result[15] = m[3] * a[12] + m[7] * a[13] + m[11] * a[14] + m[15] * a[15];

		return Matrix(result);
	}

	void Matrix::operator=(Matrix ma)
	{
		SetMatrixf(ma.GetMatrixf());
	}

}