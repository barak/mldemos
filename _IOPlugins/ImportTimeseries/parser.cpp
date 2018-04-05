/*********************************************************************
MLDemos: A User-Friendly visualization toolkit for machine learning
Copyright (C) 2011 Chrstophe Paccolat
Contact: mldemos@b4silio.com

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License,
version 3 as published by the Free Software Foundation.

This library is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free
Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*********************************************************************/
#include <QDebug>
#include "parser.h"

/* CSVRow stuff */

std::istream& operator>>(std::istream& str,CSVRow& data)
{
    data.readNextRow(str);
    return str;
}

std::string const& CSVRow::operator[](std::size_t index) const
{
    return m_data[index];
}
std::string CSVRow::at(size_t column) const
{
    return m_data.at(column);
}
std::string CSVRow::getFirstCell() const
{
	if(!m_data.size()) return string();
	return m_data.at(0);
}
std::string CSVRow::getLastCell() const
{
	if(!m_data.size()) return string();
	return m_data.back();
}
std::vector<std::string> CSVRow::getParsedLine() const
{
    return m_data;
}
std::size_t CSVRow::size() const
{
    return m_data.size();
}

void CSVRow::readNextRow(std::istream& str)
{
    // read line from file
    std::string line;
    std::getline(str,line);

    // convert to stream
    std::stringstream lineStream(line);
    std::string cell;

    // update row (array) content
    m_data.clear();
    while(std::getline(lineStream,cell,','))
    {
        m_data.push_back(cell);
    }
}

unsigned int getType(string input)
{
    if (is<unsigned int>(input))    return UNSIGNED_INT_TYPE;
    if (is<int>(input))             return INT_TYPE;
    if (is<float>(input))           return FLOAT_TYPE;
    if (is<char>(input))            return CHAR_TYPE;
    if (is<string>(input))          return STRING_TYPE;
	return UNKNOWN_TYPE;
}

/* CSVIterator stuff */

CSVIterator::CSVIterator(std::istream& str)  :m_str(str.good()?&str:NULL)
{
    ++(*this);
}

CSVIterator::CSVIterator():m_str(NULL)
{
}

bool CSVIterator::eof()
{
    return (m_str == NULL);
}

// Pre Increment
CSVIterator& CSVIterator::operator++()
{
    if (m_str)
    {
        (*m_str) >> m_row;
        m_str = m_str->good()?m_str:NULL;
    }
    return *this;
}
// Post increment
CSVIterator CSVIterator::operator++(int)
{
    CSVIterator tmp(*this);
    ++(*this);
    return tmp;
}

CSVRow const& CSVIterator::operator*()   const
{
    return m_row;
}

CSVRow const* CSVIterator::operator->()  const
{
    return &m_row;
}

bool CSVIterator::operator!=(CSVIterator const& rhs)
{
    return !((*this) == rhs);
}

bool CSVIterator::operator==(CSVIterator const& rhs)
{
    return ((this == &rhs) || ((this->m_str == NULL) && (rhs.m_str == NULL)));
}

/* CSVParser stuff */

void CSVParser::parse(const char* fileName)
{
	inputTypes.clear();
	classLabels.clear();
	data.clear();
    // init
    file.open(fileName);
	if(!file.is_open()) return;
    pair<map<string,unsigned int>::iterator,bool> ret;
    unsigned int id = 0;

    // Parse CSV input file
    //for(CSVIterator parser(file); parser != CSVIterator(); ++parser)
    for(CSVIterator parser(file); !parser.eof(); ++parser)
    {
		if(!parser->size()) continue;
		// Read output (class) labels
        ret = classLabels.insert( pair<string,unsigned int>(parser->getLastCell(),id) );
        if (ret.second == true) id++; // new class found
		vector<string> parsed = parser->getParsedLine();
		if(!parsed.size()) continue;
		// Fill dataset
		data.push_back(parsed);
    }
//	cout << "Parsing done, read " << data.size() << " entries (size: " << (data.size() ? data.at(0).size() : 0) << ")" << endl;
}

vector<size_t> CSVParser::getMissingValIndex()
{
    vector<size_t> missingValIndex;
    size_t nbCols = data.at(0).size();
    for (size_t i = 0; i < data.size(); i++)
        for (size_t j = 0; j < nbCols; j++)
            if (data[i][j] == "?") missingValIndex.push_back(i);
    return missingValIndex;
}

void CSVParser::cleanData(unsigned int acceptedTypes)
{
    vector<string>::iterator it;
    for(size_t i = 0; i < inputTypes.size() - 1; i++)
        if (!(inputTypes[i]&acceptedTypes)) // data type does not correspond to a requested one
        {
            std::cout << "Removing column " << i << " of type " << inputTypes[i] <<  " ... ";
            for(size_t j = 0; j < data.size(); j++)
            {
                it = data.at(j).begin() + i;
                data.at(j).erase(it); // delete the column
            }
            std::cout << "and matching input reference ...  " ;
            inputTypes.erase(i--); // delete the input to stay consistant
            std::cout << "Done" << std::endl;
        }
}

pair<vector<fvec>,ivec> CSVParser::getData(unsigned int acceptedTypes)
{
    vector<fvec> samples(data.size());
    ivec labels(data.size());
    fvec sample(data.at(0).size()-1);
    std::cout << "Cleaning dataset" << std::endl;
    cleanData(acceptedTypes);
    std::cout << "Transfering into container" << std::endl;
	size_t j;
    for(size_t i = 0; i < data.size(); i++)
    {
		for(j = 0; j < data.at(i).size()-1; j++) // consider last col as label
            sample.at(j) = atof(data.at(i).at(j).c_str());
        samples.at(i) = sample;
        labels.at(i) = classLabels[data.at(i).at(j)]; // j is one the last col now
    }
    return pair<vector<fvec>,ivec>(samples,labels);
}
