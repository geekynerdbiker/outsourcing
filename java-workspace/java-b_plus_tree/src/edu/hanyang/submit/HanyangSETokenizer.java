package edu.hanyang.submit;

import org.apache.lucene.analysis.Analyzer;
import org.apache.lucene.analysis.TokenStream;
import org.apache.lucene.analysis.core.SimpleAnalyzer;
import org.apache.lucene.analysis.tokenattributes.CharTermAttribute;
import org.tartarus.snowball.ext.PorterStemmer;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class HanyangSETokenizer1 implements Tokenizer {
    private Analyzer analyzer = null;
    private PorterStemmer stemmer = null;

    @Override
    public void setup() {
        analyzer = new SimpleAnalyzer();
        stemmer = new PorterStemmer();
    }

    @Override
    public List<String> split(String text) {
        ArrayList stemmed = new ArrayList();
        try {
            TokenStream stream = analyzer.tokenStream(null, text);
            stream.reset();
            CharTermAttribute term = stream.getAttribute(CharTermAttribute.class);
            while (stream.incrementToken()) {
                stemmer.setCurrent(term.toString());
                stemmer.stem();
                stemmed.add(stemmer.getCurrent());
                System.out.println(stemmer.getCurrent());
            }
            stream.close();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        return stemmed;
    }

    @Override
    public void clean() {
        analyzer.close();
    }
}
