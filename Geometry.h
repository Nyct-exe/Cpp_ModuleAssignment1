#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include <iostream>
#include <memory>
#include <vector>

class Point; // forward declaration

class Shape {

public:
	// Default constructor, just to make this release version compilable.
//	// If your implementation is correct this should be removed
	Shape() = delete;

    virtual ~Shape();

	// Constructor specifying the depth of the object.
	// If d is negative, throw a std::invalid_argument exception.
	Shape(int d);

	// Set depth of object to d. If d is negative, return false and
	// do not update depth. Otherwise return true
	bool setDepth(int d);

	// Return the depth of object
    int getDepth() const;

	// Return the dimension_ of the object (0, 1 or 2)
	int dim() const;

    virtual // Translate the object horizontally by x and vertically by y
	void translate(float x, float y) = 0;

    virtual // Rotate the object 90 degrees around its centre
	void rotate() = 0;

    virtual // Scale the object by a factor f relative to its centre.
	// If f is zero or negative, throw a std::invalid-argument exception.
	void scale(float f) = 0;

	// Return true if the object contains p and false otherwise.
	// Depths are ignored for purpose of comparison
    virtual
	bool contains(const Point& p) const = 0;

	// the constant pi
	static constexpr double PI = 3.1415926;

protected:
    int depth_;
    int dimension_;
private:
	// add any protected/private member variables you need
};

class Point : public Shape {

public:
	// Constructor. Depth defaults to 0
	Point(float x, float y, int d=0);

    // Return basic information (see assignment page)
	float getX() const;
	float getY() const;

    // Sets X and Y Coordinates
    void setX(float x);
    void setY(float y);

    // Override Functions of the Shape Class
    bool contains(const Point &p) const override;

    void translate(float x, float y) override;

    void rotate() override;

    void scale(float f) override;

private:
	// add any member variables you need
    float x_, y_;

};

class LineSegment : public Shape {

public:
	// Constructor.
	// If the two points have different depths, or have the same x- and
	// y-coordinate, or if the line is not axis-aligned, throw a
	// std::invalid_argument exception
	LineSegment(const Point& p, const Point& q);

	// Return basic information (see assignment page)
	float getXmin() const;
	float getXmax() const;
	float getYmin() const;
	float getYmax() const;

	// Return the length of the line segment
	float length() const;

    // Override Functions of the Shape Class
    void translate(float x, float y) override;

    void rotate() override;

    bool contains(const Point &p) const override;

    void scale(float f) override;

private:
	// add any member variables you need
    Point p1_ = Point(0, 0), p2_ = Point(0, 0);

};

class TwoDShape : public Shape {

public:
	// Default constructor.
	// Similar comment to Student default constructor applies
    TwoDShape() = delete;

    //Destructor
    virtual ~TwoDShape();


	// Constructor specifying the depth d
	 TwoDShape(int d);


    // Return the area of the object
     virtual float area() const = 0;

protected:
private:
	// add any protected/private member variables you need
};

class Rectangle : public TwoDShape {

public:
	// Constructor.
	// If the two points have different depths, or have the same x-
	// and/or y-coordinate, throw a std::invalid_argument exception
	Rectangle(const Point& p, const Point& q);

	// Return basic information (see assignment page)
	float getXmin() const;
	float getYmin() const;
	float getXmax() const;
	float getYmax() const;


    // Override Functions of the Shape Class
    void translate(float x, float y) override;

    bool contains(const Point &p) const override;

    void rotate() override;

    void scale(float f) override;

    float area() const override;

private:
	// add any member variables you need
//    int depth;
    Point p1_ = Point(0, 0), p2_ = Point(0, 0);
    Point p3_ = Point(0, 0), p4_ = Point(0, 0);
};

class Circle : public TwoDShape {

public:
	// Constructor.
	// If r is zero or negative, throw a std::invalid-argument exception.
	Circle(const Point& c, float r);

	// Return basic information (see assignment page)
	float getX() const;
	float getY() const;
	float getR() const;

    //Sets a radius of a circle
    void setR(float r);

    // Override Functions of the Shape Class
    bool contains(const Point &p) const;

    void translate(float x, float y) override;

    void scale(float f) override;

    float area() const override;

    void rotate() override;

private:
	// add any member variables you need
    Point p1_ = Point(0, 0);
    float r_;
};


class Scene {

public:
	// Constructor
	Scene();

	// Add the pointer to the collection of pointers stored
	void addObject(std::shared_ptr<Shape> ptr);

	// Set the drawing depth to d
	void setDrawDepth(int d);

	// Constants specifying the size of the drawing area
	static constexpr int WIDTH = 60;
	static constexpr int HEIGHT = 20;

private:
	// add any member variables you need
    std::vector<std::shared_ptr<Shape>> shapeVector_;
    int drawingDepth_;

	// Draw objects as specified in the assignment page
friend std::ostream& operator<<(std::ostream& out, const Scene& s);
};

#endif /* GEOMETRY_H_ */
