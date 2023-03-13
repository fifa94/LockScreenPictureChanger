#pragma once

#include <iostream>
#include "windows.h"
#include <string>

#define RegOpenKeyEx __AW_SUFFIXED__(RegOpenKeyEx)

namespace AuxiliaryFunctions {
    
    void RegOpenKeyEx(void);

    void RegOpenKeyEx(void){

        std::cout<< "NamespaceFunction";
    }
}


class RegistryPictureChange
{
private:
    HKEY* _hKey;
    LPCSTR _Path;
    DWORD _dwType, _dwSize;
public:
    RegistryPictureChange(HKEY* hKey, LPCSTR Path);
    ~RegistryPictureChange();
    long CheckRegistry(int ValueOfRegistry, LPCSTR NameOfRegistry);
};

// Constructor
RegistryPictureChange::RegistryPictureChange(HKEY* hKey, LPCSTR Path)
:_hKey(hKey), _Path(Path)
{
}

// Destructor
RegistryPictureChange::~RegistryPictureChange()
{
}

long RegistryPictureChange::CheckRegistry(int ValueOfRegistry, LPCSTR NameOfRegistry)
{
    long result;

    if (RegOpenKeyExA(HKEY_CURRENT_USER, _Path, 0, KEY_READ, _hKey) == ERROR_SUCCESS)
    {
       if (RegQueryValueExA(*_hKey, NameOfRegistry, NULL, &_dwType, (BYTE*)&ValueOfRegistry, &_dwSize) == ERROR_SUCCESS)
        {
            std::cout<< "Value of registry: " << ValueOfRegistry << std::endl;

            result = 0;
        }
        else
        {
            result = RegQueryValueExA(*_hKey, NameOfRegistry, NULL, &_dwType, (BYTE*)&ValueOfRegistry, &_dwSize);
        }
    }
    else
    {
        result = RegOpenKeyExA(HKEY_CURRENT_USER, _Path, 0, KEY_READ, _hKey);
    }

    return result; 

}

