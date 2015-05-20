//
//  vis_helpers.h
//  WGA visualization
//
//  Created by Matthew McGuire on 4/27/15.
//  Copyright (c) 2015 Matthew McGuire. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

#ifndef WGA_visualization_vis_helpers_h
#define WGA_visualization_vis_helpers_h

const bool VERBOSE = false;

/*== (BEGIN) Miscellaneous helper functions  === */
float roundThousandth (float inputVal)
{
    int temp = int(inputVal*1000.0);
    return float(temp)/1000.0;
}
int roundDownDecade (int inputYr)
{
    if (inputYr<10) return 0;
    return (inputYr/10) *10;
}
int returnDecade(std::string Date, int Timeframe)
{
    std::string tempStr;
    tempStr.clear();
    char tempChar = 0;
    for(int q = 0; q < 128; q++) {
        if (q<48 || q> 57) {
            tempChar = q;
            Date.erase(std::remove(Date.begin(), Date.end(), tempChar), Date.end());
        }
    }
    std::size_t leadNumbers = 0;
    leadNumbers = Date.find_first_of("0123456789");
    int foundNums = 0;
    while (leadNumbers!=std::string::npos && foundNums <4)
    {
        tempStr.append(Date.substr(leadNumbers,1));
        leadNumbers = Date.find_first_of("0123456789",leadNumbers+1);
        foundNums++;
    }

    if (Date.empty()) return Timeframe+20; // without a date, we place it in the mid-half century
    if (std::stoi(tempStr) > 1900) return 1900;
    return roundDownDecade(std::stoi(tempStr));
}
template<typename metadType>
std::set<metadType> distinctVals(const std::vector<metadType> colForm)
{
    std::set<metadType> distinctBin;
    for (auto currElement = colForm.begin(), endElement = colForm.end();
         currElement != endElement; ++currElement)
    {
        distinctBin.insert(*currElement);
    }
    return distinctBin;
}

/*== (BEGIN) Miscellaneous helper functions  === */

class FilterTFMap
{
    std::map <std::string, bool> filterMap;
    int filtersAdded;
public:
    FilterTFMap();
    void addFilters(std::set<std::string>, bool);
    bool getFilterVal(std::string);
    void setFilterVal(std::string, bool);
    void clearAll(void);
    void print(void);
};
FilterTFMap::FilterTFMap()
{
    filtersAdded = 0;
}
void FilterTFMap::addFilters(std::set<std::string> newFilters, bool initVal)
{
    // introduce a set of new filters into the object, with initial value
    for (std::set<std::string>::iterator i = newFilters.begin(),
         j = newFilters.end(); i != j; ++i)
    {
        filterMap[*i] = initVal;
        filtersAdded++;
    }
}
bool FilterTFMap::getFilterVal(std::string filterName)
{
    // return the boolean value of the given filter name
    return filterMap[filterName];
}
void FilterTFMap::setFilterVal(std::string filterName, bool newValue)
{
    // assign given value to the filter
    filterMap[filterName]= newValue;
}
void FilterTFMap::clearAll(void)
{
    // remove all filter keys and values from the map
    filterMap.clear();
}
void FilterTFMap::print(void)
{
    // cout all filter keys and values from the map
    for (std::map<std::string, bool>::iterator i = filterMap.begin(),
         j = filterMap.end(); i != j; ++i)
        std::cout << i->first << "\t\t" << i->second << std::endl;
}


/*== (BEGIN) Map of filter values to integers  === */
class ColumnIndexMap
{
    std::map <std::string, int> metaMap;
    int columnsAdded;
public:
    ColumnIndexMap();
    void addStringKeys(std::set<std::string>, std::string);
    void addIntKeys(std::set<int>, std::string);
    int getStringVal(std::string, std::string);
    int getIntVal(int, std::string);
    std::set<std::string> getStrings(void);
    void clearAll(void);
    void print(void);
};
ColumnIndexMap::ColumnIndexMap()
{
    columnsAdded = 0;
}
void ColumnIndexMap::addStringKeys(std::set<std::string> newSet, std::string prefix)
{
    int k = 0;
    for (std::set<std::string>::iterator i = newSet.begin(), j = newSet.end(); i != j; ++i)
    {
        metaMap[prefix+*i] = k++;
    }
    columnsAdded++;
}
void ColumnIndexMap::addIntKeys(std::set<int> newSet, std::string prefix)
{
    int k = 0;
    for (std::set<int>::iterator i = newSet.begin(), j = newSet.end(); i != j; ++i)
    {
        metaMap[prefix+std::to_string(*i)] = k++;
    }
    columnsAdded++;
}
int ColumnIndexMap::getStringVal(std::string v, std::string prefix)
{
    return metaMap[prefix+v];
}
int ColumnIndexMap::getIntVal(int v, std::string prefix)
{
    return metaMap[prefix+std::to_string(v)];
}
void ColumnIndexMap::clearAll(void)
{
    columnsAdded = 0;
    metaMap.clear();
};
void ColumnIndexMap::print(void)
{
    for (std::map<std::string, int>::iterator i = metaMap.begin(), j = metaMap.end(); i != j; ++i)
        std::cout << i->first << "\t\t" << i->second << std::endl;
}
std::set<std::string> ColumnIndexMap::getStrings(void)
{
    std::set<std::string> outList;
    for (std::map<std::string, int>::iterator i = metaMap.begin(), j = metaMap.end(); i != j; ++i)
        outList.insert(i->first);
    return outList;
}
/*== (END) Map of filter values to integers  === */

/*== (BEGIN) Fundamental class of art object metadata  === */
class Artwork
{
public:
    Artwork();
    std::string author;
    int decade;
    std::string technique;
    std::string location;
    std::string form;
    std::string type;
    std::string school;
    int timeframe;
    bool isAgged;
    
};
Artwork::Artwork()
{
    author.empty();
    decade = -1;
    technique.empty();
    location.empty();
    form.empty();
    type.empty();
    school.empty();
    timeframe = -1;
    isAgged = true;
}
/*== (END) Fundamental class of art object metadata  === */


class AggMetrics
{
private:
    size_t totalCountries;
    void init(std::set<std::string>);
    std::vector<int> numWorks;
    std::vector<float> percWorks;
public:
    AggMetrics();
    AggMetrics(std::set<std::string>);
    void updatePercs(void);
    void clearWorks(void);
    void printCountries(void);
    void addWorks(std::string, int);
    void setWorks(std::string, int);
    int getWorks(std::string);
    float getPerc(std::string);
    std::vector<int> histogramVals;
    void clearHistogram(int);
    void incrementHistogramValue(int, int);
    void setHistogramValue(int, int);
    size_t totalWorks;
    std::vector<std::string> countryNames;
};
AggMetrics::AggMetrics(void)
{
    
}
AggMetrics::AggMetrics(std::set<std::string> countrySet)
{
    AggMetrics();
    init(countrySet);
}
void AggMetrics::init(std::set<std::string> countrySet)
{
    countryNames.clear();
    // add every element of the set as a new Country name
    for (std::set<std::string>::iterator it=countrySet.begin(); it!=countrySet.end(); ++it)
    {
        countryNames.push_back(*it);
        // initialize numWorks and percWorks to zero
        numWorks.push_back(0);
        percWorks.push_back(0.0);
    }
    totalCountries = countrySet.size();
    countryNames.push_back(""); // Add an empty element to the end for easier vector iteration
    clearWorks();
}
void AggMetrics::printCountries(void)
{
    std::cout << "Code\tCountry Name\t\tWorks\tPerc." << std::endl;
    for(int q = 0; q < totalCountries; q++)
        std::cout << q << "\t" << countryNames[q]
        << "\t\t" << numWorks[q] << "\t" << percWorks[q] << std::endl;
}
void AggMetrics::clearWorks(void)
{
    for (auto currCountry = 0; currCountry != totalCountries; ++currCountry)
    {
        numWorks[currCountry]=0;
        percWorks[currCountry]=0.0;
    }
    totalWorks = 0;
};
void AggMetrics::addWorks(std::string whichCountry, int worksDelta)
{
    std::vector<std::string>::iterator iter;
    iter = find(countryNames.begin(), countryNames.end(), whichCountry);
    if (iter== countryNames.end())
    {
        std::cerr << "You referenced a country that isn't known!" << std::endl;
        return;
    }
    long workIndex = std::distance(countryNames.begin(), iter);
    numWorks[workIndex] += worksDelta;
    totalWorks += worksDelta;
    updatePercs();
}
void AggMetrics::setWorks(std::string whichCountry, int quantity)
{
    std::vector<std::string>::iterator iter;
    iter = find(countryNames.begin(), countryNames.end(), whichCountry);
    if (iter== countryNames.end())
    {
        std::cerr << "You referenced a country that isn't known!" << std::endl;
        return;
    }
    long workIndex = std::distance(countryNames.begin(), iter);
    totalWorks +=  (quantity - getWorks(whichCountry));
    numWorks[workIndex] = quantity;
    updatePercs();
}
int AggMetrics::getWorks(std::string whichCountry)
{
    std::vector<std::string>::iterator iter;
    iter = find(countryNames.begin(), countryNames.end(), whichCountry);
    if (iter== countryNames.end())
    {
        std::cerr << "You referenced a country that isn't known!" << std::endl;
        return -1;
    }
    long workIndex = std::distance(countryNames.begin(), iter);
    return numWorks[workIndex];
}
float AggMetrics::getPerc(std::string whichCountry)
{
    std::vector<std::string>::iterator iter;
    iter = find(countryNames.begin(), countryNames.end(), whichCountry);
    if (iter== countryNames.end())
    {
        std::cerr << "You referenced a country that isn't known!" << std::endl;
        return -1;
    }
    long workIndex = std::distance(countryNames.begin(), iter);
    return percWorks[workIndex];
}
void AggMetrics::updatePercs()
{
    for(int q = 0; q < totalCountries; q++)
    {
        percWorks[q] = roundThousandth(float(numWorks[q])/float(totalWorks));
    }
}
void AggMetrics::clearHistogram(int numHistoBins)
{
    // reset: clear all histogram values to 0.0
    histogramVals.clear();
    for(int j = 0; j < numHistoBins; ++j)
        histogramVals.push_back(0);
}
void AggMetrics::incrementHistogramValue(int decade, int value)
{
    histogramVals[decade] +=value;
}
void AggMetrics::setHistogramValue(int decade, int value)
{
    histogramVals[decade] =value;
}

class WorkList
{
    std::vector<Artwork> works;
    int totalAgged;
    // vectors made from sets of unique column values
    std::vector<std::string> colForm;
    std::vector<std::string> colType;
    std::vector<std::string> colSchool;
    std::vector<int> colTimeframe;
    void readWorks(std::string fileToRead);
    ColumnIndexMap colIndices;
    AggMetrics formMetrics;
    FilterTFMap filterList;
    Artwork parseOneLine(std::vector<std::string>);
    void extractCols(void);
    void updateNumbers(void);
    bool filterCheck(std::string,std::string,std::string);
public:
    WorkList(std::string fileToRead);
    void clearWorks(void);
    float getPerc(std::string);
    std::vector<float> getAllPercs(void);
    int getRaw(std::string);
    void setFilterState(std::string, bool);
    bool getFilterState(std::string);
    std::vector<float> getDecadeHisto(void);
    void updateDecadeHisto(void);
    void adjustTimeframes(int, int);
    void printSummary(void);
    std::vector<std::string> getCountriesList(void);
};
WorkList::WorkList(std::string fileToRead)
{
    readWorks(fileToRead);
    extractCols();
    formMetrics = distinctVals(colSchool);
    filterList.addFilters(colIndices.getStrings(), true);
    updateNumbers();
    updateDecadeHisto();
    formMetrics.printCountries();
}
std::vector<float> WorkList::getDecadeHisto(void)
{
    std::vector<float> currentHisto;
    currentHisto.reserve(100);
    for(int i = 0; i < formMetrics.histogramVals.size(); ++i)
    {
        currentHisto.push_back(float(formMetrics.histogramVals[i])/float(formMetrics.totalWorks));
    }
    return currentHisto;
}
void WorkList::updateDecadeHisto(void)
{
    // clear 96 histogram bins (one for each decade from 950 to 1900)
    formMetrics.clearHistogram(96);
    // loop through visible works
    // increment bins by decade
    for(int i = 0; i < works.size(); ++i)
    {
        if(works[i].isAgged) {
            // update raw count values
            formMetrics.incrementHistogramValue(((works[i].decade-950)/10), 1);
        }
    }
}
bool WorkList::filterCheck(std::string first,std::string second,std::string third)
{
    // check the Visible flag of each filter
    // return true if all visible, false otherwise
    if(!filterList.getFilterVal(first)) return false;
    if(!filterList.getFilterVal(second)) return false;
    if(!filterList.getFilterVal(third)) return false;
    return true;
}
void WorkList::updateNumbers(void)
{
    formMetrics.clearWorks();
    // loop through every (visible) work
    for(int i = 0; i < works.size(); ++i)
    {
        if(works[i].isAgged) {
            // update raw count values
            formMetrics.addWorks(works[i].school, 1);
        }
    }
    // totalAgged and percentages are automatically
    // kept up to date by the addWorks(string, int) call above
}
void WorkList::clearWorks(void)
{
    // clear all works
    // clear all column extractions
    // reset all metrics
}
float WorkList::getPerc(std::string country)
{
    // return the current filtered percentage value for the country
    return formMetrics.getPerc(country);
}
std::vector<float> WorkList::getAllPercs(void)
{
    formMetrics.updatePercs();
    std::vector<float> returnList;
    std::vector<std::string>::iterator itr;
    for (itr =formMetrics.countryNames.begin(); itr < formMetrics.countryNames.end(); itr++)
    {
        returnList.push_back(formMetrics.getPerc(*itr));
    }
    return returnList;
}
int WorkList::getRaw(std::string country)
{
    // return the current filtered raw # works for the country
    return formMetrics.getWorks(country);
}
bool WorkList::getFilterState(std::string filter)
{
    // reply with the current state of given filter
    return filterList.getFilterVal(filter);
}
void WorkList::adjustTimeframes(int lowYear, int highYear)
{
    for(int i =950; i <=1900; i+= 50)
    {
        std::string filterTempName="timeframe_"+std::to_string(i);
        if(i<lowYear)           // set a too-low timeframe to false
        {
            if(getFilterState(filterTempName))
                setFilterState(filterTempName, false);
        }
        else
        if(i>highYear)           // set a too-low timeframe to false
        {
            if(getFilterState(filterTempName))
                setFilterState(filterTempName, false);
        }
        else
        if(!getFilterState(filterTempName))
            setFilterState(filterTempName, true);
    }
}
void WorkList::setFilterState(std::string filter, bool state)
{
    // set the given filter to the state
    if (filterList.getFilterVal(filter)  == state) return;
    filterList.setFilterVal(filter, state);
    // update relevant works as Agged or not
    std::string prefix =filter.substr(0,filter.find('_'));
    std::string suffix =filter.substr(filter.find('_')+1,filter.length());
    if (state== false) {
        // setting a filter to FALSE when it was previously TRUE
        if(prefix=="school")
        {
            for(int i = 0; i < works.size(); ++i)
            {
                if (works[i].school == suffix) works[i].isAgged = false;
            }
        }
        else if (prefix=="timeframe")
        {
            for(int i = 0; i < works.size(); ++i)
            {
                if (std::to_string(works[i].timeframe) == suffix) works[i].isAgged = false;
            }
        }
        else if (prefix=="type")
        {
            for(int i = 0; i < works.size(); ++i)
            {
                if (works[i].type == suffix) works[i].isAgged = false;
            }
        }
        else
        {
            for(int i = 0; i < works.size(); ++i)
            {
                if (works[i].form == suffix) works[i].isAgged = false;
            }
        }
        
    }
    else
    {   // setting a filter to TRUE when it was previously FALSE
        if(prefix=="school")
        {
            for(int i = 0; i < works.size(); ++i)
            {
                if (works[i].school == suffix) {
                    if(filterCheck("timeframe_"+std::to_string(works[i].timeframe),"type_"+works[i].type,"form_"+works[i].form)) works[i].isAgged = true;
                }
            }
        }
        else if (prefix=="timeframe")
        {
            for(int i = 0; i < works.size(); ++i)
            {
                if (std::to_string(works[i].timeframe) == suffix){
                    if(filterCheck("school_"+works[i].school,"type_"+works[i].type,"form_"+works[i].form)) works[i].isAgged = true;
                }
            }
        }
        else if (prefix=="type")
        {
            for(int i = 0; i < works.size(); ++i)
            {
                if (works[i].type == suffix) {
                    if(filterCheck("timeframe_"+std::to_string(works[i].timeframe),"school_"+works[i].school,"form_"+works[i].form)) works[i].isAgged = true;
                }
            }
        }
        else
        {
            for(int i = 0; i < works.size(); ++i)
            {
                if (works[i].form == suffix){
                    if(filterCheck("timeframe_"+std::to_string(works[i].timeframe),"type_"+works[i].type,"school_"+works[i].school)) works[i].isAgged = true;
                }
            }
        }
        
    }
    std::cout << "setting filter " << filter << " to " << (state ? "true":"false") << std::endl;
    updateNumbers();
    updateDecadeHisto();
    formMetrics.updatePercs();
//    formMetrics.printCountries();
}
void WorkList::extractCols(void)
{
    // create unique keys for all filter values
    std::transform(std::begin(works), std::end(works), std::back_inserter(colForm), [](const Artwork c) {return c.form;});
    std::transform(std::begin(works), std::end(works), std::back_inserter(colType), [](const Artwork c) {return c.type;});
    std::transform(std::begin(works), std::end(works), std::back_inserter(colSchool), [](const Artwork c) {return c.school;});
    std::transform(std::begin(works), std::end(works), std::back_inserter(colTimeframe), [](const Artwork c) {return c.timeframe;});
    colIndices.addStringKeys(distinctVals(colForm), "form_");
    colIndices.addStringKeys(distinctVals(colType), "type_");
    colIndices.addStringKeys(distinctVals(colSchool), "school_");
    colIndices.addIntKeys(distinctVals(colTimeframe), "timeframe_");
}
void WorkList::readWorks(std::string fileToRead)
{
    std::vector<std::string> tempMeta;
    tempMeta.reserve(10);       // should be 8 but we play safe...
    Artwork tempWork;
    
    size_t nextTab = 0, placeMark = 0;
    bool stillParsing = true;
    std::string tempStr;
    std::string oneLineStr;
    char eolDelim = 13;     // expect carriage return (ascii hex 0D) as line end
    
    // (I) Open a file for reading
    std::ifstream inputFile(fileToRead);
    
    // (II) Read one line at a time into a string until EOF
    while (inputFile)
    {
        getline(inputFile, oneLineStr, eolDelim);
        if(VERBOSE) std::cout << oneLineStr << std::endl;
        
        // (III) Divide the string into a temporary vector<string> then send peices for parsing
        while (stillParsing)
        {
            nextTab = oneLineStr.find('\t',placeMark);
            if(nextTab != std::string::npos)
            {
                tempMeta.push_back(oneLineStr.substr(placeMark,nextTab-placeMark));
                if(VERBOSE) std::cout <<oneLineStr.substr(placeMark,nextTab-placeMark) << std::endl;
                placeMark = nextTab+1;
            }
            else
            {
                tempMeta.push_back(oneLineStr.substr(placeMark));
                if(VERBOSE) std::cout <<oneLineStr.substr(placeMark) << std::endl;
                stillParsing= false;
                tempWork = parseOneLine(tempMeta);
                works.push_back(tempWork);
            }
        }
        tempMeta.clear();
        stillParsing = true;
        placeMark = 0;
        nextTab = 0;
    }
    inputFile.close();
    works.erase(works.begin());
    std::cout << "I just read and parsed " << works.size() << " from this file:" << std::endl;
    std::cout << fileToRead << std::endl;
}
Artwork WorkList::parseOneLine(std::vector<std::string> tempMeta)
{
    Artwork thisWork;
    std::string tempStr;
    char quoteChar = 34;     // expect carriage return (ascii hex 0D) as line end
    
    // (I) Remove quotes from Author, Technique, and Location fields
    // and add them to the temporary Struct
    tempStr = tempMeta[0];
    tempStr.erase(std::remove(tempStr.begin(), tempStr.end(), quoteChar), tempStr.end());
    thisWork.author = tempStr;
    if(VERBOSE) std::cout << thisWork.author << std::endl;
    tempStr = tempMeta[2];
    tempStr.erase(std::remove(tempStr.begin(), tempStr.end(), quoteChar), tempStr.end());
    thisWork.technique = tempStr;
    if(VERBOSE) std::cout << thisWork.technique << std::endl;
    tempStr = tempMeta[3];
    tempStr.erase(std::remove(tempStr.begin(), tempStr.end(), quoteChar), tempStr.end());
    thisWork.location = tempStr;
    if(VERBOSE) std::cout << thisWork.location << std::endl;
    
    // (II) Add Form, Type, and School to the temporary Struct
    thisWork.form = tempMeta[4];
    thisWork.type = tempMeta[5];
    thisWork.school = tempMeta[6];
    if(VERBOSE) std::cout <<thisWork.form << " " << thisWork.type << " " << thisWork.school << std::endl;
    if(VERBOSE) std::cout <<tempMeta[1] << " " << tempMeta[7] << std::endl;
    
    // (III) convert Timeframe to integer date and add it to the temporary struct
    tempStr.clear();
    std::size_t leadNumbers = 0;
    leadNumbers = tempMeta[7].find_first_of("0123456789");
    int foundNums = 0;
    while (leadNumbers!=std::string::npos && foundNums <4)
    {
        tempStr.append(tempMeta[7].substr(leadNumbers,1));
        leadNumbers = tempMeta[7].find_first_of("0123456789",leadNumbers+1);
        foundNums++;
    }
    if (!tempStr.empty()) thisWork.timeframe =roundDownDecade(std::stoi(tempStr));
    else thisWork.timeframe =-1;
    
    // (III) Parse Year into a Decade and add to the temporary struct
    
    thisWork.decade = returnDecade(tempMeta[1], thisWork.timeframe);
    if (thisWork.decade < thisWork.timeframe) thisWork.timeframe -= 50; // fix the wga timeframe errors
    if(VERBOSE) std::cout <<thisWork.timeframe << " " << thisWork.decade << std::endl << std::endl;
    
    return thisWork;
}
void WorkList::printSummary(void)
{
    formMetrics.printCountries();
    std::cout << "\nHistogram data:\n";
    for(int i = 0; i < formMetrics.histogramVals.size(); ++i)
    {
        std::cout << 950+10*i << "   " << (float(formMetrics.histogramVals[i])/float(formMetrics.totalWorks)) << std::endl;
    }
    
}
std::vector<std::string> WorkList::getCountriesList(void)
{
    std::vector<std::string> listNeeded;
    listNeeded = formMetrics.countryNames;
    return listNeeded;
}

#endif
