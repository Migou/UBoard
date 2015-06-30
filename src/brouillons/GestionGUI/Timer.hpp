#ifndef __TIMER_HPP__
#define __TIMER_HPP__

#include <irrlicht.h>

using namespace irr;
using namespace video;

class Timer : public ITimer
{
    private:
        f32 m_fSpeed;
        f32 m_fTime;
        f32 m_fDelta;
        bool m_bStopped;
        u32 m_iLastTickTime;
        
    public:
    ITimer * m_pDeviceTimer;
    
    Timer(ITimer* _pDeviceTimer);
    ~Timer();
    u32	getRealTime () const;
    f32 getSpeed () const;
    u32 getTime () const;
    f32 getDelta() const;
    bool isStopped () const;
    void setSpeed (f32 speed=1.0f);
    void setTime (u32 time);
    void start ();
    void stop ();
    void tick ();
	u32 getCurrentDeviceTime();
    
};

#endif
