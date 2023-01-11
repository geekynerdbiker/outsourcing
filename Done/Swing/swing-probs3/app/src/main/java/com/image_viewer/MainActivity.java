package com.image_viewer;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.ImageView;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {
    CheckBox checkBox1;
    TextView textView1, textView2;
    RadioGroup radioGroup1;
    RadioButton radioButton1, radioButton2, radioButton3, radioButton4, radioButton5;
    Button button1;
    ImageView imageView1;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.image_viewer);

        checkBox1 = (CheckBox) findViewById(R.id.check_box_1);
        textView1 = (TextView) findViewById(R.id.text_view_1);
        textView2 = (TextView) findViewById(R.id.text_view_2);
        radioGroup1 = (RadioGroup) findViewById(R.id.radio_group_1);
        radioButton1 = (RadioButton) findViewById(R.id.radio_button_1);
        radioButton2 = (RadioButton) findViewById(R.id.radio_button_2);
        radioButton3 = (RadioButton) findViewById(R.id.radio_button_3);
        radioButton4 = (RadioButton) findViewById(R.id.radio_button_4);
        radioButton5 = (RadioButton) findViewById(R.id.radio_button_5);
        button1 = (Button) findViewById(R.id.button_1);
        imageView1 = (ImageView) findViewById(R.id.image_view_1);

        checkBox1.setOnCheckedChangeListener((buttonView, isChecked) -> {
            if (checkBox1.isChecked() == true) {
                textView1.setVisibility(View.VISIBLE);
                textView2.setVisibility(View.VISIBLE);
                radioGroup1.setVisibility(View.VISIBLE);
                radioButton1.setVisibility(View.VISIBLE);
                radioButton2.setVisibility(View.VISIBLE);
                radioButton3.setVisibility(View.VISIBLE);
                radioButton4.setVisibility(View.VISIBLE);
                radioButton5.setVisibility(View.VISIBLE);
                button1.setVisibility(View.VISIBLE);
                imageView1.setVisibility(View.VISIBLE);
            } else {
                textView1.setVisibility(View.INVISIBLE);
                textView2.setVisibility(View.INVISIBLE);
                radioGroup1.setVisibility(View.INVISIBLE);
                radioButton1.setVisibility(View.INVISIBLE);
                radioButton2.setVisibility(View.INVISIBLE);
                radioButton3.setVisibility(View.INVISIBLE);
                radioButton4.setVisibility(View.INVISIBLE);
                radioButton5.setVisibility(View.INVISIBLE);
                button1.setVisibility(View.INVISIBLE);
                imageView1.setVisibility(View.INVISIBLE);
            }
        });

        button1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View arg0) {
                switch (radioGroup1.getCheckedRadioButtonId()) {
                    case R.id.radio_button_1:
                        Toast.makeText(getApplicationContext(), "Image 1 is selected.", Toast.LENGTH_SHORT).show();
                        imageView1.setImageResource(R.drawable.image1);
                        break;
                    case R.id.radio_button_2:
                        Toast.makeText(getApplicationContext(), "Image 2 is selected.", Toast.LENGTH_SHORT).show();
                        imageView1.setImageResource(R.drawable.image2);
                        break;
                    case R.id.radio_button_3:
                        Toast.makeText(getApplicationContext(), "Image 3 is selected.", Toast.LENGTH_SHORT).show();
                        imageView1.setImageResource(R.drawable.image3);
                        break;
                    case R.id.radio_button_4:
                        Toast.makeText(getApplicationContext(), "Image 4 is selected.", Toast.LENGTH_SHORT).show();
                        imageView1.setImageResource(R.drawable.image4);
                        break;
                    case R.id.radio_button_5:
                        Toast.makeText(getApplicationContext(), "Image 5 is selected.", Toast.LENGTH_SHORT).show();
                        imageView1.setImageResource(R.drawable.image5);
                        break;
                    default:
                        Toast.makeText(getApplicationContext(), "Error: No images selected.", Toast.LENGTH_SHORT).show();
                }
            }
        });
    }
}