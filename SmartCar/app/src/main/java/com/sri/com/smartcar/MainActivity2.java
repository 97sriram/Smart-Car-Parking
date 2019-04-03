package com.sri.com.smartcar;

import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity2 extends AppCompatActivity {


    static TextView tv,tvv;
    Button bt,bt2;
    TextView tee;

    static String enrf="";
    static String parf="";

    ImageView iv;

    int img[]={R.drawable.greentick,R.drawable.warning};


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main2);



        tv=(TextView)findViewById(R.id.ttt);
        tvv=(TextView)findViewById(R.id.tttt);



        bt=(Button)findViewById(R.id.bt1);
        bt2=(Button)findViewById(R.id.bt2);

        tee=(TextView)findViewById(R.id.te);

        iv=(ImageView)findViewById(R.id.imageView);

        try {

            bt.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {

                    fett();






                }
            });

        }catch (Exception e)
        {
            Toast.makeText(this.getApplicationContext(), e + "", Toast.LENGTH_LONG).show();
        }



        bt2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                upd();
            }
        });



    }

    public void fett()
    {
        fetch2 ob = new fetch2();

        ob.execute();
        enrf=ob.rfid;

        fetch3 ob1=new fetch3();
        ob1.execute();
        parf=ob1.rfid;









    }

    public void upd()
    {
        if(enrf.equals(parf))
        {
            iv.setImageResource(img[0]);
            tee.setText("Successfully parked in a right place...");
        }
        else
        {
            iv.setImageResource(img[1]);
            tee.setText("Parked in different slot!!!!!!");
        }
    }
}
