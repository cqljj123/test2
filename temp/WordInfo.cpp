//WordInfo.cpp source file
#include "WordInfo.h"

using namespace WORDINFO;


//Word 类函数的定义
template<>
void Word::SetValueName<double>(const double& value)
{
	_WordName=to_string(value);
}

template<>
void Word::SetValueName<string>(const string& value)
{
	_WordName=value;
}

//WordList类函数的定义
void WordList::AddWord(const Word& word)
{
	this->_WordList.push_back(word);
}

void WordList::DelWrod(Word& word)
{
	auto it=_WordList.begin();
	while( it != _WordList.end() )
	{
		if( it->GetWordName() == word.GetWordName() )
			break;
		++it;
	}
	_WordList.erase(it);
}

int WordList::GetSize() const 
{
	return _WordList.size();
}