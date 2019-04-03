package com.sri.com.smartcar;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    public static ImageView imgv1;
    public static ImageView imgv2;

    int imag[]={R.drawable.red,R.drawable.green};


    Button but,s1,s2,but2;
    public static TextView tvv;

    public static String slot1;
    public static String slot2;



    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        but=(Button)findViewById(R.id.but);
        but2=(Button)findViewById(R.id.bt2);
        //tvv=(TextView)findViewById(R.id.tv1);
        s1=(Button)findViewById(R.id.s1);
        s2=(Button)findViewById(R.id.s2);
        imgv1=(ImageView)findViewById(R.id.iv1);
        imgv2=(ImageView)findViewById(R.id.iv2);


        try {

            but.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {

                    fetch ob = new fetch();

                    ob.execute();







                }
            });

        }catch (Exception e)
        {
            Toast.makeText(this.getApplicationContext(),e+"",Toast.LENGTH_LONG).show();
        }


        but2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                open2();
            }
        });



    }


    public void open2()
    {


        Intent i=new Intent(this,MainActivity2.class);
        startActivity(i);


    }


}

