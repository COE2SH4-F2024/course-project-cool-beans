#include "objPosArrayList.h"
#include <stdexcept>

using namespace std;

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

    // Decrease each index location to make room for head element
    for(int i = listSize; i > 0; i--)
    {
        aList[i] = aList[i - 1];
    }

    aList[0] = thisPos; // Insert head at index 0
    listSize++; // Increase list size
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if(listSize == arrayCapacity)
    {
        throw overflow_error("Array capacity exceeded.");
    }

    aList[listSize++] = thisPos; // Insert tail at listSize + 1
}

void objPosArrayList::removeHead()
{
    if(listSize == 0)
    {
        throw underflow_error("Cannot remove from empty list.");
    }

    // Increase each index location to replace head element
    for(int i = 0; i < listSize - 1; i++)
    {
        aList[i] = aList[i + 1];
    }

    listSize--; // Decrease list size
}

void objPosArrayList::removeTail()
{
    if(listSize == 0)
    {
        throw underflow_error("Cannot remove from empty list.");
    }

    listSize--; // Decrease list size to remove index and tail element
}

void objPosArrayList::removeElement(int index)
{
    if(listSize == 0)
    {
        throw underflow_error("Cannot remove from empty list.");
    }

    if(index < 0 || index >= arrayCapacity)
    {
        throw out_of_range("Index out of range.");
    }

    // Starting from target index, decrease each index location to remove element
    for (int i = index; i < listSize - 1; ++i) 
    {
        aList[i] = aList[i + 1];
    }

    listSize--; // Decrease list size
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