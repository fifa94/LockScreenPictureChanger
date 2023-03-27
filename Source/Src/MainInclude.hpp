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
    void CloseKey(HKEY* hKey){RegCloseKey(*_hKey);};
    
public:
    RegistryPictureChange(HKEY* hKey, LPCSTR Path, DWORD dwType);
    ~RegistryPictureChange();
    long CheckRegistry(LPSTR ValueOfRegistry, LPCSTR NameOfRegistry);
    long WriteRegistry(LPCSTR ValueToWrite,LPCSTR NameOfRegistry);
};

// Constructor
RegistryPictureChange::RegistryPictureChange(HKEY* hKey, LPCSTR Path, DWORD dwType)
:_hKey(hKey), _Path(Path), _dwType(dwType)
{
}

// Destructor
RegistryPictureChange::~RegistryPictureChange()
{
}

long RegistryPictureChange::CheckRegistry(LPSTR ValueOfRegistry, LPCSTR NameOfRegistry)
{
    long result;

    if (RegOpenKeyExA(HKEY_CURRENT_USER, _Path, 0, KEY_READ, _hKey) == ERROR_SUCCESS)
    {
       if (RegQueryValueExA(*_hKey, NameOfRegistry, NULL, &_dwType, (LPBYTE)ValueOfRegistry, &_dwSize) == ERROR_SUCCESS)
        {
            std::cout<< "Value of registry: " << ValueOfRegistry << std::endl;
            //std::cout<< "V " << _dwSize << std::endl;

            result = 0;
        }
        else
        {
            result = RegQueryValueExA(*_hKey, NameOfRegistry, NULL, &_dwType, (LPBYTE)&ValueOfRegistry, &_dwSize);
            CloseKey(_hKey);
        }
    }
    else
    {
        result = RegOpenKeyExA(HKEY_CURRENT_USER, _Path, 0, KEY_READ, _hKey);
        CloseKey(_hKey);
    }

    return result; 

}

long RegistryPictureChange::WriteRegistry(LPCSTR ValueToWrite,LPCSTR NameOfRegistry)
{
    long Result;   

    Result = RegSetValueExA(*_hKey, NameOfRegistry, 0, REG_SZ, (const BYTE*)ValueToWrite, strlen(ValueToWrite) + 1); 

    if (Result != ERROR_SUCCESS) {
        printf("Error writing registry value: %d\n", Result);
        CloseKey(_hKey);
        return Result;
    }

    CloseKey(_hKey);
    return Result;
}