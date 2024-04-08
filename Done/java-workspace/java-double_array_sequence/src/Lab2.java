//----------------------------------------------------------------------------------
//Authors:     Jason McMullen and Adam Reese
//Due Date:    10/14/13
//
//Program:     Lab2
//Description: This program reads in, from a file, a list of 
//             numbers along with their menu options. Depending on the options a 
//             new array can be created, elements can be added or taken away in the
//             deisred index of the array and two different arrays can be combined
//             into one while maintaining the proper sequence of elemnts as 
//             specified.
//----------------------------------------------------------------------------------

import java.io.*;

//this class contains the main method that will run the program

public class Lab2{

    //The main method will be responsible for reading the attached txt document and
    //sending line per line to the parse method in SequenceTest

    public static void main(String[] args){

        SequenceTest seqTest = new SequenceTest();

        try{

            //fr is an object of the FileReader class
            FileReader fr = new FileReader("input.txt");

            //fileIn is an object of the BufferedReader class
            BufferedReader fileIn = new BufferedReader(fr);

            //inital read to start the loop
            String line = fileIn.readLine();

            while(line != null){

                //send line to menu to determine what information the line
                //contains
                seqTest.menu(line);

                //read the next line
                line = fileIn.readLine();

            }//end while

        }//end try
        catch(IOException e){

            System.out.println("The file was not found.");

        }//end catch

    }//end main method

}//end Lab2 class