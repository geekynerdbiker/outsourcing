package db;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.URL;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;

import java.io.IOException;

public class api {
	static String key = "474f68495566726f38334c48535250";
	public static void main(String[] args) throws IOException {
		String startData = "1";
		String endData = "2";
		String result = "";
		
		try {
			URL url = new URL("http://openapi.seoul.go.kr:8088/" + key + "/json/TbPublicWifiInfo/" + startData + "/" + endData);
			
			BufferedReader bf;
			
			bf = new BufferedReader(new InputStreamReader(url.openStream(), "UTF-8"));
			
			result = bf.readLine();
			
			JSONParser jsonParser = new JSONParser();
			JSONObject jsonObject = (JSONObject)jsonParser.parse(result);
			JSONObject wifiInfo = (JSONObject)jsonObject.get("TbPublicWifiInfo");
			String dataCnt = wifiInfo.get("list_total_count").toString();
			System.out.println("전체 데이터 개수 : " + dataCnt);
			
			
			JSONObject resultJSON = (JSONObject) (wifiInfo.get("RESULT"));
			String resultMsg = resultJSON.get("MESSAGE").toString();
			String resultCode = resultJSON.get("CODE").toString();
			System.out.println("데이터 가져오기 결과 : " + resultMsg);
			System.out.println("데이터 가져오기 결과 코드 : " + resultCode);
			
			JSONArray wifiList = (JSONArray)wifiInfo.get("row");
			
        	
			
        	for (int i = 0; i < wifiList.size(); i++) {
        		JSONObject obj = (JSONObject)wifiList.get(i);
        		System.out.println(obj);
        		String MGR_NO = (String)obj.get("X_SWIFI_MGR_NO");
        		String WRDOFC = (String)obj.get("X_SWIFI_WRDOFC");
        		String MAIN_NM = (String)obj.get("X_SWIFI_MAIN_NM");
        		String ADRES1 = (String)obj.get("X_SWIFI_ADRES1");
        		String ADRES2 = (String)obj.get("X_SWIFI_ADRES2");
        		String INSTL_FLOOR = (String)obj.get("X_SWIFI_INSTL_FLOOR");
        		String INSTL_TY = (String)obj.get("X_SWIFI_INSTL_TY");
        		String INSTL_MBY = (String)obj.get("X_SWIFI_INSTL_MBY");
        		String SVC_SE = (String)obj.get("X_SWIFI_SVC_SE");
        		String CMCWR = (String)obj.get("X_SWIFI_CMCWR");
        		String CNSTC_YEAR = (String)obj.get("X_SWIFI_CNSTC_YEAR");
        		String INOUT_DOOR = (String)obj.get("X_SWIFI_INOUT_DOOR");
        		String REMARS3 = (String)obj.get("X_SWIFI_REMARS3");
        		String LAT = (String)obj.get("LAT");
        		String LNT = (String)obj.get("LNT");
        		String WORK_DTTM = (String)obj.get("WORK_DTTM");
        		
        		System.out.println("=====" + (i+1) + "=====");
        		System.out.println("관리번호 : " + MGR_NO);
        		System.out.println("자치구 : " + WRDOFC);
        		System.out.println("와이파이명 : " + MAIN_NM);
        		System.out.println("도로명주소 : " + ADRES1);
        		System.out.println("상세주소 : " + ADRES2);
        		System.out.println("설치위치(층) : " + INSTL_FLOOR);
        		System.out.println("설치유형 : " + INSTL_TY);
        		System.out.println("설치기관 : " + INSTL_MBY);
        		System.out.println("서비스구분 : " + SVC_SE);
        		System.out.println("망종류 : " + CMCWR);
        		System.out.println("설치년도 : " + CNSTC_YEAR);
        		System.out.println("실내외구분 : " + INOUT_DOOR);
        		System.out.println("WiFi접속환경 : " + REMARS3);
        		System.out.println("X좌표 : " + LAT);
        		System.out.println("Y좌표 : " + LNT);
        		System.out.println("작업일자 : " + WORK_DTTM);
        	}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}