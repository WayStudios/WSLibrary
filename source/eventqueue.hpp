/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef EVENTQUEUE_HEADER
#define	EVENTQUEUE_HEADER

#include <global.hpp>
#include <eventelement.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

class EXPORT EventQueue {
    DECLARE_IMPLEMENTATION(EventQueue)
public:
    typedef EventElement VALUE;

    EventQueue();
    EventQueue(const EventQueue&);
    ~EventQueue();

    size Total() const;
    boolean Empty() const;
    void Clear();
    void Destroy();

    void Append(Event*, Object*, Object*);
    void Append(const EventElement&);
    void Pop();

    const EventElement& Top() const;

    EventQueue& operator=(const EventQueue&);
};

END_WS_NAMESPACE

END_HEADER

#endif
