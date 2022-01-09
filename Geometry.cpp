#include "Geometry.h"

// ============ Shape class =================

Shape::Shape() {} // REMOVE ME

Shape::Shape(int d) {
	// IMPLEMENT ME
    if(d < 0){
        throw std::invalid_argument("Depth Cannot be negative");
    }
}

bool Shape::setDepth(int d) {
    if(d>0){
        depth = d;
        return true;
    }
    else{
        return false;
    }
}

int Shape::getDepth() const {
	return depth;
}

int Shape::dim() const {
	return dimension; // dummy
}

void Shape::translate(float x, float y) {
	// IMPLEMENT ME
    x_ = x_ + x;
    y_ = y_ + y;
}

void Shape::rotate() {
	// IMPLEMENT ME

}

void Shape::scale(float f) {
	// IMPLEMENT ME
}

bool Shape::contains(const Point& p) const {
	// IMPLEMENT ME (NOT FINISHED)
    if(p.getX() == x_ & p.getY() == y_ ){
        return true;
    }
    else{
        return false; // dummy
    }
}

// =============== Point class ================

Point::Point(float x, float y, int d) {
	// IMPLEMENT ME
    x_ = x;
    y_ = y;
    depth = d;
}

float Point::getX() const {
	// IMPLEMENT ME
	return x_; // dummy
}

float Point::getY() const {
	// IMPLEMENT ME
	return y_; // dummy
}


// =========== LineSegment class ==============

LineSegment::LineSegment(const Point& p, const Point& q) {
	// IMPLEMENT ME

    if(p.getDepth() != q.getDepth()){
        throw std::invalid_argument("Points are on different depths");
    }
    else if (p.getX() == q.getX() && p.getY() == q.getY()){
        throw std::invalid_argument("Points are Colliding");
    }
    else if(p.getX() != q.getX() && p.getY() != q.getY()){
        throw std::invalid_argument("Points are not horizontal/vertical to each other");
    }
    else
        //This might be cheating
        depth = p.getDepth();
    // ^^^^^^^^^^^^^^^^^^^^^^^^^^
        x1_ = p.getX(); y1_ = p.getY();
        x2_ = q.getX(); y2_ = q.getY();
}

float LineSegment::getXmin() const {
	// IMPLEMENT ME
    if(x1_ < x2_){
        return x1_;
    }
    else if(x1_ == x2_){
        return x1_;
    }
    else
	    return x2_; // dummy
}

float LineSegment::getXmax() const {
    // IMPLEMENT ME
    if(x1_ > x2_){
        return x1_;
    }
    else if(x1_ == x2_){
        return x1_;
    }
    else
        return x2_; // dummy
}

float LineSegment::getYmin() const {
	// IMPLEMENT
    if(y1_ < y2_){
        return y1_;
    }
    else if(y1_ == y2_){
        return y1_;
    }
    else
        return y2_; // dummy
}

float LineSegment::getYmax() const {
	// IMPLEMENT ME
    if(y1_ > y2_){
        return y1_;
    }
    else if(y1_ == y2_){
        return y1_;
    }
    else
        return y2_; // dummy
}

float LineSegment::length() const {
	// IMPLEMENT ME
    if(getYmax() - getYmin() != 0){
        return getYmax() - getYmin();
    }
    else if(getXmax() - getXmin() != 0){
        return getXmax() - getXmin(); // dummy
    }
}

// ============ TwoDShape class ================

TwoDShape::TwoDShape(){} // REMOVE ME

TwoDShape::TwoDShape(int d) {
	// IMPLEMENT ME
}

float TwoDShape::area() const {
	// IMPLEMENT ME
	return -999; // dummy
}

// ============== Rectangle class ================

Rectangle::Rectangle(const Point& p, const Point& q) {
	// IMPLEMENT ME
}

float Rectangle::getXmin() const {
	// IMPLEMENT ME
	return -999; // dummy
}

float Rectangle::getYmin() const {
	// IMPLEMENT ME
	return -999; // dummy
}

float Rectangle::getXmax() const {
	// IMPLEMENT ME
	return -999; // dummy
}

float Rectangle::getYmax() const {
	// IMPLEMENT ME
	return -999; // dummy
}

// ================== Circle class ===================

Circle::Circle(const Point& c, float r) {
	// IMPLEMENT ME
}

float Circle::getX() const {
	// IMPLEMENT ME
	return -999; // dummy
}

float Circle::getY() const {
	// IMPLEMENT ME
	return -999; // dummy
}

float Circle::getR() const {
	// IMPLEMENT ME
	return -999; // dummy
}

// ================= Scene class ===================

Scene::Scene() {
	// IMPLEMENT ME
}

void Scene::addObject(std::shared_ptr<Shape> ptr) {
	// IMPLEMENT ME
}

void Scene::setDrawDepth(int depth) {
	// IMPLEMENT ME
}

std::ostream& operator<<(std::ostream& out, const Scene& s) {
	// IMPLEMENT ME
	return out;
}

