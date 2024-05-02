/**
 Double Array Sequence
 By - Adam Reese, Jason McMullen

 This class creats objects of arrays to store data. The objects can be increased in size
 and new elements can be added at any time.
 **/
import java.text.*;

public class DoubleArraySeq implements Cloneable
{
    // Invariant of the DoubleArraySeq class:
    //   1. The number of elements in the seqeunces is in the instance variable
    //      manyItems.
    //   2. For an empty sequence (with no elements), we do not care what is
    //      stored in any of data; for a non-empty sequence, the elements of the
    //      sequence are stored in data[0] through data[manyItems-1], and we
    //      donít care whatís in the rest of data.
    //   3. If there is a current element, then it lies in data[currentIndex];
    //      if there is no current element, then currentIndex equals manyItems.
    private double[] data;
    private int manyItems;
    private int currentIndex;

    /**
     * Initialize an empty sequence with an initial capacity of 10.  Note that
     * the addAfter and addBefore methods work
     * efficiently (without needing more memory) until this capacity is reached.
     * @param - none
     * @postcondition
     *   This sequence is empty and has an initial capacity of 10.
     * @exception OutOfMemoryError
     *   Indicates insufficient memory for:
     *   new double[10].
     **/
    public DoubleArraySeq( )
    {
        data = new double[10];
        manyItems = 0;
        currentIndex = 0;
    }


    /**
     * Initialize an empty sequence with a specified initial capacity. Note that
     * the addAfter and addBefore methods work
     * efficiently (without needing more memory) until this capacity is reached.
     * @param cap
     *   the initial capacity of this sequence
     * @precondition
     *   initialCapacity is non-negative.
     * @postcondition
     *   This sequence is empty and has the given initial capacity.
     * @exception IllegalArgumentException
     *   Indicates that initialCapacity is negative.
     * @exception OutOfMemoryError
     *   Indicates insufficient memory for:
     *   new double[cap].
     **/
    public DoubleArraySeq(int cap)
    {
        if(cap > 0)
        {
            data = new double[cap];
            manyItems = 0;
            currentIndex = 0;
        }
        else
        {
            throw new IllegalArgumentException
                    ("The capacity cannot be negetive");
        }
    }

    /**
     * Change the current capacity of this sequence.
     * @param minimumCapacity
     *   the new capacity for this sequence
     * @postcondition
     *   This sequence's capacity has been changed to at least minimumCapacity.
     *   If the capacity was already at or greater than minimumCapacity,
     *   then the capacity is left unchanged.
     * @exception OutOfMemoryError
     *   Indicates insufficient memory for: new int[minimumCapacity].
     **/
    private void ensureCapacity(int minimumCapacity)
    {
        double biggerArray[];
        if (data.length < minimumCapacity)
        {
            biggerArray = new double[minimumCapacity];
            System.arraycopy(data, 0, biggerArray, 0, manyItems);
            data = biggerArray;
        }
    }

    /**
     * Add a new element to this sequence, after the current element.
     * If the new element would take this sequence beyond its current capacity,
     * then the capacity is increased before adding the new element.
     * @param element
     *   the new element that is being added
     * @postcondition
     *   A new copy of the element has been added to this sequence. If there was
     *   a current element, then the new element is placed after the current
     *   element. If there was no current element, then the new element is placed
     *   at the end of the sequence. In all cases, the new element becomes the
     *   new current element of this sequence.
     * @exception OutOfMemoryError
     *   Indicates insufficient memory for increasing the sequence's capacity.
     * @note
     *   An attempt to increase the capacity beyond
     *   Integer.MAX_VALUE will cause the sequence to fail with an
     *   arithmetic overflow.
     **/
    public void addAfter(int element)
    {
        ensureCapacity(manyItems + 1);
        for(int i = manyItems; i > currentIndex; i--)
            data[i] = data[i-1];
        data[currentIndex+1] = element;
        manyItems++;
        advance();
    }


    /**
     * Add a new element to this sequence, before the current element.
     * If the new element would take this sequence beyond its current capacity,
     * then the capacity is increased before adding the new element.
     * @param element
     *   the new element that is being added
     * @postcondition
     *   A new copy of the element has been added to this sequence. If there was
     *   a current element, then the new element is placed before the current
     *   element. If there was no current element, then the new element is placed
     *   at the start of the sequence. In all cases, the new element becomes the
     *   new current element of this sequence.
     * @exception OutOfMemoryError
     *   Indicates insufficient memory for increasing the sequence's capacity.
     * @note
     *   An attempt to increase the capacity beyond
     *   Integer.MAX_VALUE will cause the sequence to fail with an
     *   arithmetic overflow.
     **/
    public void addBefore(int element)
    {
        ensureCapacity(manyItems + 1);
        for(int i = manyItems; i > currentIndex-1; i--)
            data[i] = data[i-1];
        data[currentIndex] = element;
        manyItems++;
    }


    /**
     * Place the contents of another sequence at the end of this sequence.
     * @param addend
     *   a sequence whose contents will be placed at the end of this sequence
     * @precondition
     *   The parameter, addend, is not null.
     * @postcondition
     *   The elements from addend have been placed at the end of
     *   this sequence. The current element of this sequence remains where it
     *   was, and the addend is also unchanged.
     * @exception NullPointerException
     *   Indicates that addend is null.
     * @exception OutOfMemoryError
     *   Indicates insufficient memory to increase the size of this sequence.
     * @note
     *   An attempt to increase the capacity beyond
     *   Integer.MAX_VALUE will cause an arithmetic overflow
     *   that will cause the sequence to fail.
     **/
    public void addAll(DoubleArraySeq addend)
    {
        ensureCapacity(manyItems + addend.manyItems);

        System.arraycopy(addend.data, 0, data, manyItems, addend.manyItems);
        manyItems += addend.manyItems;
        currentIndex = manyItems - 1;
    }


    /**
     * Move forward, so that the current element is now the next element in
     * this sequence.
     * @param - none
     * @precondition
     *   isCurrent() returns true.
     * @postcondition
     *   If the current element was already the end element of this sequence
     *   (with nothing after it), then there is no longer any current element.
     *   Otherwise, the new element is the element immediately after the
     *   original current element.
     * @exception IllegalStateException
     *   Indicates that there is no current element, so
     *   advance may not be called.
     **/
    public void advance()
    {
        currentIndex++;
    }


    /**
     * Generate a copy of this sequence.
     * @param - none
     * @return
     *   The return value is a copy of this sequence. Subsequent changes to the
     *   copy will not affect the original, nor vice versa.
     * @exception OutOfMemoryError
     *   Indicates insufficient memory for creating the clone.
     **/
    public DoubleArraySeq clone( )
    {  // Clone a DoubleArraySeq object.
        DoubleArraySeq answer;

        try
        {
            answer = (DoubleArraySeq) super.clone( );
        }
        catch (CloneNotSupportedException e)
        {  // This exception should not occur. But if it does, it would probably
            // indicate a programming error that made super.clone unavailable.
            // The most common error would be forgetting the "Implements Cloneable"
            // clause at the start of this class.
            throw new RuntimeException
                    ("This class does not implement Cloneable");
        }

        answer.data = data.clone( );

        return answer;
    }


    /**
     * Create a new sequence that contains all the elements from one sequence
     * followed by another.
     * @param s1
     *   the first of two sequences
     * @param s2
     *   the second of two sequences
     * @precondition
     *   Neither s1 nor s2 is null.
     * @return
     *   a new sequence that has the elements of s1 followed by the
     *   elements of s2 (with no current element)
     * @exception NullPointerException
     *   Indicates that one of the arguments is null.
     * @exception OutOfMemoryError
     *   Indicates insufficient memory for the new sequence.
     * @note
     *   An attempt to create a sequence with a capacity beyond
     *   Integer.MAX_VALUE will cause an arithmetic overflow
     *   that will cause the sequence to fail.
     **/
    public static DoubleArraySeq catenation(DoubleArraySeq s1, DoubleArraySeq s2)
    {
        DoubleArraySeq s3 = new DoubleArraySeq(s1.manyItems + s2.manyItems);
        System.arraycopy(s1, 0, s3, 0, s1.manyItems);
        System.arraycopy(s2, 0, s3, s1.manyItems, s2.manyItems);
        s3.manyItems = (s1.manyItems + s2.manyItems);
        return s3;
    }

    /**
     * Accessor method to get the current capacity of this sequence.
     * The add method works efficiently (without needing
     * more memory) until this capacity is reached.
     * @param - none
     * @return
     *   the current capacity of this sequence
     **/
    public int getCapacity()
    {
        int cap = data.length;
        return cap;
    }

    /**
     * Accessor method to determine whether this sequence has a specified
     * current element that can be retrieved with the
     * getCurrent method.
     * @param - none
     * @return
     *   true (there is a current element) or false (there is no current element at the moment)
     **/
    public boolean isCurrent()
    {

        boolean answer = false;

        if(currentIndex <= data.length)
            answer = true;

        return answer;

    }

    /**
     * Accessor method to get the current element of this sequence.
     * @param - none
     * @precondition
     *   isCurrent() returns true.
     * @return
     *   the current element of this sequence
     * @exception IllegalStateException
     *   Indicates that there is no current element, so
     *   getCurrent may not be called.
     **/
    public double getCurrent( )
    {
        if(isCurrent() == true)
            return data[currentIndex];
        else
            throw new IllegalStateException
                    ("There is no current element");
    }

    /**
     * Remove the current element from this sequence.
     * @param - none
     * @precondition
     *   isCurrent() returns true.
     * @postcondition
     *   The current element has been removed from this sequence, and the
     *   following element (if there is one) is now the new current element.
     *   If there was no following element, then there is now no current
     *   element.
     * @exception IllegalStateException
     *   Indicates that there is no current element, so
     *   removeCurrent may not be called.
     **/
    public void removeCurrent( )
    {
        if(currentIndex != manyItems)
        {
            int i;
            for(i = currentIndex; i<manyItems-1; i++)
            {
                data[i] = data[i+1];
            }
            manyItems--;
        }
        else
        {
            throw new IllegalStateException
                    ("There is no current element");
        }
    }

    /**
     * Determine the number of elements in this sequence.
     * @param - none
     * @return
     *   the number of elements in this sequence
     **/
    public int size( )
    {
        return manyItems;
    }

    /**
     * Set the current element at the front of this sequence.
     * @param - none
     * @postcondition
     *   The front element of this sequence is now the current element (but
     *   if this sequence has no elements at all, then there is no current
     *   element).
     **/
    public void start( )
    {
        if(data[0] != 0)
            currentIndex = 0;
    }

    /**
     * Reduce the current capacity of this sequence to its actual size (i.e., the
     * number of elements it contains).
     * @param - none
     * @postcondition
     *   This sequence's capacity has been changed to its current size.
     * @exception OutOfMemoryError
     *   Indicates insufficient memory for altering the capacity.
     **/
    public void trimToSize( )
    {
        double[ ] trimmedArray;

        if (data.length != manyItems)
        {
            trimmedArray = new double[manyItems];
            System.arraycopy(data, 0, trimmedArray, 0, manyItems);
            data = trimmedArray;
        }
    }

    /**
     * Add a number to the front of the sequence
     * @param - num, the new element to be added to the sequence
     * @postcondition
     *   The new elemenet has been added to the front of the sequence
     * and if the sequence was too short the size has been increased by 1.
     * @exception OutOfMemoryError
     *   Indicates insufficient memory for altering the capacity.
     **/
    public void addFront(int num)
    {
        ensureCapacity(manyItems + 1);
        if(data[0] != 0)
        {
            manyItems++;
            for(int i = manyItems; i>=0; i--)
            {
                data[i] = data[i-1];
            }
            data[0] = num;
        }
        else
        {
            data[0] = num;
        }
    }

    /**
     * Remove the front element of the sequence
     * @param - none
     * @postcondition
     *   The front element has been removed and the sequence contains one less element
     **/
    public void removeFront()
    {
        for(int i = 0; i<manyItems-1; i++)
        {
            data[i] = data[i+1];
        }
        manyItems--;
        start();

    }

    /**
     * Add a number to the end of the sequence
     * @param - num, the number to be added
     * @postcondition
     *   The number has been added to the end of the sequence and if
     * the sequence was too short the size has been increased by 1.
     * @exception OutOfMemoryError
     *   Indicates insufficient memory for altering the capacity.
     **/
    public void addEnd(int num)
    {
        ensureCapacity(manyItems+1);
        data[manyItems] = num;
        manyItems++;
        currentIndex = manyItems - 1;
    }

    /**
     * Set the current index to the last element of the sequence
     * @param - none
     * @postcondition
     *   The current element is now the last element
     * @exception IllegalStateException
     *   Indicates the sequence is empty or does not contain any elements.
     **/
    public void currentLast()
    {
        if(manyItems != 0)
            currentIndex = manyItems - 1;
        else
        {
            throw new IllegalStateException
                    ("The sequence is empty or does not contain any elements");
        }
    }

    /**
     * Set the current index to i and return the element at i
     * @param - i
     *		the index to be retrived
     * @precondition
     *		i is not negetive and the sequence contains atleast i elements
     * @postcondition
     *   The current element is now i
     * @exception IllegalStateException
     *   Indicates the sequence is empty or does not contain any elements.
     **/
    public double retrieveElement(int i)
    {
        if(i < manyItems)
        {
            currentIndex = i;
            return data[i];
        }
        else
        {
            throw new IllegalStateException
                    ("The element cannot be retrived because the sequence is empty or does not contain that many elements.");
        }
    }

    /**
     * Sets the current index to i.
     * @param - i, the new current index
     * @postcondition
     *   The current index is set to i.
     * @exception IllegalStateException
     *   Indicates the sequence is empty or i is larger than the sequence legnth
     **/
    public void setCurrent(int i)
    {

        if(i < manyItems && data[0] != 0)
            currentIndex = i;
        else
        {
            throw new IllegalStateException
                    ("setCurrent could not complete because the sequence is empty or the index specified is larger than the sequence legnth.");
        }
    }

    //method to print out the elements of the array. It does this by creating
    //a String and continually adding more and more elements to it and then
    //returning that String.
    public String printArray(DecimalFormat pattern)
    {

        String sequence = "The sequence: ";

        for(int i = 0; i < manyItems; i++)
        {

            double answer = data[i];
            sequence = sequence + pattern.format(answer) + " ";

        }

        return sequence;

    }//end printArray method

    //adds elements into the array being sent over from SequenceTest.
    //this method is used when creating a new array, it will add elements
    //one a time from the txt file to the array in order.
    public void createArray(int element, int count)
    {

        data[count] = element;
        manyItems++;
        currentIndex = count;

    }//creatArray method

}//end DoubleArraySeq class