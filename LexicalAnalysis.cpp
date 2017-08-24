#include <iostream>
#include <fstream>
#include <string>

#include "pa3.h"//includes header file

using namespace std;

bool keyCheck1 = false;//these global variables will be used throughout the program
bool keyCheck2 = false;//the boolean values are for checking if whatever I am looking for is found the files.
bool keyCheck3 = false;
bool operCheck = false;//all these bool values are for the search of operators within text file
bool operCheck1 = false;
bool operCheck2 = false;
bool operCheck3 = false;
bool operCheck4 = false;
bool operCheck5 = false;
bool operCheck6 = false;
bool deliCheck = false;//these are for delimeters
bool deliCheck1 = false;

string tempIdent = "";
string identifiers[1000];
string tempConst = "";//to satisfy any test cases
string constinFile[1000];
int identCounter = 0;//counter to increment through arrays in for their respective functions
int constCounter = 0;
string syntaxErrors[400];
int errorCount = 0;
string depthLoop[1000];//this will store all "FOR" and "END" in array in order to push

int main(int argc, char *argv[])
{
    bool fileCheck = false;
    string sectofText = "";
    string text = "";
    string contents = "";
    string fileinput = "";

    keywordsList keyList;//objects for all of my classes
    identifierList identList;
    constantList constList;
    operatorList operList;
    delimeterList deliList;
    stackStruct stackList;

    cout<<"-----------Lexical Analysis File Checker-----------"<<endl;//title of my program

    while(fileCheck == false){

        cin>>fileinput;
        ifstream userFile(fileinput.c_str());//to make this compatible with command console. It accepts an argument

//        if(!userFile.good()){//if file is not found then exit program
//            cout<<"File not found in directory!"<<endl;
//            return -1;
//            }

            for(int i = 0; i < 500; i++){//this loop simply calls all the create node functions for each linkedList to
                keyList.createkeyNodes();//create a sufficient amount of nodes needed
                identList.createIdentNodes();
                constList.createConstantNodes();
                operList.createOperNodes();
                deliList.createDelNodes();
            }

            while(!userFile.eof()){
                getline(userFile, text);//makes sure this gets each word
                text += "\n";//add a newline at the end of each run through the text file


                keyList.keywordSearch(text);//all function calls to search through whats inside the file
                identList.identifierSearch(text);
                constList.constantSearch(text);
                operList.operatorSearch(text);
                deliList.delimeterSearch(text);

                keyList.createkeyNodes();//create nodes for each linkedList in case they are needed
                identList.createIdentNodes();
                constList.createConstantNodes();
                operList.createOperNodes();
                deliList.createDelNodes();

                contents += text;//adds all text in file
                contents += "\n";//This will mainly be used for syntax errors as it adds up everything within the file
            }
                fileCheck = true;//condition to exit loop
                break;

                userFile.close();//good to close the stream
        }
    cout<<endl;

     for(int i=0;i < contents.length();i++){//this loop will separate everything in the string that contains a parenthesis
       if ((contents[i] == ' ') && (contents[i+1] == '(')){
    	   contents[i] = '\n';
       }
       if (contents[i] == ' ' && isupper(contents[i+1])){//this condition separates keywords in the string from other text
    	   contents[i] = '\n';
       }
    }

    for(int i = 0; i < contents.length(); i++){//for the getErrors, I decided it was best to separate the strings being passed in, by new lines after separating them above
    	if (contents[i] == '\n') {
            keyList.getErrors(sectofText);
            //stackListstackList.depthLoop();
            depthLoop[i] += sectofText;
    	    sectofText.clear();//clears the string, to get ready for next set of text
    	}
    	else {
            sectofText += contents[i];//whatever is not at the end of a line, add to that section of the string
    	}
    }


    for(int i = 0; i < 1000; i++){//loop to push all "FOR" and "END" found in the list
        if(depthLoop[i] == "FOR"){
            stackList.pushLoop("FOR");//pushes "FOR" into stack
        }
        else if(depthLoop[i] == "END"){
            stackList.pushLoop("END");
        }
    }


    cout<<"Keywords: ";//output all the requirements
    keyList.keywordsPresent(keyCheck1, keyCheck2, keyCheck3);
    cout<<endl;
    cout<<"Constants: ";
    constList.printConstants();
    cout<<endl;
	cout<<"Identifiers: ";
    identList.printIdentifiers();
    cout<<endl;
    cout<<"Operators: ";
    operList.operatorsPresent(operCheck, operCheck1, operCheck2, operCheck3, operCheck4, operCheck5, operCheck6);
    cout<<endl;
    cout<<"Delimeters: ";
    deliList.delimetersPresent(deliCheck, deliCheck1);
    cout<<endl;
	cout<<"Syntax Errors: ";
	keyList.printErrors();
	cout<<endl;
	stackList.depthLoop(stackList);

    return 0;
}//end of main method

/*the constructor for the keyword LinkedList.*/

keywordsList::keywordsList(){
    root = NULL;
    temporary = NULL;
}

/*The function below creates nodes for my LinkedList*/

void keywordsList::createkeyNodes(){
    node* start = new node;//make a new node
    start -> next = NULL;
    //start -> page = pageStatus;//set its string value = to "Free"

    if(root != NULL){
        temporary = root;
        while(temporary -> next != NULL){
            temporary = temporary -> next;//keep going through list as long as next node is not NULL
        }
        temporary -> next = start;//when next node is not yet made, set it equal to the node created above
    }
    else{
        root = start;//begin by setting the first node in list equal to the node created above
    }
}

void keywordsList::keywordSearch(string files){//type of method learned in COP3502, in which I use boolean values to output, the keys found
    temporary = root;//set temporary equal to beginning of LinkedList
    temporary->keyWord = files;
    if((temporary->keyWord.find("BEGIN") != std::string::npos) && keyCheck1 == false){
        keyCheck1 = true;
    }
    if((temporary->keyWord.find("END") != std::string::npos) && keyCheck2 == false){
        keyCheck2 = true;
    }
    if((temporary->keyWord.find("FOR") != std::string::npos) && keyCheck3 == false){
        keyCheck3 = true;
    }
}

/*This function gets all the syntax errors made for keywords, by using a global string array and some boolean values. */

void keywordsList::getErrors(string files){

    bool keyCheck = false;//boolean values to be used later on in method
    bool keyCheck1 = false;
    bool keyCheck2 = false;
    bool keyCheck3 = false;
    bool keyCheck4 = false;
    bool keyCheck6 = false;
    bool errorsBool = false;

    temporary = root;

    while(temporary != NULL && keyCheck3 == false){
        while(keyCheck6 == false){//make sure this boolean does not cause problems later
        temporary->keyWord = files;
        string splitString = temporary->keyWord;//set splitString equal to string stored for each node, while loop is running

         for(int i = 0; i < splitString.length(); i++){
            if(!isupper(splitString[i])){
                keyCheck4 = true;//if something is not uppercase, then set this bool value to true in order to gain
                continue;//access to the conditional statements below
                }
            }
                if(keyCheck4 == false){
                    errorsBool = true;
                }
                if(errorsBool == true){
                    bool check = true;
                    if((splitString != "BEGIN") && (splitString != "FOR") && (splitString != "END")){
                                //cout<<"yoo";
                        for(int i = 0; i < 400; i++){
                            if(syntaxErrors[i] == splitString){//if the string is equal to an error within the string array, then clear string in order
                                splitString.clear();//to remove duplicates
                                return;//return before getting to the bottom
                       }
                        }
                    syntaxErrors[errorCount++] = splitString;//increment the string array index and store the error
                    }
                }
                //temporary = temporary->next;
                keyCheck6 = true;//to exit loops
                keyCheck3 = true;
         }
    }

}//end of getErrors method

/*The function below is used to print the keywords that are found using global bool values that are passed in as arguments.*/

void keywordsList::keywordsPresent(bool begKey, bool endKey, bool forKey){//I used a method similar to one implemented in COP3502
    if(begKey == true){
        cout<<"BEGIN ";
    }
    if(endKey == true){
        cout<<"END ";
    }
    if(forKey == true){
        cout<<"FOR ";
    }
}

/*Below is the function of how to print the syntax errors when they are found.*/

void keywordsList::printErrors(){
    for(int i=0;i < 400; i++) {
        if(!syntaxErrors[i].empty() && isupper(syntaxErrors[i][0])){//would only print if it is capitalized and the string array is not empty
            cout << syntaxErrors[i]<<" ";
            }
	    }
}

/*Below is the constructor of my identifier LinkedList.*/

identifierList::identifierList(){
    root1 = NULL;
    temporary1 = NULL;
}

/*This function is used to search through the text file and find which identifiers are used.*/

void identifierList::identifierSearch(string files1){

    bool identCheck = false;//boolean values later in function
    bool check23 = false;
    bool check33 = false;
    temporary1 = root1;
    size_t location = 0;//this will be used to make a substring below
    string space = " ";
    string word = "";

//    while(temporary1 != NULL && check23 == false){//makes another substring for each space in the string, so that it is easier to make comparisons
//        while((location = files1.find(space)) != std::string::npos){
//            word = files1.substr(0, location);
//            temporary1->identiWord = word;
//            if(temporary1->next1 == NULL){//routine check to make sure the next node is not NULL
//                break;
//            }
//            temporary1 = temporary1->next1;
//            files1.erase(0, location + space.length());//erase section of string that I do not need anymore
//        }
//        check23 = true;//bool value used to exit loop
//    }

    //temporary1 = root1;
    temporary1->identiWord = files1;
    while(temporary1 != NULL && check33 == false){
        while(identCheck == false){//make sure this boolean does not cause problems later
            if(temporary1->next1 == NULL){
                break;
        }
         string splitString = temporary1->identiWord;
         for(int i = 0; i < splitString.length(); i++){
                if(isalpha(splitString[i])){
                    if(islower(splitString[i]) && isalpha(splitString[i])){//if word qualifies to be an identifier, then add the word to tempIdent string
                        tempIdent += splitString[i];
                        }
                }
                else{
                    if(tempIdent.empty()){//when the string is empty just go back up loop
                        continue;
                        }
                    else{
                        for(int i = 0;i < 1000; i++){
                            if (identifiers[i] == tempIdent){//if an identifier already within the identifiers string array is equal
                                tempIdent.clear();               //to one in tempIdent string, then remove it as it is a duplicate and clear tempIdent.
                                return;//return before it can go below and increment the index within the identifiers array.
                            }
                        }
                   identifiers[identCounter++] = tempIdent;//increment the identifiers string array and set it equal to whatever identifier is in tempIdent.
                   tempIdent.clear();//clear the string for next loop
                }
                }
        }
       temporary1 = temporary1->next1;//go to next node
       check33 = true;
    }

    }
}//end of identifier search function

/*Below is the function to print out all identifiers.*/

void identifierList::printIdentifiers(){//this function is for printing identifiers

    for(int i=0; i < 1000; i++){//prints out every identifier found
		if (!identifiers[i].empty() && isalpha(identifiers[i][0])) {
		cout << identifiers[i]<<" ";
		}
	}

}//end of printing function for identifiers


void identifierList::createIdentNodes(){//this function creates nodes for the identifier LinkedList
    node* start1 = new node;//make a new node
    start1 -> next1 = NULL;

    if(root1 != NULL){
        temporary1 = root1;
        while(temporary1 -> next1 != NULL){
            temporary1 = temporary1 -> next1;//keep going through list as long as next node is not NULL
        }
        temporary1 -> next1 = start1;//when next node is not yet made, set it equal to the node created above
    }
    else{
        root1 = start1;//begin by setting the first node in list equal to the node created above
    }
}

constantList::constantList(){//constructor for constant LinkedList class
    root = NULL;
    temporary = NULL;
}

/*The function below searches the text file for constants by first creating a substring.*/

void constantList::constantSearch(string fileText){

    temporary = root;
    bool constCheck = false;//these bool values are used throughout the function to exit loops
    bool constCheck2 = false;
    bool constCheck3 = false;

    size_t spaceIndex = 0;//this is for the substring
    string space = " ";
    string word = "";

//    while(temporary != NULL && constCheck2 == false){
//        while((spaceIndex = fileText.find(space)) != std::string::npos){
////            if(temporary->next == NULL){//if next node is NULL, then break
////                break;
////            }
//        word = fileText.substr(0, spaceIndex);//this is the erase function for creating a substring
//        temporary->constantNum = word;
//        temporary = temporary->next;
//        if(temporary->next == NULL){
//            break;
//        }
//        fileText.erase(0, spaceIndex + space.length());//erase what is not needed from the string anymore
//    }
//    constCheck2 = true;
//    }

    //temporary = root;
    temporary->constantNum = fileText;
    while(temporary != NULL && constCheck3 == false){
            while(constCheck == false){//make sure this boolean does not cause problems later

         string splitString = temporary->constantNum;//set splitString equal to the string stored in constantNum within node

         for(int i = 0; i < splitString.length(); i++){
                if(isalnum(splitString[i])){
                    if(isdigit(splitString[i]) && !isalpha(splitString[i])){
                        tempConst += splitString[i];
                        }
                }
                else{
                    if(tempConst.empty()){//do not want spaces going to next condition so just made this condition
                    //do not need anything here
                    }
                    else{
                        for(int i=0;i < 1000; i++) {
                            if (tempConst == constinFile[i]){//if the temporary string contains elements already within my array, then remove them
                                tempConst.clear();
                                return;
                            }
                        }
                   constinFile[constCounter++] = tempConst;//add whats in the string to the string array, with index incremented
                   tempConst.clear();//clear the string
                }

                }
        }
         if(temporary->next == NULL){
                    break;
                }
       temporary = temporary->next;//move to next node
       constCheck3 = true;
        }
    }
}//end of constant search method

void constantList::createConstantNodes(){
    node* start3 = new node;//make a new node
    start3 -> next = NULL;

    if(root != NULL){
        temporary = root;
        while(temporary -> next != NULL){
            temporary = temporary -> next;//keep going through list as long as next node is not NULL
        }
        temporary -> next = start3;//when next node is not yet made, set it equal to the node created above
    }
    else{
        root = start3;//begin by setting the first node in list equal to the node created above
    }
}

void constantList::printConstants(){
    for(int i = 0; i < 1000; i++) { //consider changing max length
		if (!constinFile[i].empty() && isdigit(constinFile[i][0])){//print each value for constants
		cout << constinFile[i]<<" ";
		}
	}
}

/*The operator LinkedList constructor.*/

operatorList::operatorList(){
    root = NULL;
    temporary = NULL;
}

/*The function below just creates nodes when necessary for the operator linked list. If it does then set the bool value equal to true.*/

void operatorList::createOperNodes(){
    node* start2 = new node;//make a new node
    start2 -> next = NULL;

    if(root != NULL){
        temporary = root;
        while(temporary -> next != NULL){
            temporary = temporary -> next;//keep going through list as long as next node is not NULL
        }
        temporary -> next = start2;//when next node is not yet made, set it equal to the node created above
    }
    else{
        root = start2;//begin by setting the first node in list equal to the node created above
    }
}

/*The function below finds the operators in the file and sets the global bool value to true if an operator is found.*/

void operatorList::operatorSearch(string subFile){
    temporary = root;//set temporary equal to first node
    temporary->operWord = subFile;

    if((temporary->operWord.find("+") != std::string::npos)&& operCheck == false){//uses the find keyword, which should be not equal to npos if something is found because
        operCheck = true;                                                         //npos is essentially does not exist
       }
    if((temporary->operWord.find("-") != std::string::npos)&& operCheck1 == false){
        operCheck1 = true;
       }
    if((temporary->operWord.find("*") != std::string::npos)&& operCheck2 == false){
        operCheck2 = true;
       }
    if((temporary->operWord.find("/") != std::string::npos)&& operCheck3 == false){
        operCheck3 = true;
       }
     if((temporary->operWord.find("++") != std::string::npos)&& operCheck4 == false){
        operCheck4 = true;
       }
    if((temporary->operWord.find("=") != std::string::npos)&& operCheck5 == false){
        operCheck5 = true;
    }
    if((temporary->operWord.find("%") != std::string::npos)&& operCheck6 == false){
        operCheck6 = true;
       }
}

/*The function below outputs the operators that were present in the text file. It uses global bool values that are set to true
if an operator is found.*/

void operatorList::operatorsPresent(bool operatorCheck1, bool operatorCheck2, bool operatorCheck3,bool operatorCheck4,bool operatorCheck5,bool operatorCheck6,bool operatorCheck7){

    if(operatorCheck1 == true){//all these conditions are based off the global bool values that are within the search functions
        cout<<"+ ";
    }
    if(operatorCheck2 == true){
        cout<<"- ";
    }
    if(operatorCheck3 == true){
        cout<<"* ";
    }
    if(operatorCheck4 == true){
        cout<<"/ ";
    }
    if(operatorCheck5 == true){
        cout<<"++ ";
    }
    if(operatorCheck6 == true){
        cout<<"= ";
    }
    if(operatorCheck7 == true){
        cout<<"% ";
    }
}

delimeterList::delimeterList(){//delimeter linkedlist constructor
    root = NULL;
    temporary = NULL;
}

void delimeterList::createDelNodes(){
    node* start4 = new node;//make a new node
    start4 -> next = NULL;

    if(root != NULL){
        temporary = root;
        while(temporary -> next != NULL){
            temporary = temporary -> next;//keep going through list as long as next node is not NULL
        }
        temporary -> next = start4;//when next node is not yet made, set it equal to the node created above
    }
    else{
        root = start4;//begin by setting the first node in list equal to the node created above
    }
}

/*The function below searches the file for delimeters and sets the appropriate global bool value equal to true if one is found.*/

void delimeterList::delimeterSearch(string delFile){
    temporary = root;
    temporary->deliWord = delFile;

    if((temporary->deliWord.find(",") != std::string::npos)&& deliCheck == false){//this will search the file using the find keyword
        deliCheck = true;//if "," is found, then set bool value to true
       }
    if((temporary->deliWord.find(";") != std::string::npos)&& deliCheck1 == false){
        deliCheck1 = true;
       }
}//end of delimeter search function

/*The function below prints the delimeters based on the boolean values passed in.*/

void delimeterList::delimetersPresent(bool delimeterCheck, bool delimeterCheck2){
    if(delimeterCheck == true){
        cout<<", ";
    }
    if(delimeterCheck2 == true){
        cout<<"; ";
    }
}

stackStruct::stackStruct(){//constructor for the stack class
    objPtr = NULL;
}

/*The function below pushes an element into the stack.*/

void stackStruct::pushLoop(string loopName){//determine if I need to pass in this pointer or not

    obj* loopN = new obj;
    loopN->loop = loopName;//set the string value of the node equal to the loop name passed in

    if(objPtr == NULL){//if stack is empty
        objPtr = loopN;//set objPtr equal to the loopN pointer made above
        objPtr->before = NULL;//set any previous entry NULL
    }
    else{//set the previous obj equal to objPtr
        loopN->before = objPtr;
        objPtr = loopN;
    }
}

/*The function below is the pop method from the stack class, which pops a string off the stack.*/

string stackStruct::popLoop(){
    string dataType = "";

    if(objPtr == NULL){//if list is empty just
        return dataType;
    }
    else{
        obj* pop = objPtr;
        objPtr = objPtr->before;
        dataType = pop->loop;
        delete pop;//remove the item from the stack
        return dataType;//return the string dataType
    }
}

/*The function below calculates the depth of the nested loops within the text files to determine the loop with
the most nested loops within it.*/

void stackStruct::depthLoop(stackStruct stacker){//pass in a stack object

    string loopKind = "";
    int amount = 0;//this will be the value of the most nested loops
    int increment = 0;//this will just increment or decrement whenever a "FOR" or "END" is found in the text file

    while(objPtr != NULL){
        loopKind = stacker.popLoop();//set the value returned from the pop function equal to loopKind
        cout<<"abc"<<endl;
        if(loopKind == "END" || loopKind == "FOR"){
            if(loopKind == "FOR"){
                increment++;//increment whenever it gets to the beginning of a loop
            }
            if(amount < increment){
                amount = increment;//get the highest amount of depth
            }
            if(increment > 0 && loopKind == "END"){
                increment--;//we want to decrement whenever it gets to the end of a loop
            }
        }
        objPtr = objPtr->before;
    }

    cout<<"The maximum depth of the nested loop(s) is: "<<amount;
}

