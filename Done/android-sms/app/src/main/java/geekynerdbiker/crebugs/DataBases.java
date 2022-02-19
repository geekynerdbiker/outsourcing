package geekynerdbiker.crebugs;

import android.provider.BaseColumns;

public final class DataBases {

    public static final class CreateDB implements BaseColumns {
        public static final String SENDER = "sender";
        public static final String RECEIVEDDATE = "receivedDate";
        public static final String CONTENTS = "contents";
        public static final String _TABLENAME0 = "sms";
        public static final String _CREATE0 = "create table if not exists " + _TABLENAME0 + "("
                + _ID + " integer primary key autoincrement, "
                + SENDER + " text not null , "
                + RECEIVEDDATE + " text not null , "
                + CONTENTS + " text not null );";
    }
}