#ifndef VECTOR2_H
#define VECTOR2_H

class Vector2 {
	public:
	    float x,y;
			Vector2();
	    Vector2(float x, float y);
	    float distance(Vector2 other);
	    float angle(Vector2 other);
	    float size();
	    Vector2 operator-(const Vector2& v);
	    Vector2 operator+(const Vector2& v);
	    Vector2 operator/(const float& v);
	    Vector2 operator*(const float& v);
	    void operator+=(const Vector2& v);
	    bool operator==(const Vector2 v) const;
	    //bool closeToEdge(cv::Size edges);
};

#endif //VECTOR2_H
