//  CSC 125 - Online
//  nwilliams59_Project1.cpp
//  Author: Nick Williams on 2/21/15.
//  Description:
//          This Program manages a List of Books either saved to file or entered manually by a user.

#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

const int MAXARRAY = 10;

ifstream in_stream;
ofstream out_stream;

struct Book_Detail
{
    string title = " ";
    int page_count = 0;
    int review = 0;
    float price = 0.00;
} book[MAXARRAY];

void main_menu(); //Displays Main Menu
void display_books(Book_Detail book[], int); //Displays Currently Loaded Array of Books
void display_titles(Book_Detail book[], int); //Displays Choices for Deletion Function
void find_book(Book_Detail book[], int); //Finds a Book By Title
void add_book(Book_Detail book[], int); //Adds a Book to Array if Slot Available
void delete_book(Book_Detail book[], int); //Deletes a Book from Array and Closes Gap
void save_list(ostream&, Book_Detail book[], int); //Saves Books to Text File
void load_list(istream&, Book_Detail book[]); //Loads Books from Text File into Book Array
void sort_list(Book_Detail book[], int); //Sorts Books by User Criteria
void sorting_options(); //Displays Sorting Criteria
string print_stars(int); //Converts Numerical Review Rating into Stars and Displays
string capitalize(string); //Converts Strings to Uppercase for comparison
int size_of_array(Book_Detail book[]); //Determines number of elements in array of Books

int main(int argc, const char * argv[]) {
   
    int user_selection = 0;
    
    do
    {
        int size = size_of_array(book); //Finds Number of Books Entered
        
        main_menu(); //Displays Main Menu
        
        cin >> user_selection;
        
        //Throws an error if alpha char or out-of-range entered
        while ((!cin) || (user_selection < 1) || (user_selection > 8))
        {
            cin.clear();
            cin.ignore();
            cout << "Please enter specifically 1 - 8: ";
            
            cin >> user_selection;
        }
        
        switch (user_selection)
        {
            case 1: //Display Books
            {
                display_books(book, size);
                break;
            }
            case 2: //Find Book
            {
                find_book(book, size);
                break;
            }
            case 3: //Add Book
            {
                add_book(book, size);
                break;
            }
            case 4: //Delete Book
            {
                delete_book(book, size);
                break;
            }
            case 5: //Save List
            {
                out_stream.open("books.txt");
                if (out_stream.fail())
                {
                    cout << "File Opening Failed\n";
                    break;
                }
                
                save_list(out_stream, book, size);
                
                out_stream.close();
                
                cout << "List Saved!\n\n";
                cout << "Press Enter to Return to Main Menu\n";
                
                cin.get();
                cin.ignore();
                
                break;
            }
            case 6: //Load List
            {
                in_stream.open("books.txt");
                if (in_stream.fail())
                {
                    cout << "File Does Not Exist\n" << endl;
                    cout << "Returning to Main Menu\n" << endl;
                    break;
                }
                
                load_list(in_stream, book);
                
                in_stream.close();
                
                cout << "List Loaded!\n\n";
                cout << "Press Enter to Return to Main Menu\n";
                
                cin.get();
                cin.ignore();
                
                break;
            }
            case 7: //Sort List
            {
                sort_list(book, size);
                break;
            }
            case 8: //Quit
                break;
            default:
                break;
        }
    } while (user_selection != 8);
    
    return 0;
}

void main_menu()
{
    cout << "MAIN MENU\n\n";
    cout << "Please Make a Selection by Entering the Numerical Value that\n";
    cout << "Corresponds to the Option You Would Like to Choose (1 - 8).\n\n";
    cout << "1 - Display a List of Books\n";
    cout << "2 - Find a Book\n";
    cout << "3 - Add a New Book\n";
    cout << "4 - Delete a Book\n";
    cout << "5 - Save Book List to File\n";
    cout << "6 - Load Book List from File\n";
    cout << "7 - Sort List of Books\n";
    cout << "8 - QUIT\n\n";
    cout << "Your Selection: ";
}

//Displays all Books currently loaded into Book Array
void display_books(Book_Detail book[], int size)
{
    if (size == 0) //If no Books are in the Array
    {
        cout << "\nNo Books have been Entered!\n";
    }
    else
    {
        //Header Bar to Display Categories
        cout << setw(20) << left << "Title";
        cout << setw(8) << left << "Pages";
        cout << setw(8) << left << "Stars";
        cout << setw(8) << right << "Price\n";
        
        for (int i = 0; i < size; i++)
        {
            int star_count = book[i].review; //Retrieves number for star symbol conversion
            
            cout << setw(20) << left << book[i].title;
            cout << setw(8) << left << book[i].page_count;
            cout << setw(8) << left << print_stars(star_count);
            cout << setw(8) << right << book[i].price << endl;
        }

    }
    
    cout << endl;
    cout << "Press Enter to Return to Main Menu\n";
    
    cin.get();
    cin.ignore();
}

//Converts Review Number into Stars and Displays
string print_stars(int number_stars)
{
    string star_count = "";
    
    for (int j = 1; j <= number_stars; j++)
    {
        star_count += "*";
    }
    
    return star_count;
}

//Determines Number of Elements in Book Array
int size_of_array(Book_Detail book[])
{
    int total_books = 0;
    
    
    while ((book[total_books].title != " ") && (total_books < MAXARRAY))
    {
        total_books++;
    }
    
    return total_books;
}

//Searches for Book by Title
void find_book(Book_Detail book[], int size)
{
    string criteria = "";
    int match_count = 0;
    
    if (size == 0)
    {
        cout << "\nNo Books have been Entered!\n";
    }
    else
    {
        cout << "FIND A BOOK BY TITLE\n\n";
        cout << "Search Criteria: ";
        
        cin >> criteria;
        cout << "Searching for: " << criteria << endl << endl;
        
        cout << "Results:\n";
        
        for (int i = 0; i < size; i++)
        {
            bool is_complete_match = false;
            
            //If a complete match is found, the result does not show in partial match list
            if (capitalize(book[i].title) == capitalize(criteria))
            {
                int star_count = book[i].review;
                
                cout << "Complete Match Found:\n";
                cout << setw(20) << left << book[i].title;
                cout << setw(8) << left << book[i].page_count;
                cout << setw(8) << left << print_stars(star_count);
                cout << setw(8) << right << book[i].price << endl;
                
                match_count++;
                is_complete_match = true;
            }
            
            if ((capitalize(book[i].title).find(capitalize(criteria)) != string::npos) &&
                (is_complete_match == false))
            {
                int star_count = book[i].review;
                
                cout << "Partial Match Found:\n";
                cout << setw(20) << left << book[i].title;
                cout << setw(8) << left << book[i].page_count;
                cout << setw(8) << left << print_stars(star_count);
                cout << setw(8) << right << book[i].price << endl;
                
                match_count++;
            }
        }
        
        if (match_count == 0)
        {
            cout << "No Matches Found!\n\n";
        }
    }
    
    cout << endl;
    cout << "Press Enter to Return to Main Menu\n";
    
    cin.get();
    cin.ignore();
}

//Converts Title to Uppercase for comparison function
string capitalize(string title)
{
    string capitalized = "";
    
    for (int i = 0; i < title.size(); i++)
    {
        capitalized += toupper(title[i]);
    }
    
    return capitalized;
}

//Adds Book Details to end of Book Array
void add_book(Book_Detail book[], int size)
{
    cout << "ADD BOOK\n\n";
    
    if (size < MAXARRAY)
    {
        string temp_title;
        
        cout << "Please Enter the Book Details...\n\n";
        cout << "Title: ";
        cin >> temp_title;
        
        //Compares to see if Book has already been entered before moving on
        for (int i = 0; i < size; i++)
        {
            while (capitalize(book[i].title) == capitalize(temp_title))
            {
                cout << "That Title has Already Been Entered\n\nTitle: ";
                cin.clear();
                cin.ignore();
                cin >> temp_title;
            }
        }
        
        book[size].title = temp_title;
        cout << "Number of Pages: ";
        cin >> book[size].page_count;
        cout << "Star Rating (0 - 5): ";
        cin >> book[size].review;
        cout << "Price: $";
        cin >> book[size].price;
        cout << "Book Added!\n\n";
    }
    else
    {
        cout << "The Maximum Number of Books Have Been Added.\n\n";
    }
    
    cout << endl;
    cout << "Press Enter to Return to Main Menu\n";
    
    cin.get();
    cin.ignore();
}

//Deletes Book Details from Book Array
void delete_book(Book_Detail book[], int size)
{
    if (size == 0)
    {
        cout << "\nNo Books have been Entered!\n";
    }
    else
    {
        string delete_title;
        bool match = false; //Sets Default value to run While Loop at least once
        int match_location = 0;
        Book_Detail temp;
        
        cout << "DELETE BOOK\n\n";
        cout << "Please Enter the Title to Delete.\n\n";
        cout << "Title: ";
        cin >> delete_title;
        
        //Test to Determine if Book Exists for Deletion
        while (match == false)
        {
            for (int i = 0; i < size; i++)
            {
                if (capitalize(book[i].title) == capitalize(delete_title))
                {
                    match = true;
                    match_location = i;
                }
            }
            
            //If Book Does not Exist, All of the current books are listed for easier selection
            if (match == false)
            {
                cout << "That Title has Does Not Exist\n\n";
                display_titles(book, size); //Displays Current List
                cout << "Title to Delete: ";
                cin.clear();
                cin.ignore();
                cin >> delete_title;
            }
        }
        
        //Closes Gap in Array
        if (match == true)
        {
            for (int i = match_location; i < size; i++)
            {
                temp = book[i+1];
                book[i] = temp;
            }
            
            cout << "Book Deleted!\n\n";
        }
    }
    
    cout << endl;
    cout << "Press Enter to Return to Main Menu\n";
    
    cin.get();
    cin.ignore();
}

//Displays List of Current Book Titles for Deletion after "Does not Exist" error
void display_titles(Book_Detail book[], int size)
{
    cout << "Title Choices\n";
    
    for (int i = 0; i < size; i++)
    {
        cout << book[i].title << endl;
    }
    
    cout << endl;
}

//Saves Book Details to Text File
void save_list(ostream& out_stream, Book_Detail book[], int size)
{
    out_stream << "Number of Books: " << size << endl;
    
    for (int i = 0; i < size; i++)
    {
        out_stream << book[i].title << " ";
        out_stream << book[i].page_count << " ";
        out_stream << book[i].review << " ";
        out_stream << book[i].price << endl;
    }
}

//Loads Book Details From Text File
void load_list(istream& out_stream, Book_Detail book[])
{
    string book_qty_dump = " ";
    
    //Discards Top Line Consisting of Number of Books in List
    getline(in_stream, book_qty_dump);
    
    while (!in_stream.eof())
    {
        for (int i = 0; i < MAXARRAY; i++)
        {
            in_stream >> book[i].title;
            in_stream >> book[i].page_count;
            in_stream >> book[i].review;
            in_stream >> book[i].price;
        }
    }
}

//Massive Book Detail Sorting Options
void sort_list(Book_Detail book[], int size)
{
    int selection = 0;
    bool ascend = true;
    
    
    
    
    //NOTE: I began the code to provide an option for
    //      Ascending/Descending Order, as shown below.
    //      Unfortunately for me, I ran out of time
    //      for its complete implementation.
    
    
    
    
    
    if (size == 0)
    {
        cout << "\nNo Books have been Entered!\n";
    }
    else
    {
        cout << "SORT LIST\n\n";
        
        //Displays Criteria for Sorting
        sorting_options();
        
        cin >> selection;
        
        //Throws an error if alpha char or out-of-range entered
        while ((!cin) || (selection < 1) || (selection > 4))
        {
            cin.clear();
            cin.ignore();
            cout << "Please enter specifically 1 - 4: ";
            
            cin >> selection;
        }
        
        switch (selection)
        {
            case 1: //By Title
            {
                if (ascend == true)
                {
                    for (int i = 1; i < size; i++)
                    {
                        for (int j = 0; j < size - i; j++)
                        {
                            if (book[j].title > book[j+1].title)
                            {
                                Book_Detail temp = book[j];
                                book[j] = book[j+1];
                                book[j+1] = temp;
                            }
                        }
                    }
                }
                else
                {
                    for (int i = 1; i < size; i++)
                    {
                        for (int j = 0; j < size - i; j++)
                        {
                            if (book[j].title < book[j+1].title)
                            {
                                Book_Detail temp = book[j];
                                book[j] = book[j+1];
                                book[j+1] = temp;
                            }
                        }
                    }
                }
                
                break;
            }
            case 2: //By Page Count
            {
                if (ascend == true)
                {
                    for (int i = 1; i < size; i++)
                    {
                        for (int j = 0; j < size - i; j++)
                        {
                            if (book[j].page_count > book[j+1].page_count)
                            {
                                Book_Detail temp = book[j];
                                book[j] = book[j+1];
                                book[j+1] = temp;
                            }
                        }
                    }
                }
                else
                {
                    for (int i = 1; i < size; i++)
                    {
                        for (int j = 0; j < size - i; j++)
                        {
                            if (book[j].page_count < book[j+1].page_count)
                            {
                                Book_Detail temp = book[j];
                                book[j] = book[j+1];
                                book[j+1] = temp;
                            }
                        }
                    }
                }
                
                break;
            }
            case 3: //By Review
            {
                if (ascend == true)
                {
                    for (int i = 1; i < size; i++)
                    {
                        for (int j = 0; j < size - i; j++)
                        {
                            if (book[j].review > book[j+1].review)
                            {
                                Book_Detail temp = book[j];
                                book[j] = book[j+1];
                                book[j+1] = temp;
                            }
                        }
                    }
                }
                else
                {
                    for (int i = 1; i < size; i++)
                    {
                        for (int j = 0; j < size - i; j++)
                        {
                            if (book[j].review < book[j+1].review)
                            {
                                Book_Detail temp = book[j];
                                book[j] = book[j+1];
                                book[j+1] = temp;
                            }
                        }
                    }
                }
                
                break;
            }
            case 4: //By Price
            {
                if (ascend == true)
                {
                    for (int i = 1; i < size; i++)
                    {
                        for (int j = 0; j < size - i; j++)
                        {
                            if (book[j].price > book[j+1].price)
                            {
                                Book_Detail temp = book[j];
                                book[j] = book[j+1];
                                book[j+1] = temp;
                            }
                        }
                    }
                }
                else
                {
                    for (int i = 1; i < size; i++)
                    {
                        for (int j = 0; j < size - i; j++)
                        {
                            if (book[j].price < book[j+1].price)
                            {
                                Book_Detail temp = book[j];
                                book[j] = book[j+1];
                                book[j+1] = temp;
                            }
                        }
                    }
                }
                
                break;
            }
            default:
                break;
        }
        
        cout << "Sorted!\n\n";
        cout << "Press Enter to Return to Main Menu\n";
        
        cin.get();
        cin.ignore();
    }
}

//Displays Sub Menu showing sorting option selection
void sorting_options()
{
    cout << "How Would You Like To Sort?\n";
    cout << "Please Make a Selection by Entering the Numerical Value that\n";
    cout << "Corresponds to the Option You Would Like to Choose (1 - 4).\n\n";
    cout << "1 - By Title\n";
    cout << "2 - By Page Count\n";
    cout << "3 - By Review\n";
    cout << "4 - By Price\n\n";
    cout << "Your Selection: ";
}