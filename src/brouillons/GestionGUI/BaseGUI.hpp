#ifndef __BASEGUI_HPP__
#define __BASEGUI_HPP__
#include <iostream>
#include <vector>
#include <iomanip>
#include "Timer.hpp"
using namespace std;
using namespace gui;
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;

// Declare a structure to hold some context for the event receiver so that it
// has it available inside its OnEvent() method.
struct SAppContext
{
    IrrlichtDevice *device;
    s32             counter;
};

/**
	Classe de base décrivant une interface graphique.
	C'est au développeur qui implémente la classe d'ajouter autant de membres qu'il y a de IGUIElement sur l'interface,
	d'ajouter les traitements nécessaire à leur initialisation dans init()
	et d'écrire la fonction handleEvent() pour décrire les traitements associé à chaque événement de chaque élément.
*/
class BaseGUI
{
	public:
	static int nextID;
	
	SAppContext context;
	
	/**
		@param _context Contexte Irrlicht
	*/
	BaseGUI(SAppContext _context):context(_context)
	{
	}
	/**
		L'implémentation du destructeur devra contenir les IGUIElement.remove()
	*/
	~BaseGUI()
	{
	}
	
	/**
		Retourne le prochain ID libre et incrémente le compteur
		@return valeur de l'ID généré
	*/
	static int useNextID()
	{
		nextID++;
		return nextID-1;
	}
	
	/**
		@return Valeur du dernier ID utilisé
	*/
	static int getCurrentID()
	{
		return nextID-1;
	}
	
	/**
		Traite l'événement passé en paramètre si l'élément fait partie de la GUI gérée par la classe
		@param event événement à traiter
		@return renvoi true si l'élément faisait partie de cette GUI, false sinon
	*/
	virtual bool handleGUIEvent(const SEvent& event)=0;
	
	/**
		change la visibilité de la GUI
		@param _visible true pour rendre la GUI visible, false pour la masquer
	*/
	virtual void setVisible(bool _visible)=0;
	
	/**
		Initialisation de la GUI : 
	*/
	virtual void init()=0;
};

int BaseGUI::nextID = 0;

/**
	Exemple d'implémentation de BaseGUI pour gérer un bouton quitter.
*/
class MyGUI : public BaseGUI
{
	public:
	
	IGUIButton* BT_quitter;		///< Bouton quitter
	IGUIStaticText* TXT_Hello;
	
	
	// Barre de Menu
	IGUIContextMenu * menuBar;
	
	s32 itemIDNewProject;
	s32 itemIDOpenProject;
	s32 itemIDCloseProject;
	s32 itemIDSave;
	s32 itemIDSaveAs;
	s32 itemIDExport;
	s32 itemIDQuit;
	
	s32 itemIDProjectProperties;
	
	MyGUI(SAppContext _context):BaseGUI(_context)
	{
		init();
	}
	
	~MyGUI()
	{
		// Retirer les widgets de l'environnement
		BT_quitter->remove();
		TXT_Hello->remove();
	}
	
	virtual bool handleGUIEvent(const SEvent& event)
	{
		bool found = false;
		
		{
			
			switch(event.GUIEvent.EventType)
			{
				case EGET_BUTTON_CLICKED:
					if(event.GUIEvent.Caller->getID() == BT_quitter->getID())
					{
						context.device->closeDevice();
						found = true;
					}

				break;
				case EGET_MENU_ITEM_SELECTED :
					IGUIContextMenu* menu = (gui::IGUIContextMenu*)event.GUIEvent.Caller;
					s32 id = menu->getItemCommandId(menu->getSelectedItem());
					
					if(id==itemIDQuit)
					{
						context.device->closeDevice();
						found = true;
					}
				break;
			}
		}

		
		return found;
	}
	
	virtual void setVisible(bool _visible)
	{
		BT_quitter->setVisible(_visible);
	}
	
	virtual void  init()
	{
		IGUIEnvironment* guienv = this->context.device->getGUIEnvironment();
		BT_quitter = guienv->addButton(rect<s32>(10,240,110,240 + 32), 0, useNextID(), L"Quit", L"Exits Program");
		TXT_Hello = guienv->addStaticText(L"Hello World!", rect<s32>(210,210,460,222), true);
		TXT_Hello->setDrawBorder(false);
		
		menuBar = guienv->addMenu();
        menuBar->addItem(L"Fichier", -1, true, true);

        gui::IGUIContextMenu* subMenuFile = menuBar->getSubMenu(0);
        subMenuFile->addItem(L"Nouveau Projet", useNextID());
		itemIDNewProject = getCurrentID();
        subMenuFile->addItem(L"Ouvrir un Projet", useNextID());
		itemIDOpenProject = getCurrentID();
        subMenuFile->addItem(L"Fermer le Projet", useNextID());
		itemIDCloseProject = getCurrentID();
		
        subMenuFile->addSeparator();
		
		subMenuFile->addItem(L"Enregistrer", useNextID());
		itemIDSave = getCurrentID();
        subMenuFile->addItem(L"Enregistrer Sous", useNextID());
		itemIDSaveAs = getCurrentID();
        subMenuFile->addItem(L"Exporter", useNextID());
		itemIDExport = getCurrentID();
		
		subMenuFile->addSeparator();
		
        subMenuFile->addItem(L"Quitter", useNextID());
		itemIDQuit = getCurrentID();
		
		menuBar->addItem(L"Projet", -1, true, true);

        gui::IGUIContextMenu* subMenuProject = menuBar->getSubMenu(1);
		subMenuProject->addItem(L"Propriétés du Projet", useNextID());
		itemIDProjectProperties = getCurrentID();
	}
};

#endif
