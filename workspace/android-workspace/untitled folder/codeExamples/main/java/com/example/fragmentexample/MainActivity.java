package com.example.fragmentexample;

import androidx.appcompat.app.AppCompatActivity;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentTransaction;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

/**
 * This class demos how Fragment works.
 * The layout file associated with the MainActivity has a FrameLayout where different fragments
 * can be displayed.
 */
public class MainActivity extends AppCompatActivity {
    private Button bt1, bt2;
    private String i = "10";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        bt1 = findViewById(R.id.btn_fg1);
        bt2 = findViewById(R.id.btn_fg2);
        ///when button 1 is clicked, FragmentOne will be displayed
        bt1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                showFragment(new FragmentOne());
            }
        });
        //when button 2 is clicked, FragmentTwo will be displayed
        bt2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                showFragment(new FragmentTwo());
            }
        });
    }

    //A helper method to display the fragment in the FrameLayout.
    private void showFragment(Fragment fragment) {
        FragmentManager fm = getSupportFragmentManager();
        FragmentTransaction ftran = fm.beginTransaction();
        ftran.replace(R.id.frameLayout, fragment);
        ftran.commit();
    }
}