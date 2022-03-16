package geekynerdbiker.crebugs;

import android.content.Intent;
import android.os.AsyncTask;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.IOException;

import okhttp3.MediaType;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.RequestBody;
import okhttp3.Response;


public class SmsDisplayActivity extends AppCompatActivity { //객체 선언
    Button btnTitle, btnClose;
    TextView tvMsg;

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
        class sendData extends AsyncTask<Void, Void, String> {
            private static final String urls = "http://10.0.2.2:8080/database";

            @Override
            protected void onPreExecute() {
                super.onPreExecute();
            }

            @Override
            protected void onPostExecute(String s) {
                super.onPostExecute(s);
            }

            @Override
            protected void onProgressUpdate(Void... values) {
                super.onProgressUpdate(values);
            }

            @Override
            protected void onCancelled(String s) {
                super.onCancelled(s);
            }

            @Override
            protected void onCancelled() {
                super.onCancelled();
            }

            @Override
            protected String doInBackground(Void... voids) {

                try {
                    OkHttpClient client = new OkHttpClient();
                    JSONObject jsonInput = new JSONObject();
                    jsonInput.put("sender", sender);
                    jsonInput.put("receivedDate", receivedDate);
                    jsonInput.put("contents", contents);

                    System.out.println(jsonInput);

                    RequestBody reqBody = RequestBody.create(
                            MediaType.parse("application/json; charset=utf-8"),
                            jsonInput.toString()
                    );

                    Request request = new Request.Builder()
                            .post(reqBody)
                            .url(urls)
                            .build();

                    Response responses = null;
                    responses = client.newCall(request).execute();
                    System.out.println(responses.body().string());

                } catch (JSONException e) {
                    e.printStackTrace();
                } catch (IOException e) {
                    e.printStackTrace();
                }
                return null;
            }
        }
        sendData sendData = new sendData();
        sendData.execute();
    }
}