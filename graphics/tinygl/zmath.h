#ifndef GRAPHICS_TINYGL_ZMATH_H
#define GRAPHICS_TINYGL_ZMATH_H

namespace TinyGL {

#define X _v[0]
#define Y _v[1]
#define Z _v[2]
#define W _v[3]

// Matrix & Vertex
class Vector3 {
public:
	Vector3() { }
	Vector3(float x, float y, float z);

	//float getX() const { return _v[0]; }
	//float getY() const { return _v[1]; }
	//float getZ() const { return _v[2]; }

	//void setX(float val) { _v[0] = val; }
	//void setY(float val) { _v[1] = val; }
	//void setZ(float val) { _v[2] = val; }

	void normalize();

	float getLength() const { return sqrt(_v[0] * _v[0] + _v[1] * _v[1] + _v[2] * _v[2]); }

	static float dot(const Vector3 &a, const Vector3 &b) {
		return a._v[0] * b._v[0] + a._v[1] * b._v[1] + a._v[2] * b._v[2];
	}

	bool operator==(const Vector3 &other) const {
		return _v[0] == other._v[0] && _v[1] == other._v[1] && _v[2] == other._v[2];
	}

	bool operator!=(const Vector3 &other) const {
		return _v[0] != other._v[0] || _v[1] != other._v[1] || _v[2] != other._v[2];
	}

	Vector3 operator-() const {
		return Vector3(-_v[0],-_v[1],-_v[2]);
	}

	Vector3 operator*(float factor) const {
		return Vector3(_v[0] * factor, _v[1] * factor, _v[2] * factor);
	}

	Vector3 operator+(const Vector3 &other) const {
		return Vector3(_v[0] + other._v[0], _v[1] + other._v[1], _v[2] + other._v[2]);
	}

	Vector3 operator-(const Vector3 &other) const {
		return Vector3(_v[0] - other._v[0], _v[1] - other._v[1], _v[2] - other._v[2]);
	}

	Vector3 &operator*=(float factor) {
		_v[0] *= factor;
		_v[1] *= factor;
		_v[2] *= factor;
		return *this;
	}

	Vector3 &operator+=(float value) {
		_v[0] += value;
		_v[1] += value;
		_v[2] += value;
		return *this;
	}

	Vector3 &operator-=(float value) {
		_v[0] -= value;
		_v[1] -= value;
		_v[2] -= value;
		return *this;
	}

	float _v[3];
};

class Vector4 {
public:
	Vector4() { }
	Vector4(const Vector3 &vec, float w);
	Vector4(float x, float y, float z, float w);

	bool operator==(const Vector4 &other) const {
		return _v[0] == other._v[0] && _v[1] == other._v[1] && _v[2] == other._v[2] && _v[3] == other._v[3];
	}

	bool operator!=(const Vector4 &other) const {
		return _v[0] != other._v[0] || _v[1] != other._v[1] || _v[2] != other._v[2] || _v[3] != other._v[3];
	}

	Vector4 operator-() const {
		return Vector4(-_v[0],-_v[1],-_v[2],-_v[3]);
	}

	Vector4 operator*(float factor) const {
		return Vector4(_v[0] * factor, _v[1] * factor, _v[2] * factor,_v[3] * factor);
	}

	Vector4 operator+(const Vector4 &other) const {
		return Vector4(_v[0] + other._v[0], _v[1] + other._v[1], _v[2] + other._v[2], _v[3] + other._v[3]);
	}

	Vector4 operator-(const Vector4 &other) const {
		return Vector4(_v[0] - other._v[0], _v[1] - other._v[1], _v[2] - other._v[2], _v[3] - other._v[3]);
	}

	Vector4 &operator*=(float factor) {
		_v[0] *= factor;
		_v[1] *= factor;
		_v[2] *= factor;
		_v[3] *= factor;
		return *this;
	}

	Vector4 &operator+=(float value) {
		_v[0] += value;
		_v[1] += value;
		_v[2] += value;
		_v[3] += value;
		return *this;
	}

	Vector4 &operator-=(float value) {
		_v[0] -= value;
		_v[1] -= value;
		_v[2] -= value;
		_v[3] -= value;
		return *this;
	}

	Vector3 toVector3() const {
		return Vector3(_v[0],_v[1],_v[2]);
	}

	//float getX() const { return _v[0]; }
	//float getY() const { return _v[1]; }
	//float getZ() const { return _v[2]; }
	//float getW() const { return _v[3]; }

	//void setX(float val) { _v[0] = val; }
	//void setY(float val) { _v[1] = val; }
	//void setZ(float val) { _v[2] = val; }
	//void setW(float val) { _v[3] = val; }

	float _v[4];
};

class Matrix4 {
public:
	Matrix4() { }

	bool IsIdentity() const;

	inline Matrix4 operator+(const Matrix4 &b) const {
		Matrix4 result;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				result.set(i,j, get(i,j) + b.get(i,j));
			}
		}
		return result;
	}

	inline Matrix4 operator-(const Matrix4 &b) const {
		Matrix4 result;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				result.set(i,j, get(i,j) - b.get(i,j));
			}
		}
		return result;
	}

	inline Matrix4 operator*(const Matrix4 &b) const {
		Matrix4 result;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				float s = 0.0;
				for (int k = 0; k < 4; k++)
					s += this->get(i,k) * b.get(k,j);
				result.set(i,j,s);
			}
		}
		return result;
	}

	inline Matrix4 &operator*=(const Matrix4 &b) {
		Matrix4 a = *this;
		float s;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				s = 0.0;
				for (int k = 0; k < 4; k++)
					s += a.get(i,k) * b.get(k,j);
				this->set(i,j,s);
			}
		}
		return *this;
	}

	static Matrix4 identity();
	static Matrix4 rotation(float t, int u);

	void fill(float val) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				_m[i][j] = val;
			}
		}
	}

	inline void set(int x,int y,float val) {
		_m[x][y] = val;
	}

	inline float get(int x, int y) const {
		return _m[x][y];
	}

	void invert();
	void transpose();

	Matrix4 transpose() const;
	Matrix4 inverseOrtho() const;
	Matrix4 inverse() const;

	inline Vector3 transform(const Vector3 &vector) const {
		return Vector3(
			vector.X * _m[0][0] + vector.Y * _m[0][1] + vector.Z * _m[0][2] + _m[0][3],
			vector.X * _m[1][0] + vector.Y * _m[1][1] + vector.Z * _m[1][2] + _m[1][3],
			vector.X * _m[2][0] + vector.Y * _m[2][1] + vector.Z * _m[2][2] + _m[2][3]);
	}

	// Transform the vector as if this were a 3x3 matrix.
	inline Vector3 transform3x3(const Vector3 &vector) const {
		return Vector3(
			vector.X * _m[0][0] + vector.Y * _m[0][1] + vector.Z * _m[0][2],
			vector.X * _m[1][0] + vector.Y * _m[1][1] + vector.Z * _m[1][2],
			vector.X * _m[2][0] + vector.Y * _m[2][1] + vector.Z * _m[2][2]);
	}

	// Transform the vector as if this were a 3x4 matrix.
	inline Vector4 transform3x4(const Vector4 &vector) const {
		return Vector4(
			vector.X * _m[0][0] + vector.Y * _m[0][1] + vector.Z * _m[0][2] + _m[0][3],
			vector.X * _m[1][0] + vector.Y * _m[1][1] + vector.Z * _m[1][2] + _m[1][3],
			vector.X * _m[2][0] + vector.Y * _m[2][1] + vector.Z * _m[2][2] + _m[2][3],
			vector.X * _m[3][0] + vector.Y * _m[3][1] + vector.Z * _m[3][2] + _m[3][3]);
	}

	inline Vector4 transform(const Vector4 &vector) const {
		return Vector4(
			vector.X * _m[0][0] + vector.Y * _m[0][1] + vector.Z * _m[0][2] + vector.W * _m[0][3],
			vector.X * _m[1][0] + vector.Y * _m[1][1] + vector.Z * _m[1][2] + vector.W * _m[1][3],
			vector.X * _m[2][0] + vector.Y * _m[2][1] + vector.Z * _m[2][2] + vector.W * _m[2][3],
			vector.X * _m[3][0] + vector.Y * _m[3][1] + vector.Z * _m[3][2] + vector.W * _m[3][3]);
	}

private:
	float _m[4][4];
};

} // end of namespace TinyGL

#endif
