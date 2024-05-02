//----------------------------------------------------------------------------------
//Author:      Jason McMullen and Adam Reese
//Due Date:    10/14/13
//
//Program:     SequenceTest
//Description: This program inturprets the menu selection read in from a txt file
//             and executes those selections. The selections are: create a sequence,
//             delete a number, delete the first number in the sequence, add a
//             number before another number, add a number after another number, add
//             a number to the end of the sequence, display a number at a certain
//             index, display the last element in the sequence, replace a number
//             with another number, append another sequence to the first sequence,
//             create a clone sequence, print the sequence, and create a clone.
//             After all of these changes have been perfromed, each method called
//             will print out the changes to the array along with all of its
//             details.
//----------------------------------------------------------------------------------

import java.io.*;
import java.util.*;
import java.text.*;

public class SequenceTest {

    //variable to hold the user selected option for the menu
    private int option;

    //variable to hold the amount of elements in the current string
    private int manyElements;

    //objects of class DoubleArraySeq
    private DoubleArraySeq sq1, sq2;
    private DoubleArraySeq sq3 = new DoubleArraySeq();

    //format the double variablers to like int type
    DecimalFormat pattern = new DecimalFormat("0.##");

    //This method will interpret the desired selection from the user and execute the
    //commands by calling on various smaller methods to manipulate the array.

    public void menu(String line) throws IOException {

        //objects needed to print to an outside txt file. The "true" in the parameter
        //is needed to add onto a txt file without erasing the contents inside
        //everytime the program trys to write to it
        FileWriter fileOut = new FileWriter("Output.txt", true);
        PrintWriter pw = new PrintWriter(fileOut);

        StringTokenizer tokenizer = new StringTokenizer(line, "\b\n\t,- ");

        pw.println("Input line: " + line);

        option = Integer.parseInt(tokenizer.nextToken());

        switch (option) {

            //Create a new sequence
            case 1:

                pw.println("Create a squence");

                manyElements = tokenizer.countTokens();

                if (manyElements > 0) {

                    if (sq1 == null) {

                        sq1 = createSequence(tokenizer, line, pw);

                    }//end if
                    else {

                        sq2 = createSequence(tokenizer, line, pw);

                    }//end else

                }//end if
                else {

                    pw.println("--------------------");
                    pw.println("Exception - no data was created");
                    pw.println("");
                    pw.println("");

                }//end else

                break;

            //----------------------------------------------------------
            //Delete a number
            case 2:

                pw.println("Delete a number");

                deleteNumber(tokenizer, line, pw);

                break;

            //----------------------------------------------------------
            //Delete the first number from the sequence
            case 3:

                pw.println("Delete the first number from the sequence");

                deleteFirst(pw);

                break;

            //----------------------------------------------------------
            //Add a number before another number
            case 4:

                pw.println("Add a number before another number");

                addBefore(tokenizer, line, pw);

                break;

            //----------------------------------------------------------
            //Add a number after a number
            case 5:

                pw.println("Add a number after a number");

                addAfter(tokenizer, line, pw);

                break;

            //-----------------------------------------------------------
            //Add a number to the end of the sequence
            case 6:

                pw.println("Add a number to the end of the sequence");

                addEnd(tokenizer, line, pw);

                break;

            //-----------------------------------------------------------
            //Display a number at a certain index
            case 7:

                pw.println("Display a number at a certain index");

                displayIndex(tokenizer, line, pw);

                break;

            //-----------------------------------------------------------
            //Display the last element in the sequence
            case 8:

                pw.println("Display the last element in the sequence");

                displayLast(pw);

                break;

            //-----------------------------------------------------------
            //Replace a number with another number
            case 9:

                pw.println("Replace a number with another number");

                replaceNumber(tokenizer, line, pw);

                break;

            //-----------------------------------------------------------
            //Append another sequence to the first sequence
            case 10:

                pw.println("Append another sequence to the first sequence");

                appendSequence(pw);

                break;

            //-----------------------------------------------------------
            //Create a clone sequence
            case 11:

                pw.println("Create a clone sequence");

                createClone(pw);

                break;

            //-----------------------------------------------------------
            //Print the sequence
            case 12:

                pw.println("Print the sequence");

                printTheSequence(tokenizer, line, pw);

                break;

            //----------------------------------------------------------
            //Quit
            case 13:

                pw.println("Quit");

                pw.close();

                //exit out of the program
                System.exit(0);

                break;

            //----------------------------------------------------------

        }//end switch statement

    }//end menu method

    //Create a new DoubleArraySeq object and use the non-default constructor need to
    //send in the amount of elements that will be added to the seq

    public DoubleArraySeq createSequence(StringTokenizer tokenizer, String line,
                                         PrintWriter pw) {

        //create a new DoubleArraySeq object and send the constructor the total amount
        //of elements that will be stored in the array so the array can be created
        //with enough spaces for the total amount of elements
        int manyElement = tokenizer.countTokens();
        DoubleArraySeq sq = new DoubleArraySeq(manyElement);

        int element;

        //add in the elements for each of the spaces in the array, filling it up
        for (int i = 0; i < manyElements; i++) {

            element = Integer.parseInt(tokenizer.nextToken());
            sq.createArray(element, i);

        }//end for loop

        //return the currentIndex to the final position of the array
        sq.setCurrent(manyElement - 1);

        //print the results of this method
        printSequence(sq, pw);

        return sq;

    }//end createSequence method

    //This method searches through the entire array looking for a specific number,
    //once found it then returns the index value of that number. If there is more
    //instances of the number in the array this method will only return the index
    //value of that first instance.

    public int find(DoubleArraySeq sq, int num) {

        int answer = 0;

        //set the currentIndex to 0 so we can see every element in the array
        //starting from the begining
        sq.start();

        for (int i = 0; i < sq.size(); i++) {

            //if the number is found, set the currentIndex equal to its location
            //in the array
            if (num == sq.retrieveElement(i)) {

                answer = i;
                sq.setCurrent(i);

            }//end if
            else {

                //move to the next location to check that element
                sq.advance();

            }//end else

        }//end for loop

        return answer;

    }//end find method

    //This method will delete a number from an array at a specified location it first
    //needs to find the index the element resides in the array and then it sets the
    //currentIndex of the array to that point. After that it deletes the element by
    //replacing it with the elements that follow it

    public void deleteNumber(StringTokenizer tokenizer, String line, PrintWriter pw) {

        int delete = Integer.parseInt(tokenizer.nextToken());

        sq1.setCurrent(find(sq1, delete));
        sq1.removeCurrent();

        printSequence(sq1, pw);

    }//end deleteNumber method

    //This method will delete the first element in the array. It does this by setting
    //the currentIndex of the array to the front and then removes the element at that
    //point by moving the elements following into its place

    public void deleteFirst(PrintWriter pw) {

        sq1.start();
        sq1.removeFront();
        printSequence(sq1, pw);

    }//end deleteFirst method

    //This method adds an element before the desired element. It does this by
    //determining the position of the element and setting the currentIndex to that
    //point. After it expands the size of the array to accomodate the extra element
    //and puts it in its place.

    public void addBefore(StringTokenizer tokenizer, String line, PrintWriter pw) {

        int addThis = Integer.parseInt(tokenizer.nextToken());
        int beforeThis = Integer.parseInt(tokenizer.nextToken());

        sq1.setCurrent(find(sq1, beforeThis));
        sq1.addBefore(addThis);

        printSequence(sq1, pw);

    }//end addBefore method

    //This method adds an element behind the desired element in the array. It does
    //this by determining the location of the element and setting currentIndex equal
    //to that point. It then expands the size of the array by one and adds the new
    //element behind the one desired.

    public void addAfter(StringTokenizer tokenizer, String line, PrintWriter pw) {

        int addThis = Integer.parseInt(tokenizer.nextToken());
        int AfterThis = Integer.parseInt(tokenizer.nextToken());

        sq1.setCurrent(find(sq1, AfterThis));
        sq1.addAfter(addThis);

        printSequence(sq1, pw);

    }//end addAfter method

    //This method adds a new element to the end of the array. It does this by setting
    // the currentIndex equal to the amount of items in the array and then expanding
    //the size of the array to make room for the new element.

    public void addEnd(StringTokenizer tokenizer, String line, PrintWriter pw) {

        int addThis = Integer.parseInt(tokenizer.nextToken());

        sq1.addEnd(addThis);
        printSequence(sq1, pw);

    }//end addEnd

    //This method display the element residing in the desired index location. The
    //currentIndex location so set to the desired index location so that element may
    //be printed to the screen.

    public void displayIndex(StringTokenizer tokenizer, String line, PrintWriter pw) {

        int index = Integer.parseInt(tokenizer.nextToken());

        sq1.setCurrent(index);
        printSequence(sq1, pw);

    }//end displayIndex method

    //This method displays the last element in the array. It does this by setting \
    //currentIndex equal to the last space in the array.

    public void displayLast(PrintWriter pw) {

        sq1.currentLast();
        printSequence(sq1, pw);

    }//end displayLast method

    //This method replaces a number with another selected number. It does this by
    //finding the index the number wishing to be replaced is located in and then
    //adding the new number to that spot effictively replacing the old number.

    public void replaceNumber(StringTokenizer tokenizer, String line, PrintWriter pw) {

        int replaceWhat = Integer.parseInt(tokenizer.nextToken());
        int replaceIndex = find(sq1, replaceWhat);

        //set CurrentIndex = to the index the element we want to
        //replace is located in
        sq1.setCurrent(replaceIndex);

        int replaceWith = Integer.parseInt(tokenizer.nextToken());

        //add the new element before our element and then increase
        //currentIndex so we can then remove the element we wanted
        //replaced. After that set currentIndex equal to the new
        //element placed in the array.
        sq1.addBefore(replaceWith);
        sq1.advance();
        sq1.removeCurrent();
        sq1.setCurrent(replaceIndex);

        printSequence(sq1, pw);

    }//end replaceNumber method

    //This method creates a new array and then places the origional and then new
    //array after it into it.

    public void appendSequence(PrintWriter pw) {

        sq1.addAll(sq2);
        printSequence(sq1, pw);

    }//end appendSequence method

    //This method creates a clone of sq1

    public void createClone(PrintWriter pw) {

        sq3 = sq1.clone();
        printSequence(sq3, pw);

    }//end createClone method

    //This method prints out the details of the arrays. It does this by figuring
    //out the selected option from the txt file.

    public void printTheSequence(StringTokenizer tokenizer, String line,
                                 PrintWriter pw) {

        int whichSequence = Integer.parseInt(tokenizer.nextToken());

        if (whichSequence == 1) {

            printSequence(sq1, pw);

        }//end if
        else {

            printSequence(sq2, pw);

        }//end else

    }//end printTheSequence method

    //This method prints out all the details of every action taken. It will show the
    //entire array, the currentIndex,and the amount of elements that are located in
    //the array.

    public void printSequence(DoubleArraySeq sq, PrintWriter pw) {

        double answer = 0;
        pw.println("--------------------");
        pw.print("The sequence: ");

        sq.start();
        for (int i = 0; i < sq.size(); i++) {

            answer = sq.getCurrent();
            pw.print(pattern.format(answer) + " ");
            sq.advance();

        }//end for loop
        pw.println("");

        pw.println("Number of elements: " + sq.size());
        pw.println("The current element: " + pattern.format(answer));
        pw.println("");
        pw.println("");

        pw.close();

    }//end printSequence method

}//end class