package com.example.photoedit;

import androidx.annotation.NonNull;
import androidx.annotation.RequiresApi;
import androidx.appcompat.app.AppCompatActivity;

import android.annotation.SuppressLint;
import android.content.Context;
import android.content.Intent;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.ColorMatrix;
import android.graphics.ColorMatrixColorFilter;
import android.graphics.Paint;
import android.graphics.drawable.BitmapDrawable;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.os.Environment;
import android.provider.MediaStore;
import android.util.Log;
import android.view.View;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.SeekBar;
import android.widget.TextView;
import android.widget.Toast;

import com.example.photoedit.util.FaceGlow;
import com.example.photoedit.util.ImageProcess;
import com.example.photoedit.util.LipsDraw;
import com.example.photoedit.util.MediaScanning;
import com.google.android.gms.tasks.OnFailureListener;
import com.google.android.gms.tasks.OnSuccessListener;
import com.google.android.gms.tasks.Task;
import com.google.mlkit.vision.common.InputImage;
import com.google.mlkit.vision.face.Face;
import com.google.mlkit.vision.face.FaceDetection;
import com.google.mlkit.vision.face.FaceDetector;
import com.google.mlkit.vision.face.FaceDetectorOptions;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.text.SimpleDateFormat;
import java.util.List;
import java.util.Locale;

public class ImageEditActivity extends AppCompatActivity implements View.OnClickListener {

    Uri fileURi;
    String type;
    ImageView imageView, colorImageView;
    ImageButton cancelButton;
    LinearLayout sliderLayout, brightness, contrast, saturation, faceColor, lips, colorPicker;
    TextView label, colorCode, finishButton;
    SeekBar seekBar, redSeekBar, greenSeekBar, blueSeekBar, alphaSeekBar;
    int mode = 0, editmode = 0;

    int brightValue = 0, contrastValue = 1, saturationValue = 100;
    Bitmap originImage;

    FaceDetectorOptions realTimeOpts;
    InputImage inputImage;

    FaceDetector detector;
    Task<List<Face>> faceDetectionResult;
    List<Face> facesData;

    //Google ML Kit을 이용하여 얼굴을 인식하는 메소드
    void faceDetection(){
        //얼굴인식을 담당하는 FaceDetector라는 클래스를 realTimeOpts 옵션과 함께 초기화
        detector = FaceDetection.getClient(realTimeOpts);
        //얼굴인식을 진행하고 그 결과를 faceDetectionResult라는 변수에 담음
        faceDetectionResult =
                //FaceDetector를 실행하는 부분
                detector.process(inputImage)
                        .addOnSuccessListener(
                                new OnSuccessListener<List<Face>>() {
                                    @Override
                                    public void onSuccess(List<Face> faces) {
                                        // Task completed successfully
                                        // ...
                                        facesData = faces;
                                        if(faces.size() > 0){
                                            Log.d("I", faces.get(0).getAllLandmarks().toString());
                                        }
                                    }
                                })
                        .addOnFailureListener(
                                new OnFailureListener() {
                                    @Override
                                    public void onFailure(@NonNull Exception e) {
                                        // Task failed with an exception
                                        // ...
                                        e.printStackTrace();
                                    }
                                });
    }


    @RequiresApi(api = Build.VERSION_CODES.O)
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_image_edit);

        //Google ML - Face Detection AI를 사용하기 위한 초기 설정
        realTimeOpts =new FaceDetectorOptions.Builder()
                .setClassificationMode(FaceDetectorOptions.PERFORMANCE_MODE_ACCURATE)
                .setLandmarkMode(FaceDetectorOptions.LANDMARK_MODE_ALL)
                .setContourMode(FaceDetectorOptions.CONTOUR_MODE_ALL)
                .setClassificationMode(FaceDetectorOptions.CLASSIFICATION_MODE_ALL)
                .setMinFaceSize(0.15f)
                .enableTracking()
                .build();



        //사진 찍은 파일 또는 갤러리에서 불러온 파일의 경로를 불러온다
        Intent intent = getIntent();
        fileURi = intent.getParcelableExtra("IMG_PATH");
        type = intent.getStringExtra("TYPE");

        //편집창(이미지)를 초기화 하는 부분
        imageView = findViewById(R.id.image);
        imageView.setImageURI(fileURi);
        BitmapDrawable drawable = (BitmapDrawable) imageView.getDrawable();
        originImage = drawable.getBitmap();

        //사진에 얼굴을 인식하기 위해 inputImage를 설정하고 faceDetection 메소드를 호출하여 얼굴 인식 진행
        inputImage = InputImage.fromBitmap(originImage, 0);
        faceDetection();

        //밝기, 대비, 색조 수정을 위한 Component 설정
        label = findViewById(R.id.label);
        sliderLayout = findViewById(R.id.sliderLayout);
        seekBar = findViewById(R.id.seekBar2);

        seekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int i, boolean b) {



            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            //Seekbar 움직임이 멈췄을 때
            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                switch(mode){
                    case 1:
                        brightValue = seekBar.getProgress();
                        break;
                    case 2:
                        contrastValue = seekBar.getProgress();
                        break;
                    case 3 :
                        saturationValue = seekBar.getProgress();
                        break;
                }

                Bitmap bitmap = ImageProcess.changeBitmapContrastBrightness(originImage, contrastValue, brightValue);
                bitmap = ImageProcess.saturation(bitmap, saturationValue);
                imageView.setImageBitmap(bitmap);

            }
        });
        colorPicker = findViewById(R.id.colorPicker);
        colorImageView = findViewById(R.id.colorImage);
        colorCode = findViewById(R.id.colorCode);

        redSeekBar = findViewById(R.id.redSeekBar);
        redSeekBar.setMin(0);
        redSeekBar.setMax(255);
        greenSeekBar = findViewById(R.id.greenSeekBar);
        greenSeekBar.setMin(0);
        greenSeekBar.setMax(255);
        blueSeekBar = findViewById(R.id.blueSeekBar);
        blueSeekBar.setMin(0);
        blueSeekBar.setMax(255);
        alphaSeekBar = findViewById(R.id.alphaSeekBar);
        alphaSeekBar.setMax(100);
        alphaSeekBar.setMin(0);


        redSeekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int i, boolean b) {

            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                //입술색, 얼굴색 보정을 위한 색깔을 선택하는 코드
                Bitmap colorImage = Bitmap.createBitmap(100, 100, Bitmap.Config.ARGB_8888);
                //현재 Seekbar에 설정되어 있는 RGB 값들을 조합하여 색상을 colorImageView에 표현한다
                colorImage.eraseColor(android.graphics.Color.rgb(redSeekBar.getProgress(), greenSeekBar.getProgress(), blueSeekBar.getProgress()));
                colorImageView.setImageBitmap(colorImage);
                //현재 Seekbar에 설정되어 있는 RGB 값들을 조합하여 색상을 hex 코드로 표현한다
                String hex = String.format("#%02x%02x%02x", redSeekBar.getProgress(), greenSeekBar.getProgress(), blueSeekBar.getProgress());
                colorCode.setText(hex);

                if(editmode == 1) {
                    //입술색을 변환한 비트맵 데이터
                    Bitmap editBitmap = new LipsDraw().drawFace(originImage, facesData.get(0), Color.parseColor(hex), alphaSeekBar.getProgress());
                    //원본 이미지를 변형된 이미지로 바꾼다
                    originImage = editBitmap;
                    //변형된 이미지에 밝기, 대비를 반영한다
                    imageView.setImageBitmap(ImageProcess.changeBitmapContrastBrightness(originImage, contrastValue, brightValue));
                }else if(editmode == 2) {
                    //입술색을 변환한 비트맵 데이터
                    Bitmap editBitmap = new FaceGlow().drawFace(originImage, facesData.get(0), Color.parseColor(hex), alphaSeekBar.getProgress());
//원본 이미지를 변형된 이미지로 바꾼다
                    originImage = editBitmap;
                    //변형된 이미지에 밝기, 대비를 반영한다
                    imageView.setImageBitmap(ImageProcess.changeBitmapContrastBrightness(originImage, contrastValue, brightValue));
                }
            }
        });

        greenSeekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int i, boolean b) {

            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                Bitmap colorImage = Bitmap.createBitmap(100, 100, Bitmap.Config.ARGB_8888);
                colorImage.eraseColor(android.graphics.Color.rgb(redSeekBar.getProgress(), greenSeekBar.getProgress(), blueSeekBar.getProgress()));
                colorImageView.setImageBitmap(colorImage);
                String hex = String.format("#%02x%02x%02x", redSeekBar.getProgress(), greenSeekBar.getProgress(), blueSeekBar.getProgress());
                colorCode.setText(hex);
                if(editmode == 1) {
                    Bitmap editBitmap = new LipsDraw().drawFace(originImage, facesData.get(0), Color.parseColor(hex), alphaSeekBar.getProgress());

                    originImage = editBitmap;
                    imageView.setImageBitmap(ImageProcess.changeBitmapContrastBrightness(originImage, contrastValue, brightValue));
                }else if(editmode == 2) {
                    Bitmap editBitmap = new FaceGlow().drawFace(originImage, facesData.get(0), Color.parseColor(hex), alphaSeekBar.getProgress());
                    originImage = editBitmap;
                    imageView.setImageBitmap(ImageProcess.changeBitmapContrastBrightness(originImage, contrastValue, brightValue));
                }
            }
        });

        blueSeekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int i, boolean b) {

            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                Bitmap colorImage = Bitmap.createBitmap(100, 100, Bitmap.Config.ARGB_8888);
                colorImage.eraseColor(android.graphics.Color.rgb(redSeekBar.getProgress(), greenSeekBar.getProgress(), blueSeekBar.getProgress()));
                colorImageView.setImageBitmap(colorImage);
                String hex = String.format("#%02x%02x%02x", redSeekBar.getProgress(), greenSeekBar.getProgress(), blueSeekBar.getProgress());
                colorCode.setText(hex);

                if(editmode == 1) {
                    Bitmap editBitmap = new LipsDraw().drawFace(originImage, facesData.get(0), Color.parseColor(hex), alphaSeekBar.getProgress());

                    originImage = editBitmap;
                    imageView.setImageBitmap(ImageProcess.changeBitmapContrastBrightness(originImage, contrastValue, brightValue));
                }else if(editmode == 2) {
                    Bitmap editBitmap = new FaceGlow().drawFace(originImage, facesData.get(0), Color.parseColor(hex), alphaSeekBar.getProgress());

                    originImage = editBitmap;
                    imageView.setImageBitmap(ImageProcess.changeBitmapContrastBrightness(originImage, contrastValue, brightValue));
                }

            }
        });

        alphaSeekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int i, boolean b) {

            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                Bitmap colorImage = Bitmap.createBitmap(100, 100, Bitmap.Config.ARGB_8888);
                colorImage.eraseColor(android.graphics.Color.rgb(redSeekBar.getProgress(), greenSeekBar.getProgress(), blueSeekBar.getProgress()));
                colorImageView.setImageBitmap(colorImage);
                String hex = String.format("#%02x%02x%02x", redSeekBar.getProgress(), greenSeekBar.getProgress(), blueSeekBar.getProgress());
                colorCode.setText(hex);

                if(editmode == 1) {
                    Bitmap editBitmap = new LipsDraw().drawFace(originImage, facesData.get(0), Color.parseColor(hex), alphaSeekBar.getProgress());

                    originImage = editBitmap;
                    imageView.setImageBitmap(ImageProcess.changeBitmapContrastBrightness(originImage, contrastValue, brightValue));
                }else if(editmode == 2) {
                    Bitmap editBitmap = new FaceGlow().drawFace(originImage, facesData.get(0), Color.parseColor(hex), alphaSeekBar.getProgress());

                    originImage = editBitmap;
                    imageView.setImageBitmap(ImageProcess.changeBitmapContrastBrightness(originImage, contrastValue, brightValue));
                }

            }
        });

        brightness = findViewById(R.id.brightnessButton);
        brightness.setOnClickListener(this);
        contrast = findViewById(R.id.beforeAfterButton);
        contrast.setOnClickListener(this);
        saturation = findViewById(R.id.saturationButton);
        saturation.setOnClickListener(this);
        faceColor = findViewById(R.id.faceColorButton);
        faceColor.setOnClickListener(this);
        lips = findViewById(R.id.lipsButton);
        lips.setOnClickListener(this);

        //입술색, 얼굴색 조절 하는 Dialog 없앨때
        cancelButton = findViewById(R.id.cancelImageButton);
        cancelButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                colorPicker.setVisibility(View.GONE);
                redSeekBar.setProgress(0);
                greenSeekBar.setProgress(0);
                blueSeekBar.setProgress(0);
            }
        });

        //이미지 보정을 모두 마치고 저장할 때
        // TODO :
        finishButton = findViewById(R.id.finishButton);
        finishButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
//                String[] proj = { MediaStore.Images.Media.DATA };
//                Toast.makeText(ImageEditActivity.this,"test",Toast.LENGTH_SHORT).show();
//                //기존 파일에다가 덮어쓰기를 진행함
//                Cursor cursor = getContentResolver().query(fileURi, proj, null, null, null);
//                cursor.moveToNext();
//                @SuppressLint("Range") String path = cursor.getString(cursor.getColumnIndex(MediaStore.MediaColumns.DATA));

//                String newFileName = new SimpleDateFormat("yyyyMMddHHmmss", Locale.US
//                ).format(System.currentTimeMillis()) + ".jpg";

                //File temp = new File(path);

//                try {
//                    //파일 저장을 위한 Stream
//                    //FileOutputStream out = new FileOutputStream(temp);

                   //이미지 뷰에 있는 이미지를 불러와서 저장함
                    Bitmap tempBitmap = originImage;
                    tempBitmap = ImageProcess.changeBitmapContrastBrightness(originImage, contrastValue, brightValue);
                    tempBitmap = ImageProcess.saturation(tempBitmap, saturationValue);

                    //tempBitmap.compress(Bitmap.CompressFormat.JPEG, 100, out);
                    saveBitmap(tempBitmap,ImageEditActivity.this);
                    Toast.makeText(ImageEditActivity.this, "사진이 저장되었습니다", Toast.LENGTH_SHORT).show();

                    //out.close();
//                } catch (FileNotFoundException e) {
//                    e.printStackTrace();
//                    Log.e("HAN","exception: "+e);
//                } catch (IOException e) {
//                    e.printStackTrace();
//                    Log.e("HAN","exception: "+e);
//                }

            }
        });
    }

    public static void saveBitmap(Bitmap b, Context context) {
        String newFileName = new SimpleDateFormat("yyyyMMddHHmmss", Locale.US
        ).format(System.currentTimeMillis()) + ".jpg";
        String path = createPictureFilePath(newFileName);
        saveBitmapAsFile(b,path);
        scanMediaFile(new File(path),context);
    }
    private static  void scanMediaFile(final File file,Context context) {
        new MediaScanning(context,file);
    }

    public static final String SAVE_MEDIA_PATH = Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_PICTURES).getAbsolutePath() + "/";
    public static String createPictureFilePath(String fileName) {
        createMediaFileDirectory();
        //String fileName = "img1"+ ".jpg";
        String fullPath = SAVE_MEDIA_PATH + fileName;
        return fullPath;
    }

    private static void createMediaFileDirectory() {
        File downloadDir = Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_PICTURES);
        if (!downloadDir.exists()) {
            downloadDir.mkdir();
        }

        File cameraDir = new File(SAVE_MEDIA_PATH);
        if (!cameraDir.exists()) {
            cameraDir.mkdir();
        }
    }


    private static void saveBitmapAsFile(Bitmap bitmap, String filepath) {
        File file = new File(filepath);
        OutputStream os = null;

        try {
            file.createNewFile();
            os = new FileOutputStream(file);

            bitmap.compress(Bitmap.CompressFormat.PNG, 100, os);
            os.close();
            //Toast.makeText(mContext,"사진 저장",Toast.LENGTH_SHORT).show();
        } catch (Exception e) {
            Log.e("HAN","Exception: "+e);
            e.printStackTrace();
        }
    }


    void openSlider(){
        sliderLayout.setVisibility(View.VISIBLE);
    }

    @RequiresApi(api = Build.VERSION_CODES.O)
    @Override
    public void onClick(View view) {
        switch(view.getId()){
            case R.id.brightnessButton:
                label.setText("밝기");
                seekBar.setProgress(brightValue);
                seekBar.setMin(-150);
                seekBar.setMax(150);
                mode = 1;
                colorPicker.setVisibility(View.GONE);
                openSlider();
                break;
            case R.id.beforeAfterButton:
                label.setText("대비");
                seekBar.setProgress(contrastValue);
                seekBar.setMin(0);
                seekBar.setMax(10);
                mode = 2;
                colorPicker.setVisibility(View.GONE);
                openSlider();
                break;
            case R.id.saturationButton:
                label.setText("색조");
                seekBar.setProgress(saturationValue);
                seekBar.setMin(0);
                seekBar.setMax(200);
                mode = 3;
                colorPicker.setVisibility(View.GONE);
                openSlider();
                break;
            case R.id.lipsButton:
                if(facesData.size() == 0){
                    Toast.makeText(this, "해당 기능은 얼굴이 감지된 경우에만 사용하실 수 있습니다.", Toast.LENGTH_SHORT).show();
                }else {
                    sliderLayout.setVisibility(View.GONE);
                    colorPicker.setVisibility(View.VISIBLE);
                    Bitmap colorImage = Bitmap.createBitmap(100, 100, Bitmap.Config.ARGB_8888);
                    colorImage.eraseColor(android.graphics.Color.rgb(redSeekBar.getProgress(), greenSeekBar.getProgress(), blueSeekBar.getProgress()));
                    colorImageView.setImageBitmap(colorImage);
                    String hex = String.format("#%02x%02x%02x", redSeekBar.getProgress(), greenSeekBar.getProgress(), blueSeekBar.getProgress());
                    colorCode.setText(hex);
                    alphaSeekBar.setProgress(1);
                    editmode = 1;
                }

                break;

            case R.id.faceColorButton:
                if(facesData.size() == 0){
                    Toast.makeText(this, "해당 기능은 얼굴이 감지된 경우에만 사용하실 수 있습니다.", Toast.LENGTH_SHORT).show();
                }else {
                    sliderLayout.setVisibility(View.GONE);
                    colorPicker.setVisibility(View.VISIBLE);
                    Bitmap colorImage = Bitmap.createBitmap(100, 100, Bitmap.Config.ARGB_8888);
                    colorImage.eraseColor(android.graphics.Color.rgb(redSeekBar.getProgress(), greenSeekBar.getProgress(), blueSeekBar.getProgress()));
                    colorImageView.setImageBitmap(colorImage);
                    String hex = String.format("#%02x%02x%02x", redSeekBar.getProgress(), greenSeekBar.getProgress(), blueSeekBar.getProgress());
                    colorCode.setText(hex);
                    alphaSeekBar.setProgress(1);
                    editmode = 2;
                }

                break;

        }
    }
}