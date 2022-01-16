#include "Geometry.h"
#include <cmath>
#include <algorithm>
#include <sstream>
#include <climits>

// ============ Shape class =================

Shape::Shape(int d) {

    if (d < 0) {
        throw std::invalid_argument("Depth Cannot be negative");
    }
    depth_ = 0;
    dimension_ = 0;
}

Shape::~Shape() {}

bool Shape::setDepth(int d) {
    if (d >= 0) {
        depth_ = d;
        return true;
    } else {
        return false;
    }
}

int Shape::getDepth() const {
    return depth_;
}

int Shape::dim() const {
    return dimension_;
}

void Shape::translate(float x, float y) {
    // Purely Virtual
}

void Shape::rotate() {
    // Purely Virtual
}

void Shape::scale(float f) {
    // Purely Virtual
}

bool Shape::contains(const Point &p) const {
    // Purely Virtual
}

// =============== Point class ================

Point::Point(float x, float y, int d) : Shape(d) {
    if (d < 0) {
        throw std::invalid_argument("Negative Depth is not allowed");
    }
    x_ = x;
    y_ = y;
    depth_ = d;
    dimension_ = 0;
}

float Point::getX() const {
    return x_;
}

float Point::getY() const {
    return y_;
}

void Point::setX(float x) {
    x_ = x;
}

void Point::setY(float y) {
    y_ = y;
}

bool Point::contains(const Point &p) const {
    if (p.getX() == x_ && p.getY() == y_) {
        return true;
    } else {
        return false;
    }
}

void Point::translate(float x, float y) {
    x_ = x_ + x;
    y_ = y_ + y;
}

void Point::rotate() {
    // Can't Rotate a Point
    // Does Nothing
}

void Point::scale(float f) {

    // You can't scale a point, this is used just to check if scale is <= 0;
    if (f <= 0) {
        throw std::invalid_argument("Scaling factor cannot be zero or negative");
    }
}


// =========== LineSegment class ==============

LineSegment::LineSegment(const Point &p, const Point &q) : Shape(p.getDepth()) {
    if (p.getDepth() != q.getDepth()) {
        throw std::invalid_argument("Points are on different depths");
    } else if (p.getX() == q.getX() && p.getY() == q.getY()) {
        throw std::invalid_argument("Points are Colliding");
    } else if (p.getX() != q.getX() && p.getY() != q.getY()) {
        throw std::invalid_argument("Points are not horizontal/vertical to each other");
    }
    p1_ = Point(p.getX(), p.getY(), p.getDepth());
    p2_ = Point(q.getX(), q.getY(), q.getDepth());
    depth_ = p.getDepth();
    dimension_ = 1;
}

float LineSegment::getXmin() const {

    if (p1_.getX() < p2_.getX()) {
        return p1_.getX();
    } else if (p1_.getX() == p2_.getX()) {
        return p1_.getX();
    } else
        return p2_.getX();
}

float LineSegment::getXmax() const {

    if (p1_.getX() > p2_.getX()) {
        return p1_.getX();
    } else if (p1_.getX() == p2_.getX()) {
        return p1_.getX();
    } else
        return p2_.getX();
}

float LineSegment::getYmin() const {

    if (p1_.getY() < p2_.getY()) {
        return p1_.getY();
    } else if (p1_.getY() == p2_.getY()) {
        return p1_.getY();
    } else
        return p2_.getY();
}

float LineSegment::getYmax() const {

    if (p1_.getY() > p2_.getY()) {
        return p1_.getY();
    } else if (p1_.getY() == p2_.getY()) {
        return p1_.getY();
    } else
        return p2_.getY();
}

float LineSegment::length() const {

    if (getYmax() - getYmin() != 0) {
        return getYmax() - getYmin();
    } else
        return getXmax() - getXmin();
}

// My Overrides

void LineSegment::translate(float x, float y) {

    float x1 = p1_.getX();
    float y1 = p1_.getY();
    float x2 = p2_.getX();
    float y2 = p2_.getY();

    p1_.setX(x1 + x);
    p2_.setX(x2 + x);
    p1_.setY(y1 + y);
    p2_.setY(y2 + y);

}

void LineSegment::rotate() {
    float x1 = p1_.getX();
    float y1 = p1_.getY();
    float x2 = p2_.getX();
    float y2 = p2_.getY();


    // Finds The center to rotate around
    float center_x = (x1 + x2) / 2;
    float center_y = (y1 + y2) / 2;

    // Moves the line segment to the center
    x1 -= center_x;
    x2 -= center_x;
    y1 -= center_y;
    y2 -= center_y;

    //Rotates Both Points
    float xtemp = x1;
    float ytemp = y1;
    x1 = -ytemp;
    y1 = xtemp;

    xtemp = x2;
    ytemp = y2;
    x2 = -ytemp;
    y2 = xtemp;

    //Moves the line segment to the original position
    x1 += center_x;
    x2 += center_x;
    y1 += center_y;
    y2 += center_y;

    //Setting new values
    p1_.setX(x1);
    p1_.setY(y1);
    p2_.setX(x2);
    p2_.setY(y2);
}

bool LineSegment::contains(const Point &p) const {

    if (((getXmin() <= p.getX()) && (p.getX() <= getXmax()))
        && ((getYmin() <= p.getY()) && (p.getY() <= getYmax()))) {
        return true;
    } else {
        return false;
    }
}

void LineSegment::scale(float f) {
    if (f <= 0) {
        throw std::invalid_argument("Scaling factor cannot be zero or negative");
    }
    // Getting X and Y coordinates of points
    float x1 = p1_.getX();
    float y1 = p1_.getY();
    float x2 = p2_.getX();
    float y2 = p2_.getY();

    // Finds The center to rotate around
    float center_x = (x1 + x2) / 2;
    float center_y = (y1 + y2) / 2;

    // Moves the line segment to the center
    x1 -= center_x;
    x2 -= center_x;
    y1 -= center_y;
    y2 -= center_y;

    // Applies scaling to both points
    x1 *= f;
    x2 *= f;
    y1 *= f;
    y2 *= f;

    //Moves the line segment to the original position
    x1 += center_x;
    x2 += center_x;
    y1 += center_y;
    y2 += center_y;

    //Setting new values
    p1_.setX(x1);
    p1_.setY(y1);
    p2_.setX(x2);
    p2_.setY(y2);


}



// ============ TwoDShape class ================

TwoDShape::TwoDShape(int d) : Shape(d) {

    dimension_ = 2;
    depth_ = d;
}

float TwoDShape::area() const {
    // Purely Virtual
    return -999;
}

TwoDShape::~TwoDShape() {}

// ============== Rectangle class ================

Rectangle::Rectangle(const Point &p, const Point &q) : TwoDShape(p.getDepth()) {

    if (p.getDepth() != q.getDepth())
        throw std::invalid_argument("Points are on different depths");
    if (p.getX() == q.getX() && p.getY() == q.getY())
        throw std::invalid_argument("Points are Colliding");
    if (p.getX() == q.getX() && p.getY() == q.getY())
        throw std::invalid_argument("Points are horizontal/vertical to each other");
    if (p.getX() == q.getX() || p.getY() == q.getY())
        throw std::invalid_argument("Two points on the same coordinate");

    p1_ = Point(p.getX(), p.getY(), p.getDepth());
    p2_ = Point(q.getX(), q.getY(), q.getDepth());
    p3_ = Point(q.getX(), p.getY(), p.getDepth());
    p4_ = Point(p.getX(), q.getY(), q.getDepth());
    depth_ = p.getDepth();
    dimension_ = 2;

}

float Rectangle::getXmin() const {

    float arr[4] = {p1_.getX(), p2_.getX(), p3_.getX(), p4_.getX()};
    float minX = p1_.getX();
    for (int i = 0; i < 4; i++) {
        if (arr[ i ] < minX) {
            minX = arr[ i ];
        }
    }
    return minX;
}

float Rectangle::getYmin() const {

    float arr[4] = {p1_.getY(), p2_.getY(), p3_.getY(), p4_.getY()};
    float minY = p1_.getY();
    for (int i = 0; i < 4; i++) {
        if (arr[ i ] < minY) {
            minY = arr[ i ];
        }
    }
    return minY;
}

float Rectangle::getXmax() const {

    float arr[4] = {p1_.getX(), p2_.getX(), p3_.getX(), p4_.getX()};
    float maxX = p1_.getX();
    for (int i = 0; i < 4; i++) {
        if (arr[ i ] > maxX) {
            maxX = arr[ i ];
        }
    }
    return maxX;
}

float Rectangle::getYmax() const {

    float arr[4] = {p1_.getY(), p2_.getY(), p3_.getY(), p4_.getY()};
    float maxY = p1_.getY();
    for (int i = 0; i < 4; i++) {
        if (arr[ i ] > maxY) {
            maxY = arr[ i ];
        }
    }
    return maxY;
}

// Overrides

void Rectangle::translate(float x, float y) {

    Point *arr[4] = {&p1_, &p2_, &p3_, &p4_};
    for (int i = 0; i < 4; i++) {
        arr[ i ]->setX(arr[ i ]->getX() + x);
        arr[ i ]->setY(arr[ i ]->getY() + y);
    }
}

void Rectangle::rotate() {
    // The same as Line Segments

    float x1 = p1_.getX();
    float y1 = p1_.getY();
    float x2 = p2_.getX();
    float y2 = p2_.getY();


    // Finds The center to rotate around
    float center_x = (x1 + x2) / 2;
    float center_y = (y1 + y2) / 2;

    // Moves the Rectangle to the center
    x1 -= center_x;
    x2 -= center_x;
    y1 -= center_y;
    y2 -= center_y;

    //Rotates Both Points
    float xtemp = x1;
    float ytemp = y1;
    x1 = -ytemp;
    y1 = xtemp;

    xtemp = x2;
    ytemp = y2;
    x2 = -ytemp;
    y2 = xtemp;

    //Moves the Rectangle to the original position
    x1 += center_x;
    x2 += center_x;
    y1 += center_y;
    y2 += center_y;

    //Setting new values
    p1_.setX(x1);
    p1_.setY(y1);
    p2_.setX(x2);
    p2_.setY(y2);
    p3_.setX(x2);
    p3_.setY(y1);
    p4_.setX(x1);
    p4_.setY(y2);
}

bool Rectangle::contains(const Point &p) const {
    if (((getXmin() <= p.getX()) && (p.getX() <= getXmax()))
        && ((getYmin() <= p.getY()) && (p.getY() <= getYmax()))) {
        return true;
    } else {
        return false;
    }
}

void Rectangle::scale(float f) {
    if (f <= 0) {
        throw std::invalid_argument("Scaling factor cannot be zero or negative");
    }
    // Getting X and Y coordinates of points
    float x1 = p1_.getX();
    float y1 = p1_.getY();
    float x2 = p2_.getX();
    float y2 = p2_.getY();

    // Finds The center to rotate around
    float center_x = (x1 + x2) / 2;
    float center_y = (y1 + y2) / 2;

    // Moves the Rectangle to the center
    x1 -= center_x;
    x2 -= center_x;
    y1 -= center_y;
    y2 -= center_y;

    // Applies scaling to both points
    x1 *= f;
    x2 *= f;
    y1 *= f;
    y2 *= f;

    //Moves the Rectangle to the original position
    x1 += center_x;
    x2 += center_x;
    y1 += center_y;
    y2 += center_y;

    //Setting new values
    p1_.setX(x1);
    p1_.setY(y1);
    p2_.setX(x2);
    p2_.setY(y2);
    p3_.setX(x2);
    p3_.setY(y1);
    p4_.setX(x1);
    p4_.setY(y2);

}

float Rectangle::area() const {
    return (getXmax() - getXmin()) * (getYmax() - getYmin());
}

// ================== Circle class ===================

Circle::Circle(const Point &c, float r) : TwoDShape(c.getDepth()) {

    if (r <= 0) {
        throw std::invalid_argument("Radius cannot be <= 0");
    } else
        p1_ = Point(c.getX(), c.getY(), c.getDepth());
    r_ = r;
    depth_ = c.getDepth();
    dimension_ = 2;

}

float Circle::getX() const {

    return p1_.getX();
}

float Circle::getY() const {

    return p1_.getY();
}

float Circle::getR() const {

    return r_;
}

void Circle::setR(float r) {
    r_ = r;
}

void Circle::translate(float x, float y) {
    p1_.setX(p1_.getX() + x);
    p1_.setY(p1_.getY() + y);
}

void Circle::scale(float f) {
    if (f <= 0) {
        throw std::invalid_argument("Scaling factor cannot be zero or negative");
    } else
        setR((float) (r_ * f));
}

void Circle::rotate() {
    // Circle rotating changes nothing
}

bool Circle::contains(const Point &p) const {
    if ((float) (pow((p.getX() - p1_.getX()), 2) + pow((p.getY() - p1_.getY()), 2)) <= (float) (pow(r_, 2))) {
        return true;
    } else
        return false;
}

float Circle::area() const {
    return PI * pow(r_, 2);
}

// ================= Scene class ===================

Scene::Scene() {
    // Setting initial depth to maximum Integer value in an unlikely scenario where depth is absurdly large
    drawingDepth_ = INT_MAX;
}

void Scene::addObject(std::shared_ptr<Shape> ptr) {

    shapeVector_.push_back(ptr);
}

void Scene::setDrawDepth(int depth) {

    drawingDepth_ = depth;
}

std::ostream &operator<<(std::ostream &out, const Scene &s) {

    // Draws a blank sheet
    char symbol = '*';
    bool pointExists = false;
    // Set as negatives on purpose to not overlap with existing points on the plane
    int lastX = -1;
    int lastY = -1;
    for (int h = s.HEIGHT - 1; h >= 0; h--) {
        for (int w = 0; w < s.WIDTH; w++) {
            // If shapeVector is not empty it iterates over the given points and checks if they are in the plane of the coordinates
            if (!s.shapeVector_.empty()) {
                for (auto it = std::begin(s.shapeVector_); it != std::end(s.shapeVector_); ++it) {
                    if (it->get()->contains(Point(w, h)) && ((lastX != w) || (lastY != h)) &&
                        it->get()->getDepth() <= s.drawingDepth_) {
                        //Remembers the Last Y and X coordinates to avoid spaces/clashes when one or both points exists or another doesn't
                        lastX = w;
                        lastY = h;
                        out.put(symbol);
                        pointExists = true;
                    } else {
                        pointExists = false;
                    }
                }
                if (!pointExists && ((lastX != w) || (lastY != h))) {
                    out.put(' ');
                }
            } else { out.put(' '); }
        }
        if (h != s.HEIGHT)
            out.put('\n');
    }

    return out;
}

