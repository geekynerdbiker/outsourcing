package com.example.app;

import android.app.Activity;
import android.os.Bundle;
import android.widget.GridView;



public class ImageGridActivity extends Activity {
    private int[] imageIDs = new int[] {
            R.drawable.image_01,
            R.drawable.image_01,
            R.drawable.image_01,
            R.drawable.image_01,
            R.drawable.image_01,
            R.drawable.image_01,
            R.drawable.image_01,
            R.drawable.image_01,
            R.drawable.image_01,
            R.drawable.image_01,
    };

    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        GridView gridViewImages = (GridView)findViewById(R.id.gridViewImages);
        ImageGridAdapter imageGridAdapter = new ImageGridAdapter(this, imageIDs);
        gridViewImages.setAdapter(imageGridAdapter);
    }
}