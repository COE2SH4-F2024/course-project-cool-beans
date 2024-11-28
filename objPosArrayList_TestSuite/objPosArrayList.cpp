#include "objPosArrayList.h"
#include <stdexcept>

using namespace std;

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    arrayCapacity = ARRAY_MAX_CAP;
    aList = new objPos[arrayCapacity];  
    listSize = 0;
      
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

int objPosArrayList::getSize() const
{
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    if(listSize == arrayCapacity)
    {
        throw overflow_error("Array capacity exceeded.");
    }

    for(int i = listSize; i > 0; i--)
    {
        aList[i] = aList[i - 1];
    }

    aList[0] = thisPos;
    listSize++;
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if(listSize == arrayCapacity)
    {
        throw overflow_error("Array capacity exceeded.");
    }

    aList[listSize++] = thisPos;
}

void objPosArrayList::removeHead()
{
    if(listSize == 0)
    {
        throw underflow_error("Cannot remove from empty list.");
    }

    for(int i = 0; i < listSize - 1; i++)
    {
        aList[i] = aList[i + 1];
    }

    listSize--;
}

void objPosArrayList::removeTail()
{
    if(listSize == 0)
    {
        throw underflow_error("Cannot remove from empty list.");
    }

    listSize--;
}

objPos objPosArrayList::getHeadElement() const
{
    if(listSize == 0)
    {
        throw underflow_error("List is empty.");
    }

    return aList[0];
}

objPos objPosArrayList::getTailElement() const
{
    if(listSize == 0)
    {
        throw underflow_error("List is empty.");
    }

    return aList[listSize - 1];
}

objPos objPosArrayList::getElement(int index) const
{
    if(index < 0 || index >= arrayCapacity)
    {
        throw out_of_range("Index out of range.");
    }
    if(index >= listSize)
    {
        return objPos();
    }
   
    return aList[index];
}