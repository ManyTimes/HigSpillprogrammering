#ifndef _MATRIX_H
#define _MATRIX_H

//#include <math.h>
#include "include.h"
#include "mathtool.h"

namespace cgl
{
	class DECLARE Matrix
	{
	private:
		float	m[16];
	public:
		Matrix::Matrix();
		Matrix::Matrix(float matrix[16]);
		void Matrix::LoadIdentity();
		float* Matrix::GetMatrixf();
		void Matrix::SetMatrixf(float matrix[16]);
		Vector3f Matrix::GetRightVector();
		Vector3f Matrix::GetUpVector();
		Vector3f Matrix::GetForwardVector();
		float& operator[](int i);
		Vector3f Matrix::operator*(Vector3f vector) const;
		Vector3f Matrix::operator*(float v[4]) const;
		Matrix Matrix::operator*(Matrix ma) const;
		void Matrix::operator=(Matrix ma);
	};
}

#endif