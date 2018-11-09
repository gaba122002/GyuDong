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

public class Person extends AppCompatActivity {
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
            String sql="select * from person order by time desc";
            ps=conn.prepareStatement(sql);
            Statement st=conn.createStatement();
            st.execute("use sil5759");
            rs=st.executeQuery(sql);
            while(rs.next()){
                arrayList.add(rs.getString(1)+"번방   "+rs.getString(2));
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
        setContentView(R.layout.person);
        setTitle("\n 침입 기록");
        getSupportActionBar().setIcon(R.drawable.no_icon);
        getSupportActionBar().setDisplayShowHomeEnabled(true);

        arrayList=new ArrayList<String>();
        listView=(ListView)findViewById(R.id.personList);
        arrayAdapter=new ArrayAdapter<String>(this,android.R.layout.simple_list_item_1,arrayList);
        reList();

        swipe=(SwipeRefreshLayout)findViewById(R.id.swipe1);
        swipe.setOnRefreshListener(new SwipeRefreshLayout.OnRefreshListener() {
            @Override
            public void onRefresh() {
                reList();
                swipe.setRefreshing(false);
            }
        });
    }
}
