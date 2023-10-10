#include "Sequencer.h"

Sequencer::Sequencer(string fileName) {
    // store the passed file name in m_fileName
    m_fileName = fileName;
}

Sequencer::~Sequencer() {
    // Iterates through all of items in m_DNA and deletes them all
    for (int i = 0; i < int(m_DNA.size()); i++) {
        delete m_DNA.at(i);
    }

    // Extra check, just clears the vector
    m_DNA.clear();

    // Iterates through all of items in m_mRNA and deletes them all
    for (int i = 0; i < int(m_mRNA.size()); i++) {
        delete m_mRNA.at(i);
    }
    // Extra check, just clears the vector
    m_mRNA.clear();

    // Tells the user what happened
    cout << "Deleting DNA Strands" << endl;
    cout << "Deleting mRNA Strands" << endl;
}

void Sequencer::StartSequencing() {
    // Call ReadFile()
    ReadFile();

    // gameOver is used to see if the user wants to continue playing
    bool gameOver = false;

    // userChoice stores the user's input
    int userChoice;

    while (gameOver == false) {
        // Call MainMenu and store the return value in userChoice
        userChoice = MainMenu();

        // A switch statement to determine what to do from userChoice
        switch (userChoice) {
        case 1:
            DisplayStrands();
            break;
        case 2:
            ReverseSequence();
            break;
        case 3:
            Transcribe();
            break;
        case 4:
            Translate();
            break;
        case 5:
            gameOver = true;
            cout << "Exiting program" << endl;
            break;
        }
    }
}

void Sequencer::DisplayStrands() {
    // Iterate through all the strands in m_DNA and use the overloaded
    //  << to print out all the user's DNA strands
    for (int i = 0; i < int(m_DNA.size()); i++) {
        cout << "DNA " << i + 1 << endl;
        cout << *m_DNA.at(i);
    }

    // Iterate through all the strands in m_mRNA and use the overloaded
    //  << to print out all the user's RNA strands
    for (int i = 0; i < int(m_mRNA.size()); i++) {
        cout << "RNA " << i + 1 << endl;
        cout << *m_mRNA.at(i);
    }
}

void Sequencer::ReadFile() {
    fstream file;

    // Open the file and put it in read mode
    file.open(m_fileName, ios::in);

    // fileLine is used to store the information from the file
    string fileLine;

    // split by new lines
    while (getline(file, fileLine, '\n')) {
        // Create a strand and set it equal to nullptr
        Strand *newStrand = nullptr;
        string name;

        // Iterate throught the length of the string provided
        for (int i = 0; i < int(fileLine.length()); i++) {

            // if newStrand has no value
            if (newStrand == nullptr) {

                // if the character is a comma, create the Strand and insert the
                // name
                if (fileLine[i] == ',') {
                    newStrand = new Strand(name);

                    // else, add each character to the string name until a comma
                    // is reached in which newStrand will no longer equal
                    // nullptr
                } else {
                    name += fileLine[i];
                }

                // if the strand is not empty, and the character is not a comma,
                // insert the character to the newStrand
            } else {
                if (fileLine[i] != ',') {
                    newStrand->InsertEnd(fileLine[i]);
                }
            }
        }
        // Add newStrand to the vector for DNA strands.
        m_DNA.push_back(newStrand);
    }

    // Tell the user the file was opened and how many items were loaded
    cout << "Opened File" << endl;
    cout << int(m_DNA.size()) << " strands loaded." << endl;

    // close the file
    file.close();
}

int Sequencer::MainMenu() {
    // userChoice stores the user's choice
    int userChoice;

    // list the possible options
    cout << "1. Display Strands" << endl;
    cout << "2. Reverse Strand" << endl;
    cout << "3. Transcribe DNA to mRNA" << endl;
    cout << "4. Translate mRNA to Amino Acids" << endl;
    cout << "5. Exit" << endl;

    // add the user's choice to userChoice
    cin >> userChoice;

    // if the number provide is not between 1-5, tell the user to pick again
    while (userChoice < 1 || userChoice > 5) {
        // the user's choice was invalid, ask them to pick again
        cout << "Please enter a number between 1-5" << endl;
        cin.ignore(120, '\n');
        cin >> userChoice;
    }

    // return the user's choice
    return userChoice;
}

int Sequencer::ChooseDNA() {
    // if the size of the vector is zero, do nothing and return -1
    if (int(m_DNA.size()) == 0) {
        return -1;
    }

    // store the user's decision in userChoice
    int userChoice;

    // Ask the user which strand they want to work with
    cout << "Which strand to work with?" << endl;

    // user chooses between 1 - and the size of the vector
    cout << "Choose 1-" << int(m_DNA.size()) << endl;

    // add user's choice to userChoice
    cin >> userChoice;

    // checks if the user's choice was between 1 and the size of the vector
    // if not, ask the user to choose again
    while (userChoice < 1 || userChoice > int(m_DNA.size())) {
        cout << "Please enter a number between 1-" << int(m_DNA.size()) << endl;
        cin.ignore(120, '\n');
        cin >> userChoice;
    }

    // subtract 1 for correct indexing
    userChoice -= 1;

    // return userChoice
    return userChoice;
}

int Sequencer::ChooseMRNA() {
    // if the vector size is zero, do nothing and return -1
    if (int(m_mRNA.size()) == 0) {
        return -1;
    }

    // userChoice stores the user's choice
    int userChoice;

    // Ask the user which strand they want to work with
    cout << "Which strand to work with?" << endl;

    // user chooses between 1 - and the size of the vector
    cout << "Choose 1-" << int(m_mRNA.size()) << endl;

    // add user's choice to userChoice
    cin >> userChoice;

    // checks if the user's choice was between 1 and the size of the vector
    // if not, ask the user to choose again
    while (userChoice < 1 || userChoice > int(m_mRNA.size())) {
        cout << "Please enter a number between 1-" << int(m_mRNA.size())
             << endl;
        cin.ignore(120, '\n');
        cin >> userChoice;
    }

    // subtract 1 for correct indexing
    userChoice -= 1;

    // return userChoice
    return userChoice;
}

void Sequencer::ReverseSequence() {

    // store the user's decision in userChoice
    int userChoice;

    // List the options to the user
    cout << "Which type of strand to reverse?" << endl;
    cout << "1. DNA" << endl;
    cout << "2. mRNA" << endl;

    // add user's choice to userChoice
    cin >> userChoice;

    // checks if the user's input is either 1 or 2
    // if not, ask the user to choose again
    while (userChoice < 1 && userChoice > 2) {
        cout << "Please enter either 1 or 2" << endl;
        cin.ignore(120, '\n');
        cin >> userChoice;
    }

    // Stores the user's descion of which DNA or RNA to use
    int userStrandChoice;

    // if the user choose DNA
    if (userChoice == 1) {
        // Gets the user's choice of which DNA strand they want to use
        userStrandChoice = ChooseDNA();

        // if ChooseDna does not return -1
        if (userStrandChoice != -1) {

            // Reverses the strand that the user wanted to reverse
            m_DNA.at(userStrandChoice)->ReverseSequence();

            // Tell the user what happend and what strand got reversed
            cout << "Done reversing DNA " << userStrandChoice + 1
                 << "'s strand." << endl;

            // ChooseDna returned -1, no DNA Strands
        } else {
            // Tell the user what happend
            cout << "Not enough DNA Strands" << endl;
        }

        // if the user choose RNA
    } else if (userChoice == 2) {
        // Gets the user's choice of which RNA strand they want to use
        userStrandChoice = ChooseMRNA();

        // if ChooseRNA does not return -1
        if (userStrandChoice != -1) {

            // Reverses the strand that the user wanted to reverse
            m_mRNA.at(userStrandChoice)->ReverseSequence();

            // Tell the user what happend and what strand got reversed
            cout << "Done reversing mRNA " << userStrandChoice + 1
                 << "'s strand." << endl;

            // ChooseDna returned -1, no RNA Strands
        } else {
            // Tell the user what happend
            cout << "No mRNA to reverse; transcribe first" << endl;
        }
    }
}

void Sequencer::Transcribe() {
    // iterate through all DNA Strands in m_DNA
    for (int i = 0; i < int(m_DNA.size()); i++) {
        // create a string name which is equal to the name of the DNA strand
        string name = m_DNA.at(i)->GetName();

        // Create a new strand called newStrand
        Strand *newStrand = new Strand(name);

        // iterate through each DNA sequence
        for (int j = 0; j < m_DNA.at(i)->GetSize(); j++) {

            // temp stores the char at j with GetData
            char temp = m_DNA.at(i)->GetData(j);

            // Converts temp to the correct RNA version
            if (temp == 'A') {
                temp = 'U';
            } else if (temp == 'T') {
                temp = 'A';
            } else if (temp == 'C') {
                temp = 'G';
            } else if (temp == 'G') {
                temp = 'C';
            }

            // add temp to the newStrand
            newStrand->InsertEnd(temp);
        }
        // add newStrand to m_mRNA
        m_mRNA.push_back(newStrand);
    }
    // Tell the user what happened and how many RNA strands were made
    cout << int(m_mRNA.size())
         << " strands of DNA successfully transcribed into new mRNA strands"
         << endl;
}

void Sequencer::Translate() {
    // Gets the user's choice of which RNA strand they want to use
    int userChoice = ChooseMRNA();

    // count is used to track iterations
    int count = 0;

    // used to store the characters in the RNA Strand
    string trinucleotide;

    // if ChooseMRNA does not return -1
    if (userChoice != -1) {

        //*rnaUser is the rna strand the user picked
        Strand *rnaUser = m_mRNA.at(userChoice);

        // iterate through the RNA strand the user choose
        for (int i = 0; i <= rnaUser->GetSize(); i++) {

            // if count == 3
            if (count == 3) {
                // print out trinucleotide
                cout << trinucleotide << "->";

                // print out the Amino Acid made by trinucleotide by using
                // Convert()
                cout << Convert(trinucleotide) << endl;

                // clear trinucleotide
                trinucleotide.clear();

                // reset count to 0
                count = 0;
            }

            // add the character from the RNA strand to trinucleotide
            trinucleotide += rnaUser->GetData(i);

            // increase count
            count++;
        }
        // if there are no RNA strands
    } else {
        // Tell the user the problem
        cout << "No mRNA to translate; transcribe first" << endl;
    }
}

string Sequencer::Convert(const string trinucleotide) {
    if ((trinucleotide == "AUU") || (trinucleotide == "AUC") ||
        (trinucleotide == "AUA"))
        return ("Isoleucine");
    else if ((trinucleotide == "CUU") || (trinucleotide == "CUC") ||
             (trinucleotide == "CUA") || (trinucleotide == "CUG") ||
             (trinucleotide == "UUA") || (trinucleotide == "UUG"))
        return ("Leucine");
    else if ((trinucleotide == "GUU") || (trinucleotide == "GUC") ||
             (trinucleotide == "GUA") || (trinucleotide == "GUG"))
        return ("Valine");
    else if ((trinucleotide == "UUU") || (trinucleotide == "UUC"))
        return ("Phenylalanine");
    else if ((trinucleotide == "AUG"))
        return ("Methionine (START)");
    else if ((trinucleotide == "UGU") || (trinucleotide == "UGC"))
        return ("Cysteine");
    else if ((trinucleotide == "GCU") || (trinucleotide == "GCC") ||
             (trinucleotide == "GCA") || (trinucleotide == "GCG"))
        return ("Alanine");
    else if ((trinucleotide == "GGU") || (trinucleotide == "GGC") ||
             (trinucleotide == "GGA") || (trinucleotide == "GGG"))
        return ("Glycine");
    else if ((trinucleotide == "CCU") || (trinucleotide == "CCC") ||
             (trinucleotide == "CCA") || (trinucleotide == "CCG"))
        return ("Proline");
    else if ((trinucleotide == "ACU") || (trinucleotide == "ACC") ||
             (trinucleotide == "ACA") || (trinucleotide == "ACG"))
        return ("Threonine");
    else if ((trinucleotide == "UCU") || (trinucleotide == "UCC") ||
             (trinucleotide == "UCA") || (trinucleotide == "UCG") ||
             (trinucleotide == "AGU") || (trinucleotide == "AGC"))
        return ("Serine");
    else if ((trinucleotide == "UAU") || (trinucleotide == "UAC"))
        return ("Tyrosine");
    else if ((trinucleotide == "UGG"))
        return ("Tryptophan");
    else if ((trinucleotide == "CAA") || (trinucleotide == "CAG"))
        return ("Glutamine");
    else if ((trinucleotide == "AAU") || (trinucleotide == "AAC"))
        return ("Asparagine");
    else if ((trinucleotide == "CAU") || (trinucleotide == "CAC"))
        return ("Histidine");
    else if ((trinucleotide == "GAA") || (trinucleotide == "GAG"))
        return ("Glutamic acid");
    else if ((trinucleotide == "GAU") || (trinucleotide == "GAC"))
        return ("Aspartic acid");
    else if ((trinucleotide == "AAA") || (trinucleotide == "AAG"))
        return ("Lysine");
    else if ((trinucleotide == "CGU") || (trinucleotide == "CGC") ||
             (trinucleotide == "CGA") || (trinucleotide == "CGG") ||
             (trinucleotide == "AGA") || (trinucleotide == "AGG"))
        return ("Arginine");
    else if ((trinucleotide == "UAA") || (trinucleotide == "UAG") ||
             (trinucleotide == "UGA"))
        return ("Stop");
    else
        cout << "returning unknown" << endl;
    return ("Unknown");
}
