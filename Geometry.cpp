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

float Point::setX(float x) {
        x_ = x;
}

float Point::setY(float y) {
    y_ = y;
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
        p1_ = Point(p.getX(),p.getY(),p.getDepth());
        p2_ = Point(q.getX(),q.getY(),q.getDepth());
        //This might be cheating
        depth = p.getDepth();
    // ^^^^^^^^^^^^^^^^^^^^^^^^^^
}

float LineSegment::getXmin() const {
	// IMPLEMENT ME
    if(p1_.getX() < p2_.getX()){
        return p1_.getX();
    }
    else if(p1_.getX() == p2_.getX()){
        return p1_.getX();
    }
    else
        return p2_.getX(); // dummy
}

float LineSegment::getXmax() const {
    // IMPLEMENT ME
    if(p1_.getX() > p2_.getX()){
        return p1_.getX();
    }
    else if(p1_.getX() == p2_.getX()){
        return p1_.getX();
    }
    else
        return p2_.getX(); // dummy
}

float LineSegment::getYmin() const {
    // IMPLEMENT
    if(p1_.getY() < p2_.getY()){
        return p1_.getY();
    }
    else if(p1_.getY() == p2_.getY()){
        return p1_.getY();
    }
    else
        return p2_.getY(); // dummy
}

float LineSegment::getYmax() const {
    // IMPLEMENT ME
    if(p1_.getY() > p2_.getY()){
        return p1_.getY();
    }
    else if(p1_.getY() == p2_.getY()){
        return p1_.getY();
    }
    else
        return p2_.getY(); // dummy
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
    
    int x1 = p1_.getX(); int y1 = p1_.getY();
    int x2 = p2_.getX(); int y2 = p2_.getY();
    
    p1_.setX(x1 + x); p2_.setX(x2 + x);
    p1_.setY(y1 + y); p2_.setY(y2 + y);
//    x1_ = x1_ + x ; x2_ = x2_ + x;
//    y1_ = y1_ + y; y2_ = y2_ + y;

}

void LineSegment::rotate(){
    int x1 = p1_.getX(); int y1 = p1_.getY();
    int x2 = p2_.getX(); int y2 = p2_.getY();
    
    
    // Finds The center to rotate around
    float center_x = (x1 + x2) / 2;
    float center_y = (y1 + y2) / 2;

    // Moves the line segment to the center
    x1 -= center_x;  x2 -= center_x;
    y1 -= center_y;  y2 -= center_y;

    //Rotates Both Points
    float xtemp = x1; float ytemp = y1;
    x1 = -ytemp; y1 = xtemp;

    xtemp = x2; ytemp = y2;
    x2 = -ytemp; y2 = xtemp;

    //Moves the line segment to the original position
    x1 += center_x; x2 += center_x;
    y1 += center_y; y2 += center_y;

    //Setting new values
    p1_.setX(x1); p1_.setY(y1);
    p2_.setX(x2); p2_.setY(y2);
}

bool LineSegment::contains(const Point &p) const {

    if(((getXmin() <= p.getX()) && (p.getX() <= getXmax()))
    && ((getYmin() <= p.getY()) && (p.getY() <= getYmax()))){
       return true;
    }else{
        return false;
    }
}

void LineSegment::scale(float f) {
    if(f <= 0){
        throw std::invalid_argument("Scaling factor cannot be zero or negative");
    }
    // Getting X and Y coordinates of points
    int x1 = p1_.getX(); int y1 = p1_.getY();
    int x2 = p2_.getX(); int y2 = p2_.getY();

    // Finds The center to rotate around
    float center_x = (x1 + x2) / 2;
    float center_y = (y1 + y2) / 2;

    // Moves the line segment to the center
    x1 -= center_x;  x2 -= center_x;
    y1 -= center_y;  y2 -= center_y;

    // Applies scaling to both points
    x1 *= f; x2 *= f;
    y1 *= f; y2 *= f;

    //Moves the line segment to the original position
    x1 += center_x; x2 += center_x;
    y1 += center_y; y2 += center_y;

    //Setting new values
    p1_.setX(x1); p1_.setY(y1);
    p2_.setX(x2); p2_.setY(y2);



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
    if(p.getDepth() != q.getDepth()){
        throw std::invalid_argument("Points are on different depths");
    }
    else if (p.getX() == q.getX() && p.getY() == q.getY()){
        throw std::invalid_argument("Points are Colliding");
    }
    else if(p.getX() == q.getX() && p.getY() == q.getY()){
        throw std::invalid_argument("Points are horizontal/vertical to each other");
    }
    else
        p1_ = Point(p.getX(),p.getY(),p.getDepth());
        p2_ = Point(q.getX(),q.getY(),q.getDepth());
        p3_ = Point(q.getX(),p.getY(),p.getDepth());
        p4_ = Point(p.getX(),q.getY(),q.getDepth());
        //TODO: Make an override function
        depth = p.getDepth();

}

float Rectangle::getXmin() const {
	// IMPLEMENT ME
    float arr[4] = {p1_.getX(),p2_.getX(),p3_.getX(),p4_.getX()};
    float minX=p1_.getX();
    for(int i = 0; i<4; i++){
        if(arr[i]<minX){
            minX = arr[i];
        }
    }
	return minX;
}

float Rectangle::getYmin() const {
	// IMPLEMENT ME
    float arr[4] = {p1_.getY(),p2_.getY(),p3_.getY(),p4_.getY()};
    float minY=p1_.getY();
    for(int i = 0; i<4; i++){
        if(arr[i]<minY){
            minY = arr[i];
        }
    }
    return minY;
}

float Rectangle::getXmax() const {
	// IMPLEMENT ME
    float arr[4] = {p1_.getX(),p2_.getX(),p3_.getX(),p4_.getX()};
    float maxX=p1_.getX();
    for(int i = 0; i<4; i++){
        if(arr[i]>maxX){
            maxX = arr[i];
        }
    }
    return maxX;
}

float Rectangle::getYmax() const {
	// IMPLEMENT ME
    float arr[4] = {p1_.getY(),p2_.getY(),p3_.getY(),p4_.getY()};
    float maxY=p1_.getY();
    for(int i = 0; i<4; i++){
        if(arr[i]>maxY){
            maxY = arr[i];
        }
    }
    return maxY;
}

// Overrides

void Rectangle::translate(float x, float y) {
    Point arr[4] = {p1_,p2_,p3_,p4_};
    for(int i = 0; i<4; i++){
        arr[i].setX(arr[i].getX() + x);
        arr[i].setY(arr[i].getY() + y);
    }
}

void Rectangle::rotate() {
//    Point arr[4] = {p1_,p2_,p3_,p4_};
//    for(int i = 0; i<4; i++){
//
//    }
}

bool Rectangle::contains(const Point &p) const {

}

void Rectangle::scale(float f) {

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

