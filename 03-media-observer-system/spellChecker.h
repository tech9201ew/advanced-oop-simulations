

#ifndef SENECA_SPELLCHECKER_H
#define SENECA_SPELLCHECKER_H

#include <ostream>
#include <string>

namespace seneca {
class SpellChecker {

   static const size_t m_arraySize = 6;
   std::string m_badWords[m_arraySize];
   std::string m_goodWords[m_arraySize];

   size_t m_replacementCounts[m_arraySize]{0};

 public:
   SpellChecker(const char *filename);

   void operator()(std::string &text);

   void showStatistics(std::ostream &out) const;
};
} // namespace seneca

#endif
