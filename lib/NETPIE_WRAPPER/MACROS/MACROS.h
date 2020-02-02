#ifndef MACROS_H
#define MACROS_H
#include <Arduino.h>

class MACROS
{
private:
    /* data */
    boolean isShow;

public:
    MACROS(boolean show = true);
    ~MACROS();

    template <typename P>
    void Sprintln(P payload)
    {
        if (isShow)
        {
            Serial.println(payload);
        }
    }

    template <typename P>
    void Sprint(P payload)
    {
        if (isShow)
        {
            Serial.print(payload);
        }
    }
};

MACROS::MACROS(boolean show)
{
    this->isShow = show;
}

MACROS::~MACROS()
{
}

#endif