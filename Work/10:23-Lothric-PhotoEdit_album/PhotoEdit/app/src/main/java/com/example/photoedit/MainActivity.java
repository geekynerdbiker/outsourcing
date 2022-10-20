package com.example.photoedit;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.camera.core.AspectRatio;
import androidx.camera.core.CameraFilter;
import androidx.camera.core.CameraSelector;
import androidx.camera.core.ImageAnalysis;
import androidx.camera.core.ImageCapture;
import androidx.camera.core.ImageCaptureException;
import androidx.camera.core.ImageProxy;
import androidx.camera.core.Preview;
import androidx.camera.core.impl.ImageCaptureConfig;
import androidx.camera.core.internal.utils.ImageUtil;
import androidx.camera.lifecycle.ProcessCameraProvider;
import androidx.camera.view.CameraController;
import androidx.camera.view.PreviewView;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;

import android.Manifest;
import android.annotation.SuppressLint;
import android.content.ContentValues;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.graphics.Bitmap;
import android.hardware.camera2.CameraCharacteristics;
import android.hardware.camera2.CameraManager;
import android.media.Image;
import android.net.Uri;
import android.os.Bundle;
import android.os.Environment;
import android.provider.MediaStore;
import android.util.Log;
import android.util.Range;
import android.view.Surface;
import android.view.View;
import android.widget.ImageButton;
import android.widget.Toast;

import java.io.File;
import java.text.SimpleDateFormat;
import java.util.Locale;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Executors;

public class MainActivity extends AppCompatActivity{

    PreviewView previewView;
    ImageButton takePicture, loadImage;
    ProcessCameraProvider processCameraProvider;
    int lensFacing = CameraSelector.LENS_FACING_FRONT;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        /*
            Component를 코드에서 사용하기 위해 초기화 하는 부분
         */
        previewView = findViewById(R.id.previewView);
/*
            카메라 사용 및 파일 읽기/쓰기를 위해 권한을 요청하는 부분
         */
        ActivityCompat.requestPermissions(this, new String[]{android.Manifest.permission.CAMERA, Manifest.permission.WRITE_EXTERNAL_STORAGE, Manifest.permission.READ_EXTERNAL_STORAGE}, 1);

        /*
        Component를 코드에서 사용하기 위해 초기화 하는 부분
         */
        takePicture = findViewById(R.id.takePictureButton);

        try {
            /*
            카메라를 PreviewView에서 사용하기 위해 카메라 제공자를 불러와서 초기화 하는 부분
         */
            processCameraProvider = ProcessCameraProvider.getInstance(this).get();

        }
        catch (ExecutionException e) {
            e.printStackTrace();
        }
        catch (InterruptedException e) {
            e.printStackTrace();
        }

        if (ActivityCompat.checkSelfPermission(MainActivity.this, android.Manifest.permission.CAMERA) == PackageManager.PERMISSION_GRANTED &&
                ActivityCompat.checkSelfPermission(MainActivity.this, Manifest.permission.WRITE_EXTERNAL_STORAGE) == PackageManager.PERMISSION_GRANTED &&
                ActivityCompat.checkSelfPermission(MainActivity.this, Manifest.permission.READ_EXTERNAL_STORAGE) == PackageManager.PERMISSION_GRANTED) {
            //PreviewView에다가 카메라에 보이는 화면을 표시하도록 하는 부분
            bindPreview();

            //갤러리에서 사진을 불러오는 버튼을 초기화 하는 부분
            loadImage = findViewById(R.id.imageButton2);

            loadImage.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {

                    //intent를 이용하여 갤러리 앱을 호출함
                    Intent intent = new Intent(Intent.ACTION_PICK);
                    intent. setDataAndType(android.provider.MediaStore.Images.Media.EXTERNAL_CONTENT_URI, "image/*");
                    startActivityForResult(intent, 1);
                }
            });
        }




    }

    //갤러리에서 이미지를 불러왔을 때 아래 이벤트 실행
    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {

        super.onActivityResult(requestCode, resultCode, data);
        //갤러리에서 사진을 불러오는 이벤트를 정상적으로 수행했을 때
        if (requestCode == 1 && resultCode == RESULT_OK && data != null && data.getData() != null) {
            //파일의 경로를 불러옴
            Uri selectedImageUri = data.getData();
            //이미지를 수정하는 ImageEditActivity로 이동하는 코드
            Intent intent = new Intent(MainActivity.this, ImageEditActivity.class);
            intent.putExtra("IMG_PATH", selectedImageUri);
            intent.putExtra("TYPE", "LOAD_GALLERY");
            startActivity(intent);

        }

    }

    void bindPreview() {
        //기존에 남아있던 자원을 할당 해제함
        processCameraProvider.unbindAll();
        //카메라 화면의 모습이 중앙점을 기준으로 표시되도록 함
        previewView.setScaleType(PreviewView.ScaleType.FIT_CENTER);
        //내가 쓰고자 하는 카메라를 선택함
        CameraSelector cameraSelector = new CameraSelector.Builder()
                .requireLensFacing(lensFacing)
                .build();

        //PreviewView의 초기 설정을 하는 부분
        Preview preview = new Preview.Builder()
                .setTargetAspectRatio(AspectRatio.RATIO_4_3) //디폴트 표준 비율
                .build();
        //preview에 어떤 걸 보여줄 지 설정하는 부분
        preview.setSurfaceProvider(previewView.getSurfaceProvider());

        //사진 찍기에 필요한 ImageCapture를 빌드하는 부분
        ImageCapture imageCapture =
                new ImageCapture.Builder().setTargetRotation(Surface.ROTATION_0)
                        .build();

        //카메라 제공자에 카메라 선택, PreviewView 연결, 사진찍기 기능을 연결함
        processCameraProvider.bindToLifecycle(this, cameraSelector, preview, imageCapture);

        //사진 찍기 버튼을 눌렀을 때
        takePicture.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                //파일 이름은 연월일시분초.jpg로 함
                String newFileName = new SimpleDateFormat("yyyyMMddHHmmss", Locale.US
                ).format(System.currentTimeMillis()) + ".jpg";
                //파일의 콘텐츠 값을 수정하는 부분
                ContentValues contentValues = new ContentValues();
                contentValues.put(MediaStore.MediaColumns.DISPLAY_NAME, newFileName);
                contentValues.put(MediaStore.MediaColumns.MIME_TYPE, "image/jpg"); //이미지라는 태그 해당 태그를 붙혀야 Gallery에서 감지됨

                //이미지 저장 할 때 필요한 옵션을 저장하는 부분
                ImageCapture.OutputFileOptions outputFileOptions =
                        new ImageCapture.OutputFileOptions.Builder(getContentResolver(), MediaStore.Images.Media.EXTERNAL_CONTENT_URI, contentValues).build(); //외부저장소에 저장하고, 위에 contentValue 속성에 맞춰서 저장


                //사진을 찍는 부분
                imageCapture.takePicture(outputFileOptions, ContextCompat.getMainExecutor(MainActivity.this),
                        new ImageCapture.OnImageSavedCallback() {
                            @Override
                            public void onImageSaved(ImageCapture.OutputFileResults outputFileResults) {
                                // insert your code here.
                                Toast.makeText(MainActivity.this, "사진이 저장되었습니다.", Toast.LENGTH_SHORT).show();

                                //이미지 파일 주소와 사진을 찍었는지, 불러오기 했는지를 구분한 정보를 담아서 ImageEditActivity로 이동
                                Intent intent = new Intent(MainActivity.this, ImageEditActivity.class);
                                intent.putExtra("IMG_PATH", outputFileResults.getSavedUri());
                                intent.putExtra("TYPE", "TAKE_PICTURE");
                                startActivity(intent);
                            }
                            @Override
                            public void onError(ImageCaptureException error) {
                                // insert your code here.
                                Log.e("Main",error.getMessage());
                            }
                        }
                );
            }
        });

    }



    @Override
    protected void onDestroy() {
        super.onDestroy();
        //이 앱이 종료되면 카메라 제공자에 할당된 자원을 모두 해제한다
        processCameraProvider.unbindAll();
    }

    //처음에 액티비티가 실행되고 나서 권한이 부여되지 않았을 때 권한을 요청하는 Dialog를 띄우고 사용자가 누른 값을 확인하는 Callback 함수
    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
        switch (requestCode){
            case 1:
                if(grantResults[0] != PackageManager.PERMISSION_GRANTED){

                }else{
                    //권한들이 허용되었을 때
                    bindPreview();
                }
        }
    }
}