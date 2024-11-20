#include <iostream>
#include <vector>
#include "graphics.hpp"

std::vector<GraphicalObject*> createGraphicalObjects(
    int theSize)
{
    std::vector<GraphicalObject*> graphicalObjects(theSize);
    for(int i=0; i < theSize; i++)
    {
       graphicalObjects[i] = new Line();
       graphicalObjects[++i] = new Circle();
    }
    return graphicalObjects;
}

void drawGraphicalObjects(std::vector<GraphicalObject*>& theGraphicalObjects)
{
    for(auto it = theGraphicalObjects.begin(); 
        it < theGraphicalObjects.end(); it++)
    {
       (*it)->draw();
    }
}

void deleteGraphicalObjects(std::vector<GraphicalObject*>& theGraphicalObjects)
{
    for(auto it = theGraphicalObjects.begin(); 
        it < theGraphicalObjects.end(); it++)
    {
       delete *it;
    }
}

int main()
{
    auto graphicalObjects = createGraphicalObjects(10);
    drawGraphicalObjects(graphicalObjects);
    deleteGraphicalObjects(graphicalObjects);

    return 0;
}