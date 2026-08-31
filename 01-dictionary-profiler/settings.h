/* 
assignment 1 

Author: YI-LUN,WU
Student ID: 173968231
Email: ywu296@myseneca.ca

Date       
2025/09/25
*/


#ifndef SENECA_SETTINGS_H
#define SENECA_SETTINGS_H
#include <string>

namespace seneca {

    struct settings
    {
        bool m_show_all = false;
        bool m_verbose = false;
        std::string m_time_units = "nanoseconds";
    };  
    
    extern settings g_settings ;

};

#endif