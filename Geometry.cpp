#include "Geometry.h"
#include <math.h>

// ============ Shape class =================

Shape::Shape(int d) {
	// IMPLEMENT ME
    if(d < 0){
        throw std::invalid_argument("Depth Cannot be negative");
    }
}

bool Shape::setDepth(int d) {
    if(d>=0){
        depth_ = d;
        return true;
    }
    else{
        return false;
    }
}

int Shape::getDepth() const {
	return depth_;
}

int Shape::dim() const {
	return dimension_; // dummy
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
    // You can't scale a point, this is used just to check if scale is <= 0;
    if(f <= 0){
        throw std::invalid_argument("Scaling factor cannot be zero or negative");
    }
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

Point::Point(float x, float y, int d) : Shape(d) {
	// IMPLEMENT ME
    if(d < 0){
        throw std::invalid_argument("Negative Depth is not allowed");
    }
    x_ = x;
    y_ = y;
    depth_ = d;
    dimension_ = 0;
}

float Point::getX() const {
	// IMPLEMENT ME
	return x_; // dummy
}

float Point::getY() const {
	// IMPLEMENT ME
	return y_; // dummy
}

void Point::setX(float x) {
        x_ = x;
}

void Point::setY(float y) {
    y_ = y;
}


// =========== LineSegment class ==============

LineSegment::LineSegment(const Point& p, const Point& q) : Shape(p.getDepth()) {
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
        depth_ = p.getDepth();
    // ^^^^^^^^^^^^^^^^^^^^^^^^^^
        dimension_ = 1;
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

    float x1 = p1_.getX(); float y1 = p1_.getY();
    float x2 = p2_.getX(); float y2 = p2_.getY();

    p1_.setX(x1 + x); p2_.setX(x2 + x);
    p1_.setY(y1 + y); p2_.setY(y2 + y);
//    x1_ = x1_ + x ; x2_ = x2_ + x;
//    y1_ = y1_ + y; y2_ = y2_ + y;

}

void LineSegment::rotate(){
    float x1 = p1_.getX(); float y1 = p1_.getY();
    float x2 = p2_.getX(); float y2 = p2_.getY();


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
    float x1 = p1_.getX(); float y1 = p1_.getY();
    float x2 = p2_.getX(); float y2 = p2_.getY();

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

TwoDShape::TwoDShape(int d) : Shape(d) {
	// IMPLEMENT ME
    dimension_ = 2;
    depth_ = d;
}

 float TwoDShape::area() const {
	// IMPLEMENT ME
	return -999; // dummy
}

TwoDShape::~TwoDShape() {}

// ============== Rectangle class ================

Rectangle::Rectangle(const Point& p, const Point& q) : TwoDShape(p.getDepth()) {
	// IMPLEMENT ME
    if(p.getDepth() != q.getDepth())
        throw std::invalid_argument("Points are on different depths");
    if (p.getX() == q.getX() && p.getY() == q.getY())
        throw std::invalid_argument("Points are Colliding");
    if(p.getX() == q.getX() && p.getY() == q.getY())
        throw std::invalid_argument("Points are horizontal/vertical to each other");
    if(p.getX() == q.getX() || p.getY() == q.getY())
        throw std::invalid_argument("Two points on the same coordinate");

    p1_ = Point(p.getX(),p.getY(),p.getDepth());
    p2_ = Point(q.getX(),q.getY(),q.getDepth());
    p3_ = Point(q.getX(),p.getY(),p.getDepth());
    p4_ = Point(p.getX(),q.getY(),q.getDepth());
    //TODO: Make an override function
    depth_ = p.getDepth();
    dimension_ = 2;

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

    Point* arr[4] = {&p1_,&p2_,&p3_,&p4_};
    for(int i = 0; i<4; i++){
        arr[i]->setX(arr[i]->getX() + x);
        arr[i]->setY(arr[i]->getY() + y);
    }
}

void Rectangle::rotate() {
    // The same as Line Segments

    float x1 = p1_.getX(); float y1 = p1_.getY();
    float x2 = p2_.getX(); float y2 = p2_.getY();


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

    // Finding new X Y Coordinates for p3_ and p4_ based on new values
    // NOT COPY PASTED CODE:
    p3_.setX(x2); p3_.setY(y1);
    p4_.setX(x1); p4_.setY(y2);
}

bool Rectangle::contains(const Point &p) const {
    //TODO: Might need to remove this and finalise Line Segment, since this is the same as line segment
    if(((getXmin() <= p.getX()) && (p.getX() <= getXmax()))
       && ((getYmin() <= p.getY()) && (p.getY() <= getYmax()))){
        return true;
    }else{
        return false;
    }
}

void Rectangle::scale(float f) {
    if(f <= 0){
        throw std::invalid_argument("Scaling factor cannot be zero or negative");
    }
    // Getting X and Y coordinates of points
    float x1 = p1_.getX(); float y1 = p1_.getY();
    float x2 = p2_.getX(); float y2 = p2_.getY();

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

    // Finding new X Y Coordinates for p3_ and p4_ based on new values
    // NOT COPY PASTED CODE:
    p3_.setX(x2); p3_.setY(y1);
    p4_.setX(x1); p4_.setY(y2);

}

float Rectangle::area() const {
    return (getXmax()-getXmin())*(getYmax()-getYmin());
}

// ================== Circle class ===================

Circle::Circle(const Point& c, float r) : TwoDShape(c.getDepth()) {
	// IMPLEMENT ME
    if(r <= 0){
        throw std::invalid_argument("Radius cannot be <= 0");
    } else
        p1_ = Point(c.getX(),c.getY(),c.getDepth());
        r_ = r;
        depth_ = c.getDepth();
        dimension_ = 2;

}

float Circle::getX() const {
	// IMPLEMENT ME
	return p1_.getX(); // dummy
}

float Circle::getY() const {
	// IMPLEMENT ME
	return p1_.getY(); // dummy
}

float Circle::getR() const {
	// IMPLEMENT ME
	return r_; // dummy
}

void Circle::setR(float r) {
    r_ = r;
}

void Circle::translate(float x, float y) {
    p1_.setX(p1_.getX() + x);
    p1_.setY(p1_.getY() + y);
}

void Circle::scale(float f) {
    if(f <= 0){
        throw std::invalid_argument("Scaling factor cannot be zero or negative");
    } else
        setR((float)(r_ * f));



}

bool Circle::contains(const Point &p) const{
    if( pow((p.getX() - p1_.getX()),2) + pow((p.getY() - p1_.getY()),2) < pow(r_,2) ){
        return true;
    } else
        return false;
}

float Circle::area() const{
    return PI*pow(r_,2);
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

