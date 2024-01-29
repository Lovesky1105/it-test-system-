#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
#include <fstream> //To generate file
#include <algorithm>
#include <stdlib.h>

using namespace std;

//Declare a constant value to store 100 questions
const int SIZE = 100; //Only can store 100 questions

//Record type
struct Questions{
	string questionText;
	string answerA;
	string answerB;
	string answerC;
	string answerD;
	char actualAnswer;
};

struct Answers{
	string refNo;
	string date;
	string name;
	string ans[10];	//Use string array to store the answer
	int total_correct;
	int percentage;
	string result;
};

//Function prototypes
void showMenu(); 			//Display main menu
int getOption(string); 		//Let user enter a choice
void showSubMenu();			//Display question banks menu
void addQuestion(Questions [], int &); 		//Add question
void editQuestion(Questions [], int); 		//Edit question
void deleteQuestion(Questions [], int &); 	//Delete question
void viewAllQuestion(Questions [], int); 	//View all question
void saveQuestion(Questions [], int); 		//Save question to file
void startTest(Answers [], int &); 			//Start the test
void saveAnswer(Answers [], int ); 			//Save test result into file
void viewHistory(Answers [], int ); 		//View back past result

int main() {
	
	//Declare & initialise the variables to a default value
	int sub_menu_option = 0;	//User picks an option
	int option = 0;				//User picks an option
	int num = 0; 				//Existed question number
	Questions question[SIZE];	//Create 100 question records
	int ansNum = 0; 			//Existed test result number
	char ans;
	Answers answer[SIZE];		//Create 100 test results records
	
	fstream dataFile;		//Create file object
	char buffer[200];		//Used to store a line of questions
	
	//open the question file for reading
	dataFile.open("question.txt", ios::in);
	
	//checking on the file status
	if (dataFile.fail()){
		cout << "File open error" << endl;
        return 0; //End the program
	}
	
	//start loop the file untill eof (end of file)
	dataFile.getline(buffer,200); //read untill the next line 
	while (!dataFile.eof()){
		question[num].questionText = buffer;
		
		//read the next line 
		dataFile.getline(buffer,200);
		question[num].answerA = buffer;
		
		//read the next line 
		dataFile.getline(buffer,200);
		question[num].answerB = buffer;
		
		//read the next line 
		dataFile.getline(buffer,200);
		question[num].answerC = buffer;
		
		//read the next line 
		dataFile.getline(buffer,200);
		question[num].answerD = buffer;
		
		//read the next line 
		dataFile.getline(buffer,200);
		string temp = buffer;
		question[num].actualAnswer = temp.at(0);
		
		//read the next line 
		dataFile.getline(buffer,200);
		num++;
	}		
	//close the data file
	dataFile.close();
	
	//open the answer file for reading
	fstream answerFile;		//Create file object
	answerFile.open("answer.txt", ios::in);
	char ansbuffer[200];	//Used to store a line of test results

	//Checking on the file status
	if (answerFile.fail()) {
		cout << "Unable to open the answer.txt file." << endl;
		return 0;
	}

	//start loop the file untill eof(end of file)
	answerFile.getline(ansbuffer, 200); //read untill the next line 
	while (!answerFile.eof()) {
		answer[ansNum].refNo = ansbuffer;
		
		//read the next line 
		answerFile.getline(ansbuffer,200);
		answer[ansNum].date = ansbuffer;
		
		//read the next line 
		answerFile.getline(ansbuffer,200);
		answer[ansNum].name = ansbuffer;
		
		for (int i = 0; i < 10; i++) {
			answerFile.getline(ansbuffer,200);
    		answer[ansNum].ans[i] = ansbuffer;
		}
		
		//read the next line 
		answerFile.getline(ansbuffer,200);
		answer[ansNum].total_correct = atoi(ansbuffer);
		
		//read the next line 
		answerFile.getline(ansbuffer,200);
		answer[ansNum].percentage = atoi(ansbuffer);
		
		//read the next line 
		answerFile.getline(ansbuffer,200);
		answer[ansNum].result = ansbuffer;
		
		//read the next line 
		answerFile.getline(ansbuffer,200);
		answerFile.getline(ansbuffer,200); //read untill the next line 
		ansNum++;
	}
	
	answerFile.close(); //close the answer file
	
	do {
		showMenu();	//Show the main menu
		option = getOption ("Enter Your Choice: ");	//Prompt user to enter option
		cout << endl;
		
		//Process the user option
		switch(option) {
			
			//Question Banks
			case 1:
				do {
					showSubMenu();	//Show the question banks menu
					sub_menu_option = getOption ("Enter Your Choice: "); //Prompt user to enter option
					
				    switch (sub_menu_option){
				    	case 1 : //Add a question
				    		addQuestion(question, num);
				    		break;
				    	
				    	case 2 : //Edit question
				    		editQuestion(question, num);
				    	    break;
				    	    
				    	case 3 : //Delete question
				    		deleteQuestion(question, num);
				    		break;
				    		
				    	case 4: //View all question
				    		viewAllQuestion(question, num);
				    		break;
				    		
				    	case 5: //Save question into file and return to main menu
				    		saveQuestion(question, num);
				    		cout << endl;
				    		break;
				    	
				    	default :
				    		cout << "Invalid option! Please enter again...\n" << endl;
				    		break;
					}
				} while(sub_menu_option != 5);
				
				break;
				
			//Start Test
			case 2:
				startTest(answer, ansNum);
				break;
			
			//View Historical Results
			case 3:
				viewHistory(answer, ansNum);
				cout << endl;
				break;	
			
			//Exit
			case 4:
				cout << "Bye!" << endl;
				break;
				
			default:
				cout << "Invalid option! Please enter again...\n" << endl;			
				break;
		}
	
	} while (option != 4);
	
	return 0;
}

void viewHistory(Answers answer[], int ansNum)	{
	string refNo = "";
	int searchResult = -1; //-1 meant not found
	
	cin.ignore(100,'\n');
	
	//Prompt user to enter the reference no that need to search
	cout << "Enter Exam Reference No that want to search: A" ;
	getline(cin, refNo); //Get the user's input
	
	//Search the test result
	for (int i = 0; i < ansNum; i++) {
		if (answer[i].refNo == "A" + refNo) {			
			searchResult = i;
			break;
		}
	}
	
	if (searchResult != -1){
		cout << "\nThe existing exam result" << endl;
		cout << "--------------------------" << endl;
		cout << "ReferenceNo:" << answer[searchResult].refNo << endl;
	    cout << "Date:" << answer[searchResult].date << endl;
	    cout << "Name:" << answer[searchResult].name << endl;
	    
		for (int i = 0; i < 10; i++){
			cout << (i + 1) << ") " << answer[searchResult].ans[i] << endl;
		}
		
	    cout << "Total correct: " << answer[searchResult].total_correct << endl;
	    cout << "Percentage: " << answer[searchResult].percentage << "%"  << endl;
	    cout << "You " << answer[searchResult].result << endl;
	}
	else{
		cout << "\nRecord not found!\n" << endl;
	}
}

//Prompt users to start test
void startTest(Answers answer[], int &ansNum){
	int num = 0;				//Existed question number
	srand (time(0));			//Randomizes the rand function
	fstream dataFile;
	char buffer[200];			//Used to store a line of questions
	Questions question[SIZE];	//Create 100 questions records
	
	//open the question file for reading
	dataFile.open("question.txt", ios::in);
	
	//checking on the question file status
	if (dataFile.fail()){
		cout << "File open error" << endl;
		
        return;
	}
	
	//start loop the file untill eof(end of file)
	dataFile.getline(buffer,200); //read untill the next line 
	while (!dataFile.eof()){
		question[num].questionText = buffer;
		
		//read the next line 
		dataFile.getline(buffer,200);
		question[num].answerA = buffer;
		
		//read the next line 
		dataFile.getline(buffer,200);
		question[num].answerB = buffer;
		
		//read the next line 
		dataFile.getline(buffer,200);
		question[num].answerC = buffer;
		
		//read the next line 
		dataFile.getline(buffer,200);
		question[num].answerD = buffer;
		
		//read the next line 
		dataFile.getline(buffer,200);
		string temp = buffer;
		question[num].actualAnswer = temp.at(0);
		
		//read the next line 
		dataFile.getline(buffer,200);
		num++;
	}		
	//close the data file
	dataFile.close();	
	
	if (num < 10){
		cout << "Not enough 10 questions!! Please add at least 10 questions to start the test.\n" << endl;
        return;
	}
	
	int i = 0;
	string referenceNo = " ", username = " ", date = " ";
		
	//Prompt user to enter student reference no & date & name
	cout << "Enter Exam Reference No : A";
	cin >> referenceNo;
			
	cin.ignore();	//Remove the enter key in the keyboard buffer
				
	cout << "Date (MM/DD/YY) : ";
	getline(cin, date);
			
	cout << "Name : ";
	getline(cin, username);
				
	cout << "Start test...";
	cout << endl << endl;
				
	cout << "----------------------------------";
	cout << endl << endl;				
				
	answer[ansNum].refNo = "A" + referenceNo;
	answer[ansNum].date = date;
	answer[ansNum].name = username;
	
	string ans = " ";
	int totalCorrect = 0;
	int randNum[10];	//Generate 10 random number
	
	//Generate random question number without repetition and store in array
	for (int index = 0; index < 10; index++){
		bool repeat;
		
		do {
			randNum[index] = rand() % num;
			repeat = false;
			
			for (int k = 0; k < index; k++){
				
				if (randNum[index] == randNum[k]){
					repeat = true;
				}
			}
			
		} while(repeat);
	}
	
	//Display the question 	based on random number
	for (int j = 0; j < 10; j++) {	
		for (int i = 0; i < num; i++) {
			if (randNum[j] == i){
				cout << "Question " << (j + 1) << endl;
				cout << question[i].questionText << endl;
				cout << "A " << question[i].answerA << endl;
				cout << "B " << question[i].answerB << endl;
				cout << "C " << question[i].answerC << endl;
				cout << "D " << question[i].answerD << endl;    	
				
				do {
					cout << "Enter your answer (A, B, C or D): ";
					cin >> ans;
			   		
					cout << endl;
			   		
					if (ans != "A" && ans != "B" && ans != "C" && ans != "D") {
						cout << "Invalid answer! Enter again..." << endl;
					   }
					   
				} while (ans != "A" && ans != "B" && ans != "C" && ans != "D");
				
				//Convert char actual answer into string
				string temp(1, question[i].actualAnswer);
				string actualAns = temp;
				
				//Check the answer whether is it correct
				if (ans != actualAns) {
					answer[ansNum].ans[j] = ans + " (" + actualAns + ")";
				}	
				else {
					answer[ansNum].ans[j] = ans;
					
					totalCorrect += 1;
				}
			}
		}
	}
	
	int percentage = 0;
	percentage = totalCorrect * 10;
	
	answer[ansNum].total_correct = totalCorrect;
	answer[ansNum].percentage = percentage;
		
	if (percentage >= 50)
	{
		answer[ansNum].result = "Pass!\n";
	} 
	else {
		answer[ansNum].result = "Fail!\n";
	}
	
	cout << "Congratulations!! You have completed the test ! \n" <<endl;
	
	cout << "ReferenceNo:" << answer[ansNum].refNo << endl;
	cout << "Date:" << answer[ansNum].date << endl;
	cout << "Name:" << answer[ansNum].name << endl;
    
	for (int i = 0; i < 10; i++){
    	cout << (i + 1) << ") " << answer[ansNum].ans[i] << endl;
	}
	
    cout << "Total correct: " << answer[ansNum].total_correct << endl;
    cout << "Percentage: " << answer[ansNum].percentage << "%"  << endl;
    cout << "You " << answer[ansNum].result << endl;
    
    //Save the test result into file
    saveAnswer(answer, ansNum);
    
    ansNum++;
}

void saveAnswer(Answers answer[], int ansNum){
	fstream dataFile;	
	dataFile.open("answer.txt", ios::app); 

	//Check the answer file status
	if (dataFile.fail()){
		cout << "Unable to open the answer.txt file." << endl;
		return;
	}
	
	//Write the test results in the file
	dataFile << answer[ansNum].refNo << endl;
	dataFile << answer[ansNum].date << endl;
	dataFile << answer[ansNum].name << endl;
	
	for (int i = 0; i < 10; i++){
	    dataFile << (i + 1) << ") " << answer[ansNum].ans[i] << endl;
	}
	
	dataFile << answer[ansNum].total_correct << endl;
	dataFile << answer[ansNum].percentage << "%"  << endl;
	dataFile << answer[ansNum].result << endl;
	
	dataFile.close(); //Close the file
}

//Save the question records into file
void saveQuestion(Questions question[], int num){
	fstream dataFile;
    dataFile.open("question.txt", ios::out);
    
    //Check the question file status
	if (dataFile.fail()){
		cout << "Unable to open the question.txt file." << endl;
		return;
	}
    
	//Iterate the records and save to the file
	for (int i = 0; i<num; i++) {
		if(question[i].questionText != "")
	    	dataFile << question[i].questionText << endl;
	    
	    if(question[i].answerA != "")
	    	dataFile << question[i].answerA 	<< endl;
	    
	    if(question[i].answerB != "")
	    	dataFile << question[i].answerB 	<< endl;
	    
	    if(question[i].answerC != "")
	    	dataFile << question[i].answerC 	<< endl;
	    
	    if(question[i].answerD != "")
	    	dataFile << question[i].answerD 	<< endl;
	    
	    if(question[i].actualAnswer != '\0')
	    	dataFile << question[i].actualAnswer << endl;
	}
	
	dataFile.close(); //Close the file
}

void viewAllQuestion(Questions question[], int num){
	//Iterate the array and display all the question
	for (int i = 0; i < num; i++){
		if(question[i].questionText != "") {
			cout << "Question " << (i + 1) 		<< endl;
			cout << question[i].questionText 	<< endl;
			cout << "A " << question[i].answerA << endl;
			cout << "B " << question[i].answerB << endl;
			cout << "C " << question[i].answerC << endl;
			cout << "D " << question[i].answerD << endl;
			cout << "Actual Answer: " << question[i].actualAnswer << endl;
			cout << endl;		
		}
	}	
}

void deleteQuestion(Questions question[], int &num){
	string questext = "";
	int searchResult = -1; //-1 meant not found
	
	cin.ignore();	//Remove the enter key in the keyboard buffer
	
	cout << "Enter question text that want to delete: ";
	getline(cin, questext);
	
	//Search the question
	for (int i = 0; i < num; i++){
		if (question[i].questionText == questext){
			searchResult = i;
			break;
		}
	}
	
	//Display the question if the question exists
	if (searchResult != -1){
		cout << "\nThe existing question" << endl;
		cout << "---------------------" << endl;
		cout << "Question " << (searchResult + 1) 		<< endl;
		cout << question[searchResult].questionText 	<< endl;
		cout << "A " << question[searchResult].answerA 	<< endl;
		cout << "B " << question[searchResult].answerB 	<< endl;
		cout << "C " << question[searchResult].answerC 	<< endl;
		cout << "D " << question[searchResult].answerD 	<< endl;
		cout << "Actual Answer: " << question[searchResult].actualAnswer << endl;
		
		char confirm = '\0';
		cout << "Are you confirm to delete this question? [Y/N]: ";
		cin >> confirm;
		cout << endl;
		
		//Confirm to delete the question
		if (confirm == 'Y' || confirm == 'y'){
			for (int i = searchResult; i < num; i++){
		    	question[i] = question[i+1];	
			}
			cout << "The question deleted successfully!\n" << endl ;
		}
		else{
			cout << "Delete aborted!\n" << endl;
		}
	}
	else{
		cout << "\nRecord not found!\n" << endl;
	}
}

void editQuestion(Questions question[], int num){
	string questext = "";
	int searchResult = -1; //-1 meant not found
	
	cin.ignore();
	
	cout << "Enter question text that want to edit: ";
	getline(cin, questext);
	
	//Search the question
	for (int i = 0; i < num; i++){
		if (question[i].questionText == questext){
			searchResult = i;
			break;
		}
	}
	
	//Display the question if it exists
	if (searchResult != -1){
		cout << "\nThe existing question" << endl;
		cout << "---------------------" << endl;
		cout << "Question " << (searchResult + 1) 		<< endl;
		cout << question[searchResult].questionText 	<< endl;
		cout << "A " << question[searchResult].answerA 	<< endl;
		cout << "B " << question[searchResult].answerB 	<< endl;
		cout << "C " << question[searchResult].answerC 	<< endl;
		cout << "D " << question[searchResult].answerD 	<< endl;
		cout << "Actual Answer: " << question[searchResult].actualAnswer << endl;
		
		//Display the menu for user to choose which detail to edit
		cout << "\n1. Question Text" << endl;
		cout << "2. Answer A" 		<< endl;
		cout << "3. Answer B" 		<< endl;
		cout << "4. Answer C" 		<< endl;
		cout << "5. Answer D" 		<< endl;
		cout << "6. Actual Answer" 	<< endl;
		
		string newQuesText = "", newAnsA = "", newAnsB = "", newAnsC = "", newAnsD = "";
		char newActualAns = '\0';
		int item = 0;
		
		//Repeat if invalid option is entered
		do{
			cout << "Please choose which item that want to edit: ";
		    cin >> item;
		
		    cin.ignore(100,'\n');
		
			switch(item){
			case 1: //Edit the question text
			        cout << "\nEnter new Question Text: ";
					getline(cin, newQuesText);
					
					question[searchResult].questionText = newQuesText;
					cout << "\nThe question edit successfully!\n" << endl;
			        break;
			        
			case 2: //Edit the Answer A
			        cout << "\nEnter new Answer A: ";
					getline(cin, newAnsA);
					
					question[searchResult].answerA = newAnsA;
					cout << "\nThe question edit successfully!\n" << endl;
			        break;
			        
			case 3: //Edit the Answer B
			        cout << "\nEnter new Answer B: ";
					getline(cin, newAnsB);
					
					question[searchResult].answerB = newAnsB;
					cout << "\nThe question edit successfully!\n" << endl;
			        break;
			        
			case 4: //Edit the Answer C
			        cout << "\nEnter new Answer C: ";
			    	getline(cin, newAnsC);
			    	
			    	question[searchResult].answerC = newAnsC;
					cout << "\nThe question edit successfully!\n" << endl;
			        break;
			        
			case 5: //Edit the Answer D
			        cout << "\nEnter new Answer D: ";
			    	getline(cin, newAnsD);
			    	
			    	question[searchResult].answerD = newAnsD;
					cout << "\nThe question edit successfully!\n" << endl;
			        break;
			        
			case 6: //Edit the Actual Answer
			        cout << "\nEnter new Actual Answer: ";
					cin  >> newActualAns;
					
					question[searchResult].actualAnswer = newActualAns;
					cout << "\nThe question edit successfully!\n" << endl;
			        break;
			        
			default: cout << "\nInvalid option! Please choose again!\n" << endl;
			        break;
		    }
		} while (item < 1 || item > 6);
	}
	else{
		cout << "\nRecord not found!\n" << endl;
	}
}

void addQuestion(Questions question[], int &num){
	if (num < SIZE){
	   Questions ques;
	   cin.ignore(100,'\n');
	   
	   //Prompt user to enter the questions
	   //Get all the questions answer option & actual answer
	   cout << "Enter Question Text: ";
	   getline(cin, ques.questionText);
	
	   cout << "Enter Answer A: ";
	   getline(cin, ques.answerA);
	
	   cout << "Enter Answer B: ";
	   getline(cin, ques.answerB);
	
	   cout << "Enter Answer C: ";
	   getline(cin, ques.answerC);
	   
	   cout << "Enter Answer D: ";
	   getline(cin, ques.answerD);
	   
	   do {
			cout << "Enter Actual Answer (A, B, C or D): ";
	   		cin >> ques.actualAnswer;
	   		
	   		//Prompt if user does not enter A, B, C or D
	   		if (ques.actualAnswer != 'A' && ques.actualAnswer != 'B' && ques.actualAnswer != 'C' && ques.actualAnswer != 'D') {
	   			cout << "Invalid actual answer! Enter again..." << endl;
			   }
			   
	   } while (ques.actualAnswer != 'A' && ques.actualAnswer != 'B' && ques.actualAnswer != 'C' && ques.actualAnswer != 'D');
	
	   //Add the question records to the question array
	   question[num] = ques;
	
	   num++; //Advance to next locations	
	   
	   //Prompt user that the question record is saved successfully 
	   cout << "\nQuestion record saved successfully!\n" << endl;
	    
	}
	
	else{
		//Prompt user if the database is full
		cout << "\nSorry! The database is full." << endl;
		cout << "No questions can be added.\n" << endl;
	}
}

//Display question banks menu
void showSubMenu() {	
	cout << setfill ('*') ;
	cout << setw (20) << setfill (' ') << "IT Test System" << endl;
	cout << setw (20) << setfill (' ') << "Question Banks" << endl;
	cout << endl;
	cout << "1. Add Question" 				<< endl;
	cout << "2. Edit Question" 				<< endl;
	cout << "3. Delete Question" 			<< endl;
	cout << "4. View All Questions" 		<< endl;
	cout << "5. Return to the Main Menu" 	<< endl;
}

int getOption(string prompt) {
	//Let user to enter the option
	int option= 0;
	cout << endl << prompt;
	cin >> option;
	
	return option;
}

//Display main menu
void showMenu() {	
	cout << setfill ('*') ;
	cout << setw (20) << setfill (' ') << "IT Test System" << endl;
	cout << setw (18) << setfill (' ') << "Main Menu" << endl;
	cout << endl;
	cout << "1. Question Banks" 		 << endl;
	cout << "2. Start Test"				 << endl;
	cout << "3. View Historical Results" << endl;
	cout << "4. Exit"					 << endl;
}
