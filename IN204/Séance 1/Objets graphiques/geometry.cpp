#include <iostream>
#include "geometry.hpp"

void Point::print() const{
    std::cout << "(" << m_x << "," << m_y << ")" << std::endl;
}

bool Segment::contain_point(Point point) const
{
    // Test d'alignement
    float a1 = (float)(extremite2.m_y-extremite1.m_y)/(float)(extremite2.m_x-extremite1.m_x);
    float a2 = (float)(extremite2.m_y-point.m_y)/(float)(extremite2.m_x-point.m_x);
    
    if(a2 != a1){
        return false;
    }

    // Test si coordonnées de point entre celle des extremités
    if(std::min(extremite1.m_x,extremite2.m_x) <= point.m_x && point.m_x <= std::max(extremite1.m_x,extremite2.m_x)
    && std::min(extremite1.m_y,extremite2.m_y) <= point.m_y && point.m_y <= std::max(extremite1.m_y,extremite2.m_y)){
        return true;
    }

    return false;
}

bool Segment::intersect_seg(Segment segment, Point* point_intersect) const{
    Droite droite_from_segment = Droite(segment);
    
    if(!droite_from_segment.intersect_segment(*this, point_intersect)){
        return false;
    }
    
    if(!this->contain_point(*point_intersect)){
        return false;
    }

    return true;
}

void Segment::print() const{
    std::cout << "(" << extremite1.m_x << "," << extremite1.m_y << ") - (" << extremite2.m_x << "," << extremite2.m_y << ")" << std::endl;
}

bool Droite::intersect_droite(Droite droite, Point* point_intersect) const{
    if(this->m_vect_dir.m_coord_x*droite.m_vect_dir.m_coord_y == this->m_vect_dir.m_coord_y*droite.m_vect_dir.m_coord_x){
        return false;
    }

    /* 
    On représente les droites par leurs équations cartésiennes
    y + ax + b = 0
    y + cx + d = 0
    */
    float a = -this->m_vect_dir.m_coord_y/this->m_vect_dir.m_coord_x;
    float c = -droite.m_vect_dir.m_coord_y/droite.m_vect_dir.m_coord_x;
    float b = -a*this->m_point.m_x - this->m_point.m_y;
    float d = -c*droite.m_point.m_x - droite.m_point.m_y;

    point_intersect->m_x = (d-b)/(a-c);
    point_intersect->m_y = (b*c - a*d)/(a-c);
    return true;
}

bool Droite::intersect_segment(Segment segment, Point* point_intersect) const{
    Droite droite_from_seg = Droite(segment);
    if(!this->intersect_droite(droite_from_seg, point_intersect)){
        return false;
    }

    if(!segment.contain_point(*point_intersect)){
        return false;
    }

    return true;
}

void Droite::rotate90(){
    float temp = m_vect_dir.m_coord_x;
    m_vect_dir.m_coord_x = -m_vect_dir.m_coord_y;
    m_vect_dir.m_coord_y = temp;
}

void Droite::move(int x, int y){
    m_point.m_x += x;
    m_point.m_y += y;
}


void Droite::print() const{
    std::cout << "(" << m_point.m_x << "," << m_point.m_y << ") -> (" << m_vect_dir.m_coord_x << "," << m_vect_dir.m_coord_y << ")" << std::endl;
}