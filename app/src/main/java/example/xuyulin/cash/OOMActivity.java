package example.xuyulin.cash;

import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

import example.xuyulin.xiaosheng.R;

/**
 * Create by 徐玉林.
 * Create on 2019-11-04.
 * Describe: =>十
 */
public class OOMActivity extends AppCompatActivity implements View.OnClickListener {

    private EditText mOOMEdittext;
    private Button mOOMButton;

    static {
        System.loadLibrary("xiaosheng-lib");
    }

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_oom);
        mOOMEdittext = findViewById(R.id.oom_edittext);
        mOOMButton = findViewById(R.id.oom_button);
        mOOMButton.setOnClickListener(this);
    }

    @Override
    public void onClick(View v) {
        if (v.getId() == R.id.oom_button) {
            String[] strings = getStrings(Integer.parseInt(mOOMEdittext.getText().toString()), "I Love You %d Year");
        }
    }

    public native String[] getStrings(int count, String sample);
}
