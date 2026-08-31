
#include <fstream>   
#include <utility>  
#include "dictionary.h"
#include "settings.h" 

namespace seneca
{
	std::ostream& operator<<(std::ostream& os, PartofSpeech pos) {
		switch (pos) {
		case PartofSpeech::Noun: os << "noun"; break;
		case PartofSpeech::Pronoun: os << "pronoun"; break;
		case PartofSpeech::Adjective: os << "adjective"; break;
		case PartofSpeech::Adverb: os << "adverb"; break;
		case PartofSpeech::Verb: os << "verb"; break;
		case PartofSpeech::Preposition: os << "preposition"; break;
		case PartofSpeech::Conjunction: os << "conjunction"; break;
		case PartofSpeech::Interjection: os << "interjection"; break;
		case PartofSpeech::Unknown: break; 
		}
		return os;
	}


	Dictionary::Dictionary(const char* filename) {
		std::ifstream file(filename);
		if (!file) {
			return; 
		}

		std::string line;
		size_t count = 0;
		while (std::getline(file, line)) {
			count++;
		}

		m_words = new Word[count];
		m_word_count = count;

		file.clear();
		file.seekg(0);

		std::string term, pos_str, def;
		for (size_t i = 0; i < m_word_count; ++i) {

			std::getline(file, term, ',');
			std::getline(file, pos_str, ',');
			std::getline(file, def, '\n');

			m_words[i].m_word = term;
			m_words[i].m_definition = def;
			

			if (pos_str == "n." || pos_str == "n. pl.") m_words[i].m_pos = PartofSpeech::Noun;
			else if (pos_str == "adv.") m_words[i].m_pos = PartofSpeech::Adverb;
			else if (pos_str == "a.") m_words[i].m_pos = PartofSpeech::Adjective;
			else if (pos_str == "v." || pos_str == "v. t." || pos_str == "v. i." || pos_str == "v. t. & i.") m_words[i].m_pos = PartofSpeech::Verb;
			else if (pos_str == "prep.") m_words[i].m_pos = PartofSpeech::Preposition;
			else if (pos_str == "pron.") m_words[i].m_pos = PartofSpeech::Pronoun;
			else if (pos_str == "conj.") m_words[i].m_pos = PartofSpeech::Conjunction;
			else if (pos_str == "interj.") m_words[i].m_pos = PartofSpeech::Interjection;
			else m_words[i].m_pos = PartofSpeech::Unknown;
		}
	}


	void Dictionary::searchWord(const char* word_to_find) const {
		bool first_found = false;
		std::string search_str(word_to_find);

		for (size_t i = 0; i < m_word_count; ++i) {
			if (m_words[i].m_word == search_str) {

				if (!first_found) {
					std::cout << m_words[i].m_word;
					first_found = true;
				} else {
					std::cout << std::string(m_words[i].m_word.length(), ' ');
				}

				std::cout << " - ";

				if (g_settings.m_verbose && m_words[i].m_pos != PartofSpeech::Unknown) {
					std::cout << "(" << m_words[i].m_pos << ") ";
				}

				std::cout << m_words[i].m_definition << std::endl;

				if (!g_settings.m_show_all) {
					break; 
				}
			}
		}

		if (!first_found) {
			std::cout << "Word '" << word_to_find << "' was not found in the dictionary." << std::endl;
		}
	}

	Dictionary::~Dictionary() {
		delete[] m_words;
	}

	Dictionary::Dictionary(const Dictionary& other) {
		if (other.m_words) {
			m_word_count = other.m_word_count;
			m_words = new Word[m_word_count];
			for (size_t i = 0; i < m_word_count; ++i) {
				m_words[i] = other.m_words[i];
			}
		}
	}
	
	Dictionary& Dictionary::operator=(const Dictionary& other) {
		if (this != &other) {
			delete[] m_words;
			m_words = nullptr;
			m_word_count = 0;

			if (other.m_words) {
				m_word_count = other.m_word_count;
				m_words = new Word[m_word_count];
				for (size_t i = 0; i < m_word_count; ++i) {
					m_words[i] = other.m_words[i];
				}
			}
		}
		return *this;
	}

	Dictionary::Dictionary(Dictionary&& src) {
		m_words = src.m_words;
		m_word_count = src.m_word_count;
		src.m_words = nullptr;
		src.m_word_count = 0;
	}

	Dictionary& Dictionary::operator=(Dictionary&& src) {
		if (this != &src) {
			delete[] m_words;
			m_words = src.m_words;
			m_word_count = src.m_word_count;
			src.m_words = nullptr;
			src.m_word_count = 0;
		}
		return *this;
	}
}

