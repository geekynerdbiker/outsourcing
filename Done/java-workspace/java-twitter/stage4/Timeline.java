package stage4;

import stage1.User;
import stage2.Reply;
import stage3.Tweet;

/**
 * Represents Tweet recommendations to a specific user. This user is the
 * 'owner' of the Timeline.
 *
 * @author mic
 */

public class Timeline {

    public User owner;
    public Tweet[] tweets;

    /**
     * @param u - the user to check for
     * @return the number of Tweet objects in 'tweets' whose 'poster' is equal to
     * the passed User object 'u'. Hint: use the equals function to compare
     * User objects.
     */
    public int countTweets(User u) {
        // TODO To be completed
        int count = 0;

        if (tweets != null && u != null) {
            for (Tweet t : tweets) {
                if (t.poster.equals(u)) {
                    count++;
                }
            }
        }
        return count;
    }


    /**
     * @return the User object who is the poster of the most Tweet objects in
     * 'tweets', i.e. the User who has made the most Tweets. Return null if
     * 'tweets' is null or 'tweets' is of length 0.
     */
    public User mostTweets() {
        // TODO To be completed
        User mostTweets = null;
        int maxCount = 0;
        if (tweets == null || tweets.length == 0) {
            return null;
        }
        for (Tweet t : tweets) {
            int count = countTweets(t.poster);
            if (count > maxCount) {
                maxCount = count;
                mostTweets = t.poster;
            }
        }

        return mostTweets;
    }

    /**
     * @return the User who has had the most activity. Activity is defined as the
     * number of Tweets posted plus the number of replies made. Return null
     * if 'tweets' is null or 'tweets' is of length 0. You may assume that
     * every User has made at least one Tweet, i.e. there are no Users who
     * have ONLY made replies.
     */
    public User mostActivity() {
        // TODO To be completed
        User[] userList = new User[100];
        int[] mostActivity = new int[100];
        int maxCount = 0, maxIndex = 0;

        int userIdx = 0;
        if (tweets == null || tweets.length == 0) {
            return null;
        }

        for (Tweet t : tweets) {
            boolean userExist = false;

            for (int i = 0; i < userIdx; i++) {
                if (userList[i] == t.poster) {
                    userExist = true;
                    break;
                }
            }
                if (!userExist) {
                    userList[userIdx] = t.poster;
                    mostActivity[userIdx] = 0;
                    userIdx++;
                }
            for (Reply r : t.replies) {
                userExist = false;
                for (int i = 0; i < userIdx; i++) {
                    if (userList[i] == r.from) {
                        userExist = true;
                        break;
                    }
                }
                    if (!userExist) {
                        userList[userIdx] = r.from;
                        mostActivity[userIdx] = 0;
                        userIdx++;
                    }
                for (User u : r.to) {
                    userExist = false;
                    for (int i = 0; i < userIdx; i++) {
                        if (userList[i] == u) {
                            userExist = true;
                            break;
                        }
                    }
                    if (!userExist) {
                        userList[userIdx] = u;
                        mostActivity[userIdx] = 0;
                        userIdx++;
                    }
                }
            }
        }

        for (int i = 0; i < userIdx; i++) {
            for (Tweet t : tweets) {
                if (t.poster == userList[i])
                    mostActivity[i]++;
                for (Reply r : t.replies) {
                    if (r.from == userList[i])
                        mostActivity[i]++;
                    for (User u : r.to)
                        if (u == userList[i])
                            mostActivity[i]++;
                }
            }
        }

        for (int i = 0; i < userIdx; i++)
            if (mostActivity[i] > maxCount) {
                maxCount = mostActivity[i];
                maxIndex = i;
            }

        return userList[maxIndex];
    }

    /**
     * @return an array of Tweet objects containing all Tweets made by the owner of
     * the timeline, i.e. all Tweets the owner has posted. Return null if
     * 'owner' or 'tweets' is null. Hint: use the equals function to compare
     * User objects.
     */
    public Tweet[] getAllTweetsByTimelineOwner() {
        // TODO To be completed
        if (owner == null || tweets == null) {
            return null;
        }
        int count = 0;
        for (Tweet t : tweets) {
            if (t.poster.equals(owner)) {
                count++;
            }
        }
        Tweet[] ownerTweets = new Tweet[count];
        int index = 0;
        for (Tweet t : tweets) {
            if (t.poster.equals(owner)) {
                ownerTweets[index] = t;
                index++;
            }
        }
        return ownerTweets;
    }

    /**
     * @return a String which represents the Timeline object.
     * The String should follow the below format (with the actual Timeline data used).
     * Hint: the \n character adds a new line
     * For example:
     * <p>
     * Timeline Owner: mic1511
     * ----------
     * <p>
     * => Poster: traveler
     * => Message: This is the first message!!!!
     * <p>
     * Replying to @mic1511, @Janedoe, @traveler
     * This is a test message
     * Replying to @traveler, @Charlie, @Foodie
     * This is another test message!!!
     * <p>
     * ----------
     * <p>
     * => Poster: traveler
     * => Message: Wow this is the second Tweet in this timeline :O
     * <p>
     * Replying to @mic1511, @Janedoe, @traveler
     * This is a test message
     * Replying to @traveler, @Charlie, @Foodie
     * This is another test message!!!
     * <p>
     * ----------
     * <p>
     * => Poster: Janedoe
     * => Message: Finally at the last one now
     * <p>
     * Replying to no one
     * This is the last message in this Timeline
     * <p>
     * ----------
     */
    public String printTimeline() {
        // TODO To be completed
        StringBuilder sb = new StringBuilder();
        sb.append("Timeline Owner: ");
        sb.append(owner.handle);
        sb.append("\n----------\n");
        if (tweets != null) {
            for (Tweet t : tweets) {
                sb.append("\n=> Poster: ");
                sb.append(t.poster.handle);
                sb.append("\n=> Message: ");
                sb.append(t.message);
                sb.append("\n\n");


                    for (Reply r : t.replies) {
                        int idx = 0;
                        int len = r.to.length;

                        sb.append("Replying to ");
                        boolean isReplied = false;
                        for (User u : r.to) {
                            isReplied = true;
                            sb.append("@").append(u.handle);

                            if (++idx < len) {
                                sb.append(", ");
                            }
                        }

                        if (!isReplied)
                            sb.append("no one");
                        sb.append("\n");
                        sb.append(r.message);
//                        for (int i = 1; i < t.replies.length; i++) {
//                            sb.append("\n").append(t.replies[i].message);
//                        }
                        sb.append("\n");
                    }
                sb.append("\n----------\n");
                }

        } else {
            sb.append("\nNo tweets\n");
            sb.append("\n----------\n");
        }
        return sb.toString();
    }


    /**
     * @param term - the term to look for
     * @return the number of Tweet objects with either a message that contains the passed
     * 'term' or has a Reply whose message contains the passed term.
     * If the 'term' appears in a Tweet objects message and in its replies,
     * it should be counted once.
     */
    public int countSearchResults(String term) {
        //TODO To be completed
        int count = 0;
        if (tweets != null) {
            for (Tweet t : tweets) {
                boolean isContains = false;
                if (t.message.contains(term)) {
                    isContains = true;
                    count++;
                    continue;
                }
                for (Reply r : t.replies) {
                    if (r.message.contains(term)) {
                        isContains = true;
                        break;
                    }
                }
                if (isContains)
                    count++;
            }
        }
        return count;
    }

    /**
     * @param term - the term to look for
     * @return an array of Tweet objects from 'tweets' which match any of the
     * following criteria: 1) the Tweet has a poster whose handle contains
     * 'term', 2) the Tweet contains a message containing 'term', 3) the
     * Tweet contains any replies whose message contains 'term' and 4) the
     * tweet contains any replies whose 'from' and 'to' User objects have a
     * handle containing 'term'.
     */
    public Tweet[] searchAll(String term) {
        // TODO To be completed
        if (tweets == null || term == null) {
            return null;
        }
        int count = 0;
        for (Tweet tweet : tweets) {
            if (tweet.poster.handle.contains(term) || tweet.message.contains(term)) {
                count++;
            } else {
                for (int i = 0; i < tweet.replies.length; i++) {
                    if (tweet.replies[i].message.contains(term)
                            || tweet.replies[i].from.handle.contains(term)) {
                        count++;
                        break;
                    } else {
                        for (int j = 0; j < tweet.replies[i].to.length; j++) {
                            if (tweet.replies[i].to[j].handle.contains(term)) {
                                count++;
                                break;
                            }
                        }
                    }
                }
            }
        }

        Tweet[] result = new Tweet[count];
        int index = 0;
        for (Tweet tweet : tweets) {
            if (tweet.poster.handle.contains(term) || tweet.message.contains(term)) {
                result[index] = tweet;
                index++;
            } else {
                for (int i = 0; i < tweet.replies.length; i++) {
                    if (tweet.replies[i].message.contains(term)
                            || tweet.replies[i].from.handle.contains(term)) {
                        result[index] = tweet;
                        index++;
                        break;
                    } else {
                        for (int j = 0; j < tweet.replies[i].to.length; j++) {
                            if (tweet.replies[i].to[j].handle.contains(term)) {
                                result[index] = tweet;
                                index++;
                                break;
                            }
                        }
                    }
                }
            }
        }

        return result;
    }

    /**
     * DO NOT MODIFY
     */
    public Timeline(User owner, Tweet[] tweets) {
        this.owner = owner;
        this.tweets = tweets;
    }

}