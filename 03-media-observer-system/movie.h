/*
assignment 3

Author: YI-LUN,WU
Student ID: 173968231
Email: ywu296@myseneca.ca

Date
2025/11/14
*/

#ifndef SENECA_MOVIE_H
#define SENECA_MOVIE_H

#include "mediaItem.h"
#include <ostream>
#include <string>

namespace seneca {
class Movie : public MediaItem {

   Movie(const std::string &title, const std::string &summary,
         unsigned short year)
       : MediaItem(title, summary, year) {}

 public:
   Movie(const Movie &) = delete;
   Movie &operator=(const Movie &) = delete;
   Movie(Movie &&) = delete;
   Movie &operator=(Movie &&) = delete;

   static Movie *createItem(const std::string &strMovie);

   void display(std::ostream &out) const override;
};
} // namespace seneca

#endif