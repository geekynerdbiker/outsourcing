package server;

import user.User;

import match.Betting;
import match.Match;

import utils.ErrorCode;

import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.*;
import java.text.SimpleDateFormat;

public class Server {
    public String currentTime;
    private Map<Integer, Match> matchList;
    private Map<String, User> userList;

    private SimpleDateFormat formatter = new SimpleDateFormat("yyyy/MM/dd HH:mm");

    private String DATA_FOLDER = "data/";

    public Server(String currentTime) {
        this.matchList = getMatchList();
        this.userList = getUserList();
        this.currentTime = currentTime;
    }

    public Server(String currentTime, String data_folder) {
        this(currentTime);
        this.DATA_FOLDER = data_folder;
    }

    public void setCurrentTime(String currentTime){
        this.currentTime = currentTime;
    }

    public Map<Integer, Match> getMatchList() {
        // Save match info
        Map<Integer, Match> matchList = new TreeMap();
        File matchRootDirFile = new File(String.format("%s/Matches", DATA_FOLDER));
        File[] sportsDirFiles = matchRootDirFile.listFiles();
        if (sportsDirFiles == null) {
            // No such directory or IO exception
            return new TreeMap<Integer, Match>();
        }
        for (File sportsDirFile: sportsDirFiles) {
            String sportsType = sportsDirFile.getName();
            if (sportsDirFile.isDirectory()) {
                for (File matchDir: sportsDirFile.listFiles()) {
                    if (matchDir.isDirectory()) {
                        for (File matchFile : matchDir.listFiles()) {

                            if (matchFile.getName().endsWith("_info.txt")) {
                                int matchId = Integer.parseInt(matchFile.getName().substring(0, matchFile.getName().length() - 9));

                                String matchInfo = null;
                                try {
                                    matchInfo = Files.readString(Paths.get(matchFile.getAbsolutePath()));
                                } catch (IOException e) {
                                    e.printStackTrace();
                                }
                                String[] infos = matchInfo.split("\\|");
                                int numBets = Integer.parseInt(infos[4]);
                                double[] currentOdds = new double[numBets];
                                for (int i = 0; i < numBets; i++) {
                                    currentOdds[i] = Double.parseDouble(infos[5 + i]);
                                }

                                matchList.put(matchId, new Match(
                                                matchId,
                                                sportsType,
                                                infos[0], // home team
                                                infos[1], // away team
                                                infos[3], // match time
                                                infos[2], // location
                                                numBets, // the number of possible betting sides
												currentOdds
                                        )
                                );
                            }
                        }
                    }
                }
            }
        }
        return matchList;
    }

    public Map<String, User> getUserList() {
        // Save match info
        if (userList == null){
            userList= new TreeMap();
        }
        File userRootDirFile = new File(String.format("%s/Users", DATA_FOLDER));
        File[] userRootDirFiles = userRootDirFile.listFiles();
        if (userRootDirFiles == null) {
            // No such directory or IO exception
            return null;
        }
        for (File userDirFile: userRootDirFiles) {
            String userId = userDirFile.getName();
            if (userList.get(userId) == null) {
                userList.put(userId, new User(userId, DATA_FOLDER));
            }
        }

        return userList;
    }

    private Match searchMatch(int matchId) {
        return matchList.get(matchId);
    }

    private User searchUser(String userId){
        return userList.get(userId);
    }

    private long compareTimes(String time1, String time2){
        try {
            long time1ToLong = formatter.parse(time1).getTime();
            long time2ToLong = formatter.parse(time2).getTime();

            return Long.compare(time1ToLong, time2ToLong);
        } catch (Exception e){
            e.printStackTrace();
        }
        
        return 0;
    }

    public List<Match> search(Map<String,Object> searchConditions, String sortCriteria){
        // TODO Problem 2-1

        return searchResult;
    }

    public int collectBettings(){
        // TODO Problem 2-2

        return ErrorCode.SUCCESS;
    }

    public List<Betting> getBettingBook(int matchId){
        // TODO Problem 2-2

        return bettingBook;
    }

    public boolean settleMatch(int matchId, int winNumber){
        // TODO Problem 2-3

        return true;
    }
}
