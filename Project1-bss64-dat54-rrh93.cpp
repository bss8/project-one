#include <iostream>
#include <fstream> 
#include <string.h>
#include <cstdlib> 
#include <iostream>
#include <fstream>
#include <stdexcept>

#ifndef CLAUSE_ITEM_H
#define CLAUSE_ITEM_H

#include <string>

#define INT 1
#define STRING 2
#define FLOAT 3

/**
 * ClauseItem - Represents either a premise or a conclusion (or both). 
 * How a variable is treated depends on the data structure in which it 
 * resides (e.g., premiseList or conclusionList)
 */ 
class ClauseItem
{
public:
    std::string name;
    std::string value;
    int type;

    ClauseItem();
    ClauseItem(std::string nameP, std::string valueP, int typeP);
    void operator=(const ClauseItem& srcClause);

};

#endif // !CLAUSE_ITEM_H


#ifndef STATEMENT_H
#define STATEMENT_H

#include <vector>

/**
 * Represents a single line entry in the knowledge base file. 
 * 0 to n premises and 1 conclusion. A statement may be atomic (e.g., var = true). 
 * 
 */ 
class Statement
{
public:
    Statement();
    Statement(ClauseItem conclusionP, std::vector<ClauseItem>& premiseListP);
    ClauseItem conclusion;
    std::vector<ClauseItem> premiseList;
};

#endif // !STATEMENT_H

#ifndef KNOWLEDGE_BASE_H
#define KNOWLEDGE_BASE_H

#include <vector>
#include <string>
#include <set>


class KnowledgeBase 
{
public:
    KnowledgeBase();  // Constructor
    void displayBase();  // Display Entire KnowledgeBase
    void populateKnowledgeBase(std::string fileName);
    std::string getConclusion(unsigned int);  //  get a conclusion from index provided
    std::string getPremise(unsigned int, unsigned int);  // first UI is kBase index, second is premise index  
    std::vector<Statement> kBase;
    std::set<std::string> conclusionSet;
private:
    bool isConclusionGood(Statement&, std::string, std::string&);
    bool arePremisesGood(Statement&, std::string);
};


#endif //KNOWLEDGE_BASE_H

#ifndef VARIABLE_LIST_ITEM_H
#define VARIABLE_LIST_ITEM_H

#include <string>
#include <vector>

class VariableListItem
{
public:
    VariableListItem(std::string nameP, bool instantiatedP, std::string valueP, std::string descriptionP, int typeP);
    void populateStatementIndex(const KnowledgeBase& knowledgeBase);
    
    std::string name;
    bool instantiated;
    std::string value;
    std::string description;
    int type;
    std::vector<int>statementIndex;
};

#endif // !VARIABLE_LIST_ITEM_H

#include <iostream>
#include <fstream>

#ifndef BACK_CHAIN_H
#define BACK_CHAIN_H

#include <string>
#include <vector>

class BackChain
{
public:
    void populateLists();
    void runBackwardChaining();
    void populateVariableList(std::string);

    KnowledgeBase ruleSystem;
    std::vector<VariableListItem> variableList;

    // Due to the design of the system (use the info from the backward
    // chain to populate the forward chain), this list is needed
    // to keep track of the conclusions that were set.
    std::vector<VariableListItem> intermediateConclusionList;

private:
    int findValidConclusionInStatements(std::string conclusionName, int startingIndex, std::string stringToMatch);
    bool instantiatePremiseClause(const ClauseItem& clause);
    bool processPremiseList(const Statement& statement);
    void addToIntermediateConclusionList(const ClauseItem& intermediateConclusion);

};

#endif // !BACK_CHAIN_H


#ifndef FORWARD_CHAIN_H
#define FORWARD_CHAIN_H

#include <string>
#include <vector>
#include <queue>

class ForwardChain
{
public:
    void runForwardChaining();
    void copyVariableList(const std::vector<VariableListItem>& srcVariableList);
    void copyKnowledgeBase(const KnowledgeBase& srcKnowledgeBase);
    int getMatchingVariableListEntry(std::string entryName);
    void addIntermediateConclusions(const std::vector<VariableListItem>& srcConclusionVariableList);
    
    std::queue<ClauseItem> conclusionVariableQueue;

    KnowledgeBase ruleSystem;
    std::vector<VariableListItem> variableList;

private:
    void processStatementIndex(int variableListEntry);
    bool instantiatePremiseClause(const ClauseItem& clause);
    bool processPremiseList(std::vector<ClauseItem>& premiseList);
};

#endif // !FORWARD_CHAIN_H


// These defines are used throughout the program to specify what type of clause
// is being processed. The current implementation is all strings. As such, they
// are retained only for future development.
#define INT 1
#define STRING 2
#define FLOAT 3


/**
 * Constructor | ClauseItem | ClauseItem
 *
 * Summary: Instantiates a default clause with NULL values. Note that if the 
 *          knowledge base contains the value of NULL, some care must be taken.
 *          However, a guard is in place as each index begins at element 1.
 *
 */
ClauseItem::ClauseItem()
{
    name = "NULL";
    value = "NULL";
    type = STRING;
}


/**
 * Constructor | ClauseItem | ClauseItem
 *
 * Summary: Instantiates a clause item with the specified values. Clauses follow
 *          the pattern of Name = Value. The type parameter is for future use.
 *          All types are currently set to type string.
 *
 * @param string nameP:   The name portion of the clause.
 * @param string valueP:  The value portion of the clause.
 * @param int typeP:      The type of clause that it is.
 *
 */
ClauseItem::ClauseItem(std::string nameP, std::string valueP, int typeP)
{
    name = nameP;
    value = valueP;
    type = typeP;
}


/**
 * Operator overload | ClauseItem | operator=
 *
 * Summary: Overloaded equals operator to copy over one clause to another.
 *
 * @param const ClauseItem& srcClause:    The clause that holds the name,
 *                                          value and type to be copied into the
 *                                          new clause.
 *
 */
void ClauseItem::operator=(const ClauseItem& srcClause)
{
    name = srcClause.name;
    value = srcClause.value;
    type = srcClause.type;
}


/**
 * Constructor | Statement | Statement
 *
 * Summary: Instantiates a default statement with NULL values. Note that if the 
 *          knowledge base contains the value of NULL, some care must be taken.
 *          However, a guard is in place as each index begins at element 1.
 *
 */
Statement::Statement()
{
    conclusion.name = "NULL";
    conclusion.value = "NULL";
    conclusion.type = STRING;
    premiseList.push_back(ClauseItem());
}


/**
 * Constructor | ClauseItem | ClauseItem
 *
 * Summary: Instantiates a statement item with the specified values. Statements
 *          follow the pattern of premiseList then conclusion.
 *          All types are currently set to type string.
 *
 * @param ClauseItem conclusionP: The conclusion portion of the statement
 * @param std::vector<ClauseItem>& premiseListP> :    A vector of premise 
 *                                  clauses to be used in the statement.
 *
 */
Statement::Statement(ClauseItem conclusionP, std::vector<ClauseItem>& premiseListP)
{
    conclusion = conclusionP;
    premiseList = premiseListP;
}



/**
 * Constructor | VariableListItem | VariableListItem
 *
 * Summary: Instantiates a variable item with the specified values. Note that no
 *          values are passed in to the statement index. This is because
 *          this index is only used for forward chaining and is populated
 *          at that time.
 *
 * @param string nameP:   Name of the clause variable .
 * @param bool instantiatedP: If it has been given a value. Will start as false.
 * @param string valueP:  Initial value of the clause.
 * @param string descriptionP: A prompt to display when assigning a value.
 * @param int typeP:  The type of clause, usually set to STRING.
 *
 */
VariableListItem::VariableListItem(std::string nameP, bool instantiatedP, std::string valueP, std::string descriptionP, int typeP)
{
    name = nameP;
    instantiated = instantiatedP;
    value = valueP;
    description = descriptionP;
    type = typeP;
    statementIndex.push_back(-1); // To keep in line with the other indexes. But use -1 to note bad values
}


/**
 * CMember function | VariableListItem | populateAtatementIndex
 *
 * Summary: Creates an inverted index to allow for quicker searching when using
 *          forward chaining. Also helps prevent the need to double search or 
 *          process needless entries.
 *
 * @param const KnowledgeBase& knowledgeBase: Used to find entries that match
 *          the name for this variable list entry.
 */
void VariableListItem::populateStatementIndex(const KnowledgeBase& knowledgeBase)
{
    bool isFound = false;

    for (int statementIter = 1; statementIter < knowledgeBase.kBase.size(); statementIter++)
    {
        isFound = false;
        for (int premiseIter = 1; (!isFound && premiseIter < knowledgeBase.kBase.at(statementIter).premiseList.size()); premiseIter++)
        {
            if (name == knowledgeBase.kBase.at(statementIter).premiseList.at(premiseIter).name)
            {
                isFound = true;
                statementIndex.push_back(statementIter);
            }
        }
    }
}



KnowledgeBase::KnowledgeBase()
{
    std::cout << "\nCreating knowledge base instance..." << std::endl;
}

/**
 * populateKnowledgeBase - reads in a data file and creates the knowledge base (KB) 
 * accordingly, provided the right format is used. 
 * File format example
 * issue = Failure to Start ^ has_fuel = n : repair = Insufficient Fuel, Add more fuel.
 *
 * = is used to separate variable and value
 * ^ is logical AND
 * : separates clause and conclusion
 *
 * The above example should be read as follows. If issue is equal to failure to start, and has fuel is false
 * then repair conclusion equals "Insufficient Fuel, Add more fuel." 
 *
 * @param string fileName - the name of the file containing the knowledge base. knowledgeBase.txt
 *
 * @return none
 *
 */
void KnowledgeBase::populateKnowledgeBase(std::string fileName)
{
    int total_good = 0, total_bad = 0;

    std::string inputBuffer;
    std::ifstream inputFile;
    inputFile.open(fileName);

    if (inputFile)
    {
        while (getline(inputFile, inputBuffer))  // while read was successfull
        {
            std::cout << "Processing:  " << inputBuffer << std::endl;
            if (inputBuffer.size() > 0)
            {
                Statement lList;
                std::string listPremise;

                int indicatorLocation;
                if (isConclusionGood(lList, inputBuffer, listPremise))
                {
                    if (arePremisesGood(lList, listPremise))
                    {
                        std::cout << "Conclusion and premise(s) are good => List Updated\n";
                        kBase.push_back(lList);
                        ++total_good;
                    }
                    else
                    {
                        std::cout << "Premise List is formatted incorrectly.  List NOT updated\n";
                        ++total_bad;
                    }
                }
                else
                {
                    std::cout << "Conclusion is formatted incorrectly.  List NOT updated\n";
                    ++total_bad;
                }
            }
            std::cout << std::endl; 
        }
    }
    else {
        throw std::runtime_error("Error reading Knowledge Base (KB) file. Please validate it uses the correct format. Invoke application with -h or -help for details.");
    }
    std::cout << "\nKnowledge Base finished Loading.\n" << total_good << " items were loaded into the KnowledgeBase\n";
    if ( total_bad > 0 )
        std::cerr << "\nWARNING! " << total_bad << " malfromed item(s) were not loaded into the Knowledge Base. " << 
        "\nPlease check output above for items not loaded and inspect data file.\n";
    std::cout << "<CR/Enter> to continue  ";
    std::cin.ignore();
}

/**
 * isConclusionGood - helper function to check if the conclusion in the premise is valid and trim any white spaces
 * 
 * @param Statement& lList - a statement containing the premise list and the conclusion it leads to
 * @param std::string iBuffer - the entire statement (premise and conclusions)
 * @param std::string& listPremise - a list of the premises (left side of expression) 
 * 
 * @return bool - if the conclusion is valid, true. Otherwise false. 
 */
bool KnowledgeBase::isConclusionGood(Statement& lList, std::string iBuffer, std::string& listPremise)
{
    ClauseItem nClause;
    std::string listConclusion;
    int indicatorLocation = iBuffer.find(':', 0);  // THEN symbol

    if (indicatorLocation == -1)
        return false;

    listPremise = iBuffer.substr(0, indicatorLocation);
    listConclusion = iBuffer.substr(indicatorLocation + 1, iBuffer.size());
    indicatorLocation = listConclusion.find('=', 0);  // Assignment Symbol
    
    if (indicatorLocation == -1)
        return false;
    
    lList.conclusion.name = listConclusion.substr(0, indicatorLocation);
    
    // trim white spaces in conclusion name, first front, then back
    if (lList.conclusion.name.front() == ' ')
    {
        lList.conclusion.name = lList.conclusion.name.substr(1);
    }
    if (lList.conclusion.name.back() == ' ')
    {
        lList.conclusion.name = lList.conclusion.name.substr(0, lList.conclusion.name.size() - 1);
    }

    lList.conclusion.value = listConclusion.substr(indicatorLocation + 1, listConclusion.size());
    // trim white spaces in conclusion value, first front, then back
    if (lList.conclusion.value.front() == ' ')
    {
        lList.conclusion.value = lList.conclusion.value.substr(1);
    }
    if (lList.conclusion.value.back() == ' ')
    {
        lList.conclusion.value = lList.conclusion.value.substr(0, lList.conclusion.value.size() - 1);
    }

    lList.conclusion.type = STRING;
    conclusionSet.insert(lList.conclusion.name); // add conclusion to set, maintaining unique list of conclusions

    std::cout << "Conclusion is good; ";
    return true;
}

/**
 * isConclusionGood - helper function to check if the conclusion in the premise is valid and trim any white spaces
 * 
 * @param Statement& lList - a statement containing the premise list and the conclusion it leads to
 * @param std::string& listPremise - a list of the premises (left side of expression) 
 * 
 * @return bool - if the premise is valid, true. Otherwise false. 
 */
bool KnowledgeBase::arePremisesGood(Statement& lList, std::string listPremise)
{
    ClauseItem nClause;
    std::string listRight,
        listLeft,
        tmpList;
    do
    {
        int andLocation = listPremise.find('^', 0),
            equalsLocation;

        if (andLocation == -1 && listPremise.size() == 0) // no premise
            return false;

        if (andLocation == -1)
            andLocation = listPremise.size();

        tmpList = listPremise.substr(0, andLocation);
        listPremise.erase(0, andLocation + 1);
        equalsLocation = tmpList.find('=', 0);  // assignment Symbol

        if (equalsLocation == -1)
            return false;

        listRight = tmpList.substr(0, equalsLocation);
        listLeft = tmpList.substr(equalsLocation + 1, tmpList.size());

        if (listLeft.size() == 0 || listRight.size() == 0)  // missing something
            return false;

        // trim white space from clause name, first front then back
        nClause.name = listRight;
        if (nClause.name.front() == ' ')
        {
            nClause.name = nClause.name.substr(1);
        }
        if (nClause.name.back() == ' ')
        {
            nClause.name = nClause.name.substr(0, nClause.name.size() - 1);
        }

        // trim white space from clause value, first front then back
        nClause.value = listLeft;
        if (nClause.value.front() == ' ')
        {
            nClause.value = nClause.value.substr(1);
        }
        if (nClause.value.back() == ' ')
        {
            nClause.value = nClause.value.substr(0, nClause.value.size() - 1);
        }

        nClause.type = STRING;
        lList.premiseList.push_back(nClause);
    } while (listPremise.size() != 0);

    std::cout << "Premise list is good!  " << lList.premiseList.size() - 1 << " premise(s) loaded\n";
    return true;
}

/**
 * displayBase - prints out the imported knowledge base to the screen 
 * We iterate over the knowledge base vector and print the premise list 
 * and the conclusion they lead to in a human readable format. 
 */
void KnowledgeBase::displayBase()
{
    Statement n;
    unsigned int pntr = 1;
    while (pntr < kBase.size())
    {
        unsigned int pPntr = 1,
            lastPntr = kBase.at(pntr).premiseList.size();
        std::cout << pntr << ". IF ";
        while (pPntr < kBase.at(pntr).premiseList.size())
        {
            std::cout << kBase.at(pntr).premiseList.at(pPntr).name;
            pPntr++;
            if (pPntr < lastPntr)
                std::cout << " AND ";

        }
        std::cout << " THEN " << kBase.at(pntr).conclusion.name << std::endl;
        pntr++;
    }
}

/**
 * getConclusion - helper function, which allows to get a conclusion of a specific index in the KB
 * 
 * @param unsigned int index - position of the statement in the knowledge base vector, whose conclusion we want
 * 
 * @return std::string the string representation of the conclusion
 */ 
std::string KnowledgeBase::getConclusion(unsigned int index)
{
    return kBase.at(index).conclusion.name;
}

/**
 * getConclusion - helper function, which allows to get a conclusion of a specific index in the KB
 * 
 * @param unsigned int index - position of the statement in the knowledge base vector, whose conclusion we want
 * @param unsigned int index_1 - once we know which statement, we need to know which premise
 *                               as a statement may contain one or more premises. 
 * 
 * @return std::string the string representation of the premise
 */ 
std::string KnowledgeBase::getPremise(unsigned int index, unsigned int index_1)
{
    return kBase.at(index).premiseList.at(index_1).name;
}




/**
 * Member Function | BackChain | populateLists
 *
 * Summary: Populates the knowledge base and variable lists for the back
 *          chaining portion of the program. Typically read from a csv or text
 *          file. Takes the outside representation of the knowledge base and
 *          allows the inference engine to act on it.
 */
void BackChain::populateLists()
{
    // To offest the vectors by 1, populate index 0 with NULL or Empty elements.
    ruleSystem.kBase.push_back(Statement());
    variableList.push_back(VariableListItem("Empty", false, "", "This is an error string", STRING));
    intermediateConclusionList.push_back(VariableListItem("Empty", false, "", "This is an error string", STRING));

    // Populate the knowledge base and variable list.
    ruleSystem.populateKnowledgeBase("knowledgeBase.txt");
    populateVariableList("variablesList.csv");
}

/**
 * Member Function | BackChain | populateVariableList
 *
 * Summary: Populates the variable list for back chaining. This initial list 
 *          contains only the premises. Note that is is later passed on
 *          to forward chaining in a modified format. 
 *
 * @param string fileName: The name of the file to read entries from. This file
 *                  is in a CSV format of name, prompt, type.
 *
 */
void BackChain::populateVariableList(std::string fileName)
{
    std::string csvLine;

    std::string name;
    std::string prompt = " ";
    int type = 1;
    int startParseLocation = 0;
    int endParseLocation = 0;
    bool isValid = true;

    std::ifstream variableListFile;
    variableListFile.open(fileName);
    int varCount = 0;

    std::cout << "List of variables: "; 

    if (variableListFile)
    {
        while (getline(variableListFile, csvLine))
        {
            startParseLocation = 0;
            endParseLocation = (csvLine.find(',', startParseLocation) - startParseLocation);
            if (endParseLocation <= -1)
            {
                isValid = false;
            }
            name = csvLine.substr(startParseLocation, endParseLocation);

            std::cout << name << ", ";

            startParseLocation = endParseLocation + 1;
            endParseLocation = (csvLine.find(',', startParseLocation) - startParseLocation);
            if (endParseLocation <= -1)
            {
                isValid = false;
            }
            prompt = csvLine.substr(startParseLocation, endParseLocation);

            startParseLocation = endParseLocation + 1;
            endParseLocation = (csvLine.find(',', startParseLocation) - startParseLocation);
            if (endParseLocation <= -1)
            {
                isValid = false;
            }

            if (isValid)
            {
                variableList.push_back(VariableListItem(name, false, "", prompt, type));
                varCount++;
            }
            else
            {
                std::cout << "\nInvalid entry, line " << csvLine << " not added." << std::endl;
            }
        }
        std::cout << "\nNumber of variables: " << varCount << std::endl;
    }
    else
    {
        std::cout << "Could not find the file" << std::endl;
    }
}

/**
 * Member Function | BackChain | processPremiseList
 *
 * Summary: Processed the premise list of a given statement. This statement
 *          can lead to a recursive call if the statement contains a conclusion
 *          in its premise list.
 *
 * Preconditions:   The statement parameter was found to have a valid conclusion.
 *
 * @param Statement& statement   :   An individual statement taken from the
 *                                      knowledge base. It typically includes 
 *                                      premise clauses that will be processed
 *                                      in order to see if they are conclusions,
 *                                      premise clauses, or just invalid.
 *
 */
bool BackChain::processPremiseList(const Statement &statement)
{
    int solution = 0;
    bool isValid = true;
    int location = 0;
    int conclusionLocation = 0;
    std::string valueToMatch = "";

    // Process the premise list for a conclusion that was found to be valid.
    for (int premiseIter = 1; (isValid && premiseIter < statement.premiseList.size()); premiseIter++)
    {

        // Go through and if it is a conclusion on the premise side,
        // back chain with it.
        // This will cause another recursive call by adding a conclusion
        // to the stack. It is this step that allows the removal of the actual
        // stack in back chaining.
        conclusionLocation = findValidConclusionInStatements(statement.premiseList.at(premiseIter).name, 1,
                                                             statement.premiseList.at(premiseIter).value);

        // It is a conclusion but not valid
        if (conclusionLocation == -1)
        {
            isValid = false;
        }

        // It is a conclusion and valid
        if (conclusionLocation > 0)
        {
            isValid = true;

            // This step is not needed for the backward chaining portion. It is used
            // when farward chaining is to immediately follow backward chaining and
            // use values that have already been instantiated.
            addToIntermediateConclusionList(statement.premiseList.at(premiseIter));
        }

        // It was not a conclusion. Go to the clause variable list and
        // check if it is instantiated as well as what the value was.
        if (conclusionLocation == 0)
        {
            isValid = instantiatePremiseClause(statement.premiseList.at(premiseIter));
        }
    }

    return isValid;
}

/**
 * Member Function | BackChain | instantiatePremiseClause
 *
 * Summary: Checks to see if the single premise clause passed in has a matching
 *          value to what exists in the clause variable list. If not, ask for
 *          a value and then check.
 *
 * Postcondition:   The clause variable list, if it matches, will have the
 *                  matching entry instantiated.
 *
 * @param  const ClauseItem& clause:   An individual premise clause. Contains
 *                                      a name and potentially a value.
 *
 * @return bool isValid:   Returns if the individual premise clause was found
 *                          to be valid by matching the name and value of the
 *                          premise clause in the knowledge base to what is
 *                          in the clause variable list.
 *
 */
bool BackChain::instantiatePremiseClause(const ClauseItem &clause)
{
    bool isValid = false;
    bool isFound = false;

    // Go through the entire clause variable list and look for the matching
    // Entry. It has to find a match. If not, it could be the case that
    // The two are out of sync with eachother (the knowledge base and clause
    // variable list).
    for (int premiseClauseIter = 1; (!isFound && premiseClauseIter < variableList.size()); premiseClauseIter++)
    {
        // If the premise clause we are looking to resolve matches, check
        // its status.
        if (clause.name == variableList.at(premiseClauseIter).name)
        {
            isFound = true;

            // This means that it is the first time we encountered this
            // premise. We need more info and will get it in this step.
            if (!variableList.at(premiseClauseIter).instantiated)
            {
                std::cout << variableList.at(premiseClauseIter).description << ": ";
                std::cin >> variableList.at(premiseClauseIter).value;
                std::cout << "\nYou entered: " << variableList.at(premiseClauseIter).value << std::endl;
                variableList.at(premiseClauseIter).instantiated = true;
            }

            // Clause variable list is guaranteed to be updated here.
            // It can now be safely compared to the incoming premise clause
            // value.
            if (variableList.at(premiseClauseIter).value == clause.value)
            {
                isValid = true;
            }
        }
    }

    // The premise clause we just looked at will either be good or bad.
    // One thing to note is that this is for an individual premise.
    return isValid;
}

/**
 * Member Function | BackChain | findValidConclusionInStatements
 *
 * Summary: Takes a conclusion name and value and tries to find a statement
 *          that matches up to both. If it finds one and the recursive stack
 *          is done, that will be the solution. If the stack is not empty,
 *          that means that we just completed an intermediate step in the process.
 *
 * @param string conclusionName: The name of a conclusion to match up to. Used
 *                                  As the first part in checking if a statement
 *                                  is valid or not.
 * @param int startingIndex: The first index location to begin searching
 *                                  from. Typically a 1, but can be adjusted.
 *          string  stringToMatch:  The value portion to be matched when searching
 *                                  for a valid conclusion. It will take on
 *                                  a value when this function is called
 *                                  recursively.
 *
 * @return int location:   Specifies the location of a conclusion.
 *
 */
int BackChain::findValidConclusionInStatements(std::string conclusionName, int startingIndex, std::string stringToMatch)
{
    int location = 0;
    bool isConclusion = false;
    bool isValid = false;

    // This loop will go through the knowledge base and look for a matching
    // conclusion in all of the statements. It initially is not trying to
    // find a match to the conclusion value, as the first inquiry will be
    // the open ended question that the user wants the system to solve.
    // It also begins at index 1 for the first run.
    for (int conclusionIter = startingIndex; (conclusionIter < ruleSystem.kBase.size() && !isValid); conclusionIter++)
    {
        // Check that the conclusion name matches what the user entered or
        // if the back chain is recursing, see if it matches the conclusion
        // Next in the list.
        if (conclusionName == ruleSystem.kBase.at(conclusionIter).conclusion.name)
        {
            // It matched the conclusion name, just that at this point.
            isConclusion = true;

            // Note the DONTCARE here. This allows the initial inquiry to go through
            // Since it is open ended. However, if not DONTCARE, the stringToMatch
            // Parameter that was passed in must match. This is due to the multi
            // purposing of this function.
            if (stringToMatch == ruleSystem.kBase.at(conclusionIter).conclusion.value || stringToMatch == "DONTCARE")
            {
                // It matched the conclusion name (above) and now it also matched the
                // value in the knowledge base. This needs to be fully processed.
                // Process premiseList will do just that for this statement.
                // If everything lines up, we are good.
                isValid = processPremiseList(ruleSystem.kBase.at(conclusionIter));

                if (isValid)
                {
                    // Everything matched up, conclusion name, conclusion value
                    // and the premises all were good.
                    location = conclusionIter;
                }
            }
        }
    }

    /*
    * There are actually three options here. -1 means that the conclusion name
    * was found, but it was not valid. This could happen if there is a bad
    * knowledge base or perhaps the user entered in a bad value, such as an x
    * instead of a y or n.
    *
    * The second option is 0, which means there was no match, no nothing.
    * This can happen if the user enters in a bad inquiry to start.
    *
    * The third option is the actual index of where a valid conclusion was found.
    */
    if (isConclusion && !isValid)
    {
        location = -1;
    }

    // See comment right above this one for info on this return value.
    return location;
}

/**
 * Member Function | BackChain | runBackwardChaining
 *
 * Summary: The entry point for starting the backward chain process. Asks
 *          the user to enter the conclusion to solve and then runs.
 *
 */
void BackChain::runBackwardChaining()
{

    std::string conclusionToSolve = "";
    int conclusionLocation = 0;
    bool isSolvedStatement = false;     

    std::cout << "Please enter a conclusion to solve (values can be: "; 
    int tmpSetCounter = 0; 
    for (auto f : ruleSystem.conclusionSet) 
    {
        std::cout << f;
        tmpSetCounter++;
        if (tmpSetCounter != ruleSystem.conclusionSet.size())
        {
             std::cout << ", ";
        }
    }
    std::cout << "): ";
    std::cin >> conclusionToSolve;
    std::cout << "\nYou entered: " << conclusionToSolve << std::endl;

    conclusionLocation = findValidConclusionInStatements(conclusionToSolve, 1, "DONTCARE");

    //is a conclusion but not valid
    if (conclusionLocation == -1)
    {
        std::cout << "No conclusion match available. Based on your entries, the results are inconclusive. ";
    }
    
    //is a conclusion and valid
    if (conclusionLocation > 0)
    {
        std::cout << "\nResult is: " << ruleSystem.kBase.at(conclusionLocation).conclusion.value << std::endl;
        std::cout << "Conclusion is valid. ";
    }

    //not a conclusion
    if (conclusionLocation == 0)
    {
        std::cout << "No conclusion. ";
    }
}

/**
 * Member Function | BackChain | addToIntermediateConclusionList
 *
 * Summary: This function allows for intermediate conclusion clauses to be added
 *          to the forward chaining variable list. This is needed in order to
 *          run the forward chaining portion immediately after the backward
 *          chaining portion. It allows for all entries including the resolved
 *          intermediate conclusion clauses to be preserved. Note that the 
 *          description field is not specific. This is entered in here only to
 *          keep in line with the other entries. It will not actually be seen.
 *
 */
void BackChain::addToIntermediateConclusionList(const ClauseItem &intermediateConclusion)
{
    intermediateConclusionList.push_back(
        VariableListItem(intermediateConclusion.name,
                         true,
                         intermediateConclusion.value,
                         (intermediateConclusion.name + "(y/n)"),
                         intermediateConclusion.type));
}


/**
 * Member Function | ForwardChain | copyVariableList
 *
 * Summary: Copies over all values that were used to find the backward chaining
 *          conclusion from the clause variable list. This is part one of two.
 *          The second part will also bring over the intermediate conclusions.
 *
 * @param  const vector<VariableListItem>& srcVariableList:    The variable
 *                  list to be copied over. Each element is copied with the
 *                  current values instantiated by backward chaining.
 *
 */
void ForwardChain::copyVariableList(const std::vector<VariableListItem> &srcVariableList)
{
    //do start at 0 in this case, might as well copy over the NULL.
    for (int varListiter = 0; varListiter < srcVariableList.size(); varListiter++)
    {
        variableList.push_back(srcVariableList.at(varListiter));
        variableList.back().populateStatementIndex(ruleSystem);
    }
}

/**
 * Member Function | ForwardChain | addIntermediateConclusions
 *
 * Summary: Takes the intermediate conclusion list that was populated during
 *          backward chaining and adds it to the clause variable list. This is 
 *          needed due to forward chaining requiring all premise items to be in
 *          the clause variable list, which is different from backward chaining.
 *
 * @param  const vector<VariableListItem>& srcConclusionVariableList:  The
 *                  additional conclusion variable list items to copy into the
 *                  forward chaining clause variable list.
 *
 */
void ForwardChain::addIntermediateConclusions(const std::vector<VariableListItem> &srcConclusionVariableList)
{
    //do start at 0 in this case, might as well copy over the NULL.
    for (int conclListIter = 0; conclListIter < srcConclusionVariableList.size(); conclListIter++)
    {
        variableList.push_back(srcConclusionVariableList.at(conclListIter));
        variableList.back().populateStatementIndex(ruleSystem);
    }
}

/**
 * Member Function | ForwardChain | copyKnowledgeBase
 *
 * Summary: Copy the internal representation of the knowledge base over to be used
 *          inforward chaining.
 *
 * @param  const KnowledgeBase& srcKnowledgeBase:  The internal representation
 *          of the knowledge base to be used. Similar to what was done for 
 *          back chaining. 
 */
void ForwardChain::copyKnowledgeBase(const KnowledgeBase &srcKnowledgeBase)
{
    //do start at 0 in this case, might as well copy over the NULL.
    for (int kBaseIter = 0; kBaseIter < srcKnowledgeBase.kBase.size(); kBaseIter++)
    {
        ruleSystem.kBase.push_back(srcKnowledgeBase.kBase.at(kBaseIter));
    }
}

/**
 * Member Function | ForwardChain | runForwardChaining
 *
 * Summary: Entry point for running forward chaining. This is expected to run
 *          after backward chaining, as part of the suggested fix step.
 *
 */
void ForwardChain::runForwardChaining()
{
    ClauseItem queueTopPtr;
    int variableListEntry;
    int initialRepairEntry;

    queueTopPtr.name = "inconclusive";
    queueTopPtr.value = "no valid solution.";

    std::cout << std::endl
              << std::endl
              << "Now running forward chain" << std::endl;

    // Start the chain by looking for the very first prompt, does it have an issue.
    // Note that this will also prevent forward chaining from running if the user
    // entered in a bad value to resolve while back chaining.
    initialRepairEntry = getMatchingVariableListEntry("has_issue");

    if (variableList.at(initialRepairEntry).instantiated)
    {
        conclusionVariableQueue.push(ClauseItem(variableList.at(initialRepairEntry).name,
                                                variableList.at(initialRepairEntry).value,
                                                variableList.at(initialRepairEntry).type));
    }

    while (!conclusionVariableQueue.empty())
    {
        queueTopPtr = conclusionVariableQueue.front();
        std::cout << "Processing " << queueTopPtr.name << std::endl;
        // Note that this is the only location where the queue is reduced.
        conclusionVariableQueue.pop();

        //get the matching entry in the variable list, the value does not matter at this time.
        variableListEntry = getMatchingVariableListEntry(queueTopPtr.name);

        //go through the variable list's inverted index of statements and push any valid conclusions.
        //make sure to prompt for entry of any non instantiated.
        if (variableListEntry != -1)
        {
            processStatementIndex(variableListEntry);
        }
    }

    std::cout << "The final conclusion is - " << queueTopPtr.name << " - with a value of: " << queueTopPtr.value << std::endl;
}

/**
 * Member Function | ForwardChain | processStatementIndex
 *
 * Summary: Runs through an inverted index of the current variable list entry and
 *          checks to see which statements are to be processed due to its value.
 *          This step is part of the BFS, where each matching item
 *          is added to the queue for this particular entry before it is 
 *          popped off the queue and the next one is processed.
 *
 *  @param int variableListEntry: A numeric value of which variable list entry 
 *          is being processed. 
 *
 *  @return    None - note that this is indeed the case since the queue will be 
 *              added to if there is a valid value. If it is not valid, it is not
 *              added.
 */
void ForwardChain::processStatementIndex(int variableListEntry)
{
    int curStatement = 0;

    for (int variableListIter = 1; variableListIter < variableList.at(variableListEntry).statementIndex.size(); variableListIter++)
    {
        //           = The matching variable list entry  . The individual statment number
        curStatement = variableList.at(variableListEntry).statementIndex.at(variableListIter);
        if (true == processPremiseList(ruleSystem.kBase.at(curStatement).premiseList))
        {
            // Everything matched up, so move forward on adding it to the queue to be
            // processed.
            conclusionVariableQueue.push(ruleSystem.kBase.at(curStatement).conclusion);
        }
    }
}

/**
 * Member Function | ForwardChain | processPremiseList
 *
 * Summary: Takes a conclusion name and value and tries to find a statement
 *          that matches up to both. If it finds one and the recursive stack
 *          is done, that will be the solution. If the stack is not empty,
 *          that means that we just completed an intermediate step in the process.
 *
 * @param  vector<ClauseItem>& premiseList: the premise list of a particular
 *                      statement.
 *
 * @return bool isValid: Specifies if the premise clauses were all found
 *                  to be valid for a particular statement..
 *
 */
bool ForwardChain::processPremiseList(std::vector<ClauseItem> &premiseList)
{
    bool isValid = true;

    for (int premiseIter = 1; (isValid && premiseIter < premiseList.size()); premiseIter++)
    {
        isValid = instantiatePremiseClause(premiseList.at(premiseIter));
    }
    return isValid;
}

/**
 * Member Function | ForwardChain | instantiatePremiseClause
 *
 * Summary: Takes a single clause and verifies that it has been instantiated and
 *          that it matches up to the back chaining portion of diagnostics.
 *          Note that this varies slightly from back chaining and the typical
 *          behavior of the instantiation step.
 *
 * Preconditions: Backchaining has been ran and the variable list is populated
 *                  with the needed results.
 *
 * @param  string  conclusionName: The name of a conclusion to match up to. Used
 *                                  As the first part in checking if a statement
 *                                  is valid or not.
 *
 * @return isFound:    Specifies if the incoming clause is found within the 
 *                      variable list. 
 */
bool ForwardChain::instantiatePremiseClause(const ClauseItem &clause)
{
    bool isFound = false;

    // Look through the variable list and see if this particular clause has a valid match.
    for (int varListIter = 1; (!isFound && varListIter < variableList.size()); varListIter++)
    {
        if (variableList.at(varListIter).instantiated && clause.name == variableList.at(varListIter).name && clause.value == variableList.at(varListIter).value)
        {
            isFound = true;
        }
    }

    return isFound;
}

/**
 * Member Function | ForwardChain | getMatchingVariableListEntry
 *
 * Summary: Takes a conclusion name that was popped off of the queue and tries to 
 *          locate it in the variable list. Note that the variable list will only
 *          contain unique values.
 *
 * @param  string entryName: The name of the variable list entry to match up.
 *
 * @return int matchingEntryIndex: The location of the matching entry. Returns
 *                  -1 if it is not found.
 *
 */
int ForwardChain::getMatchingVariableListEntry(std::string entryName)
{
    int matchingEntryIndex = -1;
    bool isFound = false;

    for (int variableListIter = 1; (!isFound && variableListIter < variableList.size()); variableListIter++)
    {
        if (entryName == variableList.at(variableListIter).name)
        {
            isFound = true;
            matchingEntryIndex = variableListIter;
        }
    }

    return matchingEntryIndex;
}








/**
 * diagnose - as per project requirements, diagnose function emplyes Backward chaining
 * This is how we allow for diagnosing what issue the vehicle has. 
 *
 * @param BackChain& backChain - a BackChain instance
 *
 * @return none
 *
 */
void diagnose(BackChain& backChain)
{
    backChain.runBackwardChaining();
}


/**
 * repair - as per project requirements, repair function employs Forward Chaining
 * This is how we recommend a repair given an issue. 
 *
 * @param ForwardChain& forwardChain
 *
 * @return none
 */
void repair(ForwardChain& forwardChain)
{
    forwardChain.runForwardChaining();
}


/**
 * main - main function which serves as the entry point into the application.
 * User will be greeted with a welcome message. 
 *
 * If they invoke the program with -h or -help, a help menu with a set of instructions will 
 * be printed to the console. It is also recommended to review the README.md file in the project 
 * root directory. 
 *
 * @param int argc - the count of the number of command line arguments provided
 * @param char* argv[] - array holding the arguments provided during program invocation  
 *
 * @return EXIT_SUCCESS 0 
 *
 */
int main(int argc, char* argv[])
{
    std::cout << "Welcome to the Automobile Diagnostic Program." << std::endl;
    std::cout << "Authors: David Torrente (dat54@txstate.edu), Randall Henderson (rrh93@txstate.edu), Borislav Sabotinov (bss64@txstate.edu)." << std::endl;
    std::cout << std::endl;

    if (argc == 2 && (strcmp(argv[1], "-h") || strcmp(argv[1], "-help"))) 
    {
        std::cout << "To use this program, please read the instructions below and re-launch." << std::endl;
        std::cout << "Additional details for building and execution are also available in the README.md file." << std::endl;
        std::cout << std::endl;

        std::cout << "1. variablesList.csv and knowledgeBase.txt files will be processed to create an instance of the knowledge base" << std::endl;
        std::cout << "2. user will be prompted for a conclusion to solve." << std::endl;
        std::cout << "     - Valid choices for the provided KB file are: issue, repair." << std::endl;

        return EXIT_SUCCESS;
    }


    BackChain backChain;
    backChain.populateLists();

    std::string displayKb;
    std::cout << "Do you want to display the knowledge base (y/n)? ";
    std::cin >> displayKb;

    if ((displayKb == "Y") || (displayKb == "y"))
        backChain.ruleSystem.displayBase();

    diagnose(backChain);

    ForwardChain forwardChain;
    forwardChain.copyKnowledgeBase(backChain.ruleSystem);
    forwardChain.copyVariableList(backChain.variableList);
    forwardChain.addIntermediateConclusions(backChain.intermediateConclusionList);

    repair(forwardChain);

    return EXIT_SUCCESS;
}

