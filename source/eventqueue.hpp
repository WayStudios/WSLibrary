/*******************************************************************************
 * Way Studios Library
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
    typedef EventElement TYPE;

    EventQueue();
    EventQueue(const EventQueue&);
    ~EventQueue();

    SIZE total() const;
    BOOLEAN empty() const;
    void clear();
    void destroy();

    void append(Event*, Object*, Object*);
    void append(const EventElement&);
    void pop();

    const EventElement& top() const;

    EventQueue& operator=(const EventQueue&);
};

END_WS_NAMESPACE

END_HEADER

#endif
