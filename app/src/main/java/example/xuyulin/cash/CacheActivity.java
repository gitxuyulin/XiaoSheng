package example.xuyulin.cash;

import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;

import example.xuyulin.xiaosheng.R;

/**
 * Create by 徐玉林.
 * Create on 2019-10-22.
 * Describe: =>使用时缓存
 */
public class CacheActivity extends AppCompatActivity {

    private String str = "java";

    static {
        System.loadLibrary("xiaosheng-lib");
    }

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_cash);
        initParams();
    }

    public void initParams() {
        accessField();
        Log.e("xyl", "字符串的值:" + str);
    }

    public native void accessField();//访问str成员变量
}
