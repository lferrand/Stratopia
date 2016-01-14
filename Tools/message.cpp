#include "message.h"

Message::Message(std::string _content,RenderableObject* _sender,RenderableObject* _target)
{
    content = _content;
    sender = _sender;
    target = _target;
}

Message::~Message()
{
    //dtor
}
