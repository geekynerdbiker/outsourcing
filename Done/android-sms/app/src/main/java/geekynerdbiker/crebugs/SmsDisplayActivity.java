package geekynerdbiker.crebugs;

import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

import org.jetbrains.annotations.NotNull;

import java.io.File;
import java.io.IOException;

import okhttp3.Call;
import okhttp3.Callback;
import okhttp3.MediaType;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.RequestBody;
import okhttp3.Response;


public class SmsDisplayActivity extends AppCompatActivity { //객체 선언
    private DbOpenHelper mDbOpenHelper;
    Button btnTitle, btnClose;
    TextView tvMsg;
    final String DB_ADDRESS = Environment.getDataDirectory().getAbsolutePath() + "/data/" + "geekynerdbiker.crebugs" + "/databases/sms.db";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_sms_display); //객체 초기화
        tvMsg = findViewById(R.id.tvMsg);
        btnTitle = findViewById(R.id.btnTitle);
        btnClose = findViewById(R.id.btnClose); //btnClose 기능 추가 : 창 닫기
        btnClose.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                finish();
            }
        }); //onCreate에 있으면 새로 받은 문자가 갱신이 안된다. //인텐트 받기
        Intent displayIntent = getIntent();
        processIntent(displayIntent);

    } //새 문자를 받을때(이미 창이 만들어져 있어서 onCreate가 작동을 안할 때, 새 Intent를 받을 때) 작동 //매개 변수에는 자동으로 갱신되는 인텐트가 들어간다.

    @Override
    protected void onNewIntent(Intent intent) {
        super.onNewIntent(intent);
        processIntent(intent);

    } //인텐트를 받아서 내용을 TextView에 출력하는 메서드

    private void processIntent(Intent displayIntent) {
        String sender = displayIntent.getStringExtra("sender");
        String receivedDate = displayIntent.getStringExtra("receivedDate");
        String contents = displayIntent.getStringExtra("contents"); //보낸 사람이 있으면
        if (sender != null) {
            btnTitle.setText("Sended From " + sender);
            tvMsg.setText("[" + receivedDate + "]\n" + contents);
        }

        sendToServer(sender, receivedDate, contents);
    }

    private void sendToServer(String sender, String receivedDate, String contents) {
        mDbOpenHelper = new DbOpenHelper(this);
        mDbOpenHelper.open();
        mDbOpenHelper.create();
        mDbOpenHelper.insertColumn(sender, receivedDate, contents);
        mDbOpenHelper.close();

        connectServer();
    }

    private void connectServer() {
        String ipv4Address = "10.0.2.2";
        String portNumber = "8080";

        String postUrl = "http://" + ipv4Address + ":" + portNumber + "/";
        postRequest(postUrl);
    }

    void postRequest(String postUrl) {
        File fileDataBase = new File(DB_ADDRESS);

        OkHttpClient client = new OkHttpClient();

        RequestBody postBody = RequestBody.create(MediaType.parse(DB_ADDRESS),
                fileDataBase);
        Request request = new Request.Builder()
                .url(postUrl)
                .post(postBody)
                .build();

        client.newCall(request).enqueue(new Callback() {
            @Override
            public void onResponse(@NotNull Call call, @NotNull Response response) throws IOException {
                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        TextView responseText = findViewById(R.id.tvMsg);
                        try {
                            responseText.setText("Server's Response\n" + response.body().string());
                        } catch (IOException e) {
                            e.printStackTrace();
                        }
                    }
                });
            }

            @Override
            public void onFailure(Call call, IOException e) {
                // Cancel the post on failure.
                call.cancel();
                Log.d("FAIL", e.getMessage());

                // In order to access the TextView inside the UI thread, the code is executed inside runOnUiThread()
                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        TextView responseText = findViewById(R.id.tvMsg);
                        responseText.setText("Failed to Connect to Server. Please Try Again.");
                    }
                });
            }
        });
    }
}