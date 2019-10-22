package example.xuyulin.cash;

import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;

import example.xuyulin.xiaosheng.R;

/**
 * Create by 徐玉林.
 * Create on 2019-10-22.
 * Describe: =>
 */
public class CacheActivity extends AppCompatActivity {

    private String str = "java";

    static {
        System.loadLibrary("xiaosheng-lib");
        initIDs();
    }

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_cash);
//        initParams();
        nativeMethod();
    }

    public void initParams() {
        char chars[] = {'天', '地', '玄', '黄'};
        Log.e("xyl", "字符串的值:" + newString(chars, chars.length));

//        accessField();
//        Log.e("xyl", "字符串的值:" + str);
    }

    //---------------------使用时缓存-------------------------
    //访问str成员变量
    public native void accessField();

    //根据字符数组和制定长度创建string对象
    public native String newString(char[] chars, int length);

    //----------------------类静态初始化缓存------------------------

    public void callBack() {
        Log.e("xyl", "CacheActivity callBack");
    }

    public static native void initIDs();

    public native void nativeMethod();
}
