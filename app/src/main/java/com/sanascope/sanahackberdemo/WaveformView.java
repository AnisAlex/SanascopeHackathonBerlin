package com.sanascope.sanahackberdemo;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.util.AttributeSet;
import android.view.View;

import androidx.annotation.Nullable;
import androidx.core.content.ContextCompat;

public class WaveformView extends View {

    Paint paint = new Paint();
    int horizon;
    float[] percentages;

    private void init() {
        int color = ContextCompat.getColor(getContext(), R.color.colorPrimaryDark);
        paint.setColor(color);
        horizon = getHeight() / 2;
        percentages = new float[getWidth()];
    }

    public WaveformView(Context context) {
        super(context);
        init();
    }

    public WaveformView(Context context, @Nullable AttributeSet attrs) {
        super(context, attrs);
        init();
    }

    @Override
    protected void onDraw(Canvas canvas) {
        super.onDraw(canvas);
        for (int i = 0; i < percentages.length; i++) {
            canvas.drawLine(i, Math.max(0, horizon - getHeight() * percentages[i]/2),
                    i, Math.min(getHeight(), horizon + getHeight() * percentages[i]/2),
                    paint);
        }
    }

    public void addColumn(float percentage) {
        if (getWidth() == 0 || getHeight() == 0) {
            return;
        }
        if (percentages.length != getWidth()) {
            init();
        }
        for (int i = 0; i < getWidth()-1; i++) {
            percentages[i] = percentages[i+1];
        }
        percentages[getWidth()-1] = percentage;
        invalidate();
    }
}
