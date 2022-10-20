package com.example.photoedit.util;
import android.graphics.Bitmap;
import android.graphics.BitmapShader;
import android.graphics.BlurMaskFilter;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.ComposeShader;
import android.graphics.Paint;
import android.graphics.Path;
import android.graphics.Point;
import android.graphics.PointF;
import android.graphics.PorterDuff;
import android.graphics.PorterDuffXfermode;
import android.graphics.RadialGradient;
import android.graphics.Rect;
import android.graphics.RectF;
import android.graphics.Shader;

import androidx.annotation.Nullable;

import com.google.mlkit.vision.face.Face;
import com.google.mlkit.vision.face.FaceContour;

import java.util.List;
import java.util.Objects;

public class FaceGlow {
    public Bitmap drawFace(Bitmap bitmap, Face face, int color, int alpha) {
        Bitmap tempBitmap = null;
        try {
            tempBitmap = Bitmap.createBitmap(bitmap.getWidth(), bitmap.getHeight(), Bitmap.Config.RGB_565);
            Canvas canvas = new Canvas(tempBitmap);
            canvas.drawBitmap(bitmap, 0f, 0f, null);

            //앞으로 그릴 그림의 궤적 정보를 담는 역할
            Path mainPath = new android.graphics.Path();

            //얼굴에서 핵심이 되는 랜드마크들의 포인트를 List에 담는다.
            List<PointF> pointsUpperTop = Objects.requireNonNull(face.getContour(FaceContour.FACE)).getPoints();
            //0,0으로 궤적 위치를 옮긴다
            mainPath.moveTo(pointsUpperTop.get(0).x, pointsUpperTop.get(0).y);
            //얼굴의 랜드마크들 하나하나 탐색한다
            for (PointF pointF : pointsUpperTop) {
                float px = pointF.x;
                float py = pointF.y;
                //라인 궤적을 저장한다.
                mainPath.lineTo(px, py);
            }
            //얼굴에 보정된 색상을 그린다.
            draw(canvas, mainPath, color, alpha);

        } catch (Exception e) {
            e.printStackTrace();
        }
        return tempBitmap;
    }

    //    Point point = new Point();
//        point.set(50, 50);
    public static void draw(Canvas canvas, Path facePath, int color, int alpha) {
        final PointF position = new PointF();

        Bitmap mask = createMask(facePath, color, position, alpha, 8);

        if (mask != null && !mask.isRecycled()) {

            Bitmap gradientBitmapByXferomd = getGradientBitmapByXferomd(mask, Math.max(mask.getWidth(), mask.getHeight()));
            mask.recycle();
            Paint paint = new Paint(Paint.ANTI_ALIAS_FLAG);
            paint.setXfermode(new PorterDuffXfermode(PorterDuff.Mode.SRC_OVER));
            if (gradientBitmapByXferomd != null) {
                canvas.drawBitmap(gradientBitmapByXferomd, position.x, position.y, paint);
                gradientBitmapByXferomd.recycle();
            }
        }
    }

    private static Bitmap getGradientBitmapByXferomd(Bitmap originBitmap, float radius) {
        if (radius < 10) radius = 10;
        Bitmap canvasBitmap = Bitmap.createBitmap(originBitmap.getWidth(), originBitmap.getHeight(), Bitmap.Config.ARGB_8888);
        Canvas canvas = new Canvas(canvasBitmap);
        Paint paint = new Paint();

        BitmapShader bitmapShader = new BitmapShader(originBitmap, Shader.TileMode.CLAMP, Shader.TileMode.CLAMP);
        RadialGradient radialGradient = new RadialGradient(originBitmap.getWidth() / 2, originBitmap.getHeight() / 2,
                radius, Color.BLACK, Color.TRANSPARENT, Shader.TileMode.CLAMP);
        paint.setShader(new ComposeShader(bitmapShader, radialGradient, new PorterDuffXfermode(PorterDuff.Mode.DST_IN)));
        canvas.drawRect(new Rect(0, 0, canvasBitmap.getWidth(), canvasBitmap.getHeight()), paint);
        return canvasBitmap;
    }

    private static Bitmap createMask(final Path path, int color, @Nullable PointF position, int alpha, int blur_radius) {
        if (path == null || path.isEmpty())
            return null;

        RectF bounds = new RectF();
        path.computeBounds(bounds, true);

        int width = (int) bounds.width();
        int height = (int) bounds.height();
        Bitmap bitmap = Bitmap.createBitmap(width, height, Bitmap.Config.ARGB_8888);  // mutable
        Canvas canvas = new Canvas(bitmap);
        Paint paint = new Paint(Paint.ANTI_ALIAS_FLAG);
        paint.setMaskFilter(new BlurMaskFilter(blur_radius, BlurMaskFilter.Blur.NORMAL));
        paint.setColor(color);
        paint.setAlpha(alpha);
        paint.setStyle(Paint.Style.FILL);
        path.offset(-bounds.left, -bounds.top);
        canvas.drawPath(path, paint);
        if (position != null) {
            position.x = bounds.left;
            position.y = bounds.top;
        }
        return bitmap;
    }


}