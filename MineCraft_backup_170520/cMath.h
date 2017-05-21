#pragma once

#include "stdafx.h"

#define MATH				cMath::GetInstance()
#define EPSILON				0.01f
#define PI					3.141592f
#define ANGLE_TO_RADIAN		0.0174533f
#define RADIAN_TO_ANGLE		57.2958f

struct Vector
{
	float x, y;

	Vector() { x = 0.0f; y = 0.0f; }
	Vector(float x, float y) { this->x = x; this->y = y; }
	Vector(POINT point) { x = point.x; y = point.y; }

	float Magnitude() { return sqrt(SqrMagnitude()); }
	float SqrMagnitude() { return pow(x, 2) + pow(y, 2); }
	Vector Normalize()
	{
		float mag = Magnitude();
		if (mag == 0) return Zero();
		return *this / mag;
	}

	Vector operator * (float num) { return Vector(x * num, y * num); }
	Vector operator / (float num) { return Vector(x / num, y / num); }
	Vector& operator *= (float num) { x *= num; y *= num; return *this; }
	Vector& operator /= (float num) { x /= num; y /= num; return *this; }

	Vector operator + (Vector v) { return Vector(x + v.x, y + v.y); }
	Vector operator - (Vector v) { return Vector(x - v.x, y - v.y); }
	Vector operator * (Vector v) { return Vector(x * v.x, y * v.y); }
	Vector operator / (Vector v) { return Vector(x / v.x, y / v.y); }
	Vector& operator += (Vector v) { x += v.x; y += v.y; return *this; }
	Vector& operator -= (Vector v) { x -= v.x; y -= v.y; return *this; }
	Vector& operator *= (Vector v) { x *= v.x; y *= v.y; return *this; }
	Vector& operator /= (Vector v) { x /= v.x; y /= v.y; return *this; }

	bool operator == (Vector v) { return x == v.x && y == v.y; }
	bool operator != (Vector v) { return x != v.x || y != v.y; }

	static Vector Zero() { return Vector(0.0f, 0.0f); }
	static Vector One() { return Vector(1.0f, 1.0f); }
	static Vector Left() { return Vector(-1.0f, 0.0f); }
	static Vector Right() { return Vector(1.0f, 0.0f); }
	static Vector Up() { return Vector(0.0f, -1.0f); }
	static Vector Down() { return Vector(0.0f, 1.0f); }
};

// 선분
struct Line
{
	Vector point;
	Vector dir;
	float length;

	Line(Vector startPos, Vector endPos)
	{
		point = startPos;
		dir = (endPos - startPos).Normalize();
		length = (endPos - startPos).Magnitude();
	}

	void SetEndPoint(Vector endPoint)
	{
		dir = (endPoint - point).Normalize();
		length = (endPoint - point).Magnitude();
	}

	Vector StartPoint() { return point; }
	Vector EndPoint() { return point + dir * length; }
	float Slope() { return (EndPoint().y - StartPoint().y) / (EndPoint().x - StartPoint().x); }
};

// 벽
struct Wall
{
	Vector point;
	Vector dir;
	float length;
	int index;
	float scale;

	Wall(Vector startPos, Vector endPos)
	{
		point = startPos;
		dir = (endPos - startPos).Normalize();
		length = (endPos - startPos).Magnitude();
		index = -1;
		scale = 1;
	}

	void SetEndPoint(Vector endPoint)
	{
		dir = (endPoint - point).Normalize();
		length = (endPoint - point).Magnitude();
	}
	void SetIndex(int index) { this->index = index; }
	void SetScale(float scale)
	{
		length = length  * scale;
		this->scale = scale;
	}
	void SetStartPoint(Vector startPos) { point = startPos; }
	void AddStartPoint(Vector addPos) { point += addPos; }

	Vector StartPoint() { return point; }
	Vector EndPoint() { return point + dir * length; }
	float Slope() { return (EndPoint().y - StartPoint().y) / (EndPoint().x - StartPoint().x); }
	float Size() { return length; }
	Vector Dir() { return dir; }
	int Index() { return index; }
};

// 원
struct Circle
{
	Vector center;
	float radius;

	Circle(Vector center, float radius)
	{
		this->center = center;
		this->radius = radius;
	}

	void SetCenter(Vector center) { this->center = center; }
	Vector Center() { return center; }
	float Radius() { return radius; }
};

// 사각형
struct Box
{
	Vector center, size;
	Vector dirX, dirY;

	Box(Vector center, Vector size, float angle = 0)
	{
		this->center = center;
		this->size = size;
		SetAngle(angle);
	}

	void SetSize(Vector size) { this->size = size; }
	void SetCenter(Vector center) { this->center = center; }
	void SetAngle(float angle)
	{
		dirX = Vector(cosf(angle * ANGLE_TO_RADIAN), -sinf(angle * ANGLE_TO_RADIAN));
		dirY = Vector(cosf((angle - 90) *ANGLE_TO_RADIAN), -sinf((angle - 90) * ANGLE_TO_RADIAN));
	}

	void SetLeftTop(Vector leftTop)
	{
		center = leftTop + Width() * 0.5f + Height() * 0.5f;
	}

	Vector Width() { return dirX * size.x; }
	Vector Height() { return dirY * size.y; }

	Vector Left() { return center - Width() * 0.5f; }
	Vector Right() { return center + Width() * 0.5f; }
	Vector Top() { return center - Height() * 0.5f; }
	Vector Down() { return center + Height() * 0.5f; }
	Vector LeftTop() { return center - Width() * 0.5f - Height() * 0.5f; }
	Vector LeftBottom() { return LeftTop() + Height(); }
	Vector RightTop() { return LeftTop() + Width(); }
	Vector RightBottom() { return LeftTop() + Width() + Height(); }
};

// 삼각형
struct Triangle
{
	Vector p0, p1, p2;

	Triangle(Vector point0, Vector point1, Vector point2)
	{
		p0 = point0;
		p1 = point1;
		p2 = point2;
	}
};

class Math
{
public:
	SINGLETONE(cMath);

	float Min(float a, float b) { return (a < b) ? a : b; }
	float Max(float a, float b) { return (a > b) ? a : b; }
	float Clamp(float num, float min, float max) { num = Max(num, min); return Min(num, max); }

	float Cos(float angle) { return cosf(angle * ANGLE_TO_RADIAN); }
	float Sin(float angle) { return sinf(angle * ANGLE_TO_RADIAN); }
	float Tan(float angle) { return tanf(angle * ANGLE_TO_RADIAN); }
	float Dot(Vector a, Vector b) { return (a.x * b.x) + (a.y * b.y); }
	float CrossZ(Vector a, Vector b) { return (a.x * -b.y - -a.y * b.x); }

	float Distance(Vector from, Vector to) { return (to - from).Magnitude(); }
	float SqrDistance(Vector from, Vector to) { return (to - from).SqrMagnitude(); }
	Vector ToDirection(float angle) { return Vector(Cos(angle), -Sin(angle)); }
	Vector Project(Vector v, Vector axis) { return axis.Normalize() * ProjectLength(v, axis); }
	float ProjectLength(Vector v, Vector axis) { return Dot(v, axis.Normalize()); }
	float ProjectAbsLength(Vector v, Vector axis) { return abs(ProjectLength(v, axis)); }

	float SinAngle(Vector from, Vector to)
	{
		float value = CrossZ(from, to) / (from.Magnitude() * to.Magnitude());
		return asinf(value) * RADIAN_TO_ANGLE;
	}

	float CosAngle(Vector from, Vector to)
	{
		float value = Dot(from, to) / (from.Magnitude() * to.Magnitude());
		return acosf(value) * RADIAN_TO_ANGLE;
	}

	float Angle(Vector from, Vector to)
	{
		float angle = CosAngle(from, to);
		if (SinAngle(from, to) < 0) angle = 360 - angle;
		return angle;
	}

	float ToAngle(Vector dir)
	{
		float angle = CosAngle(Vector::Right(), dir);
		if (SinAngle(Vector::Right(), dir) < 0) angle = 360 - angle;
		return angle;
	}

	// 값을 일정 비율로 보간
	float Lerp(float from, float to, float rate)
	{
		rate = Clamp(rate, 0.0f, 1.0f);
		return from + (to - from) * rate;
	}

	// 벡터를 일정 비율로 보간
	Vector Lerp(Vector from, Vector to, float rate)
	{
		rate = Clamp(rate, 0.0f, 1.0f);
		return from * (1 - rate) + to * rate;
	}

	// 색을 일정 비율로 보간
	ColorF Lerp(ColorF from, ColorF to, float rate)
	{
		ColorF color(ColorF::Black);
		color.r = Lerp(from.r, to.r, rate);
		color.g = Lerp(from.g, to.g, rate);
		color.b = Lerp(from.b, to.b, rate);
		color.a = Lerp(from.a, to.a, rate);
		return color;
	}

	// 값을 일정 값만큼 보간
	float MoveForward(float from, float to, float delta)
	{
		float rate = delta / abs(from - to);
		return Lerp(from, to, rate);
	}

	// 벡터를 일정 값만큼 보간
	Vector MoveForward(Vector from, Vector to, float delta)
	{
		float rate = delta / (to - from).Magnitude();
		return Lerp(from, to, rate);
	}

	// 점에서 선까지 가장 가까운 점 반환
	Vector ClosestPoint(Vector point, Line line)
	{
		Vector vToPoint = point - line.StartPoint();

		float length = Dot(vToPoint, line.dir);
		length = Clamp(length, 0.0f, line.length);

		return line.StartPoint() + line.dir * length;
	}

	// 점에서 벽까지 가장 가까운 점 반환
	Vector ClosestPoint(Vector point, Wall line)
	{
		Vector vToPoint = point - line.StartPoint();

		float length = Dot(vToPoint, line.dir);
		length = Clamp(length, 0.0f, line.length);

		return line.StartPoint() + line.dir * length;
	}

	// 1차 함수 그래프
	float LinearGraph(Vector point, float slope, float x)
	{
		return slope * (x - point.x) + point.y;
	}

	// 2차 함수 그래프
	float QuadricGraph(Vector point, Vector vertex, float x)
	{
		float a = (point.y - vertex.y) / pow(point.x - vertex.x, 2);
		return a * pow(x - vertex.x, 2) + vertex.y;
	}

	// Sin 함수 그래프
	float SinGraph(float height, float angle)
	{
		return Sin(angle) * -height;
	}

	// Cos 함수 그래프
	float CosGraph(float height, float angle)
	{
		return Cos(angle) * -height;
	}

	// 점과 선 충돌
	bool IsCollided(Vector point, Line line)
	{
		float y = LinearGraph(line.point, line.Slope(), point.x);
		if (abs(point.y - y) < 0.01)
		{
			return Dot(point - line.StartPoint(), line.EndPoint() - point) > 0;
		}
		return false;
	}

	// 점과 원 충돌
	bool IsCollided(Vector point, Circle circle)
	{
		float sqrDist = SqrDistance(point, circle.center);
		return sqrDist <= circle.radius * circle.radius;
	}

	// 점과 사각형 충돌
	bool IsCollided(Vector point, Box box)
	{
		// AABB 충돌
		//Vector leftTop = box.LeftTop();
		//Vector rightBottom = box.RightBottom();
		//return point.x >= leftTop.x && point.x <= rightBottom.x
		//	&& point.y >= leftTop.y && point.y <= rightBottom.y;

		// OBB 충돌
		float distX = ProjectAbsLength(point - box.center, Vector::Right());
		float halfWidth = ProjectAbsLength(box.Width() * 0.5f, Vector::Right())
			+ ProjectAbsLength(box.Height() * 0.5f, Vector::Right());
		if (distX > halfWidth) return false;

		float distY = ProjectAbsLength(point - box.center, Vector::Down());
		float halfHeight = ProjectAbsLength(box.Width() * 0.5f, Vector::Down())
			+ ProjectAbsLength(box.Height() * 0.5f, Vector::Down());
		if (distY > halfHeight) return false;

		distX = ProjectAbsLength(point - box.center, box.dirX);
		if (distX > box.size.x * 0.5f) return false;

		distY = ProjectAbsLength(point - box.center, box.dirY);
		if (distY > box.size.y * 0.5f) return false;

		return true;
	}

	// 점과 삼각형 충돌
	bool IsCollided(Vector point, Triangle tri)
	{
		bool dir0 = CrossZ(tri.p1 - tri.p0, point - tri.p1) > 0;
		bool dir1 = CrossZ(tri.p2 - tri.p1, point - tri.p2) > 0;
		bool dir2 = CrossZ(tri.p0 - tri.p2, point - tri.p0) > 0;
		return dir0 == dir1 && dir0 == dir2;
	}

	// 원과 선 충돌
	bool IsCollided(Circle circle, Line line)
	{
		Vector pos = ClosestPoint(circle.center, line);
		return SqrDistance(pos, circle.center) <= circle.radius * circle.radius;
	}

	// 원과 벽 충돌
	bool IsCollided(Circle circle, Wall line)
	{
		Vector pos = ClosestPoint(circle.center, line);
		return SqrDistance(pos, circle.center) <= circle.radius * circle.radius;
	}

	// 원과 원 충돌
	bool IsCollided(Circle c0, Circle c1)
	{
		float totalRadius = c0.radius + c1.radius;
		return SqrDistance(c0.center, c1.center) <= totalRadius * totalRadius;
	}

	// 원과 박스 충돌
	bool IsCollided(Circle circle, Box box)
	{
		if (IsCollided(circle.center, box)) return true;
		if (IsCollided(circle, Line(box.LeftTop(), box.RightTop()))) return true;
		if (IsCollided(circle, Line(box.LeftTop(), box.LeftBottom()))) return true;
		if (IsCollided(circle, Line(box.RightBottom(), box.RightTop()))) return true;
		if (IsCollided(circle, Line(box.RightBottom(), box.LeftBottom()))) return true;
		return false;
	}

	// 원과 삼각형 충돌
	bool IsCollided(Circle circle, Triangle triangle)
	{
		if (IsCollided(circle.center, triangle)) return true;
		if (IsCollided(circle, Line(triangle.p0, triangle.p1))) return true;
		if (IsCollided(circle, Line(triangle.p1, triangle.p2))) return true;
		if (IsCollided(circle, Line(triangle.p2, triangle.p0))) return true;
		return false;
	}

	// 직선과 직선의 교차 여부 (교차점의 비율 반환)
	bool IsIntersected(Line a, Line b, float* pRate)
	{
		Vector A = a.StartPoint();
		Vector B = a.EndPoint();
		Vector C = b.StartPoint();
		Vector D = b.EndPoint();

		float value = CrossZ(B - A, D - C);
		if (abs(value) < EPSILON) return false;

		*pRate = CrossZ(C - A, D - C) / value;
		return true;
	}

	// 선과 선 충돌
	bool IsCollided(Line a, Line b, Vector* pCollidedPoint = NULL)
	{
		Vector A = a.StartPoint();
		Vector B = a.EndPoint();
		Vector C = b.StartPoint();
		Vector D = b.EndPoint();

		// 교차 여부 확인
		float t = 0.0f;
		if (IsIntersected(a, b, &t) && t >= 0.0f && t <= 1.0f)
		{
			if (IsIntersected(b, a, &t) && t >= 0.0f && t <= 1.0f)
			{
				if (pCollidedPoint != NULL) *pCollidedPoint = C + (D - C) * t;
				return true;
			}
		}

		// 평행선 충돌 여부 확인
		float value = CrossZ(a.EndPoint() - a.StartPoint(), b.EndPoint() - a.StartPoint());
		if (abs(value) < EPSILON)
		{
			if (Dot(A - C, A - D) < 0) { if (pCollidedPoint != NULL) *pCollidedPoint = A; return true; }
			if (Dot(B - C, B - D) < 0) { if (pCollidedPoint != NULL) *pCollidedPoint = B; return true; }
			if (Dot(C - A, C - B) < 0) { if (pCollidedPoint != NULL) *pCollidedPoint = C; return true; }
			if (Dot(D - A, D - B) < 0) { if (pCollidedPoint != NULL) *pCollidedPoint = D; return true; }
		}
		return false;
	}

	// 선과 박스 충돌
	bool IsCollided(Line line, Box box)
	{
		if (IsCollided(line.StartPoint(), box)) return true;
		if (IsCollided(line.EndPoint(), box)) return true;
		if (IsCollided(line, Line(box.LeftTop(), box.RightTop()))) return true;
		if (IsCollided(line, Line(box.LeftTop(), box.LeftBottom()))) return true;
		if (IsCollided(line, Line(box.RightBottom(), box.RightTop()))) return true;
		if (IsCollided(line, Line(box.RightBottom(), box.LeftBottom()))) return true;
		return false;
	}

	// 선과 삼각형 충돌
	bool IsCollided(Line line, Triangle triangle)
	{
		if (IsCollided(line.StartPoint(), triangle)) return true;
		if (IsCollided(line.EndPoint(), triangle)) return true;
		if (IsCollided(line, Line(triangle.p0, triangle.p1))) return true;
		if (IsCollided(line, Line(triangle.p1, triangle.p2))) return true;
		if (IsCollided(line, Line(triangle.p2, triangle.p0))) return true;
		return false;
	}

	// 박스와 박스 충돌
	bool IsCollided(Box a, Box b)
	{
		float distX = ProjectAbsLength(a.center - b.center, Vector::Right());
		float aWidth = ProjectAbsLength(a.Width() * 0.5f, Vector::Right())
			+ ProjectAbsLength(a.Height() * 0.5f, Vector::Right());
		float bWidth = ProjectAbsLength(b.Width() * 0.5f, Vector::Right())
			+ ProjectAbsLength(b.Height() * 0.5f, Vector::Right());
		if (distX > aWidth + bWidth) return false;

		float distY = ProjectAbsLength(a.center - b.center, Vector::Down());
		float aHeight = ProjectAbsLength(a.Width() * 0.5f, Vector::Down())
			+ ProjectAbsLength(a.Height() * 0.5f, Vector::Down());
		float bHeight = ProjectAbsLength(b.Width() * 0.5f, Vector::Down())
			+ ProjectAbsLength(b.Height() * 0.5f, Vector::Down());
		if (distY > aHeight + bHeight) return false;

		distX = ProjectAbsLength(a.center - b.center, a.dirX);
		aWidth = ProjectAbsLength(a.Width() * 0.5f, a.dirX) + ProjectAbsLength(a.Height() * 0.5f, a.dirX);
		bWidth = ProjectAbsLength(b.Width() * 0.5f, a.dirX) + ProjectAbsLength(b.Height() * 0.5f, a.dirX);
		if (distX > aWidth + bWidth) return false;

		distY = ProjectAbsLength(a.center - b.center, a.dirY);
		aHeight = ProjectAbsLength(a.Width() * 0.5f, a.dirY) + ProjectAbsLength(a.Height() * 0.5f, a.dirY);
		bHeight = ProjectAbsLength(b.Width() * 0.5f, a.dirY) + ProjectAbsLength(b.Height() * 0.5f, a.dirY);
		if (distY > aHeight + bHeight) return false;

		distX = ProjectAbsLength(a.center - b.center, b.dirX);
		aWidth = ProjectAbsLength(a.Width() * 0.5f, b.dirX) + ProjectAbsLength(a.Height() * 0.5f, b.dirX);
		bWidth = ProjectAbsLength(b.Width() * 0.5f, b.dirX) + ProjectAbsLength(b.Height() * 0.5f, b.dirX);
		if (distX > aWidth + bWidth) return false;

		distY = ProjectAbsLength(a.center - b.center, b.dirY);
		aHeight = ProjectAbsLength(a.Width() * 0.5f, b.dirY) + ProjectAbsLength(a.Height() * 0.5f, b.dirY);
		bHeight = ProjectAbsLength(b.Width() * 0.5f, b.dirY) + ProjectAbsLength(b.Height() * 0.5f, b.dirY);
		if (distY > aHeight + bHeight) return false;

		return true;
	}

	// 원과 선의 겹쳐진 벡터 반환
	Vector GetOverlappedVector(Circle from, Line to)
	{
		if (!IsCollided(from, to)) return Vector::Zero();

		Line line(from.center, ClosestPoint(from.center, to));
		float length = from.radius - line.length;
		return line.dir * length;
	}

	// 원과 원의 겹쳐진 벡터 반환
	Vector GetOverlappedVector(Circle from, Circle to)
	{
		if (!IsCollided(from, to)) return Vector::Zero();

		Line line(from.center, to.center);
		float length = (from.radius + to.radius) - line.length;
		return line.dir * length;
	}

	// 원과 박스의 겹쳐진 벡터 반환
	Vector GetOverlappedVector(Circle from, Box to)
	{
		if (!IsCollided(from, to)) return Vector::Zero();

		Vector v1 = GetOverlappedVector(from, Line(to.LeftTop(), to.RightTop()));
		from.center -= v1;
		Vector v2 = GetOverlappedVector(from, Line(to.LeftTop(), to.LeftBottom()));
		from.center -= v2;
		Vector v3 = GetOverlappedVector(from, Line(to.RightBottom(), to.RightTop()));
		from.center -= v3;
		Vector v4 = GetOverlappedVector(from, Line(to.RightBottom(), to.LeftBottom()));

		return v1 + v2 + v3 + v4;
	}

	// 박스와 박스의 겹쳐진 벡터 반환
	Vector GetOverlappedVector(Box from, Box to)
	{
		if (!IsCollided(from, to)) return Vector::Zero();

		Vector vDistX = Project(to.center - from.center, Vector::Right());
		float overlappedX = (to.size.x * 0.5f + from.size.x * 0.5) - vDistX.Magnitude();

		Vector vDistY = Project(to.center - from.center, Vector::Down());
		float overlappedY = (to.size.y * 0.5f + from.size.y * 0.5) - vDistY.Magnitude();

		return (overlappedX < overlappedY) ? vDistX.Normalize() * overlappedX
			: vDistY.Normalize() * overlappedY;
	}

	// 원과 선의 반사된 벡터 반환
	Vector GetReflectedVector(Circle& from, Line to, Vector dir)
	{
		Vector vOverlapped = GetOverlappedVector(from, to);
		if (vOverlapped.SqrMagnitude() > EPSILON)
		{
			from.center -= vOverlapped;
			return (dir - Project(dir, to.dir)) * -2.0f;
		}
		return Vector::Zero();
	}

	// 원과 박스의 반사된 벡터 반환
	Vector GetReflectedVector(Circle& from, Box to, Vector dir)
	{
		Vector vReflected;
		vReflected += GetReflectedVector(from, Line(to.LeftTop(), to.RightTop()), dir);
		vReflected += GetReflectedVector(from, Line(to.LeftTop(), to.LeftBottom()), dir);
		vReflected += GetReflectedVector(from, Line(to.RightBottom(), to.RightTop()), dir);
		vReflected += GetReflectedVector(from, Line(to.RightBottom(), to.LeftBottom()), dir);
		return vReflected;
	}

	// 원과 원의 반사된 벡터 반환
	Vector GetReflectedVector(Circle& from, Circle to, Vector dir)
	{
		Vector vOverlapped = GetOverlappedVector(from, to);
		if (vOverlapped.SqrMagnitude() > EPSILON)
		{
			from.center -= vOverlapped;

			Vector vTo = to.center - from.center;
			return (dir - Project(dir, Vector(-vTo.y, vTo.x))) * -2.0f;
		}
		return Vector::Zero();
	}

	// 박스와 박스의 겹쳐진 박스 반환
	Box GetOverlappedBox(Box a, Box b)
	{
		Vector min = (a.LeftTop().x < b.LeftTop().x && a.LeftTop().y < b.LeftTop().y) ?
			a.LeftTop() : b.LeftTop();
		Vector max = (a.RightBottom().x < b.RightBottom().x && a.RightBottom().y < b.RightBottom().y) ?
			a.RightBottom() : b.RightBottom();

		Vector center = min + (max - min) * 0.5f;
		float width = max.x - min.x;
		float height = max.y - min.y;
		return Box(center, Vector(width, height));
	}
};