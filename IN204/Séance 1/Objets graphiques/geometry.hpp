#include <math.h>

class Point
{
    public:
        int m_x;
        int m_y;

        Point(): m_x(0), m_y(0)
        {}

        Point(int abscisse, int ordonnee): m_x(abscisse), m_y(ordonnee)
        {}

        void print() const;
    
};

class Segment
{
    public:
        Point extremite1;
        Point extremite2;

        Segment(Point depart, Point arrivee): extremite1(depart), extremite2(arrivee)
        {}

        bool contain_point(Point point) const;

        bool intersect_seg(Segment segment, Point* point_intersect) const;

        void print() const;
};

class Vecteur
{
    public:
        float m_coord_x;
        float m_coord_y;

        Vecteur(float coord_x, float coord_y): m_coord_x(coord_x), m_coord_y(coord_y)
        {}
};

class Droite
{
    public: 
        Point m_point;
        Vecteur m_vect_dir;
    
        Droite(Segment seg): m_point(seg.extremite1), m_vect_dir{(float)(seg.extremite2.m_x-seg.extremite1.m_x), (float)(seg.extremite2.m_y - seg.extremite1.m_y)}
        {}

        Droite(Point point, float angle): m_point(point), m_vect_dir{1, atan(angle)}
        {}

        Droite(Point point1, Point point2): m_point(point1), m_vect_dir{(float)(point2.m_x-point1.m_x), (float)(point2.m_y - point1.m_y)}
        {}

        bool intersect_droite(Droite droite, Point* point_intersect) const;

        bool intersect_segment(Segment segment, Point* point_intersect) const;

        void rotate90();

        void move(int x, int y);

        void print() const;
};