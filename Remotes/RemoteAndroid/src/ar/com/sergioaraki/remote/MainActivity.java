package ar.com.sergioaraki.remote;

import org.apache.http.HttpResponse;
import org.apache.http.HttpStatus;
import org.apache.http.StatusLine;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.DefaultHttpClient;

import com.actionbarsherlock.app.SherlockActivity;
import com.actionbarsherlock.view.MenuInflater;
import com.actionbarsherlock.view.MenuItem;

import android.os.Bundle;
import android.os.Handler;
import android.view.View;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.TextView;
import android.widget.ToggleButton;
import android.content.Context;

public class MainActivity extends SherlockActivity {

	protected Context context;
	private TextView timerValue;
	private ToggleButton toggleTimer;
	
	String baseUrl = "http://10.255.110.148:8080";
	
	long elapsed_time = 0;

    //runs without a timer by reposting this handler at the end of the runnable
    Handler timerHandler = new Handler();
    Runnable timerRunnable = new Runnable() {

        @Override
        public void run() {
        	elapsed_time = elapsed_time + 1;
            int seconds = (int) (elapsed_time) % 60;
            int minutes = (int) (elapsed_time) / 60 % 60;
            int hours = (int) (elapsed_time) / 3600;

            timerValue.setText(String.format("%02d:%02d:%02d", hours, minutes, seconds));
            
            if(hours < 99) 
            	timerHandler.postDelayed(this, 1000);
        }
    };
	 
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        context = getApplicationContext();
        getSupportActionBar().setTitle(R.string.app_name);
        
        timerValue = (TextView) findViewById(R.id.lTimer);
        
        toggleTimer = (ToggleButton) findViewById(R.id.bTimer);
        toggleTimer.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                if (isChecked) {
                	timerHandler.postDelayed(timerRunnable, 0);
                } else {
                	timerHandler.removeCallbacks(timerRunnable);
                }
            }
        });
        
        Button buttonPrev = (Button) findViewById(R.id.bPrev);
        buttonPrev.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
            	HttpClient httpclient = new DefaultHttpClient();
                HttpResponse response;
				try {
					response = httpclient.execute(new HttpGet(baseUrl+"/prev.html"));
					StatusLine statusLine = response.getStatusLine();
	                if(statusLine.getStatusCode() == HttpStatus.SC_OK){
	                    //
	                } else{
	                    //Closes the connection.
	                	response.getEntity().getContent().close();
	                }
				} catch (Exception e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
            }
        });
        
        Button buttonNext = (Button) findViewById(R.id.bNext);
        buttonNext.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
            	HttpClient httpclient = new DefaultHttpClient();
                HttpResponse response;
				try {
					response = httpclient.execute(new HttpGet(baseUrl+"/next.html"));
					StatusLine statusLine = response.getStatusLine();
	                if(statusLine.getStatusCode() == HttpStatus.SC_OK){
	                    //
	                } else{
	                    //Closes the connection.
	                	response.getEntity().getContent().close();
	                }
				} catch (Exception e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
            }
        });
    }
 
    @Override
    public boolean onCreateOptionsMenu(com.actionbarsherlock.view.Menu menu) {
        MenuInflater inflater = getSupportMenuInflater();
        inflater.inflate(R.menu.main, menu);
        return super.onCreateOptionsMenu(menu);
    }
    
    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle item selection
        switch (item.getItemId()) {
            case R.id.reset:
            	toggleTimer.setChecked(false);
            	elapsed_time = 0;
            	timerValue.setText("00:00:00");
                return true;
            default:
                return super.onOptionsItemSelected(item);
        }
    }

}
