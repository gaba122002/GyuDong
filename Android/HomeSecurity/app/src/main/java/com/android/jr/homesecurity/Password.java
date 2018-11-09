package com.android.jr.homesecurity;

import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.Statement;


public class Password extends AppCompatActivity {

    Button button1;
    EditText edit1;

    Connection conn=null;
    PreparedStatement ps=null;
    ResultSet rs=null;

    void setting(){
        try{
            conn=ConnUtil.getConnection();
            String sql="update password set password=" + edit1.getText().toString() + "";
            Statement st=conn.createStatement();
            st.execute("use sil5759");
            ps=conn.prepareStatement(sql);
            ps.executeUpdate();


        }catch(Exception e){

        }finally {
            ConnUtil.close(ps,conn);
        }
    }

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.password);
        setTitle("\n 패스워드 설정");
        getSupportActionBar().setIcon(R.drawable.no_icon);
        getSupportActionBar().setDisplayShowHomeEnabled(true);

        button1 = (Button) findViewById(R.id.setting_button);
        edit1 = (EditText) findViewById(R.id.password);

        button1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                setting();
                edit1.setText("");
                Toast.makeText(getApplicationContext(), "비밀번호 변경완료", Toast.LENGTH_LONG).show();
            }
        });
    }
}

