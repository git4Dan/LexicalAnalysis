#ifndef LEX_H_INCLUDED
#define LEX_H_INCLUDED
#include <string>

//here is my Stack class and all of my LinkedList classes for their respective tasks

class stackStruct{//this is my stack class
private:
   struct obj{
        std::string loop;
        int data;
        obj* before;
  };
     obj* objPtr;

public://all methods used in main for this class are below
     stackStruct();
     void pushLoop(std::string code);
     std::string popLoop();
     void depthLoop(stackStruct stacks);
};

class keywordsList{
private:
   struct node{
        node* next;
        std::string keyWord;
  };
     node* root;
     node* temporary;

public://all methods used in main for this class are below
     keywordsList();
     void createkeyNodes();
     void keywordSearch(std::string file);
     void keywordsPresent(bool key1, bool key2, bool key3);
     void printErrors();
     void getErrors(std::string split);

};

class identifierList{
private:
   struct node{
        node* next1;
        std::string identiWord;
  };
     node* root1;
     node* temporary1;

public://all methods used in main for this class are below
     identifierList();
     void identifierSearch(std::string file1);
     void printIdentifiers();
     void createIdentNodes();

};

class constantList{
private:
   struct node{
        node* next;
        std::string constantNum;//not good to include using namespace std; in header file
  };
     node* root;
     node* temporary;

public://all methods used in main for this class are below
     constantList();
     void constantSearch(std::string file2);
     void createConstantNodes();
     void printConstants();

};

class operatorList{
private:
   struct node{
        node* next;
        std::string operWord;//not good to include using namespace std; in header file
  };
     node* root;
     node* temporary;

public://all methods used in main for this class are below
     operatorList();
     void operatorSearch(std::string file3);
     void createOperNodes();
     void operatorsPresent(bool oper1, bool oper2, bool oper3, bool oper4, bool oper5, bool oper6,bool oper7);

};

class delimeterList{
private:
   struct node{
        node* next;
        std::string deliWord;//not good to include using namespace std; in header file
  };
     node* root;
     node* temporary;

public://all methods used in main for this class are below
     delimeterList();
     void delimeterSearch(std::string file4);
     void createDelNodes();
     void delimetersPresent(bool deli1, bool deli2);

};


#endif
