package com.sanascope.sanahackberdemo;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;
import androidx.databinding.DataBindingUtil;

import android.Manifest;
import android.app.Activity;
import android.content.Context;
import android.content.pm.PackageManager;
import android.media.AudioDeviceInfo;
import android.media.AudioManager;
import android.os.Build;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

import com.sanascope.sanahackberdemo.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }


    private ActivityMainBinding binding;
    private PermissionHandler permissionHandler;
    private boolean isRecording = false;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        binding = DataBindingUtil.setContentView(this, R.layout.activity_main);

        // Example of a call to a native method
        binding.setClickListener(this);
        permissionHandler = new PermissionHandler(this);
        permissionHandler.requestAllPermission(this);


    }

    private int getHeadsetInputDeviceID() throws IllegalStateException {
        AudioManager myAudioManager = (AudioManager) getSystemService(Context.AUDIO_SERVICE);
        if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.M) {
            AudioDeviceInfo[] devices = myAudioManager.getDevices(AudioManager.GET_DEVICES_INPUTS);
            for (AudioDeviceInfo deviceInfo : devices) {
                Log.d("SSNVS", deviceInfo.getProductName().toString());
                if (deviceInfo.getProductName().equals("Bluetooth music")) {
                    myAudioManager.startBluetoothSco();
                    return deviceInfo.getId();
                }
            }
            throw new IllegalStateException("Device not found");
        } else {
            throw new IllegalStateException("Incompatible Android version");
        }
    }

    private String printAudioDevices() {
        AudioManager myAudioManager = (AudioManager) getSystemService(Context.AUDIO_SERVICE);
        if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.M) {
            StringBuilder s = new StringBuilder();
            AudioDeviceInfo[] devices = myAudioManager.getDevices(AudioManager.GET_DEVICES_INPUTS);
            for (AudioDeviceInfo deviceInfo : devices) {
                s.append(", ").append(deviceInfo.getProductName());
            }
            return s.toString();
        } else {
//            throw new IllegalStateException("Incompatible Android version");
            return "incompatible android version";
        }
    }

    @Override
    public void onRequestPermissionsResult(int requestCode,
                                           @NonNull String[] permissions,
                                           @NonNull int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
        if (permissionHandler.allPermissionsGranted()) {
            binding.sampleText.setText("Permission granted");
        } else {
            // TODO show instructions
            finish();
        }
    }

    @Override
    public void onClick(View view) {

        if (view == binding.buttonRecord) {
            binding.sampleText.setText(printAudioDevices());

            if (isRecording) {
                stopRecording();
                binding.buttonRecord.setText(R.string.start_recording);
                isRecording = false;
            } else {
                try {
                    startRecording();
                    binding.buttonRecord.setText(R.string.stop_recording);
                    isRecording = true;
                } catch (IllegalStateException e) {
                    e.printStackTrace();
                }
            }
        } else if (view == binding.buttonConnect) {
            Log.d("SSNVS", "connectButtonClicked");
            try {
                int deviceID = getHeadsetInputDeviceID();
                initialize(deviceID);
                binding.buttonRecord.setEnabled(true);
            } catch (IllegalStateException e) {
                Log.e("SSNVS", "", e);
            }
        }
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native void initialize(int deviceID);

    public native void startRecording();

    public native void stopRecording();

}
