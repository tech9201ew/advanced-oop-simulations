

#ifndef SENECA_TVSHOW_H
#define SENECA_TVSHOW_H

#include "mediaItem.h"
#include <list>
#include <ostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace seneca {

class TvShow;

struct TvEpisode {
   const TvShow *m_show{};
   unsigned short m_numberOverall{};
   unsigned short m_season{};
   unsigned short m_numberInSeason{};
   std::string m_airDate{};
   unsigned int m_length{};
   std::string m_title{};
   std::string m_summary{};
};

class TvShow : public MediaItem {
   std::string m_id;
   std::list<TvEpisode> m_episodes;

   TvShow(const std::string &title, const std::string &summary,
          unsigned short year)
       : MediaItem(title, summary, year) {}

 public:
   TvShow(const TvShow &) = delete;
   TvShow &operator=(const TvShow &) = delete;
   TvShow(TvShow &&) = delete;
   TvShow &operator=(TvShow &&) = delete;

   static TvShow *createItem(const std::string &strShow);

   void display(std::ostream &out) const override;

   const std::string &getID() const { return m_id; }

   double getEpisodeAverageLength() const;
   std::list<std::string> getLongEpisodes() const;

 
   static unsigned int parseDuration(const std::string &durationStr) {
      if (durationStr.empty())
         return 0u;

      std::string dur = durationStr;
      MediaItem::trim(dur);

      size_t colon1 = dur.find(':');
      if (colon1 == std::string::npos) {
         try {
            return static_cast<unsigned int>(std::stoul(dur));
         } catch (...) {
            return 0u;
         }
      }

      size_t colon2 = dur.find(':', colon1 + 1);
      if (colon2 == std::string::npos)
         return 0u;

      std::string hhStr = dur.substr(0, colon1);
      std::string mmStr = dur.substr(colon1 + 1, colon2 - colon1 - 1);
      std::string ssStr = dur.substr(colon2 + 1);

      try {
         unsigned int hh = static_cast<unsigned int>(std::stoul(hhStr));
         unsigned int mm = static_cast<unsigned int>(std::stoul(mmStr));
         unsigned int ss = static_cast<unsigned int>(std::stoul(ssStr));
         return hh * 3600u + mm * 60u + ss;
      } catch (...) {
         return 0u;
      }
   }


   template <typename Collection_t>
   static void addEpisode(Collection_t &col, const std::string &strEpisode) {

      if (strEpisode.empty() || strEpisode[0] == '#') {
         throw "Not a valid episode.";
      }

      TvEpisode ep{};
      std::string tempStr = strEpisode;
      size_t pos = 0;
      std::string targetID;

      try {

         pos = tempStr.find(',');
         targetID = tempStr.substr(0, pos);
         MediaItem::trim(targetID);
         tempStr.erase(0, pos + 1);

         pos = tempStr.find(',');
         std::string numStr = tempStr.substr(0, pos);
         MediaItem::trim(numStr);
         ep.m_numberOverall =
             numStr.empty() ? 0
                            : static_cast<unsigned short>(std::stoul(numStr));
         tempStr.erase(0, pos + 1);

         pos = tempStr.find(',');
         std::string seasonStr = tempStr.substr(0, pos);
         MediaItem::trim(seasonStr);
         if (seasonStr.empty()) {
            ep.m_season = 1;
         } else {
            ep.m_season = static_cast<unsigned short>(std::stoul(seasonStr));
         }
         tempStr.erase(0, pos + 1);

         pos = tempStr.find(',');
         std::string inSeasonStr = tempStr.substr(0, pos);
         MediaItem::trim(inSeasonStr);
         ep.m_numberInSeason =
             inSeasonStr.empty()
                 ? 0
                 : static_cast<unsigned short>(std::stoul(inSeasonStr));
         tempStr.erase(0, pos + 1);

         pos = tempStr.find(',');
         ep.m_airDate = tempStr.substr(0, pos);
         MediaItem::trim(ep.m_airDate);
         tempStr.erase(0, pos + 1);

         pos = tempStr.find(',');
         std::string lengthStr = tempStr.substr(0, pos);
         MediaItem::trim(lengthStr);
         ep.m_length = TvShow::parseDuration(lengthStr);
         tempStr.erase(0, pos + 1);

         pos = tempStr.find(',');
         ep.m_title = tempStr.substr(0, pos);
         MediaItem::trim(ep.m_title);
         tempStr.erase(0, pos + 1);

         ep.m_summary = tempStr;
         MediaItem::trim(ep.m_summary);

      } catch (...) {
         throw "Error parsing episode data.";
      }

      TvShow *foundShow = nullptr;
      for (size_t i = 0; i < col.size(); ++i) {
         TvShow *show = dynamic_cast<TvShow *>(col[i]);
         if (show != nullptr && show->getID() == targetID) {
            foundShow = show;
            break;
         }
      }

      if (foundShow) {
         ep.m_show = foundShow;
         foundShow->m_episodes.push_back(ep);
      }
   }
};
} // namespace seneca

#endif
