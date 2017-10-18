// ---------------------------------------------------------------------------
// Sort student data (by their last names). 
// Display a list of students using an insertion sort to standard output.
// Data includes last name, first name, and a grade.  For example:
//
// duck donald 65
// mouse mickey 73
// frog freddie 60
//
// Assumptions:  
//    -- Format of data is correct.
//    -- All names are no more in length than MAXLENGTH.
//    -- gradess are correctly sized as integers.
//    -- Data beyond MAXSIZE number of names is not in the list. 

#include <string.h>                 //if needed
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

int const MAXSIZE = 100;            // maximum number of records in total
int const MAXLENGTH = 31;           // maximum string length 
int const MAXGRADE = 100;           // highest possible grade
int const LOWGRADE = 0;             // lowest possible grade
int const GROUP = 10;               // group amount
int const HISTOGRAMSIZE = (MAXGRADE-LOWGRADE)/GROUP + 1;   // grouped by GROUP

struct StudentType  {               // information of one student
   int grade;                       // the grade of the student
   char last[MAXLENGTH];            // last name (MAXLENGTH-1 at most)
   char first[MAXLENGTH];           // first name (MAXLENGTH-1 at most)
};

//----------------------------------------------------------------------------
// function prototypes 
bool sortInput(ifstream &, StudentType [], int &);
void displayList(StudentType [], int);
void setHistogram(int [], StudentType [], int);
void displayHistogram(int []);
int findAverage(StudentType s[], int);

//----------------------------------------------------------------------------

int main()  {
   StudentType students[MAXSIZE];   // list of MAXSIZE number of students
   int size = 0;                    // total number of students
   int histogram[HISTOGRAMSIZE];    // grades grouped by GROUP
   int average = 0;                 // average exam score, truncated

   // creates file object and opens the data file
   ifstream infile;
   infile.open("data1.txt");
   if (!infile)  { 
      cout << "File could not be opened." << endl; 
      return 1;  
   }

   // read and sort input by last then first name
   bool successfulRead = sortInput(infile, students, size);

   // display list, histogram, and class average 
   if (successfulRead)  {
      displayList(students, size);
      setHistogram(histogram, students, size);
      displayHistogram(histogram);
      average = findAverage(students, size);
      cout << "Average grade: " << average << endl << endl;
   }
   return 0;
}

// ---------------------------------------------------------------------------
//sortInpt
//read the data from a file (the first parameter) for one class of students  
// and place into array (second parameter), sorted into ascending order by the 
//last name; the third parameter, size, is the number of items in the array, 
//always less than the maximum size, MAXSIZE.
//Algorithm reads a line of data into a temporary location of type StudentType
//and inserts it into its correct position in the array. Reading and sorting 
//happen at the same time.

bool sortInput (ifstream &infile, StudentType students [], int &x)  { 
   int j;                    //insertion index
   StudentType temp;         //temporary location for student names and grades
   
   //infinite loop to read and handle each line of data
   for(;;)  {
      infile >> temp.last;
	  if (x > MAXSIZE || infile.eof())
	{
			  cout << "File is empty!" << endl;
			  return false;
	  }
	  infile >> temp.first >> temp.grade;    
	  //only insert the students with grades not lower than LOWGRADE and not
	  //higher than MAXGRADE
	  if (temp.grade >= LOWGRADE && temp.grade <= MAXGRADE)  {
         for (j = (x-1); j >= 0; j--)  {
		    if (strcmp(temp.last, students[j].last) < 0)  {
			   students[j+1] = students[j];
			   students[j] = temp;
		    }
		    else if ((strcmp(temp.last, students[j].last) == 0) && 
				    (strcmp(temp.first, students[j].first) < 0))  {
			   students[j+1] = students[j];
			   students[j] = temp;
		    }
		    else  {
			   students[j+1] = temp;
			   break;
		    }
         }
		 students[j+1] = temp;
	     x++;
	  }
   }
   return true;
}

//----------------------------------------------------------------------------
//displayList
//displays a sorted list of students

void displayList (StudentType students[], int size)  {
   cout << "List of names sorted:" << endl;
   for (int i = 0; i < size; i++)  {
      cout << setw(3) << students[i].grade << " " << students[i].last << " " 
		   << students[i].first << endl;
   }
   cout << endl;
}

//----------------------------------------------------------------------------
//setHistogram
//fills in the array "histogram" with the proper number of needed asterixes 
//based on the students data. For example, if 2 students have a grade in the
//range from 70 to 79, then the arry will store "2" at 7. 

void setHistogram (int histogram[], StudentType students[], int size)  {
   for (int j = 0; j < HISTOGRAMSIZE; j++)  {
      histogram[j] = 0;           //filling up the histogram array with zeroes
   }
   int x;
   for (int i = 0; i < size; i++)  {
      x = students[i].grade/GROUP;
	  ++histogram[x];
   }
}

//----------------------------------------------------------------------------
//displayHistogram
//displays a histogram of students' grades in the required by the assignment
//format

void displayHistogram (int histogram[])  {
   cout << "Histogram of grades:" << endl;
   for (int i = 0; i < HISTOGRAMSIZE; i++)  {
      cout << setw(3) <<  i * GROUP << "-->" << setw(4) 
		   << min(((i * GROUP) + 9), MAXGRADE) << ": " ;
      for (int j = 0; j < histogram[i]; j++)  {
         cout << "*";
      }
      cout << endl;
   }
   cout << endl;
}

//----------------------------------------------------------------------------
//findAverage
//calculates the average grade of all students in the list and returns it

int findAverage (StudentType students [], int size)  {
   int sum = 0;                     //sums up all the grades
   for (int i = 0; i < size; i++)  {
      sum += students[i].grade;
   }
   return sum / size;
}
