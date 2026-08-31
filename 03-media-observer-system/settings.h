/*
assignment 3

Author: YI-LUN,WU
Student ID: 173968231
Email: ywu296@myseneca.ca

Date
2025/11/14
*/

#ifndef SENECA_SETTINGS_H
#define SENECA_SETTINGS_H

namespace seneca {
struct Settings {
   short m_maxSummaryWidth{80};
   bool m_tableView{false};
};

extern Settings g_settings;
} // namespace seneca

#endif