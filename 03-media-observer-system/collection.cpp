/*
assignment 3

Author: YI-LUN,WU
Student ID: 173968231
Email: ywu296@myseneca.ca

Date
2025/11/14
*/

#include <algorithm>
#include <functional>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>

#include "collection.h"

namespace seneca {

Collection::Collection(const std::string &name) : m_name(name) {}

Collection::~Collection() {

   for (auto *item : m_items) {
      delete item;
   }
}

const std::string &Collection::name() const { return m_name; }

size_t Collection::size() const { return m_items.size(); }

void Collection::setObserver(ObserverFunc observer) { m_observer = observer; }

Collection &Collection::operator+=(MediaItem *item) {

   if (this->operator[](item->getTitle()) != nullptr) {

      delete item;
   } else {

      m_items.push_back(item);

      if (m_observer) {
         m_observer(*this, *item);
      }
   }
   return *this;
}

MediaItem *Collection::operator[](size_t idx) const {
   if (idx >= m_items.size()) {

      throw std::out_of_range("Bad index [" + std::to_string(idx) +
                              "]. Collection has [" +
                              std::to_string(m_items.size()) + "] items."); //
   }
   return m_items[idx];
}

MediaItem *Collection::operator[](const std::string &title) const {

   auto it = std::find_if(
       m_items.begin(), m_items.end(),

       [title](const MediaItem *item) { return item->getTitle() == title; });

   if (it != m_items.end()) {
      return *it;
   }

   return nullptr;
}

void Collection::removeQuotes() {

   auto trimQuotes = [](std::string &str) {
      if (str.length() >= 1 && str.front() == '"') {
         str.erase(0, 1);
      }
      if (str.length() >= 1 && str.back() == '"') {
         str.pop_back();
      }
   };

   // ref ai
   std::for_each(m_items.begin(), m_items.end(),

                 [trimQuotes](MediaItem *item) {
                    std::string title = item->getTitle();
                    trimQuotes(title);
                    item->setTitle(title);

                    std::string summary = item->getSummary();
                    trimQuotes(summary);
                    item->setSummary(summary);
                 });
}

// ref ai
void Collection::sort(const std::string &field) {

   std::sort(m_items.begin(), m_items.end(),

             [field](const MediaItem *a, const MediaItem *b) {
                if (field == "title") {
                   return a->getTitle() < b->getTitle();
                }
                if (field == "year") {
                   return a->getYear() < b->getYear();
                }

                return false;
             });
}

std::ostream &operator<<(std::ostream &out, const Collection &col) {

   for (size_t i = 0; i < col.size(); ++i) {

      out << *col[i];
   }
   return out;
}

} // namespace seneca