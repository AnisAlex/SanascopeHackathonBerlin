package com.sanascope.sanahackberdemo;

import android.Manifest;
import android.app.Activity;
import android.content.Context;
import android.content.pm.PackageManager;
import android.os.Build;

import androidx.core.app.ActivityCompat;

public class PermissionHandler {

    private final int PERMISSION_REQUEST_CODE = 1;

    private final Context context;

    public PermissionHandler(Context context) {
        this.context = context;
    }

    // TODO Consider putting these in activity
    private boolean isPermissionGranted(String permission){
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            if (context.checkSelfPermission(permission)
                    == PackageManager.PERMISSION_GRANTED) {
                return true;
            } else {
                return false;
            }
        }
        else { //permission is automatically granted on sdk<23 upon installation
            return true;
        }
    }

    public boolean allPermissionsGranted(){
        return isPermissionGranted(Manifest.permission.WRITE_EXTERNAL_STORAGE)
                && isPermissionGranted(Manifest.permission.RECORD_AUDIO);
    }

    public void requestAllPermission(Activity activity) {
        if (allPermissionsGranted()) {
            return;
        }
        ActivityCompat.requestPermissions(activity,
                new String[]{ Manifest.permission.WRITE_EXTERNAL_STORAGE,
                        Manifest.permission.RECORD_AUDIO }, PERMISSION_REQUEST_CODE);
    }
}
