#include <iostream>
#include "geometry.hpp"

int main()
{
    Point A = Point(0,0);
    Point B = Point(1,0);
    Point C = Point(2,0);
    Point D = Point(1,1);
    Point E = Point(0,1);
    
    // Test Segment::contain_point
    Segment AC = Segment(A,C);
    Segment AB = Segment(A,B);
    Segment BC = Segment(B,C);
    std::cout << AC.contain_point(B) << AC.contain_point(D) << AB.contain_point(C) << std::endl;

    // Test Droite::intersect_droite
    Droite droite1 = Droite(A, B);
    Droite droite2 = Droite(A, C);
    Droite droite3 = Droite(D, E);
    Droite droite4 = Droite(A, D);
    Point point1,point2;
    std::cout << droite1.intersect_droite(droite2, &point1) << droite1.intersect_droite(droite3, &point1) << droite1.intersect_droite(droite4, &point2) << std::endl;
    std::cout << point2.m_x << point2.m_y << std::endl;

    // Test Droite::intersect_segment
    std::cout << droite1.intersect_segment(AB, &point1) << droite4.intersect_segment(BC, &point2) << droite3.intersect_segment(AB, &point2) << droite4.intersect_segment(AB, &point2) << std::endl;

    // Test Segment::intersect_segment
    Segment ED = Segment(E,D);
    Segment AD = Segment(A,D);
    Segment DC = Segment(D,C);
    std::cout << AB.intersect_seg(ED, &point1) << AB.intersect_seg(AC, &point1) << AB.intersect_seg(AD, &point1) << AB.intersect_seg(DC, &point2) << std::endl;

    // Test de Droite::move et Droite::rotate90
    Droite d1(Point(0,0), Point(4, 2));
    Droite d2(d1);
    d1.print(); 
    d2.print();
    std::cout << std::endl;
    d1.rotate90();
    d1.print(); 
    d2.move(1,1);
    d2.print();

    return 0;
}