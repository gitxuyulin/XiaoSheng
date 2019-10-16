package example.xuyulin.xiaosheng;

import android.util.Log;

/**
 * Create by 徐玉林.
 * Create on 2019-10-12.
 * Describe: =>
 */
public class Father {

    protected String name;

    public Father(String name) {
        this.name = name;
        Log.e("xyl", "father初始化" + name);
    }

    public String getName() {
        Log.e("xyl", "father获取名字" + name);
        return name;
    }

    public void start() {
        Log.e("xyl", "Father start");
    }
}
