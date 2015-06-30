#include "Timer.hpp"
#include <iostream>
using namespace std;

Timer::Timer(ITimer* _pDeviceTimer)
    :m_pDeviceTimer(_pDeviceTimer), m_fTime(0.0f), m_fSpeed(1.0f), m_fDelta(0.0f)
        , m_bStopped(true), m_iLastTickTime(0)
{}

Timer::~Timer()
{}

u32	Timer::getRealTime () const
{
    return m_pDeviceTimer->getRealTime();
}

f32 Timer::getSpeed () const
{
    return m_fSpeed;
}

u32 Timer::getTime () const
{
    return (u32)m_fTime;
}

f32 Timer::getDelta() const
{
    return m_fDelta;
}

bool Timer::isStopped () const
{
    return m_bStopped;
}

void Timer::setSpeed (f32 speed)
{
    m_fSpeed = speed;
}

void Timer::setTime (u32 time)
{
    m_fTime = (f32)time;
    m_fDelta = 0.0f;
}

void Timer::start ()
{
    // Si le timer était bien en stop, on initialise l'instant précédent
    // à l'instant courrant
    if(m_bStopped)
    {
        m_iLastTickTime = m_pDeviceTimer->getRealTime();
        m_bStopped = false;
        cout << "In Start" << endl;
    }
}

void Timer::stop ()
{
    if(!m_bStopped)
    {
        // on fait un dernier tick avant de mettre le timer en pause
        // cela permet de repartir du bon pied au start
        tick();       
        m_bStopped = true;
        cout << "In Stop" << endl;
    }
    
}

u32 Timer::getCurrentDeviceTime()
{
	return m_pDeviceTimer->getRealTime();
}

void Timer::tick ()
{
    // Si le timer est en route, on le met à jour
    if(!m_bStopped)
    {
        u32 iCurrentDeviceTime = m_pDeviceTimer->getRealTime();
        m_fDelta = m_fSpeed * ( (f32)iCurrentDeviceTime - (f32)m_iLastTickTime);
        m_fTime += m_fDelta;
        m_iLastTickTime = iCurrentDeviceTime;
    }
}
