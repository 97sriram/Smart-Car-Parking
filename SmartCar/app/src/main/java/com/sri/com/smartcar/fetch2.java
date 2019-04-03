package com.sri.com.smartcar;


import android.os.AsyncTask;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;

/**
 * Created by sriram on 22/03/18.
 */
public class fetch2 extends AsyncTask<Void,Void,Void> {

    String d="";
    String dh;
    String sinp,doup="";

    int g=0;

    String rfid="";




    @Override
    protected Void doInBackground(Void... params) {

        try {
            URL url = new URL("https://scps.000webhostapp.com/smartcar/read_allrf.php");

            HttpURLConnection httpURLConnection = (HttpURLConnection) url.openConnection();
            InputStream inputStream = httpURLConnection.getInputStream();
            BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(inputStream));

            String l="";

            while((l=bufferedReader.readLine())!=null)
            {
                //l=bufferedReader.readLine();

                d=d+l;
            }



            JSONArray ja = new JSONArray(d);

            g=ja.length();
            dh=g+"";


            /*JSONObject jo=(new JSONObject()).getJSONObject("smart");
            slot1=jo.getString("s1");
            slot2=jo.getString("s2");

            dp=slot1+slot2;*/

            int i=ja.length()-1;
            /*for(int i=0;i<ja.length();i++)
            {*/

            JSONObject jo= (JSONObject) ja.get(i);

            rfid=jo.get("s1")+"";



            /*sinp="Slot1 :" + jo.get("s1")+ "\n" +
                        "Slot2 :" +jo.get("s2") +"\n\n";


            doup = doup + sinp;*/


            /*}
*/


        } catch (MalformedURLException e) {
            e.printStackTrace();

        } catch (IOException e) {
            //e.printStackTrace();
        } catch (JSONException e) {
            e.printStackTrace();
        }


        return null;
    }

    @Override
    protected void onPostExecute(Void aVoid) {
        super.onPostExecute(aVoid);

        //MainActivity.slot1=this.slot1;
        //MainActivity.slot2=this.slot2;

        MainActivity2.tvv.setText("Your Car RFID Tag number:"+rfid);

        MainActivity2.enrf=rfid;



    }
}
