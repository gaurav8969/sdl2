#ifndef SYSTEM_HPP
#define SYSTEM_HPP

struct System{
public:
    virtual ~System()= default;

    virtual void init();
    virtual void update();

};

#endif