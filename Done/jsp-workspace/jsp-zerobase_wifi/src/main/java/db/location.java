package db;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.*;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.JSONValue;

public class location{
	static String key = "AIzaSyDaob8Q3U7oJEr-jqRoxo6KaGSOFQHXUKo";
	double latitude;
	double longitude;
	String regionAddress;
	String[] address;

	public location(String latitude, String longitude) throws Exception {
		this.latitude = Double.parseDouble(latitude);
		this.longitude = Double.parseDouble(longitude);
		this.regionAddress = getRegionAddress(getJSONData(getApiAddress()));
		this.address = regionAddress.split(" ");
	}

	private String getApiAddress() {
		String apiURL = "https://maps.googleapis.com/maps/api/geocode/json?latlng="
				+ latitude + "," + longitude + "&language=ko&key=" + key;
		return apiURL;
	}

	private String getJSONData(String apiURL) throws Exception {
		String jsonString = new String();
		String buf;
		URL url = new URL(apiURL);
		URLConnection conn = url.openConnection();
		BufferedReader br = new BufferedReader(new InputStreamReader(conn.getInputStream(), "UTF-8"));
		while ((buf = br.readLine()) != null) {
			jsonString += buf;
		}
		return jsonString;
	}

	private String getRegionAddress(String jsonString) {
		JSONObject jObj = (JSONObject) JSONValue.parse(jsonString);
		JSONArray jArray = (JSONArray) jObj.get("results");
		jObj = (JSONObject) jArray.get(0);
		return (String) jObj.get("formatted_address");
	}

	public String getRegionAddress() {
		return regionAddress;
	}
	
	public String[] getAddress() {
		return address;
	}
	
	public static void main(String[] args) throws Exception {
		String latitude = "37.57453752202114";
		String longitude = "126.93275787190242";

		location gps = new location(latitude, longitude);
		System.out.println(gps.getRegionAddress());
	}
}