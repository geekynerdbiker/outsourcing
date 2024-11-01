package stage5;

import stage1.User;
import stage3.Tweet;
import stage4.Timeline;


public class Twitter {
    public Timeline[] timelines;
    public User[] users;

    /**
     * @param a - the first User
     * @param b - the second User
     * @return the number of User objects that both User a and b are following.
     * Hint: use equals when comparing String objects.
     */
    public int countIntersection(User a, User b) {
        // TODO To be completed
        int count = 0;
        for (int i = 0; i < a.following.length; i++) {
            for (int j = 0; j < b.following.length; j++) {
                if (a.following[i].equals(b.following[j])) {
                    count++;
                }
            }
        }
        return count;
    }

    /**
     * @return return one unique instance of each Tweet object, i.e. If a Tweet
     * appears in two timelines, only one copy of the Tweet should be
     * returned. Hint: use the equals function to compare Tweet objects.
     */
    public Tweet[] removeDuplicates() {
        // TODO To be completed
        if (timelines == null || timelines.length == 0) {
            return null;
        }
        Tweet[] tweets = new Tweet[100];

        int tweetIndex = 0;
        for (Timeline tl : timelines) {
            for (Tweet t : tl.tweets) {
                tweets[tweetIndex++] = t;
            }
        }

        int unique =  tweetIndex;
        for (int i = 0; i < tweetIndex; i++)
            for (int j = i + 1; j < tweetIndex; j++) {
                if (tweets[i] != null && tweets[j] != null && tweets[i] == tweets[j]) {
                    tweets[j] = null;
                    unique--;
                }
            }
        Tweet[] result = new Tweet[unique];
        int resultIndex = 0;
        for (int i = 0; i < tweetIndex; i++)
            if (tweets[i] != null)
                result[resultIndex++] = tweets[i];


        return result;
    }

    /**
     * @return a 2D array where each sub array contains two User objects that are
     * following each other. You will need to compare the handles of users
     * against the 'following' String arrays in each User. Hint: You can
     * ignore the 'timelines' instance variable for this question.
     */
    public User[][] mutuallyFollowing() {
        // TODO To be completed

        if (this.users == null || this.users.length == 0)
            return null;

        User[][] resultTemp = new User[this.users.length * this.users.length][2];

        int userIndex = 0;
        for (User u1: this.users)
            for  (String s1: u1.following)
                for (User u2: this.users) {
                    if (u1 == u2)
                        continue;
                    if (u2.handle.equals(s1))
                        for (String s2 : u2.following)
                            if (u1.handle.equals(s2))
                                resultTemp[userIndex++] = new User[]{u2, u1};
                }

        User[][] result = new User[userIndex][];
        System.arraycopy(resultTemp, 0, result, 0, userIndex);

        return result;
    }

    /**
     * @return a 2D array where each sub array contains Tweet objects from different
     * users, i.e. sub array 1 will contain all tweets by user "A", sub
     * array 2 will contain all tweets by user "B" and so forth. You can
     * assume that the 'users' instance variable contains all the users
     * which have posted in each Timeline. You must ensure that you do not
     * add duplicate tweets into the final result (Hint:
     * removeDuplicates()). The order of sub arrays is determined by the
     * 'users' instance variable. All posts made by user[0] will appear in
     * the first sub array, all posts made by user[1] will appear in the
     * second sub array and so forth. The order of Tweet objects in each sub
     * array is determined by their order of appearance in each Timeline.
     */
    public Tweet[][] arrangeByPoster() {
        // TODO To be completed

        if (this.timelines == null || this.timelines.length == 0)
            return null;

        Tweet[][] resultTemp = new Tweet[this.users.length][100];
        Tweet[] tweets = this.removeDuplicates();
        int[] sizes = new int[this.users.length];
        boolean[] copied = new boolean[tweets.length];

        int userIdx = 0;
        for (User u : this.users) {
            int tweetIndex = 0;
            for (int j = 0; j < tweets.length; j++) {
                if (!copied[j]) {
                    if (u == tweets[j].poster) {
                        resultTemp[userIdx][tweetIndex++] = tweets[j];
                        sizes[userIdx]++;
                        copied[j] = true;
                    }
                }
            }
            userIdx++;
        }

        Tweet[][] result = new Tweet[this.users.length][];
        for (int i = 0; i < resultTemp.length; i++) {
            result[i] = new Tweet[sizes[i]];

            if (sizes[i] >= 0)
                System.arraycopy(resultTemp[i], 0, result[i], 0, sizes[i]);
        }

        return result;
    }

    /**
     * DO NOT MODIFY
     */
    public Twitter(Timeline[] timelines, User[] users) {
        this.timelines = timelines;
        this.users = users;
    }

}
