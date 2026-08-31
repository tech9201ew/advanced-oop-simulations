/*
assignment 3

Author: YI-LUN,WU
Student ID: 173968231
Email: ywu296@myseneca.ca

Date
2025/11/14
*/

#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H

#include "mediaItem.h"
#include <ostream>
#include <string>
#include <vector>

namespace seneca {

class Collection;

using ObserverFunc = void (*)(const Collection &, const MediaItem &);

class Collection {
   std::string m_name;
   std::vector<MediaItem *> m_items;
   ObserverFunc m_observer{nullptr};

 public:
   Collection(const std::string &name);

   ~Collection();

   Collection(const Collection &) = delete;
   Collection &operator=(const Collection &) = delete;
   Collection(Collection &&) = delete;
   Collection &operator=(Collection &&) = delete;

   const std::string &name() const;
   size_t size() const;

   void setObserver(ObserverFunc observer);

   Collection &operator+=(MediaItem *item);
   MediaItem *operator[](size_t idx) const;
   MediaItem *operator[](const std::string &title) const;

   void removeQuotes();
   void sort(const std::string &field);
};

std::ostream &operator<<(std::ostream &out, const Collection &col);

} // namespace seneca

#endif