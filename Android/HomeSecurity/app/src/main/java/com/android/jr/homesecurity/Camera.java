package com.android.jr.homesecurity;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.webkit.WebSettings;
import android.webkit.WebView;

public class Camera extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.camera);
        setTitle("\n CCTV");
        getSupportActionBar().setIcon(R.drawable.no_icon);
        getSupportActionBar().setDisplayShowHomeEnabled(true);

        WebView webView = (WebView) findViewById(R.id.webView);
        webView.setPadding(0, 0, 0, 0);
        webView.setInitialScale(100);
        webView.getSettings().setBuiltInZoomControls(false);
        webView.getSettings().setJavaScriptEnabled(true);
        webView.getSettings().setLoadWithOverviewMode(true);
        webView.getSettings().setUseWideViewPort(true);
        webView.getSettings().setLayoutAlgorithm(WebSettings.LayoutAlgorithm.NORMAL);

        String url = "http://219.248.131.133:8080/javascript_simple.html";
        webView.loadUrl(url);


    }
}