package com.myapplication;

import androidx.appcompat.app.AppCompatActivity;

import android.media.MediaPlayer;
import android.os.Bundle;
import android.os.SystemClock;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ListView;
import android.widget.SeekBar;
import android.widget.TextView;

import java.util.List;

public class MainActivity extends AppCompatActivity {
    MediaPlayer mediaPlayer;
    ListView listView;
    ArrayAdapter<String> adapter;
    String[] array = {"media1", "media2", "media3", "media4", "media5"};

    int selectedRawId;
    String selectedMedia;
    Button buttonPlay, buttonStop;
    TextView textView;
    SeekBar seekBar;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.media_player);

        listView = (ListView) findViewById(R.id.listView);
        buttonPlay = (Button) findViewById(R.id.buttonPlay);
        buttonStop = (Button) findViewById(R.id.buttonStop);
        textView = (TextView) findViewById(R.id.textView);
        seekBar = (SeekBar) findViewById(R.id.seekBar);

        adapter = new ArrayAdapter<String>(this, android.R.layout.simple_list_item_single_choice, array);
        listView.setChoiceMode(ListView.CHOICE_MODE_SINGLE);
        listView.setAdapter(adapter);

        listView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                selectedMedia = array[position];
            }
        });

        buttonPlay.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                selectedRawId = getResources().getIdentifier(selectedMedia, "raw", getPackageName());
                if (mediaPlayer != null && mediaPlayer.isPlaying())
                    mediaPlayer.stop();

                mediaPlayer = MediaPlayer.create(getApplicationContext(), selectedRawId);
                mediaPlayer.start();

                new Thread() {
                    @Override
                    public void run() {
                        if (mediaPlayer == null) return;
                        seekBar.setMax(mediaPlayer.getDuration());

                        while (mediaPlayer != null && mediaPlayer.isPlaying()) {
                            runOnUiThread(new Runnable() {
                                @Override
                                public void run() {
                                    seekBar.setProgress(mediaPlayer.getCurrentPosition());
                                }
                            });
                            SystemClock.sleep(100);
                        }
                    }
                }.start();

                textView.setText("Now Playing: " + selectedMedia);
            }
        });

        buttonStop.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                mediaPlayer.stop();
                mediaPlayer = null;
                textView.setText("Now Playing: ");
            }
        });


    }
}