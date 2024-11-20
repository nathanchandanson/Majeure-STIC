#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

class GraphicalObject 
{
    public:       
       virtual void draw () const = 0 ; 
       virtual ~GraphicalObject() { std::cout << "& Delete GraphicalObject \n"; }
 
};
 
class Line: public GraphicalObject 
{
    public:
       virtual void draw () const { std::cout << "Line\n"; } ; 
       virtual ~Line() override { std::cout << "Delete Line\n"; }
 
};
 
class Circle: public GraphicalObject 
{
    public:
       virtual void draw() const { std::cout << "Circle\n"; } ; 
       virtual ~Circle() override { std::cout << "Delete Circle\n"; }
 
};

#endif