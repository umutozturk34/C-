//**************************************************************
//*****         STUDENT NAME: MUSTAFA UMUT OZTURK          *****
//*****         STUDENT NUMBER: B221202039                 *****
//*****         ASSIGNMENT #: 2                            *****
//*****  I affirm that i will not give or receive any      *****
//*****  unauthorized help on this work, and that all      *****
//*****            work will be my own                     *****
//**************************************************************
#include <iostream> 
#include <iomanip> // to use functions like setw
#include <cmath> // to use basic math equations like pow function
#include <ctime> // to generate random row, column and matrix element
#include <fstream> // to save generated matrices into a data.txt file as well as read matrices from data.txt file
#include <string> // to use certain string operations
using namespace std;

//Our first function to generate input, core and output matrix.
void generate() { 
    // now we declare our first variables as integers
    int inputsize, coresize, outputsize;
    srand(time(NULL)); // to generate random numbers for columns, rows and elements
    inputsize = rand() % 16 + 5; // our input size (between 5 - 20)
    coresize = rand() % 4 + 2; // our core size (between 2 - 5)
    outputsize = (inputsize - coresize) + 1; // our output core size should be equal this according to the given formula
    //rows = columns because we work with square matrices
    
    //We declare a variable in ofstream in order to write our input and core matrices into a data.txt file
    ofstream writeData("data.txt", ios::app);
    //We declare another variable to check if data.txt exists and full. if it is full then it clears the data.txt file
    ofstream fileDeleter("data.txt", ofstream::out | ofstream::trunc);
    if (fileDeleter.is_open()) {
        fileDeleter.close();
    }

    writeData << "INPUT MATRIX" << endl; //writeData to save this line into data.txt file
    cout << "INPUT MATRIX" << endl; // and also it should be seen on the output screen.

    // we need to create dynamic arrays because our input and core matrices are completely generated randomly, 
    //our output is also randomly generated
    //Dynamic array for input matrix
    int** inputmatrix = new int*[inputsize];
    for (int i = 0; i < inputsize; ++i) {
        inputmatrix[i] = new int[inputsize];
    }

    //Basic matrix generator for our input matrix
    for (int i = 0; i < inputsize; i++) {
        for (int n = 0; n < inputsize; n++) {
            inputmatrix[i][n] = rand() % 11 + 10; //numbers between 10 - 20
            cout << setw(3) << inputmatrix[i][n]; // should be seen on the output screen
            if (writeData.is_open()) { // we once again save our matrix into data.txt file
                writeData << setw(3) << inputmatrix[i][n]; //and also display it on the output screen
                if ((n + 1) % inputsize == 0) // we check that if our row is full
                    writeData << endl; // if it is full it ends the line and starts the other row in data.txt
            }
        }
        cout << endl;
    }

    // we once again do the same things for core matrix
    writeData << "CORE MATRIX" << endl;
    cout << "CORE MATRIX" << endl;

    //Dynamic array for core matrix.
    int** corematrix = new int*[coresize];
    for (int i = 0; i < coresize; ++i) {
        corematrix[i] = new int[coresize];
    }   

    for (int i = 0; i < coresize; i++) {
        for (int n = 0; n < coresize; n++) {
            corematrix[i][n] = rand() % 10 + 1; // numbers between 1 - 10
            cout << setw(3) << corematrix[i][n];
            if (writeData.is_open()) {
                writeData << setw(3) << corematrix[i][n];
                if ((n + 1) % coresize == 0)
                    writeData << endl;
            }
        }
        cout << endl;
    }



    // Now the hardest part of the assignment
    // We dont save the output matrix into data.txt file. Because after input and core matrices are saved into the data.txt file
    // we will read data.txt file and create new variables after that we create another output for the same input and core matrices.
    cout << "OUTPUT MATRIX" << endl;

    //Dynamic array for output matrix.
    int** outputmatrix = new int*[outputsize];
    for (int i = 0; i < outputsize; ++i) {
        outputmatrix[i] = new int[outputsize];
    }

    int sum; //Given the formula we need a sum integer
    for (int a = 0; a < pow(outputsize, 2); a++) { // first for loop is for the output matrix creation
        // if orow and ocolumn equals to 4 we have 16 elements on output matrix that means a is our element number
        int i = a / outputsize; // i is  our row number for example a equals 13 and orow and o column equals to 4 so 13 / 4 = 3,25
        //if we say it is integer then it will be 3 so we are now in the 4th row (0 1 2 3 <--> 3 is the 4th row)
        int j = a % outputsize; // j is our column number. (% modulus symbol gives us the remaining part) so once again remaining part of the
        // 13 / 4 is 1 so we are in the 2nd column (0 1 2 3 <--> 1 is the 2nd column) 
        // Conclusion
        // 4x4 OUTPUT MATRIX
        // 0  1    2    3
        // 4  5    6    7
        // 8  9    10   1
        // 12 (13) 14   15
        // 13 is in the 4th row and 2nd column 

        sum = 0; // we need this because everytime we get out of the 2nd loop we will start a new addition.

        //Now we will create core matrices inside the input matrix and execute the given mathematical equation
        for (int k = 0; k < coresize; k++) {//Basic matrix creation again (creating core matrices inside the input matrix)
            for (int l = 0; l < coresize; l++) {
                sum += inputmatrix[i + coresize - k - 1][j + coresize - l - 1] * corematrix[k][l]; 
                //I want to explain this with another method
                // INPUT MATRIX(5x5)    CORE MATRIX(2x2)    output will be 4x4 due to given formula
                // * * * * *           
                // * * * * *               o  b     For example when i = 3 and j = 2 that means we are talking about
                // * * * * *               c  d     the element before the last element of the output matrix.
                // * * x y *                        when k = 0 and l = 0 we are now talking about the first element of the core matrix
                // * * z p *                        that means we are talking about o. Lets put the given numbers into formula
                //                                  input[3+2-0-1][2+2-0-1] = input[4][3] = p
                //                                  (0 1 2 3 4 -- 4 means 5th row - 0 1 2 3 4 -- 3 means 4th column) 
                //          OUTPUT MATRIX           core[0][0] = o , sum = 0 + o*p and now l integer increases by one. That means we are 
                //            * * * *               going other column. 
                //            * * * *               input[4][2] = z , core[0][1] = b  sum = o*p + z*b
                //            * * * *               now we are going to beginning of second loop now k increases by 1 
                //            * * Q *               that means we are now going to 2nd row of the core matrix
                //                                  input[3][3] = y , core[1][0] = c , sum = o*p + z*b + y*c now l increases by one
                // Q = (o*p + z*b + y*c + x*d)/4    input[3][2] = x , core[1][1] = d , sum = a*p + z*b + y*c + x*d.
                //                                  this is the end of the second loop and now a is going to increase by one and
                //                                  that will be our last element of the output matrix.
            }  
        }

        outputmatrix[i][j] = sum / (pow(coresize, 2)); //after the every ending of the 2nd loop we will
        //do this equation and that will be our element for the output matrix 
        cout << setw(5) << outputmatrix[i][j];
        if ((j + 1) % outputsize == 0) //if our row is full
            cout << endl;              //starts new row
    }

    writeData.close(); //ending of the writing process

    //Deleting the variables to release the memory
    for (int i = 0; i < inputsize; ++i) {
        delete[] inputmatrix[i];
    }
    delete[] inputmatrix;

    for (int i = 0; i < coresize; ++i) {
        delete[] corematrix[i];
    }
    delete[] corematrix;

    for (int i = 0; i < outputsize; ++i) {
        delete[] outputmatrix[i];
    }
    delete[] outputmatrix;
}


//second function to read input and core matrices from data.txt and save them as a variable
void readfromfile() {

    //create new variable in ifstream to read data.txt 
    ifstream readData("data.txt");
    
    //we declare new bool variables to check that our code reads whether input matrix or core matrix.
    bool isinputmatrix = false, iscorematrix = false;

    //We declare new variables to track the size of input and core matrices
    int inputsize = 0, coresize = 0;

    string line;//to store the line that has been reading
    while (getline(readData, line)) { //Check every line one by one with while loop
        if (line == "INPUT MATRIX") {
            //check that if line is the beginning of the input matrix
            isinputmatrix = true;
            iscorematrix = false;
            continue;//go to beginning of the while loop
        } 
        else if (line == "CORE MATRIX") {
            //check that if line is the beginning of the core matrix
            isinputmatrix = false;
            iscorematrix = true;
            continue;//go to beginning of the while loop
        }

        if (isinputmatrix) {//if we are in input matrix (isinputmatrix = true) size increases by one
            inputsize++;
        } 
        else if (iscorematrix) {//if we are in core matrix (iscorematrix = true) size increases by one
            coresize++;
        }
    }


    //Dynamic Array for input matrix
    int** inputmatrix = new int*[inputsize];
    for (int i = 0; i < inputsize; ++i) {
        inputmatrix[i] = new int[inputsize];
    }

    readData.clear();
    readData.seekg(0, ios::beg); // we need to start from beginning of the file

    getline(readData, line); // we pass one line to reach input matrix elements.
    for(int i = 0; i < inputsize; i++) {
        for(int n = 0; n <inputsize; n++) {
            readData >> inputmatrix[i][n];
        }
    }

    getline(readData, line); getline(readData, line); // we pass two line to reach core matrix elements.

    //Dynamic array for core matrix
    int** corematrix = new int*[coresize];
    for (int i = 0; i < coresize; ++i) {
        corematrix[i] = new int[coresize];
    }

    for(int i = 0; i < coresize; i++) {
        for(int n = 0; n < coresize; n++) {
            readData >> corematrix[i][n]; //assign the integer in the line into corematrix variable
        }
    }


    readData.close();//ending of the reading proccess

    //Displaying Input Matrix
    cout<<"INPUT MATRIX"<<endl;
    for(int i = 0; i < inputsize; i++ ){
        for (int n = 0; n < inputsize; n++) {
            cout<<setw(3)<<inputmatrix[i][n];
            }
            cout<<endl;
    }

    //Displaying core matrix
    cout<<"CORE MATRIX"<<endl;
    for(int i = 0; i < coresize; i++ ) {
        for (int n = 0; n < coresize; n++) {
            cout<<setw(3)<<corematrix[i][n];
            }
            cout<<endl;
    }


    //Declaring the variable according to given equation
    int osize = inputsize - coresize + 1;

    //Dynamic array for output matrix.
    int** outputmatrix = new int*[osize];
    for (int i = 0; i < osize; ++i) {
        outputmatrix[i] = new int[osize];
    }
    //Displaying output matrix
    int sum;
    cout<<"OUTPUT MATRIX"<<endl;
    for (int a = 0; a < osize*osize; a++) {
        int i = a / osize;
        int j = a % osize;
        sum = 0;
        for (int k = 0; k < coresize; k++) {
            for (int l = 0; l < coresize; l++) {
                sum += inputmatrix[i + coresize - k - 1][j + coresize - l - 1] * corematrix[k][l];
            }
        }
        outputmatrix[i][j] = sum / (coresize * coresize);
        cout << setw(5) << outputmatrix[i][j];
        if ((j + 1) % osize == 0) 
        cout << endl;
        } 

    //Deleting the variables to release the memory
    for (int i = 0; i < inputsize; ++i) {
        delete[] inputmatrix[i];
    }
    delete[] inputmatrix;

    for (int i = 0; i < coresize; ++i) {
        delete[] corematrix[i];
    }
    delete[] corematrix;

    for (int i = 0; i < osize; ++i) {
        delete[] outputmatrix[i];
    }
    delete[] outputmatrix;

}

//3rd function to check if data.txt full or not
bool emptycheck(string filename) {
    ifstream file(filename);
    if(file.peek() == ifstream::traits_type::eof()) {
        file.close();
        return true;
    }
    else {
        return false;
    }
}

//enum for the menu
enum m { generatenewmatrix = 1, checkoldfiles, exitt };

//4th function for the menu of our program
void menu() { 
    // declaring two variables for the menu
    int selection = 0;
    string input; //we use string because if user enters a char like "FIRST" or "SECOND" the code cracks up.

    //now our menu
    //we use do loop because if the user enters other numbers instead of 1,2 or 3 we need to show the menu again
    do {
        system("cls");
        cout << "Please select 1,2 or 3."<<endl;
        cout << "1 - Generate new matrices" <<endl;
        cout << "2 - Read matrices from existing file"<<endl;
        cout << "3 - Exit"<<endl<< ": ";
        cin >> input;
        if(input == "1" || input == "2" || input == "3") {
            selection = stoi(input);//string to integer
        }
        else
            continue;//return to beginning of the do loop if user enters string or different numbers from 1, 2 and 3
    } while ((selection != 1) && (selection != 2) && (selection !=3));

    m m1; //declaring a variable for the enum 
    m1 = (m)selection;
    switch (selection) {        
    //thanks to enum when we press 1 it will make us go to generatenewmatrix
    //when we press 2 it will make us go to checkoldfiles
    //when we press 3 it will make us go exitt
    case generatenewmatrix: 
        system("cls");
        generate(); // we call our generate function to generate input, core and output matrix
            break;

    case checkoldfiles:
        system("cls");
        if (emptycheck("data.txt")) { // we check that if our data.txt file is empty or not.
            cout << "There are no matrices to show at the moment." << endl;
            cout << "Here is the first of the program:" << endl;
            //if it is empty call the generate function to create new matrices
            generate();
        } 
        else {
             //if it is full read the input and core matrices then create the output matrix from zero
            cout << "Here is the last generated input, core and output matrix: " << endl;
            readfromfile();
            }
        break;

        case exitt:
            system("exit");
            break;
    }

}

//lastly our main function but this part is easy because we have 5 functions to do the work instead of main function
int main() {
    menu();
}
