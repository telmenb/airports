#include "heap.hpp"

size_t heap::root() const
{
    return 1;
}

size_t heap::leftChild(size_t currentIdx) const
{
    return currentIdx * 2;
}

size_t heap::rightChild(size_t currentIdx) const
{
    return (currentIdx * 2) + 1;
}

size_t heap::parent(size_t currentIdx) const
{
    return currentIdx / 2;
}

bool heap::hasAChild(size_t currentIdx) const
{
    return leftChild(currentIdx) < _elems.size();
}

size_t heap::maxPriorityChild(size_t currentIdx) const
{
    if (leftChild(currentIdx) < _elems.size() && rightChild(currentIdx) < _elems.size()) {
        if (higherPriority(_elems.at(leftChild(currentIdx)), _elems.at(rightChild(currentIdx)))) {
            return leftChild(currentIdx);
        }
        return rightChild(currentIdx);

    }
    return leftChild(currentIdx);
}

void heap::heapifyDown(size_t currentIdx)
{
    if (!hasAChild(currentIdx))
        return;
    size_t prioChild = maxPriorityChild(currentIdx);
    if (higherPriority(_elems.at(prioChild), _elems.at(currentIdx))) {
        std::swap(_elems.at(currentIdx), _elems.at(prioChild));
        heapifyDown(prioChild);
    }
}

void heap::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

heap::heap() {
    _elems.push_back(NULL);
}

heap::heap(const std::vector<Airport*>& elems) 
{
    _elems.push_back(NULL);
    for (size_t i = 0; i < elems.size(); i++) {
        _elems.push_back(elems.at(i));
    }

    for (size_t i = parent(_elems.size() - 1); i > 0; i--) {
        heapifyDown(i);
    }
}

 Airport* heap::pop()
{
    Airport* priority = _elems.at(root());
    std::swap(_elems.at(root()), _elems.at(_elems.size() - 1));
    _elems.pop_back();
    heapifyDown(root());
    return priority;
}

Airport* heap::peek() const
{
    return _elems.at(root());
}

void heap::push(Airport* elem)
{
    _elems.push_back(elem);
    heapifyUp(_elems.size() - 1);
}

void heap::updateElem(const size_t & idx, Airport* elem)
{
    _elems.at(idx) = elem;
    if (higherPriority(_elems.at(idx), _elems.at(parent(idx)))) {
        heapifyUp(idx);

    }
    heapifyDown(idx);
}


bool heap::empty() const
{
    return _elems.size() == 1;
}

void heap::getElems(std::vector<Airport*> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);
    }
}