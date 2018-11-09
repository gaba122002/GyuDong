package com.android.jr.homesecurity;

import android.content.Intent;
import android.os.Bundle;
import android.os.StrictMode;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.Switch;
import android.widget.TextView;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.Statement;

public class MainActivity extends AppCompatActivity {

    Switch sw;
    Button b1,b2,b3,b4,b5;
    TextView text1;
    Connection conn=null;
    PreparedStatement ps=null;
    ResultSet rs=null;
    int mode;



    @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        getSupportActionBar().setIcon(R.drawable.no_icon);
        getSupportActionBar().setDisplayShowHomeEnabled(true);

        StrictMode.ThreadPolicy policy = new StrictMode.ThreadPolicy.Builder().permitAll().build();
        StrictMode.setThreadPolicy(policy);
        text1=(TextView)findViewById(R.id.text1);
        sw=(Switch)findViewById(R.id.switch1);


        try{
            conn=ConnUtil.getConnection();
            String sql="select mode from semode where num=1004";
            ps=conn.prepareStatement(sql);
            Statement st=conn.createStatement();
            st.execute("use sil5759");
            rs=st.executeQuery(sql);
            while(rs.next()){
                mode=rs.getInt(1);
            }

        }catch (Exception e){
            text1.setText(e.getMessage());
        }finally {
            ConnUtil.close(ps,conn);
        }

        if(mode==1){
            sw.setChecked(true);
            text1.setText("보안모드 : 작동중");
        }else{
            sw.setChecked(false);
            text1.setText("보안모드 : 작동안함");
        }




        sw.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton compoundButton, boolean b) {
                if(mode==0){
                    try{
                        conn=ConnUtil.getConnection();
                        String sql="update semode set mode=1 where num=1004";
                        Statement st=conn.createStatement();
                        st.execute("use sil5759");
                        ps=conn.prepareStatement(sql);
                        ps.executeUpdate();
                        text1.setText("보안모드 : 작동중");
                        mode=1;



                    }catch(Exception e){
                        text1.setText(e.getMessage());
                    }finally {
                        ConnUtil.close(ps,conn);
                    }
                }else{
                    try{
                        conn=ConnUtil.getConnection();
                        String sql="update semode set mode=0 where num=1004";
                        Statement st=conn.createStatement();
                        st.execute("use sil5759");
                        ps=conn.prepareStatement(sql);
                        ps.executeUpdate();
                        text1.setText("보안모드 : 작동안함");
                        mode=0;
                    }catch(Exception e){
                        text1.setText(e.getMessage());

                    }finally {
                        ConnUtil.close(ps,conn);
                    }
                }
            }
        });

        b1=(Button)findViewById(R.id.button1);
        b2=(Button)findViewById(R.id.button2);
        b3=(Button)findViewById(R.id.button3);
        b4=(Button)findViewById(R.id.button4);
        b5=(Button)findViewById(R.id.button5);

        b1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent=new Intent(MainActivity.this,Person.class);

                startActivity(intent);
            }
        });
        b2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent=new Intent(MainActivity.this,Fire.class);
                startActivity(intent);
            }
        });
        b3.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent=new Intent(MainActivity.this,Door.class);
                startActivity(intent);
            }
        });
        b4.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent=new Intent(MainActivity.this,Camera.class);
                startActivity(intent);
            }
        });
        b5.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent=new Intent(MainActivity.this,Password.class);
                startActivity(intent);
            }
        });
    }
}
