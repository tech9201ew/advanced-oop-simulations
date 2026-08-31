/*
assignment 3

Author: YI-LUN,WU
Student ID: 173968231
Email: ywu296@myseneca.ca

Date
2025/11/14
*/

#include "movie.h"
#include "settings.h"
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>

namespace seneca {

void Movie::display(std::ostream &out) const {
   if (g_settings.m_tableView) {
      out << "M | ";
      out << std::left << std::setfill('.');
      out << std::setw(50) << this->getTitle() << " | ";
      out << std::right << std::setfill(' ');
      out << std::setw(9) << this->getYear() << " | ";
      out << std::left;
      if (g_settings.m_maxSummaryWidth > -1) {
         if (static_cast<short>(this->getSummary().size()) <=
             g_settings.m_maxSummaryWidth)
            out << this->getSummary();
         else
            out << this->getSummary().substr(0,
                                             g_settings.m_maxSummaryWidth - 3)
                << "...";
      } else
         out << this->getSummary();
      out << std::endl;
   } else {
      size_t pos = 0;
      out << this->getTitle() << " [" << this->getYear() << "]\n";
      out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << ""
          << '\n';
      while (pos < this->getSummary().size()) {
         out << "    "
             << this->getSummary().substr(pos, g_settings.m_maxSummaryWidth)
             << '\n';
         pos += g_settings.m_maxSummaryWidth;
      }
      out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << ""
          << std::setfill(' ') << '\n';
   }
}

Movie *Movie::createItem(const std::string &strMovie) {

   if (strMovie.empty() || strMovie[0] == '#') {
      throw "Not a valid movie.";
   }

   std::string tempStr = strMovie;
   size_t pos = 0;

   try {

      pos = tempStr.find(',');
      std::string titleStr = tempStr.substr(0, pos);
      MediaItem::trim(titleStr);
      tempStr.erase(0, pos + 1);

      pos = tempStr.find(',');
      std::string yearStr = tempStr.substr(0, pos);
      MediaItem::trim(yearStr); //
      unsigned short year = static_cast<unsigned short>(std::stoul(yearStr));
      tempStr.erase(0, pos + 1);

      std::string summaryStr = tempStr;
      MediaItem::trim(summaryStr); //

      return new Movie(titleStr, summaryStr, year); //

   } catch (...) {

      throw "Error parsing movie data.";
   }
}

} // namespace seneca