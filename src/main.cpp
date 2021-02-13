#pragma warning(disable : 4996)

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "ClauseItem.h"
#include "Statement.h"
#include "BackChain.h"
#include "VariableListItem.h"

using namespace std;

void displayResults(int conclusion)
{
    // find the appropriate result string from the knowledge base 
    // and display it.
    if (0 == conclusion)
    {
        cout << "No conclusion was able to be made.";
    }
}

int main()
{
    BackChain backChain;
    backChain.populateLists();
    backChain.runBackwardChaining();
    
    return 0;
}