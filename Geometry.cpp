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
    if(p.getX() == x_ && p.getY() == y_ ){
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

// My Overrides

void LineSegment::translate(float x, float y) {
    x1_ = x1_ + x; x2_ = x2_ + x;
    y1_ = y1_ + y; y2_ = y2_ + y;

}

void LineSegment::rotate(){
    // TODO: Try putting this in the Shape, since it might work

    // Finds The center to rotate around
    float center_x = (x1_ + x2_) / 2;
    float center_y = (y1_ + y2_) / 2;

    // Moves the line segment to the center
    x1_ -= center_x;  x2_ -= center_x;
    y1_ -= center_y;  y2_ -= center_y;

    //Rotates Both Points
    float xtemp = x1_; float ytemp = y1_;
    x1_ = -ytemp; y1_ = xtemp;

    xtemp = x2_; ytemp = y2_;
    x2_ = -ytemp; y2_ = xtemp;

    //Moves the line segment to the original position
    x1_ += center_x; x2_ += center_x;
    y1_ += center_y; y2_ += center_y;
}

bool LineSegment::contains(const Point &p) const {
//    if((p.getX() == x1_ && p.getY() == y1_) || (p.getX() == x2_ && p.getY() == y2_ )){
//        return true;
//    }
//    else{
//        return false; // dummy
//    }

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

