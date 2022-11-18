/*
    Student Name: Trey Fullwood
    Student NetID: rf802
    Compiler Used: clion using g++.exe
    Program Description:
        This program creates an AVL tree that stores PC characters.
        Each PC has a unique name, a job, a race, and a level.
        Through the command <add, remove, set, search, display>
        the user can manipulate the AVL to do as the user sees fit.


        Inputs:
        exit – exits the program
        load <file> - parses the contents of file as if they were entered in the text-based interface
        add <name> – creates a new character with the specified name; The level, race, and job of the new character should be set to level 1, PC, and villager.
        remove <name> - removes the character with the specified name.
        set <name> <level/job/race> <value> - set the specified statistic to the specified value for the character with the specified name. The stat parameter can have the following values: level (int), race (string), or job (string)
        search <level/job/race> <value> - searches the character list for one or more PCs with the stat possessing the specified value. The stat parameter has the same values as above plus the value of name. You should display this list in order.
        display <preorder/inorder/postorder> – displays a list of the PCs and their statistics in the desired ordering inorder, preorder, or postorder.

*/


#include "Tokenizer.h"
#include "AVL.h"
#include <fstream>
using namespace std;

void impromptPC(AVL& tree, string name, string stat, string val);
void impromptPC(AVL& tree, string name, int valNum);
bool processText(istream& is, AVL& tree, bool interactive = true);

int main()
{
    AVL bigTree;

    processText(cin, bigTree);

    return 0;

}
// Making a PC character on the fly with a preset Job or Race
void impromptPC(AVL& tree, string name, string stat, string val)
{
    char proceed{'N'};
    cout << "There isn't a PC in the database under that name...\n"
            "Would you like to create a new PC with those stats (Y/N)? ";
    cin >> proceed;
    proceed = toupper(proceed);

    switch(proceed)
    {
        case 'Y': // insert PC, then update the stat
            tree.insert(name);
            tree.updateStat(name, stat, val);
            break;
        case 'N': // cancel operation
            cout << "Fine, we won't" << endl;
            break;
        default: // cancel operation
            cout << "Invalid input...\n"
                    "Terminating sequence, please follow directions next time." << endl;
            break;
    }

}

// Making a PC character on the fly with a preset Level
void impromptPC(AVL& tree, string name, int valNum)
{
    char proceed{'N'};
    cout << "There isn't a PC in the database under that name...\n"
            "Would you like to create a new PC with those stats (Y/N)? ";
    cin >> proceed;
    proceed = toupper(proceed);

    switch(proceed)
    {
        case 'Y': // insert the name, then update the val
            tree.insert(name);
            tree.updateStat(name, valNum);
            break;
        case 'N': // cancel operation
            cout << "Fine, we won't" << endl;
            break;
        default: // cancel operation
            cout << "Invalid input...\n"
                    "Terminating sequence, please follow directions next time." << endl;
            break;
    }
}
bool processText(istream& is, AVL& tree, bool interactive)
{

    string line;
    string command;
    string name, stat, val;
    int valNum;
    Tokenizer tkn;
    while (true)
    {
        if (!interactive)
        {
            if (is.eof()) return true;
        }
        else { cout << ">> "; }

        getline(is, line);
        tkn.setString(line);

        tkn.readWord(command);
        if (command.length() == 1 || line.length() == 0)
        {
            /* //LOGIC ERROR
             * When command == set && (stat == Job || stat == Race) but the name passed in DNE,
             * the inquiry saves the proceed val
             * and reiterates the loop, then displays "Invalid command input, try again buckaroo..."
             *
             * When command == set && stat == Level, it has a similar, but unique in its own right, bug
             * this will set the ">>" to not spawn twice on the same line
             */
            cout << endl;
            continue;
        }

        command[0] = tolower(command[0]);

        // Command == exit
        if (command == "exit")
        {
            cout << "Exiting ...." << endl;
            return false;
        }

        // Command == load
        if (command == "load")
        {
            // load expects a filename ... so read one more word
            if (!tkn.readWord(name))
            {
                cout << "Missing file name" << endl;
                continue; // skip back to the top of the read loop

            }

            ifstream fin;
            bool status = true;
            fin.open(name);
            if (fin.is_open())
            {
                // keeping in mind the note about the definition for the processText function
                // the following line of code is closer to
                // status = processText(fin, b, false);
                status = processText(fin, tree, false);
            }
            else { cout << "Failed to open the file" << endl; }

            fin.close();

            if (!status) return false;
        }

        // Commands of AVL
        // Command == add
        if (command == "add")
        {

            if (tkn.readWord(name))
            {
                if(!tree.insert(name))
                    cout << name << " already exists in the AVL" << endl;
            }

            continue;

        }

        // Command == remove
        if (command == "remove")
        {
            tkn.readWord(name);
            name = tree.fixVal(name);

            if(!tree.remove(name))
            {
                cout << name << " doesn't exists in the AVL" << endl;
            }
            else
                cout << name << " has been removed from the AVL of PCs" << endl;

            continue;
        }

        // Command == set
        if (command == "set")
        {
            tkn.readWord(name);
            name = tree.fixVal(name);
            tkn.readWord(stat);
            stat = tree.fixVal(stat);

                if (stat == "Job" || stat == "Race")
                {
                    tkn.readWord(val);
                    val = tree.fixVal(val);

                    // If name DNE, prompt to create a new one
                    if (!tree.updateStat(name, stat, val))
                        impromptPC(tree, name, stat, val);

                }else if (stat == "Level")
                {
                    if (!tkn.readInteger(valNum))
                        cout << "Expected an integer to update level...\n"
                                "Try inputting the command again" << endl;

                    // If name DNE, prompt to create new PC
                    if(!tree.updateStat(name, valNum))
                        impromptPC(tree, name, valNum);

                }else // invalid parameter for stat
                {
                    cout << "Unable to determine what stat to update...\n"
                            "Retype the command from scratch... " << endl;

                }

            continue;
        }

        // Command == search
        if (command == "search")
        {
            tkn.readWord(stat);
            stat = tree.fixVal(stat);

            if (stat == "Job" || stat == "Race") // display job/race matches
            {
                tkn.readWord(val);
                val = tree.fixVal(val);
                tree.scanTree(stat, val);
            }
            else if (stat == "Level") // display level matches
            {
                if (!tkn.readInteger(valNum)) // invalid input for level
                {
                    cout << "Invalid argument for updating the PC's Level..." << endl;
                    continue;
                }
                else
                    tree.scanTree(valNum);
            }

            continue;
        }

        // Command == display
        if (command == "display")
        {
            if (!tree.peek())
            {
                cout << "There aren't any players in the database..." << endl;
                continue;
            }

            tkn.readWord(name);

            if(name == "inorder")
            tree.inOrder(cout);
            else if (name == "preorder")
            tree.preOrder(cout);
            else if (name == "postorder")
            tree.postOrder(cout);
            else
            cout << "What order did you want to print the tree? \n"
                    "Check your spelling on the next iteration..." << endl;

            continue;
        }else
        {
            cout << "Invalid command input, try again buckaroo... \n";
        }

    }


}

