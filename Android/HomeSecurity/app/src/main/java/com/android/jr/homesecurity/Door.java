package com.android.jr.homesecurity;

import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v4.widget.SwipeRefreshLayout;
import android.support.v7.app.AppCompatActivity;
import android.widget.ArrayAdapter;
import android.widget.ListView;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.ArrayList;

public class Door extends AppCompatActivity {

    ListView listView;
    ArrayList<String> arrayList;
    ArrayAdapter arrayAdapter;

    Connection conn=null;
    PreparedStatement ps=null;
    ResultSet rs=null;

    SwipeRefreshLayout swipe;
    void reList(){
        try{
            arrayList.clear();
            conn=ConnUtil.getConnection();
            String sql="select * from door order by time desc";
            ps=conn.prepareStatement(sql);
            Statement st=conn.createStatement();
            st.execute("use sil5759");
            rs=st.executeQuery(sql);
            while(rs.next()){
                String d="";
                if(rs.getInt(1)==1){
                    d="현관문 열림   ";
                }else if(rs.getInt(1)==2){
                    d="현관문 닫힘   ";
                }else if(rs.getInt(1)==3){
                    d="비밀번호 오류  ";
                }
                arrayList.add(d+rs.getString(2));
            }
            listView.setAdapter(arrayAdapter);

        }catch (Exception e){

        }finally {
            ConnUtil.close(ps,conn);
        }
    }


    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.door);
        setTitle("\n 출입 기록");
        getSupportActionBar().setIcon(R.drawable.no_icon);
        getSupportActionBar().setDisplayShowHomeEnabled(true);

        arrayList=new ArrayList<String>();
        listView=(ListView)findViewById(R.id.doorList);
        arrayAdapter=new ArrayAdapter<String>(this,android.R.layout.simple_list_item_1,arrayList);
        reList();
        swipe=(SwipeRefreshLayout)findViewById(R.id.swipe3);
        swipe.setOnRefreshListener(new SwipeRefreshLayout.OnRefreshListener() {
            @Override
            public void onRefresh() {
                reList();
                swipe.setRefreshing(false);
            }
        });
    }
}
