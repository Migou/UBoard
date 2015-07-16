#ifndef __MYEVENTRECEIVER_HPP__
#define __MYEVENTRECEIVER_HPP__
#include <iostream>
#include <vector>
#include <iomanip>
#include "Timer.hpp"
#include "BaseGUI.hpp"

using namespace std;
using namespace gui;

// Define some values that we'll use to identify individual GUI controls.
enum
{
    GUI_ID_QUIT_BUTTON = 101,
    GUI_ID_NEW_WINDOW_BUTTON,
    GUI_ID_FILE_OPEN_BUTTON,
    GUI_ID_TRANSPARENCY_SCROLL_BAR
};

struct stKeyState
{
	bool KeyIsDown[KEY_KEY_CODES_COUNT];
	bool KeyIsPressed[KEY_KEY_CODES_COUNT];
	bool KeyIsReleased[KEY_KEY_CODES_COUNT];
	//KeyIsUp[n] == !KeyIsDown[n]
};

struct stKeyEvent
{
	wchar_t Char;
	EKEY_CODE Key;
	bool PressedDown:1;
	bool Shift:1;
	bool Control:1;
	u32 time;
};

struct stMouseState
{
	s32 X;
	s32 Y;
	bool ButtonLeftIsDown;
	bool ButtonLeftIsPressed;
	bool ButtonLeftIsReleased;
	bool ButtonMiddleIsDown;
	bool ButtonMiddleIsPressed;
	bool ButtonMiddleIsReleased;
	bool ButtonRightIsDown;
	bool ButtonRightIsPressed;
	bool ButtonRightIsReleased;
};

struct stMouseEvent
{
	s32 X;
	s32 Y;
	f32 Wheel;
 	bool Shift:1;
	bool Control:1;
	bool ButtonIsPressed[3];
	bool ButtonIsReleased[3];
	u32 time;
};

class MyEventReceiver : public IEventReceiver
{

	private:

	stKeyState keyState;
	vector<stKeyEvent> keyEventList;
	stMouseState mouseState;
	Timer * timer; // timer pour noter la date des inputs
	
	public:
	SAppContext context; 
	
	vector<BaseGUI*> GUIList;
	
	MyEventReceiver(Timer * _timer): timer(_timer)
	{
		init();
	}

	void setTimer(Timer* _timer)
	{
		timer = _timer;
	}

	void init()
	{
		for(int i = 0; i < KEY_KEY_CODES_COUNT; ++i)
		{
			keyState.KeyIsDown[i] = false;
			keyState.KeyIsPressed[i] = false;
			keyState.KeyIsReleased[i] = false;
		}
	}

	// This is the one method that we have to implement
	virtual bool OnEvent(const SEvent& event)
	{
		s32 id;
		IGUIEnvironment* env=NULL;
		// Remember whether each key is down or up
		switch (event.EventType)
		{
			case irr::EET_KEY_INPUT_EVENT :
			keyState.KeyIsPressed[event.KeyInput.Key] = false;
			keyState.KeyIsReleased[event.KeyInput.Key] = false;
			if(event.KeyInput.PressedDown)
			{
				if(!keyState.KeyIsDown[event.KeyInput.Key])
				{
					keyState.KeyIsPressed[event.KeyInput.Key] = true;
					//cout << "press" << endl;

					stKeyEvent keyEvent;
					keyEvent.Char = event.KeyInput.Char;
					keyEvent.Key = event.KeyInput.Key;
					keyEvent.PressedDown = true;
					keyEvent.Shift = event.KeyInput.Shift;
					keyEvent.Control = event.KeyInput.Control;
					keyEvent.time = timer->getTime();
					keyEventList.push_back(keyEvent);
				}
			}
			else
			{
				if(keyState.KeyIsDown[event.KeyInput.Key])
				{
					keyState.KeyIsReleased[event.KeyInput.Key] = true;
					//cout << "release" << endl;

					stKeyEvent keyEvent;
					keyEvent.Char = event.KeyInput.Char;
					keyEvent.Key = event.KeyInput.Key;
					keyEvent.PressedDown = false;
					keyEvent.Shift = event.KeyInput.Shift;
					keyEvent.Control = event.KeyInput.Control;
					keyEvent.time = timer->getTime();
					keyEventList.push_back(keyEvent);
				}
			}

			keyState.KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
			
			break;

			case irr::EET_MOUSE_INPUT_EVENT :
				
				mouseState.X = event.MouseInput.X;
				mouseState.Y = event.MouseInput.Y;

				mouseState.ButtonLeftIsPressed = false;
				mouseState.ButtonMiddleIsPressed = false;
				mouseState.ButtonRightIsPressed = false;
				mouseState.ButtonLeftIsReleased = false;
				mouseState.ButtonMiddleIsReleased = false;
				mouseState.ButtonRightIsReleased = false;

				switch (event.MouseInput.Event)
				{
					case EMIE_LMOUSE_PRESSED_DOWN :
						if(!mouseState.ButtonLeftIsDown) mouseState.ButtonLeftIsPressed = true;
						mouseState.ButtonLeftIsDown = true;
						
					break;
					case EMIE_RMOUSE_PRESSED_DOWN :
						if(!mouseState.ButtonRightIsDown) mouseState.ButtonRightIsPressed = true;
						mouseState.ButtonRightIsDown = true;
					break;
                  	case EMIE_MMOUSE_PRESSED_DOWN :
						if(!mouseState.ButtonMiddleIsDown) mouseState.ButtonMiddleIsPressed = true;
						mouseState.ButtonMiddleIsDown = true;
					break;
                  	case EMIE_LMOUSE_LEFT_UP      :
						if(mouseState.ButtonLeftIsDown) mouseState.ButtonLeftIsReleased = true;
						mouseState.ButtonLeftIsDown = false;
					break;
                  	case EMIE_RMOUSE_LEFT_UP      :
						if(mouseState.ButtonRightIsDown) mouseState.ButtonRightIsReleased = true;
						mouseState.ButtonRightIsDown = false;
					break;
                  	case EMIE_MMOUSE_LEFT_UP      :
						if(mouseState.ButtonMiddleIsDown) mouseState.ButtonMiddleIsReleased = true;
						mouseState.ButtonMiddleIsDown = false;
					break;
                  	case EMIE_MOUSE_MOVED         :
					//TODO
					break;
                  	case EMIE_MOUSE_WHEEL         :
					//TODO
					break;
				}

			break;
			case EET_GUI_EVENT :
			
				id = event.GUIEvent.Caller->getID();
				env = context.device->getGUIEnvironment();
				
				for(int i=0;i<GUIList.size();++i)
				{
					if(GUIList[i]->handleGUIEvent(event))
					{
						break;
					}
				}

			break;
			
			default:
			break;
		}
		
		return false;
	}
	
	// This is used to check whether a key is being held down
	virtual bool IsKeyDown(EKEY_CODE keyCode) const
	{
		return keyState.KeyIsDown[keyCode];
	}

	virtual bool IsKeyUp(EKEY_CODE keyCode) const
	{
		return !keyState.KeyIsDown[keyCode];
	}

	virtual bool IsKeyPressed(EKEY_CODE keyCode)
	{
		bool ret = keyState.KeyIsPressed[keyCode];
		keyState.KeyIsPressed[keyCode] = false;
		return ret;
	}

	virtual bool IsKeyReleased(EKEY_CODE keyCode)
	{
		bool ret = keyState.KeyIsReleased[keyCode];
		keyState.KeyIsReleased[keyCode] = false;
		return ret;
	}

	virtual bool IsMouseLeftButtonDown()
	{
		return mouseState.ButtonLeftIsDown;
	}

	virtual bool IsMouseLeftButtonPressed()
	{
		bool ret = mouseState.ButtonLeftIsPressed;
		mouseState.ButtonLeftIsPressed = false;
		return ret;
	}
	virtual bool IsMouseLeftButtonReleased()
	{
		bool ret = mouseState.ButtonLeftIsReleased;
		mouseState.ButtonLeftIsReleased = false;
		return ret;
	}

	virtual bool IsMouseRightButtonDown()
	{
		return mouseState.ButtonRightIsDown;
	}

	virtual bool IsMouseRightButtonPressed()
	{
		bool ret = mouseState.ButtonRightIsPressed;
		mouseState.ButtonRightIsPressed = false;
		return ret;
	}
	virtual bool IsMouseRightButtonReleased()
	{
		bool ret = mouseState.ButtonRightIsReleased;
		mouseState.ButtonRightIsReleased = false;
		return ret;
	}

	virtual bool IsMouseMiddleButtonDown()
	{
		return mouseState.ButtonMiddleIsDown;
	}

	virtual bool IsMouseMiddleButtonPressed()
	{
		bool ret = mouseState.ButtonMiddleIsPressed;
		mouseState.ButtonMiddleIsPressed = false;
		return ret;
	}
	virtual bool IsMouseMiddleButtonReleased()
	{
		bool ret = mouseState.ButtonMiddleIsReleased;
		mouseState.ButtonMiddleIsReleased = false;
		return ret;
	}
	virtual s32 getMouseX()
	{
		return mouseState.X;
	}

	virtual s32 getMouseY()
	{
		return mouseState.Y;
	}

	friend std::ostream &operator << (std::ostream &out, const MyEventReceiver &receiver);

};


ostream & operator<<(std::ostream &out, const MyEventReceiver &receiver)
{
    
	for (int i = 0; 
		i < receiver.keyEventList.size(); ++i)
	{
		out << setw(5) << receiver.keyEventList[i].time << ":";
    	out << setw(5) << (char)(receiver.keyEventList[i].Char);
		out << setw(5) << receiver.keyEventList[i].Char;
		out << setw(5) << receiver.keyEventList[i].Key;
		out << setw(5) << receiver.keyEventList[i].PressedDown;
		out << setw(5) << receiver.keyEventList[i].Shift;
		out << setw(5) << receiver.keyEventList[i].Control;
		out << endl;
	}
    
    return out;
}
#endif
