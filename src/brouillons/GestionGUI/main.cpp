#include <irrlicht.h>
#include <cstdlib>
#include <iostream>
#include <dirent.h>
#include<lua.hpp>
#include<lauxlib.h>
#include<lualib.h>

#include "config.hpp"
#include "Timer.hpp"
#include "MyEventReceiver.hpp"

using namespace std;
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

int main(int argc, char *argv[])
{
	Config *cfg = new Config("./config.xml");
    cfg->bCharger();
	
	MyEventReceiver receiver(NULL); // gestionnaire d'évennements
	
    IrrlichtDevice *device = createDevice(cfg->driver, 
    dimension2d<u32>(cfg->width, cfg->height), 16,
                           false, false, false, &receiver);

	if (!device) return 1;
		
	device->setWindowCaption(L"GDL");
	
	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();
	IGUIEnvironment* guienv = device->getGUIEnvironment();
	
	IGUISkin* skin = guienv->getSkin();
	IGUIFont* font = guienv->getFont("./media/fontcourier.bmp");
	if (font) skin->setFont(font);
    skin->setFont(guienv->getBuiltInFont(), EGDF_TOOLTIP);

	bool quitter = false;
	
	// Timer
	Timer * timer = NULL;
	timer = new Timer(device->getTimer());
    timer->setSpeed(1.0f);
    timer->start();
	receiver.setTimer(timer);
	
	// Store the appropriate data in a context structure.
    SAppContext context;
    context.device = device;
    context.counter = 0;
	
	receiver.context = context;
	
	MyGUI* myGUI = new MyGUI(context);
	receiver.GUIList.push_back(myGUI);
	
	// Boucle de jeu
	while(device->run() && !quitter)
	{
		// Gestion des inputs
		if(receiver.IsKeyPressed(irr::KEY_ESCAPE))
		{
			quitter = true;
		}
		
		// Affichage de la scène
		driver->beginScene(true, true, SColor(255,0,0,0));

		smgr->drawAll();
		guienv->drawAll();

		driver->endScene();
    }
	
	// Fermeture du programme
	device->closeDevice();
	device->drop();
	return 0;
}