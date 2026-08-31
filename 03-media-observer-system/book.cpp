/*
assignment 3

Author: YI-LUN,WU
Student ID: 173968231
Email: ywu296@myseneca.ca

Date
2025/11/14
*/

#include "book.h"
#include "settings.h"
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>

namespace seneca {

void Book::display(std::ostream &out) const {
   if (g_settings.m_tableView) {
      out << "B | ";
      out << std::left << std::setfill('.');
      out << std::setw(50) << this->getTitle() << " | ";
      out << std::right << std::setfill(' ');
      out << std::setw(2) << this->m_country << " | ";
      out << std::setw(4) << this->getYear() << " | ";
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
      out << this->getTitle() << " [" << this->getYear() << "] [";
      out << m_author << "] [" << m_country << "] [" << m_price << "]\n";
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

// ref ai
Book *Book::createItem(const std::string &strBook) {

   if (strBook.empty() || strBook[0] == '#') {
      throw "Not a valid book.";
   }

   std::string tempStr = strBook;
   size_t pos = 0;

   try {

      pos = tempStr.find(',');
      std::string authorStr = tempStr.substr(0, pos);
      MediaItem::trim(authorStr);
      tempStr.erase(0, pos + 1);

      pos = tempStr.find(',');
      std::string titleStr = tempStr.substr(0, pos);
      MediaItem::trim(titleStr);
      tempStr.erase(0, pos + 1);

      pos = tempStr.find(',');
      std::string countryStr = tempStr.substr(0, pos);
      MediaItem::trim(countryStr);
      tempStr.erase(0, pos + 1);

      pos = tempStr.find(',');
      std::string priceStr = tempStr.substr(0, pos);
      MediaItem::trim(priceStr);
      double price = std::stod(priceStr);
      tempStr.erase(0, pos + 1);

      pos = tempStr.find(',');
      std::string yearStr = tempStr.substr(0, pos);
      MediaItem::trim(yearStr);
      unsigned short year = static_cast<unsigned short>(std::stoul(yearStr));
      tempStr.erase(0, pos + 1);

      std::string summaryStr = tempStr;
      MediaItem::trim(summaryStr);

      Book *book = new Book(titleStr, summaryStr, year);

      book->m_author = authorStr;
      book->m_country = countryStr;
      book->m_price = price;

      return book;

   } catch (...) {

      throw "Error parsing book data.";
   }
}

} // namespace seneca