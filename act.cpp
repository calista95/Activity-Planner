/* Program: act.cpp
 * Description: This program reads from an act.txt file and generates the best activity scheduling based on start and end times of activities.
 * Name: Calista Wong
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

struct Set
        {
                int number;
                int start;
                int end;
        };


/****Reference: https://www.geeksforgeeks.org/insertion-sort/ ****/
/**Recycled from HW1**/
/**sort based on last activity**/
void insertSort(vector<Set>&set)
{
        for (int i=1; i<set.size(); i++)
        {
                int key = set[i].start; //key is the value that we are looking at, initialize it to the second value of the array
                int j= i-1; //j is the value we are comparing key to, initialize it to one less than key

                while (j>=0 && set[j].start >key) //if the value of myArray[j] is greater than the key and is a valid array value
                                {
                                        int temp1= set[j+1].number;
                                        int temp2= set[j+1].start;
                                        int temp3= set[j+1].end;
                                        set[j+1].number = set[j].number;   //move it one position ahead of its current position
                                        set[j+1].start = set[j].start;
                                        set[j+1].end = set[j].end;
                                        set[j].number= temp1;
                                        set[j].start=temp2;
                                        set[j].end=temp3;
                                        j=j-1; //decrement it to look at the one below
                                }
                set[j+1].start=key;
        }
}





/*Function that determines optimal activity order
 * Input:
 * Output:
*/
void activitySelector(vector<Set> sets)
        {

                vector<Set> collection;

                /*
                cout << "Before sort: " << endl;
                for (int i=0; i<sets.size(); i++)
                {
                        cout << sets[i].number<< " ";
                        cout << sets[i].start<< " ";
                        cout << sets[i].end << endl;
                }
                */

                //sort by start time
                insertSort(sets);

                /*
                cout << "After sort: " << endl;
                for (int i=sets.size()-1; i>=0; i--)
                {
                        cout << sets[i].number << " ";
  			cout << sets[i].start << " ";
                        cout << sets[i].end << endl;
                }
                cout << endl;
                */

                int lastStart = sets.size()-1;

                //select last activity from sorted array and put in collection
                collection.push_back(sets[lastStart]);
                //initialize the last added element
                Set lastAdded =  sets[lastStart];

                for (int i=lastStart-1; i>=0; i--)
                {
                        //if end time of element is less or equal to start time of last added element
                        if (sets[i].end <= lastAdded.start)
                               {
                                       //push it to the list
                                       collection.push_back(sets[i]);
                                       //update lastAdded
                                       lastAdded = sets[i];
                               }
                }

                cout << "Number of activities selected: " << collection.size() << endl;
                cout << "Activities: " ;

                //display collection
                for (int i=collection.size()-1; i>=0; i--)
                {
                        cout << collection[i].number << " ";
                        //cout << collection[i].start << " " ;
                        //cout << collection[i].end << " ";
                        //cout << endl;
                }
                cout << endl;

        }


int main()
{
        ifstream infile;
        infile.open("act.txt");
        if (!infile)
                {
                        cout << "File not found." << endl;
                }
        else
        {
                //determine how many activities we have
                string str;
                vector<int> result;

                int numSet;
                while (getline(infile, str))
                                {
					//cout << str << endl;
					//cout << "length: " << str.length() << endl;
                                        if (str.length() <4)
                                        {
                                                numSet++;
                                                //store as integer vector
                                                istringstream iss(str);
                                                for (string s; iss>>s;)
                                                {
                                                        stringstream geek(s);
                                                        int x=0;
                                                        geek >> x;
                                                        result.push_back(x);
                                                }
                                        }
                                }

                cout << numSet << " sets found" << endl;
                //cout << "Set " << numSet << ":" << endl;

    		//rewind
                infile.clear(); //rewind file
                infile.seekg(0);


                int numAct;
                vector<Set>temp;
                //Set *temp;
                for (int i=0; i<result.size(); i++)
                        {
                                cout << "Set " << i+1 << ":" << endl;
                                //cout << "Set of " << result[i] << ": " << endl;
                                numAct = result[i];

                                for (int j=0; j<numAct+1; j++)
                                {
                                        getline(infile, str);
                                        Set newset;
                                        if (str.length() >3)
                                        {
                                                istringstream iss(str);
                                                int count;
                                                count=1;
                                                for(string s; iss >> s;)
                                                {
                                                        //convert into integer
                                                        stringstream geek(s);
                                                        int x=1;
                                                        geek >>x;
                                                        //store into appropriate struct
                                                        if (count ==1)
                                                        {
                                                                newset.number=x;
                                                                count++;
                                                        }
                                                        else if (count ==2)
                                                        {
                                                                newset.start=x;
                                                                count++;
                                                        }
                                                        else if (count ==3)
                                                        {
                                                                newset.end=x;
                                                                count=1;
                                                        }
                                                }

                                                //add to vector
                                                temp.push_back(newset);
                                        }
                                }
                                //print out vector contents
                                /*
                                for (int k=0; k<numAct; k++)
                                {
                                        cout << temp[k].number << " ";
                                        cout << temp[k].start << " ";
                                        cout << temp[k].end << endl;
                                }
                                */
                                //send to function to determine best order
                                activitySelector(temp);
                                //clear the vector
                                temp.clear();
                        }
        }

        infile.close();
        return 0;
}
