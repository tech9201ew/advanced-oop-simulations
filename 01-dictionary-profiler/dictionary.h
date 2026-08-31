/* 
assignment 1 

Author: YI-LUN,WU
Student ID: 173968231
Email: ywu296@myseneca.ca

Date       
2025/09/25
*/


#ifndef SENECA_DICTIONARY_H
#define SENECA_DICTIONARY_H   

#include <iostream>
#include <string>


namespace seneca 
{

	enum class PartofSpeech
	{
		Unknown, Noun, Pronoun, Adjective, Adverb,
		Verb, Preposition, Conjunction, Interjection,
	};
	
	struct Word
	{
		std::string m_word{};
		std::string m_definition{};
		PartofSpeech m_pos = PartofSpeech::Unknown;
	};

	class Dictionary 
	{
		Word* m_words{ nullptr };   
		size_t m_word_count{ 0 }; 

	public:
		Dictionary() = default;
		Dictionary(const char* filename);
		void searchWord(const char* word) const;

		~Dictionary();

		Dictionary(const Dictionary& other);
		Dictionary& operator=(const Dictionary& other);

		Dictionary(Dictionary&& src);
		Dictionary& operator=(Dictionary&& src);
	};
}




#endif