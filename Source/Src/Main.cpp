#include <iostream>
#include "MainInclude.hpp"
#include <string>

int main()
{
    HKEY hKey;

    // Initializing path to the registry
    std::string str_path = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Privacy";
    // String conversion to LPCSTR
    LPCSTR StringPath = str_path.c_str();

    RegistryPictureChange RegPicObj(&hKey, StringPath);

    std::string NameOfRegistry = "PrivacyConsentPresentationVersion";

    LPCSTR StringNameOfRegistry = NameOfRegistry.c_str();

    int valueOfRegistry = 0;

    if (RegPicObj.CheckRegistry(valueOfRegistry, StringNameOfRegistry) != 0)
    {
        std::cout<< "Error with code: " <<RegPicObj.CheckRegistry(valueOfRegistry, StringNameOfRegistry) <<std::endl;
    }

    return 0;
}