/*
assignment 3

Author: YI-LUN,WU
Student ID: 173968231
Email: ywu296@myseneca.ca

Date
2025/11/14
*/

#ifndef SENECA_BOOK_H
#define SENECA_BOOK_H

#include "mediaItem.h"
#include <ostream>
#include <string>

namespace seneca {
class Book : public MediaItem {
   std::string m_author;
   std::string m_country;
   double m_price{0.0};

   Book(const std::string &title, const std::string &summary,
        unsigned short year)
       : MediaItem(title, summary, year) {}

 public:
   Book(const Book &) = delete;
   Book &operator=(const Book &) = delete;
   Book(Book &&) = delete;
   Book &operator=(Book &&) = delete;

   static Book *createItem(const std::string &strBook);

   void display(std::ostream &out) const override;
};
} // namespace seneca

#endif