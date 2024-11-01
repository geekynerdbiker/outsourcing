package ngordnet.ngrams;

import edu.princeton.cs.algs4.In;
import org.w3c.dom.html.HTMLImageElement;

import java.sql.Time;
import java.util.Collection;
import java.util.HashMap;
import java.util.Iterator;

/**
 * An object that provides utility methods for making queries on the
 * Google NGrams dataset (or a subset thereof).
 * <p>
 * An NGramMap stores pertinent data from a "words file" and a "counts
 * file". It is not a map in the strict sense, but it does provide additional
 * functionality.
 *
 * @author Josh Hug
 */
public class NGramMap {
    /**
     *
     */
    private final HashMap<String, TimeSeries> words;
    private final TimeSeries years;

    /**
     * Constructs an NGramMap from WORDSFILENAME and COUNTSFILENAME.
     */
    public NGramMap(String wordsFilename, String countsFilename) {
        In in = new In(wordsFilename);
        words = new HashMap<>();
        years = new TimeSeries();

        while (in.hasNextLine()) {
            if (in.isEmpty())
                break;

            String word = in.readString();
            Integer year = in.readInt();
            Double count = in.readDouble();

            if (!words.containsKey(word))
                words.put(word, new TimeSeries());
            words.get(word).put(year, count);

            in.readDouble();
        }

        In in2 = new In(countsFilename);

        while (in2.hasNextLine()) {
            if (in2.isEmpty())
                break;

            String[] s = in2.readLine().split(",");
            Integer year = Integer.parseInt(s[0]);
            Double count = Double.parseDouble(s[1]);

            years.put(year, count);
        }
    }

    /**
     * Provides the history of WORD. The returned TimeSeries should be a copy,
     * not a link to this NGramMap's TimeSeries. In other words, changes made
     * to the object returned by this function should not also affect the
     * NGramMap. This is also known as a "defensive copy".
     */
    public TimeSeries countHistory(String word) {
        return (TimeSeries) words.get(word).clone();
    }

    /**
     * Provides the history of WORD between STARTYEAR and ENDYEAR, inclusive of both ends. The
     * returned TimeSeries should be a copy, not a link to this NGramMap's TimeSeries. In other words,
     * changes made to the object returned by this function should not also affect the
     * NGramMap. This is also known as a "defensive copy".
     */
    public TimeSeries countHistory(String word, int startYear, int endYear) {
        TimeSeries ts = words.get(word);
        if (ts == null)
            return null;
        return new TimeSeries(ts, startYear, endYear);
    }

    /**
     * Returns a defensive copy of the total number of words recorded per year in all volumes.
     */
    public TimeSeries totalCountHistory() {
        return (TimeSeries) years.clone();
    }

    /**
     * Provides a TimeSeries containing the relative frequency per year of WORD compared to
     * all words recorded in that year.
     */
    public TimeSeries weightHistory(String word) {
        TimeSeries ts = countHistory(word);
        if (ts == null)
            return null;
        return ts.dividedBy(totalCountHistory());
    }

    /**
     * Provides a TimeSeries containing the relative frequency per year of WORD between STARTYEAR
     * and ENDYEAR, inclusive of both ends.
     */
    public TimeSeries weightHistory(String word, int startYear, int endYear) {
        TimeSeries ts = countHistory(word, startYear, endYear);
        if (ts == null)
            return null;
        return ts.dividedBy(totalCountHistory());
    }

    /**
     * Returns the summed relative frequency per year of all words in WORDS.
     */
    public TimeSeries summedWeightHistory(Collection<String> words) {
        Iterator<String> it = words.iterator();
        TimeSeries sum = new TimeSeries();

        while (it.hasNext()) {
            String s = it.next();
            sum = sum.plus(weightHistory(s));
        }

        return sum;
    }

    /**
     * Provides the summed relative frequency per year of all words in WORDS
     * between STARTYEAR and ENDYEAR, inclusive of both ends. If a word does not exist in
     * this time frame, ignore it rather than throwing an exception.
     */
    public TimeSeries summedWeightHistory(Collection<String> words,
                                          int startYear, int endYear) {
        Iterator<String> it = words.iterator();

        TimeSeries sum = new TimeSeries();
        while (it.hasNext()) {
            String s = it.next();
            sum = sum.plus(weightHistory(s, startYear, endYear));
        }

        return sum;
    }


}
