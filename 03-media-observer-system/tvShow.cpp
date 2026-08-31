/*
assignment 3

Author: YI-LUN,WU
Student ID: 173968231
Email: ywu296@myseneca.ca

Date
2025/11/14
*/

#include "tvShow.h"
#include "settings.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <list>
#include <numeric>
#include <stdexcept>
#include <string>

namespace seneca {

void TvShow::display(std::ostream &out) const {
   if (g_settings.m_tableView) {
      out << "S | ";
      out << std::left << std::setfill('.');
      out << std::setw(50) << this->getTitle() << " | ";
      out << std::right << std::setfill(' ');
      out << std::setw(2) << this->m_episodes.size() << " | ";
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
      out << this->getTitle() << " [" << this->getYear() << "]\n";
      out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << ""
          << '\n';
      while (pos < this->getSummary().size()) {
         out << "    "
             << this->getSummary().substr(pos, g_settings.m_maxSummaryWidth)
             << '\n';
         pos += g_settings.m_maxSummaryWidth;
      }
      for (auto &item : m_episodes) {
         out << std::setfill('0') << std::right;
         out << "    " << 'S' << std::setw(2) << item.m_season << 'E'
             << std::setw(2) << item.m_numberInSeason << ' ';
         if (item.m_title != "")
            out << item.m_title << '\n';
         else
            out << "Episode " << item.m_numberOverall << '\n';

         pos = 0;

         while (pos < item.m_summary.size()) {
            out << "            "
                << item.m_summary.substr(pos, g_settings.m_maxSummaryWidth - 8)
                << '\n';
            pos += g_settings.m_maxSummaryWidth - 8;
         }
      }
      out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << ""
          << std::setfill(' ') << '\n';
   }
}

TvShow *TvShow::createItem(const std::string &strShow) {

   if (strShow.empty() || strShow[0] == '#') {
      throw "Not a valid show.";
   }

   std::string tempStr = strShow;
   size_t pos = 0;

   try {

      pos = tempStr.find(',');
      std::string idStr = tempStr.substr(0, pos);
      MediaItem::trim(idStr);
      tempStr.erase(0, pos + 1);

      pos = tempStr.find(',');
      std::string titleStr = tempStr.substr(0, pos);
      MediaItem::trim(titleStr); //
      tempStr.erase(0, pos + 1);

      pos = tempStr.find(',');
      std::string yearStr = tempStr.substr(0, pos);
      MediaItem::trim(yearStr); //
      unsigned short year = static_cast<unsigned short>(std::stoul(yearStr));
      tempStr.erase(0, pos + 1);

      std::string summaryStr = tempStr;
      MediaItem::trim(summaryStr); //

      TvShow *show = new TvShow(titleStr, summaryStr, year); //

      show->m_id = idStr;

      return show;

   } catch (...) {

      throw "Error parsing show data.";
   }
}

// ref ai
double TvShow::getEpisodeAverageLength() const {
   if (m_episodes.empty()) {
      return 0.0;
   }

   double totalLength = std::accumulate(
       m_episodes.begin(), m_episodes.end(), 0.0,
       [](double sum, const TvEpisode &ep) { return sum + ep.m_length; });

   return totalLength / m_episodes.size();
}

std::list<std::string> TvShow::getLongEpisodes() const {
   std::list<std::string> resultList;

   std::transform(m_episodes.begin(), m_episodes.end(),
                  std::back_inserter(resultList), [](const TvEpisode &ep) {
                     return (ep.m_length >= 3600) ? ep.m_title
                                                  : std::string("");
                  });

   resultList.remove(std::string(""));

   return resultList;
}

} // namespace seneca