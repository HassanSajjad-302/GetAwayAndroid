package com.example.myapplication;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.os.Bundle;
import android.text.InputType;
import android.view.View;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity implements View.OnClickListener{

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        ImageButton clickButton = (ImageButton) findViewById(R.id.imageButton);
        clickButton.setOnClickListener(this);

        register();
        startGame();
    }

    @Override
    protected void onResume() {
        super.onResume();
    }

    public void onClick(View v) {
        EditText editText = findViewById(R.id.editTextTextPersonName);
        TextView tv = findViewById(R.id.sample_text);
        userTerminalInput(editText.getText().toString());
        editText.setText("");
    }

    //These Are Being Called From C++ Code
    public void clearAndPrint(String toPrint){
        runOnUiThread(() -> {

            // Stuff that updates the UI
            TextView tv = findViewById(R.id.sample_text);
            tv.setText(toPrint);
        });

    }

    public void print(String toPrint){
        runOnUiThread(() -> {
            // Stuff that updates the UI
            TextView tv = findViewById(R.id.sample_text);
            String text = tv.getText().toString();
            text += toPrint;
            tv.setText(text);
        });

    }

    public void setKeyBoard(boolean numberKeyBoard){
        runOnUiThread(() -> {
            EditText editText = findViewById(R.id.editTextTextPersonName);


            if(numberKeyBoard){
                editText.setInputType(InputType.TYPE_CLASS_DATETIME);
            }else{
                editText.setInputType(InputType.TYPE_CLASS_TEXT);
            }
        });
    }

    public void exitApp(){
        finish();
    }
    public native void register();
    public native void startGame();
    public native void userTerminalInput(String userInputString);
}