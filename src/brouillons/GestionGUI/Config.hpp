#ifndef __CONFIG_HPP__
#define __CONFIG_HPP__

#include <irrXML.h>
#include <irrlicht.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace irr; // irrXML is located in the namespace irr::io
using namespace video;
using namespace io;
using namespace std;
        
#define method(class, name) {#name, &class::name}

class Config
{
    private:

        static const char className[];
              
        bool bCharge;
        std::string cCheminFichier;
        IrrXMLReader* xml;
        
    public:

        bool antialiazing;
        bool fullscreen;
        bool musicAndFX;
        bool realTimeShadows;
        bool verticalSynch;
        bool oldHWBlending;
        E_DRIVER_TYPE driver;
        int width;
        int height;
        
        Config(std::string _cCheminFichier = "")
            :cCheminFichier(_cCheminFichier), bCharge(false), xml(NULL)
        {
            vNettoyer();
        }
        
        ~Config()
        {}
        
        bool bSauver(std::string _cCheminFichier = "")
        {
            ofstream myfile;
            if(_cCheminFichier == "")
            {
                _cCheminFichier = cCheminFichier;
            }
            
            if(_cCheminFichier == "")
            {
                return false;
            }
            
            myfile.open(_cCheminFichier.c_str());

            if(!myfile.is_open())
            {
                return false;
            }
                 
            myfile << "<?xml version=\"1.0\"?>" << endl;
            myfile << "<config>" << endl;
            myfile << " <!-- Parametrage d'application irrlicht -->" << endl;
            myfile << "<antialiazing value=\"" << (antialiazing?"ON":"OFF") << "\" />" << endl;
            myfile << "<fullscreen value=\"" << (fullscreen?"ON":"OFF") << "\" />" << endl;
            myfile << "<musicAndFX value=\"" << (musicAndFX?"ON":"OFF") << "\" />" << endl;
            myfile << "<realTimeShadows value=\"" << (realTimeShadows?"ON":"OFF") << "\" />" << endl;
            myfile << "<verticalSynch value=\"" << (verticalSynch?"ON":"OFF") << "\" />" << endl;
            myfile << "<oldHWBlending value=\"" << (oldHWBlending?"ON":"OFF") << "\" />" << endl;
            myfile << "<driver value=\"" << driver << "\" />" << endl;
            myfile << "<windowSize width=\"" << width << "\" height=\"" << height << "\" />" << endl;
            myfile << "</config>" << endl;
            myfile.close();
            
            return true;
        }
        bool bCharger(std::string _cCheminFichier = "")
        {
            bool bRetour = false;
            if(_cCheminFichier != "")
            {
                cCheminFichier = _cCheminFichier;
            }
            
            if(cCheminFichier != "")
            {
                if (bCharge == true)
                {
                    vNettoyer();
                }
                
                xml = createIrrXMLReader(cCheminFichier.c_str());
                
                while(xml && xml->read())
                {
                        switch(xml->getNodeType())
                        {
                            case EXN_TEXT:
                                /*if(strcmp("messageText", xml->getNodeName()))
                                {
                                    messageText = xml->getNodeData();
                                }*/
                                break;
                            case EXN_ELEMENT:
                                {
                                        if (!strcmp("antialiazing", xml->getNodeName()))
                                                antialiazing = (!strcmp(xml->getAttributeValue("value"),"ON")?true:false);
                                        else
                                        if (!strcmp("fullscreen", xml->getNodeName()))
                                                fullscreen = (!strcmp(xml->getAttributeValue("value"),"ON")?true:false);
                                        else
                                        if (!strcmp("musicAndFX", xml->getNodeName()))
                                                musicAndFX = (!strcmp(xml->getAttributeValue("value"),"ON")?true:false);
                                        else
                                        if (!strcmp("realTimeShadows", xml->getNodeName()))
                                                realTimeShadows = (!strcmp(xml->getAttributeValue("value"),"ON")?true:false);
                                        else
                                        if (!strcmp("verticalSynch", xml->getNodeName()))
                                                verticalSynch = (!strcmp(xml->getAttributeValue("value"),"ON")?true:false);
                                        else
                                        if (!strcmp("oldHWBlending", xml->getNodeName()))
                                                oldHWBlending = (!strcmp(xml->getAttributeValue("value"),"ON")?true:false);
                                        else
                                        if (!strcmp("driver", xml->getNodeName()))
                                                driver = (E_DRIVER_TYPE)atoi(xml->getAttributeValue("value"));
                                        else
                                        if (!strcmp("windowSize", xml->getNodeName()))
                                        {
                                                width = atoi(xml->getAttributeValue("width"));
                                                height = atoi(xml->getAttributeValue("height"));
                                        }
                                }
                                break;
                        }
                }

                // delete the xml parser after usage
                delete xml;
                xml = NULL;
                bCharge = true;
            }
            
            return bRetour;
        }
        
        void vNettoyer()
        {
            bCharge = false;
            
            antialiazing = false;
            fullscreen = false;
            width = 640;
            height = 480;
            musicAndFX = false;
            realTimeShadows = false;
            verticalSynch = false;
            oldHWBlending = false;
            driver = EDT_SOFTWARE;
            //messageText = "";
        }
        
        void vAfficher()
        {
            //cout << messageText << endl;
            cout << "antialiazing : " << (antialiazing?"ON":"OFF") <<endl;
            cout << "Fullscreen : " << (fullscreen?"ON":"OFF") <<endl;
            cout << "windowSize : " << width << "x" << height << endl;
            cout << "Music and Fx : " << (musicAndFX?"ON":"OFF") <<endl;
            cout << "Real Time Shadows : " << (realTimeShadows?"ON":"OFF") <<endl;
            cout << "Vertical Synch : " << (verticalSynch?"ON":"OFF") <<endl;
            cout << "Old HW Blending : " << (oldHWBlending?"ON":"OFF") <<endl;
            cout << "Renderer : " << sGetDriver() <<endl;
            return;
        }
        
        std::string sGetDriver()
        {
            switch(driver)
            {
                case EDT_OPENGL:
                    return std::string("OpenGL");
                case EDT_NULL:
                    return std::string("Null");
                case EDT_SOFTWARE:
                    return std::string("Software");
                case EDT_BURNINGSVIDEO:
                    return std::string("Burnings Video");
                case EDT_DIRECT3D8:
                    return std::string("Direct3d 8");
                case EDT_DIRECT3D9:
                    return std::string("Direct3d 9");
                case EDT_COUNT:
                    return std::string("Count");
            }
            return "";
        }
};

#endif
