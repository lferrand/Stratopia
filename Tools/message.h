#ifndef MESSAGE_H
#define MESSAGE_H

#include "renderableobject.h"

class Message
{
    public:
        Message();
        Message(std::string content,RenderableObject* sender,RenderableObject* target);
        virtual ~Message();
        std::string content;
        RenderableObject* sender;
        RenderableObject* target;
    protected:
    private:
};

#endif // MESSAGE_H
