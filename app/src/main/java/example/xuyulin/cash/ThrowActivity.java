package example.xuyulin.cash;

import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;

import example.xuyulin.xiaosheng.R;

/**
 * Create by 徐玉林.
 * Create on 2019-11-05.
 * Describe: =>
 */
public class ThrowActivity extends AppCompatActivity {

    static {
        System.loadLibrary("xiaosheng-lib");
    }

    public static void exceptionCallBack() {
        int a = 20 / 0;
        Log.e("xyl", "数值：" + a);
    }

    public static void normalCallBack() {
        Log.e("xyl", "normalCallBack调用");
    }

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_throw);
        doit();
    }

    public static native void doit();

}
