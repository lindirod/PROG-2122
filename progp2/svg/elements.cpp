#include "elements.hpp"

#include <utility>

namespace svg {
    ellipse::ellipse(const svg::color &fill,
                     const point &center,
                     const point &radius) :
            shape(fill), center(center), radius(radius) { }

    circle::circle(const color &fill, const point &center, const point &radius) : ellipse(fill, center, radius) { }

    polyline::polyline(const svg::color &stroke, std::vector<point>  points) : shape(stroke), points(std::move(points)) { }

    line::line(const svg::color &stroke, const std::vector<point> &points) : polyline(stroke,points) { }

    polygon::polygon(const color &fill, std::vector<point>  points) : shape(fill), points(std::move(points)){ }

    rect::rect(const svg::color &fill, const std::vector<point> &points) : polygon(fill,points){}

    group::group(const svg::color &fill, std::vector<shape*> shapes) : shape(fill), shapes(std::move(shapes)) { }


    shape *circle::duplicate() const {
        return ellipse::duplicate();
    }


    void ellipse::draw(png_image &img) const {
        img.draw_ellipse(center, radius, get_color());
    }


    void ellipse::translate(const point &t) {
        center = center.translate(t);
    }

    void ellipse::scale(const point &origin, int v) {
        radius.x *= v;
        radius.y *= v;
        center = center.scale(origin,v);
    }

    void ellipse::rotate(const point &origin, int degrees) {
        center = center.rotate(origin, degrees);
    }



    shape *ellipse::duplicate() const {
        return new ellipse(get_color(), center, radius);
    }

    void polyline::draw(png_image &img) const {
        for (int x = 0; x < points.size() - 1; x++){
            img.draw_line(points.at(x), points.at(x + 1), get_color());
        }
    }

    void polyline::translate(const point &t) {
        for (auto &point: points){
            point = point.translate(t);
        }
    }

    void polyline::scale(const point &origin, int v) {
        for (auto &point: points) {
        point = point.scale(origin, v);
        }
    }

    void polyline::rotate(const point &origin, int v) {
        for(auto & point : points) {
            point = point.rotate(origin, v);
        }
    }


    shape *polyline::duplicate() const{
        return new polyline(get_color(),points);
    }



    shape *line::duplicate() const{
        return new line(get_color(),points);
    }

    void polygon::draw(png_image &img) const {
        img.draw_polygon(points,get_color());
    }

    void polygon::translate(const point &t) {
        for (auto &point: points){
            point = point.translate(t);
        }
    }

    void polygon::scale(const point &origin, int v) {
        for (auto &point: points){
            point = point.scale(origin, v);
        }
    }

    void polygon::rotate(const point &origin, int v) {
        for(auto & point : points) {
            point = point.rotate(origin, v);
        }
    }

    shape *polygon::duplicate() const {
        return new polygon(get_color(), points);
    }



    shape *rect::duplicate() const{
        return new polyline(get_color(), points);
    }



    group::~group() noexcept{
        for(auto s : shapes) {
            delete s;
        }
    }

    void group::draw(png_image &img) const {
        for(auto shape : shapes){
            shape->draw(img);
        }
    }

    void group::translate(const point &t) {
     for(auto & shape : shapes){
         shape->translate(t);
     }
    }

    void group::scale(const point &origin, int v) {
        for(auto & shape : shapes){
            shape->scale(origin,v);
        }
    }

    void group::rotate(const point &origin, int v) {
        for(auto & shape : shapes){
            shape->rotate(origin,v);
        }
    }

    shape *group::duplicate() const {
        std::vector<shape*> shapes2;
        for(auto &shape : shapes){
            shapes2.push_back(shape->duplicate());
        }
        return new group(get_color(),shapes);
    }

}
