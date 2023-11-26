package com.dcu.monitoring.web;

import com.dcu.monitoring.domain.test.JSONData;
import com.dcu.monitoring.domain.test.Pair;
import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.servlet.ModelAndView;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

@Controller
public class MonitoringController {

    @RequestMapping("exam") // 연결 test
    public ModelAndView test(Model model) throws IOException, ParseException {
        ModelAndView mav = new ModelAndView();

        BufferedReader br = new BufferedReader(new FileReader("data.json"));
        String data;
        StringBuilder sb = new StringBuilder();
        while ((data = br.readLine()) != null) {
            sb.append(data);
        }
        data = sb.toString();

        JSONParser parser = new JSONParser();
        JSONArray array = (JSONArray) parser.parse(data);

        for (int i = 0; i < array.size(); i++) {
            JSONObject obj = (JSONObject) array.get(i);

            String robotId = (String) obj.get("robotId");
            int state = (int) obj.get("state");
            String[] sp = ((String) obj.get("startPoint")).split(",");
            String[] cp = ((String) obj.get("currentPoint")).split(",");
            String[] np = ((String) obj.get("nextPoint")).split(",");
            String[] tp = ((String) obj.get("targetPoint")).split(",");

            Pair startPoint, currentPoint, nextPoint, targetPoint;
            startPoint = new Pair(Integer.parseInt(sp[0].substring(1)), Integer.parseInt(sp[1].substring(0,sp[1].length()-1)));
            currentPoint = new Pair(Integer.parseInt(cp[0].substring(1)), Integer.parseInt(cp[1].substring(0,cp[1].length()-1)));
            nextPoint = new Pair(Integer.parseInt(np[0].substring(1)), Integer.parseInt(np[1].substring(0,np[1].length()-1)));
            targetPoint = new Pair(Integer.parseInt(tp[0].substring(1)), Integer.parseInt(tp[1].substring(0,tp[1].length()-1)));

            JSONData jsondata = new JSONData(robotId, state, startPoint, currentPoint, nextPoint, targetPoint);
            mav.addObject(jsondata);
            mav.addObject("index", i);
        }
        mav.setViewName("map.jsp");

        return mav;

    }
}
