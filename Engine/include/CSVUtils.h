//
// Created by sloath on 12-Aug-26.
//

#ifndef CSVUTILS_H
#define CSVUTILS_H

#include <iterator>
#include <fstream>
#include <vector>
#include <string>

class CSVRow
{
public:
    std::string operator[](const std::size_t index) const
    {
        return {&mLine[mData[index] + 1], static_cast<std::size_t>(mData[index + 1] - (mData[index] + 1))};
    }

    [[nodiscard]] std::size_t size() const { return mData.size() - 1; }

    void ReadNextRow(std::istream& stream)
    {
        std::getline(stream, mLine);

        mData.clear();
        mData.emplace_back(-1);
        std::string::size_type pos = 0;
        while ((pos = mLine.find(',', pos)) != std::string::npos)
        {
            mData.emplace_back(pos);
            ++pos;
        }
        // this checks for a trailing comma with no data after it.
        pos = mLine.size();
        mData.emplace_back(pos);
    }
private:
    std::string mLine;
    std::vector<int> mData;
};

inline std::istream& operator>>(std::istream& stream, CSVRow& data)
{
    data.ReadNextRow(stream);
    return stream;
}

class CSVIterator
{
public:
    typedef std::input_iterator_tag iterator_category;
    typedef CSVRow value_type;
    typedef std::size_t difference_type;
    typedef CSVRow* pointer;
    typedef CSVRow& reference;

    explicit CSVIterator(std::istream& stream) : mStream(stream.good()?&stream:nullptr) { ++(*this); }
    CSVIterator() : mStream(nullptr) {}

    CSVIterator& operator++() { if (mStream) { if (!((*mStream) >> mRow)){mStream = nullptr;}} return *this; }
    CSVIterator operator++(int) { CSVIterator temp(*this); ++(*this); return temp; }
    CSVRow const& operator*() const { return mRow;}
    CSVRow const* operator->() const { return &mRow;}

    bool operator==(CSVIterator const& rhs) const { return ((this == &rhs) or ((this->mStream == nullptr) and (rhs.mStream == nullptr))); }
    bool operator!=(CSVIterator const& rhs) const { return !((*this) == rhs); }

private:
    std::istream* mStream;
    CSVRow mRow;
};

class CSVRange
{
    std::istream& stream;
public:
    explicit CSVRange(std::istream& str) : stream(str) {}
    [[nodiscard]] CSVIterator begin() const { return CSVIterator{stream};}
    static CSVIterator end() { return CSVIterator{}; }
};

#endif //CSVUTILS_H
