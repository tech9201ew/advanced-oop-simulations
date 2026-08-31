/*
assignment 3

Author: YI-LUN,WU
Student ID: 173968231
Email: ywu296@myseneca.ca

Date
2025/11/14
*/

#include "spellChecker.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>

namespace seneca {

SpellChecker::SpellChecker(const char *filename) {
   std::ifstream file(filename);

   if (!file.is_open()) {
      throw "Bad file name!"; //
   }

   std::string bad, good;
   size_t index = 0;

   while (file >> bad >> good && index < m_arraySize) {
      m_badWords[index] = bad;
      m_goodWords[index] = good;
      m_replacementCounts[index] = 0;
      index++;
   }

   file.close();
}

void SpellChecker::operator()(std::string &text) {

   for (size_t i = 0; i < m_arraySize; ++i) {

      size_t pos = text.find(m_badWords[i]);

      while (pos != std::string::npos) //
      {

         text.replace(pos, m_badWords[i].length(), m_goodWords[i]);

         m_replacementCounts[i]++;

         pos = text.find(m_badWords[i], pos + m_goodWords[i].length());
      }
   }
}

void SpellChecker::showStatistics(std::ostream &out) const {
   out << "Spellchecker Statistics\n"; //

   for (size_t i = 0; i < m_arraySize; ++i) {
      out << std::left << std::setw(15) //
          << m_badWords[i] << ": " << m_replacementCounts[i] << " replacements"
          << std::endl; //
   }
}

} // namespace seneca