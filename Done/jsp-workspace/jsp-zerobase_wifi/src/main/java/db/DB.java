package db;

import java.io.*;
import java.net.URL;
import java.sql.*;
import java.util.*;

import org.json.simple.*;
import org.json.simple.parser.JSONParser;

public class DB {
	static String key = "68517658566d6f6f343375674a574c";
	
	public List<String[]> dbHistorySelect() {
		List<String[]> wifiHistory = new ArrayList<>();
		
		
		String url = "jdbc:mariadb://127.0.0.1:3306/wifi";
		String dbUserId = "root";
		String dbPassword = "";

		try {
			Class.forName("org.mariadb.jdbc.Driver");
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		}

		Connection connection = null;
		PreparedStatement preparedStatement = null;
		ResultSet rs = null;

		try {		
			connection = DriverManager.getConnection(url, dbUserId, dbPassword);

			String sql = " select * from wifi_history";

			preparedStatement = connection.prepareStatement(sql);

			rs = preparedStatement.executeQuery();

			while (rs.next()) {
				String[] history = new String[4];
				history[0] = rs.getString("ID");
				history[1] = rs.getString("LAT");
				history[2] = rs.getString("LNT");
				history[3] = rs.getString("Date");

				wifiHistory.add(history);
			}

		} catch (SQLException e) {
			e.printStackTrace();

		} finally {
			try {
				if (rs != null && !rs.isClosed()) {
					rs.close();
				}
			} catch (SQLException e) {
				e.printStackTrace();
			}

			try {
				if (preparedStatement != null && !preparedStatement.isClosed()) {
					preparedStatement.close();
				}
			} catch (SQLException e) {
				e.printStackTrace();
			}

			try {
				if (connection != null && !connection.isClosed()) {
					connection.close();
				}
			} catch (SQLException e) {
				e.printStackTrace();
			}
		}
		return wifiHistory;
	}

	public void dbHistoryInsert(String LAT, String LNT) {
		String dbUrl = "jdbc:mariadb://127.0.0.1:3306/wifi";
		String dbUserId = "root";
		String dbPassword = "";

		try {
			Class.forName("org.mariadb.jdbc.Driver");
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		}

		Connection connection = null;
		PreparedStatement preparedStatement = null;
		ResultSet rs = null;

		try {
			connection = DriverManager.getConnection(dbUrl, dbUserId, dbPassword);

			String sql = " insert into wifi_history (LAT,LNT,Date) values (?, ?, now())";
			
			preparedStatement = connection.prepareStatement(sql);
			preparedStatement.setString(1, LNT);
			preparedStatement.setString(2, LAT);

			try {
				int affected = preparedStatement.executeUpdate();
				if (affected > 0) {
					System.out.println(" 저장 성공 ");
				} else {
					System.out.println(" 저장 실패 ");
				}
			} catch (SQLException e) {
				e.printStackTrace();
			}

		} catch (SQLException e) {
			System.out.println("SQLException 에러");
			e.printStackTrace();

		} catch (Exception e) {
			System.out.println("Exception 에러");
			e.printStackTrace();

		} finally {
			try {
				if (rs != null && !rs.isClosed()) {
					rs.close();
				}
			} catch (SQLException e) {
				e.printStackTrace();
			}

			try {
				if (preparedStatement != null && !preparedStatement.isClosed()) {
					preparedStatement.close();
				}
			} catch (SQLException e) {
				e.printStackTrace();
			}

			try {
				if (connection != null && !connection.isClosed()) {
					connection.close();
				}
			} catch (SQLException e) {
				e.printStackTrace();
			}
		}
	}

	public List<data> dbSelect(String address) {

		List<data> wifiList = new ArrayList<>();

		String url = "jdbc:mariadb://127.0.0.1:3306/wifi";
		String dbUserId = "root";
		String dbPassword = "";

		try {
			Class.forName("org.mariadb.jdbc.Driver");
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		}

		Connection connection = null;
		PreparedStatement preparedStatement = null;
		ResultSet rs = null;

		try {
			connection = DriverManager.getConnection(url, dbUserId, dbPassword);

			String sql = " select * from wifi_list where WRDOFC = ? order by DIST ";

			preparedStatement = connection.prepareStatement(sql);
			preparedStatement.setString(1, address);

			rs = preparedStatement.executeQuery();

			while (rs.next()) {
				String DIST = rs.getString("DIST");
				String MGR_NO = rs.getString("MGR_NO");
				String WRDOFC = rs.getString("WRDOFC");
				String MAIN_NM = rs.getString("MAIN_NM");
				String ADRES1 = rs.getString("ADRES1");
				String ADRES2 = rs.getString("ADRES2");
				String INSTL_FLOOR = rs.getString("INSTL_FLOOR");
				String INSTL_TY = rs.getString("INSTL_TY");
				String INSTL_MBY = rs.getString("INSTL_MBY");
				String SVC_SE = rs.getString("SVC_SE");
				String CMCWR = rs.getString("CMCWR");
				String CNSTC_YEAR = rs.getString("CNSTC_YEAR");
				String INOUT_DOOR = rs.getString("INOUT_DOOR");
				String REMARS3 = rs.getString("REMARS3");
				String LAT = rs.getString("LAT");
				String LNT = rs.getString("LNT");
				String WORK_DTTM = rs.getString("WORK_DTTM");

				data wifi = new data();
				wifi.setDIST(DIST);
				wifi.setMGR_NO(MGR_NO);
				wifi.setWRDOFC(WRDOFC);
				wifi.setMAIN_NM(MAIN_NM);
				wifi.setADRES1(ADRES1);
				wifi.setADRES2(ADRES2);
				wifi.setINSTL_FLOOR(INSTL_FLOOR);
				wifi.setINSTL_TY(INSTL_TY);
				wifi.setINSTL_MBY(INSTL_MBY);
				wifi.setSVC_SE(SVC_SE);
				wifi.setCMCWR(CMCWR);
				wifi.setCNSTC_YEAR(CNSTC_YEAR);
				wifi.setINOUT_DOOR(INOUT_DOOR);
				wifi.setREMARS3(REMARS3);
				wifi.setLAT(LAT);
				wifi.setLNT(LNT);
				wifi.setWORK_DTTM(WORK_DTTM);

				wifiList.add(wifi);
			}

		} catch (SQLException e) {
			e.printStackTrace();

		} finally {
			try {
				if (rs != null && !rs.isClosed()) {
					rs.close();
				}
			} catch (SQLException e) {
				e.printStackTrace();
			}

			try {
				if (preparedStatement != null && !preparedStatement.isClosed()) {
					preparedStatement.close();
				}
			} catch (SQLException e) {
				e.printStackTrace();
			}

			try {
				if (connection != null && !connection.isClosed()) {
					connection.close();
				}
			} catch (SQLException e) {
				e.printStackTrace();
			}
		}

		return wifiList;
	}

	public void dbUpdate(String lat, String lnt, String address) {
		String dbUrl = "jdbc:mariadb://127.0.0.1:3306/wifi";
		String dbUserId = "root";
		String dbPassword = "";
		Double lat2 = Double.parseDouble(lat);
		Double lnt2 = Double.parseDouble(lnt);
		Double coefficient = Math.cos(lat2) * 6400 * 2 * 3.14 / 360;

		try {
			Class.forName("org.mariadb.jdbc.Driver");
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		}

		Connection connection = null;
		PreparedStatement preparedStatement = null;
		ResultSet rs = null;

		try {
			connection = DriverManager.getConnection(dbUrl, dbUserId, dbPassword);

			String sql = " select * from wifi_list where WRDOFC = ?";
			preparedStatement = connection.prepareStatement(sql);
			preparedStatement.setString(1, address);
			rs = preparedStatement.executeQuery();

			while (rs.next()) {
				Double lnt1 = Double.parseDouble(rs.getString("LAT"));
				Double lat1 = Double.parseDouble(rs.getString("LNT"));
				Double distX = coefficient * Math.abs(lnt1 - lnt2);
				Double distY = 111 * Math.abs(lat1 - lat2);
				String disT = String.format("%.3f", Math.sqrt(distX * distX + distY * distY)) + "km";
				sql = " update wifi_list set DIST = ? where MGR_NO = ? ";
				preparedStatement = connection.prepareStatement(sql);
				preparedStatement.setString(1, disT);
				preparedStatement.setString(2, rs.getString("MGR_NO"));

				try {
					int affected = preparedStatement.executeUpdate();
					if (affected > 0) {
						System.out.println(" 저장 성공 ");
					} else {
						System.out.println(" 저장 실패 ");
					}
				} catch (SQLException e) {
					e.printStackTrace();
				}
			}
		} catch (SQLException e) {
			System.out.println("SQLException 에러");
			e.printStackTrace();

		} catch (Exception e) {
			System.out.println("Exception 에러");
			e.printStackTrace();

		} finally {
			try {
				if (rs != null && !rs.isClosed()) {
					rs.close();
				}
			} catch (SQLException e) {
				e.printStackTrace();
			}

			try {
				if (preparedStatement != null && !preparedStatement.isClosed()) {
					preparedStatement.close();
				}
			} catch (SQLException e) {
				e.printStackTrace();
			}

			try {
				if (connection != null && !connection.isClosed()) {
					connection.close();
				}
			} catch (SQLException e) {
				e.printStackTrace();
			}
		}
	}

	public String[] dbInsert(String startData, String endData) {
		String dbUrl = "jdbc:mariadb://127.0.0.1:3306/wifi";
		String dbUserId = "root";
		String dbPassword = "";

		String[] resultReturn = new String[2];

		try {
			Class.forName("org.mariadb.jdbc.Driver");
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		}

		Connection connection = null;
		PreparedStatement preparedStatement = null;
		ResultSet rs = null;

		String result = "";

		try {
			URL url = new URL(
					"http://openapi.seoul.go.kr:8088/" + key + "/json/TbPublicWifiInfo/" + startData + "/" + endData);

			BufferedReader bf;

			bf = new BufferedReader(new InputStreamReader(url.openStream(), "UTF-8"));

			result = bf.readLine();

			JSONParser jsonParser = new JSONParser();
			JSONObject jsonObject = (JSONObject) jsonParser.parse(result);
			JSONObject wifiInfo = (JSONObject) jsonObject.get("TbPublicWifiInfo");
			String dataCnt = wifiInfo.get("list_total_count").toString();
			resultReturn[0] = dataCnt;
			System.out.println("전체 데이터 개수 : " + dataCnt);

			JSONObject resultJSON = (JSONObject) (wifiInfo.get("RESULT"));
			String resultMsg = resultJSON.get("MESSAGE").toString();
			String resultCode = resultJSON.get("CODE").toString();
			resultReturn[1] = resultMsg;
			System.out.println("데이터 가져오기 결과 : " + resultMsg);
			System.out.println("데이터 가져오기 결과 코드 : " + resultCode);

			JSONArray wifiList = (JSONArray) wifiInfo.get("row");

			connection = DriverManager.getConnection(dbUrl, dbUserId, dbPassword);

			for (int i = 0; i < wifiList.size(); i++) {
				JSONObject obj = (JSONObject) wifiList.get(i);
				String MGR_NO = (String) obj.get("X_SWIFI_MGR_NO");
				String WRDOFC = (String) obj.get("X_SWIFI_WRDOFC");
				String MAIN_NM = (String) obj.get("X_SWIFI_MAIN_NM");
				String ADRES1 = (String) obj.get("X_SWIFI_ADRES1");
				String ADRES2 = (String) obj.get("X_SWIFI_ADRES2");
				String INSTL_FLOOR = (String) obj.get("X_SWIFI_INSTL_FLOOR");
				String INSTL_TY = (String) obj.get("X_SWIFI_INSTL_TY");
				String INSTL_MBY = (String) obj.get("X_SWIFI_INSTL_MBY");
				String SVC_SE = (String) obj.get("X_SWIFI_SVC_SE");
				String CMCWR = (String) obj.get("X_SWIFI_CMCWR");
				String CNSTC_YEAR = (String) obj.get("X_SWIFI_CNSTC_YEAR");
				String INOUT_DOOR = (String) obj.get("X_SWIFI_INOUT_DOOR");
				String REMARS3 = (String) obj.get("X_SWIFI_REMARS3");
				String LAT = (String) obj.get("LAT");
				String LNT = (String) obj.get("LNT");
				String WORK_DTTM = (String) obj.get("WORK_DTTM");

				String sql = " insert into wifi_list (MGR_NO, WRDOFC, MAIN_NM, ADRES1, ADRES2, INSTL_FLOOR, INSTL_TY, "
						+ "INSTL_MBY, SVC_SE, CMCWR, CNSTC_YEAR, INOUT_DOOR, REMARS3, LAT, LNT, WORK_DTTM) values (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";

				preparedStatement = connection.prepareStatement(sql);
				preparedStatement.setString(1, MGR_NO);
				preparedStatement.setString(2, WRDOFC);
				preparedStatement.setString(3, MAIN_NM);
				preparedStatement.setString(4, ADRES1);
				preparedStatement.setString(5, ADRES2);
				preparedStatement.setString(6, INSTL_FLOOR);
				preparedStatement.setString(7, INSTL_TY);
				preparedStatement.setString(8, INSTL_MBY);
				preparedStatement.setString(9, SVC_SE);
				preparedStatement.setString(10, CMCWR);
				preparedStatement.setString(11, CNSTC_YEAR);
				preparedStatement.setString(12, INOUT_DOOR);
				preparedStatement.setString(13, REMARS3);
				preparedStatement.setString(14, LAT);
				preparedStatement.setString(15, LNT);
				preparedStatement.setString(16, WORK_DTTM);

				try {
					int affected = preparedStatement.executeUpdate();
					if (affected > 0) {
						System.out.println(" 저장 성공 ");
					} else {
						System.out.println(" 저장 실패 ");
					}
				} catch (SQLException e) {
					continue;
				}
			}

		} catch (SQLException e) {
			System.out.println("SQLException 에러");
			e.printStackTrace();

		} catch (Exception e) {
			System.out.println("Exception 에러");
			e.printStackTrace();

		} finally {
			try {
				if (rs != null && !rs.isClosed()) {
					rs.close();
				}
			} catch (SQLException e) {
				e.printStackTrace();
			}

			try {
				if (preparedStatement != null && !preparedStatement.isClosed()) {
					preparedStatement.close();
				}
			} catch (SQLException e) {
				e.printStackTrace();
			}

			try {
				if (connection != null && !connection.isClosed()) {
					connection.close();
				}
			} catch (SQLException e) {
				e.printStackTrace();
			}
		}

		return resultReturn;
	}
	
	public static void main(String[] args) {
		DB db = new DB();
		
		db.dbUpdate("37.5618839742693", "126.96669021575374", "강남구" );
	}

}
