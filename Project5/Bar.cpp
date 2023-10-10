#include "Bar.h"

Bar::Bar()
{
    //set m_data to a new LL
    m_data = new LL<string>;

    //set m_fileName to "test.txt"
    m_fileName = "test.txt";
}

Bar::Bar(string name)
{
    //set m_data to a new LL
    m_data = new LL<string>;

    //set m_fileName to passed string
    m_fileName = name;
}

Bar::~Bar()
{
    //delete m_data;
    delete m_data;

    //clear m_fileName
    m_fileName.clear();
}

void Bar::Start()
{
    //Call Loadfile
    LoadFile();

    //Call RemoveCommon
    RemoveCommon();

    //Call RemoveSingles
    RemoveSingles();

    //Call SortData
    SortData();

    //Call DisplayBars
    DisplayBars();

    //Call Export
    Export();
}

void Bar::LoadFile()
{
    //call fstream to file
    fstream file;

    // Open the file and put it in read mode
    file.open(m_fileName, ios::in);

    // fileLine is used to store the information from the file
    string fileLine;

    //number of words collected
    int numOfWords = 1;

    //get a line from file and set it to fileLine
    while (getline(file, fileLine, '\n'))
    {
        string word;

        //iterate through fileLine
        for (int i = 0; i < int(fileLine.length()); i++)
        {
            //if fileLine[i] is equal to a space or a new line
            if (fileLine[i] == ' ' || fileLine[i] == '\n')
            {
                //call RemovePunct on word
                RemovePunct(word);

                //add word to m_data
                m_data->Insert(word);

                //clear word so we can use it again
                word.clear();

                //increase numOfWords
                numOfWords++;
            }
            else
            {
                //add fileLine[i] to word
                word += fileLine[i];
            }
        }
    }

    //close the file
    file.close();

    //tell the user the amount of words loaded
    cout << numOfWords << " loaded" << endl;
}

void Bar::RemovePunct(string &str)
{
    //alphabet and numbers are a list of viable characters
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    string numbers = "0123456789";

    //iterate through each character and make it lowercase
    for (int i = 0; i < int(str.length()); i++)
    {
        str[i] = tolower(str[i]);
    }

    //RemoveBackA and RemoveFrontA are for checking if the first
    //and last character and checking if it is in alphabet
    bool RemoveBackA = true;
    bool RemoveFrontA = true;

    //iterate through alphabet
    for (int i = 0; i < int(alphabet.length()); i++)
    {
        //check if the front chacter is in alphabet
        if (str.front() == alphabet[i])
        {
            RemoveFrontA = false;
        }

        //checl if the last character is in the alphabet
        if (str.back() == alphabet[i])
        {
            RemoveBackA = false;
        }
    }

    //RemoveBackN and RemoveFrontN are for checking if the first
    //and last character and checking if it is in numbers
    bool RemoveBackN = true;
    bool RemoveFrontN = true;

    //iterate through numbers
    for (int i = 0; i < int(numbers.length()); i++)
    {
        //check if the front chacter is in numbers
        if (str.front() == numbers[i])
        {
            RemoveFrontN = false;
        }

        //check if the back chacter is in numbers
        if (str.back() == numbers[i])
        {
            RemoveBackN = false;
        }
    }

    //if both RemoveBackA and RemoveBackN are true, remove the last
    //character
    if (RemoveBackA == true && RemoveBackN == true)
    {
        str.pop_back();
    }

    //if both RemoveFrontA and RemoveFrontN are true, remove the first
    //character
    if (RemoveFrontA == true && RemoveFrontN == true)
    {
        str.erase(0, 1);
    }
}

void Bar::RemoveCommon()
{
    int wordsRemoved = 0;

    //ask the user if they want to remove common words
    string userInput;
    cout << "Do you want to remove common words (Only use with essays)?" << endl;
    cin >> userInput;

    //check userInput
    while (!(userInput == "yes" || userInput == "no"))
    {
        cout << "please enter yes or no" << endl;
        cin.clear();
        cin.ignore(128, '\n');
        userInput.clear();
        cin >> userInput;
    }

    //if userInput is no, do nothing
    if (userInput == "no")
    {
        return;
    }
    else
    {   
        //iterate throug m_data
        for (int i = 0; i < m_data->GetSize(); i++)
        {
            //iterate through EXCLUDE_LIST
            for (unsigned int j = 0; j < EXCLUDE_LIST.size(); j++)
            {
                //if the data at index i is equal to EXCLUDE_LIST.at(int(j))
                //remove it from the Linked List
                if (m_data->operator[](i).first == EXCLUDE_LIST.at(int(j)))
                {
                    m_data->RemoveAt(EXCLUDE_LIST.at(int(j)));

                    //increase wordsRemoved
                    wordsRemoved++;

                    //decrease i since m_data.GetSize() decrease by 1
                    i--;
                }
            }
        }
    }
    //tell the user what happened
    cout << wordsRemoved << " words removed" << endl;
}

void Bar::RemoveSingles()
{
    
    int wordsRemoved = 0;

    //Ask the user what they want to do
    string userInput;
    cout << "Would you like to remove words with a frequency of 1" << endl;
    cin >> userInput;

    //check userInput
    while (!(userInput == "yes" || userInput == "no"))
    {
        cout << "please enter yes or no" << endl;
        cin.clear();
        cin.ignore(128, '\n');
        userInput.clear();
        cin >> userInput;
    }

    //if userInput is no, do nothing
    if (userInput == "no")
    {
        return;
    }
    else
    {
        //iterate throug m_data
        for (int i = 0; i < m_data->GetSize(); i++)
        {
            //check the frequency of the data at index i
            //if the frequency of the data is equal to 1
            if (m_data->operator[](int(i)).second == 1)
            {
                //Remove the data from the Linked list
                m_data->RemoveAt(m_data->operator[](int(i)).first);

                //increase wordsRemoved
                wordsRemoved++;

                //decrease i since m_data->GetSize() has also decreased
                i--;
            }
        }
    }

    //tell the user what happened
    cout << wordsRemoved << " words removed" << endl;
}

void Bar::SortData()
{
    //iterate through each element in m_data and add it to m_dataSorted
    for (int i = 0; i < m_data->GetSize(); i++)
    {
        m_dataSorted.insert(pair<int, string>(m_data->operator[](int(i)).second, m_data->operator[](int(i)).first));
    }
}

void Bar::DisplayBars()
{
    //reverse_iterator called itr
    multimap<int, string>::reverse_iterator itr;

    //reverse through m_dataSorted
    for (itr = m_dataSorted.rbegin(); itr != m_dataSorted.rend(); itr++)
    {
        //print the name of the data
        cout << itr->second << ": ";

        //iterate the frequency of itr->first
        for (int i = 0; i < itr->first; i++)
        {
            //print barChar
            cout << barChar;
        }
        
        //add a new line
        cout << endl;
    }
}

void Bar::Export()
{
    //reverse_iterator called itr
    multimap<int, string>::reverse_iterator itr;

    //ask the user for the name of the export file
    string userInput;
    cout << "what name should the export file should be called" << endl;
    cin >> userInput;

    //create a file and pass the name the user wanted
    ofstream userFile(userInput);

    //iterate through m_dataSorted
    for (itr = m_dataSorted.rbegin(); itr != m_dataSorted.rend(); itr++)
    {
        //add the name of the data
        userFile << itr->second << ": ";

        //iterate the frequency of itr->first
        for (int i = 0; i < itr->first; i++)
        {
            //print barChar
            userFile << barChar;
        }

        //add a new line
        userFile << endl;
    }

    //close the file
    userFile.close();

    //tell the user what happened
    cout << "Output to exportFile " << userInput << endl;
}