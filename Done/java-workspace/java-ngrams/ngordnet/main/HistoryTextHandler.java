package ngordnet.main;

import ngordnet.hugbrowsermagic.NgordnetQuery;
import ngordnet.hugbrowsermagic.NgordnetQueryHandler;
import ngordnet.ngrams.NGramMap;
import ngordnet.ngrams.TimeSeries;

import java.util.ArrayList;
import java.util.List;

public class HistoryTextHandler extends NgordnetQueryHandler {

    private NGramMap nGramMap;
    public HistoryTextHandler(NGramMap map) {
        super();
        nGramMap = map;
    }
    @Override
    public String handle(NgordnetQuery q) {
        List<String> words = q.words();
        int startYear = q.startYear();
        int endYear = q.endYear();
        String response = "";
        for (String w: words) {
            TimeSeries wh = nGramMap.weightHistory(w,startYear,endYear);
            if (wh == null) continue;
            response += w+ ": " + wh.toString() + "\n";
        }
        return response;
    }
}
