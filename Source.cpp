// ----------------------------------------------------------------------------
// You write meaningful overview comments and assumptions here

#include <string.h>
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

int const MAXSIZE = 100;            // maximum number of records in total
int const MAXLENGTH = 31;           // maximum string length 
int const MAXGRADE = 100;           // highest possible grade
int const LOWGRADE = 0;             // lowest possible grade
int const GROUP = 10;               // group amount
int const HISTOGRAMSIZE = (MAXGRADE-LOWGRADE)/GROUP + 1;    // grouped by GROUP

struct StudentType  {               // information of one student
   int grade;                       // the grade of the student
   char last[MAXLENGTH];            // last name (MAXLENGTH-1 at most)
   char first[MAXLENGTH];           // first name (MAXLENGTH-1 at most)
};

// prototypes go here   

   
   void displayList(StudentType [], int);
bool sortInput (ifstream &infile, StudentType students [], int &x)
{
	int j;
	StudentType temp;
	//int x = 0;
	//infile >> temp.last >> temp.first >> temp.grade;
    while(!infile.eof())
   {
      infile >> temp.last >> temp.first >> temp.grade;
	  strcpy(students[x].last, temp.last);
      strcpy(students[x].first, temp.first);
      students[x].grade = temp.grade;
      
      cout << "TEST" << temp.last << temp.first << temp.grade << endl;
	  x++;
	}

   for(int i = 1; i < x; i++)
  {      
	 temp = students[i];
	 j = i;
	 while (j>0)  
	 {
		 if(strcmp(temp.last,students[j-1].last)<0){
			 students[j] = students[j-1];
			 j--;
		 }
		 else if ((strcmp(temp.last, students[j-1].last) == 0) && (strcmp(temp.first, students[j-1].first) < 0))
		 {
			 students[j] = students[j-1];
			 j--;
		 }
		 else 
		 {
			 students[j] = temp;
			 break;
		 }
		 students[j] = temp;

  }
   }
      cout << "Size = " << x<< " and copy position = " << j << endl;
      //students[j] = temp;
      //size++;

      //test to see if array is populated properly
      for(int i = 0; i < x; i++)
      {
         cout << "Name is " << students[i].first << " " << students[i].last << " and grade is " << students[i].grade << endl;
      }

      cout << "DONE" << endl;

    //end while loop

   return true;
}
//-----------------------------------------------------------------------------
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
      /*setHistogram(... you figure parameters ...);
      displayHistogram(... you figure parameters ...);
      average = findAverage(... you figure parameters ...);
      cout << "Average grade: " << average << endl << endl;*/
   }
   //return 0;
}

// ----------------------------------------------------------------------------


void displayList(StudentType students[], int size)
{
   cout << "List of names sorted:" << endl;

   for(int i = 0; i < size; i++)
   {
	   if(students[i].grade>0 && students[i].grade<=100)
      cout << " " << students[i].grade << " " << students[i].last << " " << students[i].first << endl;
   }
}

// You must put a separator line between every function
// Then comes the name of the function on a separate comment line
// Then comes the function comment. Clearly comment every function.
// Use bubble.cpp as a guide.
